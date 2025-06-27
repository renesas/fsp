/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_SCI_LIN_H
#define R_SCI_LIN_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_sci_lin_cfg.h"
#include "r_lin_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup SCI_LIN
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Priority interrupt bit options for ID filtering. */
typedef enum e_sci_lin_priority_interrupt_bit
{
    SCI_LIN_PRIORITY_INTERRUPT_BIT_DISABLE = 0, ///< Disable the priority interrupt bit
    SCI_LIN_PRIORITY_INTERRUPT_BIT_ENABLE  = 1, ///< Enable the priority interrupt bit
} sci_lin_priority_interrupt_bit_t;

/** Compare Data Select options for ID filtering. */
typedef enum e_sci_lin_compare_data_select
{
    SCI_LIN_COMPARE_DATA_SELECT_PRIORITY  = 0, ///< Select the priority/primary compare data filter as the compare data
    SCI_LIN_COMPARE_DATA_SELECT_SECONDARY = 1, ///< Select the secondary compare data filter as the compare data
    SCI_LIN_COMPARE_DATA_SELECT_BOTH      = 2, ///< Select both the priority/primary compare data filter and the secondary compare data filter as the compare data. The priority filter will be checked first.
} sci_lin_compare_data_select_t;

/** LIN timer divider selection. */
typedef enum e_sci_lin_timer_divider
{
    SCI_LIN_TIMER_DIV_1   = 0U,        ///< LIN timer frequency is PCLK/1
    SCI_LIN_TIMER_DIV_2   = 1U,        ///< LIN timer frequency is PCLK/2
    SCI_LIN_TIMER_DIV_4   = 2U,        ///< LIN timer frequency is PCLK/4
    SCI_LIN_TIMER_DIV_8   = 3U,        ///< LIN timer frequency is PCLK/8
    SCI_LIN_TIMER_DIV_16  = 4U,        ///< LIN timer frequency is PCLK/16
    SCI_LIN_TIMER_DIV_32  = 5U,        ///< LIN timer frequency is PCLK/32
    SCI_LIN_TIMER_DIV_64  = 6U,        ///< LIN timer frequency is PCLK/64
    SCI_LIN_TIMER_DIV_128 = 7U,        ///< LIN timer frequency is PCLK/128
} sci_lin_timer_divider_t;

/** Digital filter configuration. */
typedef enum e_sci_lin_digital_filter_clock
{
    SCI_LIN_DIGITAL_FILTER_CLOCK_DISABLED     = 0U, ///< Filter is disabled
    SCI_LIN_DIGITAL_FILTER_CLOCK_SCI_BASE_CLK = 1U, ///< Filter clock is SCI base clock.
    SCI_LIN_DIGITAL_FILTER_CLOCK_PCLK_DIV_8   = 2U, ///< Filter clock is PCLK/8
    SCI_LIN_DIGITAL_FILTER_CLOCK_PCLK_DIV_16  = 3U, ///< Filter clock is PCLK/16
    SCI_LIN_DIGITAL_FILTER_CLOCK_PCLK_DIV_32  = 4U, ///< Filter clock is PCLK/32
    SCI_LIN_DIGITAL_FILTER_CLOCK_PCLK_DIV_64  = 5U, ///< Filter clock is PCLK/64
    SCI_LIN_DIGITAL_FILTER_CLOCK_PCLK_DIV_128 = 6U, ///< Filter clock is PCLK/128
} sci_lin_digital_filter_clock_t;

/** Bus conflict detection clock selection.
 * The period of the SCI base clock is 1/16 of a single bit period when the SCIn.SEMR.ABCS is 0,
 * and 1/8 of a single bit period when the SCIn.SEMR.ABCS is 1.
 **/
typedef enum e_sci_lin_bus_conflict_clock
{
    SCI_LIN_BUS_CONFLICT_CLOCK_DIV_1 = 0U, ///< Bus conflict detection clock is base clock
    SCI_LIN_BUS_CONFLICT_CLOCK_DIV_2 = 1U, ///< Bus conflict detection clock is base clock/2
    SCI_LIN_BUS_CONFLICT_CLOCK_DIV_4 = 2U, ///< Bus conflict detection clock is base clock/4.
} sci_lin_bus_conflict_clock_t;

/** Asynchronous Mode Base Clock Select.
 * The period of the SCI base clock is 1/16 of a single bit period when the SCIn.SEMR.ABCS is 0,
 * and 1/8 of a single bit period when the SCIn.SEMR.ABCS is 1.
 **/
typedef enum e_sci_lin_base_clock
{
    SCI_LIN_BASE_CLOCK_16 = 0U,        ///< Select 16 base clock cycles for 1-bit period
    SCI_LIN_BASE_CLOCK_8  = 1U,        ///< Select 8 base clock cycles for 1-bit period
} sci_lin_base_clock_t;

