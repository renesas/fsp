/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_ELC_H
#define BSP_ELC_H

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA4W1
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
typedef enum e_elc_event_ra4w1
{
    ELC_EVENT_NONE                          = (0x0),   // Link disabled
    ELC_EVENT_ICU_IRQ0                      = (0x001), // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1                      = (0x002), // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2                      = (0x003), // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3                      = (0x004), // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4                      = (0x005), // External pin interrupt 4
    ELC_EVENT_ICU_IRQ6                      = (0x007), // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7                      = (0x008), // External pin interrupt 7
    ELC_EVENT_ICU_IRQ8                      = (0x009), // External pin interrupt 8
    ELC_EVENT_ICU_IRQ9                      = (0x00A), // External pin interrupt 9
    ELC_EVENT_ICU_IRQ11                     = (0x00C), // External pin interrupt 11
    ELC_EVENT_ICU_IRQ14                     = (0x00F), // External pin interrupt 14
    ELC_EVENT_ICU_IRQ15                     = (0x010), // External pin interrupt 15
    ELC_EVENT_DMAC0_INT                     = (0x011), // DMAC0 transfer end
    ELC_EVENT_DMAC1_INT                     = (0x012), // DMAC1 transfer end
    ELC_EVENT_DMAC2_INT                     = (0x013), // DMAC2 transfer end
    ELC_EVENT_DMAC3_INT                     = (0x014), // DMAC3 transfer end
    ELC_EVENT_DTC_COMPLETE                  = (0x015), // DTC transfer complete
    ELC_EVENT_DTC_END                       = (0x016), // DTC transfer end
    ELC_EVENT_ICU_SNOOZE_CANCEL             = (0x017), // Canceling from Snooze mode
    ELC_EVENT_FCU_FRDYI                     = (0x018), // Flash ready interrupt
    ELC_EVENT_LVD_LVD1                      = (0x019), // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_VBATT                     = (0x01B), // VBATT low voltage detect
    ELC_EVENT_CGC_MOSC_STOP                 = (0x01C), // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST            = (0x01D), // Snooze entry
    ELC_EVENT_AGT0_INT                      = (0x01E), // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A                = (0x01F), // Compare match A
    ELC_EVENT_AGT0_COMPARE_B                = (0x020), // Compare match B
    ELC_EVENT_AGT1_INT                      = (0x021), // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A                = (0x022), // Compare match A
    ELC_EVENT_AGT1_COMPARE_B                = (0x023), // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW                = (0x024), // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW                 = (0x025), // WDT underflow
    ELC_EVENT_RTC_ALARM                     = (0x026), // Alarm interrupt
    ELC_EVENT_RTC_PERIOD                    = (0x027), // Periodic interrupt
    ELC_EVENT_RTC_CARRY                     = (0x028), // Carry interrupt
    ELC_EVENT_ADC0_SCAN_END                 = (0x029), // End of A/D scanning operation
    ELC_EVENT_ADC0_SCAN_END_B               = (0x02A), // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A                 = (0x02B), // Window A Compare match interrupt
    ELC_EVENT_ADC0_WINDOW_B                 = (0x02C), // Window B Compare match interrupt
    ELC_EVENT_ADC0_COMPARE_MATCH            = (0x02D), // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH         = (0x02E), // Compare mismatch
    ELC_EVENT_ACMPLP0_INT                   = (0x02F), // Low Power Comparator channel 0 interrupt
    ELC_EVENT_ACMPLP1_INT                   = (0x030), // Low Power Comparator channel 1 interrupt
    ELC_EVENT_USBFS_FIFO_0                  = (0x031), // DMA/DTC transfer request 0
    ELC_EVENT_USBFS_FIFO_1                  = (0x032), // DMA/DTC transfer request 1
    ELC_EVENT_USBFS_INT                     = (0x033), // USBFS interrupt
    ELC_EVENT_USBFS_RESUME                  = (0x034), // USBFS resume interrupt
    ELC_EVENT_IIC0_RXI                      = (0x035), // Receive data full
    ELC_EVENT_IIC0_TXI                      = (0x036), // Transmit data empty
    ELC_EVENT_IIC0_TEI                      = (0x037), // Transmit end
    ELC_EVENT_IIC0_ERI                      = (0x038), // Transfer error
    ELC_EVENT_IIC0_WUI                      = (0x039), // Wakeup interrupt
    ELC_EVENT_IIC1_RXI                      = (0x03A), // Receive data full
    ELC_EVENT_IIC1_TXI                      = (0x03B), // Transmit data empty
    ELC_EVENT_IIC1_TEI                      = (0x03C), // Transmit end
    ELC_EVENT_IIC1_ERI                      = (0x03D), // Transfer error
    ELC_EVENT_CTSU_WRITE                    = (0x046), // Write request interrupt
    ELC_EVENT_CTSU_READ                     = (0x047), // Measurement data transfer request interrupt
    ELC_EVENT_CTSU_END                      = (0x048), // Measurement end interrupt
    ELC_EVENT_KEY_INT                       = (0x049), // Key interrupt
    ELC_EVENT_DOC_INT                       = (0x04A), // Data operation circuit interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR           = (0x04B), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END           = (0x04C), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW                  = (0x04D), // Overflow interrupt
    ELC_EVENT_CAN0_ERROR                    = (0x04E), // Error interrupt
    ELC_EVENT_CAN0_FIFO_RX                  = (0x04F), // Receive FIFO interrupt
    ELC_EVENT_CAN0_FIFO_TX                  = (0x050), // Transmit FIFO interrupt
    ELC_EVENT_CAN0_MAILBOX_RX               = (0x051), // Reception complete interrupt
    ELC_EVENT_CAN0_MAILBOX_TX               = (0x052), // Transmission complete interrupt
    ELC_EVENT_IOPORT_EVENT_1                = (0x053), // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2                = (0x054), // Port 2 event
    ELC_EVENT_IOPORT_EVENT_3                = (0x055), // Port 3 event
    ELC_EVENT_IOPORT_EVENT_4                = (0x056), // Port 4 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0          = (0x057), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1          = (0x058), // Software event 1
    ELC_EVENT_POEG0_EVENT                   = (0x059), // Port Output disable 0 interrupt
    ELC_EVENT_POEG1_EVENT                   = (0x05A), // Port Output disable 1 interrupt
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A        = (0x05B), // Capture/Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B        = (0x05C), // Capture/Compare match B
    ELC_EVENT_GPT0_COMPARE_C                = (0x05D), // Compare match C
    ELC_EVENT_GPT0_COMPARE_D                = (0x05E), // Compare match D
    ELC_EVENT_GPT0_COMPARE_E                = (0x05F), // Compare match E
    ELC_EVENT_GPT0_COMPARE_F                = (0x060), // Compare match F
    ELC_EVENT_GPT0_COUNTER_OVERFLOW         = (0x061), // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW        = (0x062), // Underflow
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A        = (0x063), // Capture/Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B        = (0x064), // Capture/Compare match B
    ELC_EVENT_GPT1_COMPARE_C                = (0x065), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D                = (0x066), // Compare match D
    ELC_EVENT_GPT1_COMPARE_E                = (0x067), // Compare match E
    ELC_EVENT_GPT1_COMPARE_F                = (0x068), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW         = (0x069), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW        = (0x06A), // Underflow
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A        = (0x06B), // Capture/Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B        = (0x06C), // Capture/Compare match B
    ELC_EVENT_GPT2_COMPARE_C                = (0x06D), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D                = (0x06E), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E                = (0x06F), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F                = (0x070), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW         = (0x071), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW        = (0x072), // Underflow
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A        = (0x073), // Capture/Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B        = (0x074), // Capture/Compare match B
    ELC_EVENT_GPT3_COMPARE_C                = (0x075), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D                = (0x076), // Compare match D
    ELC_EVENT_GPT3_COMPARE_E                = (0x077), // Compare match E
    ELC_EVENT_GPT3_COMPARE_F                = (0x078), // Compare match F
    ELC_EVENT_GPT3_COUNTER_OVERFLOW         = (0x079), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW        = (0x07A), // Underflow
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A        = (0x07B), // Capture/Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B        = (0x07C), // Capture/Compare match B
    ELC_EVENT_GPT4_COMPARE_C                = (0x07D), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D                = (0x07E), // Compare match D
    ELC_EVENT_GPT4_COMPARE_E                = (0x07F), // Compare match E
    ELC_EVENT_GPT4_COMPARE_F                = (0x080), // Compare match F
    ELC_EVENT_GPT4_COUNTER_OVERFLOW         = (0x081), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW        = (0x082), // Underflow
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A        = (0x083), // Capture/Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B        = (0x084), // Capture/Compare match B
    ELC_EVENT_GPT5_COMPARE_C                = (0x085), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D                = (0x086), // Compare match D
    ELC_EVENT_GPT5_COMPARE_E                = (0x087), // Compare match E
    ELC_EVENT_GPT5_COMPARE_F                = (0x088), // Compare match F
    ELC_EVENT_GPT5_COUNTER_OVERFLOW         = (0x089), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW        = (0x08A), // Underflow
    ELC_EVENT_GPT8_CAPTURE_COMPARE_A        = (0x09B), // Capture/Compare match A
    ELC_EVENT_GPT8_CAPTURE_COMPARE_B        = (0x09C), // Capture/Compare match B
    ELC_EVENT_GPT8_COMPARE_C                = (0x09D), // Compare match C
    ELC_EVENT_GPT8_COMPARE_D                = (0x09E), // Compare match D
    ELC_EVENT_GPT8_COMPARE_E                = (0x09F), // Compare match E
    ELC_EVENT_GPT8_COMPARE_F                = (0x0A0), // Compare match F
    ELC_EVENT_GPT8_COUNTER_OVERFLOW         = (0x0A1), // Overflow
    ELC_EVENT_GPT8_COUNTER_UNDERFLOW        = (0x0A2), // Underflow
    ELC_EVENT_OPS_UVW_EDGE                  = (0x0AB), // UVW edge event
    ELC_EVENT_SCI0_RXI                      = (0x0AC), // Receive data full
    ELC_EVENT_SCI0_TXI                      = (0x0AD), // Transmit data empty
    ELC_EVENT_SCI0_TEI                      = (0x0AE), // Transmit end
    ELC_EVENT_SCI0_ERI                      = (0x0AF), // Receive error
    ELC_EVENT_SCI0_AM                       = (0x0B0), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI               = (0x0B1), // Receive data full/Receive error
    ELC_EVENT_SCI1_RXI                      = (0x0B2), // Receive data full
    ELC_EVENT_SCI1_TXI                      = (0x0B3), // Transmit data empty
    ELC_EVENT_SCI1_TEI                      = (0x0B4), // Transmit end
    ELC_EVENT_SCI1_ERI                      = (0x0B5), // Receive error
    ELC_EVENT_SCI1_AM                       = (0x0B6), // Address match event
    ELC_EVENT_SCI4_RXI                      = (0x0C1), // Receive data full
    ELC_EVENT_SCI4_TXI                      = (0x0C2), // Transmit data empty
    ELC_EVENT_SCI4_TEI                      = (0x0C3), // Transmit end
    ELC_EVENT_SCI4_ERI                      = (0x0C4), // Receive error
    ELC_EVENT_SCI4_AM                       = (0x0C5), // Address match event
    ELC_EVENT_SCI9_RXI                      = (0x0C6), // Receive data full
    ELC_EVENT_SCI9_TXI                      = (0x0C7), // Transmit data empty
    ELC_EVENT_SCI9_TEI                      = (0x0C8), // Transmit end
    ELC_EVENT_SCI9_ERI                      = (0x0C9), // Receive error
    ELC_EVENT_SCI9_AM                       = (0x0CA), // Address match event
    ELC_EVENT_SPI0_RXI                      = (0x0CB), // Receive buffer full
    ELC_EVENT_SPI0_TXI                      = (0x0CC), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE                     = (0x0CD), // Idle
    ELC_EVENT_SPI0_ERI                      = (0x0CE), // Error
    ELC_EVENT_SPI0_TEI                      = (0x0CF), // Transmission complete event
    ELC_EVENT_SPI1_RXI                      = (0x0D0), // Receive buffer full
    ELC_EVENT_SPI1_TXI                      = (0x0D1), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE                     = (0x0D2), // Idle
    ELC_EVENT_SPI1_ERI                      = (0x0D3), // Error
    ELC_EVENT_SPI1_TEI                      = (0x0D4)  // Transmission complete event
} elc_event_t;

