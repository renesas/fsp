/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_ELC_H
#define BSP_ELC_H

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA0E1
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/* UNCRUSTIFY-OFF */

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list is device specific.
 * */
typedef enum e_elc_event_ra0e1
{
    ELC_EVENT_NONE                          = (0x0),   // Link disabled
    ELC_EVENT_ICU_IRQ0                      = (0x001), // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1                      = (0x002), // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2                      = (0x003), // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3                      = (0x004), // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4                      = (0x005), // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5                      = (0x006), // External pin interrupt 5
    ELC_EVENT_RTC_ALARM_OR_PERIOD           = (0x007), // Alarm or Periodic interrupt
    ELC_EVENT_TML0_ITL0                     = (0x008), // TML timer0 compare-match
    ELC_EVENT_TML0_ITL1                     = (0x009), // TML timer1 compare-match
    ELC_EVENT_TML0_ITL2                     = (0x00A), // TML timer2 compare-match
    ELC_EVENT_TML0_ITL3                     = (0x00B), // TML timer3 compare-match
    ELC_EVENT_TAU0_TMI00                    = (0x00C), // End of timer channel 00 count or capture
    ELC_EVENT_TAU0_TMI01                    = (0x00D), // End of timer channel 01 count or capture
    ELC_EVENT_TAU0_TMI02                    = (0x00E), // End of timer channel 02 count or capture
    ELC_EVENT_TAU0_TMI03                    = (0x00F), // End of timer channel 03 count or capture
    ELC_EVENT_SAU0_UART_TXI0                = (0x010), // SAU UART TX 0/I2C 00/SPI 00
    ELC_EVENT_SAU0_UART_RXI0                = (0x011), // SAU UART RX 0/I2C 01/SPI 01
    ELC_EVENT_DTC_END                       = (0x012), // DTC transfer end
    ELC_EVENT_LVD_LVD1                      = (0x013), // Voltage monitor 1 interrupt
    ELC_EVENT_ELC_SOFTWARE_EVENT_0          = (0x014), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1          = (0x015), // Software event 1
    ELC_EVENT_ADC0_SCAN_END                 = (0x016), // End of A/D scanning operation
    ELC_EVENT_UARTA0_ERRI                   = (0x017), // Reception error interrupt
    ELC_EVENT_UARTA0_TXI                    = (0x018), // Transfer completion interrupt
    ELC_EVENT_UARTA0_RXI                    = (0x019), // Reception transfer end
    ELC_EVENT_IICA0_TXRXI                   = (0x01A)  // Communication event
} elc_event_t;

/** Fixed vector enumeration
 * @note This list is device specific.
 * */
