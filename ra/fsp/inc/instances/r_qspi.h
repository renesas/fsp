/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @addtogroup QSPI
 * @{
 **********************************************************************************************************************/

#ifndef R_QSPI_H
#define R_QSPI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include <string.h>
#include "r_qspi_cfg.h"
#include "r_spi_flash_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define QSPI_DEVICE_START_ADDRESS    (0x60000000)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Minimum QSPCLK cycles for QSSL to remain high between operations. */
typedef enum e_qspi_qssl_min_high_level
{
    QSPI_QSSL_MIN_HIGH_LEVEL_1_QSPCLK,  ///< QSSL deselected for at least 1 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_2_QSPCLK,  ///< QSSL deselected for at least 2 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_3_QSPCLK,  ///< QSSL deselected for at least 3 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_4_QSPCLK,  ///< QSSL deselected for at least 4 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_5_QSPCLK,  ///< QSSL deselected for at least 5 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_6_QSPCLK,  ///< QSSL deselected for at least 6 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_7_QSPCLK,  ///< QSSL deselected for at least 7 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_8_QSPCLK,  ///< QSSL deselected for at least 8 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_9_QSPCLK,  ///< QSSL deselected for at least 9 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_10_QSPCLK, ///< QSSL deselected for at least 10 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_11_QSPCLK, ///< QSSL deselected for at least 11 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_12_QSPCLK, ///< QSSL deselected for at least 12 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_13_QSPCLK, ///< QSSL deselected for at least 13 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_14_QSPCLK, ///< QSSL deselected for at least 14 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_15_QSPCLK, ///< QSSL deselected for at least 15 QSPCLK
    QSPI_QSSL_MIN_HIGH_LEVEL_16_QSPCLK, ///< QSSL deselected for at least 16 QSPCLK
} qspi_qssl_min_high_level_t;

/* QSPCLK divider. */
typedef enum e_qspi_qspclk_div
{
    QSPI_QSPCLK_DIV_2  = 0x0,          ///< QSPCLK = PCLK / 2
    QSPI_QSPCLK_DIV_3  = 0x1,          ///< QSPCLK = PCLK / 3
    QSPI_QSPCLK_DIV_4  = 0x2,          ///< QSPCLK = PCLK / 4
    QSPI_QSPCLK_DIV_5  = 0x3,          ///< QSPCLK = PCLK / 5
    QSPI_QSPCLK_DIV_6  = 0x4,          ///< QSPCLK = PCLK / 6
    QSPI_QSPCLK_DIV_7  = 0x5,          ///< QSPCLK = PCLK / 7
    QSPI_QSPCLK_DIV_8  = 0x6,          ///< QSPCLK = PCLK / 8
    QSPI_QSPCLK_DIV_9  = 0x7,          ///< QSPCLK = PCLK / 9
    QSPI_QSPCLK_DIV_10 = 0x8,          ///< QSPCLK = PCLK / 10
    QSPI_QSPCLK_DIV_11 = 0x9,          ///< QSPCLK = PCLK / 11
    QSPI_QSPCLK_DIV_12 = 0xA,          ///< QSPCLK = PCLK / 12
    QSPI_QSPCLK_DIV_13 = 0xB,          ///< QSPCLK = PCLK / 13
    QSPI_QSPCLK_DIV_14 = 0xC,          ///< QSPCLK = PCLK / 14
    QSPI_QSPCLK_DIV_15 = 0xD,          ///< QSPCLK = PCLK / 15
    QSPI_QSPCLK_DIV_16 = 0xE,          ///< QSPCLK = PCLK / 16
    QSPI_QSPCLK_DIV_17 = 0xF,          ///< QSPCLK = PCLK / 17
    QSPI_QSPCLK_DIV_18 = 0x10,         ///< QSPCLK = PCLK / 18
    QSPI_QSPCLK_DIV_20 = 0x11,         ///< QSPCLK = PCLK / 20
    QSPI_QSPCLK_DIV_22 = 0x12,         ///< QSPCLK = PCLK / 22
    QSPI_QSPCLK_DIV_24 = 0x13,         ///< QSPCLK = PCLK / 24
    QSPI_QSPCLK_DIV_26 = 0x14,         ///< QSPCLK = PCLK / 26
    QSPI_QSPCLK_DIV_28 = 0x15,         ///< QSPCLK = PCLK / 28
    QSPI_QSPCLK_DIV_30 = 0x16,         ///< QSPCLK = PCLK / 30
    QSPI_QSPCLK_DIV_32 = 0x17,         ///< QSPCLK = PCLK / 32
    QSPI_QSPCLK_DIV_34 = 0x18,         ///< QSPCLK = PCLK / 34
    QSPI_QSPCLK_DIV_36 = 0x19,         ///< QSPCLK = PCLK / 36
    QSPI_QSPCLK_DIV_38 = 0x1A,         ///< QSPCLK = PCLK / 38
    QSPI_QSPCLK_DIV_40 = 0x1B,         ///< QSPCLK = PCLK / 40
    QSPI_QSPCLK_DIV_42 = 0x1C,         ///< QSPCLK = PCLK / 42
    QSPI_QSPCLK_DIV_44 = 0x1D,         ///< QSPCLK = PCLK / 44
    QSPI_QSPCLK_DIV_46 = 0x1E,         ///< QSPCLK = PCLK / 46
    QSPI_QSPCLK_DIV_48 = 0x1F,         ///< QSPCLK = PCLK / 48
} qspi_qspclk_div_t;

/* Extended configuration. */
typedef struct st_qspi_extended_cfg
{
    qspi_qssl_min_high_level_t min_qssl_deselect_cycles; ///< Minimum QSSL deselect time
    qspi_qspclk_div_t          qspclk_div;               ///< QSPCLK divider
} qspi_extended_cfg_t;

/** Instance control block. DO NOT INITIALIZE.  Initialization occurs when @ref spi_flash_api_t::open is called */
typedef struct st_qspi_instance_ctrl
{
    spi_flash_cfg_t const * p_cfg;            // Pointer to initial configuration
    spi_flash_data_lines_t  data_lines;       // Data lines
    uint32_t                total_size_bytes; // Total size of the flash in bytes
    uint32_t                open;             // Whether or not driver is open
} qspi_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const spi_flash_api_t g_qspi_on_spi_flash;

/** @endcond */

fsp_err_t R_QSPI_Open(spi_flash_ctrl_t * p_ctrl, spi_flash_cfg_t const * const p_cfg);
fsp_err_t R_QSPI_Close(spi_flash_ctrl_t * p_ctrl);
fsp_err_t R_QSPI_DirectWrite(spi_flash_ctrl_t    * p_ctrl,
                             uint8_t const * const p_src,
                             uint32_t const        bytes,
                             bool const            read_after_write);
fsp_err_t R_QSPI_DirectRead(spi_flash_ctrl_t * p_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t R_QSPI_SpiProtocolSet(spi_flash_ctrl_t * p_ctrl, spi_flash_protocol_t spi_protocol);
fsp_err_t R_QSPI_XipEnter(spi_flash_ctrl_t * p_ctrl);
fsp_err_t R_QSPI_XipExit(spi_flash_ctrl_t * p_ctrl);
fsp_err_t R_QSPI_Write(spi_flash_ctrl_t    * p_ctrl,
                       uint8_t const * const p_src,
                       uint8_t * const       p_dest,
                       uint32_t              byte_count);
fsp_err_t R_QSPI_Erase(spi_flash_ctrl_t * p_ctrl, uint8_t * const p_device_address, uint32_t byte_count);
fsp_err_t R_QSPI_StatusGet(spi_flash_ctrl_t * p_ctrl, spi_flash_status_t * const p_status);
fsp_err_t R_QSPI_BankSet(spi_flash_ctrl_t * p_ctrl, uint32_t bank);
fsp_err_t R_QSPI_DirectTransfer(spi_flash_ctrl_t                  * p_ctrl,
                                spi_flash_direct_transfer_t * const p_transfer,
                                spi_flash_direct_transfer_dir_t     direction);
fsp_err_t R_QSPI_AutoCalibrate(spi_flash_ctrl_t * p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup QSPI)
 **********************************************************************************************************************/
