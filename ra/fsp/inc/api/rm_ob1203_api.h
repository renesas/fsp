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
 * @ingroup RENESAS_INTERFACES
 * @defgroup RM_OB1203_API OB1203 Middleware Interface
 * @brief Interface for OB1203 Middleware functions.
 *
 * @section RM_OB1203_API_Summary Summary
 * The OB1203 interface provides OB1203 functionality.
 *
 * The OB1203 interface can be implemented by:
 * - @ref RM_OB1203
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_OB1203_API_H_
#define RM_OB1203_API_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include <string.h>
 #include "platform.h"
 #if BSP_CFG_RTOS_USED == 1            // FreeRTOS
  #include    "FreeRTOS.h"
  #include    "task.h"
  #include    "queue.h"
  #include    "semphr.h"
  #define BSP_CFG_RTOS    2
 #elif BSP_CFG_RTOS_USED == 5          // ThreadX
  #define BSP_CFG_RTOS    1
 #else
  #define BSP_CFG_RTOS    0
 #endif
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include <string.h>
 #include "r_cg_macrodriver.h"
 #include "r_fsp_error.h"
#else
 #include "bsp_api.h"
 #include "r_external_irq_api.h"
 #if BSP_CFG_RTOS == 1                 // ThreadX
  #include    "tx_api.h"
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
  #include    "FreeRTOS.h"
  #include    "task.h"
  #include    "queue.h"
  #include    "semphr.h"
 #endif
#endif

#include "rm_comms_api.h"

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Event in the callback function */
typedef enum e_rm_ob1203_event
{
    RM_OB1203_EVENT_SUCCESS = 0,
    RM_OB1203_EVENT_ERROR,
    RM_OB1203_EVENT_MEASUREMENT_COMPLETE,
    RM_OB1203_EVENT_OBJECT_NEAR,
    RM_OB1203_EVENT_THRESHOLD_CROSSED,
} rm_ob1203_event_t;

/** Operation mode of OB1203 */
typedef enum e_rm_ob1203_operation_mode
{
    RM_OB1203_OPERATION_MODE_STANDBY = 0, ///< Standby
    RM_OB1203_OPERATION_MODE_LIGHT,       ///< Light mode
    RM_OB1203_OPERATION_MODE_PROXIMITY,   ///< Proximity mode
    RM_OB1203_OPERATION_MODE_PPG,         ///< PPG mode
} rm_ob1203_operation_mode_t;

/** Light sensor mode of OB1203 */
typedef enum e_rm_ob1203_light_sensor_mode
{
    RM_OB1203_LIGHT_SENSOR_MODE_LS = 0x00, ///< Light sensor LS mode (Green, Clear, Comp)
    RM_OB1203_LIGHT_SENSOR_MODE_CS = 0x02, ///< Light sensor CS mode (Red, Green, Blue, Clear, Comp)
} rm_ob1203_light_sensor_mode_t;

/** PPG sensor mode of OB1203 */
typedef enum e_rm_ob1203_ppg_sensor_mode
{
    RM_OB1203_PPG_SENSOR_MODE_PPG1 = 0x02, ///< PPG sensor PPG1 mode
    RM_OB1203_PPG_SENSOR_MODE_PPG2 = 0x04, ///< PPG sensor PPG2 mode
} rm_ob1203_ppg_sensor_mode_t;

/** Data type of Light */
typedef enum e_rm_ob1203_light_data_type
{
    RM_OB1203_LIGHT_DATA_TYPE_ALL = 0, ///< Common
    RM_OB1203_LIGHT_DATA_TYPE_CLEAR,   ///< Common
    RM_OB1203_LIGHT_DATA_TYPE_GREEN,   ///< Common
    RM_OB1203_LIGHT_DATA_TYPE_BLUE,    ///< CS mode only
    RM_OB1203_LIGHT_DATA_TYPE_RED,     ///< CS mode only
    RM_OB1203_LIGHT_DATA_TYPE_COMP,    ///< Common. Temperature compensation data.
} rm_ob1203_light_data_type_t;

/** Light gain range. Gain scales the ADC output and noise */
typedef enum e_rm_ob1203_light_gain
{
    RM_OB1203_LIGHT_GAIN_1 = 0x00,     ///< Gain mode 1.
    RM_OB1203_LIGHT_GAIN_3 = 0x01,     ///< Gain mode 3.
    RM_OB1203_LIGHT_GAIN_6 = 0x02,     ///< Gain mode 6.
} rm_ob1203_light_gain_t;

/** PPG and proximity gain range. Gain scales the ADC output and noise */
typedef enum e_rm_ob1203_ppg_prox_gain
{
    RM_OB1203_PPG_PROX_GAIN_1   = 0x00, ///< Gain mode 1.
    RM_OB1203_PPG_PROX_GAIN_1P5 = 0x10, ///< Gain mode 1.5.
    RM_OB1203_PPG_PROX_GAIN_2   = 0x20, ///< Gain mode 2.
    RM_OB1203_PPG_PROX_GAIN_4   = 0x30, ///< Gain mode 4.
} rm_ob1203_ppg_prox_gain_t;

