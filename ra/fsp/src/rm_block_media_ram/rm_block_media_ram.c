/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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
#define VALUE_65536                (65536)
#define VALUE_4096                 (4096)
#define VALUE_512                  (512)
#define VALUE_341                  (341)
#define VALUE_256                  (256)
#define VALUE_128                  (128)
#define VALUE_16                   (16UL)
#define VALUE_EBH                  (0xEB)
#define VALUE_3CH                  (0x3C)
#define VALUE_90H                  (0x90)
#define VALUE_FFH                  (0xFF)
#define VALUE_20H                  (0x20)

#define STRG_SECTSIZE              (VALUE_512)
#define STRG_TOTALSECT             (RM_BLOCK_MEIDA_RAM_CFG_MEDIA_SIZE / STRG_SECTSIZE)

#define RAMDISK_MEDIATYPE          (0xF8U)
#define RAMDISK_SIGNATURE          (0xAA55U)

#define RAMDISK_CLSTSIZE           (0x01U)
#define RAMDISK_FATNUM             (0x02U)

/* "SRAM" in ASCII, used to identify general RM_BLOCK_MEDIA_RAM control block */
#define RM_BLOCK_MEDIA_RAM_OPEN    (0x5352414D)

/*
 * If the number of data areas of clusters is smaller
 * than that of value 4085(4096-11), it is FAT12.
 * If the number of data areas of clusters is smaller
 * than that of value 65525(65536-11), it is FAT16.
 * Otherwise it is FAT32.
 */

#if STRG_TOTALSECT < VALUE_4096
 #define RAMDISK_FATLENGTH         (0x155UL) /* FAT12 */
#else                                        /* STRG_TOTALSECT < 4096 */
 #if STRG_TOTALSECT < VALUE_65536
  #define RAMDISK_FATLENGTH        (0x100UL) /* FAT16 */
 #else                                       /* STRG_TOTALSECT < 65536 */
  #define RAMDISK_FATLENGTH        (0x80UL)  /* FAT32 */
 #endif                                      /* STRG_TOTALSECT < 65536 */
#endif  /* STRG_TOTALSECT < 4096 */

