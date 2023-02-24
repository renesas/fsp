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
 * @addtogroup BSP_MCU_RA4E1
 * @{
 **********************************************************************************************************************/

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list may change based on based on the device.
 * */
typedef enum e_elc_event_ra4m1
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
    ELC_EVENT_ICU_IRQ13              = (0x00E), // External pin interrupt 13
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
    ELC_EVENT_AGT2_INT               = (0x046), // AGT interrupt
    ELC_EVENT_AGT2_COMPARE_A         = (0x047), // Compare match A
    ELC_EVENT_AGT2_COMPARE_B         = (0x048), // Compare match B
    ELC_EVENT_AGT3_INT               = (0x049), // AGT interrupt
    ELC_EVENT_AGT3_COMPARE_A         = (0x04A), // Compare match A
    ELC_EVENT_AGT3_COMPARE_B         = (0x04B), // Compare match B
    ELC_EVENT_AGT5_INT               = (0x04F), // AGT interrupt
    ELC_EVENT_AGT5_COMPARE_A         = (0x050), // Compare match A
    ELC_EVENT_AGT5_COMPARE_B         = (0x051), // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW         = (0x052), // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW          = (0x053), // WDT underflow
    ELC_EVENT_RTC_ALARM              = (0x054), // Alarm interrupt
    ELC_EVENT_RTC_PERIOD             = (0x055), // Periodic interrupt
    ELC_EVENT_RTC_CARRY              = (0x056), // Carry interrupt
    ELC_EVENT_USBFS_FIFO_0           = (0x06B), // DMA transfer request 0
    ELC_EVENT_USBFS_FIFO_1           = (0x06C), // DMA transfer request 1
    ELC_EVENT_USBFS_INT              = (0x06D), // USBFS interrupt
    ELC_EVENT_USBFS_RESUME           = (0x06E), // USBFS resume interrupt
    ELC_EVENT_IIC0_RXI               = (0x073), // Receive data full
    ELC_EVENT_IIC0_TXI               = (0x074), // Transmit data empty
    ELC_EVENT_IIC0_TEI               = (0x075), // Transmit end
    ELC_EVENT_IIC0_ERI               = (0x076), // Transfer error
    ELC_EVENT_IIC0_WUI               = (0x077), // Slave address match
    ELC_EVENT_CAC_FREQUENCY_ERROR    = (0x09E), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END    = (0x09F), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW           = (0x0A0), // Overflow interrupt
    ELC_EVENT_CAN0_ERROR             = (0x0A1), // Error interrupt
    ELC_EVENT_CAN0_FIFO_RX           = (0x0A2), // Receive FIFO interrupt
    ELC_EVENT_CAN0_FIFO_TX           = (0x0A3), // Transmit FIFO interrupt
    ELC_EVENT_CAN0_MAILBOX_RX        = (0x0A4), // Reception complete interrupt
    ELC_EVENT_CAN0_MAILBOX_TX        = (0x0A5), // Transmission complete interrupt
    ELC_EVENT_IOPORT_EVENT_1         = (0x0B1), // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2         = (0x0B2), // Port 2 event
    ELC_EVENT_IOPORT_EVENT_3         = (0x0B3), // Port 3 event
    ELC_EVENT_IOPORT_EVENT_4         = (0x0B4), // Port 4 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0   = (0x0B5), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1   = (0x0B6), // Software event 1
    ELC_EVENT_POEG0_EVENT            = (0x0B7), // Port Output disable interrupt A
    ELC_EVENT_POEG1_EVENT            = (0x0B8), // Port Output disable interrupt B
    ELC_EVENT_POEG2_EVENT            = (0x0B9), // Port Output disable interrupt C
    ELC_EVENT_POEG3_EVENT            = (0x0BA), // Port Output disable interrupt D
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A = (0x0C9), // Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B = (0x0CA), // Compare match B
    ELC_EVENT_GPT1_COMPARE_C         = (0x0CB), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D         = (0x0CC), // Compare match D
    ELC_EVENT_GPT1_COMPARE_E         = (0x0CD), // Compare match E
    ELC_EVENT_GPT1_COMPARE_F         = (0x0CE), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW  = (0x0CF), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW = (0x0D0), // Underflow
    ELC_EVENT_GPT1_PC                = (0x0D1), // Period count function finish
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A = (0x0D2), // Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B = (0x0D3), // Compare match B
    ELC_EVENT_GPT2_COMPARE_C         = (0x0D4), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D         = (0x0D5), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E         = (0x0D6), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F         = (0x0D7), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW  = (0x0D8), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW = (0x0D9), // Underflow
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A = (0x0E4), // Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B = (0x0E5), // Compare match B
    ELC_EVENT_GPT4_COMPARE_C         = (0x0E6), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D         = (0x0E7), // Compare match D
    ELC_EVENT_GPT4_COMPARE_E         = (0x0E8), // Compare match E
    ELC_EVENT_GPT4_COMPARE_F         = (0x0E9), // Compare match F
    ELC_EVENT_GPT4_COUNTER_OVERFLOW  = (0x0EA), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW = (0x0EB), // Underflow
    ELC_EVENT_GPT4_PC                = (0x0EC), // Period count function finish
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A = (0x0ED), // Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B = (0x0EE), // Compare match B
    ELC_EVENT_GPT5_COMPARE_C         = (0x0EF), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D         = (0x0F0), // Compare match D
    ELC_EVENT_GPT5_COMPARE_E         = (0x0F1), // Compare match E
    ELC_EVENT_GPT5_COMPARE_F         = (0x0F2), // Compare match F
    ELC_EVENT_GPT5_COUNTER_OVERFLOW  = (0x0F3), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW = (0x0F4), // Underflow
    ELC_EVENT_GPT5_PC                = (0x0F5), // Period count function finish
    ELC_EVENT_ADC0_SCAN_END          = (0x160), // A/D scan end interrupt
    ELC_EVENT_ADC0_SCAN_END_B        = (0x161), // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A          = (0x162), // Window A Compare match
    ELC_EVENT_ADC0_WINDOW_B          = (0x163), // Window B Compare match
    ELC_EVENT_ADC0_COMPARE_MATCH     = (0x164), // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH  = (0x165), // Compare mismatch
    ELC_EVENT_SCI0_RXI               = (0x180), // Receive data full
    ELC_EVENT_SCI0_TXI               = (0x181), // Transmit data empty
    ELC_EVENT_SCI0_TEI               = (0x182), // Transmit end
    ELC_EVENT_SCI0_ERI               = (0x183), // Receive error
    ELC_EVENT_SCI0_AM                = (0x184), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI        = (0x185), // Receive data full/Receive
    ELC_EVENT_SCI3_RXI               = (0x192), // Received data full
    ELC_EVENT_SCI3_TXI               = (0x193), // Transmit data empty
    ELC_EVENT_SCI3_TEI               = (0x194), // Transmit end
    ELC_EVENT_SCI3_ERI               = (0x195), // Receive error
    ELC_EVENT_SCI3_AM                = (0x196), // Address match event
    ELC_EVENT_SCI4_RXI               = (0x198), // Received data full
    ELC_EVENT_SCI4_TXI               = (0x199), // Transmit data empty
    ELC_EVENT_SCI4_TEI               = (0x19A), // Transmit end
    ELC_EVENT_SCI4_ERI               = (0x19B), // Receive error
    ELC_EVENT_SCI4_AM                = (0x19C), // Address match event
    ELC_EVENT_SCI9_RXI               = (0x1B6), // Received data full
    ELC_EVENT_SCI9_TXI               = (0x1B7), // Transmit data empty
    ELC_EVENT_SCI9_TEI               = (0x1B8), // Transmit end
    ELC_EVENT_SCI9_ERI               = (0x1B9), // Receive error
    ELC_EVENT_SCI9_AM                = (0x1BA), // Address match event
    ELC_EVENT_SPI0_RXI               = (0x1C4), // Receive buffer full
    ELC_EVENT_SPI0_TXI               = (0x1C5), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE              = (0x1C6), // Idle
    ELC_EVENT_SPI0_ERI               = (0x1C7), // Error
    ELC_EVENT_SPI0_TEI               = (0x1C8), // Transmission complete event
    ELC_EVENT_QSPI_INT               = (0x1DA), // QSPI interrupt
    ELC_EVENT_DOC_INT                = (0x1DB), // Data operation circuit interrupt
} elc_event_t;

/** @} (end addtogroup BSP_MCU_RA4E1) */

#endif