/** LED order. Controls which LED is activated (PS, PPG1) or in which order the LEDs are activated (PPG2) */
typedef enum e_rm_ob1203_led_order
{
    RM_OB1203_LED_IR_FIRST_RED_SECOND = 0x00, ///< First LED : IR LED, second LED : red LED.
    RM_OB1203_LED_RED_FIRST_IR_SECOND = 0x08, ///< First LED : red LED, second LED : IR LED.
} rm_ob1203_led_order_t;

/** Light interrupt type */
typedef enum e_rm_ob1203_light_interrupt_type
{
    RM_OB1203_LIGHT_INTERRUPT_TYPE_THRESHOLD = 0x00, ///< Light threshold interrupt.
    RM_OB1203_LIGHT_INTERRUPT_TYPE_VARIATION = 0x02, ///< Light variation interrupt.
} rm_ob1203_light_interrupt_type_t;

/** Light interrupt source */
typedef enum e_rm_ob1203_light_interrupt_source
{
    RM_OB1203_LIGHT_INTERRUPT_SOURCE_CLEAR_CHANNEL = 0x00, ///< Clear channel.
    RM_OB1203_LIGHT_INTERRUPT_SOURCE_GREEN_CHANNEL = 0x10, ///< Green channel.
    RM_OB1203_LIGHT_INTERRUPT_SOURCE_RED_CHANNEL   = 0x20, ///< Red channel. CS mode only.
    RM_OB1203_LIGHT_INTERRUPT_SOURCE_BLUE_CHANNEL  = 0x30, ///< Blue channel. CS mode only.
} rm_ob1203_light_interrupt_source_t;

/** Proximity interrupt type */
typedef enum e_rm_ob1203_prox_interrupt_type
{
    RM_OB1203_PROX_INTERRUPT_TYPE_NORMAL = 0x00, ///< Proximity normal interrupt.
    RM_OB1203_PROX_INTERRUPT_TYPE_LOGIC  = 0x02, ///< Proximity logic output interrupt.
} rm_ob1203_prox_interrupt_type_t;

/** PPG interrupt type */
typedef enum e_rm_ob1203_ppg_interrupt_type
{
    RM_OB1203_PPG_INTERRUPT_TYPE_DATA       = 0x10, ///< PPG data interrupt.
    RM_OB1203_PPG_INTERRUPT_TYPE_FIFO_AFULL = 0x20, ///< PPG FIFO almost full interrupt.
} rm_ob1203_ppg_interrupt_type_t;

/** Variance threshold */
typedef enum e_rm_ob1203_variance_threshold
{
    RM_OB1203_VARIANCE_THRESHOLD_8_COUNTS    = 0x00, ///< New LS_DATA varies by ± 8 counts compared to previous result.
    RM_OB1203_VARIANCE_THRESHOLD_16_COUNTS   = 0x01, ///< New LS_DATA varies by ± 16 counts compared to previous result.
    RM_OB1203_VARIANCE_THRESHOLD_32_COUNTS   = 0x02, ///< New LS_DATA varies by ± 32 counts compared to previous result.
    RM_OB1203_VARIANCE_THRESHOLD_64_COUNTS   = 0x03, ///< New LS_DATA varies by ± 64 counts compared to previous result.
    RM_OB1203_VARIANCE_THRESHOLD_128_COUNTS  = 0x04, ///< New LS_DATA varies by ± 128 counts compared to previous result.
    RM_OB1203_VARIANCE_THRESHOLD_256_COUNTS  = 0x05, ///< New LS_DATA varies by ± 256 counts compared to previous result.
    RM_OB1203_VARIANCE_THRESHOLD_512_COUNTS  = 0x06, ///< New LS_DATA varies by ± 512 counts compared to previous result.
    RM_OB1203_VARIANCE_THRESHOLD_1024_COUNTS = 0x07, ///< New LS_DATA varies by ± 1024 counts compared to previous result.
} rm_ob1203_variance_threshold_t;

/** Sleep after interrupt */
typedef enum e_rm_ob1203_sleep_after_interrupt
{
    RM_OB1203_SLEEP_AFTER_INTERRUPT_DISABLE = 0x00, ///< Disable sleep after interrupt.
    RM_OB1203_SLEEP_AFTER_INTERRUPT_ENABLE  = 0x08, ///< Stop measurement after an interrupt occurs. After STATUS_0/STATUS_1 register is read, start measurement.
} rm_ob1203_sleep_after_interrupt_t;

/** Moving average */
typedef enum e_rm_ob1203_moving_average
{
    RM_OB1203_MOVING_AVERAGE_DISABLE = 0x00, ///< Moving average is disabled for Proximity mode
    RM_OB1203_MOVING_AVERAGE_ENABLE  = 0x80, ///< Moving average is enabled for Proximity mode. Proximity data is the average of the current and previous measurement. The moving average is applied after digital offset cancellation.
} rm_ob1203_moving_average_t;

