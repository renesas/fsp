/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef __BOOTUTIL_CRYPTO_SCE9_ECDSA_P256_H_
 #define __BOOTUTIL_CRYPTO_SCE9_ECDSA_P256_H_

 #include "sce9_sha256.h"
 #include "r_sce.h"
 #include "r_sce_private.h"

 #define BOOTUTIL_CRYPTO_ECDSA_P256_SIGNATURE_SIZE_BYTES         (64U)
 #define MCUBOOT_SCE9_ECC_PUBLIC_KEY_IDX_SIZE_BYTES              (21U * 4U)
 #define HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO_WORD_SIZE_TEMP    (1U)

 #define MCUBOOT_CHECK_32BIT_UNALIGNED(x)    (0 != (x & 0x03))

/** ECC P-192/224/256 public wrapped key data structure.
 * This type is create temporarily since the definition of sce_ecc_public_wrapped_key_t in r_sce_api.h has
 * a size error which makes it unusable here.
 */
typedef struct mcb_sce_ecc_public_wrapped_key
{
    uint32_t type;                                                                          ///< key type
    struct
    {
        uint32_t key_management_info[HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO_WORD_SIZE_TEMP]; ///< key management information
        uint8_t  key_q[HW_SCE_ECC_KEY_LENGTH_BYTE_SIZE];                                    ///< ECC public key Q (plaintext)
    } value;
} mcb_sce_ecc_public_wrapped_key_t;

 #ifdef __cplusplus
extern "C" {
 #endif

typedef uintptr_t bootutil_ecdsa_context;

static inline void bootutil_ecdsa_init (bootutil_ecdsa_context * ctx)
{
    (void) ctx;
}

static inline void bootutil_ecdsa_drop (bootutil_ecdsa_context * ctx)
{
    (void) ctx;
}

 #ifdef __cplusplus
}
 #endif
#endif                                 /* __BOOTUTIL_CRYPTO_SCE9_ECDSA_P256_H_ */
