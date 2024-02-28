/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef R_SCI_B_LIN_H
#define R_SCI_B_LIN_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_sci_b_lin_cfg.h"
#include "r_lin_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup SCI_B_LIN
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Register settings for configuring the LIN break field timer */
typedef struct st_sci_b_lin_timer_setting
{
    uint8_t       : 6;
    uint8_t  tcss : 2;                 ///< LIN timer count clock source selection
    uint16_t bflw;                     ///< Break field length setting (break field length is (bflw + 1) * clock of the timer)
} sci_b_lin_timer_setting_t;

/**  Register settings for achieving a desired baud rate. */
typedef struct st_sci_b_lin_baud_setting
{
    union
    {
        uint32_t baudrate_bits;

        struct
        {
            uint32_t      : 5;
            uint32_t abcs : 1;         ///< Asynchronous Mode Base Clock Select
            uint32_t      : 2;
            uint32_t brr  : 8;         ///< Bit Rate Register setting
            uint32_t      : 4;
            uint32_t cks  : 2;         ///< CKS value to get divisor (CKS = n)
            uint32_t      : 10;
        } baudrate_bits_b;
    };

    sci_b_lin_timer_setting_t timer_setting; ///< Break field timer settings associated with this baud rate
} sci_b_lin_baud_setting_t;

/** Parameters for configuring the ID filter settings */
typedef struct st_sci_b_lin_id_filter_setting
{
    /** Bit mask applied before comparing the received PID to the compare data.
     * Selects which bits of the selected compare data must match.*/
    uint8_t compare_data_mask;

    /** Priority/primary compare data */
    uint8_t priority_compare_data;

    /**Secondary compare data */
    uint8_t secondary_compare_data;

    /** Specify ONE of bits 0 to 7 of Control Field 1 as the priority interrupt bit.
     * 0 is bit 0 of the PID, 1 is bit 1 of the PID, and so on.*/
    uint8_t priority_interrupt_bit_select : 3;

    /** Set to 1 to enable the priority interrupt bit filter specified by priority_interrupt_bit_select,
     * 0 to disable. When this bit is 1, regardless of the compare_data_select setting value, the bit
     * specified by priority_interrupt_bit_select is compared  with the priority/primary comparison data
     * for Control Field 1 (priority_compare_data).*/
    uint8_t priority_interrupt_enable : 1;

    /** Select the compare data for Control Field 1 (priority, secondary, or both).
     * See @ref sci_b_lin_compare_data_select_t*/
    uint8_t compare_data_select : 2;
    uint8_t                     : 2;
} sci_b_lin_id_filter_setting_t;

/** Priority interrupt bit options for ID filtering. */
typedef enum e_sci_b_lin_priority_interrupt_bit
{
    SCI_B_LIN_PRIORITY_INTERRUPT_BIT_DISABLE = 0, ///< Disable the priority interrupt bit
    SCI_B_LIN_PRIORITY_INTERRUPT_BIT_ENABLE  = 1, ///< Enable the priority interrupt bit
} sci_b_lin_priority_interrupt_bit_t;

/** Compare Data Select options for ID filtering. */
typedef enum e_sci_b_lin_compare_data_select
{
    SCI_B_LIN_COMPARE_DATA_SELECT_PRIORITY  = 0, ///< Select the priority/primary compare data filter as the compare data
    SCI_B_LIN_COMPARE_DATA_SELECT_SECONDARY = 1, ///< Select the secondary compare data filter as the compare data
    SCI_B_LIN_COMPARE_DATA_SELECT_BOTH      = 2, ///< Select both the priority/primary compare data filter and the secondary compare data filter as the compare data. The priority filter will be checked first.
} sci_b_lin_compare_data_select_t;

/** Source clock selection options for SCI. */
typedef enum e_sci_b_lin_clock_source
{
    /* MCUs have either SCISPICLK or SCICLK, but not both */
    SCI_B_LIN_CLOCK_SOURCE_SCISPICLK = 0U,                               ///< SCISPI clock source
    SCI_B_LIN_CLOCK_SOURCE_SCICLK    = SCI_B_LIN_CLOCK_SOURCE_SCISPICLK, ///< SCI clock source
    SCI_B_LIN_CLOCK_SOURCE_PCLK      = 1U,                               ///< PCLK source
} sci_b_lin_clock_source_t;

