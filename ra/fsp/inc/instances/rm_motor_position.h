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
 * @addtogroup MOTOR_POSITION
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_POSITION_H
#define RM_MOTOR_POSITION_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "rm_motor_position_api.h"
#include "rm_motor_position_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MOTOR_POSITION_CODE_VERSION_MAJOR    (1U)
#define MOTOR_POSITION_CODE_VERSION_MINOR    (0U)

#define MOTOR_POSITION_TWOPI                 (3.14159265358979F * 2.0F)
#define MOTOR_POSITION_TWOPI_60              (MOTOR_POSITION_TWOPI / 60.0F) /* To translate rpm => rad/s */
#define MOTOR_POSITION_TWOPI_360             (MOTOR_POSITION_TWOPI / 360.0F)
#define MOTOR_POSITION_360_TWOPI             (360.0F / MOTOR_POSITION_TWOPI)

/***********************************************************************************************************************
 * Library Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* motor parameter structure */
typedef struct st_motor_position_motor_parameter
{
    uint16_t u2_mtr_pp;                ///< Pole pairs
    float    f4_mtr_r;                 ///< Resistance [ohm]
    float    f4_mtr_ld;                ///< Inductance for d-axis [H]
    float    f4_mtr_lq;                ///< Inductance for q-axis [H]
    float    f4_mtr_m;                 ///< Magnet flux [Wb]
    float    f4_mtr_j;                 ///< Rotor inertia [kgm^2]
    float    f4_nominal_current_rms;   ///< Rated torque [Nm]
} motor_position_motor_parameter_t;

/***************************/
/*     For IPD Control     */
/***************************/
/* Second order LPF structure */
typedef struct st_motor_position_2nd_order_lpf
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
} motor_position_2nd_order_lpf_t;

typedef enum  e_motor_position_ipd_lpf
{
    MOTOR_POSITION_IPD_LPF_DISABLE = 0, ///< ipd control is disabled
    MOTOR_POSITION_IPD_LPF_ENABLE  = 1  ///< ipd control is enabled
} motor_position_ipd_lpf_t;

typedef struct st_motor_position_ipd
{
    motor_position_ipd_lpf_t u1_ipd_lpf_flag;  ///< 0 : LPF OFF(default) 1 : LPF ON
    float f4_ref_pos_pre_rad_ctrl;             ///< previous position value for control [rad] (mechanical)
    float f4_ipd_pos_k;                        ///< position control gain for I-PD
    float f4_ipd_pos_1st_fb_rad;               ///< feed-back position [rad] (mechanical)
    float f4_ipd_pos_1st_fb_pre_rad;           ///< previous value of feed-back position [rad] (mechanical)
    float f4_ipd_pos_2nd_fb_rad;               ///< feed-back position [rad] (mechanical)
    float f4_ipd_ref_pos_rad;                  ///< ipd control reference [rad] (mechanical)
    float f4_ipd_err_rad;                      ///< ipd control error [rad] (mechanical)
    float f4_ipd_pos_fb_k;                     ///< feedback gain for I-PD
    float f4_ipd_pos_ff_rad;                   ///< feed-forward position [rad] (mechanical)
    float f4_ipd_pos_ff_k;                     ///< feed-forward position control gain
    float f4_ipd_pos_p_rad;                    ///< proportional control [rad] (mechanical)
    float f4_ipd_pos_kp;                       ///< position control gain kp
    float f4_ipd_pos_kp_ratio;                 ///< position contorl gain kp ratio
    float f4_ipd_pos_ff_ratio;                 ///< position feed-forward gain ratio
    float f4_ipd_speed_k;                      ///< speed gain for I-PD
    float f4_ipd_speed_k_ratio;                ///< speed gain for I-PD gain ratio
    float f4_ipd_ref_speed_rad;                ///< reference speed [rad/s] (electrical)
    float f4_ipd_err_limit_1;                  ///< position error limit 1
    float f4_ipd_err_limit_2;                  ///< position error limit 2
    float f4_ipd_lpf_omega;                    ///< natural frequency for position LPF
    float f4_ipd_lpf_zeta;                     ///< damping ratio for position LPF
    float f4_pos_omega;                        ///< Natural frequency[Hz] for position loop gain design
    motor_position_2nd_order_lpf_t st_pos_lpf; ///< second order LPF structure
} motor_position_ipd_t;

typedef struct st_motor_position_ipd_design_parameter
{
    float f4_ipd_pos_kp_ratio;         ///< position contorl gain kp ratio
    float f4_ipd_pos_ff_ratio;         ///< position feed-forward gain ratio
    float f4_ipd_speed_k_ratio;        ///< speed gain for I-PD gain ratio
    float f4_ipd_err_limit_1;          ///< position error limit 1
    float f4_ipd_err_limit_2;          ///< position error limit 2
    float f4_ipd_lpf_omega;            ///< natural frequency for position LPF
    float f4_ipd_lpf_zeta;             ///< damping ratio for position LPF
} motor_position_ipd_design_parameter_t;

