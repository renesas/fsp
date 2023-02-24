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

#ifndef R_USB_PATAPI_H
 #define R_USB_PATAPI_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

 #ifdef __cplusplus
extern "C" {
 #endif

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/* Operation when responding with a short packet to a command */

/*  0: Respond to 0x00 with CSW with setting PIPE to STALL
 *  1: Respond to 0x00 with CSW without setting PIPE to STALL
 */
 #define USB_ATAPI_SHT_RESPONSE    1

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/* ATAPI command */
typedef enum
{
    /*--- SFF-8070i command define ---*/
    USB_ATAPI_TEST_UNIT_READY      = 0x00U,
    USB_ATAPI_REQUEST_SENSE        = 0x03U,
    USB_ATAPI_FORMAT_UNIT          = 0x04U,
    USB_ATAPI_INQUIRY              = 0x12U,
    USB_ATAPI_MODE_SELECT6         = 0x15U,
    USB_ATAPI_MODE_SENSE6          = 0x1AU,
    USB_ATAPI_START_STOP_UNIT      = 0x1BU,
    USB_ATAPI_PREVENT_ALLOW        = 0x1EU,
    USB_ATAPI_READ_FORMAT_CAPACITY = 0x23U,
    USB_ATAPI_READ_CAPACITY        = 0x25U,
    USB_ATAPI_READ10               = 0x28U,
    USB_ATAPI_WRITE10              = 0x2AU,
    USB_ATAPI_SEEK                 = 0x2BU,
    USB_ATAPI_WRITE_AND_VERIFY     = 0x2EU,
    USB_ATAPI_VERIFY10             = 0x2FU,
    USB_ATAPI_MODE_SELECT10        = 0x55U,
    USB_ATAPI_MODE_SENSE10         = 0x5AU,
} usb_atapi_t;

/* ATAPI error code */
typedef enum
{
    USB_ATAPI_SUCCESS = 0x11,

    /* Command receive events */
    USB_ATAPI_NO_DATA     = 0x21,
    USB_ATAPI_A_SND_DATA  = 0x22,
    USB_ATAPI_A_RCV_DATA  = 0x23,
    USB_ATAPI_SND_DATAS   = 0x24,
    USB_ATAPI_RCV_DATAS   = 0x25,
    USB_ATAPI_NOT_SUPPORT = 0x26,

    /* Complete events */
    USB_ATAPI_CMD_CONTINUE = 0x31,
    USB_ATAPI_CMD_COMPLETE = 0x32,
    USB_ATAPI_CMD_FAILED   = 0x33,

    /* ATAPI Start events */
    USB_ATAPI_READY = 0x41,

    /* Respond error */
    USB_ATAPI_ERROR = 0x51,

    /*** ERR CODE ***/
    USB_ATAPI_ERR_CODE_SEPARATER = 0x100,
    USB_ATAPI_ERR_INVAL          = 0x61
} usb_atapi_result_t;

/* ATAPI command size */
typedef enum
{
    USB_ATAPI_REQUEST_SENSE_SIZE           = 18,
    USB_ATAPI_INQUIRY_SIZE                 = 36,
    USB_ATAPI_READ_FORMAT_CAPACITY_SIZE    = 20,
    USB_ATAPI_READ_CAPACITY_SIZE           = 8,
    USB_ATAPI_MODE_SENSE10_MODE_PARAM_SIZE = 8,
    USB_ATAPI_MODE_SENSE10_ERR_RCVR_P_SIZE = 20,
    USB_ATAPI_MODE_SENSE10_CASHING_P_SIZE  = 20,
    USB_ATAPI_MODE_SENSE10_CAP_P_SIZE      = 20,
    USB_ATAPI_MODE_SENSE10_OP_CMD_SIZE     = 20,
    USB_ATAPI_MODE_SENSE10_ALL_P_SIZE      = 44,
    USB_ATAPI_MODE_SENSE10_P_CODE_ERR_SIZE = 8,
    USB_ATAPI_DATA_SIZE_0 = 0
} usb_atapi_command_size_t;

/* INQUIRY data format */
typedef enum
{
    USB_ATAPI_INQUIRY_VENDOR_SIZE   = 8,
    USB_ATAPI_INQUIRY_PRODUCT_SIZE  = 16,
    USB_ATAPI_INQUIRY_REVISION_SIZE = 4,
} usb_atapi_inquiry_data_format_size_t;

/* Callback Message format define. */
typedef struct
{
    uint32_t ar_rst;
    uint32_t ul_size;
} usb_pmsc_cbm_t;

/* Command Descriptor Block format define. */
typedef struct
{
    uint8_t b_lun      : 3;            /* Logical Unit Number */
    uint8_t b_reserved : 5;
} usb_pmsc_lun_t;

typedef struct
{
    uint8_t        uc_opcode;
    usb_pmsc_lun_t s_lun;
    uint8_t        uc_data;
} usb_pmsc_ptn0_t;

typedef struct
{
    uint8_t b_lun       : 3;           /* Logical Unit Number */
    uint8_t b_reserved4 : 4;
    uint8_t b_immed     : 1;
} usb_pmsc_lun2_t;

typedef struct
{
    uint8_t         uc_opcode;
    usb_pmsc_lun2_t s_lun;
    uint8_t         uc_rsv2[2];
    uint8_t         uc_allocation;     /* Return Data Length */
    uint8_t         uc_rsv1[1];
    uint8_t         uc_rsv6[6];
} usb_pmsc_ptn12_t;

typedef struct
{
    uint8_t b_lun     : 3;             /* Logical Unit Number */
    uint8_t b_fmtdata : 1;             /* Fmt Data */
    uint8_t b_cmplist : 1;             /* Cmp List */
    uint8_t b_defect  : 3;             /* Defect List Fomat */
} usb_pmsc_lun3_t;

typedef struct
{
    uint8_t         uc_opcode;
    usb_pmsc_lun3_t s_lun;
    uint8_t         ul_lba0;           /* MSB */
    uint8_t         ul_lba1;
    uint8_t         ul_lba2;
    uint8_t         ul_lba3;           /* LSB */
    uint8_t         uc_rsv6[6];
} usb_pmsc_ptn378_t;

typedef struct
{
    uint8_t b_lun       : 3;           /* Logical Unit Number */
    uint8_t b_1         : 1;
    uint8_t b_reserved2 : 2;
    uint8_t b_bytechk   : 1;
    uint8_t b_sp        : 1;
} usb_pmsc_s_s_lun4_t;

typedef struct
{
    uint8_t             uc_opcode;
    usb_pmsc_s_s_lun4_t s_lun;
    uint8_t             ul_logical_block0; /* MSB */
    uint8_t             ul_logical_block1;
    uint8_t             ul_logical_block2;
    uint8_t             ul_logical_block3; /* LSB */
    uint8_t             uc_rsv1[1];
    uint8_t             us_length_hi;
    uint8_t             us_length_lo;
    uint8_t             uc_rsv3[3];
} usb_pmsc_ptn4569_t;

/* Command Descriptor Block format define. */
typedef union
{
    usb_pmsc_ptn0_t    s_usb_ptn0;
    usb_pmsc_ptn12_t   s_usb_ptn12;
    usb_pmsc_ptn378_t  s_usb_ptn378;
    usb_pmsc_ptn4569_t s_usb_ptn4569;
} usb_pmsc_cdb_t;

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
void pmsc_atapi_analyze_cbwcb(uint8_t * cbwcb);
void pmsc_atapi_command_processing(uint8_t * cbw, uint16_t usb_result, usb_cb_t complete, uint8_t module_number);
void pmsc_atapi_init(void);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* R_USB_PATAPI_H */

/***********************************************************************************************************************
 * End Of File
 ***********************************************************************************************************************/
