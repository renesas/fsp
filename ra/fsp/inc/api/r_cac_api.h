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

#ifndef R_CAC_API_H
#define R_CAC_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup CAC_API CAC Interface
 * @brief Interface for clock frequency accuracy measurements.
 *
 * @section CAC_API_SUMMARY Summary
 * The interface for the clock frequency accuracy measurement circuit (CAC) peripheral is used to check a system
 * clock frequency with a reference clock signal by counting the number of pulses of the clock to be measured.
 *
 * Implemented by:
 * @ref CAC
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Event types returned by the ISR callback when used in CAC interrupt mode */
typedef enum e_cac_event
{
    CAC_EVENT_FREQUENCY_ERROR,         ///< Frequency error
    CAC_EVENT_MEASUREMENT_COMPLETE,    ///< Measurement complete
    CAC_EVENT_COUNTER_OVERFLOW         ///< Counter overflow
} cac_event_t;

/** CAC control block.  Allocate an instance specific control block to pass into the CAC API calls.
 * @par Implemented as
 * - cac_instance_ctrl_t
 */
typedef void cac_ctrl_t;

/** Enumeration of the two possible clocks. */
typedef enum e_cac_clock_type
{
    CAC_CLOCK_MEASURED,                ///< Measurement clock
    CAC_CLOCK_REFERENCE                ///< Reference clock
} cac_clock_type_t;

/** Enumeration of the possible clock sources for both the reference and measurement clocks. */
typedef enum e_cac_clock_source
{
    CAC_CLOCK_SOURCE_MAIN_OSC = 0x00,  ///< Main clock oscillator
    CAC_CLOCK_SOURCE_SUBCLOCK = 0x01,  ///< Sub-clock
    CAC_CLOCK_SOURCE_HOCO     = 0x02,  ///< HOCO (High speed on chip oscillator)
    CAC_CLOCK_SOURCE_MOCO     = 0x03,  ///< MOCO (Middle speed on chip oscillator)
    CAC_CLOCK_SOURCE_LOCO     = 0x04,  ///< LOCO (Low speed on chip oscillator)
    CAC_CLOCK_SOURCE_PCLKB    = 0x05,  ///< PCLKB (Peripheral Clock B)
    CAC_CLOCK_SOURCE_IWDT     = 0x06,  ///< IWDT-dedicated on-chip oscillator
    CAC_CLOCK_SOURCE_EXTERNAL = 0x07,  ///< Externally supplied measurement clock on CACREF pin
} cac_clock_source_t;

/** Enumeration of available dividers for the reference clock. */
typedef enum e_cac_ref_divider
{
    CAC_REF_DIV_32   = 0x00,           ///< Reference clock divided by 32
    CAC_REF_DIV_128  = 0x01,           ///< Reference clock divided by 128
    CAC_REF_DIV_1024 = 0x02,           ///< Reference clock divided by 1024
    CAC_REF_DIV_8192 = 0x03,           ///< Reference clock divided by 8192
} cac_ref_divider_t;

/** Enumeration of available digital filter settings for an external reference clock. */
typedef enum e_cac_ref_digfilter
{
    CAC_REF_DIGITAL_FILTER_OFF = 0x00, ///< No digital filter on the CACREF pin for reference clock
    CAC_REF_DIGITAL_FILTER_1   = 0x01, ///< Sampling clock for digital filter = measuring frequency
    CAC_REF_DIGITAL_FILTER_4   = 0x02, ///< Sampling clock for digital filter = measuring frequency/4
    CAC_REF_DIGITAL_FILTER_16  = 0x03, ///< Sampling clock for digital filter = measuring frequency/16
} cac_ref_digfilter_t;

/** Enumeration of available edge detect settings for the reference clock. */
typedef enum e_cac_ref_edge
{
    CAC_REF_EDGE_RISE = 0x00,          ///< Rising edge detect for the Reference clock
    CAC_REF_EDGE_FALL = 0x01,          ///< Falling edge detect for the Reference clock
    CAC_REF_EDGE_BOTH = 0x02           ///< Both Rising and Falling edges detect for the Reference clock
} cac_ref_edge_t;