/** Power save mode */
typedef enum e_rm_ob1203_power_save_mode
{
    RM_OB1203_POWER_SAVE_MODE_DISABLE = 0x00, ///< Power save mode is disabled for PPG mode.
    RM_OB1203_POWER_SAVE_MODE_ENABLE  = 0x40, ///< Power save mode is enabled for PPG mode. On power save mode, some analog circuitry powers down between individual PPG measurements if the idle time.
} rm_ob1203_power_save_mode_t;

/** Analog cancellation */
typedef enum e_rm_ob1203_analog_cancellation
{
    RM_OB1203_ANALOG_CANCELLATION_DISABLE = 0x00, ///< No offset cancellation
    RM_OB1203_ANALOG_CANCELLATION_ENABLE  = 0x01, ///< 50% offset of the full-scale value
} rm_ob1203_analog_cancellation_t;

/** Number of LED pulses */
typedef enum e_rm_rm_ob1203_number_led_pulses
{
    RM_OB1203_NUM_LED_PULSES_1  = 0x00, ///< 1 pulse.
    RM_OB1203_NUM_LED_PULSES_2  = 0x08, ///< 2 pulses.
    RM_OB1203_NUM_LED_PULSES_4  = 0x10, ///< 4 pulses.
    RM_OB1203_NUM_LED_PULSES_8  = 0x18, ///< 8 pulses.
    RM_OB1203_NUM_LED_PULSES_16 = 0x20, ///< 16 pulses.
    RM_OB1203_NUM_LED_PULSES_32 = 0x28, ///< 32 pulses.
} rm_ob1203_number_led_pulses_t;

/** Number of averaged samples */
typedef enum e_rm_ob1203_number_averaged_samples
{
    RM_OB1203_NUM_AVERAGED_SAMPLES_1  = 0x00, ///< 1 (No averaging).
    RM_OB1203_NUM_AVERAGED_SAMPLES_2  = 0x10, ///< 2 consecutives samples are averaged.
    RM_OB1203_NUM_AVERAGED_SAMPLES_4  = 0x20, ///< 4 consecutives samples are averaged.
    RM_OB1203_NUM_AVERAGED_SAMPLES_8  = 0x30, ///< 8 consecutives samples are averaged.
    RM_OB1203_NUM_AVERAGED_SAMPLES_16 = 0x40, ///< 16 consecutives samples are averaged.
    RM_OB1203_NUM_AVERAGED_SAMPLES_32 = 0x50, ///< 32 consecutives samples are averaged.
} rm_ob1203_number_averaged_samples_t;

