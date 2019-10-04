/***********************************************************************************************************************
 * Copyright [2015] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 *
 * This file is part of Renesas RA Flex Software Package (FSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas FSP license agreement. Unless otherwise agreed in an FSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * File Name    : board_qspi.h
 * Description  : Configures QSPI bus and device access.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup BSP_BOARD_EK_RA6M3G
 * @defgroup BSP_EK_RA6M3G_QSPI Board QSPI
 * @brief QSPI configuration setup for this board.
 *
 * This is code specific to the EK-RA6M3G board.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BSP_QSPI_H_
#define BSP_QSPI_H_

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/* This QSPI header file requires this be included here. */
#include <stdint.h>
#include <stdbool.h>

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_QSPI_VAL_SFMSDE                  (1u)
#define BSP_QSPI_VAL_SFMSPI                  (2u)

#define BSP_QSPI_VAL_SFMDTY                  (0u)
#define BSP_QSPI_VAL_SFMDV                   (0u)

#define BSP_QSPI_VAL_SFMXD                   (0xFF)
#define BSP_QSPI_VAL_SFMXEN                  (0u)
#define BSP_QSPI_VAL_SFMXST                  (0u)
#define BSP_QSPI_VAL_SFMDN                   (0u)

#define BSP_QSPI_VAL_SFMSLD                  (1u)
#define BSP_QSPI_VAL_SFMSHD                  (0u)
#define BSP_QSPI_VAL_SFMSW                   (0u)

#define BSP_QSPI_VAL_SFMPFE                  (1u)
#define BSP_QSPI_VAL_SFMRM                   (5u)

/* ID and type information for the MX25L25645G Macronix Serial NOR Flash Memory */
#define BSP_PRV_MX25_QSPI_MANUFACTURER_ID    (0xC2u)
#define BSP_PRV_MX25_QSPI_MEMORY_TYPE        (0x20u)
#define BSP_PRV_MX25_QSPI_MEMORY_CAPACITY    (0x19u)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Reference cycle selects. Resultant QSPI clock is PCLKA divided down by the following: (Micron N25Q256A quad SPI flash device) */
typedef enum e_qspi_clk
{
    /** Reset Operations */
    QSPI_CLK_DIV2,                     ///< ie. QSPI CLK runs at 60.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV3,                     ///< ie. QSPI CLK runs at 40.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV4,                     ///< ie. QSPI CLK runs at  30.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV5,                     ///< ie. QSPI CLK runs at  24.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV6,                     ///< ie. QSPI CLK runs at  20.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV7,                     ///< ie. QSPI CLK runs at  17.14 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV8,                     ///< ie. QSPI CLK runs at  15.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV9,                     ///< ie. QSPI CLK runs at  13.33 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV10,                    ///< ie. QSPI CLK runs at  12.00 MHz when PCLKA is set to 120MHz
} qspi_clk;

/** Available QSPI read modes for  Micron N25Q256A/Macronix MX25L12835F quad SPI flash device */
typedef enum e_qspi_readmode
{
    /** Reset Operations */
    QSPI_READMODE_STANDARD,            ///< Standard
    QSPI_READMODE_FAST,                ///< Fast read
    QSPI_READMODE_FAST_DUAL_OUTPUT,    ///< Fast Read Dual Output
    QSPI_READMODE_FAST_DUAL_IO,        ///< Fast Read Dual I/O
    QSPI_READMODE_FAST_QUAD_OUTPUT,    ///< Fast Read Quad Output
    QSPI_READMODE_FAST_QUAD_IO,        ///< Fast Read Quad I/O
} qspi_readmode;

typedef enum qspi_protocol
{
    QSPI_EXTENDED_SPI_PROTOCOL = 0,
    QSPI_DUAL_SPI_PROTOCOL     = 1,
    QSPI_QUAD_SPI_PROTOCOL     = 2,
} qspi_protocol;

