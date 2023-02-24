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
 * @addtogroup MOTOR_SPEED
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_SPEED_H
#define RM_MOTOR_SPEED_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#include "rm_motor_speed_api.h"
#include "rm_motor_speed_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Library Macro definitions
 **********************************************************************************************************************/
#define MOTOR_SPEED_FLUXWKN_DEF_VFWRATIO              (0.95F)  /* Defines default flux-weakening voltage ratio */
#define MOTOR_SPEED_FLUXWKN_DEF_VFWRATIO_MIN          (0.5F)   /* Defines default minimum flux-weakening voltage ratio */

/*
 * Flux-weakening-states
 */
#define MOTOR_SPEED_FLUXWKN_STATE_BYPASSED            (0x0000) /* Flux-weakening control is not necessary, module is bypassed */
#define MOTOR_SPEED_FLUXWKN_STATE_FLUXWKN             (0x0001) /* Normal flux-weakening state */
#define MOTOR_SPEED_FLUXWKN_STATE_IDSAT               (0x0002) /* D-axis current has already saturated */
#define MOTOR_SPEED_FLUXWKN_STATE_ERROR               (0x8000) /* Flux-weakening general/runtime error */
#define MOTOR_SPEED_FLUXWKN_STATE_INVALID_MOTOR       (0x9001) /* Motor pointer is null or either of Ld, Lq, flux is below 0 */
#define MOTOR_SPEED_FLUXWKN_STATE_INVALID_IAMAX       (0x9002) /* Invalid maximum Ia value (Iamax < 0.0) */
#define MOTOR_SPEED_FLUXWKN_STATE_INVALID_VAMAX       (0x9003) /* Invalid maximum Va value (Vamax < 0.0)  */
#define MOTOR_SPEED_FLUXWKN_STATE_INVALID_VFWRATIO    (0x9004) /* Invalid flux-weakening maximum voltage ratio, that f4_vfw_ratio
                                                                * is out of range [VFWRATIO_MIN, 1.0]  */
#define MOTOR_SPEED_FLUXWKN_CHK_MASK                  (0xF000) /* Mask value to check error */
#define MOTOR_SPEED_FLUXWKN_INVALID_CHK               (0x9000) /* Value to check Invalidate */
#define MOTOR_SPEED_METHOD_PID                        (1)
#define MOTOR_SPEED_METHOD_IPD                        (2)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum  e_motor_speed_control_type
{
    MOTOR_SPEED_CONTROL_TYPE_SENSORLESS = 0, ///< Sensorless type
    MOTOR_SPEED_CONTROL_TYPE_ENCODER    = 1, ///< Encoder type
    MOTOR_SPEED_CONTROL_TYPE_HALL       = 2, ///< Hall type
    MOTOR_SPEED_CONTROL_TYPE_INDUCTION  = 3, ///< Induction type
} motor_speed_control_type_t;

typedef struct st_motor_speed_pi_params
{
    float f_err;                       ///< Error
    float f_kp;                        ///< Gain of proportional term
    float f_ki;                        ///< Gain of integral term
    float f_refi;                      ///< Buffer of integral term
    float f_ilimit;                    ///< Limit of integral term
} motor_speed_pi_params_t;

/* Design parameter structure */
typedef struct motor_speed_design_params
{
    float f_speed_omega;               ///< Natural frequency[Hz] for speed loop gain design
    float f_speed_zeta;                ///< Damping ratio for speed loop gain design
    float f_ed_hpf_omega;              ///< Natural frequency[Hz] for HPF in open-loop damping gain design
    float f_ol_damping_zeta;           ///< Damping ratio for open-loop damping gain design
    float f_phase_err_lpf_cut_freq;    ///< The cut-off frequency [Hz] of phase error LPF gain design
    float f_observer_omega;            ///< Natural frequency[Hz] for speed observer
    float f_observer_zeta;             ///< Damping ratio for speed observer
} motor_speed_design_params_t;

/* First order LPF structure */
typedef struct motor_speed_lpf
{
    float f_pre_output;                ///< Previous value of output
    float f_pre_input;                 ///< Previous value of input
    float f_omega_t;                   ///< Calculate value
    float f_gain_ka;                   ///< LPF gain
    float f_gain_kb;                   ///< LPF gain
} motor_speed_lpf_t;

