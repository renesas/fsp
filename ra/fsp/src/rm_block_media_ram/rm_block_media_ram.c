/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_block_media_ram.h"
#include "rm_block_media_ram_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RM_BLOCK_MEDIA_RAM_FAT16_LIMIT            (65525)
#define RM_BLOCK_MEDIA_RAM_FAT12_LIMIT            (4085)
#define RM_BLOCK_MEDIA_RAM_JMP_CODE_1             (0xEB)
#define RM_BLOCK_MEDIA_RAM_JMP_CODE_2             (0x3C)
#define RM_BLOCK_MEDIA_RAM_JMP_CODE_3             (0x90)

#define RM_BLOCK_MEDIA_RAM_SECTOR_SIZE            (512)
#define RM_BLOCK_MEDIA_RAM_SECTOR_COUNT           (RM_BLOCK_MEDIA_RAM_CFG_MEDIA_SIZE / RM_BLOCK_MEDIA_RAM_SECTOR_SIZE)

#define RM_BLOCK_MEDIA_RAM_MEDIATYPE              (0xF8U)
#define RM_BLOCK_MEDIA_RAM_SIGNATURE              (0xAA55U)

#define RM_BLOCK_MEDIA_RAM_SECTORS_PER_CLUSTER    (0x01U)
#define RM_BLOCK_MEDIA_RAM_NUM_FATS               (0x02U)

/* "SRAM" in ASCII, used to identify general RM_BLOCK_MEDIA_RAM control block */
#define RM_BLOCK_MEDIA_RAM_OPEN                   (0x5352414D)
#define RM_BLOCK_MEDIA_RAM_RESERVED_SECTORS       (0x2)

/*
 * FAT12 and FAT16 media typically use 512 root directory
 * entries on non-floppy media. Some third-party tools,
 * like mkdosfs, allow the user to set this parameter.
 */
#define RM_BLOCK_MEDIA_RAM_DIRECTORY_ENTRIES      (0x200)

/* 32 bytes per directory entry */
#define RM_BLOCK_MEDIA_RAM_DIRECTORY_SECTORS      (((RM_BLOCK_MEDIA_RAM_DIRECTORY_ENTRIES * 32) + \
                                                    (RM_BLOCK_MEDIA_RAM_SECTOR_SIZE - 1)) /       \
                                                   RM_BLOCK_MEDIA_RAM_SECTOR_SIZE)

#define RM_BLOCK_MEDIA_RAM_CLUSTER_COUNT          (RM_BLOCK_MEDIA_RAM_SECTOR_COUNT -     \
                                                   RM_BLOCK_MEDIA_RAM_RESERVED_SECTORS - \
                                                   RM_BLOCK_MEDIA_RAM_DIRECTORY_SECTORS)

/* 2 bytes per cluster needed in the FAT */
#define RM_BLOCK_MEDIA_RAM_SECTORS_PER_FAT        (((RM_BLOCK_MEDIA_RAM_CLUSTER_COUNT * 2) + \
                                                    (RM_BLOCK_MEDIA_RAM_SECTOR_SIZE - 1)) /  \
                                                   RM_BLOCK_MEDIA_RAM_SECTOR_SIZE)

#define RM_BLOCK_MEDIA_RAM_USABLE_CLUSTERS        (RM_BLOCK_MEDIA_RAM_CLUSTER_COUNT - \
                                                   (RM_BLOCK_MEDIA_RAM_SECTORS_PER_FAT * RM_BLOCK_MEDIA_RAM_NUM_FATS))

/*
 * If the number of data areas of clusters is smaller
 * than that of value 4085(4096-11), it is FAT12.
 * If the number of data areas of clusters is smaller
 * than that of value 65525(65536-11), it is FAT16.
 * Otherwise it is FAT32.
 */
#if RM_BLOCK_MEDIA_RAM_USABLE_CLUSTERS >= RM_BLOCK_MEDIA_RAM_FAT16_LIMIT
 #define RM_BLOCK_MEDIA_RAM_FAT_TYPE              (32)