#define RAMDISK_FATSIZE            (((STRG_TOTALSECT - 8) / RAMDISK_FATLENGTH) + 1)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* STRG_SECTSIZE = 512(Define for r_media_driver_api_config.h) */
static const uint8_t g_block_media_ram_boot_sector[STRG_SECTSIZE] =
{
    /* Master boot record (FAT16) */
    /* 0x00:JMP code (PBR) */
    VALUE_EBH,                                      VALUE_3CH,                                             VALUE_90H,

    /* 0x03:OEM name */
    'M',                                            'S',                                                   'D',
    'O',
    'S',                                            '5',                                                   '.',
    '0',

    /* 0x0B:Sector size */
    (uint8_t) (STRG_SECTSIZE & VALUE_FFH),          ((uint8_t) (STRG_SECTSIZE >> 8) & VALUE_FFH),

    /* 0x0D:Cluster size */
    RAMDISK_CLSTSIZE,

    /* 0x0E:reserved (FAT entry) */
    0x02,                                           0x00,

    /* 0x10:FAT number */
    RAMDISK_FATNUM,

    /* 0x11:ROOT entry address */
    0x00,                                           0x02,

    /* 0x13:Total sector(16bit) */
#if STRG_TOTALSECT < VALUE_65536
    (uint8_t) (STRG_TOTALSECT & VALUE_FFH),         ((uint8_t) (STRG_TOTALSECT >> 8) & VALUE_FFH),
#else
    0x00,                                           0x00,
#endif

    /* 0x15:Media type */
    RAMDISK_MEDIATYPE,

    /* 0x16:FAT size */
    (uint8_t) (RAMDISK_FATSIZE & VALUE_FFH),        ((uint8_t) (RAMDISK_FATSIZE >> 8) & VALUE_FFH),

    /* 0x18:Track sector */
    0x00,                                           0x00,

    /* 0x1A:Head number */
    0x00,                                           0x00,

    /* 0x1C:Offset sector */
    0x00,                                           0x00,                                                  0x00,
    0x00,

    /* 0x20:Total sector(32bit) */
#if STRG_TOTALSECT < VALUE_65536
    0x00,                                           0x00,                                                  0x00,
    0x00,
#else
    (uint8_t) (STRG_TOTALSECT & VALUE_FFH),
    ((uint8_t) (STRG_TOTALSECT >> 8) & VALUE_FFH),
    ((uint8_t) (STRG_TOTALSECT >> 16) & VALUE_FFH),
    ((uint8_t) (STRG_TOTALSECT >> 24) & VALUE_FFH),
#endif

    /* 0x24:Drive number */
    0x00,

    /* 0x25:reserved */
    0x00,

    /* 0x26:Boot signature */
    0x00,

    /* 0x27:Volume serial number */
    0x00,                                           0x00,                                                  0x00,
    0x00,

    /* 0x2B:Volume label */
    'N',                                            'O',                                                   ' ',
    'N',
    'A',                                            'M',                                                   'E',
    ' ',                                            ' ',                                                   ' ',
    ' ',

    /* 0x36:File system type */
#if RAMDISK_FATLENGTH == VALUE_341
    'F',                                            'A',                                                   'T',
    '1',
    '2',                                            ' ',                                                   ' ',
    ' ',
#endif                                 /* RAMDISK_FATLENGTH == 341 */

#if RAMDISK_FATLENGTH == VALUE_256
    'F',                                            'A',                                                   'T',
    '1',
    '6',                                            ' ',                                                   ' ',
    ' ',
#endif                                 /* RAMDISK_FATLENGTH == 256 */

#if RAMDISK_FATLENGTH == VALUE_128
    'F',                                            'A',                                                   'T',
    '3',
    '2',                                            ' ',                                                   ' ',
    ' ',
#endif                                 /* RAMDISK_FATLENGTH == 128 */

    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,
    0x00,                                           0x00,                                                  0x00,

    /* 0x1FEB:signature */
    (uint8_t) (RAMDISK_SIGNATURE & VALUE_FFH),      ((uint8_t) (RAMDISK_SIGNATURE >> 8) & VALUE_FFH),
};

/* STRG_SECTSIZE = 512(Define for r_media_driver_api_config.h) */
static const uint8_t g_block_media_ram_table1[STRG_SECTSIZE] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/* STRG_SECTSIZE = 512(Define for r_media_driver_api_config.h) */
static const uint8_t g_block_media_ram_tablefat1[STRG_SECTSIZE * RAMDISK_FATSIZE] =
{
#if RAMDISK_FATLENGTH == VALUE_341     /* FAT12 */
    RAMDISK_MEDIATYPE, VALUE_FFH,         VALUE_FFH,         0x00,      0x00,      0x00,
    0x00,
    0x00,                              /* FAT-ID   */
#endif                                 /* RAMDISK_FATLENGTH == 341 */

#if RAMDISK_FATLENGTH == VALUE_256     /* FAT16 */
    RAMDISK_MEDIATYPE, VALUE_FFH,         VALUE_FFH,         VALUE_FFH, 0x00,      0x00,
    0x00,
    0x00,                              /* FAT-ID   */
#endif                                 /* RAMDISK_FATLENGTH == 256 */

#if RAMDISK_FATLENGTH == VALUE_128     /* FAT32 */
    RAMDISK_MEDIATYPE, VALUE_FFH,         VALUE_FFH,         VALUE_FFH, VALUE_FFH, VALUE_FFH,
    VALUE_FFH,
    VALUE_FFH,                         /* FAT-ID   */
#endif                                 /* RAMDISK_FATLENGTH == 128 */

    0x00,              0x00,              0x00,              0x00,      0x00,      0x00,
    0x00,
    0x00,
};

