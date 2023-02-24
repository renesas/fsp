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
 * @addtogroup MOTOR_120_DRIVER
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_120_DRIVER_H
#define RM_MOTOR_120_DRIVER_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_adc_api.h"
#include "r_three_phase_api.h"
#include "rm_motor_120_driver_cfg.h"
#include "rm_motor_120_driver_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** 120 driver active flag */
typedef enum  e_motor_120_driver_status
{
    MOTOR_120_DRIVER_STATUS_INACTIVE = 0, ///< 120 driver status inactive
    MOTOR_120_DRIVER_STATUS_ACTIVE   = 1  ///< 120 driver status active
} motor_120_driver_status_t;

/** 120 degree control type */
typedef enum  e_motor_120_driver_type
{
    MOTOR_120_DRIVER_TYPE_SENSORLESS = 0, ///< 120 degree sensorless control
    MOTOR_120_DRIVER_TYPE_HALL       = 1  ///< 120 degree hall control
} motor_120_driver_type_t;

/** Modulation parameter */
typedef struct st_motor_120_driver_modulation
{
    float f4_vdc;                      ///< Main line voltage (Vdc) (V)
    float f4_max_duty;                 ///< Maximum duty cycle
    float f4_min_duty;                 ///< Minimum duty cycle
    float f4_neutral_duty;             ///< Duty cycle that represents 0 (V)
} motor_120_driver_modulation_t;

/** Extended configurations for motor 120 driver */
typedef struct st_motor_120_driver_extended_cfg
{
    adc_instance_t const         * p_adc_instance;         ///< ADC module instance
    three_phase_instance_t const * p_three_phase_instance; ///< PWM output module instance (GPT three phase)

    motor_120_driver_type_t motor_120_type;                ///< 120 degree control type

    adc_channel_t iu_ad_ch;                                ///< A/D channel for U phase current
    adc_channel_t iw_ad_ch;                                ///< A/D channel for W phase current
    adc_channel_t vdc_ad_ch;                               ///< A/D channel for main line voltage
    adc_channel_t vu_ad_ch;                                ///< A/D channel for U phase voltage
    adc_channel_t vv_ad_ch;                                ///< A/D channel for V phase voltage
    adc_channel_t vw_ad_ch;                                ///< A/D channel for W phase voltage

    bsp_io_port_pin_t port_up;                             ///< PWM output port UP
    bsp_io_port_pin_t port_un;                             ///< PWM output port UN
    bsp_io_port_pin_t port_vp;                             ///< PWM output port VP
    bsp_io_port_pin_t port_vn;                             ///< PWM output port VN
    bsp_io_port_pin_t port_wp;                             ///< PWM output port WP
    bsp_io_port_pin_t port_wn;                             ///< PWM output port WN

    uint32_t u4_pwm_timer_freq;                            ///< PWM timer frequency (MHz)
    uint32_t u4_pwm_carrier_freq;                          ///< PWM carrier frequency (kHz)
    uint32_t u4_deadtime;                                  ///< PWM deadtime (usec)

    float f_current_range;                                 ///< A/D current measure range (max current) (A)
    float f_vdc_range;                                     ///< A/D main line voltage measure range (max voltage) (V)
    float f_ad_resolution;                                 ///< A/D resolution
    float f_ad_current_offset;                             ///< A/D offset (Center value)
    float f_ad_voltage_conversion;                         ///< A/D conversion level

    uint32_t u4_offset_calc_count;                         ///< Calculation counts for current offset

    motor_120_driver_modulation_t mod_param;               ///< Modulation parameter
} motor_120_driver_extended_cfg_t;