#elif RM_BLOCK_MEDIA_RAM_USABLE_CLUSTERS >= RM_BLOCK_MEDIA_RAM_FAT12_LIMIT
 #define RM_BLOCK_MEDIA_RAM_FAT_TYPE              (16)
#else
 #define RM_BLOCK_MEDIA_RAM_FAT_TYPE              (12)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* RM_BLOCK_MEDIA_RAM_SECTOR_SIZE = 512 */
static const uint8_t g_block_media_ram_boot_sector[RM_BLOCK_MEDIA_RAM_SECTOR_SIZE] =
{
    /* 0x00     3   The first three bytes EB 3C 90 disassemble to JMP SHORT 3C NOP. */
    RM_BLOCK_MEDIA_RAM_JMP_CODE_1,                                       RM_BLOCK_MEDIA_RAM_JMP_CODE_2,
    RM_BLOCK_MEDIA_RAM_JMP_CODE_3,

    /* 0x03     8   OEM identifier. */
    'M',                                                                 'S',
    'D',                                                                 'O',
    'S',                                                                 '5',
    '.',                                                                 '0',

    /* 0x0B     2   The number of Bytes per sector (remember, all numbers are in the little-endian format). */
    (uint8_t) (RM_BLOCK_MEDIA_RAM_SECTOR_SIZE & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_SECTOR_SIZE >> 8) & UINT8_MAX),

    /* 0x0D     1   Number of sectors per cluster. */
    RM_BLOCK_MEDIA_RAM_SECTORS_PER_CLUSTER,

    /* 0x0E     2   Number of reserved sectors. The boot record sectors are included in this value. */
    (uint8_t) (RM_BLOCK_MEDIA_RAM_RESERVED_SECTORS & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_RESERVED_SECTORS >> 8) & UINT8_MAX),

    /* 0x10     1   Number of File Allocation Tables (FAT's) on the storage media. Often this value is 2. */
    RM_BLOCK_MEDIA_RAM_NUM_FATS,

    /* 0x11     2   Number of root directory entries (must be set so that the root directory occupies entire sectors). */
#if RM_BLOCK_MEDIA_RAM_FAT_TYPE != 32
    (uint8_t) (RM_BLOCK_MEDIA_RAM_DIRECTORY_ENTRIES & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_DIRECTORY_ENTRIES >> 8) & UINT8_MAX),
#else
    0x00,                                                                0x00,
#endif

    /* 0x13     2   The total sectors in the logical volume. If this value is 0, it means there are more than 65535 sectors in the volume, and the actual count is stored in the Large Sector Count entry at 0x20. */
#if RM_BLOCK_MEDIA_RAM_SECTOR_COUNT < 0x10000
    (uint8_t) (RM_BLOCK_MEDIA_RAM_SECTOR_COUNT & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_SECTOR_COUNT >> 8) & UINT8_MAX),
#else
    0x00,                                                                0x00,
#endif

    /* 0x15     1   This Byte indicates the media descriptor type. */
    RM_BLOCK_MEDIA_RAM_MEDIATYPE,

    /* 0x16     2   Number of sectors per FAT. FAT12/FAT16 only. */
#if RM_BLOCK_MEDIA_RAM_FAT_TYPE != 32
    (uint8_t) (RM_BLOCK_MEDIA_RAM_SECTORS_PER_FAT & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_SECTORS_PER_FAT >> 8) & UINT8_MAX),
#else
    0x00,                                                                0x00,
#endif

    /* 0x18    2   Number of sectors per track.  */
    0x00,                                                                0x00,

    /* 0x1A     2   Number of heads or sides on the storage media. */
    0x00,                                                                0x00,

    /* 0x1C     4   Number of hidden sectors. (i.e. the LBA of the beginning of the partition.) */
    0x00,                                                                0x00,
    0x00,                                                                0x00,

    /* 0x20     4   Large sector count. This field is set if there are more than 65535 sectors in the volume, resulting in a value which does not fit in the Number of Sectors entry at 0x13. */
#if RM_BLOCK_MEDIA_RAM_SECTOR_COUNT >= 0x10000
    (uint8_t) (RM_BLOCK_MEDIA_RAM_SECTOR_COUNT & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_SECTOR_COUNT >> 8) & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_SECTOR_COUNT >> 16) & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_SECTOR_COUNT >> 24) & UINT8_MAX),