/* STRG_SECTSIZE = 512(Define for r_media_driver_api_config.h) */
static const uint8_t g_block_media_ram_tablefat2[STRG_SECTSIZE * RAMDISK_FATSIZE] =
{
#if RAMDISK_FATLENGTH == VALUE_341     /* FAT12 */
    RAMDISK_MEDIATYPE, VALUE_FFH,         VALUE_FFH,         0x00,      0x00,      0x00,
    0x00,
    0x00,                              /* FAT-ID   */
#endif                                 /* RAMDISK_FATLENGTH == 341 */

#if RAMDISK_FATLENGTH == VALUE_256     /* FAT16 */
    RAMDISK_MEDIATYPE, VALUE_FFH,         VALUE_FFH,         VALUE_FFH, 0x00,      0x00,
    0x00,
    0x00,                              /* FAT-ID   */
#endif                                 /* RAMDISK_FATLENGTH == 256 */

#if RAMDISK_FATLENGTH == VALUE_128     /* FAT32 */
    RAMDISK_MEDIATYPE, VALUE_FFH,         VALUE_FFH,         VALUE_FFH, VALUE_FFH, VALUE_FFH,
    VALUE_FFH,
    VALUE_FFH,                         /* FAT-ID   */
#endif                                 /* RAMDISK_FATLENGTH == 128 */

    0x00,              0x00,              0x00,              0x00,      0x00,      0x00,
    0x00,
    0x00,
};

/* Size:8192 STRG_SECTSIZE = 512(Define for r_media_driver_api_config.h) */
static const uint8_t g_block_media_ram_rootdir[STRG_SECTSIZE * 16UL] =
{
    'S',       'A',       'M',       'P',       'L',       'E',  ' ',  ' ',
    VALUE_20H, VALUE_20H, VALUE_20H, 0x08,      0x00,      0x00, 0x00, 0x00,
    0x00,      0x00,      0x00,      0x00,      0x00,      0x00, 0x00, 0x00,
    0x00,      0x00,      0x00,      0x00,      0x00,      0x00, 0x00, 0x00,
};

static uint8_t g_block_media_ram_area[RM_BLOCK_MEIDA_RAM_CFG_MEDIA_SIZE];

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

    adr = start_address;
    memcpy((void *) adr, (void *) &g_block_media_ram_boot_sector, STRG_SECTSIZE);

    adr += (STRG_SECTSIZE);
    memcpy((void *) adr, (void *) &g_block_media_ram_table1, STRG_SECTSIZE);

    adr += (STRG_SECTSIZE);
    memcpy((void *) adr, (void *) &g_block_media_ram_tablefat1, (STRG_SECTSIZE * RAMDISK_FATSIZE));

    adr += (STRG_SECTSIZE * RAMDISK_FATSIZE);
    memcpy((void *) adr, (void *) &g_block_media_ram_tablefat2, (STRG_SECTSIZE * RAMDISK_FATSIZE));

    adr += (STRG_SECTSIZE * RAMDISK_FATSIZE);
    memcpy((void *) adr, (void *) &g_block_media_ram_rootdir, (STRG_SECTSIZE * VALUE_16));

    adr += (STRG_SECTSIZE * VALUE_16);                                                    /* rootdir are size */

    memset((void *) adr, 0, (RM_BLOCK_MEIDA_RAM_CFG_MEDIA_SIZE - (adr - start_address))); /* user media area zero clear */

    if (NULL != p_instance_ctrl->p_callback)
    {
        block_media_ram_args.event = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
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
    memcpy(p_dest_address, (void *) (start_address + (block_address * STRG_SECTSIZE)), (STRG_SECTSIZE * num_blocks));

    if (NULL != p_instance_ctrl->p_callback)
    {
        block_media_ram_args.event = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
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
    memcpy((void *) (start_address + (block_address * STRG_SECTSIZE)), p_src_address, (STRG_SECTSIZE * num_blocks));

    if (NULL != p_instance_ctrl->p_callback)
    {
        block_media_ram_args.event = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
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

    memset((void *) (start_address + (block_address * STRG_SECTSIZE)), 0, (STRG_SECTSIZE * num_blocks));

    if (NULL != p_instance_ctrl->p_callback)
    {
        block_media_ram_args.event = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
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

    p_info->sector_size_bytes = STRG_SECTSIZE;
    p_info->num_sectors       = (RM_BLOCK_MEIDA_RAM_CFG_MEDIA_SIZE / STRG_SECTSIZE);
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
