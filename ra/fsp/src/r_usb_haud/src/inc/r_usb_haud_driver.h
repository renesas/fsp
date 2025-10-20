/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#ifndef R_USB_HAUD_H
 #define R_USB_HAUD_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

 #ifdef __cplusplus
extern "C" {
 #endif

/*****************************************************************************
 * Macro definitions
 ******************************************************************************/

/* Host Sample Task */
 #if (BSP_CFG_RTOS_USED == 0)
  #define USB_HAUD_TSK                 (USB_TID_6)    /* Task ID */
  #define USB_HAUD_MBX                 (USB_HAUD_TSK) /* Mailbox ID */
  #define USB_HAUD_MPL                 (USB_HAUD_TSK) /* Memorypool ID */
 #else
  #define USB_HAUD_TSK                 (USB_TID_8)    /* Task ID */
  #define USB_HAUD_MBX                 (USB_HAUD_TSK) /* Mailbox ID */
  #define USB_HAUD_MPL                 (USB_HAUD_TSK) /* Memorypool ID */
 #endif /* (BSP_CFG_RTOS_USED == 0) */
 #define USB_MAX_CONNECT_DEVICE_NUM    (2U)           /* 1-2 */
 #define USB_MAX_WLANGID_NUM           (32U)          /* Max Index Num of wLANGID. */

/******************************************************************************
 * Exported global variables
 ******************************************************************************/
extern uint8_t * g_p_usb_haud_device_table[];
extern uint8_t * g_p_usb_haud_config_table[];
extern uint8_t * g_p_usb_haud_interface_table[];
extern uint16_t  g_usb_haud_speed[];
extern uint16_t  g_usb_haud_devaddr[];

extern void usb_haud_configured(usb_utr_t * ptr, uint16_t devadr, uint16_t data2);
extern void usb_haud_detach(usb_utr_t * ptr, uint16_t devadr, uint16_t data2);

extern void usb_haud_class_check(usb_utr_t * ptr, uint16_t ** table);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* R_USB_HAUD_H */

/******************************************************************************
 * End Of File
 ******************************************************************************/