typedef enum dummy_cycles_4_fast_read
{
    DEFAULT = 0,
    QSPCLK_CYCLES_3,
    QSPCLK_CYCLES_4,
    QSPCLK_CYCLES_5,
    QSPCLK_CYCLES_6,
    QSPCLK_CYCLES_7,
    QSPCLK_CYCLES_8,
    QSPCLK_CYCLES_9,
    QSPCLK_CYCLES_10,
    QSPCLK_CYCLES_11,
    QSPCLK_CYCLES_12,
    QSPCLK_CYCLES_13,
    QSPCLK_CYCLES_14,
    QSPCLK_CYCLES_15,
    QSPCLK_CYCLES_16,
    QSPCLK_CYCLES_17,
} dummy_cycles;

typedef enum min_high_lvl_qssl_width_slt
{
    QSPCLK_1 = 0,
    QSPCLK_2,
    QSPCLK_3,
    QSPCLK_4,
    QSPCLK_5,
    QSPCLK_6,
    QSPCLK_7,
    QSPCLK_8,
    QSPCLK_9,
    QSPCLK_10,
    QSPCLK_11,
    QSPCLK_12,
    QSPCLK_13,
    QSPCLK_14,
    QSPCLK_15,
    QSPCLK_16,
} qssl_width_slt;

/** Available QSPI commands for the Micron N25Q256A /Macronix MX25L12835F quad SPI flash device */
typedef enum e_qspi_command
{
    /** Reset Operations */
    QSPI_COMMAND_RESET_ENABLE = 0x66,              ///< Enable reset
    QSPI_COMMAND_RESET_MEMORY = 0x99,              ///< Reset memory

    /** Read Operations */
    QSPI_COMMAND_READ       = 0x03,                ///< Read memory
    QSPI_COMMAND_4BYTE_READ = 0x13,                ///< Read memory using a 4 byte address

    /** Write Operations */
    QSPI_COMMAND_WRITE_ENABLE       = 0x06,        ///< Write Enable
    QSPI_COMMAND_WRITE_DISABLE      = 0x04,        ///< Write Disable
    QSPI_COMMAND_PAGE_PROGRAM       = 0x02,        ///< Program a page
    QSPI_COMMAND_4BYTE_PAGE_PROGRAM = 0x12,        ///< Program a page using a 4 byte address

    /** Register Operations */
    QSPI_COMMAND_READ_STATUS_REGISTER      = 0x05, ///< Read Status register
    QSPI_COMMAND_READ_FLAG_STATUS_REGISTER = 0x70, ///< Read Status register
    QSPI_COMMAND_READ_ID                   = 0x9F, ///< Read the chip ID
    QSPI_COMMAND_QUAD_READ_ID              = 0xAF, ///< Read the chip ID
    QSPI_COMMAND_READ_NONVOLATILE_CFGREG   = 0xB5, ///< Read the non-volatile configuration register
    QSPI_COMMAND_READ_ENH_VOLATILE_CFGREG  = 0x65, ///< Read the Ehn volatile cfg register
    QSPI_COMMAND_WRITE_NONVOLATILE_CFGREG  = 0xB1, ///< Write the non-volatile configuration register
    QSPI_COMMAND_READ_VOLATILE_CFGREG      = 0x85, ///< Read the volatile configuration register
    QSPI_COMMAND_WRITE_VOLATILE_CFGREG     = 0x81, ///< Write the volatile configuration register
    QSPI_COMMAND_WRITE_ENH_VOLATILE_CFGREG = 0x61, ///< Write the Ehn volatile cfg register
    QSPI_COMMAND_ENABLE_QPI                = 0x35, ///< Enable QPI
    QSPI_COMMAND_EXIT_QPI                  = 0xF5, ///< Reset (Exit) QPI

    /** Erase Operations */
    QSPI_COMMAND_SECTOR_ERASE          = 0xD8,     ///< Erase a sector
    QSPI_COMMAND_4BYTE_SECTOR_ERASE    = 0xDC,     ///< Erase a sector using a 4 byte address
    QSPI_COMMAND_SUBSECTOR_ERASE       = 0x20,     ///< Erase a subsector
    QSPI_COMMAND_4BYTE_SUBSECTOR_ERASE = 0x21,     ///< Erase a subsector using a 4 byte address
    QSPI_COMMAND_CHIP_ERASE            = 0xC7,     ///< Erase the entire chip
} qspi_command;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
void bsp_qspi_init(void);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif                                 /* BSP_QSPI_H_ */
/** @} (end defgroup BSP_EK_RA6M3G_QSPI) */
