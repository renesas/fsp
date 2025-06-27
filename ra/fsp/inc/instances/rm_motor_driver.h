/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_DRIVER
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_DRIVER_H
#define RM_MOTOR_DRIVER_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#include "rm_motor_driver_cfg.h"
#include "rm_motor_driver_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Support two ADC instance valid for adc */
typedef enum e_motor_driver_select_adc_instance
{
    MOTOR_DRIVER_SELECT_ADC_INSTANCE_FIRST = 0, ///< Use first ADC instance
    MOTOR_DRIVER_SELECT_ADC_INSTANCE_SECOND,    ///< Use second ADC instance
} motor_driver_select_adc_instance_t;

/* Modulation type selection */
typedef enum  e_motor_driver_modulation_method
{
    MOTOR_DRIVER_MODULATION_METHOD_SPWM,  ///< Sinusoidal pulse-width-modulation
    MOTOR_DRIVER_MODULATION_METHOD_SVPWM, ///< Space vector pulse-width-modulation
} motor_driver_modulation_method_t;

/* For 1shunt phase detection */
typedef enum  e_motor_driver_phase
{
    MOTOR_DRIVER_PHASE_U_PHASE = 0,
    MOTOR_DRIVER_PHASE_V_PHASE,
    MOTOR_DRIVER_PHASE_W_PHASE,
} motor_driver_phase_t;

typedef struct st_motor_driver_modulation
{
    float   f4_vdc;                    ///< Main line voltage (Vdc) [V]
    float   f4_1_div_vdc;              ///< 1/Vdc (Inverse Vdc for calculation)
    float   f4_voltage_error_ratio;    ///< The voltage error ratio (VoltageError/Vdc)
    float   f4_max_duty;               ///< Maximum duty cycle
    float   f4_min_duty;               ///< Minimum duty cycle
    float   f4_neutral_duty;           ///< Duty cycle that represents 0[V]
    uint8_t u1_sat_flag;               ///< Saturation flag
} motor_driver_modulation_t;

/** For multiple motor */
typedef struct st_motor_driver_shared_instance_ctrl
{
    uint32_t open;
    uint8_t  registered_motor_count;   ///< Registered motor counts
    void   * p_context[MOTOR_DRIVER_CFG_SUPPORT_MOTOR_NUM];
} motor_driver_shared_instance_ctrl_t;

/** For multiple motor */
typedef struct st_motor_driver_extended_shared_cfg
{
    adc_instance_t const * p_adc_instance_first;  ///< first ADC instance
    adc_instance_t const * p_adc_instance_second; ///< second ADC instance

    motor_driver_shared_instance_ctrl_t * const p_shared_instance_ctrl;
} motor_driver_extended_shared_cfg_t;

typedef struct st_motor_driver_extended_cfg
{
    uint16_t u2_pwm_timer_freq;                               ///< PWM timer frequency [MHz]
    float    pwm_carrier_freq;                                ///< PWM carrier frequency [kHz]
    uint16_t u2_deadtime;                                     ///< PWM deadtime [usec]

    float f_current_range;                                    ///< A/D current measure range (max current) [A]
    float f_vdc_range;                                        ///< A/D main line voltage measure range (max voltage) [V]
    float f_ad_resolution;                                    ///< A/D resolution
    float f_ad_current_offset;                                ///< A/D offset (Center value)
    float f_ad_voltage_conversion;                            ///< A/D conversion level

    uint16_t u2_offset_calc_count;                            ///< Calculation counts for current offset

    motor_driver_modulation_method_t modulation_method;       ///< Modulation method

    /* PWM output port */
    bsp_io_port_pin_t port_up;                                ///< PWM output port UP
    bsp_io_port_pin_t port_un;                                ///< PWM output port UN
    bsp_io_port_pin_t port_vp;                                ///< PWM output port VP
    bsp_io_port_pin_t port_vn;                                ///< PWM output port VN
    bsp_io_port_pin_t port_wp;                                ///< PWM output port WP
    bsp_io_port_pin_t port_wn;                                ///< PWM output port WN

    /* For 1shunt */
    float                f_ad_current_adjust;                 ///< Adjustment value for 1shunt A/D current
    int32_t              s4_difference_minimum;               ///< Minimum difference of PWM duty
    int32_t              s4_adjust_adc_delay;                 ///< Adjustment delay for A/D conversion
    motor_driver_phase_t trigger_phase;                       ///< trigger phase of interrupt to get 1shunt current

    /* For multiple motor */
    adc_group_mask_t adc_group;                               ///< Used ADC scan group only valid for adc_b

    /* Channel assignment */
    uint8_t iu_ad_unit;                                       ///< Used A/D unit number for U phase current
    uint8_t iv_ad_unit;                                       ///< Used A/D unit number for V phase current
    uint8_t iw_ad_unit;                                       ///< Used A/D unit number for W phase current
    uint8_t vdc_ad_unit;                                      ///< Used A/D unit number for main line voltage
    uint8_t sin_ad_unit;                                      ///< Used A/D unit number for sin signal of induction sensor
    uint8_t cos_ad_unit;                                      ///< Used A/D unit number for cos signal of induction sensor

    motor_driver_modulation_t mod_param;

    motor_driver_select_adc_instance_t         interrupt_adc; ///< Select which interrupt to use
    motor_driver_extended_shared_cfg_t const * p_shared_cfg;  ///< Shared extended config
} motor_driver_extended_cfg_t;

