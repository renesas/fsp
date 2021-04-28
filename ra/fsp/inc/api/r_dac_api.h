/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @ingroup RENESAS_INTERFACES
 * @defgroup DAC_API DAC Interface
 * @brief Interface for D/A converters.
 *
 * @section DAC_API_SUMMARY Summary
 * The DAC interface provides standard Digital/Analog Converter functionality.  A DAC application writes digital
 * sample data to the device and generates analog output on the DAC output pin.
 *
 * Implemented by:
 * - @ref DAC
 * - @ref DAC8
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_DAC_API_H
#define R_DAC_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Common error codes and definitions. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DAC Open API data format settings. */
typedef enum e_dac_data_format
{
    DAC_DATA_FORMAT_FLUSH_RIGHT = 0,   ///< LSB of data is flush to the right leaving the top 4 bits unused.
    DAC_DATA_FORMAT_FLUSH_LEFT  = 1    ///< MSB of data is flush to the left leaving the bottom 4 bits unused.
} dac_data_format_t;

/** DAC information structure to store various information for a DAC */
typedef struct dac_info
{
    uint8_t bit_width;                 ///< Resolution of the DAC.
} dac_info_t;

/** DAC Open API configuration parameter */
typedef struct st_dac_cfg
{
    uint8_t      channel;              ///< ID associated with this DAC channel
    bool         ad_da_synchronized;   ///< AD/DA synchronization
    void const * p_extend;
} dac_cfg_t;

/** DAC control block.  Allocate an instance specific control block to pass into the DAC API calls.
 * @par Implemented as
 * - dac_instance_ctrl_t
 * - dac8_instance_ctrl_t
 */
typedef void dac_ctrl_t;

/** DAC driver structure.  General DAC functions implemented at the HAL layer follow this API. */
typedef struct st_dac_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_DAC_Open()
     * - @ref R_DAC8_Open()
     *
     * @param[in]   p_ctrl     Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg      Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(dac_ctrl_t * const p_ctrl, dac_cfg_t const * const p_cfg);

    /** Close the D/A Converter.
     * @par Implemented as
     * - @ref R_DAC_Close()
     * - @ref R_DAC8_Close()
     *
     * @param[in]   p_ctrl     Control block set in @ref dac_api_t::open call for this timer.
     */
    fsp_err_t (* close)(dac_ctrl_t * const p_ctrl);

    /** Write sample value to the D/A Converter.
     * @par Implemented as
     * - @ref R_DAC_Write()
     * - @ref R_DAC8_Write()
     *
     * @param[in]   p_ctrl     Control block set in @ref dac_api_t::open call for this timer.
     * @param[in]   value      Sample value to be written to the D/A Converter.
     */
    fsp_err_t (* write)(dac_ctrl_t * const p_ctrl, uint16_t value);

    /** Start the D/A Converter if it has not been started yet.
     * @par Implemented as
     * - @ref R_DAC_Start()
     * - @ref R_DAC8_Start()
     *
     * @param[in]   p_ctrl     Control block set in @ref dac_api_t::open call for this timer.
     */
    fsp_err_t (* start)(dac_ctrl_t * const p_ctrl);

    /** Stop the D/A Converter if the converter is running.
     * @par Implemented as
     * - @ref R_DAC_Stop()
     * - @ref R_DAC8_Stop()
     *
     * @param[in]   p_ctrl     Control block set in @ref dac_api_t::open call for this timer.
     */
    fsp_err_t (* stop)(dac_ctrl_t * const p_ctrl);
} dac_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_dac_instance
{
    dac_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    dac_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    dac_api_t const * p_api;           ///< Pointer to the API structure for this instance
} dac_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup DAC_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
