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
 * @file    iaq_2nd_gen_ulp.h
 * @author Renesas Electronics Corporation
 * @version 1.0.0
 * @brief   This file contains the data structure definitions and
 *          the function definitions for the 2nd Gen IAQ ULP algorithm.
 * @details The library contains an algorithm to calculate an eCO2, EtOH, TVOC and
 *          IAQ index from ZMOD4410 measurements.
 *          The implementation is made to allow more than one sensor.
 *
 */

#ifndef IAQ_2ND_GEN_ULP_H_
 #define IAQ_2ND_GEN_ULP_H_

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
 #define IAQ_2ND_GEN_ULP_OK               (0) /**< everything okay */
 #define IAQ_2ND_GEN_ULP_STABILIZATION    (1) /**< sensor in stabilization */
/** @}*/

/**
 * @brief   The algorithm handle contains variables that describe the sensor
 *          or the algorithm state. It needs to be passed with between
 *          initialization and after each algorithm calculation.
 */
typedef struct
{
    float log_nonlog_rcda[3];          /**< various baselines. */
    uint8_t
            stabilization_sample;      /**< Number of remaining stabilization samples. */
    uint8_t need_filter_init;
    float   tvoc_smooth;
    float   tvoc_deltafilter;
    float   acchw;
    float   accow;
    float   etoh;
    float   eco2;
} iaq_2nd_gen_ulp_handle_t;

/**
 * @brief Variables that receive the algorithm outputs.
 */
typedef struct
{
    float rmox[13];                    /**< MOx resistance. */
    float log_nonlog_rcda[3];          /**< various baselines. */
    float iaq;                         /**< IAQ index. */
    float tvoc;                        /**< TVOC concentration (mg/m^3). */
    float etoh;                        /**< EtOH concentration (ppm). */
    float eco2;                        /**< eCO2 concentration (ppm). */
} iaq_2nd_gen_ulp_results_t;

/**
 * @brief  Algorithm input structure
 */
typedef struct
{
    uint8_t * adc_result;              /**< Sensor raw values. */
    float     humidity_pct;            /**< Relative Humditiy in percentage */
    float     temperature_degc;        /**< Ambient Temperature in C */
} iaq_2nd_gen_ulp_inputs_t;

/**
 * @brief   calculates IAQ results from present sample.
 * @param   [in] handle Pointer to algorithm state variable.
 * @param   [in] dev Pointer to the device.
 * @param   [in] algo_input Structure containing inputs required for algo calculation.
 * @param   [out] results Pointer for storing the algorithm results.
 * @return  error code.
 */
int8_t calc_iaq_2nd_gen_ulp(iaq_2nd_gen_ulp_handle_t       * handle,
                            zmod4xxx_dev_t                 * dev,
                            const iaq_2nd_gen_ulp_inputs_t * algo_input,
                            iaq_2nd_gen_ulp_results_t      * results);

/**
 * @brief   Initializes the IAQ algorithm.
 * @param   [out] handle Pointer to algorithm state variable.
 * @return  error code.
 */
int8_t init_iaq_2nd_gen_ulp(iaq_2nd_gen_ulp_handle_t * handle);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* IAQ_2ND_GEN_ULP_H_ */
