/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 * file    :comp.h
 * author  :Renesas Electronics Corporation
 * version :1.0.0
 * brief   :This file contains the data structure definitions and
 *          the function definitions for the compensation.
 */

#ifndef COMP_H_
 #define COMP_H_

 #ifdef __cplusplus
extern "C" {
 #endif

 #include <stdint.h>
 #include <math.h>
 #include "../zmod4xxx_types.h"

/**
 * @brief Variables that describe the sensor or the algorithm state.
 */
typedef struct
{
    uint32_t sample_counter;           /**< Sample counter. Will saturate at 0xFFFFFFFF. */
    float    rmoxs_smooth[4];
    float    logrmoxs_mean[4];
    float    logrmoxs_var[4];
    float    o3_1min_ppb;
    float    o3_1h_ppb;
    float    o3_8h_ppb;
    float    no2_1min_ppb;
    float    no2_1h_ppb;
} comp_handle_t;

/**
 * @brief Variables that receive the algorithm outputs.
 */
typedef struct
{
    float    rmox[4];                  /**< MOx resistance. */
    float    temperature;              /**< Temperature (degC) used for ambient compensation. */
    float    O3_conc_ppb;              /**< O3_conc_ppb stands for the ozone concentration in part-per-billion. */
    float    NO2_conc_ppb;             /**< NO2_conc_ppb stands for the NO2 concentration in part-per-billion. */
    uint16_t FAST_AQI;                 /**< FAST_AQI stands for a 1-minute average of the Air Quality Index according to the EPA standard based on ozone. */
    uint16_t EPA_AQI;                  /**< EPA_AQI stands for the Air Quality Index according to the EPA standard based on ozone. */
} comp_results_t;

 #ifdef __cplusplus
}
 #endif

#endif                                 /* COMP_H_ */