#define BSP_PRV_VECT_ENUM(event,group)  (ELC_ ## event)

#define ELC_PERIPHERAL_NUM    (19U)
#define BSP_OVERRIDE_ELC_PERIPHERAL_T
/** Possible peripherals to be linked to event signals
 * @note This list is device specific.
 * */
typedef enum e_elc_peripheral
{
    ELC_PERIPHERAL_GPT_A         = (0),
    ELC_PERIPHERAL_GPT_B         = (1),
    ELC_PERIPHERAL_GPT_C         = (2),
    ELC_PERIPHERAL_GPT_D         = (3),
    ELC_PERIPHERAL_GPT_E         = (4),
    ELC_PERIPHERAL_GPT_F         = (5),
    ELC_PERIPHERAL_GPT_G         = (6),
    ELC_PERIPHERAL_GPT_H         = (7),
    ELC_PERIPHERAL_ADC0          = (8),
    ELC_PERIPHERAL_ADC0_B        = (9),
    ELC_PERIPHERAL_DAC0          = (12),
    ELC_PERIPHERAL_IOPORT1       = (14),
    ELC_PERIPHERAL_IOPORT2       = (15),
    ELC_PERIPHERAL_IOPORT3       = (16),
    ELC_PERIPHERAL_IOPORT4       = (17),
    ELC_PERIPHERAL_CTSU          = (18)
} elc_peripheral_t;

/** Positions of event link set registers (ELSRs) available on this MCU */
#define BSP_ELC_PERIPHERAL_MASK  (0x0007D3FFU)

/* UNCRUSTIFY-ON */
/** @} (end addtogroup BSP_MCU_RA4W1) */

#endif