#else
    0x00,                                                                0x00,
    0x00,                                                                0x00,
#endif

#if RM_BLOCK_MEDIA_RAM_FAT_TYPE == 12 || RM_BLOCK_MEDIA_RAM_FAT_TYPE == 16

    /* 0x024    1   Drive number. The value here should be identical to the value returned by BIOS interrupt 0x13, or passed in the DL register; i.e. 0x00 for a floppy disk and 0x80 for hard disks. This number is useless because the media is likely to be moved to another machine and inserted in a drive with a different drive number. */
    0x00,

    /* 0x025    1   Flags in Windows NT. Reserved otherwise. */
    0x00,

    /* 0x026    1   Signature (must be 0x28 or 0x29). */
    0x29,

    /* x027     4   VolumeID 'Serial' number. Used for tracking volumes between computers. You can ignore this if you want. */
    0x00,                                                                0x00,
    0x00,                                                                0x00,

    /* 0x02B    11  Volume label string. This field is padded with spaces. */
    'N',                                                                 'O',
    ' ',                                                                 'N',
    'A',                                                                 'M',
    'E',                                                                 ' ',
    ' ',                                                                 ' ',
    ' ',

    /* 0x036   8   System identifier string. This field is a string representation of the FAT file system type. It is padded with spaces. The spec says never to trust the contents of this string for any use. */
 #if RM_BLOCK_MEDIA_RAM_FAT_TYPE == 12
    'F',                                                                 'A',
    'T',                                                                 '1',
    '2',                                                                 ' ',
    ' ',                                                                 ' ',
 #elif RM_BLOCK_MEDIA_RAM_FAT_TYPE == 16
    'F',                                                                 'A',
    'T',                                                                 '1',
    '6',                                                                 ' ',
    ' ',                                                                 ' ',
 #endif

    /* 0x03E    448     Boot code. */
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
#else

    /* 0x024    4   Sectors per FAT. The size of the FAT in sectors. */
    (uint8_t) (RM_BLOCK_MEDIA_RAM_SECTORS_PER_FAT & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_SECTORS_PER_FAT >> 8) & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_SECTORS_PER_FAT >> 16) & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_SECTORS_PER_FAT >> 24) & UINT8_MAX),

    /* 0x028    2   Flags. */
    0x0,                                                                 0x0,

    /* 0x02A    2   FAT version number. The high byte is the major version and the low byte is the minor version. FAT drivers should respect this field. */
    0x0,                                                                 0x0,

    /* 0x02C    4   The cluster number of the root directory. Often this field is set to 2. */
    0x2,                                                                 0x0,
    0x0,                                                                 0x0,

    /* 0x030    2   The sector number of the FSInfo structure. */
    0x0,                                                                 0x0,

    /* 0x032    2   The sector number of the backup boot sector. */
    0x0,                                                                 0x0,

    /* 0x034    12  Reserved. When the volume is formated these bytes should be zero. */
    0x0,                                                                 0x0,
    0x0,                                                                 0x0,
    0x0,                                                                 0x0,
    0x0,                                                                 0x0,
    0x0,                                                                 0x0,
    0x0,                                                                 0x0,

    /* 0x040    1   Drive number. The values here are identical to the values returned by the BIOS interrupt 0x13. 0x00 for a floppy disk and 0x80 for hard disks. */
    0x0,

    /* 0x041    1   Flags in Windows NT. Reserved otherwise. */
    0x0,

    /* 0x042    1   Signature (must be 0x28 or 0x29). */
    0x29,

    /* 0x043    4   Volume ID 'Serial' number. Used for tracking volumes between computers. You can ignore this if you want. */
    0x0,                                                                 0x0,
    0x0,                                                                 0x0,

    /* 0x047    11  Volume label string. This field is padded with spaces. */
    'N',                                                                 'O',
    ' ',                                                                 'N',
    'A',                                                                 'M',
    'E',                                                                 ' ',
    ' ',                                                                 ' ',
    ' ',

    /* 0x052    8   System identifier string. Always "FAT32   ". The spec says never to trust the contents of this string for any use. */
    'F',                                                                 'A',
    'T',                                                                 '3',
    '2',                                                                 ' ',
    ' ',                                                                 ' ',
