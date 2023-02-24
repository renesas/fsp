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
 * @addtogroup BSP_MCU_RA4M1
 * @{
 **********************************************************************************************************************/

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list may change based on based on the device.
 * */
typedef enum e_elc_event_ra4m1
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
    ELC_EVENT_ICU_IRQ8               = (9),   // External pin interrupt 8
    ELC_EVENT_ICU_IRQ9               = (10),  // External pin interrupt 9
    ELC_EVENT_ICU_IRQ10              = (11),  // External pin interrupt 10
    ELC_EVENT_ICU_IRQ11              = (12),  // External pin interrupt 11
    ELC_EVENT_ICU_IRQ12              = (13),  // External pin interrupt 12
    ELC_EVENT_ICU_IRQ13              = (14),  // External pin interrupt 13
    ELC_EVENT_ICU_IRQ14              = (15),  // External pin interrupt 14
    ELC_EVENT_ICU_IRQ15              = (16),  // External pin interrupt 15
    ELC_EVENT_DMAC0_INT              = (17),  // DMAC transfer end 0
    ELC_EVENT_DMAC1_INT              = (18),  // DMAC transfer end 1
    ELC_EVENT_DMAC2_INT              = (19),  // DMAC transfer end 2
    ELC_EVENT_DMAC3_INT              = (20),  // DMAC transfer end 3
    ELC_EVENT_DTC_COMPLETE           = (21),  // DTC last transfer
    ELC_EVENT_DTC_END                = (22),  // DTC transfer end
    ELC_EVENT_ICU_SNOOZE_CANCEL      = (23),  // Canceling from Snooze mode
    ELC_EVENT_FCU_FRDYI              = (24),  // Flash ready interrupt
    ELC_EVENT_LVD_LVD1               = (25),  // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2               = (26),  // Voltage monitor 2 interrupt
    ELC_EVENT_LVD_VBATT              = (27),  // VBATT low voltage detect
    ELC_EVENT_CGC_MOSC_STOP          = (28),  // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST     = (29),  // Snooze entry
    ELC_EVENT_AGT0_INT               = (30),  // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A         = (31),  // Compare match A
    ELC_EVENT_AGT0_COMPARE_B         = (32),  // Compare match B
    ELC_EVENT_AGT1_INT               = (33),  // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A         = (34),  // Compare match A
    ELC_EVENT_AGT1_COMPARE_B         = (35),  // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW         = (36),  // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW          = (37),  // WDT underflow
    ELC_EVENT_RTC_ALARM              = (38),  // Alarm interrupt
    ELC_EVENT_RTC_PERIOD             = (39),  // Periodic interrupt
    ELC_EVENT_RTC_CARRY              = (40),  // Carry interrupt
    ELC_EVENT_ADC0_SCAN_END          = (41),  // A/D scan end interrupt
    ELC_EVENT_ADC0_SCAN_END_B        = (42),  // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A          = (43),  // Window A Compare match
    ELC_EVENT_ADC0_WINDOW_B          = (44),  // Window B Compare match
    ELC_EVENT_ADC0_COMPARE_MATCH     = (45),  // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH  = (46),  // Compare mismatch
    ELC_EVENT_ACMPLP0_INT            = (47),  // Analog Comparator Channel 0 interrupt
    ELC_EVENT_ACMPLP1_INT            = (48),  // Analog Comparator Channel 1 interrupt
    ELC_EVENT_USBFS_FIFO_0           = (49),  // DMA transfer request 0
    ELC_EVENT_USBFS_FIFO_1           = (50),  // DMA transfer request 1
    ELC_EVENT_USBFS_INT              = (51),  // USBFS interrupt
    ELC_EVENT_USBFS_RESUME           = (52),  // USBFS resume interrupt
    ELC_EVENT_IIC0_RXI               = (53),  // Receive data full
    ELC_EVENT_IIC0_TXI               = (54),  // Transmit data empty
    ELC_EVENT_IIC0_TEI               = (55),  // Transmit end
    ELC_EVENT_IIC0_ERI               = (56),  // Transfer error
    ELC_EVENT_IIC0_WUI               = (57),  // Slave address match
    ELC_EVENT_IIC1_RXI               = (58),  // Receive data full
    ELC_EVENT_IIC1_TXI               = (59),  // Transmit data empty
    ELC_EVENT_IIC1_TEI               = (60),  // Transmit end
    ELC_EVENT_IIC1_ERI               = (61),  // Transfer error
    ELC_EVENT_SSI0_TXI               = (62),  // Transmit data empty
    ELC_EVENT_SSI0_RXI               = (63),  // Receive data full
    ELC_EVENT_SSI0_INT               = (65),  // Error interrupt
    ELC_EVENT_CTSU_WRITE             = (66),  // Write request interrupt
    ELC_EVENT_CTSU_READ              = (67),  // Measurement data transfer request interrupt
    ELC_EVENT_CTSU_END               = (68),  // Measurement end interrupt
    ELC_EVENT_KEY_INT                = (69),  // Key interrupt
    ELC_EVENT_DOC_INT                = (70),  // Data operation circuit interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR    = (71),  // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END    = (72),  // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW           = (73),  // Overflow interrupt
    ELC_EVENT_CAN0_ERROR             = (74),  // Error interrupt
    ELC_EVENT_CAN0_FIFO_RX           = (75),  // Receive FIFO interrupt
    ELC_EVENT_CAN0_FIFO_TX           = (76),  // Transmit FIFO interrupt
    ELC_EVENT_CAN0_MAILBOX_RX        = (77),  // Reception complete interrupt
    ELC_EVENT_CAN0_MAILBOX_TX        = (78),  // Transmission complete interrupt
    ELC_EVENT_IOPORT_EVENT_1         = (79),  // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2         = (80),  // Port 2 event
    ELC_EVENT_IOPORT_EVENT_3         = (81),  // Port 3 event
    ELC_EVENT_IOPORT_EVENT_4         = (82),  // Port 4 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0   = (83),  // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1   = (84),  // Software event 1
    ELC_EVENT_POEG0_EVENT            = (85),  // Port Output disable interrupt A
    ELC_EVENT_POEG1_EVENT            = (86),  // Port Output disable interrupt B
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A = (87),  // Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B = (88),  // Compare match B
    ELC_EVENT_GPT0_COMPARE_C         = (89),  // Compare match C
    ELC_EVENT_GPT0_COMPARE_D         = (90),  // Compare match D
    ELC_EVENT_GPT0_COMPARE_E         = (91),  // Compare match E
    ELC_EVENT_GPT0_COMPARE_F         = (92),  // Compare match F
    ELC_EVENT_GPT0_COUNTER_OVERFLOW  = (93),  // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW = (94),  // Underflow
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A = (95),  // Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B = (96),  // Compare match B
    ELC_EVENT_GPT1_COMPARE_C         = (97),  // Compare match C
    ELC_EVENT_GPT1_COMPARE_D         = (98),  // Compare match D
    ELC_EVENT_GPT1_COMPARE_E         = (99),  // Compare match E
    ELC_EVENT_GPT1_COMPARE_F         = (100), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW  = (101), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW = (102), // Underflow
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A = (103), // Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B = (104), // Compare match B
    ELC_EVENT_GPT2_COMPARE_C         = (105), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D         = (106), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E         = (107), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F         = (108), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW  = (109), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW = (110), // Underflow
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A = (111), // Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B = (112), // Compare match B
    ELC_EVENT_GPT3_COMPARE_C         = (113), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D         = (114), // Compare match D
    ELC_EVENT_GPT3_COMPARE_E         = (115), // Compare match E
    ELC_EVENT_GPT3_COMPARE_F         = (116), // Compare match F
    ELC_EVENT_GPT3_COUNTER_OVERFLOW  = (117), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW = (118), // Underflow
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A = (119), // Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B = (120), // Compare match B
    ELC_EVENT_GPT4_COMPARE_C         = (121), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D         = (122), // Compare match D
    ELC_EVENT_GPT4_COMPARE_E         = (123), // Compare match E
    ELC_EVENT_GPT4_COMPARE_F         = (124), // Compare match F
    ELC_EVENT_GPT4_COUNTER_OVERFLOW  = (125), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW = (126), // Underflow
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A = (127), // Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B = (128), // Compare match B
    ELC_EVENT_GPT5_COMPARE_C         = (129), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D         = (130), // Compare match D
    ELC_EVENT_GPT5_COMPARE_E         = (131), // Compare match E
    ELC_EVENT_GPT5_COMPARE_F         = (132), // Compare match F
    ELC_EVENT_GPT5_COUNTER_OVERFLOW  = (133), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW = (134), // Underflow
    ELC_EVENT_GPT6_CAPTURE_COMPARE_A = (135), // Compare match A
    ELC_EVENT_GPT6_CAPTURE_COMPARE_B = (136), // Compare match B
    ELC_EVENT_GPT6_COMPARE_C         = (137), // Compare match C
    ELC_EVENT_GPT6_COMPARE_D         = (138), // Compare match D
    ELC_EVENT_GPT6_COMPARE_E         = (139), // Compare match E
    ELC_EVENT_GPT6_COMPARE_F         = (140), // Compare match F
    ELC_EVENT_GPT6_COUNTER_OVERFLOW  = (141), // Overflow
    ELC_EVENT_GPT6_COUNTER_UNDERFLOW = (142), // Underflow
    ELC_EVENT_GPT7_CAPTURE_COMPARE_A = (143), // Compare match A
    ELC_EVENT_GPT7_CAPTURE_COMPARE_B = (144), // Compare match B
    ELC_EVENT_GPT7_COMPARE_C         = (145), // Compare match C
    ELC_EVENT_GPT7_COMPARE_D         = (146), // Compare match D
    ELC_EVENT_GPT7_COMPARE_E         = (147), // Compare match E
    ELC_EVENT_GPT7_COMPARE_F         = (148), // Compare match F
    ELC_EVENT_GPT7_COUNTER_OVERFLOW  = (149), // Overflow
    ELC_EVENT_GPT7_COUNTER_UNDERFLOW = (150), // Underflow
    ELC_EVENT_OPS_UVW_EDGE           = (151), // UVW edge event
    ELC_EVENT_SCI0_RXI               = (152), // Receive data full
    ELC_EVENT_SCI0_TXI               = (153), // Transmit data empty
    ELC_EVENT_SCI0_TEI               = (154), // Transmit end
    ELC_EVENT_SCI0_ERI               = (155), // Receive error
    ELC_EVENT_SCI0_AM                = (156), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI        = (157), // Receive data full/Receive
    ELC_EVENT_SCI1_RXI               = (158), // Received data full
    ELC_EVENT_SCI1_TXI               = (159), // Transmit data empty
    ELC_EVENT_SCI1_TEI               = (160), // Transmit end
    ELC_EVENT_SCI1_ERI               = (161), // Receive error
    ELC_EVENT_SCI1_AM                = (162), // Address match event
    ELC_EVENT_SCI2_RXI               = (163), // Received data full
    ELC_EVENT_SCI2_TXI               = (164), // Transmit data empty
    ELC_EVENT_SCI2_TEI               = (165), // Transmit end
    ELC_EVENT_SCI2_ERI               = (166), // Receive error
    ELC_EVENT_SCI2_AM                = (167), // Address match event
    ELC_EVENT_SCI9_RXI               = (168), // Received data full
    ELC_EVENT_SCI9_TXI               = (169), // Transmit data empty
    ELC_EVENT_SCI9_TEI               = (170), // Transmit end
    ELC_EVENT_SCI9_ERI               = (171), // Receive error
    ELC_EVENT_SCI9_AM                = (172), // Address match event
    ELC_EVENT_SPI0_RXI               = (173), // Receive buffer full
    ELC_EVENT_SPI0_TXI               = (174), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE              = (175), // Idle
    ELC_EVENT_SPI0_ERI               = (176), // Error
    ELC_EVENT_SPI0_TEI               = (177), // Transmission complete event
    ELC_EVENT_SPI1_RXI               = (178), // Receive buffer full
    ELC_EVENT_SPI1_TXI               = (179), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE              = (180), // Idle
    ELC_EVENT_SPI1_ERI               = (181), // Error
    ELC_EVENT_SPI1_TEI               = (182), // Transmission complete event
    ELC_EVENT_SCE_PROC_BUSY          = (183),
    ELC_EVENT_SCE_ROMOK              = (184),
    ELC_EVENT_SCE_LONG_PLG           = (185),
    ELC_EVENT_SCE_TEST_BUSY          = (186),
    ELC_EVENT_SCE_WRRDY_0            = (187),
    ELC_EVENT_SCE_WRRDY_4            = (188),
    ELC_EVENT_SCE_RDRDY_0            = (189),
    ELC_EVENT_SCE_INTEGRATE_WRRDY    = (190),
    ELC_EVENT_SCE_INTEGRATE_RDRDY    = (191),
} elc_event_t;

/** @} (end addtogroup BSP_MCU_RA4M1) */

#endif
