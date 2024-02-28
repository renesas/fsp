/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
    uint16_t sdr_value;                        ///< Bit rate register settings
    uint16_t clk_divisor_value;                ///< Clock Select settings
    int      actual_bitrate;                   ///< Actual bit rate settings
    sau_i2c_operation_clock_t operation_clock; ///< I2C operating clock select
} sau_i2c_clock_settings_t;

/** I2C control structure. DO NOT INITIALIZE. */
typedef struct st_sau_i2c_instance_ctrl
{
    i2c_master_cfg_t const * p_cfg;       ///< Pointer to the configuration structure
    i2c_master_addr_mode_t   addr_mode;   ///< Indicates how slave fields should be interpreted
    uint32_t                 open;        ///< Flag to determine if the device is open
    R_SAU0_Type            * p_reg;       ///< Base register for this channel
    uint16_t                 i2c_unit;    ///< I2C unit
    uint16_t                 i2c_channel; ///< I2C channel

    IRQn_Type tei_irq;                    ///< Transmit end IRQ number

    /* Current transfer information. */
    uint8_t     * p_buff;                 ///< Holds the data associated with the transfer */
    uint32_t      total;                  ///< Holds the total number of data bytes to transfer */
    uint32_t      remain;                 ///< Tracks the remaining data bytes to transfer */
    uint32_t      loaded;                 ///< Tracks the number of data bytes written to the register */
    volatile bool activation_on_txi;      // Tracks whether the transfer is activated on TXI interrupt */

    uint8_t slave;                        ///< The address of the slave device
    uint8_t delay_time;                   ///< The delay time of the slave device

    uint8_t       addr_low;               ///< Holds the last address byte to issue */
    volatile bool read;                   ///< Holds the direction of the data byte transfer */
    volatile bool restart;                ///< Holds whether or not the restart should be issued when done */
    volatile bool restarted;              ///< Tracks whether or not a restart was issued during the previous transfer */

    volatile bool do_dummy_read;          ///< Tracks whether a dummy read is issued on the first RX */

    /* Pointer to callback and optional working memory */
    void (* p_callback)(i2c_master_callback_args_t *);

    /* Pointer to context to be passed into callback function */
    void const * p_context;
} sau_i2c_instance_ctrl_t;

/** SAU I2C extended configuration */
typedef struct st_sau_i2c_extended_cfg
{
    sau_i2c_clock_settings_t clock_settings; ///< I2C clock settings
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
                                void const * const                 p_context,
                                i2c_master_callback_args_t * const p_callback_memory);
fsp_err_t R_SAU_I2C_StatusGet(i2c_master_ctrl_t * const p_api_ctrl, i2c_master_status_t * p_status);

void R_SAU_I2C_Start(sau_i2c_instance_ctrl_t * const p_ctrl);
void R_SAU_I2C_Stop(sau_i2c_instance_ctrl_t * const p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup SAU_I2C)
 **********************************************************************************************************************/