/** Light resolution and measurement period  */
typedef enum e_rm_ob1203_light_resolution_meas_period
{
    RM_OB1203_LIGHT_RESOLUTION_13BIT_PERIOD_25MS   = 0x50, ///< Resolution : 13bit, measurement period : 25ms.
    RM_OB1203_LIGHT_RESOLUTION_13BIT_PERIOD_50MS   = 0x51, ///< Resolution : 13bit, measurement period : 50ms.
    RM_OB1203_LIGHT_RESOLUTION_13BIT_PERIOD_100MS  = 0x52, ///< Resolution : 13bit, measurement period : 100ms.
    RM_OB1203_LIGHT_RESOLUTION_13BIT_PERIOD_200MS  = 0x53, ///< Resolution : 13bit, measurement period : 200ms.
    RM_OB1203_LIGHT_RESOLUTION_13BIT_PERIOD_500MS  = 0x54, ///< Resolution : 13bit, measurement period : 500ms.
    RM_OB1203_LIGHT_RESOLUTION_13BIT_PERIOD_1000MS = 0x55, ///< Resolution : 13bit, measurement period : 1000ms.
    RM_OB1203_LIGHT_RESOLUTION_13BIT_PERIOD_2000MS = 0x56, ///< Resolution : 13bit, measurement period : 2000ms.
    RM_OB1203_LIGHT_RESOLUTION_16BIT_PERIOD_25MS   = 0x40, ///< Resolution : 16bit, measurement period : 25ms.
    RM_OB1203_LIGHT_RESOLUTION_16BIT_PERIOD_50MS   = 0x41, ///< Resolution : 16bit, measurement period : 50ms.
    RM_OB1203_LIGHT_RESOLUTION_16BIT_PERIOD_100MS  = 0x42, ///< Resolution : 16bit, measurement period : 100ms.
    RM_OB1203_LIGHT_RESOLUTION_16BIT_PERIOD_200MS  = 0x43, ///< Resolution : 16bit, measurement period : 200ms.
    RM_OB1203_LIGHT_RESOLUTION_16BIT_PERIOD_500MS  = 0x44, ///< Resolution : 16bit, measurement period : 500ms.
    RM_OB1203_LIGHT_RESOLUTION_16BIT_PERIOD_1000MS = 0x45, ///< Resolution : 16bit, measurement period : 1000ms.
    RM_OB1203_LIGHT_RESOLUTION_16BIT_PERIOD_2000MS = 0x46, ///< Resolution : 16bit, measurement period : 2000ms.
    RM_OB1203_LIGHT_RESOLUTION_17BIT_PERIOD_50MS   = 0x31, ///< Resolution : 17bit, measurement period : 50ms.
    RM_OB1203_LIGHT_RESOLUTION_17BIT_PERIOD_100MS  = 0x32, ///< Resolution : 17bit, measurement period : 100ms.
    RM_OB1203_LIGHT_RESOLUTION_17BIT_PERIOD_200MS  = 0x33, ///< Resolution : 17bit, measurement period : 200ms.
    RM_OB1203_LIGHT_RESOLUTION_17BIT_PERIOD_500MS  = 0x34, ///< Resolution : 17bit, measurement period : 500ms.
    RM_OB1203_LIGHT_RESOLUTION_17BIT_PERIOD_1000MS = 0x35, ///< Resolution : 17bit, measurement period : 1000ms.
    RM_OB1203_LIGHT_RESOLUTION_17BIT_PERIOD_2000MS = 0x36, ///< Resolution : 17bit, measurement period : 2000ms.
    RM_OB1203_LIGHT_RESOLUTION_18BIT_PERIOD_100MS  = 0x22, ///< Resolution : 18bit, measurement period : 100ms.
    RM_OB1203_LIGHT_RESOLUTION_18BIT_PERIOD_200MS  = 0x23, ///< Resolution : 18bit, measurement period : 200ms.
    RM_OB1203_LIGHT_RESOLUTION_18BIT_PERIOD_500MS  = 0x24, ///< Resolution : 18bit, measurement period : 500ms.
    RM_OB1203_LIGHT_RESOLUTION_18BIT_PERIOD_1000MS = 0x25, ///< Resolution : 18bit, measurement period : 1000ms.
    RM_OB1203_LIGHT_RESOLUTION_18BIT_PERIOD_2000MS = 0x26, ///< Resolution : 18bit, measurement period : 2000ms.
    RM_OB1203_LIGHT_RESOLUTION_19BIT_PERIOD_200MS  = 0x13, ///< Resolution : 19bit, measurement period : 200ms.
    RM_OB1203_LIGHT_RESOLUTION_19BIT_PERIOD_500MS  = 0x14, ///< Resolution : 19bit, measurement period : 500ms.
    RM_OB1203_LIGHT_RESOLUTION_19BIT_PERIOD_1000MS = 0x15, ///< Resolution : 19bit, measurement period : 1000ms.
    RM_OB1203_LIGHT_RESOLUTION_19BIT_PERIOD_2000MS = 0x16, ///< Resolution : 19bit, measurement period : 2000ms.
    RM_OB1203_LIGHT_RESOLUTION_20BIT_PERIOD_500MS  = 0x04, ///< Resolution : 20bit, measurement period : 500ms.
    RM_OB1203_LIGHT_RESOLUTION_20BIT_PERIOD_1000MS = 0x05, ///< Resolution : 20bit, measurement period : 1000ms.
    RM_OB1203_LIGHT_RESOLUTION_20BIT_PERIOD_2000MS = 0x06, ///< Resolution : 20bit, measurement period : 2000ms.
} rm_ob1203_light_resolution_meas_period_t;

