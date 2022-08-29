/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @file    iaq_1st_gen.h
 * @author  Renesas Electronics Corporation
 * @version 2.1.2
 * @brief   This file contains the data structure definitions and
 *          the function definitions for the 1st generation IAQ algorithm.
 * @details The library contains an algorithm to calculate IAQ, TVOC, eCO2
 *          and EtOH from ZMOD4410 measurements.
 *          The implementation is made to allow more than one sensor.
 *
 */

#ifndef IAQ_1ST_GEN_H_
 #define IAQ_1ST_GEN_H_

 #ifdef __cplusplus
extern "C" {
 #endif

 #include <stdint.h>
 #include <math.h>
 #include "../zmod4xxx_types.h"

/**
 * @brief Return codes of the algorithm functions.
 */
 #define IAQ_1ST_GEN_OK               (0)   /**< everything okay */
 #define IAQ_1ST_GEN_STABILIZATION    (1)   /**< sensor in stabilization */
 #define IAQ_1ST_GEN_WRONG_DEVICE     (-32) /**< wrong sensor type */
 #define IAQ_1ST_GEN_NOT_TRIMMED      (-33) /**< missing device trimming */

/**
 * @brief Variables that describe the sensor and the algorithm state.
 * @note  For internal use only! Do not change values here!
 */
typedef struct
{
    float    sample_period;
    float    eco2_filter_coeff_bm1;
    float    sd_d1m_hp;
    uint16_t sd_relaxationtimer;
    float    sd_lp_state;
    float    rcda;
    uint8_t  sample_number;
    float    prev_conc_tvoc_filt[4];
    float    non_corr_con_tvoc;
    float    one_by_alpha;
    float    a_10ppm;
    float    etoh;
    float    tvoc;
    float    eco2;
    float    iaq;
} iaq_1st_gen_handle_t;

/**
 * @brief Variables that receive the algorithm outputs.
 */
typedef struct
{
    float rmox;                        /**< MOx resistance. */
    float rcda;                        /**< CDA resistance. */
    float iaq;                         /**< IAQ index. */
    float tvoc;                        /**< TVOC concentration (mg/m^3). */
    float etoh;                        /**< EtOH concentration (ppm). */
    float eco2;                        /**< eCO2 concentration (ppm). */
} iaq_1st_gen_results_t;

/**
 * @brief   Initializes the IAQ algorithm.
 * @param   [in] handle Pointer to algorithm state variable.
 * @param   [in] dev Pointer to the device.
 * @param   [in]  sample_period Time between samples.
 * @return  error code.
 */
int8_t init_iaq_1st_gen(iaq_1st_gen_handle_t * handle, zmod4xxx_dev_t * dev, const float sample_period);

/**
 * @brief   calculates IAQ results from present sample.
 * @param   [in] handle Pointer to algorithm state variable.
 * @param   [in] dev Pointer to the device.
 * @param   [in] sensor_results Array of 2 bytes with the values from the sensor results table. See example code for the right table entry.
 * @param   [out] results Pointer to store the algorithm results.
 * @return  error code.
 */
int8_t calc_iaq_1st_gen(iaq_1st_gen_handle_t  * handle,
                        zmod4xxx_dev_t        * dev,
                        const uint8_t         * sensor_results,
                        iaq_1st_gen_results_t * results);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* IAQ_1ST_GEN_H_ */