/** Enumeration of available dividers for the measurement clock */
typedef enum e_cac_meas_divider
{
    CAC_MEAS_DIV_1  = 0x00,            ///< Measurement clock divided by 1
    CAC_MEAS_DIV_4  = 0x01,            ///< Measurement clock divided by 4
    CAC_MEAS_DIV_8  = 0x02,            ///< Measurement clock divided by 8
    CAC_MEAS_DIV_32 = 0x03             ///< Measurement clock divided by 32
} cac_meas_divider_t;

/** Structure defining the settings that apply to reference clock configuration. */
typedef struct st_cac_ref_clock_config
{
    cac_ref_divider_t   divider;       ///< Divider specification for the Reference clock
    cac_clock_source_t  clock;         ///< Clock source for the Reference clock
    cac_ref_digfilter_t digfilter;     ///< Digital filter selection for the CACREF ext clock
    cac_ref_edge_t      edge;          ///< Edge detection for the Reference clock
} cac_ref_clock_config_t;

/** Structure defining the settings that apply to measurement clock configuration. */
typedef struct st_cac_meas_clock_config
{
    cac_meas_divider_t divider;        ///< Divider specification for the Measurement clock
    cac_clock_source_t clock;          ///< Clock source for the Measurement clock
} cac_meas_clock_config_t;

/** Callback function parameter data */
typedef struct st_cac_user_cb_data
{
    cac_event_t  event;                ///< The event can be used to identify what caused the callback.
    void const * p_context;            ///< Value provided in configuration structure.
} cac_callback_args_t;

/** CAC Configuration */
typedef struct st_cac_cfg
{
    cac_ref_clock_config_t  cac_ref_clock;             ///< Reference clock specific settings
    cac_meas_clock_config_t cac_meas_clock;            ///< Measurement clock specific settings
    uint16_t                cac_upper_limit;           ///< The upper limit counter threshold
    uint16_t                cac_lower_limit;           ///< The lower limit counter threshold

    IRQn_Type mendi_irq;                               ///< Measurement End IRQ number
    IRQn_Type ovfi_irq;                                ///< Measurement Overflow IRQ number
    IRQn_Type ferri_irq;                               ///< Frequency Error IRQ number

    uint8_t mendi_ipl;                                 ///< Measurement end interrupt priority
    uint8_t ovfi_ipl;                                  ///< Overflow interrupt priority
    uint8_t ferri_ipl;                                 ///< Frequency error interrupt priority

    void (* p_callback)(cac_callback_args_t * p_args); ///< Callback provided when a CAC interrupt ISR occurs.
    void const * p_context;                            ///< Passed to user callback in @ref cac_callback_args_t.

    void const * p_extend;                             ///< CAC hardware dependent configuration */
} cac_cfg_t;

/** CAC functions implemented at the HAL layer API */
typedef struct st_cac_api
{
    /** Open function for CAC device.
     * @param[out]  p_ctrl     Pointer to CAC device control. Must be declared by user.
     * @param[in]   cac_cfg_t  Pointer to CAC configuration structure.
     */
    fsp_err_t (* open)(cac_ctrl_t * const p_ctrl, cac_cfg_t const * const p_cfg);

    /** Begin a measurement for the CAC peripheral.
     * @param[in]  p_ctrl        Pointer to CAC device control.
     */
    fsp_err_t (* startMeasurement)(cac_ctrl_t * const p_ctrl);

    /** End a measurement for the CAC peripheral.
     * @param[in]  p_ctrl        Pointer to CAC device control.
     */
    fsp_err_t (* stopMeasurement)(cac_ctrl_t * const p_ctrl);

    /** Read function for CAC peripheral.
     * @param[in]   p_ctrl Control for the CAC device context.
     * @param[in]   p_counter    Pointer to variable in which to store the current CACNTBR register contents.
     */
    fsp_err_t (* read)(cac_ctrl_t * const p_ctrl, uint16_t * const p_counter);

    /** Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref R_CAC_CallbackSet()
     *
     * @param[in]   p_ctrl                   Control block set in @ref cac_api_t::open call
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(cac_ctrl_t * const p_api_ctrl, void (* p_callback)(cac_callback_args_t *),
                              void const * const p_context, cac_callback_args_t * const p_callback_memory);

    /** Close function for CAC device.
     * @param[in]  p_ctrl        Pointer to CAC device control.
     */
    fsp_err_t (* close)(cac_ctrl_t * const p_ctrl);
} cac_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_cac_instance
{
    cac_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    cac_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    cac_api_t const * p_api;           ///< Pointer to the API structure for this instance
} cac_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup CAC_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
