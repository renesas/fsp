/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef SCE9_KEYS_H
#define SCE9_KEYS_H
#include "mcuboot_config/mcuboot_config.h"
#include <bootutil/sign_key.h>

#define MCUBOOT_MIN_FLASH_WRITE_SIZE    BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE

extern const struct bootutil_key bootutil_keys_wrapped[];

#define RM_MCUBOOT_PORT_BITS_TO_BYTES(bits)    (((bits) + 7) / 8)

#if defined(MCUBOOT_SIGN_EC256)

/* NUM_ECC_BYTES is the size of the P256 private key.
 * 2 x NUM_ECC_BYTES is the size of the public key and the signature. */
 #define NUM_ECC_BYTES                              (32U)

/* The size of the array designated to program the wrapped keys from RFP should
 * aligned to the flash write size. */
 #define MCUBOOT_SCE9_ALIGNED_ECC_KEY_SIZE_BYTES    (128U)

#elif defined(MCUBOOT_SIGN_RSA)
 #if MCUBOOT_SIGN_RSA_LEN == 2048
  #define MCUBOOT_SCE9_MAX_RSA_KEY_SIZE_BYTES       (sizeof(sce_rsa2048_public_wrapped_key_t))
 #elif MCUBOOT_SIGN_RSA_LEN == 3072
  #define MCUBOOT_SCE9_MAX_RSA_KEY_SIZE_BYTES       (sizeof(sce_rsa3072_public_wrapped_key_t))
 #endif

/* The size of the array designated to program the wrapped keys from RFP should
 * aligned to the flash write size. */
 #define MCUBOOT_SCE9_ALIGNED_RSA_KEY_SIZE_BYTES    (((MCUBOOT_SCE9_MAX_RSA_KEY_SIZE_BYTES + \
                                                       (MCUBOOT_MIN_FLASH_WRITE_SIZE - 1)) / \
                                                      MCUBOOT_MIN_FLASH_WRITE_SIZE) * MCUBOOT_MIN_FLASH_WRITE_SIZE)
#endif

#endif                                 /* SCE9_KEYS_H */
