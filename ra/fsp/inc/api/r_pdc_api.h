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
 * @ingroup RENESAS_INTERFACES
 * @defgroup PDC_API PDC Interface
 * @brief Interface for PDC functions.
 *
 * @section PDC_API_SUMMARY Summary
 *
 * DEPRECATED - PDC API will be replaced with CAPTURE API in the next major release
 *
 * The PDC interface provides the functionality for capturing an image from an image sensor/camera.
 * When a capture is complete a transfer complete interrupt is triggered.
 *
 * Implemented by:
 * - @ref PDC
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_PDC_API_H
#define R_PDC_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Clock divider applied to PDC clock to provide PCKO output frequency  */
typedef enum e_pdc_clock_division
{
    PDC_CLOCK_DIVISION_2  = 0U,        ///< CLK / 2
    PDC_CLOCK_DIVISION_4  = 1U,        ///< CLK / 4
    PDC_CLOCK_DIVISION_6  = 2U,        ///< CLK / 6
    PDC_CLOCK_DIVISION_8  = 3U,        ///< CLK / 8
    PDC_CLOCK_DIVISION_10 = 4U,        ///< CLK / 10
    PDC_CLOCK_DIVISION_12 = 5U,        ///< CLK / 12
    PDC_CLOCK_DIVISION_14 = 6U,        ///< CLK / 14
    PDC_CLOCK_DIVISION_16 = 7U,        ///< CLK / 16
} pdc_clock_division_t;

/** Endian of captured data  */
typedef enum e_pdc_endian
{
    PDC_ENDIAN_LITTLE = 0U,            ///< Data is in little endian format
    PDC_ENDIAN_BIG    = 1U,            ///< Data is in big endian format
} pdc_endian_t;

/** Polarity of input HSYNC signal  */
typedef enum e_pdc_hsync_polarity
{
    PDC_HSYNC_POLARITY_HIGH = 0U,      ///< HSYNC signal is active high
    PDC_HSYNC_POLARITY_LOW  = 1U,      ///< HSYNC signal is active low
} pdc_hsync_polarity_t;

/** Polarity of input VSYNC signal  */
typedef enum e_pdc_vsync_polarity
{
    PDC_VSYNC_POLARITY_HIGH = 0U,      ///< VSYNC signal is active high
    PDC_VSYNC_POLARITY_LOW  = 1U,      ///< VSYNC signal is active low
} pdc_vsync_polarity_t;

/** PDC events */
typedef enum e_pdc_event
{
    PDC_EVENT_TRANSFER_COMPLETE = 0U,    ///< Complete frame transferred by DMAC/DTC
    PDC_EVENT_RX_DATA_READY     = 0x01U, ///< Receive data ready interrupt
    PDC_EVENT_FRAME_END         = 0x04U, ///< Frame end interrupt
    PDC_EVENT_ERR_OVERRUN       = 0x08U, ///< Overrun interrupt
    PDC_EVENT_ERR_UNDERRUN      = 0x10U, ///< Underrun interrupt
    PDC_EVENT_ERR_V_SET         = 0x20U, ///< Vertical line setting error interrupt
    PDC_EVENT_ERR_H_SET         = 0x40U, ///< Horizontal byte number setting error interrupt
} pdc_event_t;

/** Callback function parameter data */
typedef struct st_pdc_callback_args
{
    pdc_event_t  event;                ///< Event causing the callback
    uint8_t    * p_buffer;             ///< Pointer to buffer containing the captured data
    void const * p_context;            ///< Placeholder for user data.  Set in @ref pdc_api_t::open function in @ref pdc_cfg_t.
} pdc_callback_args_t;

/** PDC configuration parameters. */
typedef struct st_pdc_cfg
{
    uint16_t                    x_capture_start_pixel; ///< Horizontal position to start capture
    uint16_t                    x_capture_pixels;      ///< Number of horizontal pixels to capture
    uint16_t                    y_capture_start_pixel; ///< Vertical position to start capture
    uint16_t                    y_capture_pixels;      ///< Number of vertical lines/pixels to capture
    pdc_clock_division_t        clock_division;        ///< Clock divider
    pdc_endian_t                endian;                ///< Endian of capture data
    pdc_hsync_polarity_t        hsync_polarity;        ///< Polarity of HSYNC input
    pdc_vsync_polarity_t        vsync_polarity;        ///< Polarity of VSYNC input
    uint8_t                   * p_buffer;              ///< Pointer to buffer to write image into
    uint8_t                     bytes_per_pixel;       ///< Number of bytes per pixel
    uint8_t                     pdc_ipl;               ///< PDC interrupt priority
    uint8_t                     transfer_req_ipl;      ///< Transfer interrupt priority
    IRQn_Type                   pdc_irq;               ///< PDC IRQ number
    IRQn_Type                   transfer_req_irq;      ///< Transfer request IRQ number
    transfer_instance_t const * p_lower_lvl_transfer;  ///< Pointer to the transfer instance the PDC should use
    void (* p_callback)(pdc_callback_args_t * p_args); ///< Callback provided when a PDC transfer ISR occurs.
    void const * p_context;                            ///< User defined context passed to callback function
    void const * p_extend;                             ///< Placeholder for user data.
} pdc_cfg_t;

/** PDC control block.  Allocate an instance specific control block to pass into the PDC API calls.
 * @par Implemented as
 * - pdc_instance_ctrl_t
 */
typedef void pdc_ctrl_t;

/** PDC functions implemented at the HAL layer will follow this API.
 * DEPRECATED - PDC API will be replaced with CAPTURE API in the next major release */
typedef struct st_pdc_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_PDC_Open()
     *
     * @note To reconfigure after calling this function, call @ref pdc_api_t::close first.
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(pdc_ctrl_t * const p_ctrl, pdc_cfg_t const * const p_cfg);

    /** Closes the driver and allows reconfiguration. May reduce power consumption.
     * @par Implemented as
     * - @ref R_PDC_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(pdc_ctrl_t * const p_ctrl);

    /** Start a capture.
     * @par Implemented as
     * - @ref R_PDC_CaptureStart()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_buffer     Pointer to store captured image data.
     */
    fsp_err_t (* captureStart)(pdc_ctrl_t * const p_ctrl, uint8_t * const p_buffer);
} pdc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_pdc_instance
{
    pdc_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    pdc_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    pdc_api_t const * p_api;           ///< Pointer to the API structure for this instance
} pdc_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup PDC_API)
 **********************************************************************************************************************/
