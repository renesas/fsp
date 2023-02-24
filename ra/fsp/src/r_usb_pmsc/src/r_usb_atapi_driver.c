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

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include <stddef.h>
#include <string.h>

#include <r_usb_basic.h>
#include "r_usb_basic_api.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "../../r_usb_basic/src/hw/inc/r_usb_bitdefine.h"
#include "../../r_usb_basic/src/hw/inc/r_usb_reg_access.h"

#include "r_usb_pmsc_api.h"
#include "inc/r_usb_pmsc_driver.h"
#include "inc/r_usb_patapi.h"
#include "inc/r_usb_pmsc.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define USB_VALUE_ADDITIONAL_LEN_20H       (0x20)
#define USB_VALUE_MODE_SENSE10_ALL_PAGE    (0x3F)
#define USB_VALUE_MASK_3FH                 (0x3F)
#define USB_VALUE_RMB                      (0x80)
#define USB_VALUE_MASK_FFH                 (0xFF)
#define USB_VALUE_32                       (32)
#define USB_VALUE_ALL_PAGE_LENGTH          (0x24)

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/
static void pmsc_atapi_get_read_data(uint32_t * size, uint8_t ** buff);
static void pmsc_atapi_get_mode_sense10_data(uint8_t page_code, uint32_t * size, uint8_t ** buff);

static uint8_t          g_usb_atapi_is_data_stage = USB_FALSE; /* Data SetUp Flag */
static uint8_t          g_usb_pmsc_media_buffer[USB_CFG_PMSC_ATAPI_BLOCK_UNIT * USB_CFG_PMSC_TRANS_COUNT];
static usb_pmsc_cdb_t * g_usb_atapi_cbwcb;                     /* CBWCB pointer */
static uint32_t         g_usb_atapi_cur_lba;                   /* the current Logical Block Address */

extern usb_utr_t g_usb_pmsc_utr;

/* Inquiry data */
static uint8_t g_usb_atapi_inquiry_tbl[USB_ATAPI_INQUIRY_SIZE] =
{
    0x00,                              /* [0]b7-b5:Reserved, b4-b0:Peripheral Device Type */
    USB_VALUE_RMB,                     /* [1]b7:RMB(ARemovable Medium Bit), b6-b0:Reserved */
    0x00,                              /* [2]b7-b6:ISO Version, b5-b3:ECMA Version, b2-b0:ANSI Version(00h) */
    0x01,                              /* [3]b7-b4:Reserved, b3-b0:Response Data Format */
    USB_VALUE_ADDITIONAL_LEN_20H,      /* [4]Additional Length(Number of bytes follwing this one) */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    0x00,                              /* [8]Vendor Information1 */
    0x00,                              /* [9]Vendor Information2 */
    0x00,                              /* [10]Vendor Information3 */
    0x00,                              /* [11]Vendor Information4 */
    0x00,                              /* [12]Vendor Information5 */
    0x00,                              /* [13]Vendor Information6 */
    0x00,                              /* [14]Vendor Information7 */
    0x00,                              /* [15]Vendor Information8 */
    0x00,                              /* [16]Product Identification1 */
    0x00,                              /* [17]Product Identification2 */
    0x00,                              /* [18]Product Identification3 */
    0x00,                              /* [19]Product Identification4 */
    0x00,                              /* [20]Product Identification5 */
    0x00,                              /* [21]Product Identification6 */
    0x00,                              /* [22]Product Identification7 */
    0x00,                              /* [23]Product Identification8 */
    0x00,                              /* [24]Product Identification9 */
    0x00,                              /* [25]Product Identification10 */
    0x00,                              /* [26]Product Identification11 */
    0x00,                              /* [27]Product Identification12 */
    0x00,                              /* [28]Product Identification13 */
    0x00,                              /* [29]Product Identification14 */
    0x00,                              /* [30]Product Identification15 */
    0x00,                              /* [31]Product Identification16 */
    0x00,                              /* [32]Product Revision Level1 */
    0x00,                              /* [33]Product Revision Level2 */
    0x00,                              /* [34]Product Revision Level3 */
    0x00                               /* [35]Product Revision Level4 */
};

/* Read Format Capacity data */
static uint8_t g_usb_atapi_read_f_capa_tbl[USB_ATAPI_READ_FORMAT_CAPACITY_SIZE] =
{
    /* Capacity List Header Length */
    0x00, 0x00, 0x00, 0x10,

    /* Current/Maximum Capacity Descriptor */
    0x00, 0x00, 0x00, 0x00,            /* Number of Blocks. */
    0x02, 0x00, 0x02, 0x00,            /* Block Length in Bytes */
    /* Formattable Capacity Descriptor */
    0x00, 0x00, 0x00, 0x00,            /* Number of Blocks. */
    0x00, 0x00, 0x02, 0x00             /* Block Length in Bytes */
};

/* Read Capacity data */
static uint8_t g_usb_atapi_read_capa_tbl[USB_ATAPI_READ_CAPACITY_SIZE] =
{
    0x00, 0x00, 0x00, 0x00,            /* Last Logical Block Address (default) */
    0x00, 0x00, 0x00, 0x00             /* Default Block Length in Bytes */
};

