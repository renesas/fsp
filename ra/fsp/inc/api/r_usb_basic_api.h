/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup USB_API USB Interface
 * @brief Interface for USB functions.
 *
 * @section USB_API_Summary Summary
 * The USB interface provides USB functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_API_H
#define R_USB_API_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "bsp_api.h"
#include "r_transfer_api.h"
#include "../../src/r_usb_basic/src/driver/inc/r_usb_basic_define.h"

#if (BSP_CFG_RTOS == 2)
 #include "FreeRTOS.h"
 #include "task.h"
 #include "queue.h"
 #include "timers.h"
 #include "semphr.h"
#elif   (BSP_CFG_RTOS == 1)
 #include "tx_api.h"
#endif                                 /* #if (BSP_CFG_RTOS == 2) */

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/* USB Request Type Register */
#define USB_BREQUEST               (0xFF00U) ///< b15-8

/* USB Standard request */
#define USB_GET_STATUS             (0x0000U) ///< USB Standard request Get Status
#define USB_CLEAR_FEATURE          (0x0100U) ///< USB Standard request Clear Feature
#define USB_REQRESERVED            (0x0200U) ///< USB Standard request Reqreserved
#define USB_SET_FEATURE            (0x0300U) ///< USB Standard request Set Feature
#define USB_REQRESERVED1           (0x0400U) ///< USB Standard request Reqreserved1
#define USB_SET_ADDRESS            (0x0500U) ///< USB Standard request Set Address
#define USB_GET_DESCRIPTOR         (0x0600U) ///< USB Standard request Get Descriptor
#define USB_SET_DESCRIPTOR         (0x0700U) ///< USB Standard request Set Descriptor
#define USB_GET_CONFIGURATION      (0x0800U) ///< USB Standard request Get Configuration
#define USB_SET_CONFIGURATION      (0x0900U) ///< USB Standard request Set Configuration
#define USB_GET_INTERFACE          (0x0A00U) ///< USB Standard request Get Interface
#define USB_SET_INTERFACE          (0x0B00U) ///< USB Standard request Set Interface
#define USB_SYNCH_FRAME            (0x0C00U) ///< USB Standard request Synch Frame

/* USB_BMREQUESTTYPEDIR 0x0080u(b7) */
#define USB_HOST_TO_DEV            (0x0000U) ///< From host to device.
#define USB_DEV_TO_HOST            (0x0080U) ///< From device to host.

/* USB_BMREQUESTTYPETYPE    0x0060u(b6-5) */
#define USB_STANDARD               (0x0000U) ///< Standard Request
#define USB_CLASS                  (0x0020U) ///< Class Request
#define USB_VENDOR                 (0x0040U) ///< Vendor Request

/* USB_BMREQUESTTYPERECIP   0x001Fu(b4-0) */
#define USB_DEVICE                 (0x0000U) ///< Device
#define USB_INTERFACE              (0x0001U) ///< Interface
#define USB_ENDPOINT               (0x0002U) ///< End Point
#define USB_OTHER                  (0x0003U) ///< Other

#define USB_NULL                   (0x0U)    ///< NULL pointer

#define USB_IP0                    (0)       ///< USB0 module
#define USB_IP1                    (1)       ///< USB1 module

/* USB pipe number */
#define USB_PIPE0                  (0x0U)    ///< Pipe Number0
#define USB_PIPE1                  (0x1U)    ///< Pipe Number1
#define USB_PIPE2                  (0x2U)    ///< Pipe Number2
#define USB_PIPE3                  (0x3U)    ///< Pipe Number3
#define USB_PIPE4                  (0x4U)    ///< Pipe Number4
#define USB_PIPE5                  (0x5U)    ///< Pipe Number5
#define USB_PIPE6                  (0x6U)    ///< Pipe Number6
#define USB_PIPE7                  (0x7U)    ///< Pipe Number7
#define USB_PIPE8                  (0x8U)    ///< Pipe Number8
#define USB_PIPE9                  (0x9U)    ///< Pipe Number9

