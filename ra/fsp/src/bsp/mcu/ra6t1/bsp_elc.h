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

#ifndef BSP_ELC_H
#define BSP_ELC_H

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

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA6T1
 * @{
 **********************************************************************************************************************/

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list may change based on based on the device.
 * */
typedef enum e_elc_event_ra6t1
{
    ELC_EVENT_NONE                    = (0),     // Link disabled
    ELC_EVENT_ICU_IRQ0                = (0x001), // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1                = (0x002), // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2                = (0x003), // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3                = (0x004), // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4                = (0x005), // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5                = (0x006), // External pin interrupt 5
    ELC_EVENT_ICU_IRQ6                = (0x007), // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7                = (0x008), // External pin interrupt 7
    ELC_EVENT_ICU_IRQ8                = (0x009), // External pin interrupt 8
    ELC_EVENT_ICU_IRQ9                = (0x00A), // External pin interrupt 9
    ELC_EVENT_ICU_IRQ10               = (0x00B), // External pin interrupt 10
    ELC_EVENT_ICU_IRQ11               = (0x00C), // External pin interrupt 11
    ELC_EVENT_ICU_IRQ12               = (0x00D), // External pin interrupt 12
    ELC_EVENT_ICU_IRQ13               = (0x00E), // External pin interrupt 13
    ELC_EVENT_DMAC0_INT               = (0x020), // DMAC transfer end 0
    ELC_EVENT_DMAC1_INT               = (0x021), // DMAC transfer end 1
    ELC_EVENT_DMAC2_INT               = (0x022), // DMAC transfer end 2
    ELC_EVENT_DMAC3_INT               = (0x023), // DMAC transfer end 3
    ELC_EVENT_DMAC4_INT               = (0x024), // DMAC transfer end 4
    ELC_EVENT_DMAC5_INT               = (0x025), // DMAC transfer end 5
    ELC_EVENT_DMAC6_INT               = (0x026), // DMAC transfer end 6
    ELC_EVENT_DMAC7_INT               = (0x027), // DMAC transfer end 7
    ELC_EVENT_DTC_COMPLETE            = (0x029), // DTC last transfer
    ELC_EVENT_DTC_END                 = (0x02A), // DTC transfer end
    ELC_EVENT_ICU_SNOOZE_CANCEL       = (0x02D), // Canceling from Snooze mode
    ELC_EVENT_FCU_FIFERR              = (0x030), // Flash access error interrupt
    ELC_EVENT_FCU_FRDYI               = (0x031), // Flash ready interrupt
    ELC_EVENT_LVD_LVD1                = (0x038), // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2                = (0x039), // Voltage monitor 2 interrupt
    ELC_EVENT_CGC_MOSC_STOP           = (0x03B), // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST      = (0x03C), // Snooze entry
    ELC_EVENT_AGT0_INT                = (0x040), // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A          = (0x041), // Compare match A
    ELC_EVENT_AGT0_COMPARE_B          = (0x042), // Compare match B
    ELC_EVENT_AGT1_INT                = (0x043), // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A          = (0x044), // Compare match A
    ELC_EVENT_AGT1_COMPARE_B          = (0x045), // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW          = (0x046), // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW           = (0x047), // WDT underflow
    ELC_EVENT_ADC0_SCAN_END           = (0x04B), // A/D scan end interrupt
    ELC_EVENT_ADC0_SCAN_END_B         = (0x04C), // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A           = (0x04D), // Window A Compare match
    ELC_EVENT_ADC0_WINDOW_B           = (0x04E), // Window B Compare match
    ELC_EVENT_ADC0_COMPARE_MATCH      = (0x04F), // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH   = (0x050), // Compare mismatch
    ELC_EVENT_ADC1_SCAN_END           = (0x051), // A/D scan end interrupt
    ELC_EVENT_ADC1_SCAN_END_B         = (0x052), // A/D scan end interrupt for group B
    ELC_EVENT_ADC1_WINDOW_A           = (0x053), // Window A Compare match
    ELC_EVENT_ADC1_WINDOW_B           = (0x054), // Window B Compare match
    ELC_EVENT_ADC1_COMPARE_MATCH      = (0x055), // Compare match
    ELC_EVENT_ADC1_COMPARE_MISMATCH   = (0x056), // Compare mismatch
    ELC_EVENT_ACMPHS0_INT             = (0x057), // Comparator interrupt 0
    ELC_EVENT_ACMPHS1_INT             = (0x058), // Comparator interrupt 1
    ELC_EVENT_ACMPHS2_INT             = (0x059), // Comparator interrupt 2
    ELC_EVENT_ACMPHS3_INT             = (0x05A), // Comparator interrupt 3
    ELC_EVENT_ACMPHS4_INT             = (0x05B), // Comparator interrupt 4
    ELC_EVENT_ACMPHS5_INT             = (0x05C), // Comparator interrupt 5
    ELC_EVENT_IIC0_RXI                = (0x063), // Receive data full
    ELC_EVENT_IIC0_TXI                = (0x064), // Transmit data empty
    ELC_EVENT_IIC0_TEI                = (0x065), // Transmit end
    ELC_EVENT_IIC0_ERI                = (0x066), // Transfer error
    ELC_EVENT_IIC0_WUI                = (0x067), // Slave address match
    ELC_EVENT_IIC1_RXI                = (0x068), // Receive data full
    ELC_EVENT_IIC1_TXI                = (0x069), // Transmit data empty
    ELC_EVENT_IIC1_TEI                = (0x06A), // Transmit end
    ELC_EVENT_IIC1_ERI                = (0x06B), // Transfer error
    ELC_EVENT_KEY_INT                 = (0x085), // Key interrupt
    ELC_EVENT_DOC_INT                 = (0x086), // Data operation circuit interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR     = (0x087), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END     = (0x088), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW            = (0x089), // Overflow interrupt
    ELC_EVENT_CAN0_ERROR              = (0x08A), // Error interrupt
    ELC_EVENT_CAN0_FIFO_RX            = (0x08B), // Receive FIFO interrupt
    ELC_EVENT_CAN0_FIFO_TX            = (0x08C), // Transmit FIFO interrupt
    ELC_EVENT_CAN0_MAILBOX_RX         = (0x08D), // Reception complete interrupt
    ELC_EVENT_CAN0_MAILBOX_TX         = (0x08E), // Transmission complete interrupt
    ELC_EVENT_IOPORT_EVENT_1          = (0x094), // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2          = (0x095), // Port 2 event
    ELC_EVENT_IOPORT_EVENT_3          = (0x096), // Port 3 event
    ELC_EVENT_IOPORT_EVENT_4          = (0x097), // Port 4 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0    = (0x098), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1    = (0x099), // Software event 1
    ELC_EVENT_POEG0_EVENT             = (0x09A), // Port Output disable interrupt A
    ELC_EVENT_POEG1_EVENT             = (0x09B), // Port Output disable interrupt B
    ELC_EVENT_POEG2_EVENT             = (0x09C), // Port Output disable interrupt C
    ELC_EVENT_POEG3_EVENT             = (0x09D), // Port Output disable interrupt D
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A  = (0x0B0), // Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B  = (0x0B1), // Compare match B
    ELC_EVENT_GPT0_COMPARE_C          = (0x0B2), // Compare match C
    ELC_EVENT_GPT0_COMPARE_D          = (0x0B3), // Compare match D
    ELC_EVENT_GPT0_COMPARE_E          = (0x0B4), // Compare match E
    ELC_EVENT_GPT0_COMPARE_F          = (0x0B5), // Compare match F
    ELC_EVENT_GPT0_COUNTER_OVERFLOW   = (0x0B6), // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW  = (0x0B7), // Underflow
    ELC_EVENT_GPT0_AD_TRIG_A          = (0x0B8), // A/D converter start request A
    ELC_EVENT_GPT0_AD_TRIG_B          = (0x0B9), // A/D converter start request B
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A  = (0x0BA), // Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B  = (0x0BB), // Compare match B
    ELC_EVENT_GPT1_COMPARE_C          = (0x0BC), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D          = (0x0BD), // Compare match D
    ELC_EVENT_GPT1_COMPARE_E          = (0x0BE), // Compare match E
    ELC_EVENT_GPT1_COMPARE_F          = (0x0BF), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW   = (0x0C0), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW  = (0x0C1), // Underflow
    ELC_EVENT_GPT1_AD_TRIG_A          = (0x0C2), // A/D converter start request A
    ELC_EVENT_GPT1_AD_TRIG_B          = (0x0C3), // A/D converter start request B
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A  = (0x0C4), // Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B  = (0x0C5), // Compare match B
    ELC_EVENT_GPT2_COMPARE_C          = (0x0C6), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D          = (0x0C7), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E          = (0x0C8), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F          = (0x0C9), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW   = (0x0CA), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW  = (0x0CB), // Underflow
    ELC_EVENT_GPT2_AD_TRIG_A          = (0x0CC), // A/D converter start request A
    ELC_EVENT_GPT2_AD_TRIG_B          = (0x0CD), // A/D converter start request B
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A  = (0x0CE), // Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B  = (0x0CF), // Compare match B
    ELC_EVENT_GPT3_COMPARE_C          = (0x0D0), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D          = (0x0D1), // Compare match D
    ELC_EVENT_GPT3_COMPARE_E          = (0x0D2), // Compare match E
    ELC_EVENT_GPT3_COMPARE_F          = (0x0D3), // Compare match F
    ELC_EVENT_GPT3_COUNTER_OVERFLOW   = (0x0D4), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW  = (0x0D5), // Underflow
    ELC_EVENT_GPT3_AD_TRIG_A          = (0x0D6), // A/D converter start request A
    ELC_EVENT_GPT3_AD_TRIG_B          = (0x0D7), // A/D converter start request B
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A  = (0x0D8), // Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B  = (0x0D9), // Compare match B
    ELC_EVENT_GPT4_COMPARE_C          = (0x0DA), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D          = (0x0DB), // Compare match D
    ELC_EVENT_GPT4_COMPARE_E          = (0x0DC), // Compare match E
    ELC_EVENT_GPT4_COMPARE_F          = (0x0DD), // Compare match F
    ELC_EVENT_GPT4_COUNTER_OVERFLOW   = (0x0DE), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW  = (0x0DF), // Underflow
    ELC_EVENT_GPT4_AD_TRIG_A          = (0x0E0), // A/D converter start request A
    ELC_EVENT_GPT4_AD_TRIG_B          = (0x0E1), // A/D converter start request B
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A  = (0x0E2), // Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B  = (0x0E3), // Compare match B
    ELC_EVENT_GPT5_COMPARE_C          = (0x0E4), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D          = (0x0E5), // Compare match D
    ELC_EVENT_GPT5_COMPARE_E          = (0x0E6), // Compare match E
    ELC_EVENT_GPT5_COMPARE_F          = (0x0E7), // Compare match F
    ELC_EVENT_GPT5_COUNTER_OVERFLOW   = (0x0E8), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW  = (0x0E9), // Underflow
    ELC_EVENT_GPT5_AD_TRIG_A          = (0x0EA), // A/D converter start request A
    ELC_EVENT_GPT5_AD_TRIG_B          = (0x0EB), // A/D converter start request B
    ELC_EVENT_GPT6_CAPTURE_COMPARE_A  = (0x0EC), // Compare match A
    ELC_EVENT_GPT6_CAPTURE_COMPARE_B  = (0x0ED), // Compare match B
    ELC_EVENT_GPT6_COMPARE_C          = (0x0EE), // Compare match C
    ELC_EVENT_GPT6_COMPARE_D          = (0x0EF), // Compare match D
    ELC_EVENT_GPT6_COMPARE_E          = (0x0F0), // Compare match E
    ELC_EVENT_GPT6_COMPARE_F          = (0x0F1), // Compare match F
    ELC_EVENT_GPT6_COUNTER_OVERFLOW   = (0x0F2), // Overflow
    ELC_EVENT_GPT6_COUNTER_UNDERFLOW  = (0x0F3), // Underflow
    ELC_EVENT_GPT6_AD_TRIG_A          = (0x0F4), // A/D converter start request A
    ELC_EVENT_GPT6_AD_TRIG_B          = (0x0F5), // A/D converter start request B
    ELC_EVENT_GPT7_CAPTURE_COMPARE_A  = (0x0F6), // Compare match A
    ELC_EVENT_GPT7_CAPTURE_COMPARE_B  = (0x0F7), // Compare match B
    ELC_EVENT_GPT7_COMPARE_C          = (0x0F8), // Compare match C
    ELC_EVENT_GPT7_COMPARE_D          = (0x0F9), // Compare match D
    ELC_EVENT_GPT7_COMPARE_E          = (0x0FA), // Compare match E
    ELC_EVENT_GPT7_COMPARE_F          = (0x0FB), // Compare match F
    ELC_EVENT_GPT7_COUNTER_OVERFLOW   = (0x0FC), // Overflow
    ELC_EVENT_GPT7_COUNTER_UNDERFLOW  = (0x0FD), // Underflow
    ELC_EVENT_GPT7_AD_TRIG_A          = (0x0FE), // A/D converter start request A
    ELC_EVENT_GPT7_AD_TRIG_B          = (0x0FF), // A/D converter start request B
    ELC_EVENT_GPT8_CAPTURE_COMPARE_A  = (0x100), // Compare match A
    ELC_EVENT_GPT8_CAPTURE_COMPARE_B  = (0x101), // Compare match B
    ELC_EVENT_GPT8_COMPARE_C          = (0x102), // Compare match C
    ELC_EVENT_GPT8_COMPARE_D          = (0x103), // Compare match D
    ELC_EVENT_GPT8_COMPARE_E          = (0x104), // Compare match E
    ELC_EVENT_GPT8_COMPARE_F          = (0x105), // Compare match F
    ELC_EVENT_GPT8_COUNTER_OVERFLOW   = (0x106), // Overflow
    ELC_EVENT_GPT8_COUNTER_UNDERFLOW  = (0x107), // Underflow
    ELC_EVENT_GPT9_CAPTURE_COMPARE_A  = (0x10A), // Compare match A
    ELC_EVENT_GPT9_CAPTURE_COMPARE_B  = (0x10B), // Compare match B
    ELC_EVENT_GPT9_COMPARE_C          = (0x10C), // Compare match C
    ELC_EVENT_GPT9_COMPARE_D          = (0x10D), // Compare match D
    ELC_EVENT_GPT9_COMPARE_E          = (0x10E), // Compare match E
    ELC_EVENT_GPT9_COMPARE_F          = (0x10F), // Compare match F
    ELC_EVENT_GPT9_COUNTER_OVERFLOW   = (0x110), // Overflow
    ELC_EVENT_GPT9_COUNTER_UNDERFLOW  = (0x111), // Underflow
    ELC_EVENT_GPT10_CAPTURE_COMPARE_A = (0x114), // Compare match A
    ELC_EVENT_GPT10_CAPTURE_COMPARE_B = (0x115), // Compare match B
    ELC_EVENT_GPT10_COMPARE_C         = (0x116), // Compare match C
    ELC_EVENT_GPT10_COMPARE_D         = (0x117), // Compare match D
    ELC_EVENT_GPT10_COMPARE_E         = (0x118), // Compare match E
    ELC_EVENT_GPT10_COMPARE_F         = (0x119), // Compare match F
    ELC_EVENT_GPT10_COUNTER_OVERFLOW  = (0x11A), // Overflow
    ELC_EVENT_GPT10_COUNTER_UNDERFLOW = (0x11B), // Underflow
    ELC_EVENT_GPT11_CAPTURE_COMPARE_A = (0x11E), // Compare match A
    ELC_EVENT_GPT11_CAPTURE_COMPARE_B = (0x11F), // Compare match B
    ELC_EVENT_GPT11_COMPARE_C         = (0x120), // Compare match C
    ELC_EVENT_GPT11_COMPARE_D         = (0x121), // Compare match D
    ELC_EVENT_GPT11_COMPARE_E         = (0x122), // Compare match E
    ELC_EVENT_GPT11_COMPARE_F         = (0x123), // Compare match F
    ELC_EVENT_GPT11_COUNTER_OVERFLOW  = (0x124), // Overflow
    ELC_EVENT_GPT11_COUNTER_UNDERFLOW = (0x125), // Underflow
    ELC_EVENT_GPT12_CAPTURE_COMPARE_A = (0x128), // Compare match A
    ELC_EVENT_GPT12_CAPTURE_COMPARE_B = (0x129), // Compare match B
    ELC_EVENT_GPT12_COMPARE_C         = (0x12A), // Compare match C
    ELC_EVENT_GPT12_COMPARE_D         = (0x12B), // Compare match D
    ELC_EVENT_GPT12_COMPARE_E         = (0x12C), // Compare match E
    ELC_EVENT_GPT12_COMPARE_F         = (0x12D), // Compare match F
    ELC_EVENT_GPT12_COUNTER_OVERFLOW  = (0x12E), // Overflow
    ELC_EVENT_GPT12_COUNTER_UNDERFLOW = (0x12F), // Underflow
    ELC_EVENT_OPS_UVW_EDGE            = (0x150), // UVW edge event
    ELC_EVENT_SCI0_RXI                = (0x174), // Receive data full
    ELC_EVENT_SCI0_TXI                = (0x175), // Transmit data empty
    ELC_EVENT_SCI0_TEI                = (0x176), // Transmit end
    ELC_EVENT_SCI0_ERI                = (0x177), // Receive error
    ELC_EVENT_SCI0_AM                 = (0x178), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI         = (0x179), // Receive data full/Receive
    ELC_EVENT_SCI1_RXI                = (0x17A), // Received data full
    ELC_EVENT_SCI1_TXI                = (0x17B), // Transmit data empty
    ELC_EVENT_SCI1_TEI                = (0x17C), // Transmit end
    ELC_EVENT_SCI1_ERI                = (0x17D), // Receive error
    ELC_EVENT_SCI1_AM                 = (0x17E), // Address match event
    ELC_EVENT_SCI2_RXI                = (0x180), // Received data full
    ELC_EVENT_SCI2_TXI                = (0x181), // Transmit data empty
    ELC_EVENT_SCI2_TEI                = (0x182), // Transmit end
    ELC_EVENT_SCI2_ERI                = (0x183), // Receive error
    ELC_EVENT_SCI2_AM                 = (0x184), // Address match event
    ELC_EVENT_SCI3_RXI                = (0x186), // Received data full
    ELC_EVENT_SCI3_TXI                = (0x187), // Transmit data empty
    ELC_EVENT_SCI3_TEI                = (0x188), // Transmit end
    ELC_EVENT_SCI3_ERI                = (0x189), // Receive error
    ELC_EVENT_SCI3_AM                 = (0x18A), // Address match event
    ELC_EVENT_SCI4_RXI                = (0x18C), // Received data full
    ELC_EVENT_SCI4_TXI                = (0x18D), // Transmit data empty
    ELC_EVENT_SCI4_TEI                = (0x18E), // Transmit end
    ELC_EVENT_SCI4_ERI                = (0x18F), // Receive error
    ELC_EVENT_SCI4_AM                 = (0x190), // Address match event
    ELC_EVENT_SCI8_RXI                = (0x1A4), // Received data full
    ELC_EVENT_SCI8_TXI                = (0x1A5), // Transmit data empty
    ELC_EVENT_SCI8_TEI                = (0x1A6), // Transmit end
    ELC_EVENT_SCI8_ERI                = (0x1A7), // Receive error
    ELC_EVENT_SCI8_AM                 = (0x1A8), // Address match event
    ELC_EVENT_SCI9_RXI                = (0x1AA), // Received data full
    ELC_EVENT_SCI9_TXI                = (0x1AB), // Transmit data empty
    ELC_EVENT_SCI9_TEI                = (0x1AC), // Transmit end
    ELC_EVENT_SCI9_ERI                = (0x1AD), // Receive error
    ELC_EVENT_SCI9_AM                 = (0x1AE), // Address match event
    ELC_EVENT_SPI0_RXI                = (0x1BC), // Receive buffer full
    ELC_EVENT_SPI0_TXI                = (0x1BD), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE               = (0x1BE), // Idle
    ELC_EVENT_SPI0_ERI                = (0x1BF), // Error
    ELC_EVENT_SPI0_TEI                = (0x1C0), // Transmission complete event
    ELC_EVENT_SPI1_RXI                = (0x1C1), // Receive buffer full
    ELC_EVENT_SPI1_TXI                = (0x1C2), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE               = (0x1C3), // Idle
    ELC_EVENT_SPI1_ERI                = (0x1C4), // Error
    ELC_EVENT_SPI1_TEI                = (0x1C5), // Transmission complete event
    ELC_EVENT_SCE_PROC_BUSY           = (0x1E1),
    ELC_EVENT_SCE_ROMOK               = (0x1E2),
    ELC_EVENT_SCE_LONG_PLG            = (0x1E3),
    ELC_EVENT_SCE_TEST_BUSY           = (0x1E4),
    ELC_EVENT_SCE_WRRDY_0             = (0x1E5),
    ELC_EVENT_SCE_WRRDY_1             = (0x1E6),
    ELC_EVENT_SCE_WRRDY_4             = (0x1E7),
    ELC_EVENT_SCE_RDRDY_0             = (0x1E8),
    ELC_EVENT_SCE_RDRDY_1             = (0x1E9),
    ELC_EVENT_SCE_INTEGRATE_WRRDY     = (0x1EA),
    ELC_EVENT_SCE_INTEGRATE_RDRDY     = (0x1EB),
} elc_event_t;

/** @} (end addtogroup BSP_MCU_RA6T1) */

#endif
