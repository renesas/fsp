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
 * @addtogroup MOTOR_CURRENT
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_CURRENT_H
#define RM_MOTOR_CURRENT_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#include "rm_motor_current_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* For Voltage Compensation */
#define MOTOR_CURRENT_VOLTAGE_COMPENSATION_TABLE_ARRAY_SIZE    (5)
#define MOTOR_CURRENT_VOLTAGE_COMPENSATION_SLOPE_ARRAY_SIZE    (6)
#define MOTOR_CURRENT_VOLTAGE_COMPENSATION_PHASE_ARRAY_SIZE    (3)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum  e_motor_current_control_type
{
    MOTOR_CURRENT_CONTROL_TYPE_SENSORLESS = 0,
    MOTOR_CURRENT_CONTROL_TYPE_ENCODER    = 1,
    MOTOR_CURRENT_CONTROL_TYPE_HALL       = 2,
    MOTOR_CURRENT_CONTROL_TYPE_INDUCTION  = 3,
} motor_current_control_type_t;

/** Selection of shunt type */
typedef enum e_motor_current_shunt_type
{
    MOTOR_CURRENT_SHUNT_TYPE_1_SHUNT = 1, ///< Only use U phase current
    MOTOR_CURRENT_SHUNT_TYPE_2_SHUNT,     ///< Use U and W phase current
    MOTOR_CURRENT_SHUNT_TYPE_3_SHUNT      ///< Use all phase current
} motor_current_shunt_type_t;

typedef enum  e_motor_current_voltage_compensation_select
{
    MOTOR_CURRENT_VOLTAGE_COMPENSATION_SELECT_DISABLE = 0,
    MOTOR_CURRENT_VOLTAGE_COMPENSATION_SELECT_ENABLE  = 1
} motor_current_voltage_compensation_select_t;

typedef enum  e_motor_current_sample_delay_compensation
{
    MOTOR_CURRENT_SAMPLE_DELAY_COMPENSATION_DISABLE = 0,
    MOTOR_CURRENT_SAMPLE_DELAY_COMPENSATION_ENABLE  = 1
} motor_current_sample_delay_compensation_t;

typedef struct st_motor_current_pi_params
{
    float f_err;                       ///< Error
    float f_kp;                        ///< Gain of proportional term
    float f_ki;                        ///< Gain of integral term
    float f_refi;                      ///< Buffer of integral term
    float f_ilimit;                    ///< Limit of integral term
} motor_current_pi_params_t;

/* Design parameter structure */
typedef struct motor_current_design_parameter
{
    float f_current_omega;             ///< Natural frequency[Hz] for current loop gain design
    float f_current_zeta;              ///< Damping ratio for current loop gain design
} motor_current_design_parameter_t;

typedef struct st_motor_current_motor_parameter
{
    uint16_t u2_mtr_pp;                ///< Pole pairs
    float    f4_mtr_r;                 ///< Resistance [ohm]
    float    f4_mtr_ld;                ///< Inductance for d-axis [H]
    float    f4_mtr_lq;                ///< Inductance for q-axis [H]
    float    f4_mtr_m;                 ///< Magnet flux [Wb]
    float    f4_mtr_j;                 ///< Rotor inertia [kgm^2]
} motor_current_motor_parameter_t;

typedef struct st_motor_current_voltage_compensation
{
    float f_comp_v[MOTOR_CURRENT_VOLTAGE_COMPENSATION_TABLE_ARRAY_SIZE];
    float f_comp_i[MOTOR_CURRENT_VOLTAGE_COMPENSATION_TABLE_ARRAY_SIZE];
    float f_slope[MOTOR_CURRENT_VOLTAGE_COMPENSATION_SLOPE_ARRAY_SIZE];
    float f_intcept[MOTOR_CURRENT_VOLTAGE_COMPENSATION_SLOPE_ARRAY_SIZE];
    float f_volt_comp_array[MOTOR_CURRENT_VOLTAGE_COMPENSATION_PHASE_ARRAY_SIZE];
    float f_vdc;
    float f_volt_comp_limit;
    motor_current_voltage_compensation_select_t u1_volt_err_comp_enable;
} motor_currnt_voltage_compensation_t;

typedef struct st_motor_current_extended_cfg
{
    motor_current_control_type_t u1_control_type;                            ///< Control type

    motor_current_shunt_type_t shunt;                                        ///< Shunt type

    float f_comp_v[MOTOR_CURRENT_VOLTAGE_COMPENSATION_TABLE_ARRAY_SIZE];     ///< Voltage error compensation table of voltage
    float f_comp_i[MOTOR_CURRENT_VOLTAGE_COMPENSATION_TABLE_ARRAY_SIZE];     ///< Voltage error compensation table of current
    motor_current_voltage_compensation_select_t vcomp_enable;                ///< Enable/Disable select of voltage error compensation
    motor_current_sample_delay_compensation_t   u1_sample_delay_comp_enable; ///< Enable/Disable select of sample delay compensation
    float f_current_ctrl_period;                                             ///< Current control period [usec]
    float f_ilimit;                                                          ///< Current limit [A]

    motor_current_motor_parameter_t  * p_motor_parameter;                    ///< Motor parameters
    motor_current_design_parameter_t * p_design_parameter;                   ///< PI control designed parameters
} motor_current_extended_cfg_t;

