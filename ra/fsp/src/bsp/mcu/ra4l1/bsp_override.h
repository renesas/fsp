/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA4L1
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RA4L1) */

#ifndef BSP_OVERRIDE_H
#define BSP_OVERRIDE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Define overrides required for this MCU. */
#define BSP_OVERRIDE_LVD_PERIPHERAL_T
#define BSP_OVERRIDE_LPM_STANDBY_WAKE_SOURCE_T
#define BSP_OVERRIDE_LPM_SNOOZE_REQUEST_T
#define BSP_OVERRIDE_LPM_SNOOZE_END_T
#define BSP_OVERRIDE_UART_DATA_BITS_T

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** PLL divider values */

/** The thresholds supported by each MCU are in the MCU User's Manual as well as
 *  in the r_lvd module description on the stack tab of the RA project. */
typedef enum
{
    LVD_THRESHOLD_MONITOR_1_LEVEL_3_10V = 0x00UL, ///< 3.10V
    LVD_THRESHOLD_MONITOR_1_LEVEL_3_00V = 0x01UL, ///< 3.00V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_90V = 0x02UL, ///< 2.90V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_79V = 0x03UL, ///< 2.79V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_68V = 0x04UL, ///< 2.68V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_58V = 0x05UL, ///< 2.58V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_48V = 0x06UL, ///< 2.48V
    LVD_THRESHOLD_MONITOR_1_LEVEL_2_20V = 0x07UL, ///< 2.20V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_96V = 0x08UL, ///< 1.96V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_86V = 0x09UL, ///< 1.86V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_75V = 0x0AUL, ///< 1.75V
    LVD_THRESHOLD_MONITOR_1_LEVEL_1_65V = 0x0BUL, ///< 1.65V
    LVD_THRESHOLD_MONITOR_2_LEVEL_3_13V = 0x00UL, ///< 3.13V
    LVD_THRESHOLD_MONITOR_2_LEVEL_2_92V = 0x01UL, ///< 2.92V
    LVD_THRESHOLD_MONITOR_2_LEVEL_2_71V = 0x02UL, ///< 2.71V
    LVD_THRESHOLD_MONITOR_2_LEVEL_2_50V = 0x03UL, ///< 2.50V
    LVD_THRESHOLD_MONITOR_2_LEVEL_2_30V = 0x04UL, ///< 2.30V
    LVD_THRESHOLD_MONITOR_2_LEVEL_2_09V = 0x05UL, ///< 2.09V
    LVD_THRESHOLD_MONITOR_2_LEVEL_1_88V = 0x06UL, ///< 1.88V
    LVD_THRESHOLD_MONITOR_2_LEVEL_1_67V = 0x07UL, ///< 1.67V
    LVD_THRESHOLD_NOT_AVAILABLE         = 0xFFUL, ///< Not Used
} lvd_threshold_t;

/** Wake from deep sleep or standby mode sources, does not apply to sleep or deep standby modes */
typedef enum e_lpm_standby_wake_source
{
    LPM_STANDBY_WAKE_SOURCE_IRQ0    = 0x00000001ULL,    ///< IRQ0
    LPM_STANDBY_WAKE_SOURCE_IRQ1    = 0x00000002ULL,    ///< IRQ1
    LPM_STANDBY_WAKE_SOURCE_IRQ2    = 0x00000004ULL,    ///< IRQ2
    LPM_STANDBY_WAKE_SOURCE_IRQ3    = 0x00000008ULL,    ///< IRQ3
    LPM_STANDBY_WAKE_SOURCE_IRQ4    = 0x00000010ULL,    ///< IRQ4
    LPM_STANDBY_WAKE_SOURCE_IRQ5    = 0x00000020ULL,    ///< IRQ5
    LPM_STANDBY_WAKE_SOURCE_IRQ6    = 0x00000040ULL,    ///< IRQ6
    LPM_STANDBY_WAKE_SOURCE_IRQ7    = 0x00000080ULL,    ///< IRQ7
    LPM_STANDBY_WAKE_SOURCE_IRQ8    = 0x00000100ULL,    ///< IRQ8
    LPM_STANDBY_WAKE_SOURCE_IRQ9    = 0x00000200ULL,    ///< IRQ9
    LPM_STANDBY_WAKE_SOURCE_IRQ10   = 0x00000400ULL,    ///< IRQ10
    LPM_STANDBY_WAKE_SOURCE_IRQ11   = 0x00000800ULL,    ///< IRQ11
    LPM_STANDBY_WAKE_SOURCE_IRQ12   = 0x00001000ULL,    ///< IRQ12
    LPM_STANDBY_WAKE_SOURCE_IRQ13   = 0x00002000ULL,    ///< IRQ13
    LPM_STANDBY_WAKE_SOURCE_IRQ14   = 0x00004000ULL,    ///< IRQ14
    LPM_STANDBY_WAKE_SOURCE_IRQ15   = 0x00008000ULL,    ///< IRQ15
    LPM_STANDBY_WAKE_SOURCE_IWDT    = 0x00010000ULL,    ///< Independent watchdog interrupt
    LPM_STANDBY_WAKE_SOURCE_LVD1    = 0x00040000ULL,    ///< Low Voltage Detection 1 interrupt
    LPM_STANDBY_WAKE_SOURCE_LVD2    = 0x00080000ULL,    ///< Low Voltage Detection 2 interrupt
    LPM_STANDBY_WAKE_SOURCE_ACMPLP0 = 0x00800000ULL,    ///< Analog Comparator Low-speed 0 interrupt
    LPM_STANDBY_WAKE_SOURCE_RTCALM  = 0x01000000ULL,    ///< RTC Alarm interrupt
    LPM_STANDBY_WAKE_SOURCE_RTCPRD  = 0x02000000ULL,    ///< RTC Period interrupt
    LPM_STANDBY_WAKE_SOURCE_USBFS   = 0x08000000ULL,    ///< USB Full-speed interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1UD  = 0x10000000ULL,    ///< AGT1 Underflow interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1CA  = 0x20000000ULL,    ///< AGT1 Compare Match A interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1CB  = 0x40000000ULL,    ///< AGT1 Compare Match B interrupt
    LPM_STANDBY_WAKE_SOURCE_IIC0    = 0x80000000ULL,    ///< I2C 0 interrupt
    LPM_STANDBY_WAKE_SOURCE_SOSTD   = 0x8000000000ULL,  ///< SOSTD interrupt
    LPM_STANDBY_WAKE_SOURCE_I3C0    = 0x80000000000ULL, ///< I3C0 address match interrupt
} lpm_standby_wake_source_t;

