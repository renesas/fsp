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

#ifndef R_USB_PMSC_H
 #define R_USB_PMSC_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

 #ifdef __cplusplus
extern "C" {
 #endif

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
 #define USB_PMSC_TSK              (USB_TID_10)   /* Task ID */
 #define USB_PMSC_MBX              (USB_PMSC_TSK) /* Mailbox ID */

/* CBW Structure define */
 #define USB_MSC_CBWLENGTH         (0x1fU)
 #define USB_MSC_CBWCB_LENGTH      (0x0cU)
 #define USB_MSC_CSW_LENGTH        (0x0dU)

 #define USB_VALUE_481             (481)
 #define USB_VALUE_33              (33)

/* CPU bit endian select (BIT_LITTLE:little, BIT_BIG:big) */
 #if USB_CFG_ENDIAN == USB_CFG_BIG
  #define USB_MSC_CBW_SIGNATURE    ((uint32_t) 0x55534243)
  #define USB_MSC_CSW_SIGNATURE    ((uint32_t) 0x55534253)
 #else                                 /* USB_CFG_ENDIAN == USB_CFG_BIG */
  #define USB_MSC_CBW_SIGNATURE    ((uint32_t) 0x43425355)
  #define USB_MSC_CSW_SIGNATURE    ((uint32_t) 0x53425355)
 #endif /* USB_CFG_ENDIAN == USB_CFG_BIG */

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/*************** enumeration define ***********************/
/* GET_MAX_LUN request check code. */
typedef enum
{
    USB_MSC_LUN_LENGTH = 0x01,         /* GET_MAX_LUN request wLength */
} usb_gpmsc_lun_req_chk_t;

/* USB Mass Storage Devie Class Lapper check. */
typedef enum
{
    USB_MSC_DNXX = 0x10,               /* Device No Data */
    USB_MSC_DIXX = 0x20,               /* Device Send(IN) Data */
    USB_MSC_DOXX = 0x30,               /* Device Recieved(OUT) Data */
    USB_MSC_XXHN = 0x01,               /* Host No Data */
    USB_MSC_XXHI = 0x02,               /* Host Recieved(IN) Data */
    USB_MSC_XXHO = 0x03,               /* Host Send(OUT) Data */
    USB_MSC_DNHN = 0x11,               /* Device No Data & Host No Data */
    USB_MSC_DNHI = 0x12,               /* Device No Data & Host Recieved(IN) Data */
    USB_MSC_DNHO = 0x13,               /* Device No Data & Host Send(OUT) Data */
    USB_MSC_DIHN = 0x21,               /* Device Send(IN) Data & Host No Data */
    USB_MSC_DIHI = 0x22,               /* Device Send(IN) Data & Host Recieved(IN) Data */
    USB_MSC_DIHO = 0x23,               /* Device Send(IN) Data & Host Send(OUT) Data */
    USB_MSC_DOHN = 0x31,               /* Device Recieved(OUT) Data & Host No Data */
    USB_MSC_DOHI = 0x32,               /* Device Recieved(OUT) Data & Host Recieved(IN) Data */
    USB_MSC_DOHO = 0x33,               /* Device Recieved(OUT) Data & Host Send(OUT) Data */
} usb_gpmsc_case13check_t;

/* USB Mass Storage Devie Class Lapper check. */
typedef enum
{
    USB_MSC_CASE01   = 0x01,           /* CBW check case01 */
    USB_MSC_CASE02   = 0x02,           /* CBW check case02 */
    USB_MSC_CASE03   = 0x03,           /* CBW check case03 */
    USB_MSC_CASE04   = 0x04,           /* CBW check case04 */
    USB_MSC_CASE05   = 0x05,           /* CBW check case05 */
    USB_MSC_CASE06   = 0x06,           /* CBW check case06 */
    USB_MSC_CASE07   = 0x07,           /* CBW check case07 */
    USB_MSC_CASE08   = 0x08,           /* CBW check case08 */
    USB_MSC_CASE09   = 0x09,           /* CBW check case09 */
    USB_MSC_CASE10   = 0x0A,           /* CBW check case10 */
    USB_MSC_CASE11   = 0x0B,           /* CBW check case11 */
    USB_MSC_CASE12   = 0x0C,           /* CBW check case12 */
    USB_MSC_CASE13   = 0x0D,           /* CBW check case13 */
    USB_MSC_CASE_ERR = 0xFF            /* CBW check case error */
} usb_gpmsc_case13nun_t;

/* CSW STATUS */
typedef enum
{
    USB_MSC_CSW_OK        = (uint16_t) 0x00,
    USB_MSC_CSW_NG        = (uint16_t) 0x01,
    USB_MSC_CSW_PHASE_ERR = (uint16_t) 0x02
} usb_gcmsc_cswsts_t;

/* USB Mass Storage Device Class Phase. */
typedef enum
{
    USB_PMSC_CBWRCV                 = 0x00, /* Receive Command Block Wrapper */
    USB_PMSC_DATASND                = 0x01, /* Send Data (Device to Host) */
    USB_PMSC_DATARCV                = 0x02, /* Receive Data (Host to Device) */
    USB_PMSC_CSWSND                 = 0x03, /* Send Command Status Wrapper */
    USB_PMSC_SIG_ERR                = 0x04, /* SIGNATURE error */
    USB_PMSC_IN_DATA_STALL_CSW_NG   = 0x05, /*  */
    USB_PMSC_OUT_DATA_STALL_CSW_NG  = 0x06, /*  */
    USB_PMSC_IN_DATA_STALL_CSW_ERR  = 0x07, /*  */
    USB_PMSC_OUT_DATA_STALL_CSW_ERR = 0x08, /*  */
    USB_PMSC_NO_DATA_CSW_NG         = 0x09, /*  */
    USB_PMSC_CHECK = 0xFF                   /* Command Check */
} usb_gpmsc_phase_t;

/* AtapiCommandExecute Result */
typedef enum
{
    USB_PMSC_CMD_COMPLETE     = 0x00,  /* Command passed */
    USB_PMSC_CMD_FAILED       = 0x01,  /* Command failed */
    USB_PMSC_CMD_CONTINUE     = 0x02,  /* (In/Out)Data   */
    USB_PMSC_CMD_ERROR        = 0x03,  /* Command Error  */
    USB_PMSC_CMD_SHT_COMPLETE = 0x04,  /* Command passed (case 5 OK) */
} usb_gpmsc_status_t;

typedef struct
{
    uint8_t reserved7 : 7;
    uint8_t cbw_dir   : 1;
} usb_msc_bmcbw_flags_t;

typedef struct
{
    uint8_t bcbwlun   : 4;
    uint8_t reserved4 : 4;
} usb_msc_bcbwlun_t;

typedef struct
{
    uint8_t bcbwcb_length : 5;
    uint8_t reserved3     : 3;
} usb_msc_bcbwcb_length_t;

/* CBW Structure define. */
typedef struct
{
    uint32_t                dcbw_signature;
    uint32_t                dcbw_tag;
    uint8_t                 dcbw_dtl_lo;
    uint8_t                 dcbw_dtl_ml;
    uint8_t                 dcbw_dtl_mh;
    uint8_t                 dcbw_dtl_hi;
    usb_msc_bmcbw_flags_t   bmcbw_flags;
    usb_msc_bcbwlun_t       bcbwlun;
    usb_msc_bcbwcb_length_t bcbwcb_length;
 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
  #if defined(BSP_MCU_GROUP_RA6M3) || defined(BSP_MCU_GROUP_RA6M5)
    uint8_t cbwcb[(16 + USB_VALUE_481)]; /* Hi-Speed USB_MSC_CBW_t:512Byte */
  #else /* defined(BSP_MCU_GROUP_RA6M3) || defined(BSP_MCU_GROUP_RA6M5) */
    uint8_t cbwcb[(16 + USB_VALUE_33)];  /* Full-Speed USB_MSC_CBW_t:64Byte*/
  #endif /* defined(BSP_MCU_GROUP_RA6M3) || defined(BSP_MCU_GROUP_RA6M5) */
 #else                                   /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */
    uint8_t cbwcb[16];
 #endif /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */
} usb_msc_cbw_t;

/* CSW Structure define define. */
typedef struct
{
    uint32_t dcsw_signature;
    uint32_t dcsw_tag;
    uint8_t  dcsw_data_residue_lo;
    uint8_t  dcsw_data_residue_ml;
    uint8_t  dcsw_data_residue_mh;
    uint8_t  dcsw_data_residue_hi;
    uint8_t  bcsw_status;
    uint8_t  dummy;
} usb_msc_csw_t;

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
extern uint32_t       g_usb_pmsc_dtl;
extern usb_pmsc_cbm_t g_usb_pmsc_message;

void usb_pmsc_init(void);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* R_USB_PMSC_H */

/***********************************************************************************************************************
 * End Of File
 ***********************************************************************************************************************/
