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

/* Modulation type selection */
typedef enum  e_motor_driver_modulation_method
{
    MOTOR_DRIVER_MODULATION_METHOD_SPWM,  ///< Sinusoidal pulse-width-modulation
    MOTOR_DRIVER_MODULATION_METHOD_SVPWM, ///< Space vector pulse-width-modulation
} motor_driver_modulation_method_t;

/* For 1shunt phase detection */
typedef enum  e_motor_driver_phase
{
    MOTOR_DRIVER_PHASE_U_PHASE = 1,
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

typedef struct st_motor_driver_extended_cfg
{
    uint16_t u2_pwm_timer_freq;                         ///< PWM timer frequency [MHz]
    uint16_t u2_pwm_carrier_freq;                       ///< PWM carrier frequency [kHz]
    uint16_t u2_deadtime;                               ///< PWM deadtime [usec]

    float f_current_range;                              ///< A/D current measure range (max current) [A]
    float f_vdc_range;                                  ///< A/D main line voltage measure range (max voltage) [V]
    float f_ad_resolution;                              ///< A/D resolution
    float f_ad_current_offset;                          ///< A/D offset (Center value)
    float f_ad_voltage_conversion;                      ///< A/D conversion level

    uint16_t u2_offset_calc_count;                      ///< Calculation counts for current offset

    motor_driver_modulation_method_t modulation_method; ///< Modulation method

    /* PWM output port */
    bsp_io_port_pin_t port_up;                          ///< PWM output port UP
    bsp_io_port_pin_t port_un;                          ///< PWM output port UN
    bsp_io_port_pin_t port_vp;                          ///< PWM output port VP
    bsp_io_port_pin_t port_vn;                          ///< PWM output port VN
    bsp_io_port_pin_t port_wp;                          ///< PWM output port WP
    bsp_io_port_pin_t port_wn;                          ///< PWM output port WN

    /* For 1shunt */
    float   f_ad_current_adjust;                        ///< Adjustment value for 1shunt A/D current
    int32_t s4_difference_minimum;                      ///< Minimum difference of PWM duty
    int32_t s4_adjust_adc_delay;                        ///< Adjustment delay for A/D conversion

    motor_driver_modulation_t mod_param;
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

    motor_driver_modulation_t  st_modulation;
    motor_driver_cfg_t const * p_cfg;

    /* For ADC callback */
    adc_callback_args_t adc_callback_args;     ///< For call ADC callbackSet function

    /* For GPT(Timer) callback */
    timer_callback_args_t timer_callback_args; ///< For call GPT(Timer) callbackSet function
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
