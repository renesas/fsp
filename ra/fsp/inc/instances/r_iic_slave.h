/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup IIC_SLAVE
 * @{
 **********************************************************************************************************************/

#ifndef R_IIC_SLAVE_H
#define R_IIC_SLAVE_H

#include "bsp_api.h"
#include "r_iic_slave_cfg.h"
#include "r_i2c_slave_api.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define IIC_SLAVE_CODE_VERSION_MAJOR    (1U)
#define IIC_SLAVE_CODE_VERSION_MINOR    (0U)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/* IIC Slave transaction enumeration */
typedef enum e_iic_slave_transfer_dir_option
{
    IIC_SLAVE_TRANSFER_DIR_MASTER_READ_SLAVE_WRITE = 0x0,
    IIC_SLAVE_TRANSFER_DIR_MASTER_WRITE_SLAVE_READ = 0x1,
    IIC_SLAVE_TRANSFER_DIR_NOT_ESTABLISHED         = 0x2
} iic_slave_transfer_dir_t;

/** I2C clock settings */
typedef struct iic_slave_clock_settings
{
    uint8_t cks_value;                 ///< Internal Reference Clock Select
    uint8_t brl_value;                 ///< Low-level period of SCL clock
    uint8_t digital_filter_stages;     ///< Number of digital filter stages based on brl_value
} iic_slave_clock_settings_t;

/* I2C control structure. DO NOT INITIALIZE. */
typedef struct st_iic_slave_instance_ctrl
{
    i2c_slave_cfg_t const * p_cfg;               // Information describing I2C device
    uint32_t                open;                // Flag to determine if the device is open
    R_IIC0_Type           * p_reg;               // Base register for this channel

    /* Current transfer information. */
    uint8_t     * p_buff;                        // Holds the data associated with the transfer
    uint32_t      total;                         // Holds the total number of data bytes to transfer
    uint32_t      remain;                        // Tracks the remaining data bytes to transfer
    uint32_t      loaded;                        // Tracks the number of data bytes written to the register
    uint32_t      transaction_count;             // Tracks the actual number of transactions
    volatile bool notify_request;                // Track whether the master request is notified to the application
    volatile iic_slave_transfer_dir_t direction; // Holds the direction of the data byte transfer
    volatile bool slave_busy;                    // Tracks if the slave is busy performing a transaction
    volatile bool do_dummy_read;                 // Tracks whether a dummy read is issued on the first RX
    volatile bool start_interrupt_enabled;       // Tracks whether the start interrupt is enabled
    volatile bool transaction_completed;         // Tracks whether previous transaction restarted
} iic_slave_instance_ctrl_t;

/** R_IIC_SLAVE extended configuration */
typedef struct st_iic_slave_extended_cfg
{
    iic_slave_clock_settings_t clock_settings; ///< I2C Clock settings
} iic_slave_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 ***********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern i2c_slave_api_t const g_i2c_slave_on_iic;

/** @endcond */

/***********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

fsp_err_t R_IIC_SLAVE_Open(i2c_slave_ctrl_t * const p_api_ctrl, i2c_slave_cfg_t const * const p_cfg);
fsp_err_t R_IIC_SLAVE_Read(i2c_slave_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t R_IIC_SLAVE_Write(i2c_slave_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);
fsp_err_t R_IIC_SLAVE_Close(i2c_slave_ctrl_t * const p_api_ctrl);
fsp_err_t R_IIC_SLAVE_VersionGet(fsp_version_t * const p_version);

#endif                                 // R_IIC_SLAVE_H

/*******************************************************************************************************************//**
 * @} (end defgroup IIC_SLAVE)
 ***********************************************************************************************************************/