/** Register settings for configuring the LIN timer */
typedef struct st_sci_lin_timer_setting
{
    uint8_t tcss;                      ///< LIN timer count clock source selection
    uint8_t break_field_tpre;          ///< Break field prescaler
    uint8_t break_field_tcnt;          ///< Break field count value
    uint8_t delimiter_tpre;            ///< Break delimiter prescaler
    uint8_t delimiter_tcnt;            ///< Break delimiter count value
} sci_lin_timer_setting_t;

/** Register settings for achieving a desired baud rate. */
typedef struct st_sci_lin_baud_setting
{
    sci_lin_timer_setting_t timer_setting; ///< Break field timer settings associated with this baud rate
    union
    {
        uint8_t semr_baudrate_bits;

        struct
        {
            uint8_t       : 3;
            uint8_t abcse : 1;         ///< Asynchronous Mode Extended Base Clock Select
            uint8_t abcs  : 1;         ///< Asynchronous Mode Base Clock Select
            uint8_t       : 1;
            uint8_t bgdm  : 1;         ///< Baud Rate Generator Double-Speed Mode Select
            uint8_t       : 1;
        } semr_baudrate_bits_b;
    };
    uint8_t brr;                       ///< Bit Rate Register setting
    uint8_t cks : 2;                   ///< CKS value to get divisor
} sci_lin_baud_setting_t;

/** Parameters for configuring the ID filter settings */
typedef struct st_sci_lin_id_filter_setting
{
    /** Bit mask applied before comparing the received PID to the compare data.
     * Selects which bits of the selected compare data must match.*/
    uint8_t compare_data_mask;

    /** Primary compare data */
    uint8_t primary_compare_data;

    /** Secondary compare data */
    uint8_t secondary_compare_data;

    /** Specify ONE of bits 0 to 7 of Control Field 1 as the priority interrupt bit.
     * 0 is bit 0 of the PID, 1 is bit 1 of the PID, and so on.*/
    uint8_t priority_interrupt_bit_select : 3;

    /** Set to 1 to enable the priority interrupt bit filter specified by priority_interrupt_bit_select,
     * 0 to disable. When this bit is 1, regardless of the compare_data_select setting value, the bit
     * specified by priority_interrupt_bit_select is compared with the Primary comparison data
     * for Control Field 1 (primary_compare_data).*/
    uint8_t priority_interrupt_enable : 1;

    /** Select the compare data for Control Field 1 (priority, secondary, or both).
     * See @ref sci_lin_compare_data_select_t*/
    uint8_t compare_data_select : 2;
    uint8_t                     : 2;
} sci_lin_id_filter_setting_t;

/** Parameters for baud and timer setting calculation */
typedef struct st_sci_lin_baud_params
{
    uint32_t             baudrate;                  ///< Desired baudrate
    uint16_t             break_bits;                ///< Master mode: Number of break field bits to transmit. Slave mode: Number of break field threshold bits.
    uint8_t              delimiter_bits;            ///< Break delimeter length setting (at least 1 nominal bit time long).
    sci_lin_base_clock_t base_clock_cycles_per_bit; ///< Number of base clock cycles for 1-bit period.
} sci_lin_baud_params_t;

/** SCI LIN extended configuration */
typedef struct st_sci_lin_extended_cfg
{
    sci_lin_digital_filter_clock_t digital_filter_clock; ///< Digital filter setting. See @ref sci_lin_digital_filter_clock_t
    sci_lin_bus_conflict_clock_t   bus_conflict_clock;   ///< Bus conflict detection clock setting. See @ref sci_lin_bus_conflict_clock_t
    uint16_t                    break_bits;              ///< Master mode: Number of break field bits to transmit. Slave mode: Number of break field threshold bits.
    uint8_t                     delimiter_bits;          ///< Break delimeter length setting (at least 1 nominal bit time long).
    sci_lin_baud_setting_t      baud_setting;            ///< Register settings for a desired baud rate.
    sci_lin_id_filter_setting_t filter_setting;          ///< ID filter setting

    /* Interrupt settings */
    IRQn_Type scix0_irq;                                 ///< Break field low width IRQ number
    IRQn_Type scix1_irq;                                 ///< Control field 0-1 match / Priority interrupt bit detect IRQ number
    IRQn_Type scix2_irq;                                 ///< Bus collision detect IRQ number
    IRQn_Type rxi_irq;                                   ///< Receive interrupt IRQ number
    IRQn_Type txi_irq;                                   ///< Transmit interrupt IRQ number
    IRQn_Type tei_irq;                                   ///< Transmit end interrupt IRQ number
    IRQn_Type eri_irq;                                   ///< Error interrupt IRQ number
    uint8_t   scix0_ipl;                                 ///< Break field low width interrupt priority
    uint8_t   scix1_ipl;                                 ///< Control field 0-1 match / Priority interrupt bit detect interrupt priority
    uint8_t   scix2_ipl;                                 ///< Bus collision detect interrupt priority
    uint8_t   rxi_ipl;                                   ///< Receive interrupt priority
    uint8_t   txi_ipl;                                   ///< Transmit interrupt priority
    uint8_t   tei_ipl;                                   ///< Transmit end interrupt priority
    uint8_t   eri_ipl;                                   ///< Error interrupt priority
} sci_lin_extended_cfg_t;

