/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup IICA_SLAVE
 * @{
 **********************************************************************************************************************/

#ifndef R_IICA_SLAVE_H
#define R_IICA_SLAVE_H

#include "bsp_api.h"
#include "r_iica_slave_cfg.h"
#include "r_i2c_slave_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/** IICA clock settings */
typedef struct iica_slave_clock_settings
{
    uint8_t operation_clock;           // Internal Reference Clock Select
    uint8_t cks_value;                 // Transfer clock value
    uint8_t iicwh_value;               // High-level period of SCL clock
    uint8_t iicwl_value;               // Low-level period of SCL clock
    uint8_t digital_filter;            // Digital filter operation select
} iica_slave_clock_settings_t;

/** Configuration settings for IICA pins */
typedef struct iica_slave_pin_settings
{
    bsp_io_port_pin_t pin;             ///< The pin
    uint32_t          cfg;             ///< Configuration for the pin
} iica_slave_pin_settings_t;

/* IICA control structure. DO NOT INITIALIZE. */
typedef struct st_iica_slave_instance_ctrl
{
    i2c_slave_cfg_t const * p_cfg;     // Information describing IICA device
    uint32_t                open;      // Flag to determine if the device is open
    R_IICA0_Type          * p_reg;     // Base register for this channel

    /* Current transfer information. */
    uint8_t * p_buff;                  // Holds the data associated with the transfer
    uint32_t  total;                   // Holds the total number of data bytes to transfer
    uint32_t  loaded;                  // Tracks the number of data bytes written to the register (will clear util next call of read/write)
    uint32_t  total_loaded;            // Tracks the number of data bytes written to the register (will clear util stop)

    /* Pointer to callback and optional working memory */
    void (* p_callback)(i2c_slave_callback_args_t *);

    /* Pointer to context to be passed into callback function */
    void * p_context;

    uint8_t               communication_dir;  // Communication direction: 0 for read, R_IICA_IICS0_TRC_Msk for write
    uint8_t               communication_mode; // Communication mode: 0 for clear, 1 for data communication is performed
    bool                  tenbitaddr_matched; // Saves 10 bit address match status
    i2c_slave_addr_mode_t addr_mode;          // Indicates how slave fields should be interpreted
} iica_slave_instance_ctrl_t;

/** R_IICA_SLAVE extended configuration */
typedef struct st_iica_slave_extended_cfg
{
    iica_slave_clock_settings_t clock_settings;   // IICA clock settings
    iica_slave_pin_settings_t   sda_pin_settings; ///< SDAA pin setting
    iica_slave_pin_settings_t   scl_pin_settings; ///< SCLAA pin setting
} iica_slave_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 ***********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern i2c_slave_api_t const g_iica_slave_on_iica;

/** @endcond */

/***********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

fsp_err_t R_IICA_SLAVE_Open(i2c_slave_ctrl_t * const p_api_ctrl, i2c_slave_cfg_t const * const p_cfg);
fsp_err_t R_IICA_SLAVE_Read(i2c_slave_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t R_IICA_SLAVE_Write(i2c_slave_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);
fsp_err_t R_IICA_SLAVE_Close(i2c_slave_ctrl_t * const p_api_ctrl);
fsp_err_t R_IICA_SLAVE_CallbackSet(i2c_slave_ctrl_t * const          p_api_ctrl,
                                   void (                          * p_callback)(i2c_slave_callback_args_t *),
                                   void * const                      p_context,
                                   i2c_slave_callback_args_t * const p_callback_memory);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_IICA_SLAVE_H

/*******************************************************************************************************************//**
 * @} (end defgroup IICA_SLAVE)
 ***********************************************************************************************************************/
