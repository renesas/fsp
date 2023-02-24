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
 * @defgroup LPM_API Low Power Modes Interface
 * @brief Interface for accessing low power modes.
 *
 * @section LPM_API_SUMMARY Summary
 * This section defines the API for the LPM (Low Power Mode) Driver.
 * The LPM Driver provides functions for controlling power consumption by configuring
 * and transitioning to a low power mode.
 * The LPM driver supports configuration of MCU low power modes using the LPM hardware
 * peripheral. The LPM driver supports low power modes deep standby, standby, sleep, and snooze.
 *
 * @note Not all low power modes are available on all MCUs.
 *
 * The LPM interface is implemented by:
 * - @ref LPM
 *
 * @{
 **********************************************************************************************************************/
#ifndef R_LPM_API_H
#define R_LPM_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Low power modes */
typedef enum e_lpm_mode
{
    LPM_MODE_SLEEP,                    ///< Sleep mode
    LPM_MODE_DEEP_SLEEP,               ///< Deep Sleep mode
    LPM_MODE_STANDBY,                  ///< Software Standby mode
    LPM_MODE_STANDBY_SNOOZE,           ///< Software Standby mode with Snooze mode enabled
    LPM_MODE_DEEP,                     ///< Deep Software Standby mode
} lpm_mode_t;

/** Snooze request sources */
typedef enum e_lpm_snooze_request
{
    LPM_SNOOZE_REQUEST_RXD0_FALLING   = 0x00000000ULL,  ///< Enable RXD0 falling edge snooze request
    LPM_SNOOZE_REQUEST_IRQ0           = 0x00000001ULL,  ///< Enable IRQ0 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ1           = 0x00000002ULL,  ///< Enable IRQ1 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ2           = 0x00000004ULL,  ///< Enable IRQ2 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ3           = 0x00000008ULL,  ///< Enable IRQ3 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ4           = 0x00000010ULL,  ///< Enable IRQ4 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ5           = 0x00000020ULL,  ///< Enable IRQ5 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ6           = 0x00000040ULL,  ///< Enable IRQ6 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ7           = 0x00000080ULL,  ///< Enable IRQ7 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ8           = 0x00000100ULL,  ///< Enable IRQ8 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ9           = 0x00000200ULL,  ///< Enable IRQ9 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ10          = 0x00000400ULL,  ///< Enable IRQ10 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ11          = 0x00000800ULL,  ///< Enable IRQ11 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ12          = 0x00001000ULL,  ///< Enable IRQ12 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ13          = 0x00002000ULL,  ///< Enable IRQ13 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ14          = 0x00004000ULL,  ///< Enable IRQ14 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ15          = 0x00008000ULL,  ///< Enable IRQ15 pin snooze request
    LPM_SNOOZE_REQUEST_KEY            = 0x00020000ULL,  ///< Enable KR snooze request
    LPM_SNOOZE_REQUEST_ACMPHS0        = 0x00400000ULL,  ///< Enable High-speed analog comparator 0 snooze request
    LPM_SNOOZE_REQUEST_RTC_ALARM      = 0x01000000ULL,  ///< Enable RTC alarm snooze request
    LPM_SNOOZE_REQUEST_RTC_PERIOD     = 0x02000000ULL,  ///< Enable RTC period snooze request
    LPM_SNOOZE_REQUEST_AGT1_UNDERFLOW = 0x10000000ULL,  ///< Enable AGT1 underflow snooze request
    LPM_SNOOZE_REQUEST_AGT1_COMPARE_A = 0x20000000ULL,  ///< Enable AGT1 compare match A snooze request
    LPM_SNOOZE_REQUEST_AGT1_COMPARE_B = 0x40000000ULL,  ///< Enable AGT1 compare match B snooze request
    LPM_SNOOZE_REQUEST_AGT3_UNDERFLOW = 0x100000000ULL, ///< Enable AGT3 underflow snooze request
    LPM_SNOOZE_REQUEST_AGT3_COMPARE_A = 0x200000000ULL, ///< Enable AGT3 compare match A snooze request
    LPM_SNOOZE_REQUEST_AGT3_COMPARE_B = 0x400000000ULL, ///< Enable AGT3 compare match B snooze request
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
    LPM_SNOOZE_END_ADC1_COMPARE_MATCH         = 0x20U,  ///< ADC 1 compare match
    LPM_SNOOZE_END_ADC1_COMPARE_MISMATCH      = 0x40U,  ///< ADC 1 compare mismatch
    LPM_SNOOZE_END_SCI0_ADDRESS_MATCH         = 0x80U,  ///< SCI0 address mismatch
    LPM_SNOOZE_END_AGT3_UNDERFLOW             = 0x100U, ///< AGT3 underflow
} lpm_snooze_end_t;

typedef uint16_t lpm_snooze_end_bits_t;

/** Snooze cancel control */
typedef enum e_lpm_snooze_cancel
{
    LPM_SNOOZE_CANCEL_SOURCE_NONE       = ELC_EVENT_NONE,                     ///< No snooze cancel source
    LPM_SNOOZE_CANCEL_SOURCE_ADC0_WCMPM = ELC_EVENT_ADC0_COMPARE_MATCH,       ///< ADC Channel 0 window compare match
#if (2U != BSP_FEATURE_ELC_VERSION)
    LPM_SNOOZE_CANCEL_SOURCE_ADC0_WCMPUM = ELC_EVENT_ADC0_COMPARE_MISMATCH,   ///< ADC Channel 0 window compare mismatch
#endif
#if BSP_FEATURE_ADC_VALID_UNIT_MASK & (1U << 1)                               // If ADC has unit 1
    LPM_SNOOZE_CANCEL_SOURCE_ADC1_WCMPM = ELC_EVENT_ADC1_COMPARE_MATCH,       ///< ADC Channel 1 window compare match
 #if (2U != BSP_FEATURE_ELC_VERSION)
    LPM_SNOOZE_CANCEL_SOURCE_ADC1_WCMPUM = ELC_EVENT_ADC1_COMPARE_MISMATCH,   ///< ADC Channel 1 window compare mismatch
 #endif
#endif
#if (BSP_FEATURE_SCI_CHANNELS & (1U << 0)) && (2U != BSP_FEATURE_ELC_VERSION) // If SCI has channel 0
    LPM_SNOOZE_CANCEL_SOURCE_SCI0_AM         = ELC_EVENT_SCI0_AM,             ///< SCI0 address match event
    LPM_SNOOZE_CANCEL_SOURCE_SCI0_RXI_OR_ERI = ELC_EVENT_SCI0_RXI_OR_ERI,     ///< SCI0 receive error
#endif
    LPM_SNOOZE_CANCEL_SOURCE_DTC_COMPLETE = ELC_EVENT_DTC_COMPLETE,           ///< DTC transfer completion
    LPM_SNOOZE_CANCEL_SOURCE_DOC_DOPCI    = ELC_EVENT_DOC_INT,                ///< Data operation circuit interrupt
#if BSP_FEATURE_CTSU_VERSION
    LPM_SNOOZE_CANCEL_SOURCE_CTSU_CTSUFN = ELC_EVENT_CTSU_END,                ///< CTSU measurement end interrupt
#endif
} lpm_snooze_cancel_t;

/** DTC Enable in Snooze Mode */
typedef enum e_lpm_snooze_dtc
{
    LPM_SNOOZE_DTC_DISABLE = 0U,       ///< Disable DTC operation
    LPM_SNOOZE_DTC_ENABLE  = 1U,       ///< Enable DTC operation
} lpm_snooze_dtc_t;

/** Wake from deep sleep or standby mode sources, does not apply to sleep or deep standby modes */
typedef enum e_lpm_standby_wake_source
{
    LPM_STANDBY_WAKE_SOURCE_IRQ0    = 0x00000001ULL,      ///< IRQ0
    LPM_STANDBY_WAKE_SOURCE_IRQ1    = 0x00000002ULL,      ///< IRQ1
    LPM_STANDBY_WAKE_SOURCE_IRQ2    = 0x00000004ULL,      ///< IRQ2
    LPM_STANDBY_WAKE_SOURCE_IRQ3    = 0x00000008ULL,      ///< IRQ3
    LPM_STANDBY_WAKE_SOURCE_IRQ4    = 0x00000010ULL,      ///< IRQ4
    LPM_STANDBY_WAKE_SOURCE_IRQ5    = 0x00000020ULL,      ///< IRQ5
    LPM_STANDBY_WAKE_SOURCE_IRQ6    = 0x00000040ULL,      ///< IRQ6
    LPM_STANDBY_WAKE_SOURCE_IRQ7    = 0x00000080ULL,      ///< IRQ7
    LPM_STANDBY_WAKE_SOURCE_IRQ8    = 0x00000100ULL,      ///< IRQ8
    LPM_STANDBY_WAKE_SOURCE_IRQ9    = 0x00000200ULL,      ///< IRQ9
    LPM_STANDBY_WAKE_SOURCE_IRQ10   = 0x00000400ULL,      ///< IRQ10
    LPM_STANDBY_WAKE_SOURCE_IRQ11   = 0x00000800ULL,      ///< IRQ11
    LPM_STANDBY_WAKE_SOURCE_IRQ12   = 0x00001000ULL,      ///< IRQ12
    LPM_STANDBY_WAKE_SOURCE_IRQ13   = 0x00002000ULL,      ///< IRQ13
    LPM_STANDBY_WAKE_SOURCE_IRQ14   = 0x00004000ULL,      ///< IRQ14
    LPM_STANDBY_WAKE_SOURCE_IRQ15   = 0x00008000ULL,      ///< IRQ15
    LPM_STANDBY_WAKE_SOURCE_IWDT    = 0x00010000ULL,      ///< Independent watchdog interrupt
    LPM_STANDBY_WAKE_SOURCE_KEY     = 0x00020000ULL,      ///< Key interrupt
    LPM_STANDBY_WAKE_SOURCE_LVD1    = 0x00040000ULL,      ///< Low Voltage Detection 1 interrupt
    LPM_STANDBY_WAKE_SOURCE_LVD2    = 0x00080000ULL,      ///< Low Voltage Detection 2 interrupt
    LPM_STANDBY_WAKE_SOURCE_VBATT   = 0x00100000ULL,      ///< VBATT Monitor interrupt
    LPM_STANDBY_WAKE_SOURCE_ACMPHS0 = 0x00400000ULL,      ///< Analog Comparator High-speed 0 interrupt
    LPM_STANDBY_WAKE_SOURCE_ACMPLP0 = 0x00800000ULL,      ///< Analog Comparator Low-speed 0 interrupt
    LPM_STANDBY_WAKE_SOURCE_RTCALM  = 0x01000000ULL,      ///< RTC Alarm interrupt
    LPM_STANDBY_WAKE_SOURCE_RTCPRD  = 0x02000000ULL,      ///< RTC Period interrupt
    LPM_STANDBY_WAKE_SOURCE_USBHS   = 0x04000000ULL,      ///< USB High-speed interrupt
    LPM_STANDBY_WAKE_SOURCE_USBFS   = 0x08000000ULL,      ///< USB Full-speed interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1UD  = 0x10000000ULL,      ///< AGT1 underflow interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1CA  = 0x20000000ULL,      ///< AGT1 compare match A interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1CB  = 0x40000000ULL,      ///< AGT1 compare match B interrupt
    LPM_STANDBY_WAKE_SOURCE_IIC0    = 0x80000000ULL,      ///< I2C 0 interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT3UD  = 0x100000000ULL,     ///< AGT3 underflow interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT3CA  = 0x200000000ULL,     ///< AGT3 compare match A interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT3CB  = 0x400000000ULL,     ///< AGT3 compare match B interrupt
    LPM_STANDBY_WAKE_SOURCE_COMPHS0 = 0x800000000ULL,     ///< Comparator-HS0 Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP0U   = 0x10000000000ULL,   ///< ULPT0 Underflow Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP0A   = 0x20000000000ULL,   ///< ULPT0 Compare Match A Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP0B   = 0x40000000000ULL,   ///< ULPT0 Compare Match B Interrupt
    LPM_STANDBY_WAKE_SOURCE_I3C0    = 0x800000000000ULL,  ///< I3C0 address match interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP1U   = 0x1000000000000ULL, ///< ULPT1 Underflow Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP1A   = 0x2000000000000ULL, ///< ULPT1 Compare Match A Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP1B   = 0x4000000000000ULL, ///< ULPT1 Compare Match B Interrupt
} lpm_standby_wake_source_t;

typedef uint64_t lpm_standby_wake_source_bits_t;

/** I/O port state after Deep Software Standby mode */
typedef enum e_lpm_io_port
{
    /**
     * When the Deep Software Standby mode is canceled, the I/O ports are in the reset state
     */
    LPM_IO_PORT_RESET = 0U,

    /**
     * When the Deep Software Standby mode is canceled, the I/O ports are in the same state as
     * in the Deep Software Standby mode
     */
    LPM_IO_PORT_NO_CHANGE = 1U,
} lpm_io_port_t;

/** Power supply control */
typedef enum e_lpm_power_supply
{
    /**
     * Power to the standby RAM, Low-speed on-chip oscillator, AGTn, and USBFS/HS resume
     * detecting unit is supplied in deep software standby mode
     */
    LPM_POWER_SUPPLY_DEEPCUT0 = 0U,

    /**
     * Power to the standby RAM, Low-speed on-chip oscillator, AGTn, and USBFS/HS resume
     * detecting unit is not supplied in deep software standby mode
     */
    LPM_POWER_SUPPLY_DEEPCUT1 = 1U,

    /**
     * Power to the standby RAM, Low-speed on-chip oscillator, AGTn, and USBFS/HS resume
     * detecting unit is not supplied in deep software standby mode. In addition, LVD is
     * disabled and the low power function in a poweron reset circuit is enabled
     */
    LPM_POWER_SUPPLY_DEEPCUT3 = 3UL,

    /**
     * Power to the standby RAM, Low-speed on-chip oscillator, Programmable Voltage Detection Unit 0,
     * and USBFS/HS resume detecting unit is supplied in deep software standby mode.
     */
    LPM_POWER_SUPPLY_DEEP_STANDBY_MODE1 = 0U,

    /**
     * Power to standby RAM, USBFS/HS resume detecting unit, Low-speed on-chip oscillator, and IWDT is
     * disabled in deep software standby mode. Power to the Programmable Voltage Detection Unit 0 is
     * supplied in deep software standby mode.
     */
    LPM_POWER_SUPPLY_DEEP_STANDBY_MODE2 = 1U,

    /**
     * Power to standby RAM, Programmable Voltage Detection Unit 0, USBFS/HS resume detecting unit,
     * Low-speed on-chip oscillator, and IWDT is disabled in deep software standby mode.
     */
    LPM_POWER_SUPPLY_DEEP_STANDBY_MODE3 = 2U,
} lpm_power_supply_t;

/** Deep Standby Interrupt Edge */
typedef enum e_lpm_deep_standby_cancel_edge
{
    LPM_DEEP_STANDBY_CANCEL_SOURCE_EDGE_NONE    = 0U,           ///< No options for a deep standby cancel source
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ0_RISING  = 0x00000001U,  ///< IRQ0-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ0_FALLING = 0U,           ///< IRQ0-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ1_RISING  = 0x00000002U,  ///< IRQ1-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ1_FALLING = 0U,           ///< IRQ1-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ2_RISING  = 0x00000004U,  ///< IRQ2-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ2_FALLING = 0U,           ///< IRQ2-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ3_RISING  = 0x00000008U,  ///< IRQ3-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ3_FALLING = 0U,           ///< IRQ3-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ4_RISING  = 0x00000010U,  ///< IRQ4-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ4_FALLING = 0U,           ///< IRQ4-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ5_RISING  = 0x00000020U,  ///< IRQ5-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ5_FALLING = 0U,           ///< IRQ5-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ6_RISING  = 0x00000040U,  ///< IRQ6-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ6_FALLING = 0U,           ///< IRQ6-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ7_RISING  = 0x00000080U,  ///< IRQ7-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ7_FALLING = 0U,           ///< IRQ7-DS Pin Falling Edge

    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ8_RISING   = 0x00000100U, ///< IRQ8-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ8_FALLING  = 0U,          ///< IRQ8-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ9_RISING   = 0x00000200U, ///< IRQ9-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ9_FALLING  = 0U,          ///< IRQ9-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ10_RISING  = 0x00000400U, ///< IRQ10-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ10_FALLING = 0U,          ///< IRQ10-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ11_RISING  = 0x00000800U, ///< IRQ11-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ11_FALLING = 0U,          ///< IRQ11-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ12_RISING  = 0x00001000U, ///< IRQ12-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ12_FALLING = 0U,          ///< IRQ12-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ13_RISING  = 0x00002000U, ///< IRQ13-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ13_FALLING = 0U,          ///< IRQ13-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ14_RISING  = 0x00004000U, ///< IRQ14-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ14_FALLING = 0U,          ///< IRQ14-DS Pin Falling Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ15_RISING  = 0x00008000U, ///< IRQ14-DS Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ15_FALLING = 0U,          ///< IRQ14-DS Pin Falling Edge

    LPM_DEEP_STANDBY_CANCEL_SOURCE_LVD1_RISING  = 0x00010000U,  ///< LVD1 Rising Slope
    LPM_DEEP_STANDBY_CANCEL_SOURCE_LVD1_FALLING = 0U,           ///< LVD1 Falling Slope
    LPM_DEEP_STANDBY_CANCEL_SOURCE_LVD2_RISING  = 0x00020000U,  ///< LVD2 Rising Slope
    LPM_DEEP_STANDBY_CANCEL_SOURCE_LVD2_FALLING = 0U,           ///< LVD2 Falling Slope
    LPM_DEEP_STANDBY_CANCEL_SOURCE_NMI_RISING   = 0x00100000U,  ///< NMI Pin Rising Edge
    LPM_DEEP_STANDBY_CANCEL_SOURCE_NMI_FALLING  = 0U,           ///< NMI Pin Falling Edge
} lpm_deep_standby_cancel_edge_t;

typedef uint32_t lpm_deep_standby_cancel_edge_bits_t;

/** Deep Standby cancel sources */
typedef enum e_lpm_deep_standby_cancel_source
{
    LPM_DEEP_STANDBY_CANCEL_SOURCE_RESET_ONLY = 0U,            ///< Cancel deep standby only by reset

    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ0 = 0x00000001U,         ///< IRQ0
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ1 = 0x00000002U,         ///< IRQ1
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ2 = 0x00000004U,         ///< IRQ2
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ3 = 0x00000008U,         ///< IRQ3
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ4 = 0x00000010U,         ///< IRQ4
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ5 = 0x00000020U,         ///< IRQ5
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ6 = 0x00000040U,         ///< IRQ6
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ7 = 0x00000080U,         ///< IRQ7

    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ8  = 0x00000100U,        ///< IRQ8
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ9  = 0x00000200U,        ///< IRQ9
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ10 = 0x00000400U,        ///< IRQ10
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ11 = 0x00000800U,        ///< IRQ11
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ12 = 0x00001000U,        ///< IRQ12
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ13 = 0x00002000U,        ///< IRQ13
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ14 = 0x00004000U,        ///< IRQ14
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ15 = 0x00008000U,        ///< IRQ15

    LPM_DEEP_STANDBY_CANCEL_SOURCE_LVD1         = 0x00010000U, ///< LVD1
    LPM_DEEP_STANDBY_CANCEL_SOURCE_LVD2         = 0x00020000U, ///< LVD2
    LPM_DEEP_STANDBY_CANCEL_SOURCE_RTC_INTERVAL = 0x00040000U, ///< RTC Interval Interrupt
    LPM_DEEP_STANDBY_CANCEL_SOURCE_RTC_ALARM    = 0x00080000U, ///< RTC Alarm Interrupt
    LPM_DEEP_STANDBY_CANCEL_SOURCE_NMI          = 0x00100000U, ///< NMI

    LPM_DEEP_STANDBY_CANCEL_SOURCE_USBFS = 0x01000000U,        ///< USBFS Suspend/Resume
    LPM_DEEP_STANDBY_CANCEL_SOURCE_USBHS = 0x02000000U,        ///< USBHS Suspend/Resume
    LPM_DEEP_STANDBY_CANCEL_SOURCE_AGT1  = 0x04000000U,        ///< AGT1 Underflow
    LPM_DEEP_STANDBY_CANCEL_SOURCE_AGT3  = 0x08000000U,        ///< AGT3 Underflow
    LPM_DEEP_STANDBY_CANCEL_SOURCE_ULPT0 = 0x04000000U,        ///< ULPT0 Overflow
    LPM_DEEP_STANDBY_CANCEL_SOURCE_ULPT1 = 0x08000000U,        ///< ULPT1 Overflow
    LPM_DEEP_STANDBY_CANCEL_SOURCE_IWDT  = 0x20000000U,        ///< IWDT Underflow
    LPM_DEEP_STANDBY_CANCEL_SOURCE_VBATT = 0x80000000U,        ///< VBATT Tamper Detection
} lpm_deep_standby_cancel_source_t;

typedef uint32_t lpm_deep_standby_cancel_source_bits_t;

/** Output port enable */
typedef enum e_lpm_output_port_enable
{
    /**
     * 0: In Software Standby Mode or Deep Software Standby Mode, the
     * address output pins, data output pins, and other bus control signal
     * output pins are set to the high-impedance state. In Snooze, the
     * status of the address bus and bus control signals are same as
     * before entering Software Standby Mode.
     */
    LPM_OUTPUT_PORT_ENABLE_HIGH_IMPEDANCE = 0U,

    /**
     * 1: In Software Standby Mode, the address output pins, data output
     * pins, and other bus control signal output pins retain the
     * output state.
     */
    LPM_OUTPUT_PORT_ENABLE_RETAIN = 1U,
} lpm_output_port_enable_t;

/** Configure the behavior of an oscillator's LDO in standby mode. */
typedef enum e_lpm_ldo_standby_operation
{
    /** The LDO is disabled in standby mode. */
    LPM_LDO_STANDBY_OPERATION_DISABLED,

    /** The LDO state is retained during standby mode. */
    LPM_LDO_STANDBY_OPERATION_RETAINED,
} lpm_ldo_standby_operation_t;

#if BSP_FEATURE_LPM_HAS_PDRAMSCR || BSP_FEATURE_LPM_HAS_DPSBYCR_SRKEEP
/** RAM Retention Configuration for deep sleep and standby modes. */
typedef struct s_lpm_ram_retention
{
#if BSP_FEATURE_LPM_HAS_PDRAMSCR
    /** Configure RAM retention in software standby mode. */
    uint16_t ram_retention;

    /** Enable or disable TCM retention in deep sleep and software standby modes. */
    bool tcm_retention;
#endif
#if BSP_FEATURE_LPM_HAS_DPSBYCR_SRKEEP
    /** Enable Standby RAM retention in software standby and deep software standby modes. */
    bool standby_ram_retention;
#endif
} lpm_ram_retention_t;
#endif

/** Configure LDO operation in standby mode. */
typedef struct lpm_ldo_standby_cfg_s
{
    lpm_ldo_standby_operation_t pll1_ldo; ///< Configure the state of PLL1 LDO in standby mode.
    lpm_ldo_standby_operation_t pll2_ldo; ///< Configure the state of PLL2 LDO in standby mode.
    lpm_ldo_standby_operation_t hoco_ldo; ///< Configure the state of HOCO LDO in standby mode.
} lpm_ldo_standby_cfg_t;

/** User configuration structure, used in open function */
typedef struct st_lpm_cfg
{
    /** Low Power Mode */
    lpm_mode_t low_power_mode;

    /** Bitwise list of sources to wake from deep sleep and standby mode */
    lpm_standby_wake_source_bits_t standby_wake_sources;

#if BSP_FEATURE_LPM_HAS_SNOOZE

    /** Snooze request source */
    lpm_snooze_request_t snooze_request_source;

    /** Bitwise list of snooze end sources */
    lpm_snooze_end_bits_t snooze_end_sources;

    /** List of snooze cancel sources */
    lpm_snooze_cancel_t snooze_cancel_sources;
#endif

    /** State of DTC in snooze mode, enabled or disabled */
    lpm_snooze_dtc_t dtc_state_in_snooze;
#if BSP_FEATURE_LPM_HAS_SBYCR_OPE

    /** Output port enabled/disabled in standby and deep standby */
    lpm_output_port_enable_t output_port_enable;
#endif
#if BSP_FEATURE_LPM_HAS_DEEP_STANDBY

    /** IO port state in deep standby (maintained or reset) */
    lpm_io_port_t io_port_state;

    /** Internal power supply state in standby and deep standby (deepcut) */
    lpm_power_supply_t power_supply_state;

    /** Sources that can trigger exit from deep standby */
    lpm_deep_standby_cancel_source_bits_t deep_standby_cancel_source;

    /** Signal edges for the sources that can trigger exit from deep standby */
    lpm_deep_standby_cancel_edge_bits_t deep_standby_cancel_edge;
#endif

#if BSP_FEATURE_LPM_HAS_PDRAMSCR || BSP_FEATURE_LPM_HAS_DPSBYCR_SRKEEP

    /** RAM retention configuration for deep sleep and standby modes. */
    lpm_ram_retention_t ram_retention_cfg;
#endif

#if BSP_FEATURE_LPM_HAS_LDO_CONTROL

    /** Configure LDOs that are disabled in standby mode. */
    lpm_ldo_standby_cfg_t ldo_standby_cfg;
#endif

    /** Placeholder for extension. */
    void const * p_extend;
} lpm_cfg_t;

/** LPM control block.  Allocate an instance specific control block to pass into the LPM API calls.
 * @par Implemented as
 * - lpm_instance_ctrl_t
 */
typedef void lpm_ctrl_t;

/** LPM driver structure. General LPM functions implemented at the HAL layer will follow this API. */
typedef struct st_lpm_api
{
    /** Initialization function
     * @par Implemented as
     * - @ref R_LPM_Open()
     **/

    fsp_err_t (* open)(lpm_ctrl_t * const p_api_ctrl, lpm_cfg_t const * const p_cfg);

    /** Initialization function
     * @par Implemented as
     * - @ref R_LPM_Close()
     **/
    fsp_err_t (* close)(lpm_ctrl_t * const p_api_ctrl);

    /** Configure a low power mode.
     * @par Implemented as
     * - @ref R_LPM_LowPowerReconfigure()
     *
     * @param[in]   p_cfg   Pointer to configuration structure. All elements of this structure must be set by user.
     **/
    fsp_err_t (* lowPowerReconfigure)(lpm_ctrl_t * const p_api_ctrl, lpm_cfg_t const * const p_cfg);

    /** Enter low power mode (sleep/standby/deep standby) using WFI macro.
     *  Function will return after waking from low power mode.
     * @par Implemented as
     * - @ref R_LPM_LowPowerModeEnter()
     **/
    fsp_err_t (* lowPowerModeEnter)(lpm_ctrl_t * const p_api_ctrl);

    /** Clear the IOKEEP bit after deep software standby.
     * * @par Implemented as
     * - @ref R_LPM_IoKeepClear()
     **/
    fsp_err_t (* ioKeepClear)(lpm_ctrl_t * const p_api_ctrl);
} lpm_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_lpm_instance
{
    lpm_ctrl_t            * p_ctrl;    ///< Pointer to the control structure for this instance
    lpm_cfg_t const * const p_cfg;     ///< Pointer to the configuration structure for this instance
    lpm_api_t const * const p_api;     ///< Pointer to the API structure for this instance
} lpm_instance_t;

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup LPM_API)
 **********************************************************************************************************************/
