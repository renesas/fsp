/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup MIPI_CSI
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_MIPI_CSI_DEVICE_TYPES_H
#define R_MIPI_CSI_DEVICE_TYPES_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************/

/* MIPI CSI Variable Length Spacer Type */
typedef enum e_mipi_csi_variable_length_spacer
{
    MIPI_CSI_VARIABLE_LENGTH_SPACER_NONE = 0, ///< Variable length spacer invalid (spacer number is fixed length)
    MIPI_CSI_VARIABLE_LENGTH_SPACER_1    = 1, ///< Variable length spacer valid (spacer number is 1 * n/lane)
    MIPI_CSI_VARIABLE_LENGTH_SPACER_2    = 2, ///< Variable length spacer valid (spacer number is 2 * n/lane)
    MIPI_CSI_VARIABLE_LENGTH_SPACER_4    = 3, ///< Variable length spacer valid (spacer number is 4 * n/lane)
} mipi_csi_variable_length_spacer_t;

/* MIPI CSI Receive Data Enable Type */
typedef enum e_mipi_csi_rx_data_enable
{
    MIPI_CSI_RX_DATA_ENABLE_EOT            = 1ULL << 4,  ///< MIPI CSI Data Type Enable EoT Reception
    MIPI_CSI_RX_DATA_ENABLE_SHORT_PACKET_1 = 1ULL << 8,  ///< MIPI CSI Data Type Enable Generic Short Packet 1 Reception
    MIPI_CSI_RX_DATA_ENABLE_SHORT_PACKET_2 = 1ULL << 9,  ///< MIPI CSI Data Type Enable Generic Short Packet 2 Reception
    MIPI_CSI_RX_DATA_ENABLE_SHORT_PACKET_3 = 1ULL << 10, ///< MIPI CSI Data Type Enable Generic Short Packet 3 Reception
    MIPI_CSI_RX_DATA_ENABLE_SHORT_PACKET_4 = 1ULL << 11, ///< MIPI CSI Data Type Enable Generic Short Packet 4 Reception
    MIPI_CSI_RX_DATA_ENABLE_SHORT_PACKET_5 = 1ULL << 12, ///< MIPI CSI Data Type Enable Generic Short Packet 5 Reception
    MIPI_CSI_RX_DATA_ENABLE_SHORT_PACKET_6 = 1ULL << 13, ///< MIPI CSI Data Type Enable Generic Short Packet 6 Reception
    MIPI_CSI_RX_DATA_ENABLE_SHORT_PACKET_7 = 1ULL << 14, ///< MIPI CSI Data Type Enable Generic Short Packet 7 Reception
    MIPI_CSI_RX_DATA_ENABLE_SHORT_PACKET_8 = 1ULL << 15, ///< MIPI CSI Data Type Enable Generic Short Packet 8 Reception
    MIPI_CSI_RX_DATA_ENABLE_YUV422_8_BIT   = 1ULL << 30, ///< MIPI CSI Data Type Enable YUV 422 8-bit Streaming Data Reception
    MIPI_CSI_RX_DATA_ENABLE_YUV422_10_BIT  = 1ULL << 31, ///< MIPI CSI Data Type Enable YUV 422 10-bit Streaming Data Reception
    MIPI_CSI_RX_DATA_ENABLE_RGB888         = 1ULL << 35, ///< MIPI CSI Data Type Enable RAW8 Streaming Data Reception
    MIPI_CSI_RX_DATA_ENABLE_RAW8           = 1ULL << 41, ///< MIPI CSI Data Type Enable RGB888 Streaming Data Reception
} mipi_csi_rx_data_enable_t;