/** Break field delimiter configuration. */
typedef enum e_sci_b_lin_break_delimiter_bits
{
    SCI_B_LIN_BREAK_DELIMITER_BITS_1 = 0U, ///< 1-bit recessive break field delimiter
    SCI_B_LIN_BREAK_DELIMITER_BITS_2 = 1U, ///< 2-bit recessive break field delimiter
} sci_b_lin_break_delimiter_bits_t;

/** LIN timer configuration, used for break field generation and detection. */
typedef enum e_sci_b_lin_timer_divider
{
    SCI_B_LIN_TIMER_DIV_4  = 1U,       ///< LIN timer frequency is TCLK/4
    SCI_B_LIN_TIMER_DIV_16 = 2U,       ///< LIN timer frequency is TCLK/16
    SCI_B_LIN_TIMER_DIV_64 = 3U,       ///< LIN timer frequency is TCLK/64
} sci_b_lin_timer_divider_t;

/** Auto synchronization setting. */
typedef enum e_sci_b_lin_synchronization
{
    SCI_B_LIN_AUTO_SYNCHRONIZATION_DISABLE = 0, ///< Disable auto synchronization during sync byte reception.
    SCI_B_LIN_AUTO_SYNCHRONIZATION_ENABLE  = 1, ///< Enable auto synchronization during sync byte reception.
} sci_b_lin_synchronization_t;

/** Noise cancellation configuration. */
typedef enum e_sci_b_lin_noise_cancellation
{
    SCI_B_LIN_NOISE_CANCELLATION_DISABLE = 0U, ///< Disable noise cancellation
    SCI_B_LIN_NOISE_CANCELLATION_ENABLE  = 1U, ///< Enable noise cancellation
} sci_b_lin_noise_cancellation_t;

/**  Bus conflict detection enable. */
typedef enum e_sci_b_lin_bus_conflict_detection
{
    SCI_B_LIN_BUS_CONFLICT_DETECTION_DISABLE = 0U, ///< Disable bus conflict detection
    SCI_B_LIN_BUS_CONFLICT_DETECTION_ENABLE  = 1U, ///< Enable bus conflict detection
} e_sci_b_lin_bus_conflict_detection_t;

/** Bus conflict detection clock selection.
 * Base clock: 1/16 period of 1 bit period when CCR2.ABCS = 0, 1/8 period of 1 bit period when CCR2.ABCS = 1
 **/
typedef enum e_sci_b_lin_bus_conflict_clock
{
    SCI_B_LIN_BUS_CONFLICT_DETECTION_BASE_CLOCK_DIV_1 = 0U, ///< Bus conflict detection clock is base clock
    SCI_B_LIN_BUS_CONFLICT_DETECTION_BASE_CLOCK_DIV_2 = 1U, ///< Bus conflict detection clock is base clock/2
    SCI_B_LIN_BUS_CONFLICT_DETECTION_BASE_CLOCK_DIV_4 = 2U, ///< Bus conflict detection clock is base clock/4. Setting prohibited when CCR2.ABCS = 1.
} sci_b_lin_bus_conflict_clock_t;

/** Parameters for baud and timer setting calculation */
typedef struct st_sci_b_lin_baud_params
{
    uint32_t                       baudrate;           ///< Desired baudrate
    sci_b_lin_clock_source_t       clock_source;       ///< Peripheral clock source
    sci_b_lin_bus_conflict_clock_t bus_conflict_clock; ///< Bus collision clock divider.
    uint16_t                       break_bits;         ///< Master mode: Number of break field bits to transmit. Slave mode: Number of break field threshold bits.
} sci_b_lin_baud_params_t;

/** SCI B LIN extended configuration */
typedef struct st_sci_b_lin_extended_cfg
{
    /* Boolean settings */
    union
    {
        uint8_t sci_b_settings;

        struct
        {
            uint8_t clock_source           : 1; ///< The source clock for the baud-rate generator.
            uint8_t noise_cancel           : 1; ///< Noise cancellation setting. See @ref sci_b_lin_noise_cancellation_t
            uint8_t break_delimiter        : 1; ///< Break delimeter length setting (1 or 2 bits recessive). See @ref sci_b_lin_break_delimiter_bits_t
            uint8_t bus_conflict_detection : 1; ///< Bus conflict detection cancellation setting. See @ref e_sci_b_lin_bus_conflict_detection_t
            uint8_t bus_conflict_clock     : 2; ///< Bus conflict detection clock setting. See @ref sci_b_lin_bus_conflict_clock_t
            uint8_t auto_synchronization   : 1; ///< Auto synchronization setting. See @ref sci_b_lin_synchronization_t.
            uint8_t                        : 1;
        } sci_b_settings_b;
    };

    sci_b_lin_baud_setting_t      baud_setting;   ///< Register settings for a desired baud rate.
    sci_b_lin_id_filter_setting_t filter_setting; ///< ID filter setting

    /* Interrupt settings */
    IRQn_Type bfd_irq;                            ///< Break field detect IRQ number
    IRQn_Type aed_irq;                            ///< Active edge detect IRQ number
    uint8_t   bfd_ipl;                            ///< Break field detect interrupt priority
    uint8_t   aed_ipl;                            ///< Active edge detect interrupt priority
    uint16_t  break_bits;                         ///< Master mode: Number of break field bits to transmit. Slave mode: Number of break field threshold bits.
} sci_b_lin_extended_cfg_t;

