/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
  * @file    rel_iaq_ulp.h
  * @author  Renesas Electronics Corporation
  * @version 1.1.0
  * @brief   This file contains the data structure definitions and
  *          the function definitions for the Relative IAQ ULP algorithm.
  * @details The library contains an algorithm to calculate a relative
  *          IAQ index from ZMOD4410 measurements.
  *          The implementation is made to allow more than one sensor.
  *
  */

#ifndef REL_IAQ_ULP_H_
#define REL_IAQ_ULP_H_

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
#define REL_IAQ_ULP_OK            (0) /**< everything okay */
#define REL_IAQ_ULP_STABILIZATION (1) /**< sensor in stabilization */
#define REL_IAQ_ULP_DAMAGE        (-102) /**< sensor damaged */
/** @}*/

/**
* @brief Variables that describe the sensor or the algorithm state.
*/
typedef struct {
    uint32_t sample_counter;
    float rg_mean;
    float rel_iaq_raw;
    float log10_rel_iaq_smooth;
    float var_log10_rel_iaq;
    float dev_log10_rel_iaq_target;
} rel_iaq_ulp_handle_t;

/**
* @brief Variables that receive the algorithm outputs.
*/
typedef struct {
    float rmox[13]; /**< MOx resistances. */
    float rhtr; /**< heater resistance. */
    float rel_iaq; /**< relative IAQ index. */
} rel_iaq_ulp_results_t;

/**
* @brief Algorithm input structure
* @param   [in] adc_result Array of 32 bytes with the values from the sensor results table.
*/
typedef struct {
    uint8_t *adc_result; /** Sensor raw values. **/
} rel_iaq_ulp_inputs_t;

/**
 * @brief   calculates algorithm results from present sample.
 * @param   [in] handle Pointer to algorithm state variable.
 * @param   [in] dev Pointer to the device.
 * @param   [in] algo_input Structure containing inputs required for algo calculation.
 * @param   [out] results Pointer for storing the algorithm results.
 * @return  error code.
 */
int8_t calc_rel_iaq_ulp(rel_iaq_ulp_handle_t *handle, const zmod4xxx_dev_t *dev,
                        const rel_iaq_ulp_inputs_t *algo_input,
                        rel_iaq_ulp_results_t *results);

/**
 * @brief   Initializes the algorithm.
 * @param   [out] handle Pointer to algorithm state variable.
 * @return  error code.
*/
int8_t init_rel_iaq_ulp(rel_iaq_ulp_handle_t *handle);

#ifdef __cplusplus
}
#endif

#endif /* REL_IAQ_ULP_H_ */