/* Request Sense data */
static const uint8_t g_usb_atapi_rs_tbl[USB_ATAPI_REQUEST_SENSE_SIZE] =
{
    0x70,                              /* [0]b7:Valid, b6-b0:Error Code(70h) */
    0x00,                              /* [1]Reserved */
    0x05,                              /* [2]b7-b5:Vendor Specific, b4:reserved, B3-b0: Sense Key */
    0x00,                              /* [3]Information(Vendor Specific) */
    0x00,                              /* [4]Information(Vendor Specific) */
    0x00,                              /* [5]Information(Vendor Specific) */
    0x00,                              /* [6]Information(Vendor Specific) */
    0x0A,                              /* [7]Additional Sense Length */
    0x00,                              /* [8]Vendor Specific */
    0x00,                              /* [9]Vendor Specific */
    0x00,                              /* [10]Vendor Specific */
    0x00,                              /* [11]Vendor Specific */
    0x24,                              /* [12]ASC(Additonal Sense Code(Mandatory)) */
    0x00,                              /* [13]ASCQ(Additonal Sense Code Qualifier(Mandatory)) */
    0x00,                              /* [14]Field Replaceable Unit Code(Optional) */
    0x00,                              /* [15]b7:SKSV(Sense-Key Specific Valid),b6-b0:Sense-Key Specific */
    0x00,                              /* [16]Sense-Key Specific */
    0x00                               /* [17]Sense-Key Specific */
};

/* Mode Sense data (Mode Parameter) */
static uint8_t g_usb_atapi_ms_mp_tbl[USB_ATAPI_MODE_SENSE10_MODE_PARAM_SIZE] =
{
    0x00,                              /* [0]Mode Data Length */
    0x00,                              /* [1]Mode Data Length */
    0x00,                              /* [2]Medium Type Code(00h-FFh Vendor Specific) */
    0x00,                              /* [3]b7:WP(Write Protect), b6-b0:Reserved */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00                               /* [7]Reserved */
};

/* Mode Sense data (ReadWrite Error Recovery Page 12byte) */
static uint8_t g_usb_atapi_ms_rcvr_tbl[USB_ATAPI_MODE_SENSE10_ERR_RCVR_P_SIZE] =
{
    /* Mode Parameter List */
    0x00,                              /* [0]Mode Data Length */
    0x0C,                              /* [1]Mode Data Length */
    0x00,                              /* [2]Medium Type Code(00h-FFh Vendor Specific) */
    0x00,                              /* [3]b7:WP(Write Protect), b6-b0:Reserved */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    /* Page(ReadWrite Error Recovery Page 12byte) */
    0x01,                              /* [0]b7:PS, b6:Reserved, b5-b0:Page Code(01h) */
    0x0A,                              /* [1]Page Length(0Ah) */
    0x00,                              /* [2]Error Recovery Parameters */
                                       /*    b7:AWRE, b6:Reserved, b5:TB, b4:RC, b3:Reserved, b2:PER, b1:Reserved, b0:DCR*/
    0x00,                              /* [3]Read Retry Count */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    0x00,                              /* [8]Write Retry Count */
    0x00,                              /* [9]Reserved */
    0x00,                              /* [10]Reserved */
    0x00                               /* [11]Reserved */
};

/* Mode Sense data (Cashing Page 12byte) */
static uint8_t g_usb_atapi_ms_cash_tbl[USB_ATAPI_MODE_SENSE10_CASHING_P_SIZE] =
{
    /* Mode Parameter List */
    0x00,                              /* [0]Mode Data Length */
    0x0C,                              /* [1]Mode Data Length */
    0x00,                              /* [2]Medium Type Code(00h-FFh Vendor Specific) */
    0x00,                              /* [3]b7:WP(Write Protect), b6-b0:Reserved */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    /* Page(Cashing Page 12byte) */
    0x08,                              /* [0]b7:PS, b6:Reserved, b5-b0:Page Code(08h) */
    0x0A,                              /* [1]Page Length(0Ah) */
    0x00,                              /* [2]b7-b3:Reserved, b2:WCE, b1:Reserved, b0:RCD */
    0x00,                              /* [3]Reserved */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    0x00,                              /* [8]Reserved */
    0x00,                              /* [9]Reserved */
    0x00,                              /* [10]Reserved */
    0x00                               /* [11]Reserved */
};

/* Mode Sense data (Removable Block Access Capacities Page 12byte) */
static uint8_t g_usb_atapi_ms_capa_tbl[USB_ATAPI_MODE_SENSE10_CAP_P_SIZE] =
{
    /* Mode Parameter List */
    0x00,                              /* [0]Mode Data Length */
    0x0C,                              /* [1]Mode Data Length */
    0x00,                              /* [2]Medium Type Code(00h-FFh Vendor Specific) */
    0x00,                              /* [3]b7:WP(Write Protect), b6-b0:Reserved */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    /* Page(Removable Block Access Capacities Page 12byte) */
    0x1B,                              /* [0]b7:PS, b6:Reserved, b5-b0:Page Code(1Bh) */
    0x0A,                              /* [1]Page Length(0Ah) */
    0x00,                              /* [2]b7:Reserved, b6:SRFP, b5-b0:Reserved */
    0x00,                              /* [3]b7:NCD, b6:SML, b5-b3:Reserved, b2-b0:TLUN */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    0x00,                              /* [8]Reserved */
    0x00,                              /* [9]Reserved */
    0x00,                              /* [10]Reserved */
    0x00                               /* [11]Reserved */
};

