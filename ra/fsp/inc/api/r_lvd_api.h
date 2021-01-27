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
 * @defgroup LVD_API Low Voltage Detection Interface
 * @brief Interface for Low Voltage Detection
 *
 * @section LVD_API_SUMMARY Summary
 * The LVD driver provides functions for configuring the LVD voltage monitors and detectors.
 *
 * Implemented by:
 * - @ref LVD
 *
 * @{
 **********************************************************************************************************************/
#ifndef R_LVD_API_H
#define R_LVD_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/** Register definitions, common services, and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define LVD_API_VERSION_MAJOR    (1U)  // DEPRECATED
#define LVD_API_VERSION_MINOR    (0U)  // DEPRECATED

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Voltage detection level */

/** The thresholds supported by each MCU are in the MCU User's Manual as well as
 *  in the r_lvd module description on the stack tab of the RA project. */
typedef enum
{
    LVD_THRESHOLD_MONITOR_1_LEVEL_4_29V = 0x00UL, ///< 4.29V
    LVD_THRESHOLD_MONITOR_1_LEVEL_4_14V = 0x01UL, ///< 4.14V
    LVD_THRESHOLD_MONITOR_1_LEVEL_4_02V = 0x02UL, ///< 4.02V
    LVD_THRESHOLD_MONITOR_1_LEVEL_3_84V = 0x03UL, ///< 3.84V
    LVD_THRESHOLD_MONITOR_1_LEVEL_3_10V = 0x04UL, ///< 3.10V
    LVD_THRESHOLD_MONITOR_1_LEVEL_3_00V = 0x05UL, ///< 3.00V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_90V = 0x06UL, ///< 2.90V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_79V = 0x07UL, ///< 2.79V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_68V = 0x08UL, ///< 2.68V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_58V = 0x09UL, ///< 2.58V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_48V = 0x0AUL, ///< 2.48V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_20V = 0x0BUL, ///< 2.20V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_96V = 0x0CUL, ///< 1.96V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_86V = 0x0DUL, ///< 1.86V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_75V = 0x0EUL, ///< 1.75V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_65V = 0x0FUL, ///< 1.65V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_99V = 0x11UL, ///< 2.99V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_92V = 0x12UL, ///< 2.92V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_85V = 0x13UL, ///< 2.85V
    LVD_THRESHOLD_MONITOR_2_LEVEL_4_29V = 0x00UL, ///< 4.29V
    LVD_THRESHOLD_MONITOR_2_LEVEL_4_14V = 0x01UL, ///< 4.14V
    LVD_THRESHOLD_MONITOR_2_LEVEL_4_02V = 0x02UL, ///< 4.02V
    LVD_THRESHOLD_MONITOR_2_LEVEL_3_84V = 0x03UL, ///< 3.84V
    LVD_THRESHOLD_MONITOR_2_LEVEL_2_99V = 0x05UL, ///< 2.99V
    LVD_THRESHOLD_MONITOR_2_LEVEL_2_92V = 0x06UL, ///< 2.92V
    LVD_THRESHOLD_MONITOR_2_LEVEL_2_85V = 0x07UL, ///< 2.85V
} lvd_threshold_t;

/** Response types for handling threshold crossing event. */
typedef enum e_lvd_response
{
    LVD_RESPONSE_NMI,                  ///< Non-maskable interrupt
    LVD_RESPONSE_INTERRUPT,            ///< Maskable interrupt
    LVD_RESPONSE_RESET,                ///< Reset
    LVD_RESPONSE_NONE,                 ///< No response, status must be requested via statusGet function
} lvd_response_t;

/** The direction from which Vcc must cross the threshold to trigger a detection (rising, falling, or both). */
typedef enum e_lvd_voltage_slope
{
    LVD_VOLTAGE_SLOPE_RISING  = 0,     ///< When VCC >= Vdet2 (rise) is detected
    LVD_VOLTAGE_SLOPE_FALLING = 1,     ///< When VCC < Vdet2 (drop) is detected
    LVD_VOLTAGE_SLOPE_BOTH    = 2,     ///< When drop and rise are detected
} lvd_voltage_slope_t;

/** Sample clock divider, use LVD_SAMPLE_CLOCK_DISABLED to disable digital filtering */
typedef enum e_lvd_sample_clock
{
    LVD_SAMPLE_CLOCK_LOCO_DIV_2  = 0,  ///< Digital filter sample clock is LOCO divided by 2
    LVD_SAMPLE_CLOCK_LOCO_DIV_4  = 1,  ///< Digital filter sample clock is LOCO divided by 4
    LVD_SAMPLE_CLOCK_LOCO_DIV_8  = 2,  ///< Digital filter sample clock is LOCO divided by 8
    LVD_SAMPLE_CLOCK_LOCO_DIV_16 = 3,  ///< Digital filter sample clock is LOCO divided by 16
    LVD_SAMPLE_CLOCK_DISABLED    = -1, ///< Digital filter is disabled
} lvd_sample_clock_t;

/** Negation delay of LVD reset signal follows reset or voltage in range */
typedef enum e_lvd_negation_delay
{
    /**
     *  Negation follows a stabilization time (tLVDn)
     *  after VCC > Vdet1 is detected.
     *  If a transition to software standby or deep software
     *  standby is to be made, the only possible value for
     *  the RN bit is LVD_NEGATION_DELAY_FROM_VOLTAGE
     */
    LVD_NEGATION_DELAY_FROM_VOLTAGE = 0,

    /**
     *  Negation follows a stabilization time (tLVDn) after
     *  assertion of the LVDn reset.
     *  If a transition to software standby or deep software
     *  standby is to be made, the only possible value for
     *  the RN bit is LVD_NEGATION_DELAY_FROM_VOLTAGE
     */
    LVD_NEGATION_DELAY_FROM_RESET = 1,
} lvd_negation_delay_t;

/** Threshold crossing detection (latched) */
typedef enum e_lvd_threshold_crossing
{
    LVD_THRESHOLD_CROSSING_NOT_DETECTED = 0, ///< Threshold crossing has not been detected.
    LVD_THRESHOLD_CROSSING_DETECTED     = 1, ///< Threshold crossing has been detected.
} lvd_threshold_crossing_t;

/** Instantaneous status of VCC (above or below threshold) */
typedef enum e_lvd_current_state
{
    LVD_CURRENT_STATE_BELOW_THRESHOLD = 0, ///< VCC <  threshold
    LVD_CURRENT_STATE_ABOVE_THRESHOLD = 1, ///< VCC >= threshold or monitor is disabled
} lvd_current_state_t;

/**
 * Current state of a voltage monitor.
 */
typedef struct st_lvd_status
{
    /** Threshold crossing detection (latched) */
    lvd_threshold_crossing_t crossing_detected;

    /** Instantaneous status of monitored voltage (above or below threshold) */
    lvd_current_state_t current_state;
} lvd_status_t;

/** LVD callback parameter definition */
typedef struct st_lvd_callback_args
{
    uint32_t            monitor_number; ///< Monitor number
    lvd_current_state_t current_state;  ///< Current state of the voltage monitor
    void const        * p_context;      ///< Placeholder for user data
} lvd_callback_args_t;

/** LVD configuration structure */
typedef struct st_lvd_cfg
{
    /** Monitor number, 1, 2, ... */
    uint32_t monitor_number;

    /** Threshold for out of range voltage detection */
    lvd_threshold_t voltage_threshold;

    /** Response on detecting a threshold crossing */
    lvd_response_t detection_response;

    /** Direction of voltage crossing that will trigger a detection (Rising Edge, Falling Edge, Both). */
    lvd_voltage_slope_t voltage_slope;

    /** Negation of LVD signal follows reset or voltage in range */
    lvd_negation_delay_t negation_delay;

    /** Sample clock divider, use LVD_SAMPLE_CLOCK_DISABLED to disable digital filtering */
    lvd_sample_clock_t sample_clock_divisor;

    /** Interrupt number. */
    IRQn_Type irq;

    /** Interrupt priority level. */
    uint8_t monitor_ipl;

    /** User function to be called from interrupt */
    void (* p_callback)(lvd_callback_args_t * p_args);

    /** Placeholder for user data. Passed to the user callback in  */
    void const * p_context;

    /** Extension parameter for hardware specific settings */
    void const * p_extend;
} lvd_cfg_t;

/** LVD control block.  Allocate an instance specific control block to pass into the LVD API calls.
 * @par Implemented as
 * - lvd_instance_ctrl_t
 */
typedef void lvd_ctrl_t;

/** LVD driver API structure.
 *  LVD driver functions implemented at the HAL layer will adhere to this API.
 */
typedef struct st_lvd_api
{
    /** Initializes a low voltage detection driver according to the passed-in configuration structure.
     * @par Implemented as
     * - @ref R_LVD_Open()
     * @param[in]       p_ctrl      Pointer to control structure for the driver instance
     * @param[in]       p_cfg       Pointer to the configuration structure for the driver instance
     **/
    fsp_err_t (* open)(lvd_ctrl_t * const p_ctrl, lvd_cfg_t const * const p_cfg);

    /** Get the current state of the monitor, (threshold crossing detected, voltage currently above or below threshold).
     * Must be used if the peripheral was initialized with lvd_response_t set to LVD_RESPONSE_NONE.
     * @par Implemented as
     * - @ref R_LVD_StatusGet()
     * @param[in]       p_ctrl          Pointer to the control structure for the driver instance
     * @param[in,out]   p_lvd_status    Pointer to a lvd_status_t structure
     **/
    fsp_err_t (* statusGet)(lvd_ctrl_t * const p_ctrl, lvd_status_t * p_lvd_status);

    /** Clears the latched status of the monitor.
     * Must be used if the peripheral was initialized with lvd_response_t set to LVD_RESPONSE_NONE.
     * @par Implemented as
     * - @ref R_LVD_StatusClear()
     * @param[in]       p_ctrl      Pointer to the control structure for the driver instance
     **/
    fsp_err_t (* statusClear)(lvd_ctrl_t * const p_ctrl);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref R_LVD_CallbackSet()
     *
     * @param[in]   p_ctrl                   Pointer to the LVD control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(lvd_ctrl_t * const p_api_ctrl, void (* p_callback)(lvd_callback_args_t *),
                              void const * const p_context, lvd_callback_args_t * const p_callback_memory);

    /** Disables the LVD peripheral.
     * Closes the driver instance.
     * @par Implemented as
     * - @ref R_LVD_Close()
     * @param[in]   p_ctrl      Pointer to the control structure for the driver instance
     **/
    fsp_err_t (* close)(lvd_ctrl_t * const p_ctrl);

    /* DEPRECATED Returns the LVD driver version based on compile time macros.
     * @par Implemented as
     * - @ref R_LVD_VersionGet()
     * @param[in,out]   p_version   Pointer to version structure
     **/
    fsp_err_t (* versionGet)(fsp_version_t * const p_version);
} lvd_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_lvd_instance
{
    lvd_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    lvd_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this interface instance
    lvd_api_t const * p_api;           ///< Pointer to the API structure for this interface instance
} lvd_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup LVD_API)
 **********************************************************************************************************************/
