/**
  * @file    pbaq.h
  * @author  Renesas Electronics Corporation
  * @version 1.0.0
  * @brief   This file contains the data structure definitions and
  *          the function definitions for the PBAQ algorithm.
  * @details The library contains an algorithm to calculate an EtOH, TVOC 
  *          from ZMOD4410 measurements.
  *          The implementation is made to allow more than one sensor.
  *
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

/** \addtogroup RetCodes Return codes of the algorithm functions.
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
    float log_rcda[9]; /**< log10 of CDA resistances. */
    float rh_cda;
    float t_cda;
    uint32_t sample_counter;
    float etoh;
} pbaq_handle_t;

/**
* @brief Variables that receive the algorithm outputs.
*/
typedef struct {
    float rmox[13]; /**< MOx resistance. */
    float log_rcda; /**< log10 of CDA resistance. */
    float rhtr; /**< heater resistance. */
    float temperature; /**< ambient temperature (degC). */
    float tvoc; /**< TVOC concentration (mg/m^3). */
    float etoh; /**< EtOH concentration (ppm). */
} pbaq_results_t;

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
} pbaq_inputs_t;

/**
 * @brief   calculates algorithm results from present sample.
 * @param   [in] handle Pointer to algorithm state variable.
 * @param   [in] dev Pointer to the device.
 * @param   [in] algo_input Structure containing inputs required for algo calculation.
 * @param   [out] results Pointer for storing the algorithm results.
 * @return  error code.
 */
int8_t calc_pbaq(pbaq_handle_t *handle, const zmod4xxx_dev_t *dev,
                 const pbaq_inputs_t *algo_input, pbaq_results_t *results);

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