/** MIPI CSI Interrupt Status Type (MIST) */
typedef union st_mipi_csi_interrupt_status
{
    struct
    {
        uint32_t data_lane_0      : 1; ///< MIPI CSI Data Lane 0 Interrupt Status
        uint32_t data_lane_1      : 1; ///< MIPI CSI Data Lane 1 Interrupt Status
        uint32_t                  : 6;
        uint32_t power_management : 1; ///< MIPI CSI Power Management Interrupt Status
        uint32_t short_packet     : 1; ///< MIPI CSI Generic Short Packet Interrupt Status
        uint32_t receive          : 1; ///< MIPI CSI Receive Interrupt Status
        uint32_t                  : 5;
        union
        {
            struct
            {
                uint32_t vc_00 : 1;    ///< MIPI CSI Virtual Channel 00 Interrupt Status
                uint32_t vc_01 : 1;    ///< MIPI CSI Virtual Channel 01 Interrupt Status
                uint32_t vc_02 : 1;    ///< MIPI CSI Virtual Channel 02 Interrupt Status
                uint32_t vc_03 : 1;    ///< MIPI CSI Virtual Channel 03 Interrupt Status
                uint32_t vc_04 : 1;    ///< MIPI CSI Virtual Channel 04 Interrupt Status
                uint32_t vc_05 : 1;    ///< MIPI CSI Virtual Channel 05 Interrupt Status
                uint32_t vc_06 : 1;    ///< MIPI CSI Virtual Channel 06 Interrupt Status
                uint32_t vc_07 : 1;    ///< MIPI CSI Virtual Channel 07 Interrupt Status
                uint32_t vc_08 : 1;    ///< MIPI CSI Virtual Channel 08 Interrupt Status
                uint32_t vc_09 : 1;    ///< MIPI CSI Virtual Channel 09 Interrupt Status
                uint32_t vc_10 : 1;    ///< MIPI CSI Virtual Channel 10 Interrupt Status
                uint32_t vc_11 : 1;    ///< MIPI CSI Virtual Channel 11 Interrupt Status
                uint32_t vc_12 : 1;    ///< MIPI CSI Virtual Channel 12 Interrupt Status
                uint32_t vc_13 : 1;    ///< MIPI CSI Virtual Channel 13 Interrupt Status
                uint32_t vc_14 : 1;    ///< MIPI CSI Virtual Channel 14 Interrupt Status
                uint32_t vc_15 : 1;    ///< MIPI CSI Virtual Channel 15 Interrupt Status
            }        bits;
            uint16_t mask;             ///< MIPI CSI Virtual Channel Interrupt Status Bit-Mask
        } virtual_channel;
    }        bits;
    uint32_t mask;
} mipi_csi_interrupt_status_t;

/** MIPI CSI Receive Status Type (RXST) */
typedef union st_mipi_csi_receive_status
{
    struct
    {
        union
        {
            struct
            {
                uint32_t vc_00 : 1;    ///< MIPI CSI Virtual Channel 00 Frame Active Receive Status
                uint32_t vc_01 : 1;    ///< MIPI CSI Virtual Channel 01 Frame Active Receive Status
                uint32_t vc_02 : 1;    ///< MIPI CSI Virtual Channel 02 Frame Active Receive Status
                uint32_t vc_03 : 1;    ///< MIPI CSI Virtual Channel 03 Frame Active Receive Status
                uint32_t vc_04 : 1;    ///< MIPI CSI Virtual Channel 04 Frame Active Receive Status
                uint32_t vc_05 : 1;    ///< MIPI CSI Virtual Channel 05 Frame Active Receive Status
                uint32_t vc_06 : 1;    ///< MIPI CSI Virtual Channel 06 Frame Active Receive Status
                uint32_t vc_07 : 1;    ///< MIPI CSI Virtual Channel 07 Frame Active Receive Status
                uint32_t vc_08 : 1;    ///< MIPI CSI Virtual Channel 08 Frame Active Receive Status
                uint32_t vc_09 : 1;    ///< MIPI CSI Virtual Channel 09 Frame Active Receive Status
                uint32_t vc_10 : 1;    ///< MIPI CSI Virtual Channel 10 Frame Active Receive Status
                uint32_t vc_11 : 1;    ///< MIPI CSI Virtual Channel 11 Frame Active Receive Status
                uint32_t vc_12 : 1;    ///< MIPI CSI Virtual Channel 12 Frame Active Receive Status
                uint32_t vc_13 : 1;    ///< MIPI CSI Virtual Channel 13 Frame Active Receive Status
                uint32_t vc_14 : 1;    ///< MIPI CSI Virtual Channel 14 Frame Active Receive Status
                uint32_t vc_15 : 1;    ///< MIPI CSI Virtual Channel 15 Frame Active Receive Status
            }        bits;
            uint16_t mask;             ///< MIPI CSI Virtual Channel Interrupt Status Bit-Mask
        }        virtual_channel;
        uint32_t receive_active : 1;   ///< MIPI CSI Receive Active Status
        uint32_t receive_detect : 1;   ///< MIPI CSI Receive Start Detect Status
    }        bits;
    uint32_t mask;
} mipi_csi_receive_status_t;

