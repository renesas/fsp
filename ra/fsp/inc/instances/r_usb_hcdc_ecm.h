/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : r_usb_hcdc_ecm.h
 * Description  : USB HCDC ECM public APIs.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB_HCDC_ECM
 * @{
 **********************************************************************************************************************/

#ifndef USB_HCDC_ECM_H
#define USB_HCDC_ECM_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_hcdc_cfg.h"
#include "r_ether_api.h"
#include "r_usb_basic_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MAXIMUM_ETHERNET_FRAME_SIZE    (1514U)
#define HCDC_ECM_READ_DATA_LEN         (MAXIMUM_ETHERNET_FRAME_SIZE * 2)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** USB HCDC ECM control block. DO NOT INITIALIZE.  Initialization occurs when @ref ether_api_t::open is called. */
typedef struct st_usb_hcdc_ecm_instance_ctrl
{
    uint32_t open;                                                               ///< Used to determine if the channel is configured
    uint32_t ecm_connected;

    uint8_t read_buffer[HCDC_ECM_READ_DATA_LEN] __attribute__((__aligned__(4))); ///< Buffer area for read data

    uint32_t receive_size;                                                       ///< Received data size
    uint32_t receive_status;                                                     ///< Status of receive result

    /* Pointer to callback and optional working memory */
    void (* p_callback)(ether_callback_args_t *);
    ether_callback_args_t * p_callback_memory;
    ether_cfg_t           * p_cfg;

    /* Pointer to context to be passed into callback function */
    void * p_context;

    uint8_t device_address;
} usb_hcdc_ecm_instance_ctrl_t;

typedef struct st_usb_hcdc_ecm_extended_cfg
{
    usb_instance_t const * p_usb;
} usb_hcdc_ecm_extended_cfg_t;

/******************************************************************************
 * Exported global functions (to be accessed by other files)
 ******************************************************************************/

fsp_err_t R_USB_HCDC_ECM_Open(ether_ctrl_t * const p_ctrl, ether_cfg_t const * const p_cfg);

fsp_err_t R_USB_HCDC_ECM_Close(ether_ctrl_t * const p_ctrl);

fsp_err_t R_USB_HCDC_ECM_BufferRelease(ether_ctrl_t * const p_ctrl);

fsp_err_t R_USB_HCDC_ECM_RxBufferUpdate(ether_ctrl_t * const p_ctrl, void * const p_buffer);

fsp_err_t R_USB_HCDC_ECM_LinkProcess(ether_ctrl_t * const p_ctrl);

fsp_err_t R_USB_HCDC_ECM_WakeOnLANEnable(ether_ctrl_t * const p_ctrl);

fsp_err_t R_USB_HCDC_ECM_Read(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t * const length_bytes);

fsp_err_t R_USB_HCDC_ECM_Write(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t const frame_length);

fsp_err_t R_USB_HCDC_ECM_TxStatusGet(ether_ctrl_t * const p_ctrl, void * const p_buffer_address);

fsp_err_t R_USB_HCDC_ECM_CallbackSet(ether_ctrl_t * const          p_api_ctrl,
                                     void (                      * p_callback)(ether_callback_args_t *),
                                     void * const                  p_context,
                                     ether_callback_args_t * const p_callback_memory);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* USB_HCDC_ECM_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HCDC_ECM)
 **********************************************************************************************************************/
