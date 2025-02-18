/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
  * @file    ulp_o3.h
  * @author  Renesas Electronics Corporation
  * @version 5.0.0
  * @brief   This file contains the data structure definitions and
  *          the function definitions for the ULP O3 algorithm.
  * @details The library contains an algorithm to calculate an ozone
  *          concentration and various air quality index values
  *          from the ZMOD4510 measurements.
  */

#ifndef ULP_O3_H_
#define ULP_O3_H_

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
 *  @{
 */
#define ULP_O3_OK            (0) /**< everything okay */
#define ULP_O3_STABILIZATION (1) /**< sensor in stabilization */
#define ULP_O3_DAMAGE        (-102) /**< sensor damaged */
/** @}*/

/**
* @brief Variables that describe the sensor or the algorithm state.
*/
// clang-format off
typedef struct {
    uint32_t sample_cnt; /**< Sample counter. Will satturate at 0xFFFFFFFF. */
    float smooth_rmox;
    float gcda;          /**< baseline conductance. */
    float o3_conc_ppb;
    float o3_1h_ppb;
    float o3_8h_ppb;
} ulp_o3_handle_t;
// clang-format on

/**
* @brief Variables that receive the algorithm outputs.
*/
// clang-format off
typedef struct {
    float     rmox[8];     /**< MOx resistance. */
    float     temperature; /**< Temperature (degC) used for ambient compensation */
    float     O3_conc_ppb; /**< O3_conc_ppb stands for the ozone concentration
                                in part-per-billion */
    uint16_t  FAST_AQI;    /**< FAST_AQI stands for a 1-minute average of the
                                Air Quality Index according to the EPA
                                standard based on ozone */
    uint16_t  EPA_AQI;     /**< EPA_AQI stands for the Air Quality Index
                                according to the EPA standard based on ozone.*/
} ulp_o3_results_t;
// clang-format on

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
} ulp_o3_inputs_t;

/**
 * @brief   Initializes the ULP O3 algorithm.
 * @param   [out] handle Pointer to algorithm state variable.
 * @return  error code.
*/
int8_t init_ulp_o3(ulp_o3_handle_t *handle);

/**
 * @brief   calculates results from present sample.
 * @param   [in] handle Pointer to algorithm state variable.
 * @param   [in] dev Pointer to the device.
 * @param   [in] algo_input Structure containing inputs required for algo calculation.
 * @param   [out] results Pointer for storing the algorithm results.
 * @return  error code.
 */
int8_t calc_ulp_o3(ulp_o3_handle_t *handle, zmod4xxx_dev_t *dev,
                   const ulp_o3_inputs_t *algo_input,
                   ulp_o3_results_t *results);

#ifdef __cplusplus
}
#endif

#endif /* ULP_O3_H_ */
