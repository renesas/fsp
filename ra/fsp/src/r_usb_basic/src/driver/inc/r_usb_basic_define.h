/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#ifndef R_USB_BASIC_DEFINE_H
 #define R_USB_BASIC_DEFINE_H

 #include "r_usb_basic_cfg.h"

 #define USB_CFG_LITTLE     (0U)
 #define USB_CFG_BIG        (1U)

 #define USB_NOT_SUPPORT    (0U)
 #define USB_FS_MODULE      (1U)
 #define USB_HS_MODULE      (2U)

 #define USB_CFG_ENDIAN     (USB_CFG_LITTLE)

 #if defined(USB_DEBUG_ON)
  #include    <stdlib.h>               /* @@@MISRA del */
  #include    <stdio.h>                /* @@@MISRA del */
 #endif /* defined(USB_DEBUG_ON) */

 #ifdef __cplusplus
extern "C" {
 #endif

 #define R_USB_HmscTask    usb_hmsc_task

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #if (BSP_FEATURE_USB_HAS_USBFS == 1) && (BSP_FEATURE_USB_HAS_USBHS == 1)

  #define USB_HIGH_SPEED_MODULE
  #define USB_IP0_MODULE                        USB_FS_MODULE
  #define USB_IP1_MODULE                        USB_HS_MODULE

  #define USB_NUM_USBIP                         (2U)

 #endif

 #if (BSP_FEATURE_USB_HAS_USBFS == 1) && (BSP_FEATURE_USB_HAS_USBHS == 0)
  #define USB_IP0_MODULE                        USB_FS_MODULE
  #define USB_IP1_MODULE                        USB_NOT_SUPPORT

  #define USB_NUM_USBIP                         (1U)
 #endif

 #if defined(__CM23_REV)

  #define USB_UNALIGNED_MEMORY_ACCESS_NG_MCU /* Coretex M23 etc */

 #endif

 #if (BSP_FEATURE_USB_HAS_PIPE04567 == 1)

  #define USB_SUPPORT_MINI_MODULE

 #endif

 #if (BSP_FEATURE_USB_HAS_NOT_HOST == 1)

  #define USB_NOT_SUPPORT_HOST

 #endif

 #if (BSP_FEATURE_USB_HAS_USBLS_PERI == 1)

  #define USB_SUPPORT_PERI_LS          /* USB Peripheral Low-speed Support Module */

 #endif

 #if (BSP_FEATURE_USB_REG_UCKSEL_UCKSELC == 1)

  #define USB_SUPPORT_HOCO_MODULE      /* UCKSELC bit */

 #endif

 #if (BSP_FEATURE_USB_REG_USBMC_VDCEN == 1)

  #define USB_LDO_REGULATOR_MODULE     /* VDCEN bit */

 #endif

 #if (BSP_FEATURE_USB_REG_USBMC_VDDUSBE == 1)

  #define USB_SUPPORT_VDDUSBE          /* VDDUSBE bit */

 #endif

 #if (BSP_FEATURE_USB_REG_PHYSLEW == 1)

  #define USB_SUPPORT_PHYSLEW          /* PHYSLEW bit */
  #define USB_PHYSLEW_VALUE      BSP_FEATURE_USB_REG_PHYSLEW_VALUE

 #endif

 #if (BSP_FEATURE_USB_HAS_USBHS_BC == 1)

  #define BSP_FEATURE_USBHS_REG_SYSCFG_CNEN /* CNEN bit */
  #define USB_SUPPORT_BC_HS                 /* Battery Charging in High-speed module */

 #endif

 #if (BSP_FEATURE_USB_HAS_USBFS_BC == 1)

  #define USB_SUPPORT_BC_FS            /* Battery Charging in Full-speed module*/

 #endif

 #if (BSP_FEATURE_USB_REG_PHYSECTRL_CNEN == 1)

  #define USB_CNEN_PHYSECTRL_USB_IP0   /* CNEN bit */

 #endif

 #if (BSP_FEATURE_USB_HAS_TYPEC == 1)

  #define USB_SUPPORT_TYPEC            /* USB Type-C Support Module */

 #endif

/* Version Number of API. */
 #define USB_VERSION_MAJOR        (1)
 #define USB_VERSION_MINOR        (0)

 #define CLSDATASIZE              (512U) /* Transfer data size for Standard Request */
 #if (BSP_CFG_RTOS != 0)

/* The buffer size of interrupt info is increased to avoid overlapping interrupt events. */
  #define USB_INT_BUFSIZE         (8U)   /* Size of Interrupt info buffer */
 #else /* #if (BSP_CFG_RTOS != 0) */
  #define USB_INT_BUFSIZE         (8U)   /* Size of Interrupt info buffer */
 #endif /* #if (BSP_CFG_RTOS != 0) */
 #define USB_EVENT_MAX            (10)

/* Scheduler use define */
 #define USB_TBLCLR               (0U)          /* Table clear */
 #define USB_CNTCLR               (0U)          /* Counter clear */
 #define USB_FLGCLR               (0U)          /* Flag clear */
 #define USB_FLGSET               (1U)          /* Flag set */
 #define USB_IDCLR                (0xFFU)       /* Priority clear */

/* Task ID define */
 #define USB_TID_0                (0U)          /* Task ID 0 */
 #define USB_TID_1                (1U)          /* Task ID 1 */
 #define USB_TID_2                (2U)          /* Task ID 2 */
 #define USB_TID_3                (3U)          /* Task ID 3 */
 #define USB_TID_4                (4U)          /* Task ID 4 */
 #define USB_TID_5                (5U)          /* Task ID 5 */
 #define USB_TID_6                (6U)          /* Task ID 6 */
 #define USB_TID_7                (7U)          /* Task ID 7 */
 #define USB_TID_8                (8U)          /* Task ID 8 */
 #define USB_TID_9                (9U)          /* Task ID 9 */
 #define USB_TID_10               (10U)         /* Task ID 9 */

/* Task priority define */
 #define USB_PRI_0                (0U)          /* Priority 0 */
 #define USB_PRI_1                (1U)          /* Priority 1 */
 #define USB_PRI_2                (2U)          /* Priority 2 */
 #define USB_PRI_3                (3U)          /* Priority 3 */
 #define USB_PRI_4                (4U)          /* Priority 4 */
 #define USB_PRI_5                (5U)          /* Priority 5 */
 #define USB_PRI_6                (6U)          /* Priority 6 */

/* Host Control Driver Task */
 #define USB_HCD_TSK              (USB_TID_1)   /* Task ID */
 #define USB_HCD_MBX              (USB_HCD_TSK) /* Mailbox ID */
 #define USB_HCD_MPL              (USB_HCD_TSK) /* Memory pool ID */

/* Host Manager Task */
 #define USB_MGR_TSK              (USB_TID_2)   /* Task ID */
 #define USB_MGR_MBX              (USB_MGR_TSK) /* Mailbox ID */
 #define USB_MGR_MPL              (USB_MGR_TSK) /* Memory pool ID */

/* Hub Task */
 #define USB_HUB_TSK              (USB_TID_3)   /* Task ID */
 #define USB_HUB_MBX              (USB_HUB_TSK) /* Mailbox ID */
 #define USB_HUB_MPL              (USB_HUB_TSK) /* Memory pool ID */

 #if (BSP_CFG_RTOS != 0)

/* Class Request for Internal Communication  */
  #define USB_CLS_TSK             (USB_TID_4)   /* Task ID */
  #define USB_CLS_MBX             (USB_CLS_TSK) /* Mailbox ID */
  #define USB_CLS_MPL             (USB_CLS_TSK) /* Memory pool ID */

/* Peripheral Control Driver Task */
  #define USB_PCD_TSK             (USB_TID_5)   /* Task ID */
  #define USB_PCD_MBX             (USB_PCD_TSK) /* Mailbox ID */
 #endif /* #if (BSP_CFG_RTOS != 0) */

/* Error discrimination */
 #define USB_DEBUG_HOOK_HWR       (0x0100)
 #define USB_DEBUG_HOOK_HOST      (0x0200)
 #define USB_DEBUG_HOOK_PERI      (0x0400)
 #define USB_DEBUG_HOOK_STD       (0x0800)
 #define USB_DEBUG_HOOK_CLASS     (0x1000)
 #define USB_DEBUG_HOOK_APL       (0x2000)

/* Error Code */
 #define USB_DEBUG_HOOK_CODE1     (0x0001)
 #define USB_DEBUG_HOOK_CODE2     (0x0002)
 #define USB_DEBUG_HOOK_CODE3     (0x0003)
 #define USB_DEBUG_HOOK_CODE4     (0x0004)
 #define USB_DEBUG_HOOK_CODE5     (0x0005)
 #define USB_DEBUG_HOOK_CODE6     (0x0006)
 #define USB_DEBUG_HOOK_CODE7     (0x0007)
 #define USB_DEBUG_HOOK_CODE8     (0x0008)
 #define USB_DEBUG_HOOK_CODE9     (0x0009)
 #define USB_DEBUG_HOOK_CODE10    (0x000A)
 #define USB_DEBUG_HOOK_CODE11    (0x000B)
 #define USB_DEBUG_HOOK_CODE12    (0x000C)
 #define USB_DEBUG_HOOK_CODE13    (0x000D)
 #define USB_DEBUG_HOOK_CODE14    (0x000E)
 #define USB_DEBUG_HOOK_CODE15    (0x000F)

 #ifdef USB_DEBUG_HOOK_USE
  #define USB_DEBUG_HOOK(x)    (usb_cstd_debug_hook(x))
 #else
  #define USB_DEBUG_HOOK(x)
 #endif

/* H/W function type */
 #define USB_BIT0                               ((uint16_t) 0x0001)
 #define USB_BIT1                               ((uint16_t) 0x0002)
 #define USB_BIT2                               ((uint16_t) 0x0004)
 #define USB_BIT3                               ((uint16_t) 0x0008)
 #define USB_BIT4                               ((uint16_t) 0x0010)
 #define USB_BIT5                               ((uint16_t) 0x0020)
 #define USB_BIT6                               ((uint16_t) 0x0040)
 #define USB_BIT7                               ((uint16_t) 0x0080)
 #define USB_BIT8                               ((uint16_t) 0x0100)
 #define USB_BIT9                               ((uint16_t) 0x0200)
 #define USB_BIT10                              ((uint16_t) 0x0400)
 #define USB_BIT11                              ((uint16_t) 0x0800)
 #define USB_BIT12                              ((uint16_t) 0x1000)
 #define USB_BIT13                              ((uint16_t) 0x2000)
 #define USB_BIT14                              ((uint16_t) 0x4000)
 #define USB_BIT15                              ((uint16_t) 0x8000)
 #define USB_BITSET(x)    ((uint16_t) ((uint16_t) 1 << (x)))

/* nonOS Use */
 #define USB_SEQ_0                              ((uint16_t) 0x0000)
 #define USB_SEQ_1                              ((uint16_t) 0x0001)
 #define USB_SEQ_2                              ((uint16_t) 0x0002)
 #define USB_SEQ_3                              ((uint16_t) 0x0003)
 #define USB_SEQ_4                              ((uint16_t) 0x0004)
 #define USB_SEQ_5                              ((uint16_t) 0x0005)
 #define USB_SEQ_6                              ((uint16_t) 0x0006)
 #define USB_SEQ_7                              ((uint16_t) 0x0007)
 #define USB_SEQ_8                              ((uint16_t) 0x0008)
 #define USB_SEQ_9                              ((uint16_t) 0x0009)
 #define USB_SEQ_10                             ((uint16_t) 0x000a)

/* USB HUB PIPE No. */
 #define USB_HUB_PIPE                           (9U)

 #define USB_HUB_P1                             ((uint16_t) 0x0001)
 #define USB_HUB_P2                             ((uint16_t) 0x0002)
 #define USB_HUB_P3                             ((uint16_t) 0x0003)
 #define USB_HUB_P4                             ((uint16_t) 0x0004)

 #define USB_HUB                                (USB_CLASS_REQUEST + 1)

/* Interrupt message num */
 #define USB_INTMSGMAX                          ((uint16_t) 15U)

/* USB Device Connect */
 #define USB_DEV_NO_CONNECT                     ((uint16_t) 0U)
 #define USB_DEV_CONNECTED                      ((uint16_t) 1U)

 #define USB_OK                                 (0U)
 #define USB_ERROR                              (0xff)
 #define USB_ERR_TMOUT                          (0xfe)
 #define USB_ERR_FIFO_ACCESS                    (0xfd)
 #define USB_QOVR                               (0xd5) /* Submit overlap error */
 #define USB_PAR                                (0xef) /* parameter error */

 #define USB_TRUE                               (1U)
 #define USB_FALSE                              (0U)

 #define USB_YES                                (1U)
 #define USB_NO                                 (0U)

 #define USB_CFG_HIGH                           (0U)
 #define USB_CFG_LOW                            (1U)

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/* USB module definition */
 #define USB_M0                                 (R_USB_FS0)

 #ifdef  R_USB_HS0
  #define USB_M1                                (R_USB_HS0)
 #else                                 /* R_USB_HS0 */
  #ifndef R_USB_HS0_BASE
   #define R_USB_HS0_BASE                       (0x40060000)
  #endif /* R_USB_HS0_BASE */

  #define USB_M1                                (((R_USB_FS0_Type *) R_USB_HS0_BASE))
 #endif                                /* R_USB_HS0 */

/* FIFO port register default access size */
 #define USB0_CFIFO_MBW                         (USB_MBW_16)
 #define USB0_D0FIFO_MBW                        (USB_MBW_16)
 #define USB0_D1FIFO_MBW                        (USB_MBW_16)

 #define USB1_CFIFO_MBW                         (USB_MBW_32)
 #define USB1_D0FIFO_MBW                        (USB_MBW_32)
 #define USB1_D1FIFO_MBW                        (USB_MBW_32)

/* Start Pipe No */
 #if defined(USB_SUPPORT_MINI_MODULE)
  #define USB_MIN_PIPE_NO                       (4U)
  #define USB_MAXPIPE_BULK                      (5U)
  #define USB_BULK_PIPE_START                   (4U)
  #define USB_INT_PIPE_END                      (7U)
  #define USB_MAX_PIPE_NO                       (7U) /* PIPE4 ... PIPE7 */
 #else  /* defined(USB_MINI_MODULE_DMAC) || defined(USB_MINI_MODULE_NO_DMAC) */
  #define USB_MIN_PIPE_NO                       (1U)
  #define USB_MAXPIPE_BULK                      (5U)
  #define USB_BULK_PIPE_START                   (1U)
  #define USB_INT_PIPE_END                      (9U)
  #define USB_MAX_PIPE_NO                       (9U) /* PIPE0 ... PIPE9 */
 #endif /* defined(USB_MINI_MODULE_DMAC) || defined(USB_MINI_MODULE_NO_DMAC) */

 #define USB_MAXPIPE_NUM                        (9U)
 #define USB_INT_PIPE_START                     (6U)
 #define USB_BULK_PIPE_END                      (5U)

 #define USB_ISO_PIPE_START                     (1U)
 #define USB_ISO_PIPE_END                       (2U)
 #define USB_MAXPIPE_ISO                        (2U)

/* SPEED mode */
 #define USB_HS_DISABLE                         ((uint16_t) 0U)
 #define USB_HS_ENABLE                          ((uint16_t) 1U)

 #define USBA_ADDRESS_OFFSET                    (0x0010)
 #define USB_ADDRESS_MASK                       (0x000f)
 #define USB_IP_MASK                            (0x00f0)

/* USB Device address define */
 #define USB_DEVICEADDR                         (1U) /* PORT0 USB Address (1 to 10) */

/* HUB Address */
 #define USB_HUBDPADDR                          ((uint16_t) (USB_DEVICEADDR + 1U))

 #define USB_PIPE_DIR_IN                        (0U)
 #define USB_PIPE_DIR_OUT                       (1U)
 #define USB_PIPE_DIR_MAX                       (2U)

 #define USB_CFG_ENABLE                         (1U)
 #define USB_CFG_DISABLE                        (0U)

 #define USB_CFG_IP0                            (0)
 #define USB_CFG_IP1                            (1)
 #define USB_CFG_MULTI                          (2)

 #define USB_CFG_HOST                           (1)
 #define USB_CFG_PERI                           (2)

 #define USB_CFG_CDC                            (0)
 #define USB_CFG_VEN                            (1)

 #define USB_CFG_24MHZ                          (0)
 #define USB_CFG_20MHZ                          (1)
 #define USB_CFG_OTHER                          (2)
 #define USB_CFG_12MHZ                          (3)
 #define USB_CFG_48MHZ                          (4)

/* Channel Number */
 #define USB_CFG_CH0                            (0U)
 #define USB_CFG_CH1                            (1U)
 #define USB_CFG_CH2                            (2U)
 #define USB_CFG_CH3                            (3U)
 #define USB_CFG_CH4                            (4U)
 #define USB_CFG_CH5                            (5U)
 #define USB_CFG_CH6                            (6U)
 #define USB_CFG_CH7                            (7U)

/* Bus Wait */
 #define USB_CFG_BUSWAIT_0                      (USB_BWAIT_0)
 #define USB_CFG_BUSWAIT_1                      (USB_BWAIT_1)
 #define USB_CFG_BUSWAIT_2                      (USB_BWAIT_2)
 #define USB_CFG_BUSWAIT_3                      (USB_BWAIT_3)
 #define USB_CFG_BUSWAIT_4                      (USB_BWAIT_4)
 #define USB_CFG_BUSWAIT_5                      (USB_BWAIT_5)
 #define USB_CFG_BUSWAIT_6                      (USB_BWAIT_6)
 #define USB_CFG_BUSWAIT_7                      (USB_BWAIT_7)
 #define USB_CFG_BUSWAIT_8                      (USB_BWAIT_8)
 #define USB_CFG_BUSWAIT_9                      (USB_BWAIT_9)
 #define USB_CFG_BUSWAIT_10                     (USB_BWAIT_10)
 #define USB_CFG_BUSWAIT_11                     (USB_BWAIT_11)
 #define USB_CFG_BUSWAIT_12                     (USB_BWAIT_12)
 #define USB_CFG_BUSWAIT_13                     (USB_BWAIT_13)
 #define USB_CFG_BUSWAIT_14                     (USB_BWAIT_14)
 #define USB_CFG_BUSWAIT_15                     (USB_BWAIT_15)

 #define USB_CFG_USE                            (0U)
 #define USB_CFG_NOUSE                          (0xFFFFU)

 #define USB_CFG_ON                             (1U)
 #define USB_CFG_OFF                            (0U)

 #define USB_CFG_FS                             (1)
 #define USB_CFG_HS                             (2)

/******************************************************************************
 * USB specification define
 ******************************************************************************/

/* Standard Device Descriptor Define */
 #define USB_DEV_B_LENGTH                       (0U)    /* Size of descriptor */
 #define USB_DEV_B_DESCRIPTOR_TYPE              (1U)    /* Descriptor type */
 #define USB_DEV_BCD_USB_L                      (2U)    /* USB Specification Release Number */
 #define USB_DEV_BCD_USB_H                      (3U)    /* USB Specification Release Number */
 #define USB_DEV_B_DEVICE_CLASS                 (4U)    /* Class code */
 #define USB_DEV_B_DEVICE_SUBCLASS              (5U)    /* Subclass code */
 #define USB_DEV_B_DEVICE_PROTOCOL              (6U)    /* Protocol code */
 #define USB_DEV_B_MAX_PACKET_SIZE_0            (7U)    /* Max packet size for EP0(only 8,16,32,64 are valid) */
 #define USB_DEV_ID_VENDOR_L                    (8U)    /* Vendor ID */
 #define USB_DEV_ID_VENDOR_H                    (9U)    /* Vendor ID */
 #define USB_DEV_ID_PRODUCT_L                   (10U)   /* Product ID */
 #define USB_DEV_ID_PRODUCT_H                   (11U)   /* Product ID */
 #define USB_DEV_BCD_DEVICE_L                   (12U)   /* Device release number */
 #define USB_DEV_BCD_DEVICE_H                   (13U)   /* Device release number */
 #define USB_DEV_I_MANUFACTURER                 (14U)   /* Index of string descriptor describing manufacturer */
 #define USB_DEV_I_PRODUCT                      (15U)   /* Index of string descriptor describing product */
 #define USB_DEV_I_SERIAL_NUMBER                (16U)   /* Device serial number */
 #define USB_DEV_B_NUM_CONFIGURATION            (17U)   /* Number of possible configuration */

/* Standard Configuration Descriptor Define */
 #define USB_DEV_W_TOTAL_LENGTH_L               (2U)    /* Total length of data returned for this configuration */
 #define USB_DEV_W_TOTAL_LENGTH_H               (3U)    /* Total length of data returned for this configuration */
 #define USB_DEV_B_NUM_INTERFACES               (4U)    /* Number of interfaces supported by this configuration */
 #define USB_DEV_B_CONFIGURATION_VALUE          (5U)    /* Configuration value */
 #define USB_DEV_I_CONFIGURATION                (6U)    /* Index of string descriptor describing this configuration */
 #define USB_DEV_BM_ATTRIBUTES                  (7U)    /* Configuration characteristics */
 #define USB_DEV_B_MAX_POWER                    (8U)    /* Max power consumption of the USB device from the bus */

/* Endpoint Descriptor  Define */
 #define USB_EP_DIRMASK                         (0x80U) /* Endpoint direction mask [2] */
 #define USB_EP_NUMMASK                         (0x0FU) /* Endpoint number mask [2] */
 #define USB_EP_USGMASK                         (0x30U) /* Usage type mask [2] */
 #define USB_EP_SYNCMASK                        (0x0CU) /* Synchronization type mask [2] */
 #define USB_EP_TRNSMASK                        (0x03U) /* Transfer type mask [2] */
 #define USB_EP_CNTRL                           (0x00U) /* Control Transfer */

 #define USB_EP_B_LENGTH                        (0U)    /* Size of descriptor */
 #define USB_EP_B_DESCRIPTORTYPE                (1U)    /* Descriptor type */
 #define USB_EP_B_ENDPOINTADDRESS               (2U)    /* Endpoint No. , Dir */
 #define USB_EP_B_ATTRIBUTES                    (3U)    /* Transfer Type */
 #define USB_EP_B_MAXPACKETSIZE_L               (4U)    /* Max packet size */
 #define USB_EP_B_MAXPACKETSIZE_H               (5U)    /* Max packet size */
 #define USB_EP_B_INTERVAL                      (6U)    /* Interval */

/* Standard Interface Descriptor Offset Define */
 #define USB_IF_B_INTERFACENUMBER               (2U)    /* bInterfaceNumber */
 #define USB_IF_B_ALTERNATESETTING              (3U)    /* bAlternateSetting */
 #define USB_IF_B_NUMENDPOINTS                  (4U)    /* bNumEndpoints */
 #define USB_IF_B_INTERFACECLASS                (5U)    /* bInterfaceClass */
 #define USB_IF_B_INTERFACESUBCLASS             (6U)    /* bInterfaceSubClass @@*/
 #define USB_IF_B_INTERFACEPROTOCOL             (7U)    /* bInterfacePtorocol */
 #define USB_IF_I_INTERFACE                     (8U)    /* iInterface */

/* GET_STATUS request information */
/* Standard Device status */
 #define USB_GS_BUSPOWERD                       (0x0000U)
 #define USB_GS_SELFPOWERD                      (0x0001U)
 #define USB_GS_REMOTEWAKEUP                    (0x0002U)

/* Endpoint status */
 #define USB_GS_NOTHALT                         (0x0000U)
 #define USB_GS_HALT                            (0x0001U)

/* CLEAR_FEATURE/GET_FEATURE/SET_FEATURE request information */
/* Standard Feature Selector */
 #define USB_ENDPOINT_HALT                      (0x0000U)
 #define USB_DEV_REMOTE_WAKEUP                  (0x0001U)
 #define USB_TEST_MODE                          (0x0002U)

/* GET_DESCRIPTOR/SET_DESCRIPTOR request information */
/* Standard Descriptor type */
 #define USB_HUB_DESCRIPTOR                     (0x0000U)
 #define USB_DEV_DESCRIPTOR                     (0x0100U)
 #define USB_CONF_DESCRIPTOR                    (0x0200U)
 #define USB_STRING_DESCRIPTOR                  (0x0300U)
 #define USB_INTERFACE_DESCRIPTOR               (0x0400U)
 #define USB_ENDPOINT_DESCRIPTOR                (0x0500U)
 #define USB_DEV_QUALIFIER_DESCRIPTOR           (0x0600U)
 #define USB_OTHER_SPEED_CONF_DESCRIPTOR        (0x0700U)
 #define USB_INTERFACE_POWER_DESCRIPTOR         (0x0800U)

 #define USB_OTG_SELECTOR                       (0xF000U)
 #define B_HNP_ENABLE                           (0x3U)
 #define A_HNP_SUPPORT                          (0x4U)

/* HUB CLASS REQUEST */
 #define USB_HUB_CLEAR_TT_BUFFER                (0x0800U)
 #define USB_HUB_RESET_TT                       (0x0900U)
 #define USB_HUB_GET_TT_STATE                   (0x0A00U)
 #define USB_HUB_STOP_TT                        (0x0B00U)

/* HUB CLASS FEATURE SELECTER */
 #define USB_HUB_C_HUB_LOCAL_POWER              (0x0000U)
 #define USB_HUB_C_HUB_OVER_CURRENT             (0x0001U)
 #define USB_HUB_PORT_CONNECTION                (0x0000U)
 #define USB_HUB_PORT_ENABLE                    (0x0001U)
 #define USB_HUB_PORT_SUSPEND                   (0x0002U)
 #define USB_HUB_PORT_OVER_CURRENT              (0x0003U)
 #define USB_HUB_PORT_RESET                     (0x0004U)
 #define USB_HUB_PORT_POWER                     (0x0008U)
 #define USB_HUB_PORT_LOW_SPEED                 (0x0009U)
 #define USB_HUB_PORT_HIGH_SPEED                (0x000AU)
 #define USB_HUB_C_PORT_CONNECTION              (0x0010U)
 #define USB_HUB_C_PORT_ENABLE                  (0x0011U)
 #define USB_HUB_C_PORT_SUSPEND                 (0x0012U)
 #define USB_HUB_C_PORT_OVER_CURRENT            (0x0013U)
 #define USB_HUB_C_PORT_RESET                   (0x0014U)
 #define USB_HUB_PORT_TEST                      (0x0015U)
 #define USB_HUB_PORT_INDICATOR                 (0x0016U)

/* HUB PORT STAUS */
 #define USB_HUB_STS_PORT_CONNECT               (0x0001U)
 #define USB_HUB_STS_PORT_ENABLE                (0x0002U)
 #define USB_HUB_STS_PORT_SUSPEND               (0x0004U)
 #define USB_HUB_STS_PORT_OVRCURRNET            (0x0008U)
 #define USB_HUB_STS_PORT_RESET                 (0x0010U)
 #define USB_HUB_STS_PORT_POWER                 (0x0100U)
 #define USB_HUB_STS_PORT_LOWSPEED              (0x0200U)
 #define USB_HUB_STS_PORT_FULLSPEED             (0x0000U)
 #define USB_HUB_STS_PORT_HIGHSPEED             (0x0400U)
 #define USB_HUB_STS_PORT_TEST                  (0x0800U)
 #define USB_HUB_STS_PORT_INDICATOR             (0x1000U)

/* HUB PORT CHANGE */
 #define USB_HUB_CHG_PORT_CONNECT               (0x0001U)
 #define USB_HUB_CHG_PORT_ENABLE                (0x0002U)
 #define USB_HUB_CHG_PORT_SUSPEND               (0x0004U)
 #define USB_HUB_CHG_PORT_OVRCURRNET            (0x0008U)
 #define USB_HUB_CHG_PORT_RESET                 (0x0010U)

/* Device connect information */
 #define USB_ATTACH                             (0x0040U)
 #define USB_ATTACHL                            (0x0041U)
 #define USB_ATTACHF                            (0x0042U)
 #define USB_DETACH                             (0x0043U)

/* Reset Handshake result */
 #define USB_NOCONNECT                          (0x0000U) /* Speed undecidedness */
 #define USB_HSCONNECT                          (0x00C0U) /* Hi-Speed connect */
 #define USB_FSCONNECT                          (0x0080U) /* Full-Speed connect */
 #define USB_LSCONNECT                          (0x0040U) /* Low-Speed connect */

/* Pipe define */
 #define USB_USEPIPE                            (0x00FEU)
 #define USB_PERIPIPE                           (0x00FDU)
 #define USB_CLRPIPE                            (0x00FCU) /* Clear Pipe registration */

/* Pipe configuration table define */
 #define USB_EPL                                (6U)      /* Pipe configuration table length */
 #define USB_TYPFIELD                           (0xC000U) /* Transfer type */
 #define USB_PERIODIC                           (0x8000U) /* Periodic pipe */
 #define USB_TYPFIELD_ISO                       (0xC000U) /* Isochronous */
 #define USB_TYPFIELD_INT                       (0x8000U) /* Interrupt */
 #define USB_TYPFIELD_BULK                      (0x4000U) /* Bulk */
 #define USB_TYPFIELD_NOUSE                     (0x2000U) /* Not Used Pipe */
 #define USB_NOUSE                              (0x0000U) /* Not configuration */
 #define USB_BFREFIELD                          (0x0400U) /* Buffer ready interrupt mode select */
 #define USB_BFREON                             (0x0400U)
 #define USB_BFREOFF                            (0x0000U)
 #define USB_DBLBFIELD                          (0x0200U) /* Double buffer mode select */
 #define USB_CFG_DBLBON                         (0x0200U)
 #define USB_CFG_DBLBOFF                        (0x0000U)
 #define USB_CNTMDFIELD                         (0x0100U) /* Continuous transfer mode select */
 #define USB_CFG_CNTMDON                        (0x0100U)
 #define USB_CFG_CNTMDOFF                       (0x0000U)
 #define USB_SHTNAKFIELD                        (0x0080U) /* Transfer end NAK */
 #define USB_DIRFIELD                           (0x0010U) /* Transfer direction select */
 #define USB_DIR_H_OUT                          (0x0010U) /* HOST OUT */
 #define USB_DIR_P_IN                           (0x0010U) /* PERI IN */
 #define USB_DIR_H_IN                           (0x0000U) /* HOST IN */
 #define USB_DIR_P_OUT                          (0x0000U) /* PERI OUT */
 #define USB_BUF2FIFO                           (0x0010U) /* Buffer --> FIFO */
 #define USB_FIFO2BUF                           (0x0000U) /* FIFO --> buffer */
 #define USB_EPNUMFIELD                         (0x000FU) /* Endpoint number select */
 #define USB_MAX_EP_NO                          (15U)     /* EP0 EP1 ... EP15 */
 #define USB_ENDPOINT_DIRECTION                 (0x0080U) /* EndPoint Address direction */

 #define USB_BUF_SIZE(x)    ((uint16_t) (((x) / 64U) - 1U) << 10U)
 #define USB_BUF_NUMB(x)    (x)

 #define USB_IFISFIELD                          (0x1000U) /* Isochronous in-buf flash mode */
 #define USB_IFISON                             (0x1000U)
 #define USB_IFISOFF                            (0x0000U)
 #define USB_IITVFIELD                          (0x0007U) /* Isochronous interval */
 #define USB_IITV_TIME(x)    (x)

/* FIFO port & access define */
 #define USB_CUSE                               (0U)      /* CFIFO  trans */
 #define USB_D0USE                              (1U)      /* D0FIFO trans */
 #define USB_D1USE                              (2U)      /* D1FIFO trans */
 #define USB_FIFO_ACCESS_NUM_MAX                (3U)      /* MAX number for FIFO port define */

/******************************************************************************
 * Another define
 ******************************************************************************/

/* FIFO read / write result */
 #define USB_FIFOERROR                          (USB_ERROR) /* FIFO not ready */
 #define USB_WRITEEND                           (0x0000U)   /* End of write (but packet may not be outputting) */
 #define USB_WRITESHRT                          (0x0001U)   /* End of write (send short packet) */
 #define USB_WRITING                            (0x0002U)   /* Write continues */
 #define USB_READEND                            (0x0000U)   /* End of read */
 #define USB_READSHRT                           (0x0001U)   /* Insufficient (receive short packet) */
 #define USB_READING                            (0x0002U)   /* Read continues */
 #define USB_READOVER                           (0x0003U)   /* Buffer size over */

/* Pipe define table end code */
 #define USB_PDTBLEND                           (0xFFFFU)   /* End of table */

/* Transfer status Type */
 #define USB_CTRL_END                           (0U)
 #define USB_DATA_NONE                          (1U)
 #define USB_DATA_WAIT                          (2U)
 #define USB_DATA_OK                            (3U)
 #define USB_DATA_SHT                           (4U)
 #define USB_DATA_OVR                           (5U)
 #define USB_DATA_STALL                         (6U)
 #define USB_DATA_ERR                           (7U)
 #define USB_DATA_STOP                          (8U)
 #define USB_DATA_TMO                           (9U)
 #define USB_CTRL_READING                       (17U)
 #define USB_CTRL_WRITING                       (18U)
 #define USB_DATA_READING                       (19U)
 #define USB_DATA_WRITING                       (20U)
 #define USB_DATA_FIFO_ERR                      (21U)

/* Utr member (segment) */
 #define USB_TRAN_CONT                          (0x00U)
 #define USB_TRAN_END                           (0x80U)

/* Callback argument */
 #define USB_NO_ARG                             (0U)

/* USB interrupt type (common)*/
 #define USB_INT_UNKNOWN                        (0x0000U)
 #define USB_INT_BRDY                           (0x0001U)
 #define USB_INT_BEMP                           (0x0002U)
 #define USB_INT_NRDY                           (0x0003U)
 #define USB_INT_DXFIFO                         (0x0004U) /* BSP_CFG_RTOS == 2 */

/* USB interrupt type (PERI)*/
 #define USB_INT_VBINT                          (0x0011U)
 #define USB_INT_RESM                           (0x0012U)
 #define USB_INT_SOFR                           (0x0013U)
 #define USB_INT_DVST                           (0x0014U)
 #define USB_INT_CTRT                           (0x0015U)
 #define USB_INT_ATTACH                         (0x0016U)
 #define USB_INT_DETACH                         (0x0017U)

/* USB interrupt type (HOST)*/
 #define USB_INT_OVRCR0                         (0x0041U)
 #define USB_INT_BCHG0                          (0x0042U)
 #define USB_INT_DTCH0                          (0x0043U)
 #define USB_INT_ATTCH0                         (0x0044U)
 #define USB_INT_EOFERR0                        (0x0045U)
 #define USB_INT_PDDETINT0                      (0x0046U)
 #define USB_INT_OVRCR1                         (0x0051U)
 #define USB_INT_BCHG1                          (0x0052U)
 #define USB_INT_ATTCH1                         (0x0053U)
 #define USB_INT_DTCH1                          (0x0054U)
 #define USB_INT_EOFERR1                        (0x0055U)
 #define USB_INT_SACK                           (0x0061U)
 #define USB_INT_SIGN                           (0x0062U)

/* USB interrupt type (OTG)*/
 #define USB_INT_OTG_HOST_INIT                  (0x0071U)

 #define USB_UACTON                             (1U)
 #define USB_UACTOFF                            (0U)
 #define USB_VBON                               (1U)
 #define USB_VBOFF                              (0U)

 #define USB_NOVENDOR                           (0xFFFFU) /* Vendor ID no check */
 #define USB_NOPRODUCT                          (0xFFFFU) /* Product ID no check */

 #define USB_INTFCLSHET                         (0xAAU)   /* Host electrical test class */

/* Root port */
 #define USB_NOPORT                             (0xFFFFU) /* Not connect */

/* Condition compilation by the difference of IP */
 #define USB_MAXDEVADDR                         (5U)

 #define USB_DEVICE_0                           (0x0000U) /* Device address 0 */
 #define USB_DEVICE_1                           (0x1000U) /* Device address 1 */
 #define USB_DEVICE_2                           (0x2000U) /* Device address 2 */
 #define USB_DEVICE_3                           (0x3000U) /* Device address 3 */
 #define USB_DEVICE_4                           (0x4000U) /* Device address 4 */
 #define USB_DEVICE_5                           (0x5000U) /* Device address 5 */
 #define USB_DEVICE_6                           (0x6000U) /* Device address 6 */
 #define USB_DEVICE_7                           (0x7000U) /* Device address 7 */
 #define USB_DEVICE_8                           (0x8000U) /* Device address 8 */
 #define USB_DEVICE_9                           (0x9000U) /* Device address 9 */
 #define USB_DEVICE_A                           (0xA000U) /* Device address A */
 #define USB_NODEVICE                           (0xF000U) /* No device */
 #define USB_DEVADDRBIT                         (12U)

/* DCP Max packet size */
 #define USB_MAXPFIELD                          (0x007FU) /* Max packet size of DCP */

/******************************************************************************
 * Another define
 ******************************************************************************/

/* ControlPipe Max Packet size */
 #define USB_DEFPACKET                          (0x0040U) /* Default DCP Max packet size */

/* Device state define */
 #define USB_NONDEVICE                          (0U)
 #define USB_NOTTPL                             (1U)
 #define USB_DEVICEENUMERATION                  (3U)
 #define USB_COMPLETEPIPESET                    (10U)

/* Control Transfer Stage */
 #define USB_IDLEST                             (0U)  /* Idle */
 #define USB_SETUPNDC                           (1U)  /* Setup Stage No Data Control */
 #define USB_SETUPWR                            (2U)  /* Setup Stage Control Write */
 #define USB_SETUPRD                            (3U)  /* Setup Stage Control Read */
 #define USB_DATAWR                             (4U)  /* Data Stage Control Write */
 #define USB_DATARD                             (5U)  /* Data Stage Control Read */
 #define USB_STATUSRD                           (6U)  /* Status stage */
 #define USB_STATUSWR                           (7U)  /* Status stage */
 #define USB_SETUPWRCNT                         (17U) /* Setup Stage Control Write */
 #define USB_SETUPRDCNT                         (18U) /* Setup Stage Control Read */
 #define USB_DATAWRCNT                          (19U) /* Data Stage Control Write */
 #define USB_DATARDCNT                          (20U) /* Data Stage Control Read */

/******************************************************************************
 * HUB define
 ******************************************************************************/

/* HUB spec */
 #define USB_FSHUB                              (1U)
 #define USB_HSHUBS                             (2U)
 #define USB_HSHUBM                             (3U)

/* Interface number */
 #define USB_HUB_INTNUMFS                       (1U)
 #define USB_HUB_INTNUMHSS                      (1U)
 #define USB_HUB_INTNUMHSM                      (1U)

/*  USB Manager mode    */
 #define USB_PORTOFF                            (0U)   /* Disconnect(VBUSoff) */
 #define USB_DETACHED                           (10U)  /* Disconnect(VBUSon) */
 #define USB_ATTACHED                           (20U)  /* Disconnect(HUBdiconfigured) */
 #define USB_POWERED                            (30U)  /* Start reset handshake */
 #define USB_DEFAULT                            (40U)  /* Set device address */
 #define USB_ADDRESS                            (50U)  /* Enumeration start */
 #define USB_ENUMERATION                        (60U)  /* Wait device enumeration */
 #define USB_CONFIGURED                         (70U)  /* Detach detected */
 #define USB_SUSPENDED                          (80U)  /* Device suspended */
 #define USB_DETACH_PROCESS                     (101U) /* Wait device detach */
 #define USB_SUSPENDED_PROCESS                  (102U) /* Wait device suspend */
 #define USB_RESUME_PROCESS                     (103U) /* Wait device resume */

/* HCD common task message command */
 #define USB_MSG_HCD_ATTACH                     (0x0101U)
 #define USB_MSG_HCD_DETACH                     (0x0102U)
 #define USB_MSG_HCD_USBRESET                   (0x0103U)
 #define USB_MSG_HCD_SUSPEND                    (0x0104U)
 #define USB_MSG_HCD_RESUME                     (0x0105U)
 #define USB_MSG_HCD_REMOTE                     (0x0106U)
 #define USB_MSG_HCD_VBON                       (0x0107U)
 #define USB_MSG_HCD_VBOFF                      (0x0108U)
 #define USB_MSG_HCD_CLR_STALL                  (0x0109U)
 #define USB_MSG_HCD_DETACH_MGR                 (0x010AU)
 #define USB_MSG_HCD_ATTACH_MGR                 (0x010BU)

 #define USB_MSG_HCD_CLR_STALL_RESULT           (0x010CU)
 #define USB_MSG_HCD_CLR_STALLBIT               (0x010DU)
 #define USB_MSG_HCD_SQTGLBIT                   (0x010FU)

/* HCD task message command */
 #define USB_MSG_HCD_SETDEVICEINFO              (0x0111U)
 #define USB_MSG_HCD_SUBMITUTR                  (0x0112U)
 #define USB_MSG_HCD_TRANSEND1                  (0x0113U)
 #define USB_MSG_HCD_TRANSEND2                  (0x0114U)
 #define USB_MSG_HCD_CLRSEQBIT                  (0x0115U)
 #define USB_MSG_HCD_SETSEQBIT                  (0x0116U)
 #define USB_MSG_HCD_INT                        (0x0117U)
 #define USB_MSG_HCD_DMAINT                     (0x0119U)

 #define USB_MSG_HCD_OTG_SUSPEND                (0x0120U)

 #define USB_MSG_HCD_D0FIFO_INT                 (0x0141U)
 #define USB_MSG_HCD_D1FIFO_INT                 (0x0142U)
 #define USB_MSG_HCD_RESM_INT                   (0x0143U)
 #define USB_MSG_PCD_D0FIFO_INT                 (0x0144U)
 #define USB_MSG_PCD_D1FIFO_INT                 (0x0145U)
 #define USB_MSG_PCD_RESM_INT                   (0x0146U)

/* USB Manager task message command */
 #define USB_MSG_MGR_AORDETACH                  (0x0121U)
 #define USB_MSG_MGR_OVERCURRENT                (0x0122U)
 #define USB_MSG_MGR_STATUSRESULT               (0x0123U)
 #define USB_MSG_MGR_SUBMITRESULT               (0x0124U)
 #define USB_MSG_MGR_TRANSENDRESULT             (0x0125U)

 #define USB_MSG_MGR_SETCONFIGURATION           (0x0300)
 #define USB_MSG_MGR_SETCONFIGURATION_RESULT    (0x0301)

 #define USB_MSG_MGR_GETDESCRIPTOR              (0x0400)
 #define USB_MSG_MGR_GETDESCRIPTOR_RESULT       (0x0401)

/* USB HUB task message command */
 #define USB_MSG_HUB_HUB2HUBSTART               (0x0131U)
 #define USB_MSG_HUB_START                      (0x0132U)
 #define USB_MSG_HUB_STOP                       (0x0133U)
 #define USB_MSG_HUB_SUBMITRESULT               (0x0134U)
 #define USB_MSG_HUB_EVENT                      (0x0135U) /* nonOS */
 #define USB_MSG_HUB_ATTACH                     (0x0136U) /* nonOS */
 #define USB_MSG_HUB_RESET                      (0x0137U) /* nonOS */

/* CLS task message command */
 #define USB_MSG_CLS_CHECKREQUEST               (0x0201U) /* nonOS */
 #define USB_MSG_CLS_INIT                       (0x0202U) /* nonOS */
 #define USB_MSG_CLS_TASK                       (0x0203U) /* nonOS */
 #define USB_MSG_CLS_WAIT                       (0x0204U) /* nonOS */
 #define USB_MSG_CLS_PROCESSRESULT              (0x0205U) /* nonOS */

/* HET task message command */
 #define USB_MSG_HET_UACTOFF                    (0x0171U)
 #define USB_MSG_HET_UACTON                     (0x0172U)
 #define USB_MSG_HET_VBUSOFF                    (0x0173U)
 #define USB_MSG_HET_VBUSON                     (0x0174U)
 #define USB_MSG_HET_RESET                      (0x0175U)
 #define USB_MSG_HET_SUSPEND                    (0x0176U)
 #define USB_MSG_HET_RESUME                     (0x0177U)
 #define USB_MSG_HET_ENUMERATION                (0x0178U)
 #define USB_MSG_HET_TESTNONE                   (0x0181U)
 #define USB_MSG_HET_TESTPACKET                 (0x0182U)
 #define USB_MSG_HET_TESTJ                      (0x0183U)
 #define USB_MSG_HET_TESTK                      (0x0184U)
 #define USB_MSG_HET_TESTSE0                    (0x0185U)
 #define USB_MSG_HET_TESTSIGSTOP                (0x0186U)
 #define USB_MSG_HET_SINGLESETUP                (0x0187U)
 #define USB_MSG_HET_SINGLEDATA                 (0x0188U)

/* Descriptor index */
 #define USB_DEV_MAX_PKT_SIZE                   (7U)  /* Index of bMAXPacketSize */
 #define USB_DEV_NUM_CONFIG                     (17U) /* Index of bNumConfigurations */
 #define USB_ALT_NO                             (255U)
 #define USB_SOFT_CHANGE                        (0U)

/* USB Peripheral task message command */
 #define USB_MSG_PCD_INT                        (0x0151U)
 #define USB_MSG_PCD_SUBMITUTR                  (0x0152U)
 #define USB_MSG_PCD_TRANSEND1                  (0x0153U)
 #define USB_MSG_PCD_TRANSEND2                  (0x0154U)
 #define USB_MSG_PCD_REMOTEWAKEUP               (0x0155U)
 #define USB_MSG_PCD_DETACH                     (0x0161U)
 #define USB_MSG_PCD_ATTACH                     (0x0162U)
 #define USB_MSG_PCD_CLRSEQBIT                  (0x0163U)
 #define USB_MSG_PCD_SETSTALL                   (0x0164U)
 #define USB_MSG_PCD_PCUTINT                    (0x0156U)

 #define USB_MSG_PCD_DP_ENABLE                  (0x0157U)
 #define USB_MSG_PCD_DP_DISABLE                 (0x0158U)
 #define USB_MSG_PCD_DM_ENABLE                  (0x0159U)
 #define USB_MSG_PCD_DM_DISABLE                 (0x015AU)

 #define USB_MSG_PCD_DMAINT                     (0x015bU)

 #define USB_DO_REMOTEWAKEUP                    (USB_MSG_PCD_REMOTEWAKEUP)
 #define USB_DP_ENABLE                          (USB_MSG_PCD_DP_ENABLE)
 #define USB_DP_DISABLE                         (USB_MSG_PCD_DP_DISABLE)
 #define USB_DM_ENABLE                          (USB_MSG_PCD_DM_ENABLE)
 #define USB_DM_DISABLE                         (USB_MSG_PCD_DM_DISABLE)

 #define USB_DO_STALL                           (USB_MSG_PCD_SETSTALL)

 #define USB_DO_RESET_AND_ENUMERATION           (0x0202U) /* USB_MSG_HCD_ATTACH */
 #define USB_PORT_ENABLE                        (0x0203U) /* USB_MSG_HCD_VBON */
 #define USB_PORT_DISABLE                       (0x0204U) /* USB_MSG_HCD_VBOFF */
 #define USB_DO_GLOBAL_SUSPEND                  (0x0205U) /* USB_MSG_HCD_SUSPEND */
 #define USB_DO_SELECTIVE_SUSPEND               (0x0206U) /* USB_MSG_HCD_SUSPEND */
 #define USB_DO_GLOBAL_RESUME                   (0x0207U) /* USB_MSG_HCD_RESUME */
 #define USB_DO_SELECTIVE_RESUME                (0x0208U) /* USB_MSG_HCD_RESUME */
 #define USB_DO_CLR_STALL                       (0x0209U) /* USB_MSG_HCD_CLR_STALL */
 #define USB_DO_SET_SQTGL                       (0x020AU) /* USB_MSG_HCD_SQTGLBIT */
 #define USB_DO_CLR_SQTGL                       (0x020BU) /* USB_MSG_HCD_CLRSEQBIT */

/* BC State Define */
 #define USB_BC_STATE_INIT                      (0x00U)
 #define USB_BC_STATE_DET                       (0x01U)
 #define USB_BC_STATE_CDP                       (0x02U)
 #define USB_BC_STATE_SDP                       (0x03U)
 #define USB_BC_STATE_DCP                       (0x04U)
 #define USB_BC_STATE_MAX                       (0x05U)

/* BC State Change Event Define */
 #define USB_BC_EVENT_VB                        (0x00U)
 #define USB_BC_EVENT_AT                        (0x01U)
 #define USB_BC_EVENT_DT                        (0x02U)
 #define USB_BC_EVENT_MAX                       (0x03U)

/* DCP Mode Setting Define */
 #define USB_BC_DCPMODE                         (0x01U)

/*#define USB_BC_DCPMODE                      (0x00U)*/

 #define USB_NOT_BC                             (0xFFFEU)

 #define USB_ODD                                (0x1U)

/*************************************************************************
 * old basic_cfg.h #define
 *************************************************************************/
 #define USB_SND_MSG(ID, MESS)         (usb_cstd_snd_msg((uint8_t) (ID), (usb_msg_t *) (MESS)))
 #define USB_ISND_MSG(ID, MESS)        (usb_cstd_isnd_msg((uint8_t) (ID), (usb_msg_t *) (MESS)))
 #define USB_WAI_MSG(ID, MESS, TM)     (usb_cstd_wai_msg((uint8_t) (ID), (usb_msg_t *) (MESS), (usb_tm_t) (TM)))
 #define USB_RCV_MSG(ID, MESS)         (usb_cstd_rec_msg((uint8_t) (ID), (usb_msg_t **) (MESS), (usb_tm_t) (0U)))
 #define USB_TRCV_MSG(ID, MESS, TM)    (usb_cstd_rec_msg((uint8_t) (ID), (usb_msg_t **) (MESS), (usb_tm_t) (TM)))

 #define USB_PGET_BLK(ID, BLK)         (usb_cstd_pget_blk((uint8_t) (ID), (usb_utr_t **) (BLK)))
 #define USB_REL_BLK(ID, BLK)          (usb_cstd_rel_blk((uint8_t) (ID), (usb_utr_t *) (BLK)))

/* Descriptor size */
 #define USB_DEVICESIZE     (20U)      /* Device Descriptor size */
 #ifdef USB_CFG_HUVC_USE
  #define USB_CONFIGSIZE    (3 * 1024) /* Configuration Descriptor size */
 #else
  #define USB_CONFIGSIZE    (1 * 1024) /* Configuration Descriptor size */
 #endif /* USB_CFG_HUVC_USE */

/* Number of software retries when a no-response condition occurs during a transfer */
 #define USB_PIPEERROR      (1U)

/** [Output debugging message in a console of IDE.]
 *   not defined(USB_DEBUG_ON) : No output the debugging message
 *   defined(USB_DEBUG_ON)     : Output the debugging message
 */
 #if defined(USB_DEBUG_ON)
  #define USB_PRINTF0(FORM)                                (printf(FORM))
  #define USB_PRINTF1(FORM, x1)                            (printf((FORM), (x1)))
  #define USB_PRINTF2(FORM, x1, x2)                        (printf((FORM), (x1), (x2)))
  #define USB_PRINTF3(FORM, x1, x2, x3)                    (printf((FORM), (x1), (x2), (x3)))
  #define USB_PRINTF4(FORM, x1, x2, x3, x4)                (printf((FORM), (x1), (x2), (x3), (x4)))
  #define USB_PRINTF5(FORM, x1, x2, x3, x4, x5)            (printf((FORM), (x1), (x2), (x3), (x4), (x5)))
  #define USB_PRINTF6(FORM, x1, x2, x3, x4, x5, x6)        (printf((FORM), (x1), (x2), (x3), (x4), (x5), (x6)))
  #define USB_PRINTF7(FORM, x1, x2, x3, x4, x5, x6, x7)    (printf((FORM), (x1), (x2), (x3), (x4), (x5), (x6), (x7)))
  #define USB_PRINTF8(FORM,                                                                                          \
                      x1,                                                                                            \
                      x2,                                                                                            \
                      x3,                                                                                            \
                      x4,                                                                                            \
                      x5,                                                                                            \
                      x6,                                                                                            \
                      x7,                                                                                            \
                      x8)                                  (printf((FORM), (x1), (x2), (x3), (x4), (x5), (x6), (x7), \
                                                                   (x8)))
 #else                                 /* defined(USB_DEBUG_ON) */
  #define USB_PRINTF0(FORM)
  #define USB_PRINTF1(FORM, x1)
  #define USB_PRINTF2(FORM, x1, x2)
  #define USB_PRINTF3(FORM, x1, x2, x3)
  #define USB_PRINTF4(FORM, x1, x2, x3, x4)
  #define USB_PRINTF5(FORM, x1, x2, x3, x4, x5)
  #define USB_PRINTF6(FORM, x1, x2, x3, x4, x5, x6)
  #define USB_PRINTF7(FORM, x1, x2, x3, x4, x5, x6, x7)
  #define USB_PRINTF8(FORM, x1, x2, x3, x4, x5, x6, x7, x8)
 #endif                                /* defined(USB_DEBUG_ON) */

 #ifdef __cplusplus
}
 #endif

#endif                                 /* R_USB_BASIC_DEFINE_H */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
