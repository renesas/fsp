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
 * @addtogroup CEU
 * @{
 **********************************************************************************************************************/

#ifndef R_CEU_H
#define R_CEU_H

#include "bsp_api.h"
#include "r_capture_api.h"
#include "r_ceu.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Capture mode */
typedef enum e_ceu_capture_mode
{
    CEU_CAPTURE_MODE_SINGLE     = 0U,  ///< Single image capture
    CEU_CAPTURE_MODE_CONTINUOUS = 1U,  ///< Continuous image capture
} ceu_capture_mode_t;

/** Data bus width */
typedef enum e_ceu_data_bus_size
{
    CEU_DATA_BUS_SIZE_8_BIT  = 0U,     ///< Data bus is 8-bit
    CEU_DATA_BUS_SIZE_16_BIT = 1U,     ///< Data bus is 16-bit
} ceu_data_bus_size_t;

/** Polarity of input HSYNC signal  */
typedef enum e_ceu_hsync_polarity
{
    CEU_HSYNC_POLARITY_HIGH = 0U,      ///< HSYNC signal is active high
    CEU_HSYNC_POLARITY_LOW  = 1U,      ///< HSYNC signal is active low
} ceu_hsync_polarity_t;

/** Polarity of input VSYNC signal  */
typedef enum e_ceu_vsync_polarity
{
    CEU_VSYNC_POLARITY_HIGH = 0U,      ///< VSYNC signal is active high
    CEU_VSYNC_POLARITY_LOW  = 1U,      ///< VSYNC signal is active low
} ceu_vsync_polarity_t;

typedef enum e_ceu_burst_transfer_mode
{
    CEU_BURST_TRANSFER_MODE_X1 = (0u), ///< Transferred to the bus in 32-byte units */
    CEU_BURST_TRANSFER_MODE_X2 = (1u), ///< Transferred to the bus in 64-byte units */
    CEU_BURST_TRANSFER_MODE_X4 = (2u), ///< Transferred to the bus in 128-byte units */
    CEU_BURST_TRANSFER_MODE_X8 = (3u)  ///< Transferred to the bus in 256-byte units */
} ceu_burst_transfer_mode_t;

typedef enum e_ceu_event
{
    CEU_EVENT_NONE          = 0x00000000, // No event, default state
    CEU_EVENT_FRAME_END     = 0x00000001, ///< Frame end event (CPE)
    CEU_EVENT_HD            = 0x00000100, ///< (Not Used) HD received (HD)
    CEU_EVENT_VD            = 0x00000200, ///< VD received (VD)
    CEU_EVENT_CRAM_OVERFLOW = 0x00010000, ///< Data overflowed in the CRAM buffer (CDTOF)
    CEU_EVENT_HD_MISMATCH   = 0x00020000, ///< HD mismatch (IGHS)
    CEU_EVENT_VD_MISMATCH   = 0x00040000, ///< VD mismatch (IGVS)
    CEU_EVENT_VD_ERROR      = 0x00100000, ///< Invalid VD condition (VBP)
    CEU_EVENT_FIREWALL      = 0x00800000, ///< Data write address exceeds firewall (FWF)
    CEU_EVENT_HD_MISSING    = 0x01000000, ///< HD was expected but not input (NHD)
    CEU_EVENT_VD_MISSING    = 0x02000000, ///< VD was expected but not input (NVD)
} ceu_event_t;

/** Capture mode for CEU. */
typedef enum e_ceu_capture_format
{
    CEU_CAPTURE_FORMAT_DATA_SYNCHRONOUS = 0x1, ///< Raw formatted data.
    CEU_CAPTURE_FORMAT_DATA_ENABLE      = 0x2  ///< JPG formatted data
} ceu_capture_format_t;

/** Swap bits configuration */
typedef struct st_ceu_byte_swapping_t
{
    uint8_t swap_8bit_units  : 1;      ///< Byte swapping in 8-bit units
    uint8_t swap_16bit_units : 1;      ///< Byte swapping in 16-bit units
    uint8_t swap_32bit_units : 1;      ///< Byte swapping in 32-bit units
} ceu_byte_swapping_t;

/** Edge information for latching signals */
typedef struct st_ceu_edge_info_t
{
    uint8_t dsel  : 1;                 ///< Sets the edge for fetching the image data (D15 to D0) from an external module.
    uint8_t hdsel : 1;                 ///< Sets the edge for capturing hd from external module.
    uint8_t vdsel : 1;                 ///< Sets the edge for capturing vd from external module.
} ceu_edge_info_t;

/** Extended configuration structure for CEU. */
typedef struct st_ceu_extended_cfg
{
    ceu_capture_format_t      capture_format;     ///< Capture format for incoming data
    ceu_data_bus_size_t       data_bus_width;     ///< Size of camera data bus
    ceu_edge_info_t           edge_info;
    ceu_hsync_polarity_t      hsync_polarity;     ///< Polarity of HSYNC input
    ceu_vsync_polarity_t      vsync_polarity;     ///< Polarity of VSYNC input
    uint32_t                  image_area_size;    ///< Image capture size. Used when setting firewall address for Data Enable Fetch mode.
    ceu_byte_swapping_t       byte_swapping;      ///< Controls byte swapping in 8-bit, 16-bit and 32-bit units
    ceu_burst_transfer_mode_t burst_mode;         ///< Bus transfer data size
    uint32_t                  interrupts_enabled; ///< Enabled interrupt events bit mask
    uint8_t   ceu_ipl;                            ///< PDC interrupt priority
    IRQn_Type ceu_irq;                            ///< PDC IRQ number
} ceu_extended_cfg_t;

/** CEU instance control block. DO NOT INITIALIZE. */
typedef struct st_ceu_instance_ctrl
{
    capture_cfg_t const * p_cfg;                    // Pointer to the configuration structure
    uint32_t              open;                     // Indicates whether or not the driver is open called.
    uint8_t             * p_buffer;                 // Pointer to buffer currently in use
    uint32_t              image_area_size;          // Size of capture area for image (Used for Data Enable Fetch)
    uint32_t              interrupts_enabled;       // Interrupts enabled bitmask
    void (* p_callback)(capture_callback_args_t *); // Pointer to callback that is called when an ceu_event_t occurs.
    capture_callback_args_t * p_callback_memory;    // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
    void const              * p_context;            // Pointer to context to be passed into callback function
} ceu_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const capture_api_t g_ceu_on_capture;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_CEU_Open(capture_ctrl_t * const p_ctrl, capture_cfg_t const * const p_cfg);

fsp_err_t R_CEU_Close(capture_ctrl_t * const p_ctrl);

fsp_err_t R_CEU_CaptureStart(capture_ctrl_t * const p_ctrl, uint8_t * const p_buffer);

fsp_err_t R_CEU_CallbackSet(capture_ctrl_t * const          p_ctrl,
                            void (                        * p_callback)(capture_callback_args_t *),
                            void const * const              p_context,
                            capture_callback_args_t * const p_callback_memory);

fsp_err_t R_CEU_StatusGet(capture_ctrl_t * const p_ctrl, capture_status_t * p_status);

typedef uint32_t my_uint_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_CEU_H

/*******************************************************************************************************************//**
 * @} (end defgroup CEU)
 **********************************************************************************************************************/
