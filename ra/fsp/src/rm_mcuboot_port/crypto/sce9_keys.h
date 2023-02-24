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
