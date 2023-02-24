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
 * @defgroup SLCDC_API SLCDC Interface
 * @brief Interface for Segment LCD controllers.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_SLCDC_API_H
#define R_SLCDC_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** LCD display bias method. */
typedef enum e_slcd_bias_method
{
    SLCDC_BIAS_2 = 0,                  ///< 1/2 bias method
    SLCDC_BIAS_3,                      ///< 1/3 bias method
    SLCDC_BIAS_4,                      ///< 1/4 bias method
} slcdc_bias_method_t;

/** Time slice of LCD display. */
typedef enum e_slcd_time_slice
{
    SLCDC_STATIC  = 0,                 ///< Static
    SLCDC_SLICE_2 = 1,                 ///< 2-time slice
    SLCDC_SLICE_3 = 2,                 ///< 3-time slice
    SLCDC_SLICE_4 = 3,                 ///< 4-time slice
    SLCDC_SLICE_8 = 5,                 ///< 8-time slice
} slcdc_time_slice_t;

/** LCD display waveform select. */
typedef enum e_slcd_waveform
{
    SLCDC_WAVE_A = 0,                  ///< Waveform A
    SLCDC_WAVE_B,                      ///< Waveform B
} slcdc_waveform_t;

/** LCD Drive Voltage Generator Select.*/
typedef enum e_slcd_drive_volt_gen
{
    SLCDC_VOLT_EXTERNAL = 0,           ///< External resistance division method
    SLCDC_VOLT_INTERNAL,               ///< Internal voltage boosting method
    SLCDC_VOLT_CAPACITOR,              ///< Capacitor split method
} slcdc_drive_volt_gen_t;

/** Display Data Area Control*/
typedef enum e_slcd_display_area_control_blink
{
    SLCDC_NOT_BLINKING = 0,            ///< Display either A-pattern or B-pattern data
    SLCDC_BLINKING,                    ///< Alternately display A-pattern and B-pattern data
} slcdc_display_area_control_blink_t;

/** Display Area data */
typedef enum e_slcd_display_area
{
    SLCDC_DISP_A = 0,                  ///< Display A-pattern data
    SLCDC_DISP_B,                      ///< Display B-pattern data
    SLCDC_DISP_BLINK,                  ///< Blink between A- and B-pattern
} slcdc_display_area_t;

/** LCD Boost Level (contrast) settings */
typedef enum e_slcd_contrast
{
    SLCDC_CONTRAST_0 = 0,              ///< Contrast level 0
    SLCDC_CONTRAST_1,                  ///< Contrast level 1
    SLCDC_CONTRAST_2,                  ///< Contrast level 2
    SLCDC_CONTRAST_3,                  ///< Contrast level 3
    SLCDC_CONTRAST_4,                  ///< Contrast level 4
    SLCDC_CONTRAST_5,                  ///< Contrast level 5
    SLCDC_CONTRAST_6,                  ///< Contrast level 6
    SLCDC_CONTRAST_7,                  ///< Contrast level 7
    SLCDC_CONTRAST_8,                  ///< Contrast level 8
    SLCDC_CONTRAST_9,                  ///< Contrast level 9
    SLCDC_CONTRAST_10,                 ///< Contrast level 10
    SLCDC_CONTRAST_11,                 ///< Contrast level 11
    SLCDC_CONTRAST_12,                 ///< Contrast level 12
    SLCDC_CONTRAST_13,                 ///< Contrast level 13
    SLCDC_CONTRAST_14,                 ///< Contrast level 14
    SLCDC_CONTRAST_15                  ///< Contrast level 15
} slcdc_contrast_t;

/** LCD Display Enable/Disable*/
typedef enum e_slcd_display_on_off
{
    SLCDC_DISP_OFF = 0,                ///< Display off
    SLCDC_DISP_ON,                     ///< Display on
} slcdc_display_on_off_t;

/** LCD Display output enable */
typedef enum e_slcd_display_enable_disable
{
    SLCDC_DISP_DISABLE = 0,            ///< Output ground level to segment/common pins
    SLCDC_DISP_ENABLE,                 ///< Output enable
} slcdc_display_enable_disable_t;