/* Second order LPF structure */
typedef struct motor_speed_2nd_order_lpf
{
    float f4_pre_output;               ///< Previous value of output
    float f4_pre2_output;              ///< Before last value of output
    float f4_pre_input;                ///< Previous value of input
    float f4_pre2_input;               ///< Before last value of input
    float f4_omega_t;                  ///< Calculate value
    float f4_omega2_t;                 ///< Calculate value
    float f4_omega2_t2;                ///< Calculate value
    float f4_gain_ka;                  ///< LPF gain
    float f4_gain_kb;                  ///< LPF gain
    float f4_gain_kc;                  ///< LPF gain
} motor_speed_2nd_order_lpf_t;

/* For Openloop damping */
typedef enum  e_motor_speed_openloop_damping
{
    MOTOR_SPEED_OPENLOOP_DAMPING_DISABLE = 0, ///< Disable openloop damping
    MOTOR_SPEED_OPENLOOP_DAMPING_ENABLE  = 1  ///< Enable openloop damping
} motor_speed_openloop_damping_t;

typedef struct st_motor_speed_oldamp_sub
{
    motor_speed_lpf_t st_ed_lpf;             ///< Ed LPF structure
    float             f_damp_comp_gain;      ///< The gain for open-loop damping
    float             f_fb_speed_limit_rate; ///< The limit of speed feed-back rate
} motor_speed_oldamp_sub_t;

typedef struct st_motor_speed_oldamp
{
    float f4_ol_id_up_step;            ///< The d-axis current reference ramping up rate [A/ms]
    float f4_ol_id_down_step;          ///< The d-axis current reference ramping down rate [A/ms]
    float f4_ol_iq_down_step_ratio;    ///< The Iq reference ramping down proportion to Iqref before open-loop
    float f4_ol_id_ref;                ///< The d-axis current reference in open-loop drive
    float f4_id_down_speed_rad;        ///< The speed threshold[rad/s] to ramp down the d-axis current
    float f4_id_up_speed_rad;          ///< The speed threshold[rad/s] to ramp up the d-axis current
    float f4_opl2less_sw_time;         ///< Time to switch open-loop to sensor-less [s]
    float f4_switch_phase_err_rad;     ///< Phase error to decide sensor-less switch timing [rad]
} motor_speed_oldamp_t;

/* For Flux Weakening */
typedef enum  e_motor_speed_flux_weaken
{
    MOTOR_SPEED_FLUX_WEAKEN_DISABLE = 0, ///< Disable flux-weakening control
    MOTOR_SPEED_FLUX_WEAKEN_ENABLE  = 1  ///< Enable flux-weakening control
} motor_speed_flux_weaken_t;

typedef struct st_motor_speed_motor_parameter
{
    uint16_t u2_mtr_pp;                ///< Pole pairs
    float    f4_mtr_r;                 ///< Resistance [ohm]
    float    f4_mtr_ld;                ///< Inductance for d-axis [H]
    float    f4_mtr_lq;                ///< Inductance for q-axis [H]
    float    f4_mtr_m;                 ///< Magnet flux [Wb]
    float    f4_mtr_j;                 ///< Rotor inertia [kgm^2]
} motor_speed_motor_parameter_t;

typedef struct st_motor_speed_flux_weakening
{
    /* User configurations */
    const motor_speed_motor_parameter_t * pmotor; ///< The pointer to the motor parameter data structure
    float f4_ia_max;                              ///< The maximum magnitude of current vector
    float f4_va_max;                              ///< The maximum magnitude of voltage vector
    float f4_vfw_ratio;                           ///< The maximum ratio of voltage used by flux-weakening module

    /* Internal data */
    float    f4_id_demag;                         ///< The demagnetization current derived by (-flux/Ld)
    float    f4_id_min;                           ///< The minimum Id output, min(-Ia,Id_demag)
    float    f4_v_fw;                             ///< The target abs. limit value of voltage vector due to the total flux
    uint16_t u2_fw_status;                        ///< The status of flux-weakening
} motor_speed_flux_weakening_t;

typedef enum  e_motor_speed_less_switch
{
    MOTOR_SPEED_LESS_SWITCH_DISABLE = 0, ///< Disable soft switching between open-loop mode and normal field oriented control mode
    MOTOR_SPEED_LESS_SWITCH_ENABLE  = 1  ///< Enable soft switching between open-loop mode and normal field oriented control mode
} motor_speed_less_switch_t;

