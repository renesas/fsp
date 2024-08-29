/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 * @file    odor.h
 * @author Renesas Electronics Corporation
 * @version 2.1.2
 * @brief   This file contains the definitions for data structure and the odor
 *          algorithm function.
 * @details This file contains the function definitions for the odor algorithm.
 */

#ifndef ODOR_H_
 #define ODOR_H_

 #include <math.h>
 #include <stdint.h>
 #include "../zmod4xxx_types.h"

 #ifdef __cplusplus
extern "C" {
 #endif

/**
 * @brief Status of the sensor.
 */

 #define ODOR_OK               (0)     /**< Everything ok. */
 #define ODOR_STABILIZATION    (1)     /**< Sensor not stabilized. */

/**
 * @brief Parameters to control the odor algorithm.
 */
typedef struct
{
    float    alpha;                    /**< Slope parameter for odor algorithm. */
    uint32_t stop_delay;               /**< Control signal follow-up time. */
    float    threshold;                /**< Threshold to switch, i.e. 1.3 - corresponds to 30 %
                                        * rise in concentration. */
    uint32_t tau;                      /**< Time constant for averaging. */
    uint32_t stabilization_samples;    /**< Ignore number of samples for sensor
                                        * stabilization. */
} odor_params;

 #ifndef CONTROL_SIGNAL_STATE          // Add to avoid build errors due to multiple definitions (Odor and RAQ)
  #define CONTROL_SIGNAL_STATE

/**
 * @brief Control signal states.
 */
typedef enum
{
    OFF = 0,
    ON  = 1,
} control_signal_state_t;
 #endif

/**
 * @brief odor results.
 */
typedef struct
{
    control_signal_state_t cs_state;   /**< Control signal input. */
    float conc_ratio;                  /**< Concentration ratio. */
} odor_results_t;

/**
 * @brief   Calculates odor from r_mox and odor parameters.
 * @param   [in] r_mox MOx resistance.
 * @param   [in] params odor algorithm parameters.
 * @param   [in,out] results odor results.
 * @return  Status of the sensor.
 * @retval  0 Sensor stabilized.
 * @retval  1 Sensor not stabilized.
 */
int8_t calc_odor(float r_mox, odor_params * params, odor_results_t * results);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* ODOR_H_ */
