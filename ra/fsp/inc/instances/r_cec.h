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

#ifndef R_CEC_H
#define R_CEC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_cec_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup CEC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define CEC_CECFC_MASK_ALL    (uint8_t) (R_CEC_CECFC_OCTRG_Msk |   \
                                         R_CEC_CECFC_UCTRG_Msk |   \
                                         R_CEC_CECFC_ACKCTRG_Msk | \
                                         R_CEC_CECFC_TCTRG_Msk |   \
                                         R_CEC_CECFC_TXCTRG_Msk |  \
                                         R_CEC_CECFC_ACTRG_Msk |   \
                                         R_CEC_CECFC_BLCTRG_Msk)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* CEC Instance Control Block   */
typedef struct st_cec_instance_ctrl
{
    /* Parameters to control CEC peripheral device */
    cec_cfg_t const * p_cfg;                    // Pointer to the configuration structure
    uint32_t          open;                     // Open status of CEC Module
    cec_addr_t        local_address;            // Local address of this CEC device
    uint8_t const   * p_tx_buf;                 // Pointer to transmit buffer
    uint32_t          tx_bytes;                 // Number of bytes to transmit
    cec_state_t       state;                    // CEC Module state
    uint8_t           cecctl0;                  // Cached CEC Registry data
    void (* p_callback)(cec_callback_args_t *); // Pointer to callback function
    cec_callback_args_t * p_callback_memory;    // Pointer to optional callback argument memory
    void const          * p_context;            // Pointer to context to be passed into callback function
} cec_instance_ctrl_t;

/* ACMPLP extended configuration */
typedef struct
{
    uint8_t ctl0_clock_select;         ///< CEC Clock Select Setting
    uint8_t ctl0_ackten;               ///< CEC ACK Bit Timing Error (Bit Width) Check Enable
    uint8_t ctl1;                      ///< CEC Control 1 register configuration data
    uint8_t err_detect_lerplen;        ///< Error Pulse Output Enable for Long Bit Width Error
    uint8_t err_detect_rercven;        ///< Error Start Detection Reception Restart Enable
    uint8_t intda_timing_select;       ///< Data Interrupt Timing Selection
} cec_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const cec_api_t g_cec_on_cec;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_CEC_Open(cec_ctrl_t * const p_ctrl, cec_cfg_t const * const p_cfg);
fsp_err_t R_CEC_MediaInit(cec_ctrl_t * const p_ctrl, cec_addr_t local_address);
fsp_err_t R_CEC_Close(cec_ctrl_t * const p_ctrl);
fsp_err_t R_CEC_Write(cec_ctrl_t * const p_ctrl, cec_message_t const * const p_message, uint32_t message_size);
fsp_err_t R_CEC_StatusGet(cec_ctrl_t * const p_ctrl, cec_status_t * const p_status);
fsp_err_t R_CEC_CallbackSet(cec_ctrl_t * const          p_ctrl,
                            void (                    * p_callback)(cec_callback_args_t *),
                            void const * const          p_context,
                            cec_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end defgroup CEC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
