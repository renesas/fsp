/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @addtogroup BSP_MCU_RA4W1
 * @{
 **********************************************************************************************************************/

/** Sources of event signals to be linked to other peripherals or the CPU1
 * @note This list may change based on device. This list is for RA4W1.
 * */
typedef enum e_elc_event
{
    ELC_EVENT_NONE                   = (0),   // Link disabled
    ELC_EVENT_ICU_IRQ0               = (1),   // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1               = (2),   // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2               = (3),   // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3               = (4),   // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4               = (5),   // External pin interrupt 4
    ELC_EVENT_ICU_IRQ6               = (7),   // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7               = (8),   // External pin interrupt 7
    ELC_EVENT_ICU_IRQ8               = (9),   // Interrupt for BLE middleware use only
    ELC_EVENT_ICU_IRQ9               = (10),  // External pin interrupt 9
    ELC_EVENT_ICU_IRQ11              = (12),  // External pin interrupt 11
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
    ELC_EVENT_SSI0_TXI               = (66),  // Transmit data empty
    ELC_EVENT_SSI0_RXI               = (67),  // Receive data full
    ELC_EVENT_SSI0_INT               = (69),  // Error interrupt
    ELC_EVENT_CTSU_WRITE             = (70),  // Write request interrupt
    ELC_EVENT_CTSU_READ              = (71),  // Measurement data transfer request interrupt
    ELC_EVENT_CTSU_END               = (72),  // Measurement end interrupt
    ELC_EVENT_KEY_INT                = (73),  // Key interrupt
    ELC_EVENT_DOC_INT                = (74),  // Data operation circuit interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR    = (75),  // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END    = (76),  // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW           = (77),  // Overflow interrupt
    ELC_EVENT_CAN0_ERROR             = (78),  // Error interrupt
    ELC_EVENT_CAN0_FIFO_RX           = (79),  // Receive FIFO interrupt
    ELC_EVENT_CAN0_FIFO_TX           = (80),  // Transmit FIFO interrupt
    ELC_EVENT_CAN0_MAILBOX_RX        = (81),  // Reception complete interrupt
    ELC_EVENT_CAN0_MAILBOX_TX        = (82),  // Transmission complete interrupt
    ELC_EVENT_IOPORT_EVENT_1         = (83),  // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2         = (84),  // Port 2 event
    ELC_EVENT_IOPORT_EVENT_3         = (85),  // Port 3 event
    ELC_EVENT_IOPORT_EVENT_4         = (86),  // Port 4 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0   = (87),  // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1   = (88),  // Software event 1
    ELC_EVENT_POEG0_EVENT            = (89),  // Port Output disable interrupt A
    ELC_EVENT_POEG1_EVENT            = (90),  // Port Output disable interrupt B
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A = (91),  // Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B = (92),  // Compare match B
    ELC_EVENT_GPT0_COMPARE_C         = (93),  // Compare match C
    ELC_EVENT_GPT0_COMPARE_D         = (94),  // Compare match D
    ELC_EVENT_GPT0_COMPARE_E         = (95),  // Compare match E
    ELC_EVENT_GPT0_COMPARE_F         = (96),  // Compare match F
    ELC_EVENT_GPT0_COUNTER_OVERFLOW  = (97),  // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW = (98),  // Underflow
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A = (99),  // Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B = (100), // Compare match B
    ELC_EVENT_GPT1_COMPARE_C         = (101), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D         = (102), // Compare match D
    ELC_EVENT_GPT1_COMPARE_E         = (103), // Compare match E
    ELC_EVENT_GPT1_COMPARE_F         = (104), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW  = (105), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW = (106), // Underflow
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A = (107), // Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B = (108), // Compare match B
    ELC_EVENT_GPT2_COMPARE_C         = (109), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D         = (110), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E         = (111), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F         = (112), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW  = (113), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW = (114), // Underflow
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A = (115), // Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B = (116), // Compare match B
    ELC_EVENT_GPT3_COMPARE_C         = (117), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D         = (118), // Compare match D
    ELC_EVENT_GPT3_COMPARE_E         = (119), // Compare match E
    ELC_EVENT_GPT3_COMPARE_F         = (120), // Compare match F
    ELC_EVENT_GPT3_COUNTER_OVERFLOW  = (121), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW = (122), // Underflow
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A = (123), // Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B = (124), // Compare match B
    ELC_EVENT_GPT4_COMPARE_C         = (125), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D         = (126), // Compare match D
    ELC_EVENT_GPT4_COMPARE_E         = (127), // Compare match E
    ELC_EVENT_GPT4_COMPARE_F         = (128), // Compare match F
    ELC_EVENT_GPT4_COUNTER_OVERFLOW  = (129), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW = (130), // Underflow
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A = (131), // Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B = (132), // Compare match B
    ELC_EVENT_GPT5_COMPARE_C         = (133), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D         = (134), // Compare match D
    ELC_EVENT_GPT5_COMPARE_E         = (135), // Compare match E
    ELC_EVENT_GPT5_COMPARE_F         = (136), // Compare match F
    ELC_EVENT_GPT5_COUNTER_OVERFLOW  = (137), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW = (138), // Underflow
    ELC_EVENT_GPT8_CAPTURE_COMPARE_A = (155), // Compare match A
    ELC_EVENT_GPT8_CAPTURE_COMPARE_B = (156), // Compare match B
    ELC_EVENT_GPT8_COMPARE_C         = (157), // Compare match C
    ELC_EVENT_GPT8_COMPARE_D         = (158), // Compare match D
    ELC_EVENT_GPT8_COMPARE_E         = (159), // Compare match E
    ELC_EVENT_GPT8_COMPARE_F         = (160), // Compare match F
    ELC_EVENT_GPT8_COUNTER_OVERFLOW  = (161), // Overflow
    ELC_EVENT_GPT8_COUNTER_UNDERFLOW = (162), // Underflow
    ELC_EVENT_OPS_UVW_EDGE           = (171), // UVW edge event
    ELC_EVENT_SCI0_RXI               = (172), // Receive data full
    ELC_EVENT_SCI0_TXI               = (173), // Transmit data empty
    ELC_EVENT_SCI0_TEI               = (174), // Transmit end
    ELC_EVENT_SCI0_ERI               = (175), // Receive error
    ELC_EVENT_SCI0_AM                = (176), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI        = (177), // Receive data full/Receive
    ELC_EVENT_SCI1_RXI               = (178), // Received data full
    ELC_EVENT_SCI1_TXI               = (179), // Transmit data empty
    ELC_EVENT_SCI1_TEI               = (180), // Transmit end
    ELC_EVENT_SCI1_ERI               = (181), // Receive error
    ELC_EVENT_SCI1_AM                = (182), // Address match event
    ELC_EVENT_SCI4_RXI               = (193), // Received data full
    ELC_EVENT_SCI4_TXI               = (194), // Transmit data empty
    ELC_EVENT_SCI4_TEI               = (195), // Transmit end
    ELC_EVENT_SCI4_ERI               = (196), // Receive error
    ELC_EVENT_SCI4_AM                = (197), // Address match event
    ELC_EVENT_SCI9_RXI               = (198), // Received data full
    ELC_EVENT_SCI9_TXI               = (199), // Transmit data empty
    ELC_EVENT_SCI9_TEI               = (200), // Transmit end
    ELC_EVENT_SCI9_ERI               = (201), // Receive error
    ELC_EVENT_SCI9_AM                = (202), // Address match event
    ELC_EVENT_SPI0_RXI               = (203), // Receive buffer full
    ELC_EVENT_SPI0_TXI               = (204), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE              = (205), // Idle
    ELC_EVENT_SPI0_ERI               = (206), // Error
    ELC_EVENT_SPI0_TEI               = (207), // Transmission complete event
    ELC_EVENT_SPI1_RXI               = (208), // Receive buffer full
    ELC_EVENT_SPI1_TXI               = (209), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE              = (210), // Idle
    ELC_EVENT_SPI1_ERI               = (211), // Error
    ELC_EVENT_SPI1_TEI               = (212), // Transmission complete event
    ELC_EVENT_QSPI_INT               = (213), // Error
    ELC_EVENT_SDHIMMC0_ACCS          = (214), // Card access
    ELC_EVENT_SDHIMMC0_SDIO          = (215), // SDIO access
    ELC_EVENT_SDHIMMC0_CARD          = (216), // Card detect
    ELC_EVENT_SDHIMMC0_DMA_REQ       = (217), // DMA transfer request
    ELC_EVENT_SCE_PROC_BUSY          = (218),
    ELC_EVENT_SCE_ROMOK              = (219),
    ELC_EVENT_SCE_LONG_PLG           = (220),
    ELC_EVENT_SCE_TEST_BUSY          = (221),
    ELC_EVENT_SCE_WRRDY_0            = (222),
    ELC_EVENT_SCE_WRRDY_4            = (223),
    ELC_EVENT_SCE_RDRDY_0            = (224),
    ELC_EVENT_SCE_INTEGRATE_WRRDY    = (225),
    ELC_EVENT_SCE_INTEGRATE_RDRDY    = (226),
} elc_event_t;

/** @} (end addtogroup BSP_MCU_RA4W1) */

#endif
