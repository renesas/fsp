/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @ingroup RENESAS_INTERFACES
 * @defgroup DAC_API DAC Interface
 * @brief Interface for D/A converters.
 *
 * @section DAC_API_SUMMARY Summary
 * The DAC interface provides standard Digital/Analog Converter functionality.  A DAC application writes digital
 * sample data to the device and generates analog output on the DAC output pin.
 *
 * Implemented by:
 * @ref DAC
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
#define DAC_API_VERSION_MAJOR    (1U)
#define DAC_API_VERSION_MINOR    (0U)

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
    uint8_t           channel;                  ///< ID associated with this DAC channel
    bool              ad_da_synchronized;       ///< AD/DA synchronization
    dac_data_format_t data_format;              ///< Data format
    bool              output_amplifier_enabled; ///< Output amplifier enable
    void const      * p_extend;
} dac_cfg_t;

/** DAC control block.  Allocate an instance specific control block to pass into the DAC API calls.
 * @par Implemented as
 * - dac_instance_ctrl_t
 */
typedef void dac_ctrl_t;

/** DAC driver structure.  General DAC functions implemented at the HAL layer follow this API. */
typedef struct st_dac_api
{
    /** Initial configuration.
     * @par Implemented as
     * - R_DAC_Open()
     * - R_DAC8_Open()
     *
     * @param[in]   p_ctrl     Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg      Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(dac_ctrl_t * p_ctrl, dac_cfg_t const * const p_cfg);

    /** Close the D/A Converter.
     * @par Implemented as
     * - R_DAC_Close()
     * - R_DAC8_Close()
     *
     * @param[in]   p_ctrl     Control block set in dac_api_t::open call for this timer.
     */
    fsp_err_t (* close)(dac_ctrl_t * p_ctrl);

    /** Write sample value to the D/A Converter.
     * @par Implemented as
     * - R_DAC_Write()
     * - R_DAC8_Write()
     *
     * @param[in]   p_ctrl     Control block set in dac_api_t::open call for this timer.
     * @param[in]   value      Sample value to be written to the D/A Converter.
     */
    fsp_err_t (* write)(dac_ctrl_t * p_ctrl, uint16_t value);

    /** Start the D/A Converter if it has not been started yet.
     * @par Implemented as
     * - R_DAC_Start()
     * - R_DAC8_Start()
     *
     * @param[in]   p_ctrl     Control block set in dac_api_t::open call for this timer.
     */
    fsp_err_t (* start)(dac_ctrl_t * p_ctrl);

    /** Stop the D/A Converter if the converter is running.
     * @par Implemented as
     * - R_DAC_Stop()
     * - R_DAC8_Stop()
     *
     * @param[in]   p_ctrl     Control block set in dac_api_t::open call for this timer.
     */
    fsp_err_t (* stop)(dac_ctrl_t * p_ctrl);

    /** Get version and store it in provided pointer p_version.
     * @par Implemented as
     * - R_DAC_VersionGet()
     * - R_DAC8_VersionGet()
     *
     * @param[out]  p_version  Code and API version used.
     */
    fsp_err_t (* versionGet)(fsp_version_t * p_version);

    /** Get information about DAC Resolution and store it in provided pointer p_info.
     * @par Implemented as
     * - R_DAC_InfoGet()
     * - R_DAC8_InfoGet()
     *
     * @param[out]  p_info  Collection of information for this DAC.
     */
    fsp_err_t (* infoGet)(dac_info_t * const p_info);
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