#endif

    /* 0x05A    420     Boot code. */
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,
    0x00,                                                                0x00,

    /* 0x1FE:signature */
    (uint8_t) (RM_BLOCK_MEDIA_RAM_SIGNATURE & UINT8_MAX),
    ((uint8_t) (RM_BLOCK_MEDIA_RAM_SIGNATURE >> 8) & UINT8_MAX),
};

/* RM_BLOCK_MEDIA_RAM_SECTOR_SIZE = 512 */
static const uint8_t g_block_media_ram_tablefat[RM_BLOCK_MEDIA_RAM_SECTOR_SIZE] =
{
#if RM_BLOCK_MEDIA_RAM_FAT_TYPE == 12

    /* Reserve the first two FAT-12 entries. */
    RM_BLOCK_MEDIA_RAM_MEDIATYPE, UINT8_MAX,                    UINT8_MAX,
#endif

#if RM_BLOCK_MEDIA_RAM_FAT_TYPE == 16

    /* Reserve the first two FAT-16 entries. */
    RM_BLOCK_MEDIA_RAM_MEDIATYPE, UINT8_MAX,                    UINT8_MAX,                   UINT8_MAX,
#endif

#if RM_BLOCK_MEDIA_RAM_FAT_TYPE == 32

    /* Reserve the first two FAT-32 entries.  */
    RM_BLOCK_MEDIA_RAM_MEDIATYPE, UINT8_MAX,                    UINT8_MAX,                   0x0F,
    UINT8_MAX,                    UINT8_MAX,                    UINT8_MAX,                   0x0F,

    /* Preallocate the first cluster for the root directory. */
    UINT8_MAX,                    UINT8_MAX,                    UINT8_MAX,                   0x0F,
#endif
};

