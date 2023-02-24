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
#ifndef R_USB_HCDC_H
 #define R_USB_HCDC_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

 #ifdef __cplusplus
extern "C" {
 #endif

/*****************************************************************************
 * Macro definitions
 ******************************************************************************/

/* CDC Transfer data size */
 #define     USB_HCDC_EP_OFFSET_DATA    (0) /* Ep Table Bulk Pipe offset */
 #define     USB_HCDC_EP_OFFSET_CTL     (2) /* Ep Table Int Pipe offset */

 #define     USB_NOPIPE                 ((uint8_t) 0xFF)

/* Host Sample Task */
 #if (BSP_CFG_RTOS_USED == 0)
  #define USB_HCDC_TSK                  (USB_TID_6)    /* Task ID */
  #define USB_HCDC_MBX                  (USB_HCDC_TSK) /* Mailbox ID */
  #define USB_HCDC_MPL                  (USB_HCDC_TSK) /* Memorypool ID */
 #else
  #define USB_HCDC_TSK                  (USB_TID_8)    /* Task ID */
  #define USB_HCDC_MBX                  (USB_HCDC_TSK) /* Mailbox ID */
  #define USB_HCDC_MPL                  (USB_HCDC_TSK) /* Memorypool ID */
 #endif /* (BSP_CFG_RTOS_USED == 0) */
 #define USB_MAX_CONNECT_DEVICE_NUM     (2U)           /* 1-2 */
 #define USB_MAX_WLANGID_NUM            (32U)          /* Max Index Num of wLANGID. */

/******************************************************************************
 * Exported global variables
 ******************************************************************************/
extern uint8_t  * g_p_usb_hcdc_device_table[];
extern uint8_t  * g_p_usb_hcdc_config_table[];
extern uint8_t  * g_p_usb_hcdc_interface_table[];
extern uint16_t   g_usb_hcdc_speed[];
extern uint16_t   g_usb_hcdc_devaddr[];
extern int16_t    g_usb_hcdc_smpl_class_seq[];
extern uint16_t * g_p_usb_hcdc_pipe_table[];

extern void usb_hcdc_configured(usb_utr_t * ptr, uint16_t devadr, uint16_t data2);
extern void usb_hcdc_detach(usb_utr_t * ptr, uint16_t devadr, uint16_t data2);

extern usb_er_t usb_hcdc_set_pipe_registration(usb_utr_t * ptr, uint16_t dev_addr);
extern void     usb_hcdc_class_check(usb_utr_t * ptr, uint16_t ** table);

/******************************************************************************
 * Exported global functions (to be accessed by other files)
 ******************************************************************************/

void     usb_hcdc_enumeration(usb_clsinfo_t * mess);
uint16_t usb_hcdc_pipe_info(usb_utr_t * ptr, uint8_t * table, uint16_t speed, uint16_t length);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* R_USB_HCDC_H */

/******************************************************************************
 * End Of File
 ******************************************************************************/