#define USB_EP0                    (0x0U)    ///< End Point Number0
#define USB_EP1                    (0x1U)    ///< End Point Number1
#define USB_EP2                    (0x2U)    ///< End Point Number2
#define USB_EP3                    (0x3U)    ///< End Point Number3
#define USB_EP4                    (0x4U)    ///< End Point Number4
#define USB_EP5                    (0x5U)    ///< End Point Number5
#define USB_EP6                    (0x6U)    ///< End Point Number6
#define USB_EP7                    (0x7U)    ///< End Point Number7
#define USB_EP8                    (0x8U)    ///< End Point Number8
#define USB_EP9                    (0x9U)    ///< End Point Number9
#define USB_EP10                   (0xAU)    ///< End Point Number10
#define USB_EP11                   (0xBU)    ///< End Point Number11
#define USB_EP12                   (0xCU)    ///< End Point Number12
#define USB_EP13                   (0xDU)    ///< End Point Number13
#define USB_EP14                   (0xEU)    ///< End Point Number14
#define USB_EP15                   (0xFU)    ///< End Point Number15

/* Endpoint Direction */
#define USB_EP_DIR                 (0x0080U) ///< b7: Endpoint Direction
#define USB_EP_DIR_IN              (0x0080U) ///< b7: Endpoint Direction In
#define USB_EP_DIR_OUT             (0x0000U) ///< b7: Endpoint Direction Out

/* Descriptor type  Define */
#define USB_DT_DEVICE              (0x01U)   ///< Device Descriptor
#define USB_DT_CONFIGURATION       (0x02U)   ///< Configuration Descriptor
#define USB_DT_STRING              (0x03U)   ///< String Descriptor
#define USB_DT_INTERFACE           (0x04U)   ///< Interface Descriptor
#define USB_DT_ENDPOINT            (0x05U)   ///< Endpoint Descriptor
#define USB_DT_DEVICE_QUALIFIER    (0x06U)   ///< Device Qualifier Descriptor
#define USB_DT_OTHER_SPEED_CONF    (0x07U)   ///< Other Speed Configuration Descriptor
#define USB_DT_INTERFACE_POWER     (0x08U)   ///< Interface Power Descriptor
#define USB_DT_OTGDESCRIPTOR       (0x09U)   ///< OTG Descriptor
#define USB_DT_HUBDESCRIPTOR       (0x29U)   ///< HUB descriptor

/* Interface class Define */
#define USB_IFCLS_NOT              (0x00U)   ///< Un corresponding Class
#define USB_IFCLS_AUD              (0x01U)   ///< Audio Class
#define USB_IFCLS_CDC              (0x02U)   ///< CDC Class
#define USB_IFCLS_CDCC             (0x02U)   ///< CDC-Control Class
#define USB_IFCLS_HID              (0x03U)   ///< HID Class
#define USB_IFCLS_PHY              (0x05U)   ///< Physical Class
#define USB_IFCLS_IMG              (0x06U)   ///< Image Class
#define USB_IFCLS_PRN              (0x07U)   ///< Printer Class
#define USB_IFCLS_MAS              (0x08U)   ///< Mass Storage Class
#define USB_IFCLS_HUB              (0x09U)   ///< HUB Class
#define USB_IFCLS_CDCD             (0x0AU)   ///< CDC-Data Class
#define USB_IFCLS_CHIP             (0x0BU)   ///< Chip/Smart Card Class
#define USB_IFCLS_CNT              (0x0CU)   ///< Content-Security Class
#define USB_IFCLS_VID              (0x0EU)   ///< Video Class
#define USB_IFCLS_DIAG             (0xDCU)   ///< Diagnostic Device
#define USB_IFCLS_WIRE             (0xE0U)   ///< Wireless Controller
#define USB_IFCLS_APL              (0xFEU)   ///< Application-Specific
#define USB_IFCLS_VEN              (0xFFU)   ///< Vendor-Specific Class

