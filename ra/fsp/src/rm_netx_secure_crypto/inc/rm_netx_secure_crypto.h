/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#ifndef RM_NETX_SECURE_CRYPTO_H
#define RM_NETX_SECURE_CRYPTO_H
#include "bsp_api.h"
#include "rm_netx_secure_crypto_cfg.h"
#ifndef NX_CRYPTO_STANDALONE_ENABLE
 #include "nx_api.h"
#else
 #include "nx_crypto_port.h"
#endif
#if (0U == NETX_SECURE_CRYPTO_SOFTWARE_ONLY)
 #include "hw_sce_private.h"
#endif
#include "nx_crypto.h"
#include "nx_crypto_aes.h"
#include "nx_crypto_ecdsa.h"
#include "nx_crypto_ecdh.h"
#include "nx_crypto_sha2.h"
#include "nx_crypto_rsa.h"

/*******************************************************************************************************************//**
 * @addtogroup RM_NETX_SECURE_CRYPTO
 * @{
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#if defined(__GNUC__)                  /* GCC compiler */
 #define RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(arg)    (__builtin_bswap32(arg))
#elif defined(__ICCARM__)              /* IAR compiler */
 #define RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(arg)    (__REV(arg))
#elif defined(__ARMCC_VERSION)         /* AC6 compiler */
 #define RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(arg)    ((unsigned int) (__rev(arg)))
#endif

#define RM_NETX_SECURE_CRYPTO_ECC_224_CURVE_OPERATION    (0x00000001U)
#define RM_NETX_SECURE_CRYPTO_BITS_TO_BYTES(x)      (((x) + 7U) >> 3U)
#define RM_NETX_SECURE_CRYPTO_BYTES_TO_BITS(x)      ((x) << 3U)
#define RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(x)     ((x) << 2U)
#define RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(x)     (((x) + 3U) >> 2U)

#define RM_NETX_SECURE_CRYPTO_LARGEST_FORMATTED_ECC_PUBLIC_KEY_WORDS               (32U) /* Corresponding to ECC P-384 curves on SCE7 */
#define RM_NETX_SECURE_CRYPTO_ECC_192_224_256_WRAPPED_KEY_SIZE_BYTES               (13U * 4U)
#define RM_NETX_SECURE_CRYPTO_P384_CURVE_SIZE_BYTES                                (384U >> 3U)
#define RM_NETX_SECURE_CRYPTO_P256_CURVE_SIZE_BYTES                                (256U >> 3U)
#define RM_NETX_SECURE_CRYPTO_P224_CURVE_SIZE_BYTES                                (224U >> 3U)
#define RM_NETX_SECURE_CRYPTO_LARGEST_SUPPORTED_SIGNATURE_SIZE_WORDS               ( \
        RM_NETX_SECURE_CRYPTO_P384_CURVE_SIZE_BYTES >> 1U)
#define RM_NETX_SECURE_CRYPTO_LARGEST_SUPPORTED_PUBLIC_KEY_SIZE_WORDS              ( \
        RM_NETX_SECURE_CRYPTO_LARGEST_SUPPORTED_SIGNATURE_SIZE_WORDS)
#define RM_NETX_SECURE_CRYPTO_LARGEST_SUPPORTED_SIGNATURE_COORDINATE_SIZE_WORDS    ( \
        RM_NETX_SECURE_CRYPTO_LARGEST_SUPPORTED_SIGNATURE_SIZE_WORDS / 2)

#if (0U == NETX_SECURE_CRYPTO_SOFTWARE_ONLY)

/* Standard ECC public key is 1 + 2 x 'curve size'
 * SCE9 or SCE7 based public key is 2 x 'curve size' + (20 or 32) bytes, requireing an addjustment of  -1 + (20 or 32)
 */
 #define RM_NETX_SECURE_CRYPTO_FORMATTED_ECC_PUBLIC_KEY_ADJUST                     (((                                          \
                                                                                         HW_SCE_PRIVATE_KEY_WRAPPING_WORD_SIZE) \
                                                                                     * 4) - 1U)

