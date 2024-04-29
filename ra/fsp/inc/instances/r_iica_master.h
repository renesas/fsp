/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup IICA_MASTER
 * @{
 **********************************************************************************************************************/

#ifndef R_IICA_MASTER_H
#define R_IICA_MASTER_H

#include "bsp_api.h"
#include "r_iica_master_cfg.h"
#include "r_i2c_master_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** IICA communication reservation parameter definition */
typedef enum e_iica_master_comm_rez
{
    IICA_MASTER_COMM_REZ_ENABLED  = 0, // Enable communication reservation
    IICA_MASTER_COMM_REZ_DISABLED = 1  // Disable communication reservation
} iica_master_comm_rez_t;

/** IICA clock settings */
typedef struct iica_master_clock_settings
{
    uint8_t                cks_value;      // Internal reference clock select
    uint8_t                iicwh_value;    // High-level period of SCL clock
    uint8_t                iicwl_value;    // Low-level period of SCL clock
    uint8_t                digital_filter; // Digital filter operation select
    iica_master_comm_rez_t comm_rez;       // Communication reservation select
} iica_master_clock_settings_t;

/** Configuration settings for IICA pins */
typedef struct iica_master_pin_settings
{
    bsp_io_port_pin_t pin;             ///< The pin
    uint32_t          cfg;             ///< Configuration for the pin
} iica_master_pin_settings_t;

/** IICA control structure. DO NOT INITIALIZE. */
typedef struct st_iica_master_instance_ctrl
{
    i2c_master_cfg_t const * p_cfg;     // Pointer to the configuration structure
    uint32_t                 slave;     // The address of the slave device
    i2c_master_addr_mode_t   addr_mode; // Indicates how slave fields should be interpreted

    uint32_t      open;                 // Flag to determine if the device is open
    R_IICA_Type * p_reg;                // Base register for this channel

    /* Current transfer information. */
    uint8_t * p_buff;                   // Holds the data associated with the transfer
    uint32_t  total;                    // Holds the total number of data bytes to transfer
    uint32_t  loaded;                   // Tracks the number of data bytes written to the register

    uint8_t addr_low;                   // Holds the last address byte to issue
    uint8_t addr_high;                  // Holds the first address byte to issue in 10-bit mode
    uint8_t addr_total;                 // Holds the total number of address bytes to transfer
    uint8_t addr_loaded;                // Tracks the number of address bytes written to the register

    volatile bool read;                 // Holds the direction of the data byte transfer
    volatile bool restart;              // Holds whether or not the restart should be issued when done
    volatile bool restarted;            // Tracks whether or not a restart was issued during the previous transfer
    volatile bool err;                  // Tracks whether or not an error occurred during processing
    volatile bool dummy_read_completed; // Tracks whether the dummy read is performed

    /* Pointer to callback and optional working memory */
    void (* p_callback)(i2c_master_callback_args_t *);

    /* Pointer to context to be passed into callback function */
    void const * p_context;
} iica_master_instance_ctrl_t;

/** R_IICA extended configuration */
typedef struct st_iica_master_extended_cfg
{
    iica_master_clock_settings_t clock_settings;   // IICA clock settings
    iica_master_pin_settings_t   sda_pin_settings; ///< SDAA pin setting
    iica_master_pin_settings_t   scl_pin_settings; ///< SCLAA pin setting
} iica_master_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern i2c_master_api_t const g_iica_master_on_iica;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_IICA_MASTER_Open(i2c_master_ctrl_t * const p_api_ctrl, i2c_master_cfg_t const * const p_cfg);

fsp_err_t R_IICA_MASTER_Read(i2c_master_ctrl_t * const p_api_ctrl,
                             uint8_t * const           p_dest,
                             uint32_t const            bytes,
                             bool const                restart);
fsp_err_t R_IICA_MASTER_Write(i2c_master_ctrl_t * const p_api_ctrl,
                              uint8_t * const           p_src,
                              uint32_t const            bytes,
                              bool const                restart);
fsp_err_t R_IICA_MASTER_Abort(i2c_master_ctrl_t * const p_api_ctrl);
fsp_err_t R_IICA_MASTER_SlaveAddressSet(i2c_master_ctrl_t * const    p_api_ctrl,
                                        uint32_t const               slave,
                                        i2c_master_addr_mode_t const addr_mode);
fsp_err_t R_IICA_MASTER_Close(i2c_master_ctrl_t * const p_api_ctrl);
fsp_err_t R_IICA_MASTER_CallbackSet(i2c_master_ctrl_t * const          p_api_ctrl,
                                    void (                           * p_callback)(i2c_master_callback_args_t *),
                                    void const * const                 p_context,
                                    i2c_master_callback_args_t * const p_callback_memory);
fsp_err_t R_IICA_MASTER_StatusGet(i2c_master_ctrl_t * const p_api_ctrl, i2c_master_status_t * p_status);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_IICA_MASTER_H

/*******************************************************************************************************************//**
 * @} (end defgroup IICA_MASTER)
 **********************************************************************************************************************/