/** LCD Display clock selection */
typedef enum e_slcd_display_clock
{
    SLCDC_CLOCK_LOCO = 0x00,           ///< Display clock source LOCO
    SLCDC_CLOCK_SOSC = 0x01,           ///< Display clock source SOSC
    SLCDC_CLOCK_MOSC = 0x02,           ///< Display clock source MOSC
    SLCDC_CLOCK_HOCO = 0x03,           ///< Display clock source HOCO
} slcdc_display_clock_t;

/** LCD clock settings */
typedef enum e_slcdc_clk_div
{
    SLCDC_CLK_DIVISOR_LOCO_4 = 1,         ///< LOCO Clock/4
    SLCDC_CLK_DIVISOR_LOCO_8,             ///< LOCO Clock/8
    SLCDC_CLK_DIVISOR_LOCO_16,            ///< LOCO Clock/16
    SLCDC_CLK_DIVISOR_LOCO_32,            ///< LOCO Clock/32
    SLCDC_CLK_DIVISOR_LOCO_64,            ///< LOCO Clock/64
    SLCDC_CLK_DIVISOR_LOCO_128,           ///< LOCO Clock/128
    SLCDC_CLK_DIVISOR_LOCO_256,           ///< LOCO Clock/256
    SLCDC_CLK_DIVISOR_LOCO_512,           ///< LOCO Clock/512
    SLCDC_CLK_DIVISOR_LOCO_1024,          ///< LOCO Clock/1024

    SLCDC_CLK_DIVISOR_HOCO_256 = 0x11,    ///< HOCO Clock/256
    SLCDC_CLK_DIVISOR_HOCO_512,           ///< HOCO Clock/512
    SLCDC_CLK_DIVISOR_HOCO_1024,          ///< HOCO Clock/1024
    SLCDC_CLK_DIVISOR_HOCO_2048,          ///< HOCO Clock/2048
    SLCDC_CLK_DIVISOR_HOCO_4096,          ///< HOCO Clock/4096
    SLCDC_CLK_DIVISOR_HOCO_8192,          ///< HOCO Clock/8192
    SLCDC_CLK_DIVISOR_HOCO_16384,         ///< HOCO Clock/16384
    SLCDC_CLK_DIVISOR_HOCO_32768,         ///< HOCO Clock/32768
    SLCDC_CLK_DIVISOR_HOCO_65536,         ///< HOCO Clock/65536
    SLCDC_CLK_DIVISOR_HOCO_131072,        ///< HOCO Clock/131072
    SLCDC_CLK_DIVISOR_HOCO_262144,        ///< HOCO Clock/262144

    SLCDC_CLK_DIVISOR_HOCO_524288 = 0x2B, ///< HOCO Clock/524288
} slcdc_clk_div_t;

/** SLCDC configuration block */
typedef struct st_slcdc_cfg
{
    slcdc_display_clock_t  slcdc_clock;         ///< LCD clock source (LCDSCKSEL)
    slcdc_clk_div_t        slcdc_clock_setting; ///< LCD clock setting (LCDC0)
    slcdc_bias_method_t    bias_method;         ///< LCD display bias method select (LBAS bit)
    slcdc_time_slice_t     time_slice;          ///< Time slice of LCD display select (LDTY bit)
    slcdc_waveform_t       waveform;            ///< LCD display waveform select (LWAVE bit)
    slcdc_drive_volt_gen_t drive_volt_gen;      ///< LCD Drive Voltage Generator Select (MDSET bit)
    slcdc_contrast_t       contrast;            ///< LCD Boost Level (contrast setting)
} slcdc_cfg_t;

/** SLCDC control block.  Allocate an instance specific control block to pass into the SLCDC API calls.
 * @par Implemented as
 * - slcdc_instance_ctrl_t
 */

/** SLCDC control block */
typedef void slcdc_ctrl_t;

