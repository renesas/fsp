/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_SENSOR_INTERFACES
 * @defgroup RM_AIR_SENSOR_API SENSOR Middleware Interface
 * @brief Interface for AIR SENSOR Middleware functions.
 *
 * @section RM_AIR_SENSOR_API_Summary Summary
 * The AIR SENSOR interface provides AIR SENSOR functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

/* Guards against multiple inclusion */
#ifndef RM_AIR_SENSOR_API_H_
#define RM_AIR_SENSOR_API_H_

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

#include "bsp_api.h"
#include "rm_comms_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/** Event in the callback function */
typedef enum e_rm_air_sensor_event
{
    RM_AIR_SENSOR_EVENT_SUCCESS = 0,              ///< The operation completed successfully.
    RM_AIR_SENSOR_EVENT_MEASUREMENT_COMPLETE,     ///< Sensor data is ready.
    RM_AIR_SENSOR_EVENT_MEASUREMENT_NOT_COMPLETE, ///< Sensor measurement is in progress.
    RM_AIR_SENSOR_EVENT_ERROR,                    ///< A communication error has occurred.
    RM_AIR_SENSOR_EVENT_NOT_MEASURABLE,           ///< Dust concentration is extremely high or has accumulated inside the sensor.
    RM_AIR_SENSOR_EVENT_FAN_SPEED_OUT_OF_RANGE,   ///< Fan speed is out of the set range.
    RM_AIR_SENSOR_EVENT_FAN_BROKEN,               ///< Fan malfunctioned or broken down.
    RM_AIR_SENSOR_EVENT_CHECKSUM_ERROR,           ///< Checksum error occurs.
} rm_air_sensor_event_t;

/** Sign of sensor data */
typedef enum e_rm_air_sensor_sign
{
    RM_AIR_SENSOR_SIGN_MINUS = -1,     ///< Minus sign
    RM_AIR_SENSOR_SIGN_PLUS  = 1,      ///< Plus sign
} rm_air_sensor_sign_t;

/** AIR SENSOR API callback parameter definition */
typedef struct st_rm_air_sensor_callback_args
{
    void                * p_context;
    rm_air_sensor_event_t event;       ///< Event that triggered the callback.
} rm_air_sensor_callback_args_t;

/** AIR SENSOR raw data structure */
typedef struct st_rm_air_sensor_raw_data
{
    uint8_t results[37];               ///< Raw sensor data array
} rm_air_sensor_raw_data_t;

/** AIR SENSOR version structure */
typedef struct st_rm_air_sensor_version
{
    uint8_t major;                     ///< Firmware major version
    uint8_t minor;                     ///< Firmware minor version
    uint8_t patch;                     ///< Firmware patch version
    uint8_t ascii_code[11];            ///< ASCII code of firmware version
} rm_air_sensor_version_t;

/** AIR SENSOR sensor data block */
typedef struct st_rm_air_sensor_single_data
{
    rm_air_sensor_sign_t sign;         ///< Sign of sensor data.
    uint32_t             integer_part; ///< Integer part of sensor data.
    uint32_t             decimal_part; ///< Decimal part of sensor data.
} rm_air_sensor_single_data_t;

/** AIR SENSOR data block */
typedef struct st_rm_air_sensor_data
{
    uint32_t status;
    rm_air_sensor_single_data_t nc_0p3;      ///< Number concentration of particle size 0.3 um - 10 um [1/cm3]
    rm_air_sensor_single_data_t nc_0p5;      ///< Number concentration of particle size 0.5 um - 10 um [1/cm3]
    rm_air_sensor_single_data_t nc_1;        ///< Number concentration of particle size 1 um - 10 um [1/cm3]
    rm_air_sensor_single_data_t nc_2p5;      ///< Number concentration of particle size 2.5 um - 10 um [1/cm3]
    rm_air_sensor_single_data_t nc_4;        ///< Number concentration of particle size 4 um - 10 um [1/cm3]
    rm_air_sensor_single_data_t pm1_1;       ///< Mass concentration of particle size 0.3 um - 1 um with reference to KCl particle [um/cm3]
    rm_air_sensor_single_data_t pm2p5_1;     ///< Mass concentration of particle size 0.3 um - 2.5 um with reference to KCl particle [um/cm3]
    rm_air_sensor_single_data_t pm10_1;      ///< Mass concentration of particle size 0.3 um - 10 um with reference to KCl particle [um/cm3]
    rm_air_sensor_single_data_t pm1_2;       ///< Mass concentration of particle size 0.3 um - 1 um with reference to cigarette smoke [um/cm3]
    rm_air_sensor_single_data_t pm2p5_2;     ///< Mass concentration of particle size 0.3 um - 2.5 um with reference to cigarette smoke [um/cm3]
    rm_air_sensor_single_data_t pm10_2;      ///< Mass concentration of particle size 0.3 um - 10 um with reference to cigarette smoke [um/cm3]
    rm_air_sensor_single_data_t temperature; ///< Temperature [Celsius]
    rm_air_sensor_single_data_t humidity;    ///< Humidity [%RH]
    rm_air_sensor_single_data_t tvoc;        ///< Total volatile organic compounds (TVOC) concentrations [mg/m3]
    rm_air_sensor_single_data_t eco2;        ///< Carbon dioxide (CO2) level [ppm]. Value is estimated/actual value depends on sensor module.
    rm_air_sensor_single_data_t iaq;         ///< Indoor Air Quality level according to UBA
    rm_air_sensor_single_data_t rel_iaq;     ///< Relative IAQ
} rm_air_sensor_data_t;