/* Endpoint Descriptor  Define */
#define USB_EP_IN                  (0x80U)   ///< In Endpoint
#define USB_EP_OUT                 (0x00U)   ///< Out Endpoint
#define USB_EP_ISO                 (0x01U)   ///< Isochronous Transfer
#define USB_EP_BULK                (0x02U)   ///< Bulk Transfer
#define USB_EP_INT                 (0x03U)   ///< Interrupt Transfer

/* Configuration descriptor bit define */
#define USB_CF_RESERVED            (0x80U)   ///< Reserved(set to 1)
#define USB_CF_SELFP               (0x40U)   ///< Self Powered
#define USB_CF_BUSP                (0x00U)   ///< Bus Powered
#define USB_CF_RWUPON              (0x20U)   ///< Remote Wake up ON
#define USB_CF_RWUPOFF             (0x00U)   ///< Remote Wake up OFF

/* Descriptor length Define */
#define USB_DD_BLENGTH             (18U)     ///< Device Descriptor Length
#define USB_CD_BLENGTH             (9U)      ///< Configuration Descriptor Length
#define USB_ID_BLENGTH             (9U)      ///< Interface Descriptor Length
#define USB_ED_BLENGTH             (7U)      ///< Endpoint Descriptor Length

/*****************************************************************************
 * Typedef definitions
 ******************************************************************************/

/** USB speed type */
typedef enum e_usb_speed
{
    USB_SPEED_LS = 0,                  ///< Low speed operation
    USB_SPEED_FS,                      ///< Full speed operation
    USB_SPEED_HS,                      ///< Hi speed operation
} usb_speed_t;

/** USB request result */
typedef enum e_usb_setup_status
{
    USB_SETUP_STATUS_ACK = 0,          ///< ACK response
    USB_SETUP_STATUS_STALL,            ///< STALL response
} usb_setup_status_t;

/** USB driver status */
typedef enum e_usb_status
{
    USB_STATUS_POWERED = 0,            ///< Powered State
    USB_STATUS_DEFAULT,                ///< Default State
    USB_STATUS_ADDRESS,                ///< Address State
    USB_STATUS_CONFIGURED,             ///< Configured State
    USB_STATUS_SUSPEND,                ///< Suspend State
    USB_STATUS_RESUME,                 ///< Resume State
    USB_STATUS_DETACH,                 ///< Detach State
    USB_STATUS_REQUEST,                ///< Request State
    USB_STATUS_REQUEST_COMPLETE,       ///< Request Complete State
    USB_STATUS_READ_COMPLETE,          ///< Read Complete State
    USB_STATUS_WRITE_COMPLETE,         ///< Write Complete State
    USB_STATUS_BC,                     ///< battery Charge State
    USB_STATUS_OVERCURRENT,            ///< Over Current state
    USB_STATUS_NOT_SUPPORT,            ///< Device Not Support
    USB_STATUS_NONE,                   ///< None Status
    USB_STATUS_MSC_CMD_COMPLETE,       ///< MSC_CMD Complete
} usb_status_t;

/** USB class type */
typedef enum e_usb_class
{
    USB_CLASS_PCDC = 0x80,             ///< PCDC Class
    USB_CLASS_PCDCC,                   ///< PCDCC Class
    USB_CLASS_PCDC2,                   ///< PCDC2 Class
    USB_CLASS_PCDCC2,                  ///< PCDCC2 Class
    USB_CLASS_PHID,                    ///< PHID Class
    USB_CLASS_PHID2,                   ///< PHID2 Class
    USB_CLASS_PAUD,                    ///< PAUD Class
    USB_CLASS_PPRN,                    ///< PPRN Class
    USB_CLASS_DFU,                     ///< DFU Class
    USB_CLASS_PVND,                    ///< PVND Class
    USB_CLASS_HCDC,                    ///< HCDC Class
    USB_CLASS_HCDCC,                   ///< HCDCC Class
    USB_CLASS_HHID,                    ///< HHID Class
    USB_CLASS_HVND,                    ///< HVND Class
    USB_CLASS_HMSC,                    ///< HMSC Class
    USB_CLASS_PMSC,                    ///< PMSC Class
    USB_CLASS_HPRN,                    ///< HPRN Class
    USB_CLASS_HUVC,                    ///< HUVC Class
    USB_CLASS_REQUEST,                 ///< USB Class Request
    USB_CLASS_HUB,                     ///< HUB Class
    USB_CLASS_END,                     ///< USB Class End Code
} usb_class_t;