/* SCE based wrapped keys are at most 20/32 bytes larger than corresponding plain private keys */
 #define RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(x)    ((x) + ((HW_SCE_PRIVATE_KEY_WRAPPING_WORD_SIZE) * 4))

#endif

#define RM_NETX_SECURE_CRYPTO_NONALIGNMENT_CHECK(x)         ((((uint32_t) (x) & 3U) != 0) ? true : false)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* SCE initialization */
uint32_t rm_netx_secure_crypto_sce_init(void);

/* HASH */
/* NX Crypto acceleration function declarations for HASH */
UINT sce_nx_crypto_sha256_initialize(NX_CRYPTO_SHA256 * context, UINT algorithm);
UINT sce_nx_crypto_sha256_update(NX_CRYPTO_SHA256 * context, UCHAR * input_ptr, UINT input_length);
UINT sce_nx_crypto_sha256_digest_calculate(NX_CRYPTO_SHA256 * context, UCHAR * digest, UINT algorithm);

/* AES */
#define SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS    (9)
#define SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS    (13)
#define SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS    (14) /* Added 1 extra word to differentiate between 192 and 256 wrapped keys */
/* NX Crypto acceleration function declarations for AES-ECB */
UINT sce_nx_crypto_aes_key_set(NX_CRYPTO_AES * aes_ptr, UCHAR * key, UINT key_size);
UINT sce_nx_crypto_aes_decrypt(NX_CRYPTO_AES * aes_ptr, UCHAR * input, UCHAR * output, UINT length);
UINT sce_nx_crypto_aes_encrypt(NX_CRYPTO_AES * aes_ptr, UCHAR * input, UCHAR * output, UINT length);

UINT sce_nx_crypto_cbc_decrypt(VOID          * crypto_metadata,
                               NX_CRYPTO_CBC * cbc_metadata,
                               UCHAR         * input,
                               UCHAR         * output,
                               UINT            length);
UINT sce_nx_crypto_cbc_encrypt(VOID          * crypto_metadata,
                               NX_CRYPTO_CBC * cbc_metadata,
                               UCHAR         * input,
                               UCHAR         * output,
                               UINT            length);
UINT sce_nx_crypto_ctr_encrypt(VOID          * crypto_metadata,
                               NX_CRYPTO_CTR * ctr_metadata,
                               UCHAR         * input,
                               UCHAR         * output,
                               UINT            length);
UINT sce_nx_crypto_gcm_ghash_update(UCHAR * hkey, UCHAR * input, UINT input_length, UCHAR * output);

UINT sce_nx_crypto_gcm_encrypt_init(NX_CRYPTO_AES * aes_ctx,
                                    UCHAR         * hashed_ivec,
                                    VOID          * additional_data,
                                    UINT            additional_len);

/*
 * _nx_crypto_gcm_decrypt_init does not exist in NetX Crypto code and is mapped to _nx_crypto_gcm_encrypt_init.
 * SCE9 APIs are different for Encryption and Decryption.
 * sce_nx_crypto_gcm_decrypt_init is created in the nx_crypto_gcm_alt.c file to
 * mimic an equivalent _nx_crypto_gcm_decrypt_init.
 * This is directly called by the _nx_crypto_method_aes_gcm_operation function when HW AES is enabled.
 */
UINT sce_nx_crypto_gcm_decrypt_init(VOID * crypto_metadata,
                                    NX_CRYPTO_GCM * gcm_metadata,
                                    UINT (* crypto_function)(VOID *, UCHAR *, UCHAR *, UINT),
                                    VOID * additional_data,
                                    UINT additional_len,
                                    UCHAR * iv,
                                    UINT block_size);
