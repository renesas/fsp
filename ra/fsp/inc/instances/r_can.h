/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef R_CAN_H
#define R_CAN_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_can_cfg.h"
#include "r_can_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup CAN
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define CAN_CODE_VERSION_MAJOR    (1U) // DEPRECATED
#define CAN_CODE_VERSION_MINOR    (1U) // DEPRECATED

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* CAN Instance Control Block   */
typedef struct st_can_instance_ctrl
{
    /* Parameters to control CAN peripheral device */
    can_cfg_t const    * p_cfg;                 // Pointer to the configuration structure
    R_CAN0_Type        * p_reg;                 // Pointer to register base address
    uint32_t             open;                  // Open status of channel.
    can_operation_mode_t operation_mode;        // Can operation mode.
    can_test_mode_t      test_mode;             // Can operation mode.
    can_id_mode_t        id_mode;               // Standard or Extended ID mode.
    uint32_t             mailbox_count;         // Number of mailboxes.
    can_mailbox_t      * p_mailbox;             // Pointer to mailboxes.
    can_message_mode_t   message_mode;          // Overwrite message or overrun.
    can_clock_source_t   clock_source;          // Clock source. CANMCLK or PCLKB.

    void (* p_callback)(can_callback_args_t *); // Pointer to callback
    can_callback_args_t * p_callback_memory;    // Pointer to optional callback argument memory
    void const          * p_context;            // Pointer to context to be passed into callback function
} can_instance_ctrl_t;

/* CAN clock configuration and mailbox mask to be pointed to by p_extend. */
typedef struct st_can_extended_cfg
{
    can_clock_source_t clock_source;   ///< Source of the CAN clock.
    uint32_t         * p_mailbox_mask; ///< Mailbox mask, one for every 4 mailboxes.
} can_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const can_api_t g_can_on_can;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_CAN_Open(can_ctrl_t * const p_api_ctrl, can_cfg_t const * const p_cfg);
fsp_err_t R_CAN_Close(can_ctrl_t * const p_api_ctrl);
fsp_err_t R_CAN_Write(can_ctrl_t * const p_api_ctrl, uint32_t const mailbox, can_frame_t * const p_frame);
fsp_err_t R_CAN_ModeTransition(can_ctrl_t * const   p_api_ctrl,
                               can_operation_mode_t operation_mode,
                               can_test_mode_t      test_mode);
fsp_err_t R_CAN_InfoGet(can_ctrl_t * const p_api_ctrl, can_info_t * const p_info);
fsp_err_t R_CAN_CallbackSet(can_ctrl_t * const          p_api_ctrl,
                            void (                    * p_callback)(can_callback_args_t *),
                            void const * const          p_context,
                            can_callback_args_t * const p_callback_memory);
fsp_err_t R_CAN_VersionGet(fsp_version_t * const version);

/*******************************************************************************************************************//**
 * @} (end defgroup CAN)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