/** USB battery charging type */
typedef enum e_usb_bcport
{
    USB_BCPORT_SDP = 0,                ///< SDP port settings
    USB_BCPORT_CDP,                    ///< CDP port settings
    USB_BCPORT_DCP,                    ///< DCP port settings
} usb_bcport_t;

/** USB status */
typedef enum e_usb_onoff
{
    USB_OFF = 0,                       ///< USB Off State
    USB_ON,                            ///< USB On State
} usb_onoff_t;

/** USB read/write type */
typedef enum e_usb_transfer
{
    USB_TRANSFER_READ = 0,             ///< Data Receive communication
    USB_TRANSFER_WRITE,                ///< Data transmission communication
} usb_transfer_t;

/** USB transfer type */
typedef enum e_usb_transfer_type
{
    USB_TRANSFER_TYPE_BULK = 0,        ///< Bulk communication
    USB_TRANSFER_TYPE_INT,             ///< Interrupt communication
    USB_TRANSFER_TYPE_ISO,             ///< Isochronous communication
} usb_transfer_type_t;

/* H/W function type */
typedef enum e_usb_mode
{
    USB_MODE_HOST = 1,                 ///< Host mode
    USB_MODE_PERI,                     ///< Peripheral mode
} usb_mode_t;

typedef enum e_usb_compliancetest_status
{
    USB_COMPLIANCETEST_ATTACH,         ///< Device Attach Detection
    USB_COMPLIANCETEST_DETACH,         ///< Device Detach Detection
    USB_COMPLIANCETEST_TPL,            ///< TPL device connect
    USB_COMPLIANCETEST_NOTTPL,         ///< Not TPL device connect
    USB_COMPLIANCETEST_HUB,            ///< USB Hub connect
    USB_COMPLIANCETEST_OVRC,           ///< Over current
    USB_COMPLIANCETEST_NORES,          ///< Response Time out for Control Read Transfer
    USB_COMPLIANCETEST_SETUP_ERR,      ///< Setup Transaction Error
} usb_compliancetest_status_t;

typedef enum e_usb_address
{
    USB_ADDRESS1 = 1,
    USB_ADDRESS2,
    USB_ADDRESS3,
    USB_ADDRESS4,
    USB_ADDRESS5,
} usb_address_t;

/** USB TypeC operation_mode */
typedef enum e_usb_typec_mode
{
    USB_TYPEC_MODE_SINK = 0,                ///< Sink Only Mode
    USB_TYPEC_MODE_USB20_ONLY_SINK,         ///< USB 2.0 Only Sink Mode
} usb_typec_mode_t;

/** USB TypeC Connection of Plug Orientation */
typedef enum e_usb_typec_plug
{
    USB_TYPEC_PLUG_CC1_CONNECTED = 0,       ///< CC1 connected
    USB_TYPEC_PLUG_CC2_CONNECTED,           ///< CC2 connected
} usb_typec_plug_t;

/** USB TypeC Status of Connection State Machine */
typedef enum e_usb_typec_connection_status
{
    USB_TYPEC_CONNECTION_STATUS_DISABLED = 0,            ///< Disabled
    USB_TYPEC_CONNECTION_STATUS_UNATTACHED,              ///< Unattached.SNK
    USB_TYPEC_CONNECTION_STATUS_ATTACHED_WAIT,           ///< AttachedWait.SNK
    USB_TYPEC_CONNECTION_STATUS_ATTACHED,                ///< Attached.SNK
    USB_TYPEC_CONNECTION_STATUS_ATTACHED_POWER_DEFAULT,  ///< Attached.SNK (PowerDefault.SNK)
    USB_TYPEC_CONNECTION_STATUS_ATTACHED_POWER_15,       ///< Attached.SNK (Power1.5.SNK)
    USB_TYPEC_CONNECTION_STATUS_ATTACHED_POWER_30,       ///< Attached.SNK (Power3.0.SNK)
} usb_typec_connection_status_t;

