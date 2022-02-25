/*
 * Copyright (c) 2017-2020 Arm Limited. All rights reserved.
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

#ifndef __REGION_DEFS_H__
 #define __REGION_DEFS_H__

 #include "flash_layout.h"

 #ifdef __cplusplus
extern "C" {
 #endif

/* This size of buffer is big enough to store an attestation
 * token produced by initial attestation service
 */
 #define PSA_INITIAL_ATTEST_TOKEN_MAX_SIZE    (0x250)

/* Shared data area between bootloader and runtime firmware.
 * Shared data area is allocated at the beginning of the RAM, it is overlapping
 * with TF-M Secure code's MSP stack
 */
 #define BOOT_TFM_SHARED_DATA_BASE            MCUBOOT_SHARED_DATA_BASE

/* BOOT_TFM_SHARED_DATA_SIZE is used in the bl2 code as the total area reserved to save the
 * attestation info. The actual shared data area will be defined by BOOT_TFM_SHARED_DATA_LIMIT
 * which will contain other items as well. */
 #define BOOT_TFM_SHARED_DATA_SIZE            (MCUBOOT_SHARED_DATA_SIZE)

 #define BOOT_TFM_SHARED_SEED_BASE            (BOOT_TFM_SHARED_DATA_BASE + \
                                               BOOT_TFM_SHARED_DATA_SIZE)
 #define BOOT_TFM_SHARED_SEED_SIZE            (0x20)

 #define BOOT_TFM_SHARED_HUK_BASE             (BOOT_TFM_SHARED_SEED_BASE + \
                                               BOOT_TFM_SHARED_SEED_SIZE)
 #define BOOT_TFM_SHARED_HUK_SIZE             (0x30)

 #define BOOT_TFM_SHARED_IAK_BASE             (BOOT_TFM_SHARED_HUK_BASE + \
                                               BOOT_TFM_SHARED_HUK_SIZE)
 #define BOOT_TFM_SHARED_IAK_SIZE             (0x30)

 #define BOOT_TFM_SHARED_DATA_LIMIT           (BOOT_TFM_SHARED_DATA_BASE + \
                                               BOOT_TFM_SHARED_SEED_SIZE + \
                                               BOOT_TFM_SHARED_HUK_SIZE +  \
                                               BOOT_TFM_SHARED_IAK_SIZE +  \
                                               BOOT_TFM_SHARED_DATA_SIZE - 1)

 #define BOOT_TFM_SHARED_DATA_TOTAL_SIZE      (BOOT_TFM_SHARED_DATA_LIMIT - BOOT_TFM_SHARED_DATA_BASE + 1)

 #ifdef __cplusplus
}
 #endif

#endif                                 /* __REGION_DEFS_H__ */
