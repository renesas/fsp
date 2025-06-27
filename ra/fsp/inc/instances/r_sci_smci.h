/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_SCI_SMCI_H
#define R_SCI_SMCI_H

/*******************************************************************************************************************//**
 * @addtogroup SCI_SMCI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_smci_api.h"
#include "r_sci_smci_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** SMCI instance control block. */
typedef struct st_sci_smci_instance_ctrl
{
    /* Used to determine if the channel is configured. */
    uint32_t open;

    /* Source buffer pointer used to fill hardware TDR from transmit ISR. */
    uint8_t const * p_tx_src;

    /* Size of source buffer pointer used to fill hardware FIFO from transmit ISR. */
    uint32_t tx_src_bytes;

    /* Destination buffer pointer used for receiving data. */
    uint8_t * p_rx_dest;

    /* Size of destination buffer pointer used for receiving data. */
    uint32_t rx_dest_bytes;

    /* Number of bytes received */
    uint32_t rx_bytes_received;

    /* Pointer to the configuration block. */
    smci_cfg_t const * p_cfg;

    /* State of this instance of the SMCI */
    smci_state_t smci_state;

    /* Base register for this channel */
    R_SCI0_Type * p_reg;

    void (* p_callback)(smci_callback_args_t *); // Pointer to callback that is called when a smci_event_t occurs.
    smci_callback_args_t * p_callback_memory;    // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.

    /* Pointer to context to be passed into callback function */
    void * p_context;
} sci_smci_instance_ctrl_t;

/** Register settings to achieve a desired baud rate in Smart Card mode */
typedef struct st_smci_baud_setting_t
{
    uint32_t computed_baud_rate;
    union
    {
        uint8_t smr_smci_clock_bits;

        struct st_smr_smci_clock_bits_b
        {
            uint8_t cks   : 2;         ///< Clock divisor Select
            uint8_t bcp01 : 2;         ///< Base Clock Pulse
            uint8_t       : 1;
            uint8_t       : 1;
            uint8_t       : 1;
            uint8_t       : 1;
        } smr_smci_clock_bits_b;
    };

    uint8_t scmr_bcp2 : 1;             ///< BCP2 setting in Smart Card Mode Register
    uint8_t brr;                       ///< Bit Rate Register setting
} smci_baud_setting_t;

/** SMCI on SCI device Configuration */
typedef struct st_sci_smci_extended_cfg
{
    smci_baud_setting_t * p_smci_baud_setting; ///< Register settings for a desired baud rate.
} sci_smci_extended_cfg_t;

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * sci_smci_prv_ns_callback)(smci_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile sci_smci_prv_ns_callback)(smci_callback_args_t * p_args);
#endif

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const smci_api_t g_smci_on_sci;

/** @endcond */
fsp_err_t R_SCI_SMCI_Open(smci_ctrl_t * const p_api_ctrl, smci_cfg_t const * const p_cfg);
fsp_err_t R_SCI_SMCI_Write(smci_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes);
fsp_err_t R_SCI_SMCI_Read(smci_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t R_SCI_SMCI_TransferModeSet(smci_ctrl_t * const                p_api_ctrl,
                                     smci_transfer_mode_t const * const p_transfer_mode_params);
fsp_err_t R_SCI_SMCI_BaudCalculate(smci_speed_params_t const * const p_speed_params,
                                   uint32_t                          baud_rate_error_x_1000,
                                   void * const                      p_baud_setting);

fsp_err_t R_SCI_SMCI_BaudSet(smci_ctrl_t * const p_api_ctrl, void const * const p_baud_setting);
fsp_err_t R_SCI_SMCI_StatusGet(smci_ctrl_t * const p_api_ctrl, smci_status_t * const p_status);
fsp_err_t R_SCI_SMCI_ClockControl(smci_ctrl_t * const p_api_ctrl, bool clock_enable);
fsp_err_t R_SCI_SMCI_CallbackSet(smci_ctrl_t * const          p_api_ctrl,
                                 void (                     * p_callback)(smci_callback_args_t *),
                                 void * const                 p_context,
                                 smci_callback_args_t * const p_callback_memory);
fsp_err_t R_SCI_SMCI_Close(smci_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end addtogroup SCI_SMCI)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_SCI_SMCI_H */