typedef enum e_lpm_standby_wake_source_2
{
    LPM_STANDBY_WAKE_SOURCE_INTUR0  = 0x00000001ULL, ///< UARTA0 INTUR Interrupt
    LPM_STANDBY_WAKE_SOURCE_INTURE0 = 0x00000002ULL, ///< UARTA0 INTURE Interrupt
    LPM_STANDBY_WAKE_SOURCE_INTUR1  = 0x00000004ULL, ///< UARTA1 INTUR Interrupt
    LPM_STANDBY_WAKE_SOURCE_INTURE1 = 0x00000008ULL, ///< UARTA1 INTURE Interrupt
    LPM_STANDBY_WAKE_SOURCE_USBCCS  = 0x00000010ULL, ///< USBCC Status Change Interrupt
} lpm_standby_wake_source_2_t;

typedef uint64_t lpm_standby_wake_source_bits_t;

/** Snooze request sources */
typedef enum e_lpm_snooze_request
{
    LPM_SNOOZE_REQUEST_RXD0_FALLING   = 0x00000000ULL, ///< Enable RXD0 falling edge snooze request
    LPM_SNOOZE_REQUEST_IRQ0           = 0x00000001ULL, ///< Enable IRQ0 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ1           = 0x00000002ULL, ///< Enable IRQ1 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ2           = 0x00000004ULL, ///< Enable IRQ2 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ3           = 0x00000008ULL, ///< Enable IRQ3 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ4           = 0x00000010ULL, ///< Enable IRQ4 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ5           = 0x00000020ULL, ///< Enable IRQ5 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ6           = 0x00000040ULL, ///< Enable IRQ6 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ7           = 0x00000080ULL, ///< Enable IRQ7 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ8           = 0x00000100ULL, ///< Enable IRQ8 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ9           = 0x00000200ULL, ///< Enable IRQ9 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ10          = 0x00000400ULL, ///< Enable IRQ10 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ11          = 0x00000800ULL, ///< Enable IRQ11 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ12          = 0x00001000ULL, ///< Enable IRQ12 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ13          = 0x00002000ULL, ///< Enable IRQ13 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ14          = 0x00004000ULL, ///< Enable IRQ14 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ15          = 0x00008000ULL, ///< Enable IRQ15 pin snooze request
    LPM_SNOOZE_REQUEST_ACMPLP0        = 0x00800000ULL, ///< Enable Low-speed analog comparator 0 snooze request
    LPM_SNOOZE_REQUEST_RTC_ALARM      = 0x01000000ULL, ///< Enable RTC alarm snooze request
    LPM_SNOOZE_REQUEST_RTC_PERIOD     = 0x02000000ULL, ///< Enable RTC period snooze request
    LPM_SNOOZE_REQUEST_AGT1_UNDERFLOW = 0x10000000ULL, ///< Enable AGT1 underflow snooze request
    LPM_SNOOZE_REQUEST_AGT1_COMPARE_A = 0x20000000ULL, ///< Enable AGT1 compare match A snooze request
    LPM_SNOOZE_REQUEST_AGT1_COMPARE_B = 0x40000000ULL, ///< Enable AGT1 compare match B snooze request
} lpm_snooze_request_t;

/** Snooze end control */
typedef enum e_lpm_snooze_end
{
    LPM_SNOOZE_END_STANDBY_WAKE_SOURCES       = 0x00U,  ///< Transition from Snooze to Normal mode directly
    LPM_SNOOZE_END_AGT1_UNDERFLOW             = 0x01U,  ///< AGT1 underflow
    LPM_SNOOZE_END_DTC_TRANS_COMPLETE         = 0x02U,  ///< Last DTC transmission completion
    LPM_SNOOZE_END_DTC_TRANS_COMPLETE_NEGATED = 0x04U,  ///< Not Last DTC transmission completion
    LPM_SNOOZE_END_ADC0_COMPARE_MATCH         = 0x08U,  ///< ADC Channel 0 compare match
    LPM_SNOOZE_END_ADC0_COMPARE_MISMATCH      = 0x10U,  ///< ADC Channel 0 compare mismatch
    LPM_SNOOZE_END_SCI0_ADDRESS_MISMATCH      = 0x80U,  ///< SCI0 address mismatch
    LPM_SNOOZE_END_CTSU_NAJED                 = 0x200U, ///< CTSU2SLa non-touch automatic judgment
} lpm_snooze_end_t;

typedef uint16_t lpm_snooze_end_bits_t;

/** UART Data bit length definition */
typedef enum e_uart_data_bits
{
    UART_DATA_BITS_5 = 0U,             ///< Data bits 5-bit
    UART_DATA_BITS_9 = 1U,             ///< Data bits 9-bit
    UART_DATA_BITS_7 = 2U,             ///< Data bits 7-bit
    UART_DATA_BITS_8 = 3U,             ///< Data bits 8-bit
} uart_data_bits_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