/** LIN Instance Control Block. DO NOT INITIALIZE. */
typedef struct st_sci_lin_instance_ctrl
{
    uint32_t          open;                     // Used to determine if the channel is configured
    lin_cfg_t const * p_cfg;                    // Pointer to the configuration block
    R_SCI0_Type     * p_reg;                    // Base register for this channel
    void (* p_callback)(lin_callback_args_t *); // Pointer to callback
    lin_callback_args_t * p_callback_memory;    // Pointer to optional working memory
    void                * p_context;            // Pointer to context to be passed into callback function
    lin_event_t           event;                // Used to distinguish between header and data transmission completion events
    uint8_t             * p_data;               // Information frame buffer pointer (used for both transmission and reception)
    uint8_t               tx_src_bytes;         // Transmit buffer length, in bytes
    uint8_t               tx_header_bytes;      // Tracks number of header bytes transmitted
    uint8_t               rx_bytes_expected;    // Tracks number of frame bytes expected in the transfer (including checksum)
    uint8_t               rx_bytes_received;    // Tracks number of information frame bytes received in the transfer (excluding checksum)
    uint8_t               checksum;             // Stores computed checksum as bytes come in during reception. Once checksum byte is received, stores received checksum
    uint8_t               validate_checksum;    // Indicates whether checksum should be validated by driver
    uint8_t               last_pid;             // Last PID transmitted or received
} sci_lin_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const lin_api_t g_lin_on_sci;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_SCI_LIN_Open(lin_ctrl_t * const p_api_ctrl, lin_cfg_t const * const p_cfg);
fsp_err_t R_SCI_LIN_Write(lin_ctrl_t * const p_api_ctrl, const lin_transfer_params_t * const p_transfer_params);
fsp_err_t R_SCI_LIN_Read(lin_ctrl_t * const p_api_ctrl, lin_transfer_params_t * const p_transfer_params);
fsp_err_t R_SCI_LIN_CommunicationAbort(lin_ctrl_t * const p_api_ctrl);
fsp_err_t R_SCI_LIN_CallbackSet(lin_ctrl_t * const          p_api_ctrl,
                                void (                    * p_callback)(lin_callback_args_t *),
                                void * const                p_context,
                                lin_callback_args_t * const p_callback_memory);
fsp_err_t R_SCI_LIN_IdFilterSet(lin_ctrl_t * const p_api_ctrl, sci_lin_id_filter_setting_t const * const p_config);
fsp_err_t R_SCI_LIN_IdFilterGet(lin_ctrl_t * const p_api_ctrl, sci_lin_id_filter_setting_t * const p_config);
fsp_err_t R_SCI_LIN_Close(lin_ctrl_t * const p_api_ctrl);
fsp_err_t R_SCI_LIN_BaudCalculate(sci_lin_baud_params_t const * const p_baud_params,
                                  sci_lin_baud_setting_t * const      p_baud_setting);
fsp_err_t R_SCI_LIN_WakeupSend(lin_ctrl_t * const p_api_ctrl);
fsp_err_t R_SCI_LIN_SleepEnter(lin_ctrl_t * const p_api_ctrl);
fsp_err_t R_SCI_LIN_SleepExit(lin_ctrl_t * const p_api_ctrl);
fsp_err_t R_SCI_LIN_StartFrameWrite(lin_ctrl_t * const p_api_ctrl, uint8_t const id);             // [DEPRECATED]
fsp_err_t R_SCI_LIN_InformationFrameWrite(lin_ctrl_t * const                  p_api_ctrl,
                                          const lin_transfer_params_t * const p_transfer_params); // [DEPRECATED]
fsp_err_t R_SCI_LIN_InformationFrameRead(lin_ctrl_t * const            p_api_ctrl,
                                         lin_transfer_params_t * const p_transfer_params);        // [DEPRECATED]

/*******************************************************************************************************************//**
 * @} (end addtogroup SCI_LIN)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
