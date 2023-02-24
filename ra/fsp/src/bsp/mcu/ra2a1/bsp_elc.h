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

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA2A1
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

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list may change based on based on the device.
 * */
typedef enum e_elc_event_ra2a1
{
    ELC_EVENT_NONE                   = (0),   // Link disabled
    ELC_EVENT_ICU_IRQ0               = (1),   // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1               = (2),   // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2               = (3),   // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3               = (4),   // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4               = (5),   // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5               = (6),   // External pin interrupt 5
    ELC_EVENT_ICU_IRQ6               = (7),   // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7               = (8),   // External pin interrupt 7
    ELC_EVENT_DTC_COMPLETE           = (9),   // DTC last transfer
    ELC_EVENT_DTC_END                = (10),  // DTC transfer end
    ELC_EVENT_ICU_SNOOZE_CANCEL      = (11),  // Canceling from Snooze mode
    ELC_EVENT_FCU_FRDYI              = (12),  // Flash ready interrupt
    ELC_EVENT_LVD_LVD1               = (13),  // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2               = (14),  // Voltage monitor 2 interrupt
    ELC_EVENT_CGC_MOSC_STOP          = (15),  // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST     = (16),  // Snooze entry
    ELC_EVENT_AGT0_INT               = (17),  // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A         = (18),  // Compare match A
    ELC_EVENT_AGT0_COMPARE_B         = (19),  // Compare match B
    ELC_EVENT_AGT1_INT               = (20),  // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A         = (21),  // Compare match A
    ELC_EVENT_AGT1_COMPARE_B         = (22),  // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW         = (23),  // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW          = (24),  // WDT underflow
    ELC_EVENT_RTC_ALARM              = (25),  // Alarm interrupt
    ELC_EVENT_RTC_PERIOD             = (26),  // Periodic interrupt
    ELC_EVENT_RTC_CARRY              = (27),  // Carry interrupt
    ELC_EVENT_ADC0_SCAN_END          = (28),  // A/D scan end interrupt
    ELC_EVENT_ADC0_SCAN_END_B        = (29),  // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A          = (30),  // Window A Compare match
    ELC_EVENT_ADC0_WINDOW_B          = (31),  // Window B Compare match
    ELC_EVENT_ADC0_COMPARE_MATCH     = (32),  // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH  = (33),  // Compare mismatch
    ELC_EVENT_ACMPHS0_INT            = (34),  // Comparator interrupt 0
    ELC_EVENT_ACMPLP0_INT            = (35),  // Analog Comparator Channel 0 interrupt
    ELC_EVENT_ACMPLP1_INT            = (36),  // Analog Comparator Channel 1 interrupt
    ELC_EVENT_USBFS_INT              = (37),  // USBFS interrupt
    ELC_EVENT_USBFS_RESUME           = (38),  // USBFS resume interrupt
    ELC_EVENT_IIC0_RXI               = (39),  // Receive data full
    ELC_EVENT_IIC0_TXI               = (40),  // Transmit data empty
    ELC_EVENT_IIC0_TEI               = (41),  // Transmit end
    ELC_EVENT_IIC0_ERI               = (42),  // Transfer error
    ELC_EVENT_IIC0_WUI               = (43),  // Slave address match
    ELC_EVENT_IIC1_RXI               = (44),  // Receive data full
    ELC_EVENT_IIC1_TXI               = (45),  // Transmit data empty
    ELC_EVENT_IIC1_TEI               = (46),  // Transmit end
    ELC_EVENT_IIC1_ERI               = (47),  // Transfer error
    ELC_EVENT_CTSU_WRITE             = (48),  // Write request interrupt
    ELC_EVENT_CTSU_READ              = (49),  // Measurement data transfer request interrupt
    ELC_EVENT_CTSU_END               = (50),  // Measurement end interrupt
    ELC_EVENT_KEY_INT                = (51),  // Key interrupt
    ELC_EVENT_DOC_INT                = (52),  // Data operation circuit interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR    = (53),  // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END    = (54),  // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW           = (55),  // Overflow interrupt
    ELC_EVENT_CAN0_ERROR             = (56),  // Error interrupt
    ELC_EVENT_CAN0_FIFO_RX           = (57),  // Receive FIFO interrupt
    ELC_EVENT_CAN0_FIFO_TX           = (58),  // Transmit FIFO interrupt
    ELC_EVENT_CAN0_MAILBOX_RX        = (59),  // Reception complete interrupt
    ELC_EVENT_CAN0_MAILBOX_TX        = (60),  // Transmission complete interrupt
    ELC_EVENT_IOPORT_EVENT_1         = (61),  // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2         = (62),  // Port 2 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0   = (63),  // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1   = (64),  // Software event 1
    ELC_EVENT_POEG0_EVENT            = (65),  // Port Output disable interrupt A
    ELC_EVENT_POEG1_EVENT            = (66),  // Port Output disable interrupt B
    ELC_EVENT_SDADC0_ADI             = (67),  // End of SD A/D conversion
    ELC_EVENT_SDADC0_SCANEND         = (68),  // End of SD A/D scan
    ELC_EVENT_SDADC0_CALIEND         = (69),  // End of SD A/D A/D calibration
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A = (70),  // Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B = (71),  // Compare match B
    ELC_EVENT_GPT0_COMPARE_C         = (72),  // Compare match C
    ELC_EVENT_GPT0_COMPARE_D         = (73),  // Compare match D
    ELC_EVENT_GPT0_COUNTER_OVERFLOW  = (74),  // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW = (75),  // Underflow
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A = (76),  // Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B = (77),  // Compare match B
    ELC_EVENT_GPT1_COMPARE_C         = (78),  // Compare match C
    ELC_EVENT_GPT1_COMPARE_D         = (79),  // Compare match D
    ELC_EVENT_GPT1_COUNTER_OVERFLOW  = (80),  // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW = (81),  // Underflow
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A = (82),  // Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B = (83),  // Compare match B
    ELC_EVENT_GPT2_COMPARE_C         = (84),  // Compare match C
    ELC_EVENT_GPT2_COMPARE_D         = (85),  // Compare match D
    ELC_EVENT_GPT2_COUNTER_OVERFLOW  = (86),  // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW = (87),  // Underflow
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A = (88),  // Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B = (89),  // Compare match B
    ELC_EVENT_GPT3_COMPARE_C         = (90),  // Compare match C
    ELC_EVENT_GPT3_COMPARE_D         = (91),  // Compare match D
    ELC_EVENT_GPT3_COUNTER_OVERFLOW  = (92),  // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW = (93),  // Underflow
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A = (94),  // Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B = (95),  // Compare match B
    ELC_EVENT_GPT4_COMPARE_C         = (96),  // Compare match C
    ELC_EVENT_GPT4_COMPARE_D         = (97),  // Compare match D
    ELC_EVENT_GPT4_COUNTER_OVERFLOW  = (98),  // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW = (99),  // Underflow
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A = (100), // Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B = (101), // Compare match B
    ELC_EVENT_GPT5_COMPARE_C         = (102), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D         = (103), // Compare match D
    ELC_EVENT_GPT5_COUNTER_OVERFLOW  = (104), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW = (105), // Underflow
    ELC_EVENT_GPT6_CAPTURE_COMPARE_A = (106), // Compare match A
    ELC_EVENT_GPT6_CAPTURE_COMPARE_B = (107), // Compare match B
    ELC_EVENT_GPT6_COMPARE_C         = (108), // Compare match C
    ELC_EVENT_GPT6_COMPARE_D         = (109), // Compare match D
    ELC_EVENT_GPT6_COUNTER_OVERFLOW  = (110), // Overflow
    ELC_EVENT_GPT6_COUNTER_UNDERFLOW = (111), // Underflow
    ELC_EVENT_OPS_UVW_EDGE           = (112), // UVW edge event
    ELC_EVENT_SCI0_RXI               = (113), // Receive data full
    ELC_EVENT_SCI0_TXI               = (114), // Transmit data empty
    ELC_EVENT_SCI0_TEI               = (115), // Transmit end
    ELC_EVENT_SCI0_ERI               = (116), // Receive error
    ELC_EVENT_SCI0_AM                = (117), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI        = (118), // Receive data full/Receive
    ELC_EVENT_SCI1_RXI               = (119), // Received data full
    ELC_EVENT_SCI1_TXI               = (120), // Transmit data empty
    ELC_EVENT_SCI1_TEI               = (121), // Transmit end
    ELC_EVENT_SCI1_ERI               = (122), // Receive error
    ELC_EVENT_SCI1_AM                = (123), // Address match event
    ELC_EVENT_SCI9_RXI               = (124), // Received data full
    ELC_EVENT_SCI9_TXI               = (125), // Transmit data empty
    ELC_EVENT_SCI9_TEI               = (126), // Transmit end
    ELC_EVENT_SCI9_ERI               = (127), // Receive error
    ELC_EVENT_SCI9_AM                = (128), // Address match event
    ELC_EVENT_SPI0_RXI               = (129), // Receive buffer full
    ELC_EVENT_SPI0_TXI               = (130), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE              = (131), // Idle
    ELC_EVENT_SPI0_ERI               = (132), // Error
    ELC_EVENT_SPI0_TEI               = (133), // Transmission complete event
    ELC_EVENT_SPI1_RXI               = (134), // Receive buffer full
    ELC_EVENT_SPI1_TXI               = (135), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE              = (136), // Idle
    ELC_EVENT_SPI1_ERI               = (137), // Error
    ELC_EVENT_SPI1_TEI               = (138), // Transmission complete event
    ELC_EVENT_AES_WRREQ              = (139),
    ELC_EVENT_AES_RDREQ              = (140),
    ELC_EVENT_TRNG_RDREQ             = (141),
} elc_event_t;

/** @} (end addtogroup BSP_MCU_RA2A1) */

#endif
