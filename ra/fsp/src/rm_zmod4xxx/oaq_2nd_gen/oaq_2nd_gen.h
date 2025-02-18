/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
  * @file    oaq_2nd_gen.h
  * @author  Renesas Electronics Corporation
  * @version 5.0.0
  * @brief   Provide names for oaq_2nd_gen backward compatibility.
  * @note    OAQ 2nd Gen naming is deprecated and will be removed 
  *          in future revisions.
  */

#ifndef OAQ_2ND_GEN_H_
#define OAQ_2ND_GEN_H_

#include "ulp_o3.h"

// clang-format off
// #warning "The oaq_2nd_gen.h header is provided for backward compatibility only and will be removed in future revisions. Please use names defined in ulp_o3.h"
// clang-format on

/* below definitions map the legacy OAQ 2nd Gen to ULP O3 names */
#define OAQ_2ND_GEN_OK                     ULP_O3_OK
#define OAQ_2ND_GEN_STABILIZATION          ULP_O3_STABILIZATION
#define OAQ_2ND_GEN_DAMAGE                 ULP_O3_DAMAGE
#define oaq_2nd_gen_handle_t               ulp_o3_handle_t
#define oaq_2nd_gen_results_t              ulp_o3_results_t
#define oaq_2nd_gen_inputs_t               ulp_o3_inputs_t
#define init_oaq_2nd_gen                   init_ulp_o3
#define calc_oaq_2nd_gen                   calc_ulp_o3
#define g_zmod4510_oaq_2nd_gen_sensor_type g_zmod4510_ulp_o3_sensor_type

#endif /* OAQ_2ND_GEN_H_ */