/* Mode Sense data (Timer & Protect Page 8byte) */
static uint8_t g_usb_atapi_ms_op_cmd_tbl[USB_ATAPI_MODE_SENSE10_OP_CMD_SIZE] =
{
    /* Mode Parameter List */
    0x00,                              /* [0]Mode Data Length */
    0x08,                              /* [1]Mode Data Length */
    0x00,                              /* [2]Medium Type Code(00h-FFh Vendor Specific) */
    0x00,                              /* [3]b7:WP(Write Protect), b6-b0:Reserved */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    /* Page(Timer & Protect Page 8byte) */
    0x1C,                              /* [0]b7:PS, b6:Reserved, b5-b0:Page Code(1Ch) */
    0x0A,                              /* [1]Page Length(06h) */
    0x00,                              /* [2]Reserved */
    0x00,                              /* [3]b7-b4:Reserved, b3-b0:Inactivity Time Multiplier */
    0x00,                              /* [4]b7-b2:Reserved, b2:WCE, b1:DISP, b0:SWPP */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    0x00,                              /* [4]b7-b2:Reserved, b2:WCE, b1:DISP, b0:SWPP */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00                               /* [7]Reserved */
};

/* Mode Sense data (All Page) */
static uint8_t g_usb_atapi_ms_all_tbl[USB_ATAPI_MODE_SENSE10_ALL_P_SIZE] =
{
    /* Mode Parameter List */
    0x00,                              /* [0]Mode Data Length */
    USB_VALUE_ALL_PAGE_LENGTH,         /* [1]Mode Data Length */
    0x00,                              /* [2]Medium Type Code(00h-FFh Vendor Specific) */
    0x00,                              /* [3]b7:WP(Write Protect), b6-b0:Reserved */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    /* Page(ReadWrite Error Recovery Page 12byte) */
    0x01,                              /* [0]b7:PS, b6:Reserved, b5-b0:Page Code(01h) */
    0x0A,                              /* [1]Page Length(0Ah) */
    0x00,                              /* [2]Error Recovery Parameters */
                                       /*    b7:AWRE, b6:Reserved, b5:TB, b4:RC, b3:Reserved, b2:PER, b1:Reserved, b0:DCR*/
    0x00,                              /* [3]Read Retry Count */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    0x00,                              /* [8]Write Retry Count */
    0x00,                              /* [9]Reserved */
    0x00,                              /* [10]Reserved */
    0x00,                              /* [11]Reserved */
    /* Page(Cashing Page 12byte) */
    0x08,                              /* [0]b7:PS, b6:Reserved, b5-b0:Page Code(08h) */
    0x0A,                              /* [1]Page Length(0Ah) */
    0x00,                              /* [2]b7-b3:Reserved, b2:WCE, b1:Reserved, b0:RCD */
    0x00,                              /* [3]Reserved */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    0x00,                              /* [8]Reserved */
    0x00,                              /* [9]Reserved */
    0x00,                              /* [10]Reserved */
    0x00,                              /* [11]Reserved */
    /* Page(Removable Block Access Capacities Page 12byte) */
    0x1B,                              /* [0]b7:PS, b6:Reserved, b5-b0:Page Code(1Bh) */
    0x0A,                              /* [1]Page Length(0Ah) */
    0x00,                              /* [2]b7:Reserved, b6:SRFP, b5-b0:Reserved */
    0x00,                              /* [3]b7:NCD, b6:SML, b5-b3:Reserved, b2-b0:TLUN */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00,                              /* [7]Reserved */
    0x00,                              /* [8]Reserved */
    0x00,                              /* [9]Reserved */
    0x00,                              /* [10]Reserved */
    0x00                               /* [11]Reserved */
};

/* Mode Sense data (Page code error) */
static uint8_t g_usb_atapi_ms_err_tbl[USB_ATAPI_MODE_SENSE10_P_CODE_ERR_SIZE] =
{
    0x00,                              /* [0]Mode Data Length */
    0x00,                              /* [1]Mode Data Length */
    0x00,                              /* [2]Medium Type Code(00h-FFh Vendor Specific) */
    0x00,                              /* [3]b7:WP(Write Protect), b6-b0:Reserved */
    0x00,                              /* [4]Reserved */
    0x00,                              /* [5]Reserved */
    0x00,                              /* [6]Reserved */
    0x00                               /* [7]Reserved */
};

