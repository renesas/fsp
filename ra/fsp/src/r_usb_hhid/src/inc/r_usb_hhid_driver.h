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

#ifndef R_USB_HHID_DRIVER_H
#define R_USB_HHID_DRIVER_H

#include "r_usb_basic.h"
#include "../../../r_usb_basic/src/driver/inc/r_usb_typedef.h" /* type define */

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*****************************************************************************
 * Macro definitions
 ******************************************************************************/

/* ----- DESCRIPTOR Types ----- */
#define USB_HID_DT_TYPE_GETREPORT        ((uint8_t) 0x01) /* Report Type Input */
#define USB_HID_DT_TYPE_SETREPORT        ((uint8_t) 0x02) /* Report Type Output */
#define USB_HID_DT_TYPE_HIDDESCRIPTOR    ((uint8_t) 0x21) /* HID descriptor type */
#define USB_HID_DT_TYPE_RPTDESCRIPTOR    ((uint8_t) 0x22) /* Report descriptor type */

/* ----- Subclass Codes ----- */
#define USB_HID_IFSUB_NONE               ((uint8_t) 0x00) /* No Subclass */
#define USB_HID_IFSUB_BOOT               ((uint8_t) 0x01) /* Boot Interface Subclass */

/* Report Type set */
#define USB_HID_SET_DT_TYPE(v)    ((v) << 8)

#define USB_HHID_CLSDATASIZE             (512)
#define USB_MAX_DEVICE                   (3) /* 1-3 */

#if (BSP_CFG_RTOS)

/* Host HID Task */
 #define USB_HHID_TSK                    (USB_TID_9)    /* Task ID */
 #define USB_HHID_MBX                    (USB_HHID_TSK) /* Mailbox ID */
 #define USB_HHID_MPL                    (USB_HHID_TSK) /* Memorypool ID */
#else /* (BSP_CFG_RTOS) */
/* Host HID Task */
 #define USB_HHID_TSK                    (USB_TID_7)    /* Task ID */
 #define USB_HHID_MBX                    (USB_HHID_TSK) /* Mailbox ID */
 #define USB_HHID_MPL                    (USB_HHID_TSK) /* Memorypool ID */
#endif /* (BSP_CFG_RTOS) */

#define USB_B_INTERFACE_PROTOCOL         (7)            /* Interface Descriptor bInterfaceProtocol */
#define USB_VALUE_FFH                    (0xFF)
#define USB_VALUE_3000                   (3000)

/*****************************************************************************
 * Enumerated Types
 ******************************************************************************/

/* Host HID Task Command */
typedef enum
{
    USB_HHID_TCMD_OPEN
} usb_hhid_tcmd_t;

/* Enumeration Sequence */
typedef enum
{
    /* Enumeration Sequence Complete */
    USB_HHID_ENUM_COMPLETE = 0,

    /* Enumeration Sequence String Descriptor #0 receive request */
    USB_HHID_ENUM_STR_DT0_REQ,

    /* Enumeration Sequence String Descriptor #0 Receive complete */
    USB_HHID_ENUM_STR_DT0_WAIT,

    /* StringDescriptor iProduct Receive complete */
    USB_HHID_ENUM_STR_IPRODUCT_WAIT
} usb_hhid_enum_seq_t;

/*****************************************************************************
 * Struct definition
 ******************************************************************************/

/******************************************************************************
 * Exported global variables
 ******************************************************************************/
extern uint16_t  g_usb_hhid_protocol[USB_NUM_USBIP][USB_MAXDEVADDR];        /* HID Device protocol(Mouse/Keyboard) */
extern uint16_t  g_usb_hhid_num_endpoint[USB_NUM_USBIP][USB_MAXDEVADDR];    /* Num Endpoints */
extern uint16_t  g_usb_hhid_outpipe_support[USB_NUM_USBIP][USB_MAXDEVADDR]; /* OUT pipe support */
extern uint16_t  g_usb_hhid_devaddr[];                                      /* Device Address */
extern uint16_t  g_usb_hhid_speed[];                                        /* Device speed */
extern uint16_t  g_usb_hhid_enum_seq[];                                     /* Enumeration Sequence */
extern uint8_t * g_p_usb_hhid_interface_table[];                            /* Interface Descriptor Table */
extern uint8_t * g_p_usb_hhid_device_table[];                               /* Device Descriptor Table */
extern uint8_t * g_p_usb_hhid_config_table[];                               /* Configuration Descriptor Table */

/*****************************************************************************
 * Public Functions
 ******************************************************************************/

/* Functions */
uint16_t usb_hhid_pipe_info(usb_utr_t * ptr, uint8_t * table, uint16_t speed, uint16_t length);
uint16_t usb_hhid_get_string_desc(usb_utr_t * ptr, uint16_t addr, uint16_t string, usb_cb_t complete);
void     usb_hid_suspended(usb_utr_t * ptr, uint16_t devadr);
void     usb_hid_configured(usb_utr_t * ptr, uint16_t devadr, uint16_t data2);
void     usb_hid_detach(usb_utr_t * ptr, uint16_t devadr, uint16_t data2);
void     usb_hid_resume_complete(usb_utr_t * ptr, uint16_t devadr, uint16_t data2);

uint8_t usb_hhid_get_hid_protocol(uint16_t ipno, uint16_t devadr);
void    usb_hhid_set_pipe_registration(usb_utr_t * ptr, uint16_t devadr);
void    usb_hhid_class_check(usb_utr_t * ptr, uint16_t ** table);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_HHID_DRIVER_H */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