/** USB TypeC VBUS status */
typedef enum e_usb_typec_vbus_status
{
    USB_TYPEC_VBUS_STATUS_OFF = 0,            ///< VBUS Off State
    USB_TYPEC_VBUS_STATUS_ON,                 ///< VBUS On State
} usb_typec_vbus_status_t;


/** USB control block.  Allocate an instance specific control block to pass into the USB API calls.
 */
typedef void usb_ctrl_t;
typedef void (usb_compliance_cb_t)(void *);

typedef struct st_usb_descriptor
{
    uint8_t  * p_device;               ///< Pointer to the device descriptor
    uint8_t  * p_config_f;             ///< Pointer to the configuration descriptor for Full-speed
    uint8_t  * p_config_h;             ///< Pointer to the configuration descriptor for Hi-speed
    uint8_t  * p_qualifier;            ///< Pointer to the qualifier descriptor
    uint8_t ** p_string;               ///< Pointer to the string descriptor table
    uint8_t    num_string;             ///< Num entry String Descriptor
} usb_descriptor_t;

typedef struct st_usb_setup
{
    uint16_t request_type;             ///< USB standard/class request type
    uint16_t request_value;            ///< Request value
    uint16_t request_index;            ///< Request index
    uint16_t request_length;           ///< Request length
} usb_setup_t;

typedef struct st_usb_pipe
{
    uint8_t  endpoint;                 ///< Endpoint number
    uint8_t  transfer_type;            ///< Transfer type (USB_BULK/USB_INT etc)
    uint16_t maxpacketsize;            ///< Max packet size
} usb_pipe_t;

typedef struct st_usb_info
{
    uint8_t class_type;                ///< USB device class type
    uint8_t speed;                     ///< USB speed
    uint8_t device_status;             ///< USB device status
    uint8_t bcport;                    ///< Battery charging information
} usb_info_t;

typedef struct st_usb_compliance
{
    usb_compliancetest_status_t status; ///< USB Status
    uint16_t vid;                       ///< Vendor ID
    uint16_t pid;                       ///< Product ID
} usb_compliance_t;

typedef struct st_usb_event_info
{
    uint8_t                     module_number;  ///< USB module number (USB_IP0/USB_IP1)
    uint8_t                     device_address; ///< USB device address
    uint8_t                     pipe;           ///< USB pipe number
    usb_class_t                 type;           ///< USB device class etc
    uint16_t                    status;         ///< USB device state etc
    usb_status_t                event;          ///< USB event
    uint32_t                    data_size;      ///< Read data size
    usb_setup_t                 setup;          ///< usb_setup_t structure area
    void                      * p_data;         ///< Other information
    void                      * p_context;      ///< Other Context
    const transfer_instance_t * p_transfer_tx;  ///< Send context
    const transfer_instance_t * p_transfer_rx;  ///< Receive context
} usb_event_info_t;

typedef struct st_usb_typec_info
{
    usb_typec_mode_t                operation_mode;     ///< Connection State Mode
    usb_typec_plug_t                plug;               ///< Connection of Plug Orientation
    usb_typec_connection_status_t   connection_status;  ///< Status of Connection Statue Machine
    usb_typec_vbus_status_t         vbus_status;        ///< Status of VBUS
} usb_typec_info_t;

typedef usb_event_info_t usb_callback_args_t;

#if (BSP_CFG_RTOS == 0)
typedef void (usb_callback_t)(usb_callback_args_t *);
#endif
#if (BSP_CFG_RTOS == 1)
typedef TX_THREAD * usb_hdl_t;
typedef void        (usb_callback_t)(usb_event_info_t *, usb_hdl_t, usb_onoff_t);
#endif
#if (BSP_CFG_RTOS == 2)
typedef TaskHandle_t usb_hdl_t;
typedef void         (usb_callback_t)(usb_event_info_t *, usb_hdl_t, usb_onoff_t);
#endif                                 /* #if (BSP_CFG_RTOS == 2) */

