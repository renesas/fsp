/**
 * This file is a copy of the chachapoly.h file from mbedCrypto
 *  chachapoly_alt.h
 *
 *  This file contains Chacha20 definitions and functions for the alternate implementation.
 *
 */

#ifndef MBEDTLS_CHACHAPOLY_ALT_H
 #define MBEDTLS_CHACHAPOLY_ALT_H
 #include "mbedtls/private_access.h"
 #include "mbedtls/build_info.h"
 #include "hw_sce_ra_private.h"

 #include <stdint.h>
 #include <stddef.h>

 #ifdef __cplusplus
extern "C" {
 #endif

/* for shared error codes */
#include "mbedtls/poly1305.h"
#include "mbedtls/chacha20.h"

#define CHACHAPOLY_STATE_INIT       (0)
#define CHACHAPOLY_STATE_AAD        (1)
#define CHACHAPOLY_STATE_CIPHERTEXT (2)   /* Encrypting or decrypting */
#define CHACHAPOLY_STATE_FINISHED   (3)

typedef struct mbedtls_chachapoly_context
{
    mbedtls_chacha20_context MBEDTLS_PRIVATE(chacha20_ctx);     /**< The ChaCha20 context. */
    mbedtls_poly1305_context MBEDTLS_PRIVATE(poly1305_ctx);     /**< The Poly1305 context. */
    uint64_t aad_len;                                           /**< The length (bytes) of the Additional Authenticated Data. */
    uint64_t ciphertext_len;                                    /**< The length (bytes) of the ciphertext. */
    int state;                                                  /**< The current state of the context. */
    mbedtls_chachapoly_mode_t mode;                             /**< Cipher mode (encrypt or decrypt). */

    /*Internal parameters*/
    uint32_t internal_key[SIZE_CHACHA20_256BIT_KEYLEN_WORDS_WRAPPED];
    uint32_t internal_state[16];
    uint8_t indata_aad[HW_SCE_CHACHAPOLY_AAD_BYTE_SIZE];
}mbedtls_chachapoly_context;

int mbedtls_internal_chachapoly_setkey(mbedtls_chachapoly_context *ctx,
                                       const unsigned char key[HW_SCE_CHACHA20_KEY_BYTE_SIZE]);
int mbedtls_internal_chachapoly_update(mbedtls_chachapoly_context * ctx,
                                       const unsigned char      * input,
                                       unsigned char            * output,
                                       size_t                     size);
int mbedtls_internal_chachapoly_finish(mbedtls_chachapoly_context * ctx,
                                       unsigned char mac[HW_SCE_CHACHAPOLY_MAC_BYTE_SIZE]);

#ifdef __cplusplus
}
#endif

#endif                                 /* MBEDTLS_CHACHAPOLY_ALT_H */
