/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @addtogroup BSP_MCU_RA6T2
 * @{
 **********************************************************************************************************************/

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list may change based on based on the device.
 * */
typedef enum e_elc_event_ra6t2
{
    ELC_EVENT_NONE                   = (0),     // Link disabled
    ELC_EVENT_ICU_IRQ0               = (0x001), // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1               = (0x002), // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2               = (0x003), // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3               = (0x004), // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4               = (0x005), // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5               = (0x006), // External pin interrupt 5
    ELC_EVENT_ICU_IRQ6               = (0x007), // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7               = (0x008), // External pin interrupt 7
    ELC_EVENT_ICU_IRQ8               = (0x009), // External pin interrupt 8
    ELC_EVENT_ICU_IRQ9               = (0x00A), // External pin interrupt 9
    ELC_EVENT_ICU_IRQ10              = (0x00B), // External pin interrupt 10
    ELC_EVENT_ICU_IRQ11              = (0x00C), // External pin interrupt 11
    ELC_EVENT_ICU_IRQ12              = (0x00D), // External pin interrupt 12
    ELC_EVENT_ICU_IRQ13              = (0x00E), // External pin interrupt 13
    ELC_EVENT_ICU_IRQ14              = (0x00F), // External pin interrupt 14
    ELC_EVENT_ICU_IRQ15              = (0x010), // External pin interrupt 15
    ELC_EVENT_IIRFA_ORDY0            = (0x011), // IIRFA output data ready 0
    ELC_EVENT_IIRFA_ORDY1            = (0x012), // IIRFA output data ready 1
    ELC_EVENT_IIRFA_ORDY2            = (0x013), // IIRFA output data ready 2
    ELC_EVENT_IIRFA_ORDY3            = (0x014), // IIRFA output data ready 3 to 15
    ELC_EVENT_IIRFA_CPRCF0           = (0x015), // IIRFA channel processing complete 0
    ELC_EVENT_IIRFA_CPRCF1           = (0x016), // IIRFA channel processing complete 1
    ELC_EVENT_IIRFA_CPRCF2           = (0x017), // IIRFA channel processing complete 2
    ELC_EVENT_IIRFA_CPRCF3           = (0x018), // IIRFA channel processing complete 3 to 15
    ELC_EVENT_IIRFA_ERR              = (0x019), // IIRFA operation error
    ELC_EVENT_DMAC0_INT              = (0x020), // DMAC transfer end 0
    ELC_EVENT_DMAC1_INT              = (0x021), // DMAC transfer end 1
    ELC_EVENT_DMAC2_INT              = (0x022), // DMAC transfer end 2
    ELC_EVENT_DMAC3_INT              = (0x023), // DMAC transfer end 3
    ELC_EVENT_DMAC4_INT              = (0x024), // DMAC transfer end 4
    ELC_EVENT_DMAC5_INT              = (0x025), // DMAC transfer end 5
    ELC_EVENT_DMAC6_INT              = (0x026), // DMAC transfer end 6
    ELC_EVENT_DMAC7_INT              = (0x027), // DMAC transfer end 7
    ELC_EVENT_DTC_COMPLETE           = (0x029), // DTC transfer complete
    ELC_EVENT_DTC_END                = (0x02A), // DTC transfer end
    ELC_EVENT_DMA_TRANSERR           = (0x02B), // DTC transfer error
    ELC_EVENT_ICU_SNOOZE_CANCEL      = (0x02D), // Canceling from Snooze mode
    ELC_EVENT_FCU_FIFERR             = (0x030), // Flash access error interrupt
    ELC_EVENT_FCU_FRDYI              = (0x031), // Flash ready interrupt
    ELC_EVENT_LVD_LVD1               = (0x038), // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2               = (0x039), // Voltage monitor 2 interrupt
    ELC_EVENT_CGC_MOSC_STOP          = (0x03B), // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST     = (0x03C), // Snooze entry
    ELC_EVENT_AGT0_INT               = (0x040), // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A         = (0x041), // Compare match A
    ELC_EVENT_AGT0_COMPARE_B         = (0x042), // Compare match B
    ELC_EVENT_AGT1_INT               = (0x043), // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A         = (0x044), // Compare match A
    ELC_EVENT_AGT1_COMPARE_B         = (0x045), // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW         = (0x052), // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW          = (0x053), // WDT underflow
    ELC_EVENT_CAN_RXF                = (0x059), // Global recieve FIFO interrupt
    ELC_EVENT_CAN_GLERR              = (0x05A), // Global error
    ELC_EVENT_CAN_DMAREQ0            = (0x05B), // DMA 0 request
    ELC_EVENT_CAN_DMAREQ1            = (0x05C), // DMA 1 request
    ELC_EVENT_CAN0_TX                = (0x063), // Transmit interrupt
    ELC_EVENT_CAN0_CHERR             = (0x064), // Channel error
    ELC_EVENT_CAN0_COMFRX            = (0x065), // Common FIFO recieve interrupt
    ELC_EVENT_CAN0_CF_DMAREQ         = (0x066), // Channel DMA request
    ELC_EVENT_CAN0_RXMB              = (0x067), // Receive message buffer interrupt
    ELC_EVENT_ACMPHS0_INT            = (0x08F), // Comparator interrupt 0
    ELC_EVENT_ACMPHS1_INT            = (0x090), // Comparator interrupt 1
    ELC_EVENT_ACMPHS2_INT            = (0x091), // Comparator interrupt 2
    ELC_EVENT_ACMPHS3_INT            = (0x092), // Comparator interrupt 3
    ELC_EVENT_KEY_INT                = (0x09D), // Key interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR    = (0x09E), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END    = (0x09F), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW           = (0x0A0), // Overflow interrupt
    ELC_EVENT_IOPORT_EVENT_B         = (0x0B1), // Port B event
    ELC_EVENT_IOPORT_EVENT_C         = (0x0B2), // Port C event
    ELC_EVENT_IOPORT_EVENT_D         = (0x0B3), // Port D event
    ELC_EVENT_IOPORT_EVENT_E         = (0x0B4), // Port E event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0   = (0x0B5), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1   = (0x0B6), // Software event 1
    ELC_EVENT_POEG0_EVENT            = (0x0B7), // Port Output disable interrupt A
    ELC_EVENT_POEG1_EVENT            = (0x0B8), // Port Output disable interrupt B
    ELC_EVENT_POEG2_EVENT            = (0x0B9), // Port Output disable interrupt C
    ELC_EVENT_POEG3_EVENT            = (0x0BA), // Port Output disable interrupt D
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A = (0x0C0), // Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B = (0x0C1), // Compare match B
    ELC_EVENT_GPT0_COMPARE_C         = (0x0C2), // Compare match C
    ELC_EVENT_GPT0_COMPARE_D         = (0x0C3), // Compare match D
    ELC_EVENT_GPT0_COMPARE_E         = (0x0C4), // Compare match E
    ELC_EVENT_GPT0_COMPARE_F         = (0x0C5), // Compare match F
    ELC_EVENT_GPT0_COUNTER_OVERFLOW  = (0x0C6), // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW = (0x0C7), // Underflow
    ELC_EVENT_GPT0_PC                = (0x0C8), // Period count function finish
    ELC_EVENT_GPT0_AD_TRIG_A         = (0x0CA), // A/D converter start request A
    ELC_EVENT_GPT0_AD_TRIG_B         = (0x0CB), // A/D converter start request B
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A = (0x0CC), // Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B = (0x0CD), // Compare match B
    ELC_EVENT_GPT1_COMPARE_C         = (0x0CE), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D         = (0x0CF), // Compare match D
    ELC_EVENT_GPT1_COMPARE_E         = (0x0D0), // Compare match E
    ELC_EVENT_GPT1_COMPARE_F         = (0x0D1), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW  = (0x0D2), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW = (0x0D3), // Underflow
    ELC_EVENT_GPT1_PC                = (0x0D4), // Period count function finish
    ELC_EVENT_GPT1_AD_TRIG_A         = (0x0D6), // A/D converter start request A
    ELC_EVENT_GPT1_AD_TRIG_B         = (0x0D7), // A/D converter start request B
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A = (0x0D8), // Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B = (0x0D9), // Compare match B
    ELC_EVENT_GPT2_COMPARE_C         = (0x0DA), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D         = (0x0DB), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E         = (0x0DC), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F         = (0x0DD), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW  = (0x0DE), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW = (0x0DF), // Underflow
    ELC_EVENT_GPT2_PC                = (0x0E0), // Period count function finish
    ELC_EVENT_GPT2_AD_TRIG_A         = (0x0E2), // A/D converter start request A
    ELC_EVENT_GPT2_AD_TRIG_B         = (0x0E3), // A/D converter start request B
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A = (0x0E4), // Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B = (0x0E5), // Compare match B
    ELC_EVENT_GPT3_COMPARE_C         = (0x0E6), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D         = (0x0E7), // Compare match D
    ELC_EVENT_GPT3_COMPARE_E         = (0x0E8), // Compare match E
    ELC_EVENT_GPT3_COMPARE_F         = (0x0E9), // Compare match F
    ELC_EVENT_GPT3_COUNTER_OVERFLOW  = (0x0EA), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW = (0x0EB), // Underflow
    ELC_EVENT_GPT3_PC                = (0x0EC), // Period count function finish
    ELC_EVENT_GPT3_AD_TRIG_A         = (0x0EE), // A/D converter start request A
    ELC_EVENT_GPT3_AD_TRIG_B         = (0x0EF), // A/D converter start request B
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A = (0x0F0), // Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B = (0x0F1), // Compare match B
    ELC_EVENT_GPT4_COMPARE_C         = (0x0F2), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D         = (0x0F3), // Compare match D
    ELC_EVENT_GPT4_COMPARE_E         = (0x0F4), // Compare match E
    ELC_EVENT_GPT4_COMPARE_F         = (0x0F5), // Compare match F
    ELC_EVENT_GPT4_COUNTER_OVERFLOW  = (0x0F6), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW = (0x0F7), // Underflow
    ELC_EVENT_GPT4_AD_TRIG_A         = (0x0FA), // A/D converter start request A
    ELC_EVENT_GPT4_AD_TRIG_B         = (0x0FB), // A/D converter start request B
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A = (0x0FC), // Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B = (0x0FD), // Compare match B
    ELC_EVENT_GPT5_COMPARE_C         = (0x0FE), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D         = (0x0FF), // Compare match D
    ELC_EVENT_GPT5_COMPARE_E         = (0x100), // Compare match E
    ELC_EVENT_GPT5_COMPARE_F         = (0x101), // Compare match F
    ELC_EVENT_GPT5_COUNTER_OVERFLOW  = (0x102), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW = (0x103), // Underflow
    ELC_EVENT_GPT5_AD_TRIG_A         = (0x106), // A/D converter start request A
    ELC_EVENT_GPT5_AD_TRIG_B         = (0x107), // A/D converter start request B
    ELC_EVENT_GPT6_CAPTURE_COMPARE_A = (0x108), // Compare match A
    ELC_EVENT_GPT6_CAPTURE_COMPARE_B = (0x109), // Compare match B
    ELC_EVENT_GPT6_COMPARE_C         = (0x10A), // Compare match C
    ELC_EVENT_GPT6_COMPARE_D         = (0x10B), // Compare match D
    ELC_EVENT_GPT6_COMPARE_E         = (0x10C), // Compare match E
    ELC_EVENT_GPT6_COMPARE_F         = (0x10D), // Compare match F
    ELC_EVENT_GPT6_COUNTER_OVERFLOW  = (0x10E), // Overflow
    ELC_EVENT_GPT6_COUNTER_UNDERFLOW = (0x10F), // Underflow
    ELC_EVENT_GPT6_AD_TRIG_A         = (0x112), // A/D converter start request A
    ELC_EVENT_GPT6_AD_TRIG_B         = (0x113), // A/D converter start request B
    ELC_EVENT_GPT7_CAPTURE_COMPARE_A = (0x114), // Compare match A
    ELC_EVENT_GPT7_CAPTURE_COMPARE_B = (0x115), // Compare match B
    ELC_EVENT_GPT7_COMPARE_C         = (0x116), // Compare match C
    ELC_EVENT_GPT7_COMPARE_D         = (0x117), // Compare match D
    ELC_EVENT_GPT7_COMPARE_E         = (0x118), // Compare match E
    ELC_EVENT_GPT7_COMPARE_F         = (0x119), // Compare match F
    ELC_EVENT_GPT7_COUNTER_OVERFLOW  = (0x11A), // Overflow
    ELC_EVENT_GPT7_COUNTER_UNDERFLOW = (0x11B), // Underflow
    ELC_EVENT_GPT7_AD_TRIG_A         = (0x11E), // A/D converter start request A
    ELC_EVENT_GPT7_AD_TRIG_B         = (0x11F), // A/D converter start request B
    ELC_EVENT_GPT8_CAPTURE_COMPARE_A = (0x120), // Compare match A
    ELC_EVENT_GPT8_CAPTURE_COMPARE_B = (0x121), // Compare match B
    ELC_EVENT_GPT8_COMPARE_C         = (0x122), // Compare match C
    ELC_EVENT_GPT8_COMPARE_D         = (0x123), // Compare match D
    ELC_EVENT_GPT8_COMPARE_E         = (0x124), // Compare match E
    ELC_EVENT_GPT8_COMPARE_F         = (0x125), // Compare match F
    ELC_EVENT_GPT8_COUNTER_OVERFLOW  = (0x126), // Overflow
    ELC_EVENT_GPT8_COUNTER_UNDERFLOW = (0x127), // Underflow
    ELC_EVENT_GPT8_AD_TRIG_A         = (0x12A), // A/D converter start request A
    ELC_EVENT_GPT8_AD_TRIG_B         = (0x12B), // A/D converter start request B
    ELC_EVENT_GPT9_CAPTURE_COMPARE_A = (0x12C), // Compare match A
    ELC_EVENT_GPT9_CAPTURE_COMPARE_B = (0x12D), // Compare match B
    ELC_EVENT_GPT9_COMPARE_C         = (0x12E), // Compare match C
    ELC_EVENT_GPT9_COMPARE_D         = (0x12F), // Compare match D
    ELC_EVENT_GPT9_COMPARE_E         = (0x130), // Compare match E
    ELC_EVENT_GPT9_COMPARE_F         = (0x131), // Compare match F
    ELC_EVENT_GPT9_COUNTER_OVERFLOW  = (0x132), // Overflow
    ELC_EVENT_GPT9_COUNTER_UNDERFLOW = (0x133), // Underflow
    ELC_EVENT_GPT9_AD_TRIG_A         = (0x136), // A/D converter start request A
    ELC_EVENT_GPT9_AD_TRIG_B         = (0x137), // A/D converter start request B
    ELC_EVENT_OPS_UVW_EDGE           = (0x138), // UVW edge event
    ELC_EVENT_IIC0_RXI               = (0x140), // Receive data full
    ELC_EVENT_IIC0_TXI               = (0x141), // Transmit data empty
    ELC_EVENT_IIC0_TEI               = (0x142), // Transmit end
    ELC_EVENT_IIC0_ERI               = (0x143), // Transfer error
    ELC_EVENT_IIC0_WUI               = (0x144), // Slave address match
    ELC_EVENT_IIC1_RXI               = (0x146), // Receive data full
    ELC_EVENT_IIC1_TXI               = (0x147), // Transmit data empty
    ELC_EVENT_IIC1_TEI               = (0x148), // Transmit end
    ELC_EVENT_IIC1_ERI               = (0x149), // Transfer error
    ELC_EVENT_ADC12_LIMCLPI          = (0x157), // Limiter clip interrupt with the limit table 0 to 7
    ELC_EVENT_ADC12_FIFOOVF          = (0x158), // FIFO data overflow
    ELC_EVENT_ADC12_ADI0             = (0x159), // End of A/D scanning operation(Gr.0)
    ELC_EVENT_ADC12_ADI1             = (0x15A), // End of A/D scanning operation(Gr.1)
    ELC_EVENT_ADC12_ADI2             = (0x15B), // End of A/D scanning operation(Gr.2)
    ELC_EVENT_ADC12_CMPI0            = (0x15C), // Compare match interrupt with compare table 0
    ELC_EVENT_ADC12_CMPI1            = (0x15D), // Compare match interrupt with compare table 1
    ELC_EVENT_ADC0_COMPARE_MATCH     = (0x15E), // Composite compare match interrupt 0
    ELC_EVENT_ADC12_ERR0             = (0x160), // A/D converter unit 0 Error
    ELC_EVENT_ADC12_RESOVF0          = (0x161), // A/D conversion overflow on A/D converter unit 0
    ELC_EVENT_ADC12_CALEND0          = (0x163), // End of calibration of A/D converter unit 0
    ELC_EVENT_ADC12_FIFOREQ0         = (0x164), // FIFO data read request interrupt(Gr.0)
    ELC_EVENT_ADC12_FIFOREQ1         = (0x165), // FIFO data read request interrupt(Gr.1)
    ELC_EVENT_ADC12_FIFOREQ2         = (0x166), // FIFO data read request interrupt(Gr.2)
    ELC_EVENT_ADC12_ADI3             = (0x167), // End of A/D scanning operation(Gr.3)
    ELC_EVENT_ADC12_ADI4             = (0x168), // End of A/D scanning operation(Gr.4)
    ELC_EVENT_ADC12_ADI5678          = (0x169), // End of A/D scanning operation(Gr.5 to 8)
    ELC_EVENT_ADC12_CMPI2            = (0x16A), // Compare match interrupt with compare table 2
    ELC_EVENT_ADC12_CMPI3            = (0x16B), // Compare match interrupt with compare table 3
    ELC_EVENT_ADC1_COMPARE_MATCH     = (0x16C), // Composite compare match interrupt 1
    ELC_EVENT_ADC12_ERR1             = (0x16E), // A/D converter unit 1 Error
    ELC_EVENT_ADC12_RESOVF1          = (0x16F), // A/D conversion overflow on A/D converter unit 1
    ELC_EVENT_ADC12_CALEND1          = (0x171), // End of calibration of A/D converter unit 1
    ELC_EVENT_ADC12_FIFOREQ3         = (0x172), // FIFO data read request interrupt(Gr.3)
    ELC_EVENT_ADC12_FIFOREQ4         = (0x173), // FIFO data read request interrupt(Gr.4)
    ELC_EVENT_ADC12_FIFOREQ5678      = (0x174), // FIFO data read request interrupt(Gr.5 to 8)
    ELC_EVENT_SCI0_RXI               = (0x18D), // Receive data full
    ELC_EVENT_SCI0_TXI               = (0x18E), // Transmit data empty
    ELC_EVENT_SCI0_TEI               = (0x18F), // Transmit end
    ELC_EVENT_SCI0_ERI               = (0x190), // Receive error
    ELC_EVENT_SCI0_AED               = (0x191), // Active edge detection
    ELC_EVENT_SCI0_BFD               = (0x192), // Break field detection
    ELC_EVENT_SCI0_AM                = (0x193), // Address match event
    ELC_EVENT_SCI1_RXI               = (0x195), // Receive data full
    ELC_EVENT_SCI1_TXI               = (0x196), // Transmit data empty
    ELC_EVENT_SCI1_TEI               = (0x197), // Transmit end
    ELC_EVENT_SCI1_ERI               = (0x198), // Receive error
    ELC_EVENT_SCI1_AED               = (0x199), // Active edge detection
    ELC_EVENT_SCI1_BFD               = (0x19A), // Break field detection
    ELC_EVENT_SCI1_AM                = (0x19B), // Address match event
    ELC_EVENT_SCI2_RXI               = (0x19C), // Receive data full
    ELC_EVENT_SCI2_TXI               = (0x19D), // Transmit data empty
    ELC_EVENT_SCI2_TEI               = (0x19E), // Transmit end
    ELC_EVENT_SCI2_ERI               = (0x19F), // Receive error
    ELC_EVENT_SCI2_AED               = (0x1A0), // Active edge detection
    ELC_EVENT_SCI2_BFD               = (0x1A1), // Break field detection
    ELC_EVENT_SCI2_AM                = (0x1A2), // Address match event
    ELC_EVENT_SCI3_RXI               = (0x1A3), // Receive data full
    ELC_EVENT_SCI3_TXI               = (0x1A4), // Transmit data empty
    ELC_EVENT_SCI3_TEI               = (0x1A5), // Transmit end
    ELC_EVENT_SCI3_ERI               = (0x1A6), // Receive error
    ELC_EVENT_SCI3_AED               = (0x1A7), // Active edge detection
    ELC_EVENT_SCI3_BFD               = (0x1A8), // Break field detection
    ELC_EVENT_SCI3_AM                = (0x1A9), // Address match event
    ELC_EVENT_SCI4_RXI               = (0x1AA), // Receive data full
    ELC_EVENT_SCI4_TXI               = (0x1AB), // Transmit data empty
    ELC_EVENT_SCI4_TEI               = (0x1AC), // Transmit end
    ELC_EVENT_SCI4_ERI               = (0x1AD), // Receive error
    ELC_EVENT_SCI4_AED               = (0x1AE), // Active edge detection
    ELC_EVENT_SCI4_BFD               = (0x1AF), // Break field detection
    ELC_EVENT_SCI4_AM                = (0x1B0), // Address match event
    ELC_EVENT_SCI9_RXI               = (0x1B1), // Receive data full
    ELC_EVENT_SCI9_TXI               = (0x1B2), // Transmit data empty
    ELC_EVENT_SCI9_TEI               = (0x1B3), // Transmit end
    ELC_EVENT_SCI9_ERI               = (0x1B4), // Receive error
    ELC_EVENT_SCI9_AED               = (0x1B5), // Active edge detection
    ELC_EVENT_SCI9_BFD               = (0x1B6), // Break field detection
    ELC_EVENT_SCI9_AM                = (0x1B7), // Address match event
    ELC_EVENT_SPI0_RXI               = (0x1C4), // Receive buffer full
    ELC_EVENT_SPI0_TXI               = (0x1C5), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE              = (0x1C6), // Idle
    ELC_EVENT_SPI0_ERI               = (0x1C7), // Error
    ELC_EVENT_SPI0_TEI               = (0x1C8), // Transmission complete event
    ELC_EVENT_SPI1_RXI               = (0x1C9), // Receive buffer full
    ELC_EVENT_SPI1_TXI               = (0x1CA), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE              = (0x1CB), // Idle
    ELC_EVENT_SPI1_ERI               = (0x1CC), // Error
    ELC_EVENT_SPI1_TEI               = (0x1CD), // Transmission complete event
    ELC_CAN_MRAM_ERI                 = (0x1D0), // ECC error
    ELC_EVENT_DOC_INT                = (0x1DB), // Data operation circuit interrupt
} elc_event_t;

/** @} (end addtogroup BSP_MCU_RA6T2) */

#endif