/* For Speed Observer */
typedef enum  e_motor_speed_observer_switch
{
    MOTOR_SPEED_OBSERVER_SWITCH_DISABLE = 0, ///< Disable speed observer
    MOTOR_SPEED_OBSERVER_SWITCH_ENABLE  = 1  ///< Enable speed observer
} motor_speed_observer_switch_t;

typedef enum  e_motor_speed_observer_select
{
    MOTOR_SPEED_OBSERVER_SELECT_NORMAL      = 0, ///< Normal speed observer
    MOTOR_SPEED_OBSERVER_SELECT_DISTURBANCE = 1, ///< Disturbance speed observer
} motor_speed_observer_select_t;

typedef struct st_motor_speed_observer
{
    float f4_speed_rad;                 ///< speed observer output speed [rad/s] (electrical)
    float f4_ref_torque;                ///< reference torque
    float f4_ref_pre_torque;            ///< previous value of reference torque
    float f4_ref_speed_rad;             ///< reference speed for sob [rad/s] (electrical)
    float f4_ref_pre_speed_rad;         ///< previous value of reference speed for sob [rad/s] (electrical)
    float f4_hpf_k1;                    ///< HPF gain for sob
    float f4_hpf_k2;                    ///< HPF gain for sob
    float f4_hpf_k3;                    ///< HPF gain for sob
    float f4_k1;                        ///< K1 gain for sob
    float f4_k2;                        ///< K2 gain for sob
    float f4_hpf_ref_speed_rad;         ///< HPF output reference speed [rad/s]
    float f4_hpf_ref_pre_speed_rad;     ///< previous value of HPF output reference speed [rad/s]
    float f4_hpf_omega;                 ///< natural frequency for speed observer HPF
    motor_speed_2nd_order_lpf_t st_lpf; ///< second order LPF structure
} motor_speed_observer_t;

typedef struct st_motor_speed_disturbance_observer
{
    float             f4_gain_distubance_estimate; ///< Gain of disturbance estimator
    float             f4_gain_speed_estimate;      ///< Gain of speed estimator
    float             f4_estimated_distubance;     ///< Estimated disturbance
    float             f4_estimated_speed;          ///< Estimated speed
    float             f4_inertia;                  ///< Total inertia of system [kgm^2]
    float             f4_ctrl_period;              ///< Interval of estimator execution
    motor_speed_lpf_t st_lpf;                      ///< Structure for LPF
} motor_speed_disturbance_observer_t;

typedef struct st_motor_speed_extended_cfg
{
    uint8_t u1_ctrl_method;                             ///< Feedback control method

    float f_speed_ctrl_period;                          ///< Speed control period [sec]
    float f_limit_speed_change;                         ///< Reference speed max change limit [rad/s]
    float f_max_speed_rad;                              ///< Maximum speed command value [rad/s]
    float f_omega_t;                                    ///< Speed LPF design value
    float f_id_up_speed_rad;                            ///< The speed threshold[rad/s] to ramp up the d-axis current
    float f_iq_limit;                                   ///< Limit of q-axis current [A]

    float f_ol_fb_speed_limit_rate;                     ///< Rate of reference speed for feedback speed limitter

    float f_natural_frequency;                          ///< Natural frequency for disturbance observer [Hz]

    motor_speed_openloop_damping_t u1_openloop_damping; ///< Openloop damping active flag
    motor_speed_flux_weaken_t      u1_flux_weakening;   ///< Flux weakening active flag
    motor_speed_less_switch_t      u1_less_switch;      ///< Soft switching active flag
    motor_speed_observer_switch_t  u1_observer_swtich;  ///< Speed observer active flag
    motor_speed_observer_select_t  observer_select;     ///< Selection of speed observer type

    motor_speed_oldamp_t          ol_param;             ///< Parameter for open-loop damping
    motor_speed_oldamp_sub_t      ol_sub_param;         ///< Sub parameter for open-loop damping
    motor_speed_design_params_t   d_param;              ///< Design parameter for speed control
    motor_speed_control_type_t    control_type;         ///< Motor control type
    motor_speed_motor_parameter_t mtr_param;            ///< Motor parameter
} motor_speed_extended_cfg_t;

typedef enum  e_motor_speed_ctrl_status
{
    MOTOR_SPEED_CTRL_STATUS_INIT = 0,  ///< Speed control status is INIT
    MOTOR_SPEED_CTRL_STATUS_BOOT,      ///< Speed control status is BOOT
    MOTOR_SPEED_CTRL_STATUS_RUN,       ///< Speed control status is RUN
} motor_speed_ctrl_status_t;