static const uint8_t g_usb_atapi_dummy_tbl[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Renesas Abstracted ATAPI Driver API functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: pmsc_atapi_analyze_cbwcb
 * Description  : Analyze ATAPI commands
 * Arguments    : uint8_t       *cbwcb       : CBW
 * Return value : none
 ***********************************************************************************************************************/
void pmsc_atapi_analyze_cbwcb (uint8_t * cbwcb)
{
    uint32_t ar_rst;                   /* Used to pass back result codes. */
    uint32_t ar_size   = 0;            /* Used to return the number of bytes requested to be transferred. */
    uint32_t temp_size = 0;
    uint8_t  page_code;
    uint32_t num_blocks;               /* Number of contiguous blocks in the media device. */
    uint32_t block_length;             /* The length in bytes of each logical block. */
    uint32_t media_size;

    ar_rst = USB_ATAPI_NOT_SUPPORT;
    g_usb_atapi_is_data_stage = USB_FALSE;

    g_usb_atapi_cbwcb = (usb_pmsc_cdb_t *) cbwcb;

    switch (g_usb_atapi_cbwcb->s_usb_ptn0.uc_opcode)
    {
        case USB_ATAPI_READ10:
        {
            /* Set Request Parameter */
            /* Number of blocks requested. */
            ar_size = (((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.us_length_hi << 8) |
                       (uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.us_length_lo);

            /* Convert block count to byte count. */
            ar_size = (ar_size * (uint32_t) USB_CFG_PMSC_ATAPI_BLOCK_UNIT);

            ar_rst = USB_ATAPI_SND_DATAS;

            break;
        }

        case USB_ATAPI_WRITE10:
        {
            /* Set Request Parameter */
            /* Number of blocks requested. */
            ar_size = (((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.us_length_hi << 8) |
                       (uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.us_length_lo);

            /* Convert block count to byte count. */
            ar_size = (ar_size * (uint32_t) USB_CFG_PMSC_ATAPI_BLOCK_UNIT);

            /* Query the media device for total block count. */
            r_usb_pmsc_media_ioctl(USB_MEDIA_IOCTL_GET_NUM_BLOCKS, &num_blocks);

            /* Query the media device for block size in bytes. */
            r_usb_pmsc_media_ioctl(USB_MEDIA_IOCTL_GET_BLOCK_SIZE, &block_length);

            media_size = block_length * num_blocks;

            if (media_size <= ar_size)
            {
                ar_rst = USB_ATAPI_NOT_SUPPORT;
            }
            else
            {
                ar_rst = USB_ATAPI_RCV_DATAS;
            }

            break;
        }

        case USB_ATAPI_TEST_UNIT_READY:
        {
            ar_rst  = USB_ATAPI_NO_DATA;
            ar_size = USB_ATAPI_DATA_SIZE_0;

            break;
        }

        case USB_ATAPI_INQUIRY:
        {
            ar_size = g_usb_atapi_cbwcb->s_usb_ptn12.uc_allocation;

            temp_size = USB_ATAPI_INQUIRY_SIZE;

            ar_rst = USB_ATAPI_SND_DATAS;

            break;
        }

        case USB_ATAPI_REQUEST_SENSE:
        {
            ar_size = g_usb_atapi_cbwcb->s_usb_ptn12.uc_allocation;

            temp_size = USB_ATAPI_REQUEST_SENSE_SIZE;

            ar_rst = USB_ATAPI_SND_DATAS;

            break;
        }

        case USB_ATAPI_MODE_SENSE10:
        {
            /* Set Request Parameter */
            ar_size = (((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.us_length_hi << 8) |
                       (uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.us_length_lo);

            page_code = g_usb_atapi_cbwcb->s_usb_ptn0.uc_data & (uint8_t) (USB_VALUE_MASK_3FH);
            pmsc_atapi_get_mode_sense10_data(page_code, &temp_size, USB_NULL);

            ar_rst = USB_ATAPI_SND_DATAS;

            break;
        }

        case USB_ATAPI_READ_FORMAT_CAPACITY:
        {
            /* Set Request Parameter */
            ar_size = (((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.us_length_hi << 8) |
                       (uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.us_length_lo);

            temp_size = USB_ATAPI_READ_FORMAT_CAPACITY_SIZE;

            ar_rst = USB_ATAPI_SND_DATAS;

            break;
        }

        case USB_ATAPI_READ_CAPACITY:
        {
            ar_size = USB_ATAPI_READ_CAPACITY_SIZE;
            ar_rst  = USB_ATAPI_SND_DATAS;

            break;
        }

        default:
        {
            USB_PRINTF0("### CBW Command Not Support\n");

            break;
        }
    }

    if ((ar_size > temp_size) && (0 != temp_size))
    {
        ar_size = temp_size;
    }

    if ((0UL == ar_size) && (USB_ATAPI_NOT_SUPPORT != ar_rst))
    {
        ar_rst = USB_ATAPI_NO_DATA;
    }

    g_usb_pmsc_message.ar_rst  = ar_rst;
    g_usb_pmsc_message.ul_size = ar_size; /* Assign the current byte count requested by host in this cycle. */
} /* End of function pmsc_atapi_analyze_cbwcb() */

/***********************************************************************************************************************
 * Function Name: pmsc_atapi_get_read_data
 * Description  : Get read data
 * Arguments    : uint32_t      *size        : data size
 *              : uint8_t       **buff       : data address
 * Return value : none
 ***********************************************************************************************************************/
static void pmsc_atapi_get_read_data (uint32_t * size, uint8_t ** buff)
{
    uint32_t num_blocks;               /* Number of contiguous blocks in the media device. */
    uint32_t block_length;             /* The length in bytes of each logical block. */
    uint32_t trans_block;
    uint8_t  page_code;

    switch (g_usb_atapi_cbwcb->s_usb_ptn0.uc_opcode)
    {
        case USB_ATAPI_READ10:
        {
            if (USB_FALSE == g_usb_atapi_is_data_stage)
            {
                /* Get the LBA from the command data block structure. It's in Big Endian format. */
                g_usb_atapi_cur_lba = ((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.ul_logical_block0 << 24) |
                                      ((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.ul_logical_block1 << 16) |
                                      ((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.ul_logical_block2 << 8) |
                                      ((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.ul_logical_block3);
            }

            /* Calculate the number of logical blocks to read */
            if (g_usb_pmsc_message.ul_size < (USB_CFG_PMSC_ATAPI_BLOCK_UNIT * USB_CFG_PMSC_TRANS_COUNT))
            {
                trans_block = g_usb_pmsc_message.ul_size / USB_CFG_PMSC_ATAPI_BLOCK_UNIT;
            }
            else
            {
                trans_block = USB_CFG_PMSC_TRANS_COUNT;
            }

            r_usb_pmsc_media_read(&g_usb_pmsc_media_buffer[0], g_usb_atapi_cur_lba, (uint8_t) trans_block);

            g_usb_atapi_cur_lba += trans_block;

            *size = (USB_CFG_PMSC_ATAPI_BLOCK_UNIT * trans_block);
            *buff = &g_usb_pmsc_media_buffer[0];

            break;
        }

        case USB_ATAPI_INQUIRY:
        {
            memcpy((void *) &g_usb_atapi_inquiry_tbl[8], USB_CFG_PMSC_VENDOR, USB_ATAPI_INQUIRY_VENDOR_SIZE);
            memcpy((void *) &g_usb_atapi_inquiry_tbl[16], USB_CFG_PMSC_PRODUCT, USB_ATAPI_INQUIRY_PRODUCT_SIZE);
            memcpy((void *) &g_usb_atapi_inquiry_tbl[USB_VALUE_32],
                   USB_CFG_PMSC_REVISION,
                   USB_ATAPI_INQUIRY_REVISION_SIZE);

            *size = USB_ATAPI_INQUIRY_SIZE;
            *buff = &g_usb_atapi_inquiry_tbl[0];

            break;
        }

        case USB_ATAPI_REQUEST_SENSE:
        {
            *size = USB_ATAPI_REQUEST_SENSE_SIZE;
            *buff = (uint8_t *) &g_usb_atapi_rs_tbl[0];

            break;
        }

        case USB_ATAPI_MODE_SENSE10:
        {
            page_code = g_usb_atapi_cbwcb->s_usb_ptn0.uc_data & (uint8_t) (USB_VALUE_MASK_3FH);
            pmsc_atapi_get_mode_sense10_data(page_code, size, buff);

            break;
        }

        case USB_ATAPI_READ_FORMAT_CAPACITY:
        {
            /* Query the media device for total block count. */
            r_usb_pmsc_media_ioctl(USB_MEDIA_IOCTL_GET_NUM_BLOCKS, &num_blocks);

            /* Query the media device for block size in bytes. */
            r_usb_pmsc_media_ioctl(USB_MEDIA_IOCTL_GET_BLOCK_SIZE, &block_length);

            /* Current/Maximum Capacity Descriptor */
            /* Total Number of blocks in storage media */
            g_usb_atapi_read_f_capa_tbl[4] = (uint8_t) ((num_blocks >> 24) & (uint8_t) USB_VALUE_MASK_FFH);  /* MSB */
            g_usb_atapi_read_f_capa_tbl[5] = (uint8_t) ((num_blocks >> 16) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_f_capa_tbl[6] = (uint8_t) ((num_blocks >> 8) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_f_capa_tbl[7] = (uint8_t) (num_blocks & (uint8_t) USB_VALUE_MASK_FFH);          /* LSB */

            /* Descriptor Block Length field. */
            g_usb_atapi_read_f_capa_tbl[8]  = 0;                                                             /* Reserved byte */
            g_usb_atapi_read_f_capa_tbl[9]  = (uint8_t) ((block_length >> 16) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_f_capa_tbl[10] = (uint8_t) ((block_length >> 8) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_f_capa_tbl[11] = (uint8_t) (block_length & (uint8_t) USB_VALUE_MASK_FFH);       /* LSB */

            /* Formattable Capacity Descriptor */
            /* Total Number of blocks in storage media */
            g_usb_atapi_read_f_capa_tbl[12] = (uint8_t) ((num_blocks >> 24) & (uint8_t) USB_VALUE_MASK_FFH); /* MSB */
            g_usb_atapi_read_f_capa_tbl[13] = (uint8_t) ((num_blocks >> 16) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_f_capa_tbl[14] = (uint8_t) ((num_blocks >> 8) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_f_capa_tbl[15] = (uint8_t) (num_blocks & (uint8_t) USB_VALUE_MASK_FFH);         /* LSB */

            /* Descriptor Block Length field */
            g_usb_atapi_read_f_capa_tbl[16] = 0;                                                             /* Reserved byte */
            g_usb_atapi_read_f_capa_tbl[17] = (uint8_t) ((block_length >> 16) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_f_capa_tbl[18] = (uint8_t) ((block_length >> 8) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_f_capa_tbl[19] = (uint8_t) (block_length & (uint8_t) USB_VALUE_MASK_FFH);       /* LSB */

            *size = USB_ATAPI_READ_FORMAT_CAPACITY_SIZE;
            *buff = &g_usb_atapi_read_f_capa_tbl[0];

            break;
        }

        case USB_ATAPI_READ_CAPACITY:  /* READ CAPACITY Data */
        {
            /* Query the media device for total block count. */
            r_usb_pmsc_media_ioctl(USB_MEDIA_IOCTL_GET_NUM_BLOCKS, &num_blocks);

            /* Query the media device for block size in bytes. */
            r_usb_pmsc_media_ioctl(USB_MEDIA_IOCTL_GET_BLOCK_SIZE, &block_length);

            /* Fill in READ CAPACITY Data Last Logical Block Address field. 0-based. */
            g_usb_atapi_read_capa_tbl[0] = (uint8_t) (((num_blocks - 1UL) >> 24) & (uint8_t) USB_VALUE_MASK_FFH); /* MSB */
            g_usb_atapi_read_capa_tbl[1] = (uint8_t) (((num_blocks - 1UL) >> 16) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_capa_tbl[2] = (uint8_t) (((num_blocks - 1UL) >> 8) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_capa_tbl[3] = (uint8_t) ((num_blocks - 1UL) & (uint8_t) USB_VALUE_MASK_FFH);         /* LSB */

            /* Fill in READ CAPACITY Data Block Length field */
            g_usb_atapi_read_capa_tbl[4] = (uint8_t) ((block_length >> 24) & (uint8_t) USB_VALUE_MASK_FFH);       /* MSB */
            g_usb_atapi_read_capa_tbl[5] = (uint8_t) ((block_length >> 16) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_capa_tbl[6] = (uint8_t) ((block_length >> 8) & (uint8_t) USB_VALUE_MASK_FFH);
            g_usb_atapi_read_capa_tbl[7] = (uint8_t) (block_length & (uint8_t) USB_VALUE_MASK_FFH);               /* LSB */

            *size = USB_ATAPI_READ_CAPACITY_SIZE;
            *buff = &g_usb_atapi_read_capa_tbl[0];

            break;
        }

        default:
        {
            *size = 0;
            *buff = (uint8_t *) &g_usb_atapi_dummy_tbl[0];

            break;
        }
    }

    if ((g_usb_pmsc_message.ul_size < *size) && (USB_ATAPI_READ10 != g_usb_atapi_cbwcb->s_usb_ptn0.uc_opcode))
    {
        *size = g_usb_pmsc_message.ul_size;
    }
}                                      /* End of function pmsc_atapi_get_read_data() */

/***********************************************************************************************************************
 * Function Name: pmsc_atapi_command_processing
 * Description  : ATAPI Command Transfer
 * Arguments    : uint8_t       *cbw         : CBW
 *              : uint16_t      status       : status
 *              : usb_cb_t      complete     : callback
 * Return value : usb_er_t                   : error
 ***********************************************************************************************************************/
void pmsc_atapi_command_processing (uint8_t * cbw, uint16_t usb_result, usb_cb_t complete, uint8_t module_number)
{
    static usb_utr_t atapi_mess;
    static void    * p_atapi_rw_buff;    /* Transfer Address */
    static uint32_t  real_data_count;    /* The amount of real data transferred */
    static uint32_t  this_transfer_size; /* Transfer Size */
    uint32_t         residue_size;
    uint16_t         status;
    uint32_t         trans_block;

    g_usb_atapi_cbwcb = (usb_pmsc_cdb_t *) cbw;

    switch (g_usb_atapi_cbwcb->s_usb_ptn0.uc_opcode)
    {
        /* Analyze opcode  */
        /* Send Data Commands (from Device to Host) */
        case USB_ATAPI_READ10:
        case USB_ATAPI_INQUIRY:
        case USB_ATAPI_REQUEST_SENSE:
        case USB_ATAPI_MODE_SENSE10:
        case USB_ATAPI_READ_FORMAT_CAPACITY:
        case USB_ATAPI_READ_CAPACITY:
        {
            if (USB_FALSE == g_usb_atapi_is_data_stage)
            {
                if (0UL != g_usb_pmsc_message.ul_size)
                {
                    /* Returns with pointers to the expected data and the expected size. */
                    pmsc_atapi_get_read_data(&this_transfer_size, (uint8_t **) &p_atapi_rw_buff);

                    real_data_count           = 0UL; /* Clear this to initialize for new transfer cycle. */
                    status                    = (uint16_t) USB_PMSC_CMD_CONTINUE;
                    g_usb_atapi_is_data_stage = USB_TRUE;
                }
                else
                {
                    status = (uint16_t) USB_PMSC_CMD_COMPLETE;
                }
            }
            else
            {
                if (USB_DATA_NONE == usb_result)
                {
                    /* Previous Transfer OK */
                    real_data_count += this_transfer_size;
                    residue_size     = g_usb_pmsc_message.ul_size - real_data_count;

                    if (0UL != residue_size)
                    {
                        /* More data to transfer. */
                        pmsc_atapi_get_read_data(&this_transfer_size, (uint8_t **) &p_atapi_rw_buff);
                        if (residue_size < this_transfer_size)
                        {
                            this_transfer_size = residue_size;
                        }

                        status = (uint16_t) USB_PMSC_CMD_CONTINUE;
                    }
                    else
                    {
                        if (g_usb_pmsc_dtl == g_usb_pmsc_message.ul_size)
                        {
                            status = (uint16_t) USB_PMSC_CMD_COMPLETE; /* case 6 */
                        }
                        else
                        {
                            if ((USB_ATAPI_MODE_SENSE10 == g_usb_atapi_cbwcb->s_usb_ptn0.uc_opcode) ||
                                (USB_ATAPI_READ_FORMAT_CAPACITY == g_usb_atapi_cbwcb->s_usb_ptn0.uc_opcode))
                            {
                                if (g_usb_pmsc_dtl > g_usb_pmsc_message.ul_size)
                                {
#if (USB_ATAPI_SHT_RESPONSE == 0)
                                    status = (uint16_t) USB_PMSC_CMD_SHT_COMPLETE; /* case 5 */
#else                                                                              /* USB_ATAPI_SHT_RESPONSE == 0 */
                                    status = (uint16_t) USB_PMSC_CMD_COMPLETE;     /* case 5 */
#endif  /* USB_ATAPI_SHT_RESPONSE == 0 */
                                }
                                else
                                {
                                    status = (uint16_t) USB_PMSC_CMD_FAILED; /* case 7*/
                                }
                            }
                            else
                            {
                                status = (uint16_t) USB_PMSC_CMD_FAILED; /* case 5 & 7*/
                            }
                        }

                        g_usb_pmsc_dtl            = g_usb_pmsc_dtl - g_usb_pmsc_message.ul_size;
                        g_usb_atapi_is_data_stage = USB_FALSE;
                    }
                }
                else
                {
                    /* Previous Transfer Fail */
                    status = (uint16_t) USB_PMSC_CMD_FAILED;
                    g_usb_atapi_is_data_stage = USB_FALSE;
                }
            }

            break;
        }

        /* Receive Data Commands (from Host to Device) */
        case USB_ATAPI_WRITE10:
        {
            if (USB_FALSE == g_usb_atapi_is_data_stage)
            {
                if (0UL != g_usb_pmsc_message.ul_size)
                {
                    /* Get the LBA from the command data block structure. It's in Big Endian format. */
                    g_usb_atapi_cur_lba = ((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.ul_logical_block0 << 24) |
                                          ((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.ul_logical_block1 << 16) |
                                          ((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.ul_logical_block2 << 8) |
                                          ((uint32_t) g_usb_atapi_cbwcb->s_usb_ptn4569.ul_logical_block3);

                    /* Retrieve the location and size of the write buffer. */
                    this_transfer_size = g_usb_pmsc_message.ul_size;
                    p_atapi_rw_buff    = &g_usb_pmsc_media_buffer[0];

                    if (this_transfer_size > (USB_CFG_PMSC_ATAPI_BLOCK_UNIT * USB_CFG_PMSC_TRANS_COUNT))
                    {
                        /* Divide Size for WRITE10 & WRITE_AND_VERIFY*/
                        this_transfer_size = (USB_CFG_PMSC_ATAPI_BLOCK_UNIT * USB_CFG_PMSC_TRANS_COUNT);
                    }

                    real_data_count           = 0UL;
                    status                    = (uint16_t) USB_PMSC_CMD_CONTINUE;
                    g_usb_atapi_is_data_stage = USB_TRUE; /* Flag that the command has been initialized. */
                }
                else
                {
                    status = (uint16_t) USB_PMSC_CMD_COMPLETE;
                }
            }
            else
            {
                if (USB_DATA_OK == usb_result) /* Previous Transfer OK */
                {
                    p_atapi_rw_buff = &g_usb_pmsc_media_buffer[0];

                    trans_block = this_transfer_size / USB_CFG_PMSC_ATAPI_BLOCK_UNIT;
                    if (0 != (this_transfer_size % USB_CFG_PMSC_ATAPI_BLOCK_UNIT))
                    {
                        trans_block++;
                    }

                    /* Write will be limited to max one block at a time */
                    r_usb_pmsc_media_write(&g_usb_pmsc_media_buffer[0], g_usb_atapi_cur_lba, (uint8_t) trans_block);
                    g_usb_atapi_cur_lba += trans_block;

                    /* Update the count of data transferred so far. */
                    real_data_count = real_data_count + this_transfer_size;

                    /* Deduct the amount transferred from the total requested. */
                    residue_size = g_usb_pmsc_message.ul_size - real_data_count;
                    if (0 != residue_size)
                    {
                        if (residue_size < this_transfer_size)
                        {
                            this_transfer_size = residue_size;
                        }

                        status = (uint16_t) USB_PMSC_CMD_CONTINUE;
                    }
                    else
                    {
                        /* All data in Device recieved */
                        if (g_usb_pmsc_dtl == g_usb_pmsc_message.ul_size)
                        {
                            /* case 12 */
                            status = (uint16_t) USB_PMSC_CMD_COMPLETE;
                        }
                        else
                        {
                            /* case 11 & 13*/
                            status = (uint16_t) USB_PMSC_CMD_FAILED;
                        }

                        g_usb_pmsc_dtl            = g_usb_pmsc_dtl - g_usb_pmsc_message.ul_size;
                        g_usb_atapi_is_data_stage = USB_FALSE;
                    }
                }
                else
                {
                    /* Previous Transfer Fail */
                    status = (uint16_t) USB_PMSC_CMD_FAILED;
                    g_usb_atapi_is_data_stage = USB_FALSE;
                }
            }

            break;
        }

        /* No Send or Receive Data Commands */
        case USB_ATAPI_TEST_UNIT_READY:
        {
            status = (uint16_t) USB_PMSC_CMD_COMPLETE;

            break;
        }

        case USB_ATAPI_PREVENT_ALLOW:
        {
            status = (uint16_t) USB_PMSC_CMD_FAILED;

            break;
        }

        default:
        {
            status = (uint16_t) USB_PMSC_CMD_ERROR;
            USB_PRINTF0("### Command Execute error (1st sequence) \n");
            g_usb_atapi_is_data_stage = USB_FALSE;

            break;
        }
    }

    /* Set mess members */
    atapi_mess.p_tranadr     = p_atapi_rw_buff;
    atapi_mess.tranlen       = this_transfer_size;
    atapi_mess.status        = status;
    atapi_mess.ip            = module_number;
    atapi_mess.p_transfer_rx = g_usb_pmsc_utr.p_transfer_rx;
    atapi_mess.p_transfer_tx = g_usb_pmsc_utr.p_transfer_tx;

    complete(&atapi_mess, USB_NULL, USB_NULL);
}                                      /* End of function pmsc_atapi_command_processing() */

/***********************************************************************************************************************
 * Function Name: pmsc_atapi_get_mode_sense10_data
 * Description  : Get read data
 * Arguments    : uint8_t       page_code    : MODE SENSE10 Page Code
 *              : uint32_t      *size        : data size
 *              : uint8_t       **buff       : data address(USB_NULL:no use. data size only)
 * Return value : none
 ***********************************************************************************************************************/
static void pmsc_atapi_get_mode_sense10_data (uint8_t page_code, uint32_t * size, uint8_t ** buff)
{
    uint8_t * p_data;
    uint32_t  write_protect = 0;

    r_usb_pmsc_media_ioctl(USB_MEDIA_IOCTL_GET_WRITE_PROTECT_INFO, &write_protect);

    switch (page_code)
    {
        case 0x00:                     /* Mode Parameter Header */
        {
            *size = USB_ATAPI_MODE_SENSE10_MODE_PARAM_SIZE;
            g_usb_atapi_ms_mp_tbl[3] |= (uint8_t) (write_protect << 0x07);
            p_data = &g_usb_atapi_ms_mp_tbl[0];

            break;
        }

        case 0x01:                     /* ReadWrite Error Recovery Page */
        {
            *size = USB_ATAPI_MODE_SENSE10_ERR_RCVR_P_SIZE;
            g_usb_atapi_ms_rcvr_tbl[3] |= (uint8_t) (write_protect << 0x07);
            p_data = &g_usb_atapi_ms_rcvr_tbl[0];

            break;
        }

        case 0x08:                     /* Cashing Page */
        {
            *size = USB_ATAPI_MODE_SENSE10_CASHING_P_SIZE;
            g_usb_atapi_ms_cash_tbl[3] |= (uint8_t) (write_protect << 0x07);
            p_data = &g_usb_atapi_ms_cash_tbl[0];

            break;
        }

        case 0x1B:                     /* Removable Block Access Capacities Page */
        {
            *size = USB_ATAPI_MODE_SENSE10_CAP_P_SIZE;
            g_usb_atapi_ms_capa_tbl[3] |= (uint8_t) (write_protect << 0x07);
            p_data = &g_usb_atapi_ms_capa_tbl[0];

            break;
        }

        case 0x1C:                     /* Timer & Protect Page */
        {
            *size = USB_ATAPI_MODE_SENSE10_OP_CMD_SIZE;
            g_usb_atapi_ms_op_cmd_tbl[3] |= (uint8_t) (write_protect << 0x07);
            p_data = &g_usb_atapi_ms_op_cmd_tbl[0];

            break;
        }

        case USB_VALUE_MODE_SENSE10_ALL_PAGE: /* All Page */
        {
            *size = USB_ATAPI_MODE_SENSE10_ALL_P_SIZE;
            g_usb_atapi_ms_all_tbl[3] |= (uint8_t) (write_protect << 0x07);
            p_data = &g_usb_atapi_ms_all_tbl[0];

            break;
        }

        default:
        {
            *size = USB_ATAPI_MODE_SENSE10_P_CODE_ERR_SIZE;
            g_usb_atapi_ms_err_tbl[3] |= (uint8_t) (write_protect << 0x07);
            p_data = &g_usb_atapi_ms_err_tbl[0];

            break;
        }
    }

    if (USB_NULL != buff)
    {
        *buff = p_data;
    }
}                                      /* End of function pmsc_atapi_get_mode_sense10_data() */

/***********************************************************************************************************************
 * Function Name: pmsc_atapi_init
 * Description  :
 * Arguments    : none
 * Return value : none
 ***********************************************************************************************************************/
void pmsc_atapi_init (void)
{
    memset((void *) &g_usb_pmsc_media_buffer, 0, (USB_CFG_PMSC_ATAPI_BLOCK_UNIT * USB_CFG_PMSC_TRANS_COUNT));
    g_usb_atapi_cbwcb   = USB_NULL;
    g_usb_atapi_cur_lba = 0;
}                                      /* End of function pmsc_atapi_init() */

/***********************************************************************************************************************
 * End Of File
 ***********************************************************************************************************************/
