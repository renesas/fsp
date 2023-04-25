/*
 * Copyright (c) 2018-2020 Arm Limited. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __FLASH_LAYOUT_H__
 #define __FLASH_LAYOUT_H__

 #include "tfm_common_config.h"
 #include "flash_otp_nv_counters_backend.h"
 #include "bsp_api.h"
 #ifdef BL2_PROJECT
  #include "sysflash/sysflash.h"
 #else
  #include RM_TFM_PORT_MCUBOOT_CFG
 #endif

 #ifdef __cplusplus
extern "C" {
 #endif

/* Sector size of the embedded flash hardware */
 #define FLASH_AREA_IMAGE_SECTOR_SIZE            (BSP_FEATURE_FLASH_HP_CF_REGION1_BLOCK_SIZE) /* 32 KB */
 #define FLASH_TOTAL_SIZE                        (BSP_ROM_SIZE_BYTES)

/* Sector size of the data flash hardware */
 #define DATA_FLASH_AREA_IMAGE_SECTOR_SIZE       (BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE)         /* 64 B */

/* Sector size of the QSPI flash hardware */
 #define QSPI_FLASH_AREA_IMAGE_SECTOR_SIZE       (0x1000)                                     /* 4 KB */
 #define QSPI_FLASH_TOTAL_SIZE                   (0x800000)                                   /* 8 MB */

/* Flash layout info for BL2 bootloader */
 #define FLASH_BASE_ADDRESS                      (0x00000000)

/* Used by the flash service to make sure that the writes are only to the update areas */
 #define RM_TFM_PORT_SECURE_UPDATE_ADDRESS       FLASH_BASE_ADDRESS + RM_MCUBOOT_PORT_CFG_SCRATCH_SIZE + \
    RM_MCUBOOT_PORT_CFG_MCUBOOT_SIZE
 #define RM_TFM_PORT_SECURE_IMAGE_SIZE           RM_MCUBOOT_PORT_CFG_S_PARTITION_SIZE

 #define RM_TFM_PORT_NONSECURE_UPDATE_ADDRESS    FLASH_BASE_ADDRESS + RM_MCUBOOT_PORT_CFG_SCRATCH_SIZE + \
    RM_MCUBOOT_PORT_CFG_MCUBOOT_SIZE +                                                                   \
    (RM_MCUBOOT_PORT_CFG_S_PARTITION_SIZE * 2) + RM_MCUBOOT_PORT_CFG_NS_PARTITION_SIZE
 #define RM_TFM_PORT_NONSECURE_IMAGE_SIZE        RM_MCUBOOT_PORT_CFG_NS_PARTITION_SIZE

 #define DATA_FLASH_BASE_ADDRESS                 (BSP_FEATURE_FLASH_DATA_FLASH_START)

/* Not used, only the Non-swapping firmware upgrade operation
 * is supported. The maximum number of status entries
 * supported by the bootloader.
 */
 #define MCUBOOT_STATUS_MAX_ENTRIES              (0)

/* Internal Trusted Storage (ITS) Service definitions (4 KB) */
 #define FLASH_ITS_AREA_OFFSET                   (CFG_DATA_FLASH_ITS_AREA_OFFSET)
 #define FLASH_ITS_AREA_SIZE                     (CFG_DATA_FLASH_ITS_AREA_SIZE)

/* NV Counters definitions */
 #define FLASH_NV_COUNTERS_AREA_OFFSET           (CFG_DATA_FLASH_NV_COUNTERS_AREA_OFFSET)
 #define FLASH_NV_COUNTERS_AREA_SIZE             (CFG_DATA_FLASH_NV_COUNTERS_AREA_SIZE)

/* Protected Storage (PS) Service definitions size is 20 KB. */
 #define QSPI_FLASH_BASE_ADDRESS                 (0x10000000)
 #define FLASH_PS_AREA_OFFSET                    (0x0)
 #define FLASH_PS_AREA_SIZE                      (5 * QSPI_FLASH_AREA_IMAGE_SECTOR_SIZE)

/* Flash device name used by BL2
 * Name is defined in flash driver file: Driver_Flash.c
 */
 #define FLASH_DEV_NAME                          Driver_CFLASH

/* Protected Storage (PS) Service definitions
 * Note: Further documentation of these definitions can be found in the
 * TF-M PS Integration Guide.
 */
 #define TFM_HAL_PS_FLASH_DRIVER                 Driver_QSPI_FLASH0

/* In this target the CMSIS driver requires only the offset from the base
 * address instead of the full memory address.
 */

/* Base address of dedicated flash area for PS */
 #define TFM_HAL_PS_FLASH_AREA_ADDR              FLASH_PS_AREA_OFFSET

/* Size of dedicated flash area for PS */
 #define TFM_HAL_PS_FLASH_AREA_SIZE              FLASH_PS_AREA_SIZE
 #define PS_SECTOR_SIZE                          QSPI_FLASH_AREA_IMAGE_SECTOR_SIZE