/** Proximity pulse width and measurement period  */
typedef enum e_rm_ob1203_prox_pulse_width_meas_period
{
    RM_OB1203_PROX_WIDTH_26US_PERIOD_3P125MS = 0x00, ///< Pulse width : 26us, measurement period : 3.125ms. Except for the number 32 of LED pulses.
    RM_OB1203_PROX_WIDTH_26US_PERIOD_6P25MS  = 0x01, ///< Pulse width : 26us, measurement period : 6.25ms.
    RM_OB1203_PROX_WIDTH_26US_PERIOD_12P5MS  = 0x02, ///< Pulse width : 26us, measurement period : 12.5ms.
    RM_OB1203_PROX_WIDTH_26US_PERIOD_25MS    = 0x03, ///< Pulse width : 26us, measurement period : 25ms.
    RM_OB1203_PROX_WIDTH_26US_PERIOD_50MS    = 0x04, ///< Pulse width : 26us, measurement period : 50ms.
    RM_OB1203_PROX_WIDTH_26US_PERIOD_100MS   = 0x05, ///< Pulse width : 26us, measurement period : 100ms.
    RM_OB1203_PROX_WIDTH_26US_PERIOD_200MS   = 0x06, ///< Pulse width : 26us, measurement period : 200ms.
    RM_OB1203_PROX_WIDTH_26US_PERIOD_400MS   = 0x07, ///< Pulse width : 26us, measurement period : 400ms.
    RM_OB1203_PROX_WIDTH_42US_PERIOD_3P125MS = 0x10, ///< Pulse width : 42us, measurement period : 3.125ms. Except for the number 32 of LED pulses.
    RM_OB1203_PROX_WIDTH_42US_PERIOD_6P25MS  = 0x11, ///< Pulse width : 42us, measurement period : 6.25ms.
    RM_OB1203_PROX_WIDTH_42US_PERIOD_12P5MS  = 0x12, ///< Pulse width : 42us, measurement period : 12.5ms.
    RM_OB1203_PROX_WIDTH_42US_PERIOD_25MS    = 0x13, ///< Pulse width : 42us, measurement period : 25ms.
    RM_OB1203_PROX_WIDTH_42US_PERIOD_50MS    = 0x14, ///< Pulse width : 42us, measurement period : 50ms.
    RM_OB1203_PROX_WIDTH_42US_PERIOD_100MS   = 0x15, ///< Pulse width : 42us, measurement period : 100ms.
    RM_OB1203_PROX_WIDTH_42US_PERIOD_200MS   = 0x16, ///< Pulse width : 42us, measurement period : 200ms.
    RM_OB1203_PROX_WIDTH_42US_PERIOD_400MS   = 0x17, ///< Pulse width : 42us, measurement period : 400ms.
    RM_OB1203_PROX_WIDTH_71US_PERIOD_3P125MS = 0x20, ///< Pulse width : 71us, measurement period : 3.125ms. Except for the number 16 and 32 of LED pulses.
    RM_OB1203_PROX_WIDTH_71US_PERIOD_6P25MS  = 0x21, ///< Pulse width : 71us, measurement period : 6.25ms. Except for the number 32 of LED pulses.
    RM_OB1203_PROX_WIDTH_71US_PERIOD_12P5MS  = 0x22, ///< Pulse width : 71us, measurement period : 12.5ms.
    RM_OB1203_PROX_WIDTH_71US_PERIOD_25MS    = 0x23, ///< Pulse width : 71us, measurement period : 25ms.
    RM_OB1203_PROX_WIDTH_71US_PERIOD_50MS    = 0x24, ///< Pulse width : 71us, measurement period : 50ms.
    RM_OB1203_PROX_WIDTH_71US_PERIOD_100MS   = 0x25, ///< Pulse width : 71us, measurement period : 100ms.
    RM_OB1203_PROX_WIDTH_71US_PERIOD_200MS   = 0x26, ///< Pulse width : 71us, measurement period : 200ms.
    RM_OB1203_PROX_WIDTH_71US_PERIOD_400MS   = 0x27, ///< Pulse width : 71us, measurement period : 400ms.
} rm_ob1203_prox_pulse_width_meas_period_t;

/** PPG pulse width and measurement period  */
typedef enum e_rm_ob1203_ppg_pulse_width_meas_period
{
    RM_OB1203_PPG_WIDTH_130US_PERIOD_0P3125MS = 0x30, ///< Pulse width : 130us, measurement period : 0.3125ms. PPG1 mode only.
    RM_OB1203_PPG_WIDTH_130US_PERIOD_0P625MS  = 0x31, ///< Pulse width : 130us, measurement period : 0.625ms.
    RM_OB1203_PPG_WIDTH_130US_PERIOD_1MS      = 0x32, ///< Pulse width : 130us, measurement period : 1ms.
    RM_OB1203_PPG_WIDTH_130US_PERIOD_1P25MS   = 0x33, ///< Pulse width : 130us, measurement period : 1.25ms.
    RM_OB1203_PPG_WIDTH_130US_PERIOD_2P5MS    = 0x34, ///< Pulse width : 130us, measurement period : 2.5ms.
    RM_OB1203_PPG_WIDTH_130US_PERIOD_5MS      = 0x35, ///< Pulse width : 130us, measurement period : 5ms.
    RM_OB1203_PPG_WIDTH_130US_PERIOD_10MS     = 0x36, ///< Pulse width : 130us, measurement period : 10ms.
    RM_OB1203_PPG_WIDTH_130US_PERIOD_20MS     = 0x37, ///< Pulse width : 130us, measurement period : 20ms.
    RM_OB1203_PPG_WIDTH_247US_PERIOD_0P625MS  = 0x41, ///< Pulse width : 247us, measurement period : 0.625ms. PPG1 mode only.
    RM_OB1203_PPG_WIDTH_247US_PERIOD_1MS      = 0x42, ///< Pulse width : 247us, measurement period : 1ms.
    RM_OB1203_PPG_WIDTH_247US_PERIOD_1P25MS   = 0x43, ///< Pulse width : 247us, measurement period : 1.25ms.
    RM_OB1203_PPG_WIDTH_247US_PERIOD_2P5MS    = 0x44, ///< Pulse width : 247us, measurement period : 2.5ms.
    RM_OB1203_PPG_WIDTH_247US_PERIOD_5MS      = 0x45, ///< Pulse width : 247us, measurement period : 5ms.
    RM_OB1203_PPG_WIDTH_247US_PERIOD_10MS     = 0x46, ///< Pulse width : 247us, measurement period : 10ms.
    RM_OB1203_PPG_WIDTH_247US_PERIOD_20MS     = 0x47, ///< Pulse width : 247us, measurement period : 20ms.
    RM_OB1203_PPG_WIDTH_481US_PERIOD_1MS      = 0x52, ///< Pulse width : 481us, measurement period : 1ms. PPG1 mode only.
    RM_OB1203_PPG_WIDTH_481US_PERIOD_1P25MS   = 0x53, ///< Pulse width : 481us, measurement period : 1.25ms. PPG1 mode only.
    RM_OB1203_PPG_WIDTH_481US_PERIOD_2P5MS    = 0x54, ///< Pulse width : 481us, measurement period : 2.5ms.
    RM_OB1203_PPG_WIDTH_481US_PERIOD_5MS      = 0x55, ///< Pulse width : 481us, measurement period : 5ms.
    RM_OB1203_PPG_WIDTH_481US_PERIOD_10MS     = 0x56, ///< Pulse width : 481us, measurement period : 10ms.
    RM_OB1203_PPG_WIDTH_481US_PERIOD_20MS     = 0x57, ///< Pulse width : 481us, measurement period : 20ms.
    RM_OB1203_PPG_WIDTH_949US_PERIOD_2P5MS    = 0x64, ///< Pulse width : 949us, measurement period : 2.5ms. PPG1 mode only.
    RM_OB1203_PPG_WIDTH_949US_PERIOD_5MS      = 0x65, ///< Pulse width : 949us, measurement period : 5ms.
    RM_OB1203_PPG_WIDTH_949US_PERIOD_10MS     = 0x66, ///< Pulse width : 949us, measurement period : 10ms.
    RM_OB1203_PPG_WIDTH_949US_PERIOD_20MS     = 0x67, ///< Pulse width : 949us, measurement period : 20ms.
} rm_ob1203_ppg_pulse_width_meas_period_t;

