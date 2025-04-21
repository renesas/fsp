/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
  * @file    iaq_2nd_gen_ulp.h
  * @author Renesas Electronics Corporation
  * @version 1.2.0
  * @brief   This file contains the data structure definitions and
  *          the function definitions for the 2nd Gen IAQ ULP algorithm.
  * @details The library contains an algorithm to calculate an eCO2, EtOH, TVOC and
  *          IAQ index from ZMOD4410 measurements.
  *          The implementation is made to allow more than one sensor.
  *
  */

  #ifndef IAQ_2ND_GEN_ULP_H_
  #define IAQ_2ND_GEN_ULP_H_
  
  #include "ulp.h"
  
  // clang-format off
  // #warning "The iaq_2nd_gen_ulp.h header is provided for backward compatibility only and will be removed in future revisions. Please use names defined in ulp.h"
  // clang-format on
  
  /* below definitions map the legacy IAQ 2nd Gen ULP to ULP names */
  #define IAQ_2ND_GEN_ULP_OK            ULP_OK
  #define IAQ_2ND_GEN_ULP_STABILIZATION ULP_STABILIZATION
  #define IAQ_2ND_GEN_ULP_DAMAGE        ULP_DAMAGE
  #define iaq_2nd_gen_ulp_handle_t      ulp_handle_t
  #define iaq_2nd_gen_ulp_results_t     ulp_results_t
  #define iaq_2nd_gen_ulp_inputs_t      ulp_inputs_t
  #define calc_iaq_2nd_gen_ulp          calc_ulp
  #define init_iaq_2nd_gen_ulp          init_ulp
  
  #endif /* IAQ_2ND_GEN_ULP_H_ */
  