/** MIPI CSI Data Lane Status Type (DSLTn) */
typedef union st_mipi_csi_data_lane_status
{
    struct
    {
        uint32_t err_sot_hs    : 1;    ///< MIPI CSI Data Lane Start of Transmission (SoT) High Speed Error Detected
        uint32_t err_sot_sync  : 1;    ///< MIPI CSI Data Lane Start of Transmission (SoT) Synchronization High Speed Error Detected
        uint32_t err_control   : 1;    ///< MIPI CSI Data Lane Control Error Detected
        uint32_t err_escape    : 1;    ///< MIPI CSI Data Lane Escape Sequence Error Detected
        uint32_t               : 12;
        uint32_t ulps_exit     : 1;    ///< MIPI CSI Data Lane Exit From Ultra Low-Power State (ULPS) Detect
        uint32_t ulps_enter    : 1;    ///< MIPI CSI Data Lane Entry To Ultra Low-Power State (ULPS) Detect
        uint32_t               : 6;
        uint32_t escape_detect : 1;    ///< MIPI CSI Data Lane Ultra Low-Power State Escape Detect
        uint32_t               : 7;
    }        bits;
    uint32_t mask;
} mipi_csi_data_lane_status_t;

/** MIPI CSI Virtual Channel Status Type (VCSTm) */
typedef union st_mipi_csi_virtual_channel_status
{
    struct
    {
        uint32_t malformed             : 1; ///< MIPI CSI Virtual Channel Error Malformed Packet
        uint32_t err_ecc_2_bit         : 1; ///< MIPI CSI Virtual Channel Error ECC 2-bit (Double)
        uint32_t err_crc               : 1; ///< MIPI CSI Virtual Channel Error CRC
        uint32_t err_id                : 1; ///< MIPI CSI Virtual Channel Error ID
        uint32_t err_word_count        : 1; ///< MIPI CSI Virtual Channel Error Word Count
        uint32_t err_ecc_1_bit         : 1; ///< MIPI CSI Virtual Channel Error ECC 1-bit (Corrected)
        uint32_t ecc_no_error          : 1; ///< MIPI CSI Virtual Channel ECC No-Error
        uint32_t                       : 1;
        uint32_t err_frame_sync        : 1; ///< MIPI CSI Virtual Channel Error Frame Sync
        uint32_t err_frame_data        : 1; ///< MIPI CSI Virtual Channel Error Frame Data
        uint32_t                       : 6;
        uint32_t short_packet_overflow : 1; ///< MIPI CSI Virtual Channel Error Generic Short Packet FIFO Overflow
        uint32_t                       : 7;
        uint32_t frame_start           : 1; ///< MIPI CSI Virtual Channel Detect Frame Start
        uint32_t frame_end             : 1; ///< MIPI CSI Virtual Channel Detect Frame End
        uint32_t line_start            : 1; ///< MIPI CSI Virtual Channel Detect Line Start
        uint32_t line_end              : 1; ///< MIPI CSI Virtual Channel Detect Line End
        uint32_t eotp                  : 1; ///< MIPI CSI Virtual Channel Detect End of Transmission Short Packet (EoTp)
    }        bits;
    uint32_t mask;
} mipi_csi_virtual_channel_status_t;

