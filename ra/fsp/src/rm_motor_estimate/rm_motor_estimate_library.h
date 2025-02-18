/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name   : rm_motor_estimate_library.h
 * Description : Header for BEMF Ovserver functions in library
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * History : DD.MM.YYYY Version
 *         : 01.09.2020 1.00
 ***********************************************************************************************************************/

#ifndef RM_MOTOR_ESTIMATE_LIBRARY_H
 #define RM_MOTOR_ESTIMATE_LIBRARY_H

 #ifdef __cplusplus
extern "C" {
 #endif

/* Library functions */
void rm_motor_estimate_bemf_observer(motor_estimate_bemf_observer_t * p_bemf_obs,
                                     float                            f4_vd_ref,
                                     float                            f4_vq_ref,
                                     float                            f4_id,
                                     float                            f4_iq);

float rm_motor_estimate_bemf_calc_d(motor_estimate_bemf_observer_t * p_bemf_obs, float f4_speed_rad, float f4_iq);

float rm_motor_estimate_bemf_calc_q(motor_estimate_bemf_observer_t * p_bemf_obs, float f4_speed_rad, float f4_id);

void rm_motor_estimate_bemf_obs_init(motor_estimate_bemf_observer_t   * p_bemf_obs,
                                     motor_estimate_motor_parameter_t * p_motor_params);

void rm_motor_estimate_bemf_observer_gain_calc(motor_estimate_motor_parameter_t * p_motor,
                                               motor_estimate_extended_cfg_t    * p_design_params,
                                               motor_estimate_bemf_observer_t   * p_bemf_obs,
                                               float                              f4_ctrl_period);

void rm_motor_estimate_bemf_obs_reset(motor_estimate_bemf_observer_t * p_bemf_obs);

void rm_motor_estimate_speed_pll(motor_estimate_pll_est_t * p_pll_est, float f4_phase_err, float * p_f4_speed);

void rm_motor_estimate_speed_gain_calc(motor_estimate_extended_cfg_t * p_design_params,
                                       motor_estimate_pll_est_t      * p_pll_est,
                                       float                           f4_ctrl_period);

void rm_motor_estimate_speed_reset(motor_estimate_pll_est_t * p_pll_est);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* RM_MOTOR_ESTIMATE_LIBRARY_H */