#if (BSP_CFG_RTOS != 1)
typedef uint32_t ULONG;
#endif

typedef void (usb_otg_callback_t)(ULONG);

/** USB configuration. */
typedef struct st_usb_cfg
{
    usb_mode_t                  usb_mode;           ///< USB_MODE_HOST/USB_MODE_PERI
    usb_speed_t                 usb_speed;          ///< USB speed (USB_HS/USB_FS/USB_LS)
    uint8_t                     module_number;      ///< USB module number (USB_IP0/USB_IP1)
    usb_class_t                 type;               ///< USB device class etc
    usb_descriptor_t          * p_usb_reg;          ///< Pointer to the usb_decriptor_t structure area
    usb_compliance_cb_t       * usb_complience_cb;
    IRQn_Type                   irq;                ///< USBI dedicated interrupt number storage variable.
    IRQn_Type                   irq_r;              ///< USBR dedicated interrupt number storage variable.
    IRQn_Type                   irq_d0;             ///< FS D0FIFO dedicated interrupt number storage variable.
    IRQn_Type                   irq_d1;             ///< FS D1FIFO dedicated interrupt number storage variable.
    IRQn_Type                   hsirq;              ///< USBIR dedicated interrupt number storage variable.
    IRQn_Type                   irq_typec;          ///< USB Type-C IR dedicated interrupt number storage variable.
    IRQn_Type                   hsirq_d0;           ///< HS D0FIFO dedicated interrupt number storage variable.
    IRQn_Type                   hsirq_d1;           ///< HS D1FIFO dedicated interrupt number storage variable.
    uint8_t                     ipl;                ///< Variable to store the interrupt priority of USBI
    uint8_t                     ipl_r;              ///< Variable to store the interrupt priority of USBR.
    uint8_t                     ipl_d0;             ///< Variable to store the interrupt priority of FS D0FIFO.
    uint8_t                     ipl_d1;             ///< Variable to store the interrupt priority of FS D1FIFO.
    uint8_t                     hsipl;              ///< Variable to store the interrupt priority of USBIR.
    uint8_t                     ipl_typec;          ///< Variable to store the interrupt priority of USB Type-C IR.
    uint8_t                     hsipl_d0;           ///< Variable to store the interrupt priority of HS D0FIFO.
    uint8_t                     hsipl_d1;           ///< Variable to store the interrupt priority of HS D1FIFO.
    usb_callback_t            * p_usb_apl_callback; ///< Application Callback
    void const                * p_context;          ///< Other Context
    const transfer_instance_t * p_transfer_tx;      ///< Send context
    const transfer_instance_t * p_transfer_rx;      ///< Receive context
    void const                * p_extend;           ///< Pointer to extended configuration by instance of interface.
} usb_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_usb_api
{
    /** Start the USB module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(usb_ctrl_t * const p_ctrl, usb_cfg_t const * const p_cfg);

    /** Stop the USB module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(usb_ctrl_t * const p_ctrl);

    /** Request USB data read
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_buf        Pointer to area that stores read data.
     * @param[in]  size         Read request size.
     * @param[in]  destination  In Host mode, it represents the device address, and in Peripheral mode, it represents the device class.
     */
    fsp_err_t (* read)(usb_ctrl_t * const p_ctrl, uint8_t * p_buf, uint32_t size, uint8_t destination);

    /** Request USB data write
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_buf        Pointer to area that stores write data.
     * @param[in]  size         Read request size.
     * @param[in]  destination  In Host mode, it represents the device address, and in Peripheral mode, it represents the device class.
     */
    fsp_err_t (* write)(usb_ctrl_t * const p_ctrl, uint8_t const * const p_buf, uint32_t size, uint8_t destination);

    /** Stop USB data read/write processing
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  direction     Receive (USB_TRANSFER_READ) or send (USB_TRANSFER_WRITE).
     * @param[in]  destination   In Host mode, it represents the device address, and in Peripheral mode, it represents the device class.
     */
    fsp_err_t (* stop)(usb_ctrl_t * const p_ctrl, usb_transfer_t direction, uint8_t destination);

    /** Request suspend
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     */
    fsp_err_t (* suspend)(usb_ctrl_t * const p_ctrl);

    /** Request resume
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     */
    fsp_err_t (* resume)(usb_ctrl_t * const p_ctrl);

    /** Sets VBUS supply start/stop.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  state        VBUS supply start/stop specification
     */
    fsp_err_t (* vbusSet)(usb_ctrl_t * const p_ctrl, uint16_t state);

    /** Get information on USB device.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_info       Pointer to usb_info_t structure area.
     * @param[in]  destination  Device address for Host.
     */
    fsp_err_t (* infoGet)(usb_ctrl_t * const p_ctrl, usb_info_t * p_info, uint8_t destination);

    /** Request data read from specified pipe
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_buf        Pointer to area that stores read data.
     * @param[in]  size         Read request size.
     * @param[in]  pipe_number  Pipe Number.
     */
    fsp_err_t (* pipeRead)(usb_ctrl_t * const p_ctrl, uint8_t * p_buf, uint32_t size, uint8_t pipe_number);

    /** Request data write to specified pipe
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_buf        Pointer to area that stores write data.
     * @param[in]  size         Read request size.
     * @param[in]  pipe_number  Pipe Number.
     */
    fsp_err_t (* pipeWrite)(usb_ctrl_t * const p_ctrl, uint8_t * p_buf, uint32_t size, uint8_t pipe_number);

    /** Stop USB data read/write processing to specified pipe
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  pipe_number  Pipe Number.
     */
    fsp_err_t (* pipeStop)(usb_ctrl_t * const p_ctrl, uint8_t pipe_number);

    /** Get pipe number
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_pipe       Pointer to area that stores the selected pipe number (bit map information).
     * @param[in]  destination  Device address for Host.
     */
    fsp_err_t (* usedPipesGet)(usb_ctrl_t * const p_ctrl, uint16_t * p_pipe, uint8_t destination);

    /** Get pipe information
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_info       Pointer to usb_pipe_t structure area.
     * @param[in]  pipe_number  Pipe Number.
     */
    fsp_err_t (* pipeInfoGet)(usb_ctrl_t * const p_ctrl, usb_pipe_t * p_info, uint8_t pipe_number);

    /** Return USB-related completed events (OS less only)
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] event        Pointer to event.
     */
    fsp_err_t (* eventGet)(usb_ctrl_t * const p_ctrl, usb_status_t * event);

    /** Register a callback function to be called upon completion of a USB related event. (RTOS only)
     *
     * @param[in]  p_callback   Pointer to Callback function.
     */
    fsp_err_t (* callback)(usb_callback_t * p_callback);

    /** Pull-up enable/disable setting of D+/D- line.
     *
     * @param[in]  p_ctrl      Pointer to control structure.
     * @param[in]  state       Pull-up enable/disable setting.
     */
    fsp_err_t (* pullUp)(usb_ctrl_t * const p_ctrl, uint8_t state);

    /** Performs settings and transmission processing when transmitting a setup packet.
     *
     * @param[in]     p_ctrl         USB control structure.
     * @param[in]     p_setup        Setup packet information.
     * @param[in]     p_buf          Transfer area information.
     * @param[in]     device_address Device address information.
     */
    fsp_err_t (* hostControlTransfer)(usb_ctrl_t * const p_ctrl, usb_setup_t * p_setup, uint8_t * p_buf,
                                      uint8_t device_address);

    /** Receives data sent by control transfer.
     *
     * @param[in]     p_ctrl      USB control structure.
     * @param[in]     p_buf       Data reception area information.
     * @param[in]     size        Data reception size information.
     */
    fsp_err_t (* periControlDataGet)(usb_ctrl_t * const p_ctrl, uint8_t * p_buf, uint32_t size);

    /** Performs transfer processing for control transfer.
     *
     * @param[in]     p_ctrl      USB control structure.
     * @param[in]     p_buf       Area information for data transfer.
     * @param[in]     size        Transfer size information.
     */
    fsp_err_t (* periControlDataSet)(usb_ctrl_t * const p_ctrl, uint8_t * p_buf, uint32_t size);

    /** Set the response to the setup packet.
     *
     * @param[in]     p_ctrl      USB control structure.
     * @param[in]     status      USB port startup information.
     */
    fsp_err_t (* periControlStatusSet)(usb_ctrl_t * const p_ctrl, usb_setup_status_t status);

    /** Sends a remote wake-up signal to the connected Host.
     *
     * @param[in]     p_ctrl      USB control structure.
     */
    fsp_err_t (* remoteWakeup)(usb_ctrl_t * const p_ctrl);

    /** Activate USB Driver
     *
     * @param[in]     p_api_ctrl  USB control structure.
     */
    fsp_err_t (* driverActivate)(usb_ctrl_t * const p_api_ctrl);

    /** Set callback memory to USB driver.
     *
     * @param[in]     p_api_ctrl  USB control structure.
     * @param[in]     p_callback_memory  Pointer to store USB event information.
     */
    fsp_err_t (* callbackMemorySet)(usb_ctrl_t * const p_api_ctrl, usb_callback_args_t * p_callback_memory);

    /** This API gets the module number.
     *
     * @param[in]  p_ctrl           USB control structure.
     * @param[out] module_number    Module number to get.
     */
    fsp_err_t (* moduleNumberGet)(usb_ctrl_t * const p_ctrl, uint8_t * module_number);

    /** This API gets the module number.
     *
     * @param[in]  p_ctrl           USB control structure.
     * @param[out] class_type       Class type to get.
     */
    fsp_err_t (* classTypeGet)(usb_ctrl_t * const p_ctrl, usb_class_t * class_type);

    /** This API gets the device address.
     *
     * @param[in]  p_ctrl           USB control structure.
     * @param[out] device_address   Device address to get.
     */
    fsp_err_t (* deviceAddressGet)(usb_ctrl_t * const p_ctrl, uint8_t * device_address);

    /** This API gets the pipe number.
     *
     * @param[in]  p_ctrl           USB control structure.
     * @param[out] pipe_number      Pipe number to get.
     */
    fsp_err_t (* pipeNumberGet)(usb_ctrl_t * const p_ctrl, uint8_t * pipe_number);

    /** This API gets the state of the device.
     *
     * @param[in]  p_ctrl           USB control structure.
     * @param[out] state            Device state to get.
     */
    fsp_err_t (* deviceStateGet)(usb_ctrl_t * const p_ctrl, uint16_t * state);

    /** This API gets the data size.
     *
     * @param[in]  p_ctrl           USB control structure.
     * @param[out] data_size        Data size to get.
     */
    fsp_err_t (* dataSizeGet)(usb_ctrl_t * const p_ctrl, uint32_t * data_size);

    /** This API gets the setup type.
     *
     * @param[in]  p_ctrl           USB control structure.
     * @param[out] setup            Setup type to get.
     */
    fsp_err_t (* setupGet)(usb_ctrl_t * const p_ctrl, usb_setup_t * setup);

    /** This API sets the callback function for OTG.
     *
     * @param[in]  p_ctrl           USB control structure.
     * @param[in]  p_callback       Pointer to the callback function for OTG.
     */
    fsp_err_t (* otgCallbackSet)(usb_ctrl_t * const p_ctrl, usb_otg_callback_t * p_callback);

    /** This API starts SRP processing for OTG.
     *
     * @param[in]  p_ctrl           USB control structure.
     */
    fsp_err_t (* otgSRP)(usb_ctrl_t * const p_ctrl);

    /** Get information on USB Type-C Connection.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_info       Pointer to usb_typec_info_t structure area.
     */
    fsp_err_t (* typecInfoGet)(usb_ctrl_t * const p_ctrl, usb_typec_info_t * p_info);

} usb_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_usb_instance
{
    usb_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    usb_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    usb_api_t const * p_api;           ///< Pointer to the API structure for this instance
} usb_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_API_H */

/*******************************************************************************************************************//**
 * @} (end defgroup USB_API)
 **********************************************************************************************************************/
