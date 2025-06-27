/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup USB_TYPEC_API USB TYPEC Interface
 * @brief Interface for USB Type-C functions.
 *
 * @section USB_TYPEC_API_Summary Summary
 * The USB Type-C interface provides USB functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_TYPEC_API_H
#define R_USB_TYPEC_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

#if __has_include("r_usb_typec_device_types.h")
 #include "r_usb_typec_device_types.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** USB TypeC operation_mode */
typedef enum e_usb_typec_mode
{
    USB_TYPEC_MODE_SINK = 0,           ///< Sink Only Mode
    USB_TYPEC_MODE_USB20_ONLY_SINK,    ///< USB 2.0 Only Sink Mode
} usb_typec_mode_t;

/** USB TypeC Source Current Detection mode */
typedef enum e_usb_typec_pmode
{
    USB_TYPEC_PMODE_DEFAULT = 0,       ///< Detect Default USB Source
    USB_TYPEC_PMODE_DEFAULT_1_5A,      ///< Detect Default USB and 1.5A Source
    USB_TYPEC_PMODE_DEFAULT_1_5A_3_0A, ///< Detect Default USB, 1.5A and 3.0A Source
} usb_typec_pmode_t;

/** USB TypeC Connection of Plug Orientation */
typedef enum e_usb_typec_plug
{
    USB_TYPEC_PLUG_CC1_CONNECTED = 0,  ///< CC1 connected
    USB_TYPEC_PLUG_CC2_CONNECTED,      ///< CC2 connected
} usb_typec_plug_t;

/** USB TypeC Status of Connection State Machine */
typedef enum e_usb_typec_connection_status
{
    USB_TYPEC_CONNECTION_STATUS_DISABLED = 0,           ///< Disabled
    USB_TYPEC_CONNECTION_STATUS_UNATTACHED,             ///< Unattached.SNK
    USB_TYPEC_CONNECTION_STATUS_ATTACHED_WAIT,          ///< AttachedWait.SNK
    USB_TYPEC_CONNECTION_STATUS_ATTACHED,               ///< Attached.SNK
    USB_TYPEC_CONNECTION_STATUS_ATTACHED_POWER_DEFAULT, ///< Attached.SNK (PowerDefault.SNK)
    USB_TYPEC_CONNECTION_STATUS_ATTACHED_POWER_1_5,     ///< Attached.SNK (Power1.5.SNK)
    USB_TYPEC_CONNECTION_STATUS_ATTACHED_POWER_3_0,     ///< Attached.SNK (Power3.0.SNK)
} usb_typec_connection_status_t;

/** USB TypeC VBUS status */
typedef enum e_usb_typec_vbus_status
{
    USB_TYPEC_VBUS_STATUS_OFF = 0,     ///< VBUS Off State
    USB_TYPEC_VBUS_STATUS_ON,          ///< VBUS On State
} usb_typec_vbus_status_t;

/** Status code of callback function */
typedef enum e_usb_typec_status
{
    USB_TYPEC_STATUS_ISCN = 0,         ///< Connection Status Change
    USB_TYPEC_STATUS_ISCC,             ///< CC Status Change
    USB_TYPEC_STATUS_ISVBUS,           ///< VBUS Status Change
    USB_TYPEC_STATUS_ISVRA,            ///< Rp Detection for USBCC_CCI Interrupt
    USB_TYPEC_STATUS_ISVRA_CCS,        ///< Rp Detection for USBCC_CCS Interrupt
} usb_typec_status_t;

/** Status code of USBCC CCS Enable/Disable */
typedef enum e_usb_typec_ccs_status
{
    USB_TYPEC_CCS_STATUS_OFF = 0,      ///< USBCC CCS Disable
    USB_TYPEC_CCS_STATUS_ON,           ///< USBCC CCS Enable
} usb_typec_ccs_status_t;

/** USB Type-C control block.  Allocate an instance specific control block to pass into the USB Type-C API calls.
 */
typedef void usb_typec_ctrl_t;

typedef struct st_usb_typec_info
{
    usb_typec_mode_t              operation_mode;    ///< Connection State Mode
    usb_typec_plug_t              plug;              ///< Connection of Plug Orientation
    usb_typec_connection_status_t connection_status; ///< Status of Connection Statue Machine
    usb_typec_vbus_status_t       vbus_status;       ///< Status of VBUS
} usb_typec_info_t;

/** Callback function parameter data */
typedef struct st_usb_typec_callback_args
{
    uint32_t                      module_number;     ///< USB Type-C module number
    usb_typec_status_t            status;            ///< Status code
    usb_typec_plug_t              plug;              ///< Connection of Plug Orientation
    usb_typec_connection_status_t connection_status; ///< Status of Connection Statue Machine
    usb_typec_vbus_status_t       vbus_status;       ///< Status of VBUS

    void * p_context;                                ///< Placeholder for user data.  Set in @ref usb_typec_api_t::open function in @ref usb_typec_cfg_t.
} usb_typec_callback_args_t;

typedef void (usb_typec_callback_t)(usb_typec_callback_args_t *);

/** USB Type-C configuration. */
typedef struct st_usb_typec_cfg
{
    uint32_t               module_number;   ///< USB Type-C module number
    usb_typec_mode_t       usb_typec_mode;  ///< Sink Only/USB 2.0 Only Sink Mode
    usb_typec_pmode_t      usb_typec_pmode; ///< Detect Default USB Source/Detect Default USB and 1.5A Source/Detect Default USB, 1.5A and 3.0A Source
    IRQn_Type              irq_typec_cci;   ///< USBCC_CCI interrupt number storage variable.
    IRQn_Type              irq_typec_ccs;   ///< USBCC_CCS interrupt number storage variable.
    uint32_t               ipl_typec_cci;   ///< Variable to store the interrupt priority of USBCC_CCI IR.
    uint32_t               ipl_typec_ccs;   ///< Variable to store the interrupt priority of USBCC_CCS IR.
    usb_typec_callback_t * p_callback;      ///< Type-C Callback.
    void                 * p_context;       ///< Other Context
    void const           * p_extend;        ///< Pointer to extended configuration by instance of interface.
} usb_typec_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_usb_typec_api
{
    /** Start the USB Type-C module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(usb_typec_ctrl_t * const p_ctrl, usb_typec_cfg_t const * const p_cfg);

    /** Stop the USB Type-C module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(usb_typec_ctrl_t * const p_ctrl);

    /** Get information on USB Type-C module.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_info       Pointer to usb_typec_info_t structure area.
     */
    fsp_err_t (* infoGet)(usb_typec_ctrl_t * const p_ctrl, usb_typec_info_t * const p_info);

    /** Set IRQ Mode for USB Type-C module by Software Standby
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  status       Status code of USBCC CCS Enable/Disable.
     */
    fsp_err_t (* lowPowerModeSet)(usb_typec_ctrl_t * const p_ctrl, usb_typec_ccs_status_t status);
} usb_typec_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_usb_typec_instance
{
    usb_typec_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    usb_typec_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    usb_typec_api_t const * p_api;     ///< Pointer to the API structure for this instance
} usb_typec_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup USB_TYPEC_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_TYPEC_API_H */