typedef struct st_motor_speed_instance_ctrl
{
    uint32_t open;

    uint8_t u1_active;                                          ///< Flag to set active/inactive the speed control
    uint8_t u1_state_speed_ref;                                 ///< The speed control status
    uint8_t u1_flag_get_iref;                                   ///< Flag to get d/q-axis current reference
    uint8_t u1_state_id_ref;                                    ///< The d-axis current command status
    uint8_t u1_state_iq_ref;                                    ///< The q-axis current command status
    float   f_id_ref;                                           ///< D-axis current reference [A] for calculation
    float   f_iq_ref;                                           ///< Q-axis current reference [A] for calculation
    float   f_rpm2rad;                                          ///< Coeficient to translate [rpm] to [rad/s]
    float   f_ref_speed_rad_ctrl;                               ///< Command speed value for speed PI control[rad/s]
    float   f_ref_speed_rad;                                    ///< Reference speed value [rad/s]
    float   f_speed_lpf_rad;                                    ///< Speed processed by LPF
    motor_speed_ctrl_status_t e_status;

    /* Openloop damping related valiable */
    uint8_t u1_flag_down_to_ol;                                 ///< The open-loop drive flag
    float   f_ol_iq_down_step;                                  ///< The q-axis current reference ramping down rate [A/ms]
    float   f_phase_err_rad_lpf;                                ///< LPF value of phase error[rad]
    float   f_init_phase_err_rad;                               ///< Initialization value of phase error rate
    float   f_opl_torque_current;                               ///< The torque current (Iq) in sensor-less switching
    float   f_damp_comp_speed;                                  ///< The speed for open-loop damping
    float   f_damp_comp_gain;                                   ///< The gain for open-loop damping
    float   f_fb_speed_limit_rate;                              ///< The limit of speed feed-back rate

    /* Flux Weakening related valiable */
    uint8_t u1_enable_flux_weakning;                            ///< The flag for enable/disable flux weakening process
    motor_speed_flux_weakening_t st_flxwkn;                     ///< Data for flux-weakening control

    motor_speed_cfg_t const * p_cfg;
    motor_speed_pi_params_t   pi_param;                         ///< Data for flux-weakening control
    motor_speed_input_t       st_input;                         ///< Input data buffer
    motor_speed_lpf_t         st_speed_lpf;                     ///< Speed LPF structure
    motor_speed_lpf_t         st_phase_err_lpf;                 ///< Phase error LPF structure

    motor_speed_observer_t             st_observer;             ///< Speed observer structure
    motor_speed_disturbance_observer_t st_disturbance_observer; ///< Disturbance speed observer structure

    motor_speed_position_data_t st_position_data;               ///< Data for position control

    /* cyclic timer callback */
    timer_callback_args_t timer_args;                           ///< Cyclic timer callback

#if MOTOR_SPEED_CFG_POSITION_SUPPORTED == 1
    motor_position_instance_t const * p_position_instance;      ///< Position module instance
#endif
} motor_speed_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const motor_speed_api_t g_motor_speed_on_motor_speed;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SPEED_Open(motor_speed_ctrl_t * const p_ctrl, motor_speed_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_SPEED_Close(motor_speed_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SPEED_Reset(motor_speed_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SPEED_Run(motor_speed_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SPEED_SpeedReferenceSet(motor_speed_ctrl_t * const p_ctrl, float const speed_reference_rpm);

fsp_err_t RM_MOTOR_SPEED_PositionReferenceSet(motor_speed_ctrl_t * const                p_ctrl,
                                              motor_speed_position_data_t const * const p_position_data);

fsp_err_t RM_MOTOR_SPEED_ParameterSet(motor_speed_ctrl_t * const p_ctrl, motor_speed_input_t const * const p_st_input);

fsp_err_t RM_MOTOR_SPEED_SpeedControl(motor_speed_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SPEED_ParameterGet(motor_speed_ctrl_t * const p_ctrl, motor_speed_output_t * const p_st_output);

fsp_err_t RM_MOTOR_SPEED_ParameterUpdate(motor_speed_ctrl_t * const p_ctrl, motor_speed_cfg_t const * const p_cfg);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_SPEED_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_SPEED)
 **********************************************************************************************************************/