UINT sce_nx_crypto_gcm_encrypt_update(NX_CRYPTO_AES * aes_ctx, UCHAR * input, UCHAR * output, UINT length);
UINT sce_nx_crypto_gcm_decrypt_update(NX_CRYPTO_AES * aes_ctx, UCHAR * input, UCHAR * output, UINT length);
UINT sce_nx_crypto_gcm_encrypt_calculate(NX_CRYPTO_AES * aes_ctx, UCHAR * bit_size, UINT icv_len, UCHAR * tag);
UINT sce_nx_crypto_gcm_decrypt_calculate(NX_CRYPTO_AES * aes_ctx, UCHAR * bit_size, UINT icv_len, UCHAR * tag);

/* TRNG */
int  rand(void);
void srand(unsigned int seed);

/* ECC */
VOID sce_nx_crypto_ec_fp_affine_add_subtract(NX_CRYPTO_EC       * curve,
                                             NX_CRYPTO_EC_POINT * left,
                                             NX_CRYPTO_EC_POINT * right,
                                             HN_UBASE           * scratch);
VOID sce_nx_crypto_ec_fp_projective_multiple(NX_CRYPTO_EC          * curve,
                                             NX_CRYPTO_EC_POINT    * g,
                                             NX_CRYPTO_HUGE_NUMBER * d,
                                             NX_CRYPTO_EC_POINT    * r,
                                             HN_UBASE              * scratch);
VOID sce_nx_crypto_ec_secpr1_reduce(NX_CRYPTO_EC * curve, NX_CRYPTO_HUGE_NUMBER * value, HN_UBASE * scratch);

UINT sce_nx_crypto_ecdsa_sign(NX_CRYPTO_EC * curve,
                              UCHAR        * hash,
                              UINT           hash_length,
                              UCHAR        * private_key,
                              UINT           private_key_length,
                              UCHAR        * signature_r,
                              UINT         * r_size,
                              UCHAR        * signature_s,
                              UINT         * s_size);
UINT sce_nx_crypto_ecdsa_verify(NX_CRYPTO_EC * curve,
                                UCHAR        * hash,
                                UINT           hash_length,
                                UCHAR        * public_key,
                                UCHAR        * signature_r,
                                UINT           r_size,
                                UCHAR        * signature_s,
                                UINT           s_size);

UINT sce_nx_crypto_ecdh_key_pair_import(NX_CRYPTO_ECDH * ecdh_ptr,
                                        NX_CRYPTO_EC   * curve,
                                        UCHAR          * local_private_key_ptr,
                                        ULONG            local_private_key_len,
                                        ULONG            local_public_key_len);
UINT sce_nx_crypto_ecdh_private_key_export(NX_CRYPTO_ECDH * ecdh_ptr,
                                           UCHAR          * local_private_key_ptr,
                                           ULONG            local_private_key_len,
                                           ULONG          * actual_local_private_key_len);
UINT sce_nx_crypto_ecdh_setup(NX_CRYPTO_ECDH * ecdh_ptr,
                              UCHAR          * local_public_key_ptr,
                              ULONG          * actual_local_public_key_len,
                              NX_CRYPTO_EC   * curve);
UINT sce_nx_crypto_ecdh_compute_secret(NX_CRYPTO_ECDH * ecdh_ptr,
                                       UCHAR          * share_secret_key_ptr,
                                       ULONG          * actual_share_secret_key_len,
                                       UCHAR          * remote_public_key);
uint32_t rm_netx_secure_crypto_ecc_key_pair_generate(uint32_t   curve_id,
                                                     uint32_t   curve_size,
                                                     uint8_t  * output,
                                                     uint32_t   output_length_in_byte,
                                                     uint32_t * actual_output_length);

/* RSA */
UINT sce_nx_crypto_rsa_operation(const UCHAR * exponent,
                                 UINT          exponent_length,
                                 const UCHAR * modulus,
                                 UINT          modulus_length,
                                 const UCHAR * input,
                                 UINT          input_length,
                                 UCHAR       * output);

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
