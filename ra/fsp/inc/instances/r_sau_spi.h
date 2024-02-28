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

#ifndef R_SAU_SPI_H
#define R_SAU_SPI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_spi_api.h"
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*****************************************************************************************************************//**
 * @ingroup SAU_SPI
 * @{
 ********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define SAU_SPI_TRANSFER_MODE_RECEPTION                 (1U) ///< Reception only
#define SAU_SPI_TRANSFER_MODE_TRANSMISSION              (2U) ///< Transmission only
#define SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION    (3U) ///< Transmission/reception

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Selection of operating clock (fMCK) of channel */
typedef enum e_sau_spi_operation_clock
{
    SAU_SPI_OPERATION_CLOCK_CK0 = 0,   ///< Operation clock CK0 set by SPS register
    SAU_SPI_OPERATION_CLOCK_CK1 = 1,   ///< Operation clock CK1 set by SPS register
} sau_spi_operation_clock_t;

/** Selection of transfer mode of channel */
typedef enum e_sau_spi_transfer_mode
{
    SAU_SPI_TRANSFER_MODE_SINGLE     = 0, ///< Single transfer mode
    SAU_SPI_TRANSFER_MODE_CONTINUOUS = 1, ///< Continuous transfer mode
} sau_spi_transfer_mode_t;

/** Data phase */
typedef enum e_sau_spi_data_phase
{
    SAU_SPI_DATA_PHASE_START            = 0, ///< Data output starts from the start of the operation of the serial clock
    SAU_SPI_DATA_PHASE_HALF_CYCLE_START = 1, ///< Data output starts half a clock cycle before the start of the serial clock operation
} sau_spi_data_phase_t;

/** Clock phase */
typedef enum e_sau_spi_clock_phase
{
    SAU_SPI_CLOCK_PHASE_NON_REVERSE = 0, ///< Non-reverse
    SAU_SPI_CLOCK_PHASE_REVERSE     = 1, ///< Reverse
} sau_spi_clock_phase_t;

/** Settings for adjusting the SPI CLK */
typedef struct st_sau_spi_div_setting
{
    uint8_t prs;
    uint8_t stclk;
} sau_spi_div_setting_t;

/** SAU SPI extended configuration */
typedef struct st_sau_spi_extended_cfg
{
    sau_spi_div_setting_t     clk_div;
    sau_spi_operation_clock_t operation_clock;
    sau_spi_transfer_mode_t   transfer_mode;
    sau_spi_data_phase_t      data_phase;
    sau_spi_clock_phase_t     clock_phase;
    uint8_t sau_unit;
} sau_spi_extended_cfg_t;

/** SPI instance control block. DO NOT INITIALIZE. */
typedef struct st_sau_spi_instance_ctrl
{
    uint32_t          open;
    spi_cfg_t const * p_cfg;
    R_SAU0_Type     * p_reg;
    uint8_t         * p_src;
    uint8_t         * p_dest;
    uint32_t          tx_count;
    uint32_t          rx_count;
    uint32_t          count;
    bool              transfer_in_progress;

    /* Pointer to callback and optional working memory. */
    void (* p_callback)(spi_callback_args_t *);

    /* Pointer to context to be passed into callback function. */
    void const * p_context;
} sau_spi_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const spi_api_t g_spi_on_sau;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_SAU_SPI_Open(spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg);
fsp_err_t R_SAU_SPI_Read(spi_ctrl_t * const    p_api_ctrl,
                         void                * p_dest,
                         uint32_t const        length,
                         spi_bit_width_t const bit_width);
fsp_err_t R_SAU_SPI_Write(spi_ctrl_t * const    p_api_ctrl,
                          void const          * p_src,
                          uint32_t const        length,
                          spi_bit_width_t const bit_width);
fsp_err_t R_SAU_SPI_WriteRead(spi_ctrl_t * const    p_api_ctrl,
                              void const          * p_src,
                              void                * p_dest,
                              uint32_t const        length,
                              spi_bit_width_t const bit_width);
fsp_err_t R_SAU_SPI_Close(spi_ctrl_t * const p_api_ctrl);
fsp_err_t R_SAU_SPI_CalculateBitrate(uint32_t                bitrate,
                                     sau_spi_div_setting_t * sclk_div,
                                     uint8_t                 sau_unit,
                                     uint8_t                 channel);
fsp_err_t R_SAU_SPI_CallbackSet(spi_ctrl_t * const          p_api_ctrl,
                                void (                    * p_callback)(spi_callback_args_t *),
                                void const * const          p_context,
                                spi_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end ingroup SAU_SPI)
 **********************************************************************************************************************/
