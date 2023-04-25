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

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_ESTIMATE
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_ESTIMATE_H
#define RM_MOTOR_ESTIMATE_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#include "rm_motor_angle_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum  e_motor_estimate_openloop_damping
{
    MOTOR_ESTIMATE_OPENLOOP_DAMPING_DISABLE = 0,
    MOTOR_ESTIMATE_OPENLOOP_DAMPING_ENABLE  = 1
} motor_estimate_openloop_damping_t;

typedef struct st_motor_estimate_bemf_obs_axis
{
    float f4_k_e_obs_1;                ///< BEMF observer gain 1
    float f4_k_e_obs_2;                ///< BEMF observer gain 2
    float f4_i_pre;                    ///< Previous value of current
    float f4_i_est_pre;                ///< Previous value of estimated current
    float f4_d_est;                    ///< Estimated voltage disturbance
    float f4_d_est_pre;                ///< Previous value of voltage disturbance
    float f4_d_est_limit;              ///< Integration limit value of voltage disturbance estimate
} motor_estimate_bemf_obs_axis_t;

typedef struct st_motor_estimate_motor_parameter
{
    uint16_t u2_mtr_pp;                ///< Pole pairs
    float    f4_mtr_r;                 ///< Resistance [ohm]
    float    f4_mtr_ld;                ///< Inductance for d-axis [H]
    float    f4_mtr_lq;                ///< Inductance for q-axis [H]
    float    f4_mtr_m;                 ///< Magnet flux [Wb]
    float    f4_mtr_j;                 ///< Rotor inertia [kgm^2]
    float    f4_mtr_nominal_current;   ///< Nominal current [Arms]
} motor_estimate_motor_parameter_t;

typedef struct st_motor_estimate_bemf_observer
{
    float f4_dt;                                      ///< Control period
    motor_estimate_motor_parameter_t st_motor_params; ///< Motor parameters
    motor_estimate_bemf_obs_axis_t   st_d_axis;       ///< D-axis observer
    motor_estimate_bemf_obs_axis_t   st_q_axis;       ///< Q-axis observer
} motor_estimate_bemf_observer_t;

typedef struct st_motor_estimate_pll_est
{
    float f4_kp_est_speed;             ///< The proportional gain for PLL
    float f4_ki_est_speed;             ///< The integral gain for PLL
    float f4_i_est_speed;              ///< The integrator for PLL
} motor_estimate_pll_est_t;

typedef struct st_motor_estimate_input
{
    float f_vd_ref;                    ///< d-axis Voltage Reference [V]
    float f_vq_ref;                    ///< q-axis Voltage Reference [V]
    float f_id;                        ///< d-axis current [A]
    float f_iq;                        ///< q-axis current [A]
    float f4_ref_speed_rad_ctrl;       ///< Speed Reference [rad/sec]
    float f4_damp_comp_speed;
} motor_estimate_input_t;

typedef struct st_motor_estimate_extended_cfg
{
    motor_estimate_openloop_damping_t openloop_damping;
    float f_e_obs_omega;                              ///< Natural frequency of BEMF observer
    float f_e_obs_zeta;                               ///< Damping ratio of BEMF observer
    float f_pll_est_omega;                            ///< Natural frequency of PLL Speed estimate loop
    float f_pll_est_zeta;                             ///< Damping ratio of PLL Speed estimate loop
    float f4_ctrl_period;                             ///< Period of Control Process [sec]
    motor_estimate_motor_parameter_t st_motor_params; ///< Motor parameters
} motor_estimate_extended_cfg_t;

typedef struct st_motor_estimate_instance_ctrl
{
    uint32_t open;
    float    f4_ed;
    float    f4_eq;
    float    f4_speed_rad;
    float    f4_phase_err_rad;
    float    f4_angle_rad;
    uint8_t  u1_flg_pi_ctrl;
    uint8_t  u1_flg_pll_start;
    motor_estimate_bemf_observer_t st_bemf_obs; ///< BEMF observer structure
    motor_estimate_pll_est_t       st_pll_est;  ///< PLL estimator structure
    motor_estimate_input_t         st_input;    ///< Input parameter structure
    motor_angle_cfg_t const      * p_cfg;
} motor_estimate_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const motor_angle_api_t g_motor_angle_on_motor_estimate;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_Open(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_ESTIMATE_Close(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_ESTIMATE_Reset(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_ESTIMATE_CurrentSet(motor_angle_ctrl_t * const              p_ctrl,
                                       motor_angle_current_t * const           p_st_current,
                                       motor_angle_voltage_reference_t * const p_st_voltage);

fsp_err_t RM_MOTOR_ESTIMATE_SpeedSet(motor_angle_ctrl_t * const p_ctrl, float const speed_ctrl, float const damp_speed);

fsp_err_t RM_MOTOR_ESTIMATE_FlagPiCtrlSet(motor_angle_ctrl_t * const p_ctrl, uint32_t const flag_pi);

fsp_err_t RM_MOTOR_ESTIMATE_AngleSpeedGet(motor_angle_ctrl_t * const p_ctrl,
                                          float * const              p_angle,
                                          float * const              p_speed,
                                          float * const              p_phase_err);

fsp_err_t RM_MOTOR_ESTIMATE_EstimatedComponentGet(motor_angle_ctrl_t * const p_ctrl,
                                                  float * const              p_ed,
                                                  float * const              p_eq);

fsp_err_t RM_MOTOR_ESTIMATE_ParameterUpdate(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * p_cfg);

fsp_err_t RM_MOTOR_ESTIMATE_InternalCalculate(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_ESTIMATE_AngleAdjust(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_ESTIMATE_EncoderCyclic(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_ESTIMATE_InfoGet(motor_angle_ctrl_t * const p_ctrl, motor_angle_encoder_info_t * const p_info);

fsp_err_t RM_MOTOR_ESTIMATE_CyclicProcess(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_ESTIMATE_SensorDataSet(motor_angle_ctrl_t * const p_ctrl, motor_angle_ad_data_t * const p_ad_data);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_ESTIMATE_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_ESTIMATE)
 **********************************************************************************************************************/