/** AIR SENSOR configuration block */
typedef struct st_rm_air_sensor_cfg
{
    rm_comms_instance_t const * p_comms_instance;                      ///< Pointer to Communications Middleware instance.
    void       * p_context;                                            ///< Pointer to the user-provided context.
    void const * p_extend;                                             ///< Pointer to extended configuration by instance of interface.
    void (* p_comms_callback)(rm_air_sensor_callback_args_t * p_args); ///< Communications callback
} rm_air_sensor_cfg_t;

/** AIR SENSOR Control block. Allocate an instance specific control block to pass into the API calls. */
typedef void rm_air_sensor_ctrl_t;

/** AIR SENSOR APIs */
typedef struct st_rm_air_sensor_api
{
    /** Open sensor.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_air_sensor_ctrl_t * const p_ctrl, rm_air_sensor_cfg_t const * const p_cfg);

    /** Read status of the sensor
     *
     * @param[in]  p_ctrl                 Pointer to control structure.
     */
    fsp_err_t (* statusCheck)(rm_air_sensor_ctrl_t * const p_ctrl);

    /** Read ADC data.
     *
     * @param[in]   p_ctrl                 Pointer to control structure.
     * @param[out]  p_raw_data             Pointer to raw data structure.
     */
    fsp_err_t (* read)(rm_air_sensor_ctrl_t * const p_ctrl, rm_air_sensor_raw_data_t * const p_raw_data);

    /** Calculate values from measurement results.
     *
     * @param[in]   p_ctrl               Pointer to control structure.
     * @param[in]   p_raw_data           Pointer to raw data.
     * @param[out]  p_sensor_data        Pointer to SENSOR data structure.
     */
    fsp_err_t (* dataCalculate)(rm_air_sensor_ctrl_t * const p_ctrl, const rm_air_sensor_raw_data_t * const p_raw_data,
                                rm_air_sensor_data_t * const p_sensor_data);

    /** Read firmware version.
     *
     * @param[in]   p_ctrl                 Pointer to control structure.
     * @param[out]  p_version              Pointer to firmware version structure.
     */
    fsp_err_t (* firmwareVersionGet)(rm_air_sensor_ctrl_t * const p_ctrl, rm_air_sensor_version_t * const p_version);

    /** Read algorithm version.
     *
     * @param[in]   p_ctrl                 Pointer to control structure.
     * @param[out]  p_version              Pointer to algorithm version structure.
     */
    fsp_err_t (* algorithmVersionGet)(rm_air_sensor_ctrl_t * const p_ctrl, rm_air_sensor_version_t * const p_version);

    /** Close the sensor
     *
     * @param[in]  p_ctrl               Pointer to control structure.
     */
    fsp_err_t (* close)(rm_air_sensor_ctrl_t * const p_ctrl);
} rm_air_sensor_api_t;

/** AIR SENSOR instance */
typedef struct st_rm_air_sensor_instance
{
    rm_air_sensor_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    rm_air_sensor_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    rm_air_sensor_api_t const * p_api;  ///< Pointer to the API structure for this instance
} rm_air_sensor_instance_t;

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER

#endif                                 /* RM_AIR_SENSOR_API_H_*/

/******************************************************************************************************************//**
 * @} (end defgroup RM_AIR_SENSOR_API)
 *********************************************************************************************************************/
