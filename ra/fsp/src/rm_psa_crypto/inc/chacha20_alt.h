/**
 * This file is a copy of the chacha20.h file from mbedCrypto
 *  chacha20_alt.h
 *
 *  This file contains Chacha20 definitions and functions for the alternate implementation.
 *
 */

#ifndef MBEDTLS_CHACHA20_ALT_H
 #define MBEDTLS_CHACHA20_ALT_H
 #include "mbedtls/private_access.h"
 #include "mbedtls/build_info.h"
 #include "hw_sce_ra_private.h"

 #include <stdint.h>
 #include <stddef.h>

 #ifdef __cplusplus
extern "C" {
 #endif

typedef struct mbedtls_chacha20_context
{
    uint32_t state[16];
    uint8_t  keystream8[64];           /*! Leftover keystream bytes. */
    size_t   keystream_bytes_used;     /*! Number of keystream bytes already used. */

    /*Internal parameters*/
    uint32_t internal_key[SIZE_CHACHA20_256BIT_KEYLEN_WORDS_WRAPPED];
    uint32_t internal_state[2];
} mbedtls_chacha20_context;

int mbedtls_internal_chacha20_setkey(mbedtls_chacha20_context *ctx,
                                     const unsigned char key[HW_SCE_CHACHA20_KEY_BYTE_SIZE]);
int mbedtls_internal_chacha20_update(mbedtls_chacha20_context * ctx,
                                     const unsigned char      * input,
                                     unsigned char            * output,
                                     size_t                     size);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* MBEDTLS_CHACHA20_ALT_H */
