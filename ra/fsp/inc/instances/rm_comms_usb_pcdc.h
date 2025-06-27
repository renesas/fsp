/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_USB_PCDC
 * @{
 **********************************************************************************************************************/

#ifndef RM_COMMS_USB_PCDC_H
#define RM_COMMS_USB_PCDC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_usb_basic_api.h"
#include "r_usb_basic.h"
#include "r_usb_pcdc_api.h"
#include "rm_comms_api.h"
#include "rm_comms_usb_pcdc_cfg.h"

#if BSP_CFG_RTOS == 0
 #include "r_timer_api.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* USB bus configuration */
typedef struct st_rm_comms_usb_pcdc_extended_cfg
{
#if BSP_CFG_RTOS == 2
    void * const   p_tx_mutex;         ///< Lock device for writing.
    void * const   p_rx_mutex;         ///< Lock device for reading.
    uint32_t const mutex_timeout;      ///< Timeout for locking device.
    void * const   p_tx_semaphore;     ///< Block write operations. If this is NULL then operations will be non-blocking and require a callback.
    void * const   p_rx_semaphore;     ///< Block read operations. If this is NULL then operations will be non-blocking and require a callback.
#endif
    usb_instance_t const * p_usb;      ///< Pointer to USB instance.
#if BSP_CFG_RTOS == 0
    timer_instance_t const * p_gpt;    ///< Pointer to GPT instance.
#endif
    uint8_t connect_detection_en;
} rm_comms_usb_pcdc_extended_cfg_t;

/** Communications middleware control structure. */
typedef struct st_rm_comms_usb_pcdc_instance_ctrl
{
    uint32_t               open;                            ///< Open flag.
    rm_comms_cfg_t const * p_cfg;                           ///< Middleware configuration.
    rm_comms_usb_pcdc_extended_cfg_t const * p_extend;      ///< Pointer to extended configuration structure
    usb_callback_args_t    * p_usb_args;                    ///< Pointer to usb callback args
    usb_pcdc_ctrllinestate_t ctrl_line_state;               ///< Line State Control
    usb_pcdc_linecoding_t    line_coding;                   ///< Line Coding to store COM port settings

    void (* p_callback)(rm_comms_callback_args_t * p_args); ///< Pointer to callback that is called when a usb_status_t occurs.
    void * p_context;                                       ///< Pointer to context passed into callback function
} rm_comms_usb_pcdc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern rm_comms_api_t const g_comms_on_comms_usb_pcdc;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_USB_PCDC_Open(rm_comms_ctrl_t * const p_api_ctrl, rm_comms_cfg_t const * const p_cfg);
fsp_err_t RM_COMMS_USB_PCDC_Close(rm_comms_ctrl_t * const p_api_ctrl);
fsp_err_t RM_COMMS_USB_PCDC_Read(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t RM_COMMS_USB_PCDC_Write(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);
fsp_err_t RM_COMMS_USB_PCDC_WriteRead(rm_comms_ctrl_t * const            p_api_ctrl,
                                      rm_comms_write_read_params_t const write_read_params);
fsp_err_t RM_COMMS_USB_PCDC_CallbackSet(rm_comms_ctrl_t * const p_api_ctrl,
                                        void (                * p_callback)(rm_comms_callback_args_t *),
                                        void * const            p_context);

void rm_comms_usb_pcdc_notify_application(rm_comms_usb_pcdc_instance_ctrl_t const * p_ctrl, rm_comms_event_t event);

#if BSP_CFG_RTOS == 2
void rm_comms_usb_pcdc_callback_handler(usb_instance_ctrl_t * p_args, usb_hdl_t usb_handle,
                                        usb_onoff_t usb_onoff_status);

#elif BSP_CFG_RTOS == 0
void rm_comms_usb_pcdc_callback_handler(usb_callback_args_t * p_args);
void rm_comms_usb_pcdc_timer_handler(timer_callback_args_t * p_args);

#endif

FSP_FOOTER

#endif                                 /* RM_COMMS_USB_PCDC_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMMS_USB_PCDC)
 **********************************************************************************************************************/
