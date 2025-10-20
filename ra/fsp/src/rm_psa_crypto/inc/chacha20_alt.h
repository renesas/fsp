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

 #include <stdint.h>
 #include <stddef.h>

 #ifdef __cplusplus
extern "C" {
 #endif

 #define CHACHA20_BLOCK_SIZE_BYTES          (4U * 16U)
 #define CHACHA20_BLOCK_SIZE_WORDS          (CHACHA20_BLOCK_SIZE_BYTES/4U)

typedef struct mbedtls_chacha20_context
{
    uint32_t state[16];
    uint8_t  keystream8[64];           /*! Leftover keystream bytes. */
    size_t   keystream_bytes_used;     /*! Number of keystream bytes already used. */
    uint32_t internal_state[2];
} mbedtls_chacha20_context;

int mbedtls_internal_chacha20_init(mbedtls_chacha20_context * ctx, size_t size);
int mbedtls_internal_chacha20_update(mbedtls_chacha20_context * ctx,
                                     const unsigned char      * input,
                                     unsigned char            * output,
                                     size_t                     size);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* MBEDTLS_CHACHA20_ALT_H */
