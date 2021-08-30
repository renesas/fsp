/**
 * This file is a copy of the aes.h file from mbedCrypto
 *  aes_alt.h
 *
 *  This file contains AES definitions and functions for the alternate implementation.
 *
 */

#ifndef MBEDTLS_AES_ALT_H
#define MBEDTLS_AES_ALT_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(MBEDTLS_AES_ALT) || defined(MBEDTLS_CTR_DRBG_C_ALT)

typedef enum e_sce_mbedtls_cipher_operation_state
{
    SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT = 0,
    SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE
} sce_mbedtls_cipher_operation_state_t ;

    /**
 * \brief The AES context-type definition.
 */
    typedef struct mbedtls_aes_context
    {
        int nr;           /*!< The number of rounds. */
        uint32_t *rk;     /*!< AES round keys. */
        uint32_t buf[68]; /*!< Unaligned data buffer. This buffer can
                                        *         hold 32 extra Bytes, which can be used for
                                        *         one of the following purposes:
                                        *         <ul><li>Alignment if VIA padlock is
                                        *                 used.</li>
                                        *         <li>Simplifying key expansion in the 256-bit
                                        *             case by generating an extra round key.
                                        *             </li></ul> */
        void *vendor_ctx; /*!< Vendor defined context. */
        sce_mbedtls_cipher_operation_state_t  state;
    } mbedtls_aes_context;
#endif
#if defined(MBEDTLS_AES_ALT)
#if defined(MBEDTLS_CIPHER_MODE_XTS)

    /**
 * \brief The AES XTS context-type definition.
 */
    typedef struct mbedtls_aes_xts_context
    {
        mbedtls_aes_context crypt; /*!< The AES context to use for AES block
                                        *   encryption or decryption. */
        mbedtls_aes_context tweak; /*!< The AES context used for tweak
                                        *   computation. */
    } mbedtls_aes_xts_context;
#endif /* MBEDTLS_CIPHER_MODE_XTS */

    int aes_setkey_generic(mbedtls_aes_context *ctx, const unsigned char *key, unsigned int keybits);
    int mbedtls_internal_aes_encrypt_cbc(mbedtls_aes_context *ctx, unsigned int length, unsigned char *iv, const unsigned char *input, unsigned char *output);
    int mbedtls_internal_aes_decrypt_cbc(mbedtls_aes_context *ctx, unsigned int length, unsigned char *iv, const unsigned char *input, unsigned char *output);
    int mbedtls_internal_aes_encrypt_decrypt_ctr (mbedtls_aes_context *ctx, unsigned int length, unsigned char *iv, const unsigned char *input, unsigned char *output);


#endif /* MBEDTLS_AES_ALT */

#ifdef __cplusplus
}
#endif

#endif /* aes_alt.h */