/** FIFO Rollover */
typedef enum e_rm_ob1203_fifo_rollover
{
    RM_OB1203_FIFO_ROLLOVER_DISABLE = 0x00, ///< In the event of a full FIFO, no more samples of PPG data are written into the FIFO; the samples from new measurements are lost.
    RM_OB1203_FIFO_ROLLOVER_ENABLE  = 0x10, ///< New PPG data will always be written to the FIFO, and the FIFO Write Pointer is incremented (rollover). If the FIFO is full, old data will be overwritten. The FIFO Overflow Counter counts the number of lost (overwritten) and respectively the number of new samples. The FIFO Read Pointer remains unchanged.
} rm_ob1203_fifo_rollover_t;

#if BSP_CFG_RTOS

/* Semaphore Structure */
typedef struct st_rm_ob1203_semaphore
{
 #if BSP_CFG_RTOS == 1                 // ThreadX
    TX_SEMAPHORE * p_semaphore_handle;
    CHAR         * p_semaphore_name;
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    SemaphoreHandle_t * p_semaphore_handle;
    StaticSemaphore_t * p_semaphore_memory;
 #else
 #endif
} rm_ob1203_semaphore_t;
#endif

/** OB1203 callback parameter definition */
typedef struct st_rm_ob1203_callback_args
{
    void const      * p_context;
    rm_ob1203_event_t event;
} rm_ob1203_callback_args_t;

/** OB1203 raw data structure */
typedef struct st_rm_ob1203_raw_data
{
    uint8_t adc_data[96];              ///< Max of PPG data is 96 (3 bytes multiplied by 32 samples)
} rm_ob1203_raw_data_t;

/** OB1203 light data structure */
typedef struct st_rm_ob1203_light_data
{
    uint32_t clear_data;               ///< Clear channel data (20bits).
    uint32_t green_data;               ///< Green channel data (20bits).
    uint32_t blue_data;                ///< Blue channel data (20bits).
    uint32_t red_data;                 ///< Red channel data (20bits).
    uint32_t comp_data;                ///< Temperature compensation (Comp) channel data (20bits).
} rm_ob1203_light_data_t;

/** OB1203 proximity data structure */
typedef struct st_rm_ob1203_prox_data
{
    uint16_t proximity_data;           ///< Proximity data.
} rm_ob1203_prox_data_t;

/** OB1203 PPG data structure */
typedef struct st_rm_ob1203_ppg_data
{
    uint32_t ppg_data[32];             ///< PPG data (18bits).
} rm_ob1203_ppg_data_t;

