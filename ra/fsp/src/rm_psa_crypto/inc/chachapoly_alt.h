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

 #include <stdint.h>
 #include <stddef.h>

 #ifdef __cplusplus
extern "C" {
 #endif

/* for shared error codes */
#include "mbedtls/poly1305.h"
#include "mbedtls/chacha20.h"

#define SIZE_CHACHAPOLY_IN_DATA_AAD_LEN_BYTES (256U)
#define SIZE_CHACHAPOLY_IN_DATA_TAG_LEN_BYTES (16U)
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
    uint32_t internal_state[16];
    uint8_t indata_aad[SIZE_CHACHAPOLY_IN_DATA_AAD_LEN_BYTES];
}mbedtls_chachapoly_context;

int mbedtls_internal_chachapoly_update(mbedtls_chachapoly_context * ctx,
                                       const unsigned char      * input,
                                       unsigned char            * output,
                                       size_t                     size);
int mbedtls_internal_chachapoly_finish(mbedtls_chachapoly_context * ctx,
                                       unsigned char mac[16]);

#ifdef __cplusplus
}
#endif

#endif                                 /* MBEDTLS_CHACHAPOLY_ALT_H */
