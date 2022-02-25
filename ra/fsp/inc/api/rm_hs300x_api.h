/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @defgroup RM_HS300X_API HS300X Middleware Interface
 * @brief Interface for HS300X Middleware functions.
 *
 * @section RM_HS300X_API_Summary Summary
 * The HS300X interface provides HS300X functionality.
 *
 * The HS300X interface can be implemented by:
 * - @ref RM_HS300X
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_HS300X_API_H_
#define RM_HS300X_API_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include <string.h>
 #include "platform.h"
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
 #include <string.h>
 #include "r_cg_macrodriver.h"
 #include "r_fsp_error.h"
#else
 #include "bsp_api.h"
#endif

#include "rm_comms_api.h"

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Event in the callback function */
typedef enum e_rm_hs300x_event
{
    RM_HS300X_EVENT_SUCCESS = 0,
    RM_HS300X_EVENT_ERROR,
} rm_hs300x_event_t;

/** Data type of HS300X */
typedef enum e_rm_hs300x_data_type
{
    RM_HS300X_HUMIDITY_DATA = 0,
    RM_HS300X_TEMPERATURE_DATA,
} rm_hs300x_data_type_t;

/** Resolution type of HS300X */
typedef enum e_rm_hs300x_resolution
{
    RM_HS300X_RESOLUTION_8BIT  = 0x00,
    RM_HS300X_RESOLUTION_10BIT = 0x04,
    RM_HS300X_RESOLUTION_12BIT = 0x08,
    RM_HS300X_RESOLUTION_14BIT = 0x0C,
} rm_hs300x_resolution_t;

/** HS300X callback parameter definition */
typedef struct st_rm_hs300x_callback_args
{
    void const      * p_context;
    rm_hs300x_event_t event;
} rm_hs300x_callback_args_t;

/** HS300X raw data */
typedef struct st_rm_hs300x_raw_data
{
    uint8_t humidity[2];               ///< Upper 2 bits of 0th element are data status
    uint8_t temperature[2];            ///< Lower 2 bits of 1st element are mask
} rm_hs300x_raw_data_t;

/** HS300X sensor data block */
typedef struct st_rm_hs300x_sensor_data
{
    int16_t integer_part;
    int16_t decimal_part;              ///< To two decimal places
} rm_hs300x_sensor_data_t;

/** HS300X data block */
typedef struct st_rm_hs300x_data
{
    rm_hs300x_sensor_data_t humidity;
    rm_hs300x_sensor_data_t temperature;
} rm_hs300x_data_t;

/** HS300X Configuration */
typedef struct st_rm_hs300x_cfg
{
    rm_comms_instance_t const * p_instance;                  ///< Pointer to Communications Middleware instance.
    void const                * p_context;                   ///< Pointer to the user-provided context.
    void const                * p_extend;                    ///< Pointer to extended configuration by instance of interface.
    void (* p_callback)(rm_hs300x_callback_args_t * p_args); ///< Pointer to callback function.
} rm_hs300x_cfg_t;

/** HS300X control block.  Allocate an instance specific control block to pass into the HS300X API calls.
 * @par Implemented as
 * - rm_hs300x_instance_ctrl_t
 */
typedef void rm_hs300x_ctrl_t;

/** HS300X APIs */
typedef struct st_rm_hs300x_api
{
    /** Open sensor.
     * @par Implemented as
     * - @ref RM_HS300X_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_hs300x_ctrl_t * const p_ctrl, rm_hs300x_cfg_t const * const p_cfg);

    /** Start a measurement.
     * @par Implemented as
     * - @ref RM_HS300X_MeasurementStart()
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     */
    fsp_err_t (* measurementStart)(rm_hs300x_ctrl_t * const p_ctrl);

    /** Read ADC data from HS300X.
     * @par Implemented as
     * - @ref RM_HS300X_Read()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data structure.
     */
    fsp_err_t (* read)(rm_hs300x_ctrl_t * const p_ctrl, rm_hs300x_raw_data_t * const p_raw_data);

    /** Calculate humidity and temperature values from ADC data.
     * @par Implemented as
     * - @ref RM_HS300X_DataCalculate()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data.
     * @param[in]  p_hs300x_data    Pointer to HS300X data structure.
     */
    fsp_err_t (* dataCalculate)(rm_hs300x_ctrl_t * const p_ctrl, rm_hs300x_raw_data_t * const p_raw_data,
                                rm_hs300x_data_t * const p_hs300x_data);

    /** Enter the programming mode.
     * @par Implemented as
     * - @ref RM_HS300X_ProgrammingModeEnter()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     */
    fsp_err_t (* programmingModeEnter)(rm_hs300x_ctrl_t * const p_ctrl);

    /** Change the sensor resolution.
     * @par Implemented as
     * - @ref RM_HS300X_ResolutionChange()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  data_type        Data type of HS300X.
     * @param[in]  resolution       Resolution type of HS300X.
     */
    fsp_err_t (* resolutionChange)(rm_hs300x_ctrl_t * const p_ctrl, rm_hs300x_data_type_t const data_type,
                                   rm_hs300x_resolution_t const resolution);

    /** Get the sensor ID.
     * @par Implemented as
     * - @ref RM_HS300X_SensorIdGet()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_sensor_id      Pointer to sensor ID of HS300X.
     */
    fsp_err_t (* sensorIdGet)(rm_hs300x_ctrl_t * const p_ctrl, uint32_t * const p_sensor_id);

    /** Exit the programming mode.
     * @par Implemented as
     * - @ref RM_HS300X_ProgrammingModeExit()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     */
    fsp_err_t (* programmingModeExit)(rm_hs300x_ctrl_t * const p_ctrl);

    /** Close HS300X.
     * @par Implemented as
     * - @ref RM_HS300X_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_hs300x_ctrl_t * const p_ctrl);
} rm_hs300x_api_t;

/** HS300X instance */
typedef struct st_rm_hs300x_instance
{
    rm_hs300x_ctrl_t      * p_ctrl;    /**< Pointer to the control structure for this instance */
    rm_hs300x_cfg_t const * p_cfg;     /**< Pointer to the configuration structure for this instance */
    rm_hs300x_api_t const * p_api;     /**< Pointer to the API structure for this instance */
} rm_hs300x_instance_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_HS300X_API_H_*/

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_HS300X_API)
 **********************************************************************************************************************/