/*********************************/
/*     For Position Profiling    */
/*********************************/
typedef struct st_motor_positon_profiling
{
    uint8_t  u1_state_pos_pf;          ///< position profile status
    uint8_t  u1_pos_ref_mode;          ///< position reference mode
    uint16_t u2_interval_time;         ///< interval time for profile
    uint16_t u2_interval_time_buff;    ///< interval time buffer for profile
    uint16_t u2_interval_time_cnt;     ///< interval time counter for profile
    float    f4_accel_time;            ///< acceleration time
    float    f4_accel_time_buff;       ///< acceleration time buffer
    float    f4_accel_time_inv;        ///< inverse of acceleration time
    float    f4_max_accel_time;        ///< maximum acceleration time
    float    f4_accel_max_speed;       ///< maximum speed for acceleration
    float    f4_accel_max_speed_buff;  ///< maximum speed buffer for acceleration
    float    f4_time_sec;              ///< timer counter for profiling
    float    f4_pos_st_rad;            ///< start position
    float    f4_pos_ed_rad;            ///< end position
    float    f4_pos_dt_rad;            ///< position error for profile
    float    f4_pos_dt_time_sec;       ///< position error / max speed
} motor_position_profiling_t;

typedef struct st_motor_position_profiling_setting
{
    uint16_t u2_interval_time;
    float    f4_accel_time;            ///< acceleration time
    float    f4_max_accel;             ///< maximum acceleration
    float    f4_accel_max_speed;       ///< maximum speed for acceleration
    float    f4_timer_update_step;     ///< update time of profile
} motor_position_profiling_setting_t;

typedef struct st_motor_position_extended_cfg
{
    motor_position_ipd_lpf_t              ipd_lpf;       ///< ipd LPF structure
    motor_position_ipd_design_parameter_t st_ipd_design; ///< ipd design structure

    motor_position_profiling_setting_t st_profiling_set; ///< profile setting structure

    uint16_t u2_pos_dead_band;                           ///< position dead-band
    uint16_t u2_pos_band_limit;                          ///< positioning band limit
    float    f_speed_ff_ratio;                           ///< speed feed-forward gain ratio
    float    f_encd_angle_diff;                          ///< angle of encoder 1 pulse width

    float f_pos_omega;                                   ///< natural frequency for position

    float f_accel_time;                                  ///< reference acceleration time

    float f_speed_ctrl_period;                           ///< speed control period

    motor_position_motor_parameter_t st_motor;           ///< motor parameter structure
} motor_position_extended_cfg_t;

typedef struct st_motor_position_variables
{
    float f4_pos_kp;                   ///< proportional gain for position
    float f4_pos_rad;                  ///< position value [rad] (mechanical)
    float f4_pos_err_rad;              ///< position error [rad] (mechanical)
    float f4_ref_pos_rad;              ///< reference position [rad] (mechanical)
    float f4_ref_pos_pre_rad;          ///< previous value of reference position [rad] (mechanical)
    float f4_ref_pos_rad_ctrl;         ///< reference position for control [rad] (mechanical)
    float f4_speed_ff_rad;             ///< feed-forward speed [rad] (electrical)
} motor_position_variables_t;

typedef struct st_motor_position_instance_ctrl
{
    uint32_t open;                           ///< Used to determine if the channel is configured

    motor_position_ctrl_mode_t e_ctrl_mode;  ///< control mode structure

    motor_position_variables_t st_variable;  ///< position control structure
    motor_position_ipd_t       st_ipd;       ///< ipd control structure
    motor_position_profiling_t st_profiling; ///< position profile structure

    motor_position_cfg_t const * p_cfg;      ///< pointer to initial configurations
} motor_position_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const motor_position_api_t g_motor_position_on_motor_position;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_Open(motor_position_ctrl_t * const p_ctrl, motor_position_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_POSITION_Close(motor_position_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_POSITION_Reset(motor_position_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_POSITION_PositionGet(motor_position_ctrl_t * const p_ctrl, int16_t * const p_position);

fsp_err_t RM_MOTOR_POSITION_PositionSet(motor_position_ctrl_t * const p_ctrl, float const position_rad);

fsp_err_t RM_MOTOR_POSITION_PositionReferenceSet(motor_position_ctrl_t * const p_ctrl,
                                                 int16_t const                 position_reference_deg);

fsp_err_t RM_MOTOR_POSITION_ControlModeSet(motor_position_ctrl_t * const p_ctrl, motor_position_ctrl_mode_t const mode);

fsp_err_t RM_MOTOR_POSITION_PositionControl(motor_position_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_POSITION_IpdSpeedPControl(motor_position_ctrl_t * const p_ctrl,
                                             float const                   ref_speed_rad,
                                             float const                   speed_rad,
                                             float * const                 p_iq_ref);

fsp_err_t RM_MOTOR_POSITION_SpeedReferencePControlGet(motor_position_ctrl_t * const p_ctrl, float * const p_speed_ref);

fsp_err_t RM_MOTOR_POSITION_SpeedReferenceIpdControlGet(motor_position_ctrl_t * const p_ctrl,
                                                        float const                   max_speed_rad,
                                                        float * const                 p_speed_ref);

fsp_err_t RM_MOTOR_POSITION_SpeedReferenceFeedforwardGet(motor_position_ctrl_t * const p_ctrl,
                                                         float * const                 p_speed_ref);

fsp_err_t RM_MOTOR_POSITION_InfoGet(motor_position_ctrl_t * const p_ctrl, motor_position_info_t * const p_info);

fsp_err_t RM_MOTOR_POSITION_ParameterUpdate(motor_position_ctrl_t * const      p_ctrl,
                                            motor_position_cfg_t const * const p_cfg);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_POSITION_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_POSITION)
 **********************************************************************************************************************/
