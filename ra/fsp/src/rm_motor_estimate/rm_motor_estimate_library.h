/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

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
