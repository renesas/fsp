/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
  * @addtogroup <ALGO_SHORT>_api
  * @{
  * @file    pbaq.h
  * @author  Renesas Electronics Corporation
  * @version 2.1.0
  * @brief   This file contains the data structure definitions and
  *          the function definitions for the PBAQ algorithm.
  * @details The library contains an algorithm to calculate an EtOH, TVOC, IAQ
  *          and Rel IAQ index from ZMOD4410 measurements.
  */

  #ifndef PBAQ_H_
  #define PBAQ_H_
  
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
  
  /** @addtogroup RetCodes Return codes of the algorithm functions.
   *  @ingroup <ALGO_SHORT>_api
   *  @{
   */
  #define PBAQ_OK            (0) /**< everything okay */
  #define PBAQ_STABILIZATION (1) /**< sensor in stabilization */
  #define PBAQ_DAMAGE        (-102) /**< sensor damaged */
  /** @}*/
  
  /**
   * @brief Variables that describe the sensor or the algorithm state.
   */
  
  typedef struct {
      float log_rmox_nonlog_rh_t_filtered[12];
      float log_nonlog_rcda[12];
      uint32_t sample_counter;
      float etoh;
      float iaq;
      float o3;
      float rg_mean;
      float rel_iaq_raw;
      float log10_rel_iaq_smooth;
      float var_log10_rel_iaq;
      float dev_log10_rel_iaq_target;
  } pbaq_handle_t;
  
  /**
   * @brief Variables that receive the algorithm outputs.
   */
  typedef struct {
      float rmox[13]; /**< MOx resistance. */
      float zmod4510_rmox3; /**< MOx resistance of ZMOD4510. */
      float log_rcda; /**< log10 of CDA resistance. */
      float rhtr; /**< heater resistance. */
      float temperature; /**< Input or module temperature (degC). */
      float iaq; /**< IAQ index. */
      float tvoc; /**< TVOC concentration (mg/m^3). */
      float etoh; /**< EtOH concentration (ppm). */
      float rel_iaq; /**< relative IAQ index. */
  } pbaq_results_t;
  
  /**
   * @brief Variables that are needed for algorithm
   * @param   [in] adc_result Value from read_adc_result function
   * @param   [in] adc_rmox3_4510 Value from read_adc_result function
   * @param   [in] humidity_pct relative ambient humidity (%)
   * @param   [in] temperature_degc ambient temperature (degC)
   */
  typedef struct {
      uint8_t *adc_result;
      uint8_t *adc_rmox3_4510;
      float humidity_pct;
      float temperature_degc;
  } pbaq_inputs_t;
  
  /**
   * @brief   calculates algorithm results from present sample.
   * @param   [in] handle Pointer to algorithm state variable.
   * @param   [in] dev Pointer to the ZMOD4410 device.
   * @param   [in] dev4510 Pointer to the ZMOD4510 device.
   * @param   [in] algo_input Structure containing inputs required for algo calculation.
   * @param   [out] results Pointer for storing the algorithm results.
   * @return  error code.
   */
  int8_t calc_pbaq(pbaq_handle_t *handle, const zmod4xxx_dev_t *dev,
                   const zmod4xxx_dev_t *dev4510, const pbaq_inputs_t *algo_input,
                   pbaq_results_t *results);
  
  /**
   * @brief   Initializes the algorithm.
   * @param   [out] handle Pointer to algorithm state variable.
   * @return  error code.
   */
  int8_t init_pbaq(pbaq_handle_t *handle);
  
  #ifdef __cplusplus
  }
  #endif
  
  #endif /* PBAQ_H_ */
  
  /** @} */