static uint8_t BSP_PLACE_IN_SECTION(RM_BLOCK_MEDIA_RAM_CFG_SECTION) g_block_media_ram_area[
    RM_BLOCK_MEDIA_RAM_CFG_MEDIA_SIZE];

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/
const rm_block_media_api_t g_rm_block_media_on_ram_media =
{
    .open      = RM_BLOCK_MEDIA_RAM_Open,
    .mediaInit = RM_BLOCK_MEDIA_RAM_MediaInit,
    .read      = RM_BLOCK_MEDIA_RAM_Read,
    .write     = RM_BLOCK_MEDIA_RAM_Write,
    .erase     = RM_BLOCK_MEDIA_RAM_Erase,
    .infoGet   = RM_BLOCK_MEDIA_RAM_InfoGet,
    .statusGet = RM_BLOCK_MEDIA_RAM_StatusGet,
    .close     = RM_BLOCK_MEDIA_RAM_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_BLOCK_MEDIA_RAM
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the module.
 *
 * Implements @ref rm_block_media_api_t::open().
 *
 * @retval     FSP_SUCCESS                     Module is available and is now open.
 * @retval     FSP_ERR_ASSERTION               An input parameter is invalid.
 * @retval     FSP_ERR_ALREADY_OPEN            Module has already been opened with this instance of the control
 *                                             structure.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_RAM_Open (rm_block_media_ctrl_t * const p_ctrl, rm_block_media_cfg_t const * const p_cfg)
{
    rm_block_media_ram_instance_ctrl_t * p_instance_ctrl = (rm_block_media_ram_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);

    FSP_ERROR_RETURN(0UL == p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif                                 /* RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE */

    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;
    p_instance_ctrl->initialized       = false;
    p_instance_ctrl->write_protected   = false;

    p_instance_ctrl->open = RM_BLOCK_MEDIA_RAM_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initializes the RAM media area.
 *
 * Implements @ref rm_block_media_api_t::mediaInit().
 *
 * @retval     FSP_SUCCESS               Module is initialized and ready to access the memory device.
 * @retval     FSP_ERR_ASSERTION         An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN          Module is not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_RAM_MediaInit (rm_block_media_ctrl_t * const p_ctrl)
{
    uint32_t adr;
    uint32_t start_address;
    rm_block_media_callback_args_t       block_media_ram_args;
    rm_block_media_ram_instance_ctrl_t * p_instance_ctrl = (rm_block_media_ram_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_RAM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif                                 /* RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE */

    start_address = (uint32_t) &g_block_media_ram_area[0];

    /* Clear the media area */
    memset((void *) start_address, 0, RM_BLOCK_MEDIA_RAM_CFG_MEDIA_SIZE);

    adr = start_address;

    /* Copy the boot sector. */
    memcpy((void *) adr, (void *) &g_block_media_ram_boot_sector, RM_BLOCK_MEDIA_RAM_SECTOR_SIZE);
    adr += (RM_BLOCK_MEDIA_RAM_SECTOR_SIZE);

    /* Leave one sector blank after the boot sector. */
    adr += (RM_BLOCK_MEDIA_RAM_SECTOR_SIZE);

    /* Copy the fat table to the first fat copy. */
    memcpy((void *) adr, (void *) &g_block_media_ram_tablefat, sizeof(g_block_media_ram_tablefat));
    adr += (RM_BLOCK_MEDIA_RAM_SECTOR_SIZE * RM_BLOCK_MEDIA_RAM_SECTORS_PER_FAT);

    /* Copy the fat table to the second fat copy. */
    memcpy((void *) adr, (void *) &g_block_media_ram_tablefat, sizeof(g_block_media_ram_tablefat));

    if (NULL != p_instance_ctrl->p_callback)
    {
        block_media_ram_args.event     = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
        block_media_ram_args.p_context = p_instance_ctrl->p_context;
        p_instance_ctrl->p_callback(&block_media_ram_args);
    }

    p_instance_ctrl->initialized = true;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads data from RAM media.
 *
 * Implements @ref rm_block_media_api_t::read().
 *
 * This function blocks until the data is read into the destination buffer.
 *
 * @retval     FSP_SUCCESS                  Data read successfully.
 * @retval     FSP_ERR_ASSERTION            An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN             Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED      Module has not been initialized.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_RAM_Read (rm_block_media_ctrl_t * const p_ctrl,
                                   uint8_t * const               p_dest_address,
                                   uint32_t const                block_address,
                                   uint32_t const                num_blocks)
{
    uint32_t start_address;
    rm_block_media_callback_args_t       block_media_ram_args;
    rm_block_media_ram_instance_ctrl_t * p_instance_ctrl = (rm_block_media_ram_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_dest_address);
    FSP_ASSERT(num_blocks);
#endif                                 /* RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE */

    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_RAM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(true == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);

    start_address = (uint32_t) &g_block_media_ram_area[0];

    /* Copy 1 block from specified ram disk block address to read_buffer. */
    memcpy(p_dest_address, (void *) (start_address + (block_address * RM_BLOCK_MEDIA_RAM_SECTOR_SIZE)),
           (RM_BLOCK_MEDIA_RAM_SECTOR_SIZE * num_blocks));

    if (NULL != p_instance_ctrl->p_callback)
    {
        block_media_ram_args.event     = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
        block_media_ram_args.p_context = p_instance_ctrl->p_context;
        p_instance_ctrl->p_callback(&block_media_ram_args);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes data to RAM media.
 *
 * Implements @ref rm_block_media_api_t::write().
 *
 * This function blocks until the write operation completes.
 *
 * @retval     FSP_SUCCESS                   Write finished successfully.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_RAM_Write (rm_block_media_ctrl_t * const p_ctrl,
                                    uint8_t const * const         p_src_address,
                                    uint32_t const                block_address,
                                    uint32_t const                num_blocks)
{
    uint32_t start_address;
    rm_block_media_callback_args_t       block_media_ram_args;
    rm_block_media_ram_instance_ctrl_t * p_instance_ctrl = (rm_block_media_ram_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_src_address);
    FSP_ASSERT(num_blocks);
#endif                                 /* RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE */

    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_RAM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(true == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);

    start_address = (uint32_t) &g_block_media_ram_area[0];

    /* Copy 1 block from write_buffer to appropriate block address in ram disk. */
    memcpy((void *) (start_address + (block_address * RM_BLOCK_MEDIA_RAM_SECTOR_SIZE)), p_src_address,
           (RM_BLOCK_MEDIA_RAM_SECTOR_SIZE * num_blocks));

    if (NULL != p_instance_ctrl->p_callback)
    {
        block_media_ram_args.event     = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
        block_media_ram_args.p_context = p_instance_ctrl->p_context;
        p_instance_ctrl->p_callback(&block_media_ram_args);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Erases sectors of RAM media.
 *
 * Implements @ref rm_block_media_api_t::erase().
 *
 * This function blocks until erase is complete.
 *
 * @retval     FSP_SUCCESS                   Erase operation requested.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_RAM_Erase (rm_block_media_ctrl_t * const p_ctrl,
                                    uint32_t const                block_address,
                                    uint32_t const                num_blocks)
{
    uint32_t start_address;

    rm_block_media_callback_args_t       block_media_ram_args;
    rm_block_media_ram_instance_ctrl_t * p_instance_ctrl = (rm_block_media_ram_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(num_blocks);
#endif                                 /* RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE */

    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_RAM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(true == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);

    start_address = (uint32_t) &g_block_media_ram_area[0];

    memset((void *) (start_address + (block_address * RM_BLOCK_MEDIA_RAM_SECTOR_SIZE)), 0,
           (RM_BLOCK_MEDIA_RAM_SECTOR_SIZE * num_blocks));

    if (NULL != p_instance_ctrl->p_callback)
    {
        block_media_ram_args.event     = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
        block_media_ram_args.p_context = p_instance_ctrl->p_context;
        p_instance_ctrl->p_callback(&block_media_ram_args);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides driver status.
 *
 * Implements @ref rm_block_media_api_t::statusGet().
 *
 * @retval     FSP_SUCCESS                   Status stored in p_status.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_RAM_StatusGet (rm_block_media_ctrl_t * const   p_api_ctrl,
                                        rm_block_media_status_t * const p_status)
{
    rm_block_media_ram_instance_ctrl_t * p_instance_ctrl = (rm_block_media_ram_instance_ctrl_t *) p_api_ctrl;

#if RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl);
    FSP_ASSERT(p_status);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_RAM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif                                 /* RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE */

    p_status->media_inserted = true;
    p_status->initialized    = p_instance_ctrl->initialized;
    p_status->busy           = false;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Retrieves module information.
 *
 * Implements @ref rm_block_media_api_t::infoGet().
 *
 * @retval     FSP_SUCCESS                   Erase operation requested.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_RAM_InfoGet (rm_block_media_ctrl_t * const p_ctrl, rm_block_media_info_t * const p_info)
{
    rm_block_media_ram_instance_ctrl_t * p_instance_ctrl = (rm_block_media_ram_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_info);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_RAM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else                                  /* RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE */
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif  /* RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE */

    p_info->sector_size_bytes = RM_BLOCK_MEDIA_RAM_SECTOR_SIZE;
    p_info->num_sectors       = (RM_BLOCK_MEDIA_RAM_CFG_MEDIA_SIZE / RM_BLOCK_MEDIA_RAM_SECTOR_SIZE);
    p_info->reentrant         = false;
    p_info->write_protected   = false;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes the module.
 *
 * Implements @ref rm_block_media_api_t::close().
 *
 * @retval     FSP_SUCCESS                   Successful close.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_RAM_Close (rm_block_media_ctrl_t * const p_ctrl)
{
    rm_block_media_ram_instance_ctrl_t * p_instance_ctrl = (rm_block_media_ram_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_RAM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif                                 /* RM_BLOCK_MEDIA_RAM_CFG_PARAM_CHECKING_ENABLE */

    p_instance_ctrl->initialized = false;
    p_instance_ctrl->open        = 0UL;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_BLOCK_MEDIA_RAM)
 **********************************************************************************************************************/