/** OB1203 device interrupt configuration structure */
typedef struct st_rm_ob1203_device_interrupt_cfg
{
    rm_ob1203_operation_mode_t         light_prox_mode; ///< Light Proximity mode only. If Light mode uses IRQ, set RM_OB1203_OPERATION_MODE_LIGHT. If Proximity mode uses IRQ, set RM_OB1203_OPERATION_MODE_PROXIMITY.
    rm_ob1203_light_interrupt_type_t   light_type;      ///< Light mode interrupt type.
    rm_ob1203_light_interrupt_source_t light_source;    ///< Light mode interrupt source.
    rm_ob1203_prox_interrupt_type_t    prox_type;       ///< Proximity mode interrupt type.
    uint8_t persist;                                    ///< The number of similar consecutive Light mode or Proximity interrupt events that must occur before the interrupt is asserted (4bits).
    rm_ob1203_ppg_interrupt_type_t ppg_type;            ///< PPG mode interrupt type.
} rm_ob1203_device_interrupt_cfg_t;

/** OB1203 device status */
typedef struct st_rm_ob1203_device_status
{
    bool power_on_reset_occur;
    bool light_interrupt_occur;
    bool light_measurement_complete;
    bool ts_measurement_complete;
    bool fifo_afull_interrupt_occur;   ///< FIFO almost full interrupt
    bool ppg_measurement_complete;
    bool object_near;
    bool prox_interrupt_occur;
    bool prox_measurement_complete;
} rm_ob1203_device_status_t;

/** OB1203 Gain structure */
typedef struct st_rm_ob1203_gain
{
    rm_ob1203_light_gain_t    light;    ///< Gain for Light mode
    rm_ob1203_ppg_prox_gain_t ppg_prox; ///< Gain for PPG mode and Proximity mode
} rm_ob1203_gain_t;

/** OB1203 LED currents structure */
typedef struct st_rm_ob1203_led_current
{
    uint16_t ir_led;                   ///< IR LED current.
    uint16_t red_led;                  ///< Red LED current.
} rm_ob1203_led_current_t;

/** OB1203 FIFO information structure */
typedef struct st_rm_ob1203_fifo_info
{
    uint8_t write_index;               ///< The FIFO index where the next sample of PPG data will be written in the FIFO.
    uint8_t read_index;                ///< The index of the next sample to be read from the FIFO_DATA register.
    uint8_t overflow_counter;          ///< If the FIFO Rollover Enable bit is set, the FIFO overflow counter counts the number of old samples (up to 15) which are overwritten by new data.
    uint8_t unread_samples;            ///< The number of unread samples calculated from the write index and the read index.
} rm_ob1203_fifo_info_t;

/** OB1203 Configuration */
typedef struct st_rm_ob1203_cfg
{
#if BSP_CFG_RTOS
    rm_ob1203_semaphore_t const * p_semaphore;                     ///< The semaphore to wait for callback. This is used for another data read/write after a communication
#endif
    uint32_t semaphore_timeout;                                    ///< timeout for callback.
    rm_comms_instance_t const * p_comms_instance;                  ///< Pointer to Communications Middleware instance.
    void const                * p_irq_instance;                    ///< Pointer to IRQ instance.
    void const                * p_context;                         ///< Pointer to the user-provided context.
    void const                * p_extend;                          ///< Pointer to extended configuration by instance of interface.
    void (* p_comms_callback)(rm_ob1203_callback_args_t * p_args); ///< I2C Communications callback
    void (* p_irq_callback)(rm_ob1203_callback_args_t * p_args);   ///< IRQ callback
} rm_ob1203_cfg_t;

/** OB1203 control block.  Allocate an instance specific control block to pass into the OB1203 API calls.
 * @par Implemented as
 * - rm_ob1203_instance_ctrl_t
 */
typedef void rm_ob1203_ctrl_t;

