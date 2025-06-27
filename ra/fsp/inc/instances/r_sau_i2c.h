/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup SAU_I2C
 * @{
 **********************************************************************************************************************/

#ifndef R_SAU_I2C_H
#define R_SAU_I2C_H

#include "bsp_api.h"
#include "r_sau_i2c_cfg.h"
#include "r_i2c_master_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Operation clock */
typedef enum e_sau_i2c_operation_clock
{
    SAU_I2C_MASTER_OPERATION_CLOCK_CK0 = 0, ///< Operating clock select CK0
    SAU_I2C_MASTER_OPERATION_CLOCK_CK1 = 1, ///< Operating clock select CK1
} sau_i2c_operation_clock_t;

/** I2C clock settings */
typedef struct st_sau_i2c_clock_settings
{
    uint8_t stclk;                             ///< Bit rate register settings
    sau_i2c_operation_clock_t operation_clock; ///< I2C operating clock select
} sau_i2c_clock_settings_t;

/** I2C control structure. DO NOT INITIALIZE. */
typedef struct st_sau_i2c_instance_ctrl
{
    i2c_master_cfg_t const * p_cfg;    ///< Pointer to the configuration structure
    uint32_t                 open;     ///< Flag to determine if the device is open
    R_SAU0_Type            * p_reg;    ///< Base register for this channel

    /* Current transfer information. */
    uint8_t     * p_buff;              ///< Holds the data associated with the transfer
    uint32_t      total;               ///< Holds the total number of data bytes to transfer
    uint32_t      loaded;              ///< Tracks the number of data bytes written to the register
    volatile bool activation_on_txi;   // Tracks whether the transfer is activated on TXI interrupt

    volatile bool read;                ///< Holds the direction of the data byte transfer
    volatile bool restart;             ///< Holds whether or not the restart should be issued when done
    volatile bool restarted;           ///< Tracks whether or not a restart was issued during the previous transfer
    volatile bool do_dummy_read;       ///< Tracks whether a dummy read is issued on the first RX
    uint8_t       slave;               ///< The address of the slave device

    /* Pointer to callback and optional working memory */
    void (* p_callback)(i2c_master_callback_args_t *);

    /* Pointer to context to be passed into callback function */
    void * p_context;
} sau_i2c_instance_ctrl_t;

/** SAU I2C extended configuration */
typedef struct st_sau_i2c_extended_cfg
{
    sau_i2c_clock_settings_t clock_settings; ///< I2C clock settings
    uint8_t delay_time;                      ///< The delay time of the slave device
    uint8_t i2c_unit;                        ///< The SAU unit corresponding to the selected channel
} sau_i2c_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern i2c_master_api_t const g_i2c_master_on_sau;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_Open(i2c_master_ctrl_t * const p_api_ctrl, i2c_master_cfg_t const * const p_cfg);
fsp_err_t R_SAU_I2C_Close(i2c_master_ctrl_t * const p_api_ctrl);
fsp_err_t R_SAU_I2C_Read(i2c_master_ctrl_t * const p_api_ctrl,
                         uint8_t * const           p_dest,
                         uint32_t const            bytes,
                         bool const                restart);
fsp_err_t R_SAU_I2C_Write(i2c_master_ctrl_t * const p_api_ctrl,
                          uint8_t * const           p_src,
                          uint32_t const            bytes,
                          bool const                restart);
fsp_err_t R_SAU_I2C_Abort(i2c_master_ctrl_t * const p_api_ctrl);
fsp_err_t R_SAU_I2C_SlaveAddressSet(i2c_master_ctrl_t * const    p_api_ctrl,
                                    uint32_t const               slave,
                                    i2c_master_addr_mode_t const addr_mode);
fsp_err_t R_SAU_I2C_CallbackSet(i2c_master_ctrl_t * const          p_api_ctrl,
                                void (                           * p_callback)(i2c_master_callback_args_t *),
                                void * const                       p_context,
                                i2c_master_callback_args_t * const p_callback_memory);
fsp_err_t R_SAU_I2C_StatusGet(i2c_master_ctrl_t * const p_api_ctrl, i2c_master_status_t * p_status);
fsp_err_t R_SAU_I2C_Start(sau_i2c_instance_ctrl_t * const p_ctrl);
fsp_err_t R_SAU_I2C_Stop(sau_i2c_instance_ctrl_t * const p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup SAU_I2C)
 **********************************************************************************************************************/