/** MIPI CSI Power Status Type (PMST) */
typedef union st_mipi_csi_power_status
{
    struct
    {
        uint32_t stop_state_data_exit   : 1; ///< MIPI CSI Power Status Data Lane Stop State Exit Detect
        uint32_t stop_state_data_enter  : 1; ///< MIPI CSI Power Status Data Lane Stop State Entry Detect
        uint32_t stop_clock_state_exit  : 1; ///< MIPI CSI Power Status Clock Lane Stop State Exit Detect
        uint32_t stop_clock_state_enter : 1; ///< MIPI CSI Power Status Clock Lane Stop State Entry Detect
        uint32_t ulps_data_exit         : 1; ///< MIPI CSI Power Status Ultra Low-Power State (ULPS) Data Exit
        uint32_t ulps_data_enter        : 1; ///< MIPI CSI Power Status Ultra Low-Power State (ULPS) Data Enter
        uint32_t ulps_clock_exit        : 1; ///< MIPI CSI Power Status Ultra Low-Power State (ULPS) Clock Exit
        uint32_t ulps_clock_enter       : 1; ///< MIPI CSI Power Status Ultra Low-Power State (ULPS) Clock Enter
        uint32_t                        : 6;
        uint32_t clock_stop_state       : 1; ///< MIPI CSI Power Status Clock Stop State
        uint32_t clock_interted         : 1; ///< MIPI CSI Power Status Clock Inverted
        uint32_t data_lane_0_stop       : 1; ///< MIPI CSI Power Status Data Lane 0 Stop State
        uint32_t data_lane_1_stop       : 1; ///< MIPI CSI Power Status Data Lane 1 Stop State
        uint32_t                        : 6;
        uint32_t data_lane_0_ulps_state : 1; ///< MIPI CSI Power Status Ultra Low-Power State (ULPS) Data Lane 0 Escape State
        uint32_t data_lane_1_ulps_state : 1; ///< MIPI CSI Power Status Ultra Low-Power State (ULPS) Data Lane 0 Escape State
    }        bits;
    uint32_t mask;
} mipi_csi_power_status_t;

/** MIPI CSI Short Packet FIFO Type (GSST) */
typedef union st_mipi_csi_short_packet_fifo_status
{
    struct
    {
        uint32_t not_empty     : 1;    ///< MIPI CSI Generic Short Packet FIFO Not Empty Status
        uint32_t threshold_met : 1;    ///< MIPI CSI Generic Short Packet FIFO Contains Number of Packets Exceeds Threshold
        uint32_t               : 2;
        uint32_t overflow      : 1;    ///< MIPI CSI Generic Short Packet FIFO Overflow Status
        uint32_t               : 3;
        uint32_t packet_count  : 8;    ///< MIPI CSI Generic Short Packet FIFO Packet Count
        uint32_t clear         : 1;    ///< MIPI CSI Generic Short Packet FIFO Not Empty Status
        uint32_t disable       : 1;    ///< MIPI CSI Generic Short Packet FIFO Not Empty Status
    }        bits;
    uint32_t mask;
} mipi_csi_short_packet_fifo_status_t;