/* LIN Instance Control Block. DO NOT INITIALIZE.  */
typedef struct st_sci_b_lin_instance_ctrl
{
    uint32_t          open;                     // Used to determine if the channel is configured
    lin_cfg_t const * p_cfg;                    // Pointer to the configuration block
    R_SCI_B0_Type   * p_reg;                    // Base register for this channel
    void (* p_callback)(lin_callback_args_t *); // Pointer to callback
    lin_callback_args_t * p_callback_memory;    // Pointer to optional working memory
    void const          * p_context;            // Pointer to context to be passed into callback function
    lin_event_t           event;                // Used to distinguish between start frame and information frame transmission completion events
    uint8_t             * p_information;        // Information frame buffer pointer (used for both transmission and reception)
    uint32_t              sync_bits_sum;        // Sum of sync bit durations when auto synchronization is used
    uint32_t              timer_freq_hz;        // LIN timer frequency (Hz) used for break field generation/reception and auto synchronization
    uint8_t               tx_src_bytes;         // Transmit buffer length, in bytes
    uint8_t               last_tx_byte;         // Last byte of data when transmitting. When transmitting start frame, contains PID. When transmitting information frame, contains the checksum.
    uint8_t               rx_bytes_expected;    // Tracks number of frame bytes expected in the transfer (including checksum)
    uint8_t               rx_bytes_received;    // Tracks number of information frame bytes received in the transfer (excluding checksum)
    uint8_t               rx_checksum;          // Stores computed checksum as bytes come in during reception. Once checksum byte is received, stores received checksum
    uint8_t               validate_checksum;    // Indicates whether checksum should be validated by driver
    uint8_t               last_pid;             // Last PID transmitted or received
    uint8_t               sync_bits_received;   // Number of sync bits successfully measured so far during auto synchronization
} sci_b_lin_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const lin_api_t g_lin_on_sci_b;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_Open(lin_ctrl_t * const p_api_ctrl, lin_cfg_t const * const p_cfg);
fsp_err_t R_SCI_B_LIN_StartFrameWrite(lin_ctrl_t * const p_api_ctrl, uint8_t const id);
fsp_err_t R_SCI_B_LIN_InformationFrameWrite(lin_ctrl_t * const                  p_api_ctrl,
                                            const lin_transfer_params_t * const p_transfer_params);
fsp_err_t R_SCI_B_LIN_InformationFrameRead(lin_ctrl_t * const            p_api_ctrl,
                                           lin_transfer_params_t * const p_transfer_params);
fsp_err_t R_SCI_B_LIN_CommunicationAbort(lin_ctrl_t * const p_api_ctrl);
fsp_err_t R_SCI_B_LIN_CallbackSet(lin_ctrl_t * const          p_api_ctrl,
                                  void (                    * p_callback)(lin_callback_args_t *),
                                  void const * const          p_context,
                                  lin_callback_args_t * const p_callback_memory);
fsp_err_t R_SCI_B_LIN_IdFilterSet(lin_ctrl_t * const p_api_ctrl, sci_b_lin_id_filter_setting_t const * const p_config);
fsp_err_t R_SCI_B_LIN_IdFilterGet(lin_ctrl_t * const p_api_ctrl, sci_b_lin_id_filter_setting_t * const p_config);
fsp_err_t R_SCI_B_LIN_Close(lin_ctrl_t * const p_api_ctrl);
fsp_err_t R_SCI_B_LIN_BaudCalculate(sci_b_lin_baud_params_t const * const p_baud_params,
                                    sci_b_lin_baud_setting_t * const      p_baud_setting);

/*******************************************************************************************************************//**
 * @} (end addtogroup SCI_B_LIN)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
