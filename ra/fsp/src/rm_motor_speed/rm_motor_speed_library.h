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
 * File Name   : rm_motor_speed_library.h
 * Description : Definitions for Motor Speed library functions
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * History : DD.MM.YYYY Version
 *         : 01.09.2020 1.00
 ***********************************************************************************************************************/

#ifndef RM_MOTOR_SPEED_LIBRARY_H
#define RM_MOTOR_SPEED_LIBRARY_H

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

#endif                                 /* RM_MOTOR_SPEED_LIBRARY_H */