typedef struct st_motor_current_instance_ctrl
{
    uint32_t open;

    uint8_t u1_active;                 ///< Flag to set active/inactive the current control
    float   f_vd_ref;                  ///< Reference d-axis voltage [V]
    float   f_vq_ref;                  ///< Reference q-axis voltage [V]
    float   f_id_ref;                  ///< Reference d-axis current [A]
    float   f_iq_ref;                  ///< Reference q-axis current [A]
    float   f_iu_ad;                   ///< U phase current [A]
    float   f_iv_ad;                   ///< V phase current [A]
    float   f_iw_ad;                   ///< W phase current [A]
    float   f_id_ad;                   ///< D-axis current [A]
    float   f_iq_ad;                   ///< Q-axis current [A]
    float   f_vdc_ad;                  ///< Main line voltage [V]
    float   f_speed_rad;               ///< Motor rotational speed [rad/s]
    float   f_rotor_angle;             ///< Motor rotor angle [radian] (Electrical)
    float   f_position_rad;            ///< Rotor position [radian] (Mechanical)
    float   f_refu;                    ///< U phase output reference Voltage [V]
    float   f_refv;                    ///< V phase output reference Voltage [V]
    float   f_refw;                    ///< W phase output reference Voltage [V]
    float   f_va_max;

    /* For Speed Control Interface (to Angle module) */
    float   f_ed;
    float   f_eq;
    float   f_phase_err;                          ///< Error of motor phase
    uint8_t u1_flag_crnt_offset;                  ///< Finish flag to measure current offset

    /* For induction sensor control */
    float f_sin_ad_data;                          ///< A/D converted data of induction sensor sin wave
    float f_cos_ad_data;                          ///< A/D converted data of induction sensor cos wave

    motor_current_cfg_t const * p_cfg;

    motor_current_pi_params_t st_pi_id;           ///< D-axis current PI controller
    motor_current_pi_params_t st_pi_iq;           ///< Q-axis current PI controller

    motor_currnt_voltage_compensation_t st_vcomp; ///< Data for voltage error compensation

    motor_current_input_t st_input;               ///< Data buffer from speed control

    motor_angle_instance_t const  * p_angle_instance;
    motor_driver_instance_t const * p_driver_instance;
} motor_current_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const motor_current_api_t g_motor_current_on_motor_current;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_Open(motor_current_ctrl_t * const p_ctrl, motor_current_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_CURRENT_Close(motor_current_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_CURRENT_Reset(motor_current_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_CURRENT_Run(motor_current_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_CURRENT_ParameterSet(motor_current_ctrl_t * const        p_ctrl,
                                        motor_current_input_t const * const p_st_input);

fsp_err_t RM_MOTOR_CURRENT_CurrentReferenceSet(motor_current_ctrl_t * const p_ctrl,
                                               float const                  id_reference,
                                               float const                  iq_reference);

fsp_err_t RM_MOTOR_CURRENT_SpeedPhaseSet(motor_current_ctrl_t * const p_ctrl,
                                         float const                  speed_rad,
                                         float const                  phase_rad);

fsp_err_t RM_MOTOR_CURRENT_CurrentSet(motor_current_ctrl_t * const                p_ctrl,
                                      motor_current_input_current_t const * const p_st_current,
                                      motor_current_input_voltage_t const * const p_st_voltage);

fsp_err_t RM_MOTOR_CURRENT_ParameterGet(motor_current_ctrl_t * const   p_ctrl,
                                        motor_current_output_t * const p_st_output);

fsp_err_t RM_MOTOR_CURRENT_CurrentGet(motor_current_ctrl_t * const p_ctrl, float * const p_id, float * const p_iq);

fsp_err_t RM_MOTOR_CURRENT_PhaseVoltageGet(motor_current_ctrl_t * const        p_ctrl,
                                           motor_current_get_voltage_t * const p_voltage);

fsp_err_t RM_MOTOR_CURRENT_ParameterUpdate(motor_current_ctrl_t * const      p_ctrl,
                                           motor_current_cfg_t const * const p_cfg);

void rm_motor_current_encoder_cyclic(motor_current_instance_t const * p_ctrl);
void rm_motor_current_encoder_angle_adjust(motor_current_instance_t const * p_ctrl);
void rm_motor_current_induction_cyclic(motor_current_instance_t const * p_ctrl);
void rm_motor_current_induction_angle_adjust(motor_current_instance_t const * p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_CURRENT_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_CURRENT)
 **********************************************************************************************************************/