/** OB1203 APIs */
typedef struct st_rm_ob1203_api
{
    /** Open sensor.
     * @par Implemented as
     * - @ref RM_OB1203_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_ob1203_ctrl_t * const p_ctrl, rm_ob1203_cfg_t const * const p_cfg);

    /** Start measurement.
     * @par Implemented as
     * - @ref RM_OB1203_MeasurementStart()
     *
     * @param[in]  p_ctrl    Pointer to control structure.
     * @param[in]  mode      Sensor mode.
     */
    fsp_err_t (* measurementStart)(rm_ob1203_ctrl_t * const p_ctrl);

    /** Stop measurement.
     * @par Implemented as
     * - @ref RM_OB1203_MeasurementStop()
     *
     * @param[in]  p_ctrl    Pointer to control structure.
     * @param[in]  mode      Sensor mode.
     */
    fsp_err_t (* measurementStop)(rm_ob1203_ctrl_t * const p_ctrl);

    /** Read Light ADC data from OB1203.
     * @par Implemented as
     * - @ref RM_OB1203_LightRead()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data structure.
     * @param[in]  type             Light data type.
     */
    fsp_err_t (* lightRead)(rm_ob1203_ctrl_t * const p_ctrl, rm_ob1203_raw_data_t * const p_raw_data,
                            rm_ob1203_light_data_type_t type);

    /** Calculate Light data from raw data.
     * @par Implemented as
     * - @ref RM_OB1203_LightDataCalculate()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data structure.
     * @param[in]  p_ob1203_data    Pointer to OB1203 Light data structure.
     */
    fsp_err_t (* lightDataCalculate)(rm_ob1203_ctrl_t * const p_ctrl, rm_ob1203_raw_data_t * const p_raw_data,
                                     rm_ob1203_light_data_t * const p_ob1203_data);

    /** Read Proximity ADC data from OB1203.
     * @par Implemented as
     * - @ref RM_OB1203_ProxRead()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data structure.
     */
    fsp_err_t (* proxRead)(rm_ob1203_ctrl_t * const p_ctrl, rm_ob1203_raw_data_t * const p_raw_data);

    /** Calculate Proximity data from raw data.
     * @par Implemented as
     * - @ref RM_OB1203_ProxDataCalculate()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data structure.
     * @param[in]  p_ob1203_data    Pointer to OB1203 Proximity data structure.
     */
    fsp_err_t (* proxDataCalculate)(rm_ob1203_ctrl_t * const p_ctrl, rm_ob1203_raw_data_t * const p_raw_data,
                                    rm_ob1203_prox_data_t * const p_ob1203_data);

    /** Read PPG ADC data from OB1203.
     * @par Implemented as
     * - @ref RM_OB1203_PpgRead()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data structure.
     * @param[in]  number_of_samples  Number of PPG samples. One sample is 3 bytes.
     */
    fsp_err_t (* ppgRead)(rm_ob1203_ctrl_t * const p_ctrl, rm_ob1203_raw_data_t * const p_raw_data,
                          uint8_t const number_of_samples);

    /** Calculate PPG data from raw data.
     * @par Implemented as
     * - @ref RM_OB1203_PpgDataCalculate()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data structure.
     * @param[in]  p_ob1203_data    Pointer to OB1203 PPG data structure.
     */
    fsp_err_t (* ppgDataCalculate)(rm_ob1203_ctrl_t * const p_ctrl, rm_ob1203_raw_data_t * const p_raw_data,
                                   rm_ob1203_ppg_data_t * const p_ob1203_data);

    /** Get device status. Read STATUS_0 and STATUS_1 registers.
     * @par Implemented as
     * - @ref RM_OB1203_DeviceStatusGet()
     *
     * @param[in]  p_ctrl               Pointer to control structure.
     * @param[in]  p_status             Pointer to device status.
     */
    fsp_err_t (* deviceStatusGet)(rm_ob1203_ctrl_t * const p_ctrl, rm_ob1203_device_status_t * const p_status);

    /** Set device interrupt configuration.
     * @par Implemented as
     * - @ref RM_OB1203_DeviceInterruptCfgSet()
     *
     * @param[in]  p_ctrl               Pointer to control structure.
     * @param[in]  interrupt_cfg        Device interrupt configuration.
     */
    fsp_err_t (* deviceInterruptCfgSet)(rm_ob1203_ctrl_t * const               p_ctrl,
                                        rm_ob1203_device_interrupt_cfg_t const interrupt_cfg);

    /** Set gain.
     * @par Implemented as
     * - @ref RM_OB1203_GainSet()
     *
     * @param[in]  p_ctrl      Pointer to control structure.
     * @param[in]  gain        Gain configuration.
     */
    fsp_err_t (* gainSet)(rm_ob1203_ctrl_t * const p_ctrl, rm_ob1203_gain_t const gain);

    /** Set LED current value.
     * @par Implemented as
     * - @ref RM_OB1203_LedCurrentSet()
     *
     * @param[in]  p_ctrl               Pointer to control structure.
     * @param[in]  led_current          Current value structure.
     */
    fsp_err_t (* ledCurrentSet)(rm_ob1203_ctrl_t * const p_ctrl, rm_ob1203_led_current_t const led_current);

    /** Get FIFO information.
     * @par Implemented as
     * - @ref RM_OB1203_FifoInfoGet()
     *
     * @param[in]  p_ctrl               Pointer to control structure.
     * @param[in]  p_fifo_info          Pointer to FIFO information (write index, read index and overflow counter).
     */
    fsp_err_t (* fifoInfoGet)(rm_ob1203_ctrl_t * const p_ctrl, rm_ob1203_fifo_info_t * const p_fifo_info);

    /** Close OB1203.
     * @par Implemented as
     * - @ref RM_OB1203_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ob1203_ctrl_t * const p_ctrl);
} rm_ob1203_api_t;

/** OB1203 instance */
typedef struct st_rm_ob1203_instance
{
    rm_ob1203_ctrl_t      * p_ctrl;    /**< Pointer to the control structure for this instance */
    rm_ob1203_cfg_t const * p_cfg;     /**< Pointer to the configuration structure for this instance */
    rm_ob1203_api_t const * p_api;     /**< Pointer to the API structure for this instance */
} rm_ob1203_instance_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_OB1203_API_H_*/

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_OB1203_API)
 **********************************************************************************************************************/