typedef enum e_icu_event_ra0e1
{
    ICU_EVENT_IWDT_UNDERFLOW                = (0), // IWDT underflow
    ICU_EVENT_LVD_LVD1                      = (1), // Voltage monitor 1 interrupt
    ICU_EVENT_ICU_IRQ0                      = (2), // External pin interrupt 0
    ICU_EVENT_ICU_IRQ1                      = (3), // External pin interrupt 1
    ICU_EVENT_ICU_IRQ2                      = (4), // External pin interrupt 2
    ICU_EVENT_ICU_IRQ3                      = (5), // External pin interrupt 3
    ICU_EVENT_ICU_IRQ4                      = (6), // External pin interrupt 4
    ICU_EVENT_ICU_IRQ5                      = (7), // External pin interrupt 5
    ICU_EVENT_DTC_COMPLETE                  = (10), // DTC transfer complete
    ICU_EVENT_FCU_FRDYI                     = (11), // Flash ready interrupt
    ICU_EVENT_SAU1_UART_TXI2                = (12), // SAU UART TX 2/I2C 20/SPI 20
    ICU_EVENT_SAU1_UART_RXI2                = (13), // SAU UART RX 2/I2C 21/SPI 21
    ICU_EVENT_SAU1_UART_ERRI2               = (14), // SAU UART Error
    ICU_EVENT_ELC_SOFTWARE_EVENT_0          = (15), // Software event 0
    ICU_EVENT_ELC_SOFTWARE_EVENT_1          = (16), // Software event 1
    ICU_EVENT_TRNG_RDREQ                    = (17), // TRNG Read Request
    ICU_EVENT_SAU0_UART_TXI0                = (18), // SAU UART TX 0/I2C 00/SPI 00
    ICU_EVENT_TAU0_TMI00                    = (19), // End of timer channel 00 count or capture
    ICU_EVENT_SAU0_UART_ERRI0               = (20), // SAU UART Error
    ICU_EVENT_TAU0_TMI01H                   = (21), // End of timer channel 01 count or capture (higher operation)
    ICU_EVENT_SAU0_UART_TXI1                = (22), // SAU UART TX 1/I2C 10/SPI 10
    ICU_EVENT_SAU0_UART_RXI1                = (23), // SAU UART RX 1/I2C 11/SPI 11
    ICU_EVENT_SAU0_UART_ERRI1               = (24), // SAU UART Error
    ICU_EVENT_TAU0_TMI03H                   = (25), // End of timer channel 03 count or capture (higher operation)
    ICU_EVENT_IICA0_TXRXI                   = (26), // Communication event
    ICU_EVENT_SAU0_UART_RXI0                = (27), // SAU UART RX 0/I2C 01/SPI 01
    ICU_EVENT_TAU0_TMI01                    = (28), // End of timer channel 01 count or capture
    ICU_EVENT_TAU0_TMI02                    = (29), // End of timer channel 02 count or capture
    ICU_EVENT_TAU0_TMI03                    = (30), // End of timer channel 03 count or capture
    ICU_EVENT_ADC0_SCAN_END                 = (31), // End of A/D scanning operation
    ICU_EVENT_RTC_ALARM_OR_PERIOD           = (32), // Alarm or Periodic interrupt
    ICU_EVENT_TML0_ITL_OR                   = (33), // TML timer event
    ICU_EVENT_TML0_ITL0                     = (34), // TML timer0 compare-match
    ICU_EVENT_TAU0_TMI04                    = (35), // End of timer channel 04 count or capture
    ICU_EVENT_TAU0_TMI05                    = (36), // End of timer channel 05 count or capture
    ICU_EVENT_TAU0_TMI06                    = (37), // End of timer channel 06 count or capture
    ICU_EVENT_TAU0_TMI07                    = (38), // End of timer channel 07 count or capture
    ICU_EVENT_UARTA0_ERRI                   = (39), // Reception error interrupt
    ICU_EVENT_UARTA0_TXI                    = (40), // Transfer completion interrupt
    ICU_EVENT_UARTA0_RXI                    = (41)  // Reception transfer end
} icu_event_t;

#define BSP_PRV_VECT_ENUM(event, group)  (ICU_ ## event)

#define ELC_PERIPHERAL_NUM    (29U)
#define BSP_OVERRIDE_ELC_PERIPHERAL_T
/** Possible peripherals to be linked to event signals
 * @note This list is device specific.
 * */
typedef enum e_elc_peripheral
{
    ELC_PERIPHERAL_AD            = (23),
    ELC_PERIPHERAL_TAU00         = (24),
    ELC_PERIPHERAL_TAU01         = (25),
    ELC_PERIPHERAL_IOPORT1       = (26),
    ELC_PERIPHERAL_IOPORT2       = (27),
    ELC_PERIPHERAL_ITLC          = (28)
} elc_peripheral_t;

/** Positions of event link set registers (ELSRs) available on this MCU */
#define BSP_ELC_PERIPHERAL_MASK  (0x1F800000U)

/* UNCRUSTIFY-ON */
/** @} (end addtogroup BSP_MCU_RA0E1) */

#endif
