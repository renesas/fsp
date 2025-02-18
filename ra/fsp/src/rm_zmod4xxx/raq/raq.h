/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 * @file    raq.h
 * @author Renesas Electronics Corporation
 * @version 2.0.0
 * @brief   This file contains definitions for the data structure and the RAQ
 *          algorithm function definition.
 * @details This file contains the function definitions for the RAQ algorithm.
 */

#ifndef RAQ
 #define RAQ

 #include <math.h>
 #include <stdint.h>
 #if 0                                 // For multiple operations
  #include "zmod4xxx_types.h"

/**
 * @brief Variables that describe the library version
 */
typedef struct
{
    uint8_t major;
    uint8_t minor;
    uint8_t patch;
} algorithm_version;
 #else
  #include "../zmod4xxx_types.h"
 #endif

 #ifdef __cplusplus
extern "C" {
 #endif

/** \addtogroup RetCodes Return codes of the algorithm functions.
 * @{
 */

 #define ZMOD4450_OK             (0)   /**< Sensor stabilized. */
 #define ZMOD4450_STABILIZING    (9)   /**< Sensor not stabilized. */
/** @} */

/**
 * @brief Parameters to control the RAQ.
 */
typedef struct
{
    float    alpha;                    /**< Slope parameter for RAQ. */
    uint32_t stop_delay;               /**< Control signal follow-up time. */
    float    threshold;                /**< Threshold to switch, i.e. 1.3 - corresponds to 30 %
                                        *        rise in concentration. */
    uint32_t tau;                      /**< Time constant for averaging. */
    uint32_t stabilization_samples;    /**< Ignore number of samples for sensor
                                        * stabilization. */
} raq_params_t;

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
 * @brief RAQ results.
 */
typedef struct
{
    control_signal_state_t cs_state;   /**< Control signal input. */
    float conc_ratio;                  /**< Concentration ratio. */
} raq_results_t;

/**
 * @brief   Calculates RAQ from r_mox and raq parameters.
 * @param   [in] r_mox MOx resistance.
 * @param   [in] params RAQ parameters.
 * @param   [in,out] results RAQ results.
 * @return  Status of the sensor.
 * @retval  0 Sensor stabilized.
 * @retval  9 Sensor not stabilized.
 */
int8_t calc_raq(float r_mox, const raq_params_t * params, raq_results_t * results);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* RAQ */
