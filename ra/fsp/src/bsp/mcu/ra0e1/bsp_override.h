/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA0E1
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RA0E1) */

#ifndef BSP_OVERRIDE_H
#define BSP_OVERRIDE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Define overrides required for this MCU. */
#define BSP_OVERRIDE_ADC_CHANNEL_T
#define BSP_OVERRIDE_ADC_RESOLUTION_T
#define BSP_OVERRIDE_CGC_DIVIDER_CFG_T
#define BSP_OVERRIDE_CGC_SYS_CLOCK_DIV_T
#define BSP_OVERRIDE_IOPORT_CFG_OPTIONS_T
#define BSP_OVERRIDE_IOPORT_PERIPHERAL_T
#define BSP_OVERRIDE_LPM_SNOOZE_CANCEL_T
#define BSP_OVERRIDE_LPM_STANDBY_WAKE_SOURCE_T
#define BSP_OVERRIDE_LVD_PERIPHERAL_T
#define BSP_OVERRIDE_RTC_ALARM_TIME_T
#define BSP_OVERRIDE_RTC_PERIODIC_IRQ_SELECT_T
#define BSP_OVERRIDE_TIMER_EVENT_T
#define BSP_OVERRIDE_TIMER_MODE_T
#define BSP_OVERRIDE_TIMER_SOURCE_DIV_T
#define BSP_OVERRIDE_UART_DATA_BITS_T
#define BSP_OVERRIDE_UART_DATA_BITS_T

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#define IOPORT_PRV_PSEL_OFFSET       (8)
#define IOPORT_PERIPHERAL_PIN_OUT    (0x04UL) // Set PDR to 1
#define IOPORT_PERIPHERAL_PIN_IO     (0x44UL) // Set PDR, NCODR to 1

