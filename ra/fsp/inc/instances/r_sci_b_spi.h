/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_SCI_B_SPI_H
#define R_SCI_B_SPI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_spi_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*****************************************************************************************************************//**
 * @ingroup SCI_B_SPI
 * @{
 ********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Settings for adjusting the SPI CLK. */
typedef struct
{
    uint8_t brr;
    uint8_t cks  : 2;
    uint8_t bgdm : 1;
} sci_b_spi_div_setting_t;

/** Source clock selection options for SCI. */
typedef enum e_sci_b_spi_clock_source
{
    SCI_B_SPI_SOURCE_CLOCK_SCISPICLK = 0,
    SCI_B_SPI_SOURCE_CLOCK_PCLK      = 1,
} sci_b_spi_clock_source_t;

/** Adjustment value for receive sampling timing delay for RXDn */
typedef enum e_sci_b_spi_rx_sampling_delay
{
    SCI_B_SPI_RX_SAMPLING_DELAY_CYCLES_0 = 0, ///< Use the default receive sampling timing
    SCI_B_SPI_RX_SAMPLING_DELAY_CYCLES_1 = 1, ///< Delay the receive sampling timing by 1 TCLK cycle
    SCI_B_SPI_RX_SAMPLING_DELAY_CYCLES_2 = 2, ///< Delay the receive sampling timing by 2 TCLK cycles
    SCI_B_SPI_RX_SAMPLING_DELAY_CYCLES_3 = 3, ///< Delay the receive sampling timing by 3 TCLK cycles
    SCI_B_SPI_RX_SAMPLING_DELAY_CYCLES_4 = 4, ///< Delay the receive sampling timing by 4 TCLK cycles
} sci_b_spi_rx_sampling_delay_t;

/** Transmit FIFO trigger configuration. */
typedef enum e_sci_b_spi_tx_fifo_trigger
{
    SCI_B_SPI_TX_FIFO_TRIGGER_DISABLED = 0x0, ///< FIFO mode not used
    SCI_B_SPI_TX_FIFO_TRIGGER_1        = 0x1, ///< TXI is generated after each byte is received without buffering
    SCI_B_SPI_TX_FIFO_TRIGGER_2        = 0x2, ///< TXI is generated when FIFO contains 2 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_3        = 0x3, ///< TXI is generated when FIFO contains 3 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_4        = 0x4, ///< TXI is generated when FIFO contains 4 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_5        = 0x5, ///< TXI is generated when FIFO contains 5 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_6        = 0x6, ///< TXI is generated when FIFO contains 6 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_7        = 0x7, ///< TXI is generated when FIFO contains 7 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_8        = 0x8, ///< TXI is generated when FIFO contains 8 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_9        = 0x9, ///< TXI is generated when FIFO contains 9 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_10       = 0xA, ///< TXI is generated when FIFO contains 10 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_11       = 0xB, ///< TXI is generated when FIFO contains 11 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_12       = 0xC, ///< TXI is generated when FIFO contains 12 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_13       = 0xD, ///< TXI is generated when FIFO contains 13 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_14       = 0xE, ///< TXI is generated when FIFO contains 14 bytes
    SCI_B_SPI_TX_FIFO_TRIGGER_MAX      = 0xF, ///< TXI is generated when FIFO is full or after 15 bit times with no data (fewer interrupts)
} sci_b_spi_tx_fifo_trigger_t;

/** SCI SPI extended configuration */
typedef struct st_sci_b_spi_extended_cfg
{
    sci_b_spi_div_setting_t clk_div;

    /** Clock source to generate SCK can either be selected as PCLK or SCISPICLK. */
    sci_b_spi_clock_source_t clock_source;

    sci_b_spi_rx_sampling_delay_t rx_sampling_delay; ///< Receive sampling timing adjustment

    sci_b_spi_tx_fifo_trigger_t tx_fifo_trigger;     ///< TX Fifo Trigger Level
} sci_b_spi_extended_cfg_t;

/** SPI instance control block. DO NOT INITIALIZE. */
typedef struct st_sci_b_spi_instance_ctrl
{
    uint32_t          open;
    spi_cfg_t const * p_cfg;
    R_SCI_B0_Type   * p_reg;
    uint8_t         * p_src;
    uint8_t         * p_dest;
    uint32_t          tx_count;
    uint32_t          rx_count;
    uint32_t          count;

    /* Pointer to callback and optional working memory */
    void (* p_callback)(spi_callback_args_t *);
    spi_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void * p_context;
} sci_b_spi_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const spi_api_t g_spi_on_sci_b;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_SPI_Open(spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg);
fsp_err_t R_SCI_B_SPI_Read(spi_ctrl_t * const    p_api_ctrl,
                           void                * p_dest,
                           uint32_t const        length,
                           spi_bit_width_t const bit_width);
fsp_err_t R_SCI_B_SPI_Write(spi_ctrl_t * const    p_api_ctrl,
                            void const          * p_src,
                            uint32_t const        length,
                            spi_bit_width_t const bit_width);
fsp_err_t R_SCI_B_SPI_WriteRead(spi_ctrl_t * const    p_api_ctrl,
                                void const          * p_src,
                                void                * p_dest,
                                uint32_t const        length,
                                spi_bit_width_t const bit_width);
fsp_err_t R_SCI_B_SPI_Close(spi_ctrl_t * const p_api_ctrl);
fsp_err_t R_SCI_B_SPI_CalculateBitrate(uint32_t                  bitrate,
                                       sci_b_spi_clock_source_t  clock_source,
                                       sci_b_spi_div_setting_t * sclk_div);
fsp_err_t R_SCI_B_SPI_CallbackSet(spi_ctrl_t * const          p_api_ctrl,
                                  void (                    * p_callback)(spi_callback_args_t *),
                                  void * const                p_context,
                                  spi_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end ingroup SCI_B_SPI)
 **********************************************************************************************************************/
