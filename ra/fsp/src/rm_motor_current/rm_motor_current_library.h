/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_MOTOR_CURRENT_LIBRARY_H
 #define RM_MOTOR_CURRENT_LIBRARY_H

 #ifdef __cplusplus
extern "C" {
 #endif

/***********************************************************************************************************************
 * Prototype definition
 ***********************************************************************************************************************/
void rm_motor_current_pi_gain_calc(motor_current_motor_parameter_t  * st_motor,
                                   motor_current_design_parameter_t * st_design_params,
                                   motor_current_pi_params_t        * st_pi_id,
                                   motor_current_pi_params_t        * st_pi_iq,
                                   float                              f4_ctrl_period);

void rm_motor_voltage_error_compensation_init(motor_currnt_voltage_compensation_t * st_volt_comp);
void rm_motor_voltage_error_compensation_reset(motor_currnt_voltage_compensation_t * st_volt_comp);
void rm_motor_voltage_error_compensation_main(motor_currnt_voltage_compensation_t * st_volt_comp,
                                              float                               * p_f4_v_array,
                                              float                               * p_f4_i_array,
                                              float                                 f4_vdc);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* RM_MOTOR_CURRENT_LIBRARY_H */
