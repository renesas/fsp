/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_SENSOR_INTERFACES
 * @defgroup RM_HS400X_API HS400X Middleware Interface
 * @brief Interface for HS400X Middleware functions.
 *
 * @section RM_HS400X_API_Summary Summary
 * The HS400X interface provides HS400X functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_HS400X_API_H_
#define RM_HS400X_API_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include <string.h>
 #include "platform.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include <string.h>
 #include "r_cg_macrodriver.h"
 #include "r_fsp_error.h"
#else
 #include "bsp_api.h"
#endif

#include "rm_comms_api.h"

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
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
typedef enum e_rm_hs400x_event
{
    RM_HS400X_EVENT_SUCCESS = 0,
    RM_HS400X_EVENT_MEASUREMENT_NOT_COMPLETE,
    RM_HS400X_EVENT_MEASUREMENT_NOT_RUNNING,
    RM_HS400X_EVENT_ALERT_TRIGGERED,
    RM_HS400X_EVENT_ERROR,
} rm_hs400x_event_t;

/** Resolution type for temperature */
typedef enum e_rm_hs400x_temperature_resolution
{
    RM_HS400X_TEMPERATURE_RESOLUTION_8BIT  = 0x00,
    RM_HS400X_TEMPERATURE_RESOLUTION_10BIT = 0x01,
    RM_HS400X_TEMPERATURE_RESOLUTION_12BIT = 0x02,
    RM_HS400X_TEMPERATURE_RESOLUTION_14BIT = 0x03,
} rm_hs400x_temperature_resolution_t;

/** Resolution type for humidity */
typedef enum e_rm_hs400x_humidity_resolution
{
    RM_HS400X_HUMIDITY_RESOLUTION_8BIT  = 0x00,
    RM_HS400X_HUMIDITY_RESOLUTION_10BIT = 0x04,
    RM_HS400X_HUMIDITY_RESOLUTION_12BIT = 0x08,
    RM_HS400X_HUMIDITY_RESOLUTION_14BIT = 0x0C,
} rm_hs400x_humidity_resolution_t;

/** Frequency of periodic measurement */
typedef enum e_rm_hs400x_periodic_measurement_frequency
{
    RM_HS400X_PERIODIC_MEASUREMENT_FREQUENCY_2HZ   = 0x40, ///< A measurement every 0.5s
    RM_HS400X_PERIODIC_MEASUREMENT_FREQUENCY_1HZ   = 0x50, ///< A measurement every 1s
    RM_HS400X_PERIODIC_MEASUREMENT_FREQUENCY_0P4HZ = 0x60, ///< A measurement every 2.5s
} rm_hs400x_periodic_measurement_frequency_t;

/** HS400X callback parameter definition */
typedef struct st_rm_hs400x_callback_args
{
    void            * p_context;
    rm_hs400x_event_t event;
} rm_hs400x_callback_args_t;

/** HS400X resolution block */
typedef struct st_rm_hs400x_resolution
{
    rm_hs400x_temperature_resolution_t temperature;
    rm_hs400x_humidity_resolution_t    humidity;
} rm_hs400x_resolutions_t;

/** HS400X raw data */
typedef struct st_rm_hs400x_raw_data
{
    uint8_t humidity[2];               ///< Upper 2 bits of 0st element are mask
    uint8_t temperature[2];            ///< Upper 2 bits of 0st element are mask
    uint8_t checksum;                  ///< Checksum
} rm_hs400x_raw_data_t;

/** HS400X sensor data block */
typedef struct st_rm_hs400x_sensor_data
{
    int16_t integer_part;
    int16_t decimal_part;              ///< To two decimal places
} rm_hs400x_sensor_data_t;

/** HS400X data block */
typedef struct st_rm_hs400x_data
{
    rm_hs400x_sensor_data_t temperature;
    rm_hs400x_sensor_data_t humidity;
} rm_hs400x_data_t;

/** HS400X Configuration */
typedef struct st_rm_hs400x_cfg
{
    rm_hs400x_temperature_resolution_t const         temperature_resolution; ///< Resolution for temperature
    rm_hs400x_humidity_resolution_t const            humidity_resolution;    ///< Resolution for humidity
    rm_hs400x_periodic_measurement_frequency_t const frequency;              ///< Frequency for periodic measurement
    rm_comms_instance_t const * p_comms_instance;                            ///< Pointer to Communications Middleware instance.
    void       * p_context;                                                  ///< Pointer to the user-provided context.
    void const * p_extend;                                                   ///< Pointer to extended configuration by instance of interface.
    void (* p_comms_callback)(rm_hs400x_callback_args_t * p_args);           ///< I2C Communications callback
} rm_hs400x_cfg_t;

/** HS400X control block.  Allocate an instance specific control block to pass into the HS400X API calls.
 */
typedef void rm_hs400x_ctrl_t;

/** HS400X APIs */
typedef struct st_rm_hs400x_api
{
    /** Open sensor.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_hs400x_ctrl_t * const p_ctrl, rm_hs400x_cfg_t const * const p_cfg);

    /** Start one shot measurement.
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     */
    fsp_err_t (* measurementStart)(rm_hs400x_ctrl_t * const p_ctrl);

    /** Stop a period measurement.
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     */
    fsp_err_t (* measurementStop)(rm_hs400x_ctrl_t * const p_ctrl);

    /** Read ADC data from HS400X.
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data structure.
     */
    fsp_err_t (* read)(rm_hs400x_ctrl_t * const p_ctrl, rm_hs400x_raw_data_t * const p_raw_data);

    /** Calculate humidity and temperature values from ADC data.
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data.
     * @param[in]  p_hs400x_data    Pointer to HS400X data structure.
     */
    fsp_err_t (* dataCalculate)(rm_hs400x_ctrl_t * const p_ctrl, rm_hs400x_raw_data_t * const p_raw_data,
                                rm_hs400x_data_t * const p_hs400x_data);

    /** Close HS400X.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_hs400x_ctrl_t * const p_ctrl);
} rm_hs400x_api_t;

/** HS400X instance */
typedef struct st_rm_hs400x_instance
{
    rm_hs400x_ctrl_t      * p_ctrl;    /**< Pointer to the control structure for this instance */
    rm_hs400x_cfg_t const * p_cfg;     /**< Pointer to the configuration structure for this instance */
    rm_hs400x_api_t const * p_api;     /**< Pointer to the API structure for this instance */
} rm_hs400x_instance_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_HS400X_API_H_*/

/*******************************************************************************************************************//**
 * @} (end defgroup RM_HS400X_API)
 **********************************************************************************************************************/