/** MIPI CSI Control Data */
typedef struct st_mipi_csi_ctrl_data
{
    /* (MCT0) */
    union
    {
        struct
        {
            uint32_t lane_count                : 4; ///< Number of lanes for operation
            uint32_t                           : 12;
            uint32_t zero_length_packet_output : 1; ///< Output Long Packet With Word-Count of Zero to VIN
            uint32_t err_frame_notify          : 1; ///< Notifies ErrFrameData when an ECC 2-bit error or a packet of less than 4 bytes is received between FS and FE
            uint32_t                           : 1;
            uint32_t reserved_packet_reception : 1; ///< Receive packets with a data type 0x39 to 0x3E, which are reserved in CSI-2 standard “Table 10 Data Type Classes”.
            uint32_t generic_rule_mode         : 1; ///< Output all data to VIN according to Generic CSI-2 Rule
            uint32_t                           : 3;
            uint32_t ecc_check_24_bits         : 1; ///< CSI-2 specification-compliant mode of ECC checking (0: 26-bit ECC Check, 1: 24-bit ECC Check)
            uint32_t descramble_enable         : 1; ///< Enable Descrambling
        }        control_0_bits;
        uint32_t control_0_mask;
    };

    /* (MCT2) */
    union
    {
        struct
        {
            uint32_t frrclk : 9;       ///< Frequency clock rate to determine packet reception end
            uint32_t        : 7;
            uint32_t frrskw : 9;       ///< Frequency clock rate to adjust data lane skew
        }        control_2_bits;
        uint32_t control_2_mask;
    };

    /* (GSCT) */
    union
    {
        struct
        {
            uint32_t threshold   : 7;  ///< Frequency clock rate to determine packet reception end
            uint32_t             : 9;
            uint32_t fifo_enable : 1;  ///< Frequency clock rate to adjust data lane skew
            uint32_t             : 15;
        }        short_packet_control_bits;
        uint32_t short_packet_control_mask;
    };
} mipi_csi_ctrl_data_t;

/** MIPI CSI IRQ Configuration structure */
typedef struct st_mipi_csi_irq_cfg
{
    uint8_t   ipl;                     ///< Interrupt priority
    IRQn_Type irq;                     ///< Interrupt vector number
} mipi_csi_irq_cfg_t;

