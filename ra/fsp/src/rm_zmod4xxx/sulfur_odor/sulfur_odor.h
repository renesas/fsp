/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 * @file    sulfur_odor.h
 * @author Renesas Electronics Corporation
 * @version 2.1.2
 * @brief   This file contains the data structure definitions and
 *          the function definitions for the sulfor odor algorithm.
 * @details The library contains an algorithm to calculate and rate a
 *          sulfur odor.
 *          The implementation is made to allow more than one sensor.
 *
 */

#ifndef SULFUR_ODOR_H_
 #define SULFUR_ODOR_H_

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

/**
 * \defgroup sulfur_odor_ret Return codes of the sulfur odor algorithm functions
 * @{
 */
 #define SULFUR_ODOR_OK               (0)   /**< everything okay */
 #define SULFUR_ODOR_STABILIZATION    (1)   /**< sensor in stabilization */
 #define SULFUR_ODOR_WRONG_DEVICE     (-32) /**< wrong sensor type */
/** @} */

/**
 * @brief Number of MOX and CDA resistances to store
 */
 #define SULFUR_ODOR_N_RMOX           (9)

/**
 * @brief Odor classifications.
 */
typedef enum
{
    SULFUR_ODOR_ACCEPTABLE = 0,
    SULFUR_ODOR_SULFUR     = 1,
} sulfur_odor_classification_t;

/**
 * @brief Variables that describe the sensor or the algorithm state.
 * This is for internal use only! Do not change values here!
 */
typedef struct
{
    uint8_t stabilization_counter;
    uint8_t class_buffer;
    float   log_rcda[SULFUR_ODOR_N_RMOX];
    sulfur_odor_classification_t odor;
} sulfur_odor_handle_t;

/**
 * @brief Variables that receive the algorithm outputs.
 */
typedef struct
{
    float rmox[SULFUR_ODOR_N_RMOX];    /**< MOx resistance (ohm). */
    float intensity;                   /**< odor intensity rating ranges from 0.0 to 5.0 */
    sulfur_odor_classification_t odor; /**< odor classification */
} sulfur_odor_results_t;

/**
 * @brief Algorithm input structure
 */
typedef struct
{
    uint8_t *
        adc_result;                    /**< Pointer to array, with the values from the sensor results table */
} sulfur_odor_inputs_t;

/**
 * @brief   Initializes the algorithm.
 * @param   [out] handle Pointer to algorithm state variable.
 * @return  error code.
 */
int8_t init_sulfur_odor(sulfur_odor_handle_t * handle);

/**
 * @brief   calculates results from present sample.
 * @param   [in] handle Pointer to algorithm state variable.
 * @param   [in] dev Pointer to the device.
 * @param   [in] algo_input Structure containing inputs required for algo calculation.
 * @param   [out] results Pointer for storing the algorithm results.
 * @return  error code.
 */
int8_t calc_sulfur_odor(sulfur_odor_handle_t       * handle,
                        zmod4xxx_dev_t             * dev,
                        const sulfur_odor_inputs_t * algo_input,
                        sulfur_odor_results_t      * results);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* SULFUR_ODOR_H_ */
