/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name   : rm_motor_speed_library.h
 * Description : Definitions for Motor Speed library functions
 ***********************************************************************************************************************/

#ifndef RM_MOTOR_SPEED_LIBRARY_H
 #define RM_MOTOR_SPEED_LIBRARY_H

 #ifdef __cplusplus
extern "C" {
 #endif

void rm_motor_speed_pi_gain_calc(motor_speed_motor_parameter_t * p_motor,
                                 motor_speed_design_params_t   * p_design_params,
                                 motor_speed_pi_params_t       * p_pi_speed,
                                 float                           f4_speed_ctrl_period);

void rm_motor_speed_fluxwkn_init(motor_speed_flux_weakening_t        * p_fluxwkn,
                                 float                                 f4_ia_max,
                                 float                                 f4_va_max,
                                 const motor_speed_motor_parameter_t * p_mtr);
void rm_motor_speed_fluxwkn_reset(motor_speed_flux_weakening_t * p_fluxwkn);
void rm_motor_speed_fluxwkn_set_motor(motor_speed_flux_weakening_t        * p_fluxwkn,
                                      const motor_speed_motor_parameter_t * p_mtr);
void     rm_motor_speed_fluxwkn_set_vamax(motor_speed_flux_weakening_t * p_fluxwkn, float f4_va_max);
void     rm_motor_speed_fluxwkn_set_iamax(motor_speed_flux_weakening_t * p_fluxwkn, float f4_ia_max);
uint16_t rm_motor_speed_fluxwkn_run(motor_speed_flux_weakening_t * p_fluxwkn,
                                    float                          f4_speed_rad,
                                    const float                  * p_f4_idq,
                                    float                        * p_f4_idq_ref);
uint8_t rm_motor_speed_fluxwkn_check_bypass(motor_speed_flux_weakening_t * p_fluxwkn);

float rm_motor_speed_opl_damp_ctrl(motor_speed_oldamp_sub_t * p_opl_damp, float f4_ed, float f4_speed_ref);
void  rm_motor_speed_opl_damp_init(motor_speed_oldamp_sub_t * p_opl_damp, float f4_fb_speed_limit_rate);
void  rm_motor_speed_opl_damp_reset(motor_speed_oldamp_sub_t * p_opl_damp);
void  rm_motor_speed_opl_damp_r_set_gain(motor_speed_oldamp_sub_t * p_opl_damp,
                                         uint16_t                   u2_pp,
                                         float                      f4_ke,
                                         float                      f4_j,
                                         float                      f4_zeta,
                                         float                      f4_ed_hpf_fc,
                                         float                      f4_opl_current,
                                         float                      f4_id_down_speed,
                                         float                      f4_tc);
void rm_motor_speed_opl_damp_set_limit(motor_speed_oldamp_sub_t * p_opl_damp, float f4_limit_rate);

float rm_motor_speed_opl2less_torque_current_calc(const motor_speed_motor_parameter_t * p_motor,
                                                  float                                 f4_opl2less_sw_time,
                                                  float                                 f4_ol_id_ref,
                                                  float                                 f4_phase_err_rad_lpf);
float rm_motor_speed_opl2less_iq_calc(float f4_ed, float f4_eq, float f4_id, float f4_torque_current,
                                      float f4_phase_err);

float rm_motor_speed_limitfabs(float f4_value, float f4_limit_value);
float rm_motor_speed_first_order_lpf(motor_speed_lpf_t * p_lpf, float f_input);

void  rm_motor_speed_observer_init(motor_speed_observer_t * p_sob);
void  rm_motor_speed_observer_reset(motor_speed_observer_t * p_sob);
float rm_motor_speed_observer(motor_speed_observer_t        * p_sob,
                              motor_speed_motor_parameter_t * p_motor,
                              float                           f4_iq_ref,
                              float                           f4_speed_rad);
void rm_motor_speed_observer_gain_calc(motor_speed_observer_t      * p_sob,
                                       motor_speed_design_params_t * p_design_params,
                                       float                         f4_speed_ctrl_period);
void rm_motor_speed_observer_SecondOrderLpffGainCalc(motor_speed_2nd_order_lpf_t * p_lpf,
                                                     float                         f4_omega,
                                                     float                         f4_zeta,
                                                     float                         f4_ctrl_period);

void rm_motor_speed_disturbance_observer_init(motor_speed_disturbance_observer_t * p_st_observer,
                                              float                                f4_natural_freq_hz,
                                              float                                f4_ctrl_period,
                                              float                                f4_inertia_kgms2);
void  rm_motor_speed_disturbance_observer_reset(motor_speed_disturbance_observer_t * p_st_observer);
float rm_motor_speed_disturbance_observer_run(motor_speed_disturbance_observer_t * p_st_observer,
                                              float                                f4_torque_cmd_nm,
                                              float                                f4_speed_rad);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* RM_MOTOR_SPEED_LIBRARY_H */