/** MIPI CSI Interrupt control configuration */
typedef struct st_mipi_csi_interrupt_cfg
{
    mipi_csi_irq_cfg_t receive_cfg;          ///< Video Input Operation interrupt
    mipi_csi_irq_cfg_t data_lane_cfg;        ///< Data Lane interrupt
    mipi_csi_irq_cfg_t virtual_channel_cfg;  ///< Virtual Channel interrupt
    mipi_csi_irq_cfg_t power_management_cfg; ///< Power Management interrupt
    mipi_csi_irq_cfg_t short_packet_cfg;     ///< Short Packet interrupt

    /* (RXIE) */
    union
    {
        struct
        {
            uint32_t           : 17;
            uint32_t rx_detect : 1;    ///< Receive Detect Interrupt Enable
        }        receive_enable_bits;
        uint32_t receive_enable_mask;
    };

    /* (DLIE) */
    union
    {
        struct
        {
            uint32_t err_sot_hs_detect      : 1; ///< Start of Transmission Error Detect Interrupt
            uint32_t err_sot_sync_hs_detect : 1; ///< Start of Transmission Synchronization Error Detect Interrupt
            uint32_t err_control_detect     : 1; ///< Control Error Detect Interrupt
            uint32_t err_escape_detect      : 1; ///< Escape Sequence Error Detect Interrupt
            uint32_t                        : 12;
            uint32_t ulps_exit_detect       : 1; ///< ULPS Exit Detect Interrupt Enable Interrupt
            uint32_t ulps_enter_detect      : 1; ///< ULPS Enter Detect Interrupt Enable Interrupt
        }        data_lane_enable_bits[2];
        uint32_t data_lane_enable_mask[2];
    };

    /* (VCIE) */
    union
    {
        struct
        {
            uint32_t malformed_packet_detect           : 1; ///< Error Malformed Packet Detect Interrupt
            uint32_t error_ecc_2_bit_detect            : 1; ///< Error ECC 2-bit Detect Interrupt
            uint32_t error_crc_detect                  : 1; ///< Error CRC Packet Detect Interrupt
            uint32_t error_id_detect                   : 1; ///< Error ID Packet Detect Interrupt
            uint32_t error_word_count_detect           : 1; ///< Error Word Count Packet Detect Interrupt
            uint32_t error_ecc_1_bit_detect            : 1; ///< Error ECC 1-bit (corrected) Packet Detect Interrupt
            uint32_t ecc_no_error_detect               : 1; ///< ECC No-Error Packet Detect Interrupt
            uint32_t                                   : 1;
            uint32_t error_frame_sync_detect           : 1; ///< Error Frame Sync Detect Interrupt
            uint32_t error_frame_data_detect           : 1; ///< Error Frame Data Detect Interrupt
            uint32_t                                   : 6;
            uint32_t short_packet_fifo_overflow_detect : 1; ///< Generic Short Packet FIFO Overflow Detect Interrupt
            uint32_t                                   : 7;
            uint32_t frame_start_detect                : 1; ///< Frame Start Packet Detect Interrupt
            uint32_t frame_end_detect                  : 1; ///< Frame End Packet Detect Interrupt
            uint32_t line_start_detect                 : 1; ///< Line Start Packet Detect Interrupt
            uint32_t line_end_detect                   : 1; ///< Line End Packet Detect Interrupt
            uint32_t eotp_detect                       : 1; ///< End of Transmission Packet (EoTp) Detect Interrupt
        }        virtual_channel_enable_bits[16];
        uint32_t virtual_channel_enable_mask[16];
    };

    /* (PMIE) */
    union
    {
        struct
        {
            uint32_t data_stop_state_exit   : 1; ///< Power Management Data Lane Stop State Exit Detect Interrupt
            uint32_t data_stop_state_enter  : 1; ///< Power Management Data Lane Stop State Enter Detect Interrupt
            uint32_t clock_stop_state_exit  : 1; ///< Power Management Clock Lane Stop State Exit Detect Interrupt
            uint32_t clock_stop_state_enter : 1; ///< Power Management Clock Lane Stop State Enter Detect Interrupt
            uint32_t data_ulps_exit         : 1; ///< Power Management Data Lane ULPS Exit Detect Interrupt
            uint32_t data_ulps_enter        : 1; ///< Power Management Data Lane ULPS Enter Detect Interrupt
            uint32_t clock_ulps_exit        : 1; ///< Power Management Clock Lane ULPS Exit Detect Interrupt
            uint32_t clock_ulps_enter       : 1; ///< Power Management Clock Lane ULPS Enter Detect Interrupt
            uint32_t                        : 24;
        }        power_management_enable_bits;
        uint32_t power_management_enable_mask;
    };

    /* (GSIE) */
    union
    {
        struct
        {
            uint32_t fifo_not_empty          : 1; ///< Generic Short Packet FIFO Not Empty Detect
            uint32_t fifo_threshold_exceeded : 1; ///< Generic Short Packet FIFO Threshold Exceeded Detect
            uint32_t                         : 2;
            uint32_t fifo_overflow           : 1; ///< Generic Short Packet FIFO Overflow Detect
            uint32_t                         : 27;
        }        short_packet_enable_bits;
        uint32_t short_packet_enable_mask;
    };
} mipi_csi_interrupt_cfg_t;

typedef struct st_mipi_csi_option_data
{
    /* (EPCT) */
    union
    {
        struct
        {
            uint32_t long_packet_spacers : 15; ///< Specify the number of spacers/lanes inserted after a long packet.
            uint32_t epd_option          : 1;  ///< Efficient Packet Delimiter (EPD) Option Select (Must be 1 when EPDEN is 1)
            uint32_t epd_short_spacers   : 15; ///< EPD Short Packet Spacers
            uint32_t epd_enable          : 1;  ///< Enable Efficient Packet Delimiter (EPD) Operation
        }        epd_option_0_bits;
        uint32_t epd_option_0_mask;
    };

    /* (EMCT) */
    union
    {
        struct
        {
            uint32_t                                                    : 4;
            mipi_csi_variable_length_spacer_t variable_spacer_insertion : 2; ///< Enable Variable length spacer insertion when EPD Option 2 is enabled.
            uint32_t eotpen                                             : 1; ///< Enables (EOTP) when EPD Option 2 is enabled
            uint32_t                                                    : 25;
        }        epd_option_1_bits;
        uint32_t epd_option_1_mask;
    };

    mipi_csi_rx_data_enable_t data_type_enable : 64; ///< MIPI CSI Data Type Enable
} mipi_csi_option_data_t;

/* @} (end addtogroup MIPI_CSI) */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif
