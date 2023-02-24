/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/**
 * @file    oaq_2nd_gen.h
 * @author Renesas Electronics Corporation
 * @version 4.0.0
 * @brief   This file contains the data structure definitions and
 *          the function definitions for the 2nd generation OAQ algorithm.
 * @details The library contains an algorithm to calculate an ozone
 *          concentration and various air quality index values
 *          from the ZMOD4510 measurements.
 */

#ifndef OAQ_2ND_GEN_H_
 #define OAQ_2ND_GEN_H_

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
 #define OAQ_2ND_GEN_OK               (0) /**< everything okay */
 #define OAQ_2ND_GEN_STABILIZATION    (1) /**< sensor in stabilization */
/** @}*/

/**
 * @brief Variables that describe the sensor or the algorithm state.
 */
typedef struct
{
    uint32_t sample_cnt;               /**< Sample counter. Will satturate at 0xFFFFFFFF. */
    float    smooth_rmox;
    float    gcda;                     /**< baseline conductance. */
    float    o3_conc_ppb;
    float    o3_1h_ppb;
    float    o3_8h_ppb;
} oaq_2nd_gen_handle_t;

/**
 * @brief Variables that receive the algorithm outputs.
 */
typedef struct
{
    float rmox[8];                     /**< MOx resistance. */
    float O3_conc_ppb;                 /**< O3_conc_ppb stands for the ozone concentration in part-per-billion */
    uint16_t
        FAST_AQI;                      /**< FAST_AQI stands for a 1-minute average of the Air Quality Index according to the EPA standard based on ozone */
    uint16_t
        EPA_AQI;                       /**< EPA_AQI stands for the Air Quality Index according to the EPA standard based on ozone. */
} oaq_2nd_gen_results_t;

/**
 * @brief Variables that are needed for algorithm
 * @param   [in] adc_result Value from read_adc_result function
 * @param   [in] humidity_pct relative ambient humidity (%)
 * @param   [in] temperature_degc ambient temperature (degC)
 */
typedef struct
{
    uint8_t * adc_result;
    float     humidity_pct;
    float     temperature_degc;
} oaq_2nd_gen_inputs_t;

/**
 * @brief   Initializes the OAQ algorithm.
 * @param   [out] handle Pointer to algorithm state variable.
 * @return  error code.
 */
int8_t init_oaq_2nd_gen(oaq_2nd_gen_handle_t * handle);

/**
 * @brief   calculates OAQ results from present sample.
 * @param   [in] handle Pointer to algorithm state variable.
 * @param   [in] dev Pointer to the device.
 * @param   [in] algo_input Structure containing inputs required for algo calculation.
 * @param   [out] results Pointer for storing the algorithm results.
 * @return  error code.
 */
int8_t calc_oaq_2nd_gen(oaq_2nd_gen_handle_t       * handle,
                        zmod4xxx_dev_t             * dev,
                        const oaq_2nd_gen_inputs_t * algo_input,
                        oaq_2nd_gen_results_t      * results);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* OAQ_2ND_GEN_H_ */