/* Number of PS_SECTOR_SIZE per block */
 #define TFM_HAL_PS_SECTORS_PER_BLOCK            (0x1)

/* Specifies the smallest flash programmable unit in bytes */
 #define TFM_HAL_PS_PROGRAM_UNIT                 (0x1)

/* Internal Trusted Storage (ITS) Service definitions
 * Note: Further documentation of these definitions can be found in the
 * TF-M ITS Integration Guide. The ITS should be in the internal flash, but is
 * allocated in the external flash just for development platforms that don't
 * have internal flash available.
 */
 #define ITS_FLASH_DEV_NAME                      Driver_DFLASH
 #define TFM_HAL_ITS_FLASH_DRIVER                Driver_DFLASH

/* In this target the CMSIS driver requires only the offset from the base
 * address instead of the full memory address.
 */

/* Base address of dedicated flash area for ITS */
 #define TFM_HAL_ITS_FLASH_AREA_ADDR             FLASH_ITS_AREA_OFFSET

/* Size of dedicated flash area for ITS */
 #define TFM_HAL_ITS_FLASH_AREA_SIZE             FLASH_ITS_AREA_SIZE
 #define ITS_SECTOR_SIZE                         DATA_FLASH_AREA_IMAGE_SECTOR_SIZE

/* Number of ITS_SECTOR_SIZE per block */
 #define TFM_HAL_ITS_SECTORS_PER_BLOCK           (CFG_TFM_ITS_SECTORS_PER_BLOCK)

/* Specifies the smallest flash programmable unit in bytes */
 #define TFM_HAL_ITS_PROGRAM_UNIT                (BSP_FEATURE_FLASH_HP_DF_WRITE_SIZE)

/* The maximum asset size to be stored in the ITS area */
 #define ITS_MAX_ASSET_SIZE                      (CFG_TFM_ITS_MAX_ASSET_SIZE)

/* The maximum number of assets to be stored in the ITS area */
 #define ITS_NUM_ASSETS                          (CFG_TFM_ITS_NUM_ASSETS)

/* NV Counters definitions */
 #define TFM_NV_COUNTERS_AREA_ADDR               FLASH_NV_COUNTERS_AREA_OFFSET
 #define TFM_NV_COUNTERS_AREA_SIZE               (FLASH_NV_COUNTERS_AREA_SIZE)
 #define TFM_NV_COUNTERS_SECTOR_ADDR             FLASH_NV_COUNTERS_AREA_OFFSET
 #define TFM_NV_COUNTERS_SECTOR_SIZE             FLASH_NV_COUNTERS_AREA_SIZE

/* OTP_definitions */
#define ROUNDOFF_VALUE(X,Y)                      ((Y) * (((X) + (Y - 1)) / (Y)))
#define DATA_FLASH_OTP_NV_COUNTERS_AREA_SIZE     (ROUNDOFF_VALUE((sizeof(struct flash_otp_nv_counters_region_t)),\
                                                  128U))
#define FLASH_OTP_NV_COUNTERS_AREA_OFFSET        (CFG_DATA_FLASH_OTP_NV_COUNTERS_AREA_OFFSET)
#define FLASH_OTP_NV_COUNTERS_AREA_SIZE          (DATA_FLASH_OTP_NV_COUNTERS_AREA_SIZE)
#define FLASH_OTP_NV_COUNTERS_SECTOR_SIZE        (DATA_FLASH_AREA_IMAGE_SECTOR_SIZE)

/* OTP / NV counter definitions */
#define OTP_NV_COUNTERS_WRITE_BLOCK_SIZE         (DATA_FLASH_AREA_IMAGE_SECTOR_SIZE)
#define TFM_OTP_NV_COUNTERS_AREA_SIZE            (FLASH_OTP_NV_COUNTERS_AREA_SIZE)
#define TFM_OTP_NV_COUNTERS_AREA_ADDR            FLASH_OTP_NV_COUNTERS_AREA_OFFSET
#define TFM_OTP_NV_COUNTERS_SECTOR_SIZE          FLASH_OTP_NV_COUNTERS_SECTOR_SIZE
#define TFM_OTP_NV_COUNTERS_BACKUP_AREA_ADDR     (TFM_OTP_NV_COUNTERS_AREA_ADDR + \
                                                 TFM_OTP_NV_COUNTERS_AREA_SIZE)

/* Use eFlash 0 memory to store Code data */
 #define S_ROM_ALIAS_BASE                        (0x00000000)
 #define NS_ROM_ALIAS_BASE                       (0x00000000)

 #define S_RAM_ALIAS_BASE                        (0x20000000)

 #define TOTAL_ROM_SIZE                          FLASH_TOTAL_SIZE
 #define TOTAL_RAM_SIZE                          (BSP_RAM_SIZE_BYTES)

 #ifdef __cplusplus
}
 #endif

#endif                                 /* __FLASH_LAYOUT_H__ */
