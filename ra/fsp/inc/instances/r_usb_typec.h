/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : r_usb_typec.h
 * Description  : USB TYPEC public APIs.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB_TYPEC
 * @{
 **********************************************************************************************************************/

#ifndef USB_TYPEC_H
#define USB_TYPEC_H

#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_typec_cfg.h"
#include "r_usb_typec_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** USB TYPE-C control block. DO NOT INITIALIZE.  Initialization occurs when @ref usb_typec_api_t::open is called. */
typedef struct st_usb_typec_instance_ctrl
{
    uint32_t open;                     ///< Used to determine if the channel is configured

    /* Configuration of usb type-c module. */
    usb_typec_cfg_t * p_cfg;           ///< Pointer to initial configurations.

    uint32_t module_number;            ///< USB module number (USB_IP0/USB_IP1)

    /* Pointer to callback and optional working memory */
    void (* p_callback)(usb_typec_callback_args_t *);

    /* Pointer to context to be passed into callback function */
    void * p_context;

    /* Variable to store the interrupt number. */
    IRQn_Type irq_typec_cci;           ///< USBCC_CCI interrupt number storage variable.
    IRQn_Type irq_typec_ccs;           ///< USBCC_CCS interrupt number storage variable.

    /* Variable to store the interrupt priority. */
    uint32_t ipl_typec_cci;            ///< Variable to store the interrupt priority of USBCC_CCI
    uint32_t ipl_typec_ccs;            ///< Variable to store the interrupt priority of USBCC_CCS
} usb_typec_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const usb_typec_api_t g_typec_on_typec;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_USB_TYPEC_Open(usb_typec_ctrl_t * const p_ctrl, usb_typec_cfg_t const * const p_cfg);

fsp_err_t R_USB_TYPEC_Close(usb_typec_ctrl_t * const p_ctrl);

fsp_err_t R_USB_TYPEC_InfoGet(usb_typec_ctrl_t * const p_ctrl, usb_typec_info_t * p_info);

fsp_err_t R_USB_TYPEC_LowPowerModeSet(usb_typec_ctrl_t * const p_ctrl, usb_typec_ccs_status_t status);

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_TYPEC)
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* USB_TYPEC_H */
