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
