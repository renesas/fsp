/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 * @file    oaq_1st_gen.h
 * @author  Renesas Electronics Corporation
 * @version 3.0.0
 * @brief   This file contains the data structure definitions and
 *          the function definitions for the OAQ 1st Gen base algorithm.
 * @details The library contains an algorithm to calculate an OAQ index from
 *          ZMOD4510 measurements.
 */

#ifndef OAQ_1ST_GEN_H_
 #define OAQ_1ST_GEN_H_

 #ifdef __cplusplus
extern "C" {
 #endif

 #include <stdint.h>
 #include <math.h>
 #include "../zmod4xxx_types.h"

/**
 * @brief Handles of the Rcda.
 */

 #define RCDA_STRATEGY_FIX    (0)      /*!< Hold rcda fixed. */
 #define RCDA_STRATEGY_SET    (1)      /*!< Set the rcda to the actal measurement. */
 #define RCDA_STRATEGY_ADJ    (2)      /*!< Adjust rcda to follow slow drifts. */

/**
 * @brief Discriminations of the gases.
 */
 #define GAS_DETECTION_STRATEGY_AUTO \
    (0)                                /*!< Use automatic gas discrimination. */
 #define GAS_DETECTION_STRATEGY_FORCEO3 \
    (1)                                /*!< Handle the measurements as O3. */
 #define GAS_DETECTION_STRATEGY_FORCENO2 \
    (2)                                /*!< Handle the measurements as NO2. */

/**
 * @brief Internal precision for gas classification, must be at least 32bit floating point.
 */
typedef float oaq_prec_t;

/**
 * @brief Variables that describe the sensor or the algorithm state.
 */
typedef struct
{
    float   trim_beta2;                /**< Slope from trim data. */
    float   trim_b;                    /**< NO2 intercept from trim data. */
    float   rcda_22;                   /**< Rcda estimation for Rmox_22. */
    float   rcda_42;                   /**< Rcda estimation for Rmox_42. */
    uint8_t trim_data_version;         /**< Version of trim data in NVM. */
    uint8_t
          stabilization_sample;        /**< Number of samples still needed for stabilization. */
    float prob_no2;                    /**< NO2 probability. */
    float conc_no2;                    /**< Equivalent to NO2 concentration [ppb]. */
    float conc_o3;                     /**< Equivalent to O3 concentration [ppb]. */
    float aqi_no2;                     /**< Equivalent to NO2 AQI. */
    float aqi_o3;                      /**< Equivalent to O3 AQI. */
} oaq_base_handle_t;

/**
 * @brief   Initializes the OAQ 1st Gen algorithm.
 * @param   [out] handle Pointer to algorithm state variable.
 * @param   [in] general_purpose Pointer to the 9 bytes trim information.
 * @param   [in] stabilization_samples Number of samples to be ignored for stabilization.
 */
void init_oaq_1st_gen(oaq_base_handle_t * handle, const uint8_t * general_purpose, const uint8_t stabilization_samples);

/**
 * @brief   calculates AQI from present sample.
 * @param   [in] handle Pointer to algorithm state variable.
 * @param   [in] rmox Pointer to array of the 15 sequencer rmox measurements.
 * @param   [in] rcda_strategy Handling Rcda.
 * @param   [in] gas_detection_strategy Doing automatic gas discrimination or forcing O3 or NO2.
 * @param   [in] d_rising_m1 Rcda damping factor for rising rmox.
 * @param   [in] d_falling_m1 Rcda damping factor for falling rmox.
 * @param   [in] d_class_m1 Damping factor for gas classification.
 * @return  AQI value.
 */
float calc_oaq_1st_gen(oaq_base_handle_t * handle,
                       const float       * rmox,
                       const uint8_t       rcda_strategy,
                       const uint8_t       gas_detection_strategy,
                       const float         d_rising_m1,
                       const float         d_falling_m1,
                       const float         d_class_m1);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* OAQ_1ST_GEN_H_ */
