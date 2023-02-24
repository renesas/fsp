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
 * @addtogroup OSPI
 * @{
 **********************************************************************************************************************/

#ifndef R_OSPI_H
#define R_OSPI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_ospi_cfg.h"
#include "r_spi_flash_api.h"

#if OSPI_CFG_DMAC_SUPPORT_ENABLE
 #include "r_transfer_api.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* OSPI Memory device chip select */
typedef enum e_ospi_device_number
{
    OSPI_DEVICE_NUMBER_0,              ///< Device connected to Chip-Select 0
    OSPI_DEVICE_NUMBER_1,              ///< Device connected to Chip-Select 1
} ospi_device_number_t;

/* OSPI Memory device type select */
typedef enum e_ospi_device_type
{
    OSPI_DEVICE_FLASH = 0,             ///< Device Memory type OctaFlash
    OSPI_DEVICE_RAM,                   ///< Device Memory type OctaRAM
} ospi_device_type_t;

/* OSPI command to command interval in single continuous read/write mode
 * Unit: OCTACLK
 */
typedef enum e_ospi_command_interval_clocks
{
    OSPI_COMMAND_INTERVAL_CLOCKS_2,
    OSPI_COMMAND_INTERVAL_CLOCKS_5,
    OSPI_COMMAND_INTERVAL_CLOCKS_7,
    OSPI_COMMAND_INTERVAL_CLOCKS_9,
    OSPI_COMMAND_INTERVAL_CLOCKS_11,
    OSPI_COMMAND_INTERVAL_CLOCKS_13,
    OSPI_COMMAND_INTERVAL_CLOCKS_15,
    OSPI_COMMAND_INTERVAL_CLOCKS_17
} ospi_command_interval_clocks_t;

/* OSPI chip select de-assertion duration after last command in single continuous read/write mode
 * Unit: OCTACLK
 */
typedef enum e_ospi_cs_pullup_clocks
{
    OSPI_COMMAND_CS_PULLUP_CLOCKS_2,   ///< 1.5 clocks DOPI mode; 2 Clocks all other modes; Unsupported for DOPI Read
    OSPI_COMMAND_CS_PULLUP_CLOCKS_3,   ///< 2.5 clocks DOPI mode; 3 Clocks all other modes; Unsupported for DOPI Read
    OSPI_COMMAND_CS_PULLUP_CLOCKS_4,   ///< 3.5 clocks DOPI mode; 4 Clocks all other modes; Unsupported for DOPI Read
    OSPI_COMMAND_CS_PULLUP_CLOCKS_5,   ///< 4.5 clocks DOPI mode; 5 Clocks all other modes; Unsupported for DOPI Read
    OSPI_COMMAND_CS_PULLUP_CLOCKS_6,   ///< 5.5 clocks DOPI mode; 6 Clocks all other modes; Unsupported for DOPI Read
    OSPI_COMMAND_CS_PULLUP_CLOCKS_7,   ///< 6.5 clocks DOPI mode; 7 Clocks all other modes
    OSPI_COMMAND_CS_PULLUP_CLOCKS_8,   ///< 7.5 clocks DOPI mode; 8 Clocks all other modes
    OSPI_COMMAND_CS_PULLUP_CLOCKS_9    ///< 8.5 clocks DOPI mode; 9 Clocks all other modes
} ospi_command_cs_pullup_clocks_t;

/* OSPI chip select assertion duration before first command in single continuous read/write mode
 * Unit: OCTACLK
 */
typedef enum e_ospi_cs_pulldown_clocks
{
    OSPI_COMMAND_CS_PULLDOWN_CLOCKS_3 = 1, ///< 2.5 clocks DOPI mode; 3 Clocks all other modes
    OSPI_COMMAND_CS_PULLDOWN_CLOCKS_4,     ///< 3.5 clocks DOPI mode; 4 Clocks all other modes
    OSPI_COMMAND_CS_PULLDOWN_CLOCKS_5      ///< 4.5 clocks DOPI mode; 5 Clocks all other modes
} ospi_command_cs_pulldown_clocks_t;

/* OSPI DOPI byte order options */
typedef enum e_ospi_dopi_byte_order
{
    OSPI_DOPI_BYTE_ORDER_0123,         ///< DOPI byte order byte 0, byte 1, byte 2, byte 3
    OSPI_DOPI_BYTE_ORDER_1032          ///< DOPI byte order byte 1, byte 0, byte 3, byte 2
} ospi_dopi_byte_order_t;

/* Memory mapped timing */
typedef struct st_ospi_timing_setting
{
    ospi_command_interval_clocks_t    command_to_command_interval; ///< Interval between 2 consecutive commands
    ospi_command_cs_pullup_clocks_t   cs_pullup_lag;               ///< Duration to de-assert CS line after the last command
    ospi_command_cs_pulldown_clocks_t cs_pulldown_lead;            ///< Duration to assert CS line before the first command
} ospi_timing_setting_t;

/* This command set is used only with OPI mode set under ospi_extended_cfg_t. spi_flash_cfg_t holds commands for SPI mode. */
typedef struct st_ospi_opi_command_set
{
    uint16_t dual_read_command;        ///< Dual data Read command, valid only in DOPI mode
    uint16_t page_program_command;     ///< Page program command
    uint16_t write_enable_command;     ///< Command to enable write or erase, typically 0x06
    uint16_t status_command;           ///< Command to read the write status
    uint16_t read_command;             ///< Read command
    uint8_t  command_bytes;            ///< Command Bytes
} ospi_opi_command_set_t;

/* Extended configuration. */
typedef struct st_ospi_extended_cfg
{
    ospi_device_number_t           channel;                                 ///< Device number to be used for memory device
    uint32_t                       memory_size;                             ///< Size of memory device
    ospi_device_type_t             memory_type;                             ///< Type of memory device
    uint8_t                        data_latch_delay_clocks;                 ///< Specify delay between OM_DQS and OM_DQS Strobe. Set to 0 to auto-callibrate. Typical value is 0x80.
    uint8_t                        om_dqs_enable_counter_dopi;              ///< OM_DQS enable counter; Setting for DOPI mode (OctaRAM or OctaFlash based on memory_type).
    uint8_t                        om_dqs_enable_counter_sopi;              ///< OM_DQS enable counter; Setting for SOPI mode (OctaFlash Only).
    uint8_t                        single_continuous_mode_read_idle_time;   ///< Mode idle time duration in PCLKA
    uint8_t                        single_continuous_mode_write_idle_time;  ///< Mode idle time duration in PCLKA
    ospi_timing_setting_t const  * p_mem_mapped_read_timing_settings;       ///< Memory mapped read mode settings
    ospi_timing_setting_t const  * p_mem_mapped_write_timing_settings;      ///< Memory mapped write mode settings
    ospi_timing_setting_t const  * p_timing_settings;                       ///< Memory mapped write mode settings
    ospi_opi_command_set_t const * p_opi_commands;                          ///< If OPI commands are not used set this to NULL
    uint8_t                        opi_mem_read_dummy_cycles;               ///< Dummy cycles to be inserted for memory mapped reads
    uint8_t                        opi_mem_write_dummy_cycles;              ///< Dummy cycles to be inserted for memory mapped writes
    uint8_t                      * p_autocalibration_preamble_pattern_addr; ///< OctaFlash memory address holding the preamble pattern
    ospi_dopi_byte_order_t         dopi_byte_order;                         ///< Byte order on external bus. Only applicable in DOPI mode.
    uint16_t                       ram_chip_select_max_period_setting;      ///< Indicates the maximum period that OM_CS0/OM_CS1 are Low in single continuous write/read of OctaRAM.
#if OSPI_CFG_DMAC_SUPPORT_ENABLE
    transfer_instance_t const * p_lower_lvl_transfer;                       ///< DMA Transfer instance used for data transmission
#endif
} ospi_extended_cfg_t;

/** Instance control block. DO NOT INITIALIZE.  Initialization occurs when @ref spi_flash_api_t::open is called */
typedef struct st_ospi_instance_ctrl
{
    spi_flash_cfg_t const * p_cfg;        // Pointer to initial configuration
    ospi_device_number_t    channel;      // Device number to be used for memory device
    spi_flash_protocol_t    spi_protocol; // Current SPI protocol selected
    uint32_t                open;         // Whether or not driver is open
} ospi_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const spi_flash_api_t g_ospi_on_spi_flash;

/** @endcond */

fsp_err_t R_OSPI_Open(spi_flash_ctrl_t * p_ctrl, spi_flash_cfg_t const * const p_cfg);
fsp_err_t R_OSPI_Close(spi_flash_ctrl_t * p_ctrl);
fsp_err_t R_OSPI_DirectWrite(spi_flash_ctrl_t    * p_ctrl,
                             uint8_t const * const p_src,
                             uint32_t const        bytes,
                             bool const            read_after_write);
fsp_err_t R_OSPI_DirectRead(spi_flash_ctrl_t * p_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t R_OSPI_DirectTransfer(spi_flash_ctrl_t                  * p_ctrl,
                                spi_flash_direct_transfer_t * const p_transfer,
                                spi_flash_direct_transfer_dir_t     direction);
fsp_err_t R_OSPI_SpiProtocolSet(spi_flash_ctrl_t * p_ctrl, spi_flash_protocol_t spi_protocol);
fsp_err_t R_OSPI_XipEnter(spi_flash_ctrl_t * p_ctrl);
fsp_err_t R_OSPI_XipExit(spi_flash_ctrl_t * p_ctrl);
fsp_err_t R_OSPI_Write(spi_flash_ctrl_t    * p_ctrl,
                       uint8_t const * const p_src,
                       uint8_t * const       p_dest,
                       uint32_t              byte_count);
fsp_err_t R_OSPI_Erase(spi_flash_ctrl_t * p_ctrl, uint8_t * const p_device_address, uint32_t byte_count);
fsp_err_t R_OSPI_StatusGet(spi_flash_ctrl_t * p_ctrl, spi_flash_status_t * const p_status);
fsp_err_t R_OSPI_BankSet(spi_flash_ctrl_t * p_ctrl, uint32_t bank);
fsp_err_t R_OSPI_AutoCalibrate(spi_flash_ctrl_t * p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup OSPI)
 **********************************************************************************************************************/
