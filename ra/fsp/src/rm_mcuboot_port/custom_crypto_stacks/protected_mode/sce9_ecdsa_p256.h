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

typedef uintptr_t bootutil_ecdsa_p256_context;

static inline void bootutil_ecdsa_p256_init (bootutil_ecdsa_p256_context * ctx)
{
    (void) ctx;
}

static inline void bootutil_ecdsa_p256_drop (bootutil_ecdsa_p256_context * ctx)
{
    (void) ctx;
}

 #ifdef __cplusplus
}
 #endif
#endif                                 /* __BOOTUTIL_CRYPTO_SCE9_ECDSA_P256_H_ */