typedef struct st_motor_driver_instance_ctrl
{
    uint32_t open;

    uint16_t u2_carrier_base;          ///< PWM carrier base counts
    uint16_t u2_deadtime_count;        ///< Deadtime counts

    float f_iu_ad;                     ///< U phase current [A]
    float f_iv_ad;                     ///< V phase current [A]
    float f_iw_ad;                     ///< W phase current [A]
    float f_vdc_ad;                    ///< Main line voltage [V]

    float f_sin_ad;                    ///< Sin signal output of induction sensor [V]
    float f_cos_ad;                    ///< Cos signal output of induction sensor [V]

    float f_refu;                      ///< Calculated U Phase output voltage [V]
    float f_refv;                      ///< Calculated V Phase output voltage [V]
    float f_refw;                      ///< Calculated W Phase output voltage [V]

    /* for current offset calculation */
    uint8_t  u1_flag_offset_calc;      ///< The flag represents that the offset measurement is finished
    uint16_t u2_offset_calc_times;     ///< Calculation times for current offset
    float    f_offset_iu;              ///< U phase current offset value [A]
    float    f_offset_iv;              ///< V phase current offset value [A]
    float    f_offset_iw;              ///< W phase current offset value [A]
    float    f_sum_iu_ad;              ///< U phase current summation value to calculate offset [A]
    float    f_sum_iv_ad;              ///< V phase current summation value to calculate offset [A]
    float    f_sum_iw_ad;              ///< W phase current summation value to calculate offset [A]

    /* for 1shunt current calculation */
    motor_driver_phase_t min_phase;    ///< Minimum phase information to calculate 1shunt current
    motor_driver_phase_t mid_phase;    ///< Middle phase information to calculate 1shunt current

    /* Port configuration */
    uint32_t u4_gtioca_low_cfg;        ///< I/O port "Low" config for gtioca
    uint32_t u4_gtiocb_low_cfg;        ///< I/O port "Low" config for gtioca
    uint8_t  u1_flag_port_enable;      ///< The flag represents that PWM port should be enabled.

    motor_driver_modulation_t  st_modulation;
    motor_driver_cfg_t const * p_cfg;

    /* For ADC callback */
    adc_callback_args_t adc_callback_args;     ///< For call ADC callbackSet function

    /* For GPT(Timer) callback */
    timer_callback_args_t timer_callback_args; ///< For call GPT(Timer) callbackSet function

    /* Shared ADC */
    motor_driver_shared_instance_ctrl_t * p_shared_instance_ctrl;
} motor_driver_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const motor_driver_api_t g_motor_driver_on_motor_driver;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_DRIVER_Open(motor_driver_ctrl_t * const p_ctrl, motor_driver_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_DRIVER_Close(motor_driver_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_DRIVER_Reset(motor_driver_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_DRIVER_PhaseVoltageSet(motor_driver_ctrl_t * const p_ctrl,
                                          float const                 u_voltage,
                                          float const                 v_voltage,
                                          float const                 w_voltage);

fsp_err_t RM_MOTOR_DRIVER_CurrentGet(motor_driver_ctrl_t * const        p_ctrl,
                                     motor_driver_current_get_t * const p_current_get);

fsp_err_t RM_MOTOR_DRIVER_FlagCurrentOffsetGet(motor_driver_ctrl_t * const p_ctrl, uint8_t * const p_flag_offset);

fsp_err_t RM_MOTOR_DRIVER_CurrentOffsetRestart(motor_driver_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_DRIVER_ParameterUpdate(motor_driver_ctrl_t * const p_ctrl, motor_driver_cfg_t const * const p_cfg);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_DRIVER_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_DRIVER)
 **********************************************************************************************************************/