typedef enum e_ioport_peripheral
{
    IOPORT_PERIPHERAL_IO         = 0x00,
    IOPORT_PERIPHERAL_DEBUG      = (0x01UL << IOPORT_PRV_PSEL_OFFSET),
    IOPORT_PERIPHERAL_SAU1       = (0x01UL << IOPORT_PRV_PSEL_OFFSET),
    IOPORT_PERIPHERAL_SAU2       = (0x02UL << IOPORT_PRV_PSEL_OFFSET),
    IOPORT_PERIPHERAL_SAU3       = (0x03UL << IOPORT_PRV_PSEL_OFFSET),
    IOPORT_PERIPHERAL_SAU4       = (0x04UL << IOPORT_PRV_PSEL_OFFSET),
    IOPORT_PERIPHERAL_SAU1_OUT   = ((0x01UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_SAU2_OUT   = ((0x02UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_SAU3_OUT   = ((0x03UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_SAU4_OUT   = ((0x04UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_SAU1_IO    = ((0x01UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_IO),
    IOPORT_PERIPHERAL_SAU2_IO    = ((0x02UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_IO),
    IOPORT_PERIPHERAL_SAU3_IO    = ((0x03UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_IO),
    IOPORT_PERIPHERAL_SAU4_IO    = ((0x04UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_IO),
    IOPORT_PERIPHERAL_UARTA2     = (0x02UL << IOPORT_PRV_PSEL_OFFSET),
    IOPORT_PERIPHERAL_UARTA4     = (0x04UL << IOPORT_PRV_PSEL_OFFSET),
    IOPORT_PERIPHERAL_UARTA5     = (0x05UL << IOPORT_PRV_PSEL_OFFSET),
    IOPORT_PERIPHERAL_UARTA6     = (0x06UL << IOPORT_PRV_PSEL_OFFSET),
    IOPORT_PERIPHERAL_UARTA2_OUT = ((0x02UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_UARTA4_OUT = ((0x04UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_UARTA5_OUT = ((0x05UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_UARTA6_OUT = ((0x06UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_IICA1      = ((0x01UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_IO),
    IOPORT_PERIPHERAL_IICA3      = ((0x03UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_IO),
    IOPORT_PERIPHERAL_IICA4      = ((0x04UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_IO),
    IOPORT_PERIPHERAL_IICA5      = ((0x05UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_IO),
    IOPORT_PERIPHERAL_BUZ3       = ((0x03UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_BUZ5       = ((0x05UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_RTC2       = ((0x02UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_RTC4       = ((0x04UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_TAU1       = (0x01UL << IOPORT_PRV_PSEL_OFFSET),
    IOPORT_PERIPHERAL_TAU2       = (0x02UL << IOPORT_PRV_PSEL_OFFSET),
    IOPORT_PERIPHERAL_TAU1_OUT   = ((0x01UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
    IOPORT_PERIPHERAL_TAU2_OUT   = ((0x02UL << IOPORT_PRV_PSEL_OFFSET) | IOPORT_PERIPHERAL_PIN_OUT),
} ioport_peripheral_t;

/** Options to configure pin functions  */
typedef enum e_ioport_cfg_options
{
    IOPORT_CFG_PORT_DIRECTION_INPUT  = 0x00000000, ///< Sets the pin direction to input (default)
    IOPORT_CFG_PORT_DIRECTION_OUTPUT = 0x00000004, ///< Sets the pin direction to output
    IOPORT_CFG_PORT_OUTPUT_LOW       = 0x00000000, ///< Sets the pin level to low
    IOPORT_CFG_PORT_OUTPUT_HIGH      = 0x00000001, ///< Sets the pin level to high
    IOPORT_CFG_PULLUP_ENABLE         = 0x00000010, ///< Enables the pin's internal pull-up
    IOPORT_CFG_PIM_TTL               = 0x00000020, ///< Enables the pin's input mode
    IOPORT_CFG_NMOS_ENABLE           = 0x00000040, ///< Enables the pin's NMOS open-drain output
    IOPORT_CFG_IRQ_ENABLE            = 0x00004000, ///< Sets pin as an IRQ pin
    IOPORT_CFG_ANALOG_ENABLE         = 0x00008000, ///< Enables pin to operate as an analog pin
    IOPORT_CFG_PERIPHERAL_PIN        = 0x00000000  ///< Enables pin to operate as a peripheral pin
} ioport_cfg_options_t;

/** Wake from deep sleep or standby mode sources, does not apply to sleep or deep standby modes */
typedef enum e_lpm_standby_wake_source
{
    LPM_STANDBY_WAKE_SOURCE_IWDT       = 0x00000001ULL,    ///< Independent watchdog interrupt
    LPM_STANDBY_WAKE_SOURCE_LVD1       = 0x00000002ULL,    ///< Low Voltage Detection 1 interrupt
    LPM_STANDBY_WAKE_SOURCE_IRQ0       = 0x00000004ULL,    ///< IRQ0
    LPM_STANDBY_WAKE_SOURCE_IRQ1       = 0x00000008ULL,    ///< IRQ1
    LPM_STANDBY_WAKE_SOURCE_IRQ2       = 0x00000010ULL,    ///< IRQ2
    LPM_STANDBY_WAKE_SOURCE_IRQ3       = 0x00000020ULL,    ///< IRQ3
    LPM_STANDBY_WAKE_SOURCE_IRQ4       = 0x00000040ULL,    ///< IRQ4
    LPM_STANDBY_WAKE_SOURCE_IRQ5       = 0x00000080ULL,    ///< IRQ5
    LPM_STANDBY_WAKE_SOURCE_IICA0      = 0x04000000ULL,    ///< I2CA 0 interrupt
    LPM_STANDBY_WAKE_SOURCE_RTC        = 0x100000000ULL,   ///< RTC interrupt
    LPM_STANDBY_WAKE_SOURCE_ITL        = 0x200000000ULL,   ///< Interval signal of 32-bit interval timer Interrupt
    LPM_STANDBY_WAKE_SOURCE_UARTA0ERRI = 0x8000000000ULL,  ///< UARTA0 reception communication error Interrupt
    LPM_STANDBY_WAKE_SOURCE_UARTA0TXI  = 0x10000000000ULL, ///< UARTA0 transmission transfer end or buffer empty Interrupt
    LPM_STANDBY_WAKE_SOURCE_UARTA0RXI  = 0x20000000000ULL, ///< UARTA0 reception transfer end Interrupt
} lpm_standby_wake_source_t;

typedef uint64_t lpm_standby_wake_source_bits_t;

typedef enum e_lpm_snooze_cancel_source
{
    LPM_SNOOZE_CANCEL_SOURCE_NONE             = 0x00000000ULL, ///< No snooze cancel source
    LPM_SNOOZE_CANCEL_SOURCE_DTC_COMPLETE     = 0x00000400ULL, ///< DTC Transfer Complete Interrupt
    LPM_SNOOZE_CANCEL_SOURCE_SAU0_SPI_TXRXI00 = 0x00040000ULL, ///< SPI00 Transfer End or Buffer Empty Interrupt
    LPM_SNOOZE_CANCEL_SOURCE_SAU0_UART_ERR0   = 0x00100000ULL, ///< UART0 Reception Communication Error Occurrence Interrupt
    LPM_SNOOZE_CANCEL_SOURCE_SAU0_UART_RXI0   = 0x08000000ULL, ///< UART0 Reception Transfer End Interrupt
    LPM_SNOOZE_CANCEL_SOURCE_ADC0_END         = 0x80000000ULL, ///< A/D Conversion Interrupt
} lpm_snooze_cancel_source_t;

typedef uint64_t lpm_snooze_cancel_source_bits_t;

typedef enum e_cgc_sys_clock_div
{
    CGC_SYS_CLOCK_DIV_1  = 0,          ///< System clock divided by 1
    CGC_SYS_CLOCK_DIV_2  = 1,          ///< System clock divided by 2
    CGC_SYS_CLOCK_DIV_4  = 2,          ///< System clock divided by 4
    CGC_SYS_CLOCK_DIV_8  = 3,          ///< System clock divided by 8
    CGC_SYS_CLOCK_DIV_16 = 4,          ///< System clock divided by 16
    CGC_SYS_CLOCK_DIV_32 = 5,          ///< System clock divided by 32
} cgc_sys_clock_div_t;

typedef struct st_cgc_divider_cfg
{
    cgc_sys_clock_div_t moco_divider;  ///< MOCO divider
    cgc_sys_clock_div_t hoco_divider;  ///< HOCO divider
    cgc_sys_clock_div_t mosc_divider;  ///< Main oscillator divider
} cgc_divider_cfg_t;

/** UART Data bit length definition */
typedef enum e_uart_data_bits
{
    UART_DATA_BITS_5 = 0U,             ///< Data bits 5-bit
    UART_DATA_BITS_9 = 1U,             ///< Data bits 9-bit
    UART_DATA_BITS_7 = 2U,             ///< Data bits 7-bit
    UART_DATA_BITS_8 = 3U,             ///< Data bits 8-bit
} uart_data_bits_t;

/** The thresholds supported by each MCU are in the MCU User's Manual as well as
 *  in the r_lvd module description on the stack tab of the RA project. */
typedef enum
{
    LVD_THRESHOLD_MONITOR_1_LEVEL_4_08V = 0x0EUL, ///< 4.08V
    LVD_THRESHOLD_MONITOR_1_LEVEL_3_88V = 0x0FUL, ///< 3.88V
    LVD_THRESHOLD_MONITOR_1_LEVEL_3_67V = 0x10UL, ///< 3.67V
    LVD_THRESHOLD_MONITOR_1_LEVEL_3_47V = 0x11UL, ///< 3.47V
    LVD_THRESHOLD_MONITOR_1_LEVEL_3_27V = 0x12UL, ///< 3.27V
    LVD_THRESHOLD_MONITOR_1_LEVEL_3_06V = 0x13UL, ///< 3.06V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_91V = 0x14UL, ///< 2.91V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_76V = 0x15UL, ///< 2.76V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_60V = 0x16UL, ///< 2.60V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_45V = 0x17UL, ///< 2.45V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_35V = 0x18UL, ///< 2.35V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_25V = 0x19UL, ///< 2.25V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_15V = 0x1AUL, ///< 2.15V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_04V = 0x1BUL, ///< 2.04V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_94V = 0x1CUL, ///< 1.94V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_84V = 0x1DUL, ///< 1.84V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_74V = 0x1EUL, ///< 1.74V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_63V = 0x1FUL, ///< 1.63V
} lvd_threshold_t;

/** ADC channels */
typedef enum e_adc_channel
{
    ADC_CHANNEL_0                  = 0,   ///< Channel 0 for select mode or channel 0 to 3 for scan mode
    ADC_CHANNEL_1                  = 1,   ///< Channel 1 for select mode or channel 1 to 4 for scan mode
    ADC_CHANNEL_2                  = 2,   ///< Channel 2 for select mode or channel 2 to 5 for scan mode
    ADC_CHANNEL_3                  = 3,   ///< Channel 3 for select mode or channel 3 to 6 for scan mode
    ADC_CHANNEL_4                  = 4,   ///< Channel 4 for select mode or channel 4 to 7 for scan mode
    ADC_CHANNEL_5                  = 5,   ///< Channel 5 for select mode
    ADC_CHANNEL_6                  = 6,   ///< Channel 6 for select mode
    ADC_CHANNEL_7                  = 7,   ///< Channel 7 for select mode
    ADC_CHANNEL_21                 = 21,  ///< Channel 21 for select mode
    ADC_CHANNEL_22                 = 22,  ///< Channel 22 for select mode
    ADC_CHANNEL_TEMPERATURE        = 128, ///< Temperature sensor output voltage for select mode
    ADC_CHANNEL_VOLT               = 129, ///< Internal reference voltage for select mode
    ADC_CHANNEL_POSITIVE_SIDE_VREF = -2,  ///< Select positive reference voltage as target conversion
    ADC_CHANNEL_NEGATIVE_SIDE_VREF = -3   ///< Select negative reference voltage as target conversion
} adc_channel_t;

/** Alarm time setting structure */
typedef struct st_rtc_alarm_time
{
    int time_minute;                   ///< Time structure
    int time_hour;
    union
    {
        struct
        {
            uint8_t sunday_match    : 1; ///< Enable the alarm on Sunday
            uint8_t monday_match    : 1; ///< Enable the alarm on Monday
            uint8_t tuesday_match   : 1; ///< Enable the alarm on Tuesday
            uint8_t wednesday_match : 1; ///< Enable the alarm on Wednesday
            uint8_t thursday_match  : 1; ///< Enable the alarm on Thursday
            uint8_t friday_match    : 1; ///< Enable the alarm on Friday
            uint8_t saturday_match  : 1; ///< Enable the alarm on Saturday
        };
        uint8_t weekday_match;
    };
} rtc_alarm_time_t;

/** Periodic Interrupt select */
typedef enum e_rtc_periodic_irq_select
{
    RTC_PERIODIC_IRQ_SELECT_NONE              = 0, ///< A periodic irq is not generated
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_2_SECOND = 1, ///< A periodic irq is generated every 1/2 second
    RTC_PERIODIC_IRQ_SELECT_1_SECOND          = 2, ///< A periodic irq is generated every 1 second
    RTC_PERIODIC_IRQ_SELECT_1_MINUTE          = 3, ///< A periodic irq is generated every 1 minute
    RTC_PERIODIC_IRQ_SELECT_1_HOUR            = 4, ///< A periodic irq is generated every 1 hour
    RTC_PERIODIC_IRQ_SELECT_1_DAY             = 5, ///< A periodic irq is generated every 1 day
    RTC_PERIODIC_IRQ_SELECT_1_MONTH           = 7, ///< A periodic irq is generated every 1 month
} rtc_periodic_irq_select_t;

/** ADC data resolution definitions */
typedef enum e_adc_resolution
{
    ADC_RESOLUTION_10_BIT = 0,         ///< 10 bit resolution
    ADC_RESOLUTION_8_BIT  = 1,         ///< 8 bit resolution
    ADC_RESOLUTION_12_BIT = 2,         ///< 12 bit resolution
} adc_resolution_t;

/** Events that can trigger a callback function */
typedef enum e_timer_event
{
    TIMER_EVENT_CYCLE_END,             ///< Requested timer delay has expired or timer has wrapped around
    TIMER_EVENT_HIGHER_8BIT_CYCLE_END, ///< Requested higher 8-bit timer has expired
    TIMER_EVENT_CAPTURE_EDGE,          ///< A capture has occurred when detecting edge
    TIMER_EVENT_SLAVE_CYCLE_END,       ///< Requested timer pulse width (One-shot) or duty cycle (PWM) has expired
    TIMER_EVENT_MASTER_CYCLE_END,      ///< Requested timer delay (One-shot) or period (PWM) has expired
} timer_event_t;

/** Clock source divisors */
typedef enum e_timer_source_div
{
    TIMER_SOURCE_DIV_1     = 0,        ///< Timer clock source divided by 1
    TIMER_SOURCE_DIV_2     = 1,        ///< Timer clock source divided by 2
    TIMER_SOURCE_DIV_4     = 2,        ///< Timer clock source divided by 4
    TIMER_SOURCE_DIV_8     = 3,        ///< Timer clock source divided by 8
    TIMER_SOURCE_DIV_16    = 4,        ///< Timer clock source divided by 16
    TIMER_SOURCE_DIV_32    = 5,        ///< Timer clock source divided by 32
    TIMER_SOURCE_DIV_64    = 6,        ///< Timer clock source divided by 64
    TIMER_SOURCE_DIV_128   = 7,        ///< Timer clock source divided by 128
    TIMER_SOURCE_DIV_256   = 8,        ///< Timer clock source divided by 256
    TIMER_SOURCE_DIV_512   = 9,        ///< Timer clock source divided by 512
    TIMER_SOURCE_DIV_1024  = 10,       ///< Timer clock source divided by 1024
    TIMER_SOURCE_DIV_2048  = 11,       ///< Timer clock source divided by 2048
    TIMER_SOURCE_DIV_4096  = 12,       ///< Timer clock source divided by 4096
    TIMER_SOURCE_DIV_8192  = 13,       ///< Timer clock source divided by 8912
    TIMER_SOURCE_DIV_16384 = 14,       ///< Timer clock source divided by 16384
    TIMER_SOURCE_DIV_32768 = 15,       ///< Timer clock source divided by 32768
} timer_source_div_t;

/** Timer operational modes */
typedef enum e_timer_mode
{
    TIMER_MODE_8_BIT_COUNTER  = 0U,    ///< 8-bit counter mode
    TIMER_MODE_16_BIT_COUNTER = 1U,    ///< 16-bit counter mode
    TIMER_MODE_32_BIT_COUNTER = 2U,    ///< 32-bit counter mode
    TIMER_MODE_16_BIT_CAPTURE = 3U,    ///< 16-bit capture mode
    TIMER_MODE_PERIODIC,               ///< Timer restarts after period elapses.
    TIMER_MODE_ONE_SHOT,               ///< Timer stops after period elapses.
    TIMER_MODE_PWM,                    ///< Timer generates saw-wave PWM output.
} timer_mode_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