/** SLCDC functions implemented at the HAL layer will follow this API. */
typedef struct st_slcdc_api
{
    /** Open SLCDC.
     * @par Implemented as
     * - @ref R_SLCDC_Open()
     * @param[in,out]  p_ctrl        Pointer to display interface control block. Must be declared by user.
     * @param[in]      p_cfg         Pointer to display configuration structure. All elements of this structure must be
     *                               set by the user.
     */
    fsp_err_t (* open)(slcdc_ctrl_t * const p_ctrl, slcdc_cfg_t const * const p_cfg);

    /** Write data to the SLCDC segment data array.
     * Specifies the initial display data. Except when using 8-time slice mode, store values in the lower 4 bits when
     * writing to the A-pattern area and in the upper 4 bits when writing to the B-pattern area.
     * @par Implemented as
     * - @ref R_SLCDC_Write()
     * @param[in]  p_ctrl           Pointer to display interface control block.
     * @param[in]  start_segment    Specify the start segment number to be written.
     * @param[in]  p_data           Pointer to the display data to be written to the specified segments.
     * @param[in]  segment_count    Number of segments to be written.
     */
    fsp_err_t (* write)(slcdc_ctrl_t * const p_ctrl, uint8_t const start_segment, uint8_t const * p_data,
                        uint8_t const segment_count);

    /** Rewrite data in the SLCDC segment data array.
     * Rewrites the LCD display data in 1-bit units. If a bit is not specified for rewriting, the value stored in the bit is held as it is.
     * @par Implemented as
     * - @ref R_SLCDC_Modify()
     * @param[in]  p_ctrl           Pointer to display interface control block.
     * @param[in]  segment          The segment to be written.
     * @param[in]  data_mask        Mask the data being displayed. Set 0 to the bit to be rewritten and set 1 to the other bits. Multiple bits can be rewritten.
     * @param[in]  data             Specify display data to rewrite to the specified segment.
     *
     */
    fsp_err_t (* modify)(slcdc_ctrl_t * const p_ctrl, uint8_t const segment, uint8_t const data_mask,
                         uint8_t const data);

    /** Enable display signal output.
     * Displays the segment data on the LCD.
     * @par Implemented as
     * - @ref R_SLCDC_Start()
     * @param[in]  p_ctrl           Pointer to display interface control block.
     */
    fsp_err_t (* start)(slcdc_ctrl_t * const p_ctrl);

    /** Disable display signal output.
     * Stops displaying data on the LCD.
     * @par Implemented as
     * - @ref R_SLCDC_Stop()
     * @param[in]  p_ctrl           Pointer to display interface control block.
     */
    fsp_err_t (* stop)(slcdc_ctrl_t * const p_ctrl);

    /** Set the display contrast.
     * This function can be used only when the internal voltage boosting method is used for drive voltage generation.
     * @par Implemented as
     * - @ref R_SLCDC_SetContrast()
     * @param[in]  p_ctrl           Pointer to display interface control block.
     */
    fsp_err_t (* setContrast)(slcdc_ctrl_t * const p_ctrl, slcdc_contrast_t const contrast);

    /** Set LCD display area.
     * This function sets a specified display area, A-pattern or B-pattern. This function can be used to 'blink' the
     * display between A-pattern and B-pattern area data.
     *
     * When using blinking, the RTC is required to operate before this function is executed. To configure the RTC, follow the steps below.
     *  1) Open RTC
     *  2) Set Periodic IRQ
     *  3) Start RTC counter
     *  4) Enable IRQ, RTC_EVENT_PERIODIC_IRQ
     *  Refer to the User's Manual for the detailed procedure.
     *
     * @par Implemented as
     * - @ref R_SLCDC_SetDisplayArea()
     * @param[in]  p_ctrl           Pointer to display interface control block.
     * @param[in]  display_area     Display area to be used, A-pattern or B-pattern area.
     */
    fsp_err_t (* setDisplayArea)(slcdc_ctrl_t * const p_ctrl, slcdc_display_area_t const display_area);

    /** Close SLCDC.
     * @par Implemented as
     * - @ref R_SLCDC_Close()
     * @param[in]     p_ctrl   Pointer to display interface control block.
     */
    fsp_err_t (* close)(slcdc_ctrl_t * const p_ctrl);
} slcdc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_slcdc_instance
{
    slcdc_ctrl_t      * p_ctrl;        ///< Pointer to the control structure for this instance
    slcdc_cfg_t const * p_cfg;         ///< Pointer to the configuration structure for this instance
    slcdc_api_t const * p_api;         ///< Pointer to the API structure for this instance
} slcdc_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup SLCDC_API)
 **********************************************************************************************************************/