typedef struct st_motor_120_driver_instance_ctrl
{
    uint32_t open;                                           ///< Used to determine if the channel is configured

    motor_120_driver_status_t u1_active;                     ///< Flag to set active/inactive the driver control

    uint32_t u4_carrier_base;                                ///< PWM carrier base counts
    uint32_t u4_deadtime_count;                              ///< Deadtime counts

    float f_iu_ad;                                           ///< U phase current (A)
    float f_iw_ad;                                           ///< W phase current (A)
    float f_vdc_ad;                                          ///< Main line voltage (V)
    float f_refu;                                            ///< Calculated U phase output voltage (V)
    float f_refv;                                            ///< Calculated V phase output voltage (V)
    float f_refw;                                            ///< Calculated W phase output voltage (V)
    float f_vu_ad;                                           ///< U phase voltage (V)
    float f_vv_ad;                                           ///< V phase voltage (V)
    float f_vw_ad;                                           ///< W phase voltage (V)

    /* for current offset calculation */
    motor_120_driver_flag_offset_calc_t u1_flag_offset_calc; ///< The flag represents that the offset measurement is finished
    uint32_t u4_offset_calc_times;                           ///< Calculation times for current offset
    float    f_offset_iu;                                    ///< U phase current offset value (A)
    float    f_offset_iw;                                    ///< W phase current offset value (A)
    float    f_sum_iu_ad;                                    ///< U phase current summation value to calculate offset (A)
    float    f_sum_iw_ad;                                    ///< W phase current summation value to calculate offset (A)
    float    f_offset_vu;                                    ///< U phase voltage offset value (V)
    float    f_offset_vv;                                    ///< V phase voltage offset value (V)
    float    f_offset_vw;                                    ///< W phase voltage offset value (V)
    float    f_offset_off_vu;                                ///< U phase off voltage offset value (V)
    float    f_offset_off_vv;                                ///< V phase off voltage offset value (V)
    float    f_offset_off_vw;                                ///< W phase off voltage offset value (V)
    float    f_sum_vu_ad;                                    ///< U phase voltage summation value to calculate offset (V)
    float    f_sum_vv_ad;                                    ///< V phase voltage summation value to calculate offset (V)
    float    f_sum_vw_ad;                                    ///< W phase voltage summation value to calculate offset (V)

    uint32_t u4_gtioca_general_low_cfg;                      ///< I/O port "Low" config for gtioca general functions
    uint32_t u4_gtioca_general_high_cfg;                     ///< I/O port "High" config for gtioca general functions
    uint32_t u4_gtioca_periheral_low_cfg;                    ///< I/O port "Low" config for gtioca periheral functions
    uint32_t u4_gtioca_periheral_high_cfg;                   ///< I/O port "High" config for gtioca periheral functions
    uint32_t u4_gtiocb_general_low_cfg;                      ///< I/O port "Low" config for gtioca general functions
    uint32_t u4_gtiocb_general_high_cfg;                     ///< I/O port "High" config for gtioca general functions
    uint32_t u4_gtiocb_periheral_low_cfg;                    ///< I/O port "Low" config for gtioca periheral functions
    uint32_t u4_gtiocb_periheral_high_cfg;                   ///< I/O port "High" config for gtioca periheral functions

    motor_120_driver_modulation_t  st_modulation;            ///< Modulation paramter
    motor_120_driver_cfg_t const * p_cfg;                    ///< Pointer of configuration structure

    /* For ADC callback */
    adc_callback_args_t   adc_callback_args;                 ///< For call ADC callbackSet function
    timer_callback_args_t timer_callback_args;               ///< For call timer callbackSet function
} motor_120_driver_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in interface API structure for this instance. */
extern const motor_120_driver_api_t g_motor_120_driver_on_motor_120_driver;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_Open(motor_120_driver_ctrl_t * const p_ctrl, motor_120_driver_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_120_DRIVER_Close(motor_120_driver_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_DRIVER_Run(motor_120_driver_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_DRIVER_Stop(motor_120_driver_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_DRIVER_Reset(motor_120_driver_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_DRIVER_PhaseVoltageSet(motor_120_driver_ctrl_t * const p_ctrl,
                                              float const                     u_voltage,
                                              float const                     v_voltage,
                                              float const                     w_voltage);

fsp_err_t RM_MOTOR_120_DRIVER_PhasePatternSet(motor_120_driver_ctrl_t * const        p_ctrl,
                                              motor_120_driver_phase_pattern_t const pattern);

fsp_err_t RM_MOTOR_120_DRIVER_CurrentGet(motor_120_driver_ctrl_t * const           p_ctrl,
                                         motor_120_driver_current_status_t * const p_current_status);

fsp_err_t RM_MOTOR_120_DRIVER_CurrentOffsetCalc(motor_120_driver_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_DRIVER_FlagCurrentOffsetGet(motor_120_driver_ctrl_t * const             p_ctrl,
                                                   motor_120_driver_flag_offset_calc_t * const p_flag_offset);

fsp_err_t RM_MOTOR_120_DRIVER_ParameterUpdate(motor_120_driver_ctrl_t * const      p_ctrl,
                                              motor_120_driver_cfg_t const * const p_cfg);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_120_DRIVER_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_120_DRIVER)
 **********************************************************************************************************************/
