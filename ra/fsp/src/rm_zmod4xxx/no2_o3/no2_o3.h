/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 * @addtogroup <ALGO_SHORT>_api
 * @{
 * @file    no2_o3.h
 * @author  Renesas Electronics Corporation
 * @version 1.0.1
 * @brief   This file contains the data structure definitions and
 *          the function definitions for the NO2 O3 algorithm.
 * @details The library contains an algorithm to calculate ozone and
 *          nitrogen dioxide concentrations and various air quality index
 *          values from the ZMOD4510 measurements.
 */

#ifndef NO2_O3_H_
#define NO2_O3_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <math.h>

#if TEST_RM_ZMOD4XXX  // For RA FSP test
 #include "../../../../../fsp/src/rm_zmod4xxx/zmod4xxx_types.h"
#else
 #include "../zmod4xxx_types.h"
#endif

/** \addtogroup RetCodes Return codes of the algorithm functions.
 * \ingroup <ALGO_SHORT>_api
 *  @{
 */
#define NO2_O3_OK            (0) /**< everything okay */
#define NO2_O3_STABILIZATION (1) /**< sensor in stabilization */
#define NO2_O3_DAMAGE        (-102) /**< sensor damaged */
/** @}*/

/**
* @brief Variables that describe the sensor or the algorithm state.
*/
typedef struct {
    uint32_t sample_counter; /**< Sample counter. Will saturate at 0xFFFFFFFF. */
    float rmoxs_smooth[4];
    float logrmoxs_mean[4];
    float logrmoxs_var[4];
    float o3_1min_ppb;
    float o3_1h_ppb;
    float o3_8h_ppb;
    float no2_1min_ppb;
    float no2_1h_ppb;
} no2_o3_handle_t;

/**
* @brief Variables that receive the algorithm outputs.
*/
typedef struct {
    float rmox[4]; /**< MOx resistance. */
    float temperature; /**< Temperature (degC) used for ambient compensation */
    float O3_conc_ppb; /**< O3_conc_ppb stands for the ozone concentration in part-per-billion */
    float NO2_conc_ppb; /**< NO2_conc_ppb stands for the NO2 concentration in part-per-billion */
    uint16_t
        FAST_AQI; /**< FAST_AQI stands for a 1-minute average of the Air Quality Index according to the EPA standard based on ozone */
    uint16_t
        EPA_AQI; /**< EPA_AQI stands for the Air Quality Index according to the EPA standard based on ozone. */
} no2_o3_results_t;

/**
* @brief Variables that are needed for algorithm
 * @param   [in] adc_result Value from read_adc_result function
 * @param   [in] humidity_pct relative ambient humidity (%)
 * @param   [in] temperature_degc ambient temperature (degC)
*/
typedef struct {
    uint8_t *adc_result;
    float humidity_pct;
    float temperature_degc;
} no2_o3_inputs_t;

/**
 * @brief   Initializes the NO2 O3 algorithm.
 * @param   [out] handle Pointer to algorithm state variable.
 * @return  error code.
*/
int8_t init_no2_o3(no2_o3_handle_t *handle);

/**
 * @brief   calculates NO2 O3 results from present sample.
 * @param   [in] handle Pointer to algorithm state variable.
 * @param   [in] dev Pointer to the device.
 * @param   [in] algo_input Structure containing inputs required for algo calculation.
 * @param   [out] results Pointer for storing the algorithm results.
 * @return  error code.
 */
int8_t calc_no2_o3(no2_o3_handle_t *handle, const zmod4xxx_dev_t *dev,
                   const no2_o3_inputs_t *algo_input,
                   no2_o3_results_t *results);

#ifdef __cplusplus
}
#endif

#endif /* NO2_O3_H_ */
/** @} */
