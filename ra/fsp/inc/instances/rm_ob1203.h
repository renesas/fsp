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
 * @addtogroup RM_OB1203
 * @{
 **********************************************************************************************************************/

#ifndef RM_OB1203_H
#define RM_OB1203_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_ob1203_api.h"
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "r_ob1203_rx_config.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include "r_ob1203_rl_config.h"
#else
 #include "rm_ob1203_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** OB1203 initialization process block */
typedef struct st_rm_ob1203_init_process_params
{
    volatile bool              communication_finished; ///< Communication flag for blocking.
    volatile rm_ob1203_event_t event;                  ///< Callback event
} rm_ob1203_init_process_params_t;

/** OB1203 mode extended configuration */
typedef struct st_rm_ob1203_mode_extended_cfg
{
    // Common
    rm_ob1203_api_t const    * p_api;                                  ///< Pointer to APIs.
    rm_ob1203_operation_mode_t mode_irq;                               ///< Operation mode using IRQ
    rm_ob1203_ppg_prox_gain_t  ppg_prox_gain;                          ///< Proximity gain range
    rm_ob1203_led_order_t      led_order;                              ///< LED order

    // Light mode
    rm_ob1203_light_sensor_mode_t      light_sensor_mode;              ///< LS or CS sensor mode
    rm_ob1203_light_interrupt_type_t   light_interrupt_type;           ///< Light mode interrupt type.
    rm_ob1203_light_interrupt_source_t light_interrupt_source;         ///< Light mode interrupt source.
    uint8_t light_interrupt_persist;                                   ///< The number of similar consecutive Light mode interrupt events that must occur before the interrupt is asserted (4bits).
    rm_ob1203_sleep_after_interrupt_t light_sleep;                     ///< Sleep after an interrupt.
    rm_ob1203_light_gain_t            light_gain;                      ///< Light gain range
    uint32_t light_upper_threshold;                                    ///< Upper threshold for interrupt
    uint32_t light_lower_threshold;                                    ///< Lower threshold for interrupt
    rm_ob1203_variance_threshold_t           light_variance_threshold; ///< variance threshold for interrupt.
    rm_ob1203_light_resolution_meas_period_t light_resolution_period;  ///< Resolution and measurement period.
    rm_ob1203_light_data_type_t              light_data_type;          ///< Light data type.

    // Proximity mode
    rm_ob1203_sleep_after_interrupt_t prox_sleep;                      ///< Sleep after an interrupt.
    rm_ob1203_prox_interrupt_type_t   prox_interrupt_type;             ///< Proximity mode interrupt type.
    uint8_t  prox_interrupt_persist;                                   ///< The number of similar consecutive Proximity mode interrupt events that must occur before the interrupt is asserted (4bits).
    uint16_t prox_led_current;                                         ///< Proximity LED current.
    rm_ob1203_analog_cancellation_t prox_ana_can;                      ///< Analog cancellation.
    uint16_t prox_dig_can;                                             ///< Digital cancellation.
    rm_ob1203_number_led_pulses_t prox_num_led_pulses;                 ///< Number of LED pulses.
    uint16_t prox_upper_threshold;                                     ///< Upper threshold for interrupt
    uint16_t prox_lower_threshold;                                     ///< Lower threshold for interrupt
    rm_ob1203_prox_pulse_width_meas_period_t prox_width_period;        ///< Proximity pulse width and measurement period.
    rm_ob1203_moving_average_t               prox_moving_average;      ///< Moving average.
    uint8_t prox_hysteresis;                                           ///< Proximity hysteresis threshold (7bits).

    // PPG mode
    rm_ob1203_ppg_sensor_mode_t    ppg_sensor_mode;                    ///< PPG1 or PPG2 sensor mode
    rm_ob1203_ppg_interrupt_type_t ppg_interrupt_type;                 ///< PPG mode interrupt type.
    uint16_t ppg_ir_led_current;                                       ///< PPG IR LED current.
    uint16_t ppg_red_led_current;                                      ///< PPG Red LED current.
    rm_ob1203_power_save_mode_t             ppg_power_save_mode;       ///< PPG power save mode
    rm_ob1203_analog_cancellation_t         ppg_ir_led_ana_can;        ///< IR LED analog cancellations
    rm_ob1203_analog_cancellation_t         ppg_red_led_ana_can;       ///< Red LED analog cancellations
    rm_ob1203_number_averaged_samples_t     ppg_num_averaged_samples;  ///< Number of averaged PPG samples.
    rm_ob1203_ppg_pulse_width_meas_period_t ppg_width_period;          ///< PPG pulse width and measurement period.
    rm_ob1203_fifo_rollover_t               ppg_fifo_rollover;         ///< FIFO rollover enable.
    uint8_t ppg_fifo_empty_num;                                        ///< the number of empty FIFO words when the FIFO almost full interrupt is issued. In PPG2 Mode only even values should be used. (4 bits)
    uint8_t ppg_number_of_samples;                                     ///< Number of PPG samples
} rm_ob1203_mode_extended_cfg_t;

/** OB1203 Control Block */
typedef struct rm_ob1203_instance_ctrl
{
#if BSP_CFG_RTOS
    rm_ob1203_semaphore_t const * p_semaphore;                     ///< The semaphore to wait for callback. This is used for another data read/write after a communication
#endif
    uint32_t                             open;                     ///< Open flag
    rm_ob1203_cfg_t const              * p_cfg;                    ///< Pointer to OB1203 Configuration
    uint8_t                              buf[8];                   ///< Buffer for I2C communications
    rm_ob1203_init_process_params_t      init_process_params;      ///< For the initialization process.
    uint8_t                              register_address;         ///< Register address to access
    volatile rm_ob1203_device_status_t * p_device_status;          ///< Pointer to device status.
    volatile rm_ob1203_fifo_info_t     * p_fifo_info;              ///< Pointer to FIFO information structure.
    volatile bool                        fifo_reset;               ///< Flag for FIFO reset for PPG mode
    volatile bool                        prox_gain_update;         ///< Flag for gain update for Proximity mode
    volatile bool                        interrupt_bits_clear;     ///< Flag for clearing interrupt bits.
    rm_comms_instance_t const          * p_comms_i2c_instance;     ///< Pointer of I2C Communications Middleware instance structure
    rm_ob1203_mode_extended_cfg_t      * p_mode;                   ///< Pointer of OB1203 operation mode extended configuration
    void const                         * p_irq_instance;           ///< Pointer to IRQ instance.
    void const                         * p_context;                ///< Pointer to the user-provided context

    /* Pointer to callback and optional working memory */
    void (* p_comms_callback)(rm_ob1203_callback_args_t * p_args); ///< I2C Communications callback
    void (* p_irq_callback)(rm_ob1203_callback_args_t * p_args);   ///< IRQ callback
} rm_ob1203_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern rm_ob1203_api_t const g_ob1203_on_ob1203;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_Open(rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_cfg_t const * const p_cfg);
fsp_err_t RM_OB1203_Close(rm_ob1203_ctrl_t * const p_api_ctrl);
fsp_err_t RM_OB1203_MeasurementStart(rm_ob1203_ctrl_t * const p_api_ctrl);
fsp_err_t RM_OB1203_MeasurementStop(rm_ob1203_ctrl_t * const p_api_ctrl);
fsp_err_t RM_OB1203_LightRead(rm_ob1203_ctrl_t * const     p_api_ctrl,
                              rm_ob1203_raw_data_t * const p_raw_data,
                              rm_ob1203_light_data_type_t  type);
fsp_err_t RM_OB1203_LightDataCalculate(rm_ob1203_ctrl_t * const       p_api_ctrl,
                                       rm_ob1203_raw_data_t * const   p_raw_data,
                                       rm_ob1203_light_data_t * const p_ob1203_data);
fsp_err_t RM_OB1203_ProxRead(rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_raw_data_t * const p_raw_data);
fsp_err_t RM_OB1203_ProxDataCalculate(rm_ob1203_ctrl_t * const      p_api_ctrl,
                                      rm_ob1203_raw_data_t * const  p_raw_data,
                                      rm_ob1203_prox_data_t * const p_ob1203_data);
fsp_err_t RM_OB1203_PpgRead(rm_ob1203_ctrl_t * const     p_api_ctrl,
                            rm_ob1203_raw_data_t * const p_raw_data,
                            uint8_t const                number_of_samples);
fsp_err_t RM_OB1203_PpgDataCalculate(rm_ob1203_ctrl_t * const     p_api_ctrl,
                                     rm_ob1203_raw_data_t * const p_raw_data,
                                     rm_ob1203_ppg_data_t * const p_ob1203_data);
fsp_err_t RM_OB1203_GainSet(rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_gain_t const gain);
fsp_err_t RM_OB1203_LedCurrentSet(rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_led_current_t const led_current);
fsp_err_t RM_OB1203_DeviceInterruptCfgSet(rm_ob1203_ctrl_t * const               p_api_ctrl,
                                          rm_ob1203_device_interrupt_cfg_t const interrupt_cfg);
fsp_err_t RM_OB1203_FifoInfoGet(rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_fifo_info_t * const p_fifo_info);
fsp_err_t RM_OB1203_DeviceStatusGet(rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_device_status_t * const p_status);

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_OB1203_H_*/

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_OB1203)
 **********************************************************************************************************************/
