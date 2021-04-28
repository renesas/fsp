/*
 *  CTR_DRBG implementation based on AES-256 (NIST SP 800-90)
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */
/*
 *  The NIST SP 800-90 DRBGs are described in the following publication.
 *
 *  http://csrc.nist.gov/publications/nistpubs/800-90/SP800-90revised_March2007.pdf
 */

#include "common.h"

#if defined(MBEDTLS_CTR_DRBG_C_ALT)

#include "ctr_drbg_alt.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"

#include <string.h>

#if defined(MBEDTLS_FS_IO)
#include <stdio.h>
#endif

#if defined(MBEDTLS_SELF_TEST)
#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_printf printf
#endif /* MBEDTLS_PLATFORM_C */
#endif /* MBEDTLS_SELF_TEST */

/* Macros from mbedtls/aes.h */
 #define MBEDTLS_AES_ENCRYPT               1       /**< AES encryption. */
 #define MBEDTLS_AES_DECRYPT               0       /**< AES decryption. */
/* Error codes in range 0x0021-0x0025 */
 #define MBEDTLS_ERR_AES_BAD_INPUT_DATA    -0x0021 /**< Invalid input data. */
/* Functions to support software AES for CTR DRBG */
static void mbedtls_aes_free(mbedtls_aes_context * ctx);
static int  mbedtls_aes_crypt_ecb(mbedtls_aes_context * ctx,
                                  int                   mode,
                                  const unsigned char   input[16],
                                  unsigned char         output[16]);
static void mbedtls_aes_init(mbedtls_aes_context * ctx);
static int  mbedtls_aes_setkey_enc(mbedtls_aes_context * ctx, const unsigned char * key, unsigned int keybits);

 #if defined(__ICCARM__) && defined(MBEDTLS_FS_IO)              /* IAR Compiler */
static int ferror(FILE * f);

int ferror (FILE * f)
{
    return EOF;
}
 #endif
/*
 * CTR_DRBG context initialization
 */
void mbedtls_ctr_drbg_init( mbedtls_ctr_drbg_context *ctx )
{
    memset( ctx, 0, sizeof( mbedtls_ctr_drbg_context ) );
    /* Indicate that the entropy nonce length is not set explicitly.
     * See mbedtls_ctr_drbg_set_nonce_len(). */
    ctx->reseed_counter = -1;

#if defined(MBEDTLS_THREADING_C)
    mbedtls_mutex_init( &ctx->mutex );
#endif
}

void mbedtls_ctr_drbg_free( mbedtls_ctr_drbg_context *ctx )
{
    if( ctx == NULL )
        return;

#if defined(MBEDTLS_THREADING_C)
    mbedtls_mutex_free( &ctx->mutex );
#endif
    mbedtls_aes_free( &ctx->aes_ctx );
    mbedtls_platform_zeroize( ctx, sizeof( mbedtls_ctr_drbg_context ) );
}

void mbedtls_ctr_drbg_set_prediction_resistance( mbedtls_ctr_drbg_context *ctx,
                                                 int resistance )
{
    ctx->prediction_resistance = resistance;
}

void mbedtls_ctr_drbg_set_entropy_len( mbedtls_ctr_drbg_context *ctx,
                                       size_t len )
{
    ctx->entropy_len = len;
}

int mbedtls_ctr_drbg_set_nonce_len( mbedtls_ctr_drbg_context *ctx,
                                    size_t len )
{
    /* If mbedtls_ctr_drbg_seed() has already been called, it's
     * too late. Return the error code that's closest to making sense. */
    if( ctx->f_entropy != NULL )
        return( MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED );

    if( len > MBEDTLS_CTR_DRBG_MAX_SEED_INPUT )
        return( MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG );
#if SIZE_MAX > INT_MAX
    /* This shouldn't be an issue because
     * MBEDTLS_CTR_DRBG_MAX_SEED_INPUT < INT_MAX in any sensible
     * configuration, but make sure anyway. */
    if( len > INT_MAX )
        return( MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG );
#endif

    /* For backward compatibility with Mbed TLS <= 2.19, store the
     * entropy nonce length in a field that already exists, but isn't
     * used until after the initial seeding. */
    /* Due to the capping of len above, the value fits in an int. */
    ctx->reseed_counter = (int) len;
    return( 0 );
}

void mbedtls_ctr_drbg_set_reseed_interval( mbedtls_ctr_drbg_context *ctx,
                                           int interval )
{
    ctx->reseed_interval = interval;
}

static int block_cipher_df( unsigned char *output,
                            const unsigned char *data, size_t data_len )
{
    unsigned char buf[MBEDTLS_CTR_DRBG_MAX_SEED_INPUT +
                      MBEDTLS_CTR_DRBG_BLOCKSIZE + 16];
    unsigned char tmp[MBEDTLS_CTR_DRBG_SEEDLEN];
    unsigned char key[MBEDTLS_CTR_DRBG_KEYSIZE];
    unsigned char chain[MBEDTLS_CTR_DRBG_BLOCKSIZE];
    unsigned char *p, *iv;
    mbedtls_aes_context aes_ctx;
    int ret = 0;

    int i, j;
    size_t buf_len, use_len;

    if( data_len > MBEDTLS_CTR_DRBG_MAX_SEED_INPUT )
        return( MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG );

    memset( buf, 0, MBEDTLS_CTR_DRBG_MAX_SEED_INPUT +
            MBEDTLS_CTR_DRBG_BLOCKSIZE + 16 );
    mbedtls_aes_init( &aes_ctx );

    /*
     * Construct IV (16 bytes) and S in buffer
     * IV = Counter (in 32-bits) padded to 16 with zeroes
     * S = Length input string (in 32-bits) || Length of output (in 32-bits) ||
     *     data || 0x80
     *     (Total is padded to a multiple of 16-bytes with zeroes)
     */
    p = buf + MBEDTLS_CTR_DRBG_BLOCKSIZE;
    *p++ = (uint8_t) (( data_len >> 24 ) & 0xff);
    *p++ = ( data_len >> 16 ) & 0xff;
    *p++ = ( data_len >> 8  ) & 0xff;
    *p++ = ( data_len       ) & 0xff;
    p += 3;
    *p++ = MBEDTLS_CTR_DRBG_SEEDLEN;
    memcpy( p, data, data_len );
    p[data_len] = 0x80;

    buf_len = MBEDTLS_CTR_DRBG_BLOCKSIZE + 8 + data_len + 1;

    for( i = 0; i < MBEDTLS_CTR_DRBG_KEYSIZE; i++ )
        key[i] = (uint8_t) i;

    if( ( ret = mbedtls_aes_setkey_enc( &aes_ctx, key,
                                        MBEDTLS_CTR_DRBG_KEYBITS ) ) != 0 )
    {
        goto exit;
    }

    /*
     * Reduce data to MBEDTLS_CTR_DRBG_SEEDLEN bytes of data
     */
    for( j = 0; j < MBEDTLS_CTR_DRBG_SEEDLEN; j += MBEDTLS_CTR_DRBG_BLOCKSIZE )
    {
        p = buf;
        memset( chain, 0, MBEDTLS_CTR_DRBG_BLOCKSIZE );
        use_len = buf_len;

        while( use_len > 0 )
        {
            for( i = 0; i < MBEDTLS_CTR_DRBG_BLOCKSIZE; i++ )
                chain[i] ^= p[i];
            p += MBEDTLS_CTR_DRBG_BLOCKSIZE;
            use_len -= ( use_len >= MBEDTLS_CTR_DRBG_BLOCKSIZE ) ?
                       MBEDTLS_CTR_DRBG_BLOCKSIZE : use_len;

            if( ( ret = mbedtls_aes_crypt_ecb( &aes_ctx, MBEDTLS_AES_ENCRYPT,
                                               chain, chain ) ) != 0 )
            {
                goto exit;
            }
        }

        memcpy( tmp + j, chain, MBEDTLS_CTR_DRBG_BLOCKSIZE );

        /*
         * Update IV
         */
        buf[3]++;
    }

    /*
     * Do final encryption with reduced data
     */
    if( ( ret = mbedtls_aes_setkey_enc( &aes_ctx, tmp,
                                        MBEDTLS_CTR_DRBG_KEYBITS ) ) != 0 )
    {
        goto exit;
    }
    iv = tmp + MBEDTLS_CTR_DRBG_KEYSIZE;
    p = output;

    for( j = 0; j < MBEDTLS_CTR_DRBG_SEEDLEN; j += MBEDTLS_CTR_DRBG_BLOCKSIZE )
    {
        if( ( ret = mbedtls_aes_crypt_ecb( &aes_ctx, MBEDTLS_AES_ENCRYPT,
                                           iv, iv ) ) != 0 )
        {
            goto exit;
        }
        memcpy( p, iv, MBEDTLS_CTR_DRBG_BLOCKSIZE );
        p += MBEDTLS_CTR_DRBG_BLOCKSIZE;
    }
exit:
    mbedtls_aes_free( &aes_ctx );
    /*
    * tidy up the stack
    */
    mbedtls_platform_zeroize( buf, sizeof( buf ) );
    mbedtls_platform_zeroize( tmp, sizeof( tmp ) );
    mbedtls_platform_zeroize( key, sizeof( key ) );
    mbedtls_platform_zeroize( chain, sizeof( chain ) );
    if( 0 != ret )
    {
        /*
        * wipe partial seed from memory
        */
        mbedtls_platform_zeroize( output, MBEDTLS_CTR_DRBG_SEEDLEN );
    }

    return( ret );
}

/* CTR_DRBG_Update (SP 800-90A &sect;10.2.1.2)
 * ctr_drbg_update_internal(ctx, provided_data)
 * implements
 * CTR_DRBG_Update(provided_data, Key, V)
 * with inputs and outputs
 *   ctx->aes_ctx = Key
 *   ctx->counter = V
 */
static int ctr_drbg_update_internal( mbedtls_ctr_drbg_context *ctx,
                          const unsigned char data[MBEDTLS_CTR_DRBG_SEEDLEN] )
{
    unsigned char tmp[MBEDTLS_CTR_DRBG_SEEDLEN];
    unsigned char *p = tmp;
    int i, j;
    int ret = 0;

    memset( tmp, 0, MBEDTLS_CTR_DRBG_SEEDLEN );

    for( j = 0; j < MBEDTLS_CTR_DRBG_SEEDLEN; j += MBEDTLS_CTR_DRBG_BLOCKSIZE )
    {
        /*
         * Increase counter
         */
        for( i = MBEDTLS_CTR_DRBG_BLOCKSIZE; i > 0; i-- )
            if( ++ctx->counter[i - 1] != 0 )
                break;

        /*
         * Crypt counter block
         */
        if( ( ret = mbedtls_aes_crypt_ecb( &ctx->aes_ctx, MBEDTLS_AES_ENCRYPT,
                                           ctx->counter, p ) ) != 0 )
        {
            goto exit;
        }

        p += MBEDTLS_CTR_DRBG_BLOCKSIZE;
    }

    for( i = 0; i < MBEDTLS_CTR_DRBG_SEEDLEN; i++ )
        tmp[i] ^= data[i];

    /*
     * Update key and counter
     */
    if( ( ret = mbedtls_aes_setkey_enc( &ctx->aes_ctx, tmp,
                                        MBEDTLS_CTR_DRBG_KEYBITS ) ) != 0 )
    {
        goto exit;
    }
    memcpy( ctx->counter, tmp + MBEDTLS_CTR_DRBG_KEYSIZE,
            MBEDTLS_CTR_DRBG_BLOCKSIZE );

exit:
    mbedtls_platform_zeroize( tmp, sizeof( tmp ) );
    return( ret );
}

/* CTR_DRBG_Instantiate with derivation function (SP 800-90A &sect;10.2.1.3.2)
 * mbedtls_ctr_drbg_update(ctx, additional, add_len)
 * implements
 * CTR_DRBG_Instantiate(entropy_input, nonce, personalization_string,
 *                      security_strength) -> initial_working_state
 * with inputs
 *   ctx->counter = all-bits-0
 *   ctx->aes_ctx = context from all-bits-0 key
 *   additional[:add_len] = entropy_input || nonce || personalization_string
 * and with outputs
 *   ctx = initial_working_state
 */
int mbedtls_ctr_drbg_update_ret( mbedtls_ctr_drbg_context *ctx,
                                 const unsigned char *additional,
                                 size_t add_len )
{
    unsigned char add_input[MBEDTLS_CTR_DRBG_SEEDLEN];
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

    if( add_len == 0 )
        return( 0 );

    if( ( ret = block_cipher_df( add_input, additional, add_len ) ) != 0 )
        goto exit;
    if( ( ret = ctr_drbg_update_internal( ctx, add_input ) ) != 0 )
        goto exit;

exit:
    mbedtls_platform_zeroize( add_input, sizeof( add_input ) );
    return( ret );
}

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_ctr_drbg_update( mbedtls_ctr_drbg_context *ctx,
                              const unsigned char *additional,
                              size_t add_len )
{
    /* MAX_INPUT would be more logical here, but we have to match
     * block_cipher_df()'s limits since we can't propagate errors */
    if( add_len > MBEDTLS_CTR_DRBG_MAX_SEED_INPUT )
        add_len = MBEDTLS_CTR_DRBG_MAX_SEED_INPUT;
    (void) mbedtls_ctr_drbg_update_ret( ctx, additional, add_len );
}
#endif /* MBEDTLS_DEPRECATED_REMOVED */

/* CTR_DRBG_Reseed with derivation function (SP 800-90A &sect;10.2.1.4.2)
 * mbedtls_ctr_drbg_reseed(ctx, additional, len, nonce_len)
 * implements
 * CTR_DRBG_Reseed(working_state, entropy_input, additional_input)
 *                -> new_working_state
 * with inputs
 *   ctx contains working_state
 *   additional[:len] = additional_input
 * and entropy_input comes from calling ctx->f_entropy
 *                              for (ctx->entropy_len + nonce_len) bytes
 * and with output
 *   ctx contains new_working_state
 */
static int mbedtls_ctr_drbg_reseed_internal( mbedtls_ctr_drbg_context *ctx,
                                             const unsigned char *additional,
                                             size_t len,
                                             size_t nonce_len )
{
    unsigned char seed[MBEDTLS_CTR_DRBG_MAX_SEED_INPUT];
    size_t seedlen = 0;
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

    if( ctx->entropy_len > MBEDTLS_CTR_DRBG_MAX_SEED_INPUT )
        return( MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG );
    if( nonce_len > MBEDTLS_CTR_DRBG_MAX_SEED_INPUT - ctx->entropy_len )
        return( MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG );
    if( len > MBEDTLS_CTR_DRBG_MAX_SEED_INPUT - ctx->entropy_len - nonce_len )
        return( MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG );

    memset( seed, 0, MBEDTLS_CTR_DRBG_MAX_SEED_INPUT );

    /* Gather entropy_len bytes of entropy to seed state. */
    if( 0 != ctx->f_entropy( ctx->p_entropy, seed, ctx->entropy_len ) )
    {
        return( MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED );
    }
    seedlen += ctx->entropy_len;

    /* Gather entropy for a nonce if requested. */
    if( nonce_len != 0 )
    {
        if( 0 != ctx->f_entropy( ctx->p_entropy, seed, nonce_len ) )
        {
            return( MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED );
        }
        seedlen += nonce_len;
    }

    /* Add additional data if provided. */
    if( additional != NULL && len != 0 )
    {
        memcpy( seed + seedlen, additional, len );
        seedlen += len;
    }

    /* Reduce to 384 bits. */
    if( ( ret = block_cipher_df( seed, seed, seedlen ) ) != 0 )
        goto exit;

    /* Update state. */
    if( ( ret = ctr_drbg_update_internal( ctx, seed ) ) != 0 )
        goto exit;
    ctx->reseed_counter = 1;

exit:
    mbedtls_platform_zeroize( seed, sizeof( seed ) );
    return( ret );
}

int mbedtls_ctr_drbg_reseed( mbedtls_ctr_drbg_context *ctx,
                             const unsigned char *additional, size_t len )
{
    return( mbedtls_ctr_drbg_reseed_internal( ctx, additional, len, 0 ) );
}

/* Return a "good" nonce length for CTR_DRBG. The chosen nonce length
 * is sufficient to achieve the maximum security strength given the key
 * size and entropy length. If there is enough entropy in the initial
 * call to the entropy function to serve as both the entropy input and
 * the nonce, don't make a second call to get a nonce. */
static size_t good_nonce_len( size_t entropy_len )
{
    if( entropy_len >= MBEDTLS_CTR_DRBG_KEYSIZE * 3 / 2 )
        return( 0 );
    else
        return( ( entropy_len + 1 ) / 2 );
}

/* CTR_DRBG_Instantiate with derivation function (SP 800-90A &sect;10.2.1.3.2)
 * mbedtls_ctr_drbg_seed(ctx, f_entropy, p_entropy, custom, len)
 * implements
 * CTR_DRBG_Instantiate(entropy_input, nonce, personalization_string,
 *                      security_strength) -> initial_working_state
 * with inputs
 *   custom[:len] = nonce || personalization_string
 * where entropy_input comes from f_entropy for ctx->entropy_len bytes
 * and with outputs
 *   ctx = initial_working_state
 */
int mbedtls_ctr_drbg_seed( mbedtls_ctr_drbg_context *ctx,
                           int (*f_entropy)(void *, unsigned char *, size_t),
                           void *p_entropy,
                           const unsigned char *custom,
                           size_t len )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    unsigned char key[MBEDTLS_CTR_DRBG_KEYSIZE];
    size_t nonce_len;

    memset( key, 0, MBEDTLS_CTR_DRBG_KEYSIZE );

    mbedtls_aes_init( &ctx->aes_ctx );

    ctx->f_entropy = f_entropy;
    ctx->p_entropy = p_entropy;

    if( ctx->entropy_len == 0 )
        ctx->entropy_len = MBEDTLS_CTR_DRBG_ENTROPY_LEN;
    /* ctx->reseed_counter contains the desired amount of entropy to
     * grab for a nonce (see mbedtls_ctr_drbg_set_nonce_len()).
     * If it's -1, indicating that the entropy nonce length was not set
     * explicitly, use a sufficiently large nonce for security. */
    nonce_len = ( ctx->reseed_counter >= 0 ?
                  (size_t) ctx->reseed_counter :
                  good_nonce_len( ctx->entropy_len ) );

    ctx->reseed_interval = MBEDTLS_CTR_DRBG_RESEED_INTERVAL;

    /* Initialize with an empty key. */
    if( ( ret = mbedtls_aes_setkey_enc( &ctx->aes_ctx, key,
                                        MBEDTLS_CTR_DRBG_KEYBITS ) ) != 0 )
    {
        return( ret );
    }

    /* Do the initial seeding. */
    if( ( ret = mbedtls_ctr_drbg_reseed_internal( ctx, custom, len,
                                                  nonce_len ) ) != 0 )
    {
        return( ret );
    }
    return( 0 );
}

/* CTR_DRBG_Generate with derivation function (SP 800-90A &sect;10.2.1.5.2)
 * mbedtls_ctr_drbg_random_with_add(ctx, output, output_len, additional, add_len)
 * implements
 * CTR_DRBG_Reseed(working_state, entropy_input, additional[:add_len])
 *                -> working_state_after_reseed
 *                if required, then
 * CTR_DRBG_Generate(working_state_after_reseed,
 *                   requested_number_of_bits, additional_input)
 *                -> status, returned_bits, new_working_state
 * with inputs
 *   ctx contains working_state
 *   requested_number_of_bits = 8 * output_len
 *   additional[:add_len] = additional_input
 * and entropy_input comes from calling ctx->f_entropy
 * and with outputs
 *   status = SUCCESS (this function does the reseed internally)
 *   returned_bits = output[:output_len]
 *   ctx contains new_working_state
 */
int mbedtls_ctr_drbg_random_with_add( void *p_rng,
                              unsigned char *output, size_t output_len,
                              const unsigned char *additional, size_t add_len )
{
    int ret = 0;
    mbedtls_ctr_drbg_context *ctx = (mbedtls_ctr_drbg_context *) p_rng;
    unsigned char add_input[MBEDTLS_CTR_DRBG_SEEDLEN];
    unsigned char *p = output;
    unsigned char tmp[MBEDTLS_CTR_DRBG_BLOCKSIZE];
    int i;
    size_t use_len;

    if( output_len > MBEDTLS_CTR_DRBG_MAX_REQUEST )
        return( MBEDTLS_ERR_CTR_DRBG_REQUEST_TOO_BIG );

    if( add_len > MBEDTLS_CTR_DRBG_MAX_INPUT )
        return( MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG );

    memset( add_input, 0, MBEDTLS_CTR_DRBG_SEEDLEN );

    if( ctx->reseed_counter > ctx->reseed_interval ||
        ctx->prediction_resistance )
    {
        if( ( ret = mbedtls_ctr_drbg_reseed( ctx, additional, add_len ) ) != 0 )
        {
            return( ret );
        }
        add_len = 0;
    }

    if( add_len > 0 )
    {
        if( ( ret = block_cipher_df( add_input, additional, add_len ) ) != 0 )
            goto exit;
        if( ( ret = ctr_drbg_update_internal( ctx, add_input ) ) != 0 )
            goto exit;
    }

    while( output_len > 0 )
    {
        /*
         * Increase counter
         */
        for( i = MBEDTLS_CTR_DRBG_BLOCKSIZE; i > 0; i-- )
            if( ++ctx->counter[i - 1] != 0 )
                break;

        /*
         * Crypt counter block
         */
        if( ( ret = mbedtls_aes_crypt_ecb( &ctx->aes_ctx, MBEDTLS_AES_ENCRYPT,
                                           ctx->counter, tmp ) ) != 0 )
        {
            goto exit;
        }

        use_len = ( output_len > MBEDTLS_CTR_DRBG_BLOCKSIZE )
            ? MBEDTLS_CTR_DRBG_BLOCKSIZE : output_len;
        /*
         * Copy random block to destination
         */
        memcpy( p, tmp, use_len );
        p += use_len;
        output_len -= use_len;
    }

    if( ( ret = ctr_drbg_update_internal( ctx, add_input ) ) != 0 )
        goto exit;

    ctx->reseed_counter++;

exit:
    mbedtls_platform_zeroize( add_input, sizeof( add_input ) );
    mbedtls_platform_zeroize( tmp, sizeof( tmp ) );
    return( ret );
}

int mbedtls_ctr_drbg_random( void *p_rng, unsigned char *output,
                             size_t output_len )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    mbedtls_ctr_drbg_context *ctx = (mbedtls_ctr_drbg_context *) p_rng;

#if defined(MBEDTLS_THREADING_C)
    if( ( ret = mbedtls_mutex_lock( &ctx->mutex ) ) != 0 )
        return( ret );
#endif

    ret = mbedtls_ctr_drbg_random_with_add( ctx, output, output_len, NULL, 0 );

#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_unlock( &ctx->mutex ) != 0 )
        return( MBEDTLS_ERR_THREADING_MUTEX_ERROR );
#endif

    return( ret );
}

#if defined(MBEDTLS_FS_IO)
int mbedtls_ctr_drbg_write_seed_file( mbedtls_ctr_drbg_context *ctx,
                                      const char *path )
{
    int ret = MBEDTLS_ERR_CTR_DRBG_FILE_IO_ERROR;
    FILE *f;
    unsigned char buf[ MBEDTLS_CTR_DRBG_MAX_INPUT ];

    if( ( f = fopen( path, "wb" ) ) == NULL )
        return( MBEDTLS_ERR_CTR_DRBG_FILE_IO_ERROR );

    if( ( ret = mbedtls_ctr_drbg_random( ctx, buf,
                                         MBEDTLS_CTR_DRBG_MAX_INPUT ) ) != 0 )
        goto exit;

    if( fwrite( buf, 1, MBEDTLS_CTR_DRBG_MAX_INPUT, f ) !=
        MBEDTLS_CTR_DRBG_MAX_INPUT )
    {
        ret = MBEDTLS_ERR_CTR_DRBG_FILE_IO_ERROR;
    }
    else
    {
        ret = 0;
    }

exit:
    mbedtls_platform_zeroize( buf, sizeof( buf ) );

    fclose( f );
    return( ret );
}

int mbedtls_ctr_drbg_update_seed_file( mbedtls_ctr_drbg_context *ctx,
                                       const char *path )
{
    int ret = 0;
    FILE *f = NULL;
    size_t n;
    unsigned char buf[ MBEDTLS_CTR_DRBG_MAX_INPUT ];
    unsigned char c;

    if( ( f = fopen( path, "rb" ) ) == NULL )
        return( MBEDTLS_ERR_CTR_DRBG_FILE_IO_ERROR );

    n = fread( buf, 1, sizeof( buf ), f );
    if( fread( &c, 1, 1, f ) != 0 )
    {
        ret = MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG;
        goto exit;
    }
    if( n == 0 || ferror( f ) )
    {
        ret = MBEDTLS_ERR_CTR_DRBG_FILE_IO_ERROR;
        goto exit;
    }
    fclose( f );
    f = NULL;

    ret = mbedtls_ctr_drbg_update_ret( ctx, buf, n );

exit:
    mbedtls_platform_zeroize( buf, sizeof( buf ) );
    if( f != NULL )
        fclose( f );
    if( ret != 0 )
        return( ret );
    return( mbedtls_ctr_drbg_write_seed_file( ctx, path ) );
}
#endif /* MBEDTLS_FS_IO */

#if defined(MBEDTLS_SELF_TEST)

static const unsigned char entropy_source_pr[96] =
    { 0xc1, 0x80, 0x81, 0xa6, 0x5d, 0x44, 0x02, 0x16,
      0x19, 0xb3, 0xf1, 0x80, 0xb1, 0xc9, 0x20, 0x02,
      0x6a, 0x54, 0x6f, 0x0c, 0x70, 0x81, 0x49, 0x8b,
      0x6e, 0xa6, 0x62, 0x52, 0x6d, 0x51, 0xb1, 0xcb,
      0x58, 0x3b, 0xfa, 0xd5, 0x37, 0x5f, 0xfb, 0xc9,
      0xff, 0x46, 0xd2, 0x19, 0xc7, 0x22, 0x3e, 0x95,
      0x45, 0x9d, 0x82, 0xe1, 0xe7, 0x22, 0x9f, 0x63,
      0x31, 0x69, 0xd2, 0x6b, 0x57, 0x47, 0x4f, 0xa3,
      0x37, 0xc9, 0x98, 0x1c, 0x0b, 0xfb, 0x91, 0x31,
      0x4d, 0x55, 0xb9, 0xe9, 0x1c, 0x5a, 0x5e, 0xe4,
      0x93, 0x92, 0xcf, 0xc5, 0x23, 0x12, 0xd5, 0x56,
      0x2c, 0x4a, 0x6e, 0xff, 0xdc, 0x10, 0xd0, 0x68 };

static const unsigned char entropy_source_nopr[64] =
    { 0x5a, 0x19, 0x4d, 0x5e, 0x2b, 0x31, 0x58, 0x14,
      0x54, 0xde, 0xf6, 0x75, 0xfb, 0x79, 0x58, 0xfe,
      0xc7, 0xdb, 0x87, 0x3e, 0x56, 0x89, 0xfc, 0x9d,
      0x03, 0x21, 0x7c, 0x68, 0xd8, 0x03, 0x38, 0x20,
      0xf9, 0xe6, 0x5e, 0x04, 0xd8, 0x56, 0xf3, 0xa9,
      0xc4, 0x4a, 0x4c, 0xbd, 0xc1, 0xd0, 0x08, 0x46,
      0xf5, 0x98, 0x3d, 0x77, 0x1c, 0x1b, 0x13, 0x7e,
      0x4e, 0x0f, 0x9d, 0x8e, 0xf4, 0x09, 0xf9, 0x2e };

static const unsigned char nonce_pers_pr[16] =
    { 0xd2, 0x54, 0xfc, 0xff, 0x02, 0x1e, 0x69, 0xd2,
      0x29, 0xc9, 0xcf, 0xad, 0x85, 0xfa, 0x48, 0x6c };

static const unsigned char nonce_pers_nopr[16] =
    { 0x1b, 0x54, 0xb8, 0xff, 0x06, 0x42, 0xbf, 0xf5,
      0x21, 0xf1, 0x5c, 0x1c, 0x0b, 0x66, 0x5f, 0x3f };

#if defined(MBEDTLS_CTR_DRBG_USE_128_BIT_KEY)
static const unsigned char result_pr[16] =
    { 0x95, 0x3c, 0xa5, 0xbd, 0x44, 0x1, 0x34, 0xb7,
      0x13, 0x58, 0x3e, 0x6a, 0x6c, 0x7e, 0x88, 0x8a };

static const unsigned char result_nopr[16] =
    { 0x6c, 0x25, 0x27, 0x95, 0xa3, 0x62, 0xd6, 0xdb,
      0x90, 0xfd, 0x69, 0xb5, 0x42, 0x9, 0x4b, 0x84 };
#else /* MBEDTLS_CTR_DRBG_USE_128_BIT_KEY */
static const unsigned char result_pr[16] =
    { 0x34, 0x01, 0x16, 0x56, 0xb4, 0x29, 0x00, 0x8f,
      0x35, 0x63, 0xec, 0xb5, 0xf2, 0x59, 0x07, 0x23 };

static const unsigned char result_nopr[16] =
    { 0xa0, 0x54, 0x30, 0x3d, 0x8a, 0x7e, 0xa9, 0x88,
      0x9d, 0x90, 0x3e, 0x07, 0x7c, 0x6f, 0x21, 0x8f };
#endif /* MBEDTLS_CTR_DRBG_USE_128_BIT_KEY */

static size_t test_offset;
static int ctr_drbg_self_test_entropy( void *data, unsigned char *buf,
                                       size_t len )
{
    const unsigned char *p = data;
    memcpy( buf, p + test_offset, len );
    test_offset += len;
    return( 0 );
}

#define CHK( c )    if( (c) != 0 )                          \
                    {                                       \
                        if( verbose != 0 )                  \
                            mbedtls_printf( "failed\n" );  \
                        return( 1 );                        \
                    }

/*
 * Checkup routine
 */
int mbedtls_ctr_drbg_self_test( int verbose )
{
    mbedtls_ctr_drbg_context ctx;
    unsigned char buf[16];

    mbedtls_ctr_drbg_init( &ctx );

    /*
     * Based on a NIST CTR_DRBG test vector (PR = True)
     */
    if( verbose != 0 )
        mbedtls_printf( "  CTR_DRBG (PR = TRUE) : " );

    test_offset = 0;
    mbedtls_ctr_drbg_set_entropy_len( &ctx, 32 );
    mbedtls_ctr_drbg_set_nonce_len( &ctx, 0 );
    CHK( mbedtls_ctr_drbg_seed( &ctx,
                                ctr_drbg_self_test_entropy,
                                (void *) entropy_source_pr,
                                nonce_pers_pr, 16 ) );
    mbedtls_ctr_drbg_set_prediction_resistance( &ctx, MBEDTLS_CTR_DRBG_PR_ON );
    CHK( mbedtls_ctr_drbg_random( &ctx, buf, MBEDTLS_CTR_DRBG_BLOCKSIZE ) );
    CHK( mbedtls_ctr_drbg_random( &ctx, buf, MBEDTLS_CTR_DRBG_BLOCKSIZE ) );
    CHK( memcmp( buf, result_pr, MBEDTLS_CTR_DRBG_BLOCKSIZE ) );

    mbedtls_ctr_drbg_free( &ctx );

    if( verbose != 0 )
        mbedtls_printf( "passed\n" );

    /*
     * Based on a NIST CTR_DRBG test vector (PR = FALSE)
     */
    if( verbose != 0 )
        mbedtls_printf( "  CTR_DRBG (PR = FALSE): " );

    mbedtls_ctr_drbg_init( &ctx );

    test_offset = 0;
    mbedtls_ctr_drbg_set_entropy_len( &ctx, 32 );
    mbedtls_ctr_drbg_set_nonce_len( &ctx, 0 );
    CHK( mbedtls_ctr_drbg_seed( &ctx,
                                ctr_drbg_self_test_entropy,
                                (void *) entropy_source_nopr,
                                nonce_pers_nopr, 16 ) );
    CHK( mbedtls_ctr_drbg_random( &ctx, buf, 16 ) );
    CHK( mbedtls_ctr_drbg_reseed( &ctx, NULL, 0 ) );
    CHK( mbedtls_ctr_drbg_random( &ctx, buf, 16 ) );
    CHK( memcmp( buf, result_nopr, 16 ) );

    mbedtls_ctr_drbg_free( &ctx );

    if( verbose != 0 )
        mbedtls_printf( "passed\n" );

    if( verbose != 0 )
            mbedtls_printf( "\n" );

    return( 0 );
}
#endif /* MBEDTLS_SELF_TEST */

/* AES */

 #include "mbedtls/error.h"
 #if defined(MBEDTLS_PADLOCK_C)
  #include "mbedtls/padlock.h"
 #endif
 #if defined(MBEDTLS_AESNI_C)
  #include "mbedtls/aesni.h"
 #endif
 #define MBEDTLS_AES_FEWER_TABLES    (1)

/* Parameter validation macros based on platform_util.h */
 #define AES_VALIDATE_RET(cond) \
    MBEDTLS_INTERNAL_VALIDATE_RET(cond, MBEDTLS_ERR_AES_BAD_INPUT_DATA)
 #define AES_VALIDATE(cond) \
    MBEDTLS_INTERNAL_VALIDATE(cond)

/*
 * 32-bit integer manipulation macros (little endian)
 */
 #ifndef GET_UINT32_LE
  #define GET_UINT32_LE(n, b, i)                 \
    {                                            \
        (n) = ((uint32_t) (b)[(i)])              \
              | ((uint32_t) (b)[(i) + 1] << 8)   \
              | ((uint32_t) (b)[(i) + 2] << 16)  \
              | ((uint32_t) (b)[(i) + 3] << 24); \
    }
 #endif

 #ifndef PUT_UINT32_LE
  #define PUT_UINT32_LE(n, b, i)                             \
    {                                                        \
        (b)[(i)]     = (unsigned char) (((n)) & 0xFF);       \
        (b)[(i) + 1] = (unsigned char) (((n) >> 8) & 0xFF);  \
        (b)[(i) + 2] = (unsigned char) (((n) >> 16) & 0xFF); \
        (b)[(i) + 3] = (unsigned char) (((n) >> 24) & 0xFF); \
    }
 #endif

 #if defined(MBEDTLS_PADLOCK_C) && \
    (defined(MBEDTLS_HAVE_X86) || defined(MBEDTLS_PADLOCK_ALIGN16))
static int aes_padlock_ace = -1;
 #endif

 #if defined(MBEDTLS_AES_ROM_TABLES)

/*
 * Forward S-box
 */
static const unsigned char FSb[256] =
{
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5,
    0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
    0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC,
    0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A,
    0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
    0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B,
    0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85,
    0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
    0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17,
    0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
    0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
    0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9,
    0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6,
    0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
    0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94,
    0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68,
    0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

/*
 * Forward tables
 */
  #define FT                                                                    \
                                                                                \
    V(A5, 63, 63, C6), V(84, 7C, 7C, F8), V(99, 77, 77, EE), V(8D, 7B, 7B, F6), \
    V(0D, F2, F2, FF), V(BD, 6B, 6B, D6), V(B1, 6F, 6F, DE), V(54, C5, C5, 91), \
    V(50, 30, 30, 60), V(03, 01, 01, 02), V(A9, 67, 67, CE), V(7D, 2B, 2B, 56), \
    V(19, FE, FE, E7), V(62, D7, D7, B5), V(E6, AB, AB, 4D), V(9A, 76, 76, EC), \
    V(45, CA, CA, 8F), V(9D, 82, 82, 1F), V(40, C9, C9, 89), V(87, 7D, 7D, FA), \
    V(15, FA, FA, EF), V(EB, 59, 59, B2), V(C9, 47, 47, 8E), V(0B, F0, F0, FB), \
    V(EC, AD, AD, 41), V(67, D4, D4, B3), V(FD, A2, A2, 5F), V(EA, AF, AF, 45), \
    V(BF, 9C, 9C, 23), V(F7, A4, A4, 53), V(96, 72, 72, E4), V(5B, C0, C0, 9B), \
    V(C2, B7, B7, 75), V(1C, FD, FD, E1), V(AE, 93, 93, 3D), V(6A, 26, 26, 4C), \
    V(5A, 36, 36, 6C), V(41, 3F, 3F, 7E), V(02, F7, F7, F5), V(4F, CC, CC, 83), \
    V(5C, 34, 34, 68), V(F4, A5, A5, 51), V(34, E5, E5, D1), V(08, F1, F1, F9), \
    V(93, 71, 71, E2), V(73, D8, D8, AB), V(53, 31, 31, 62), V(3F, 15, 15, 2A), \
    V(0C, 04, 04, 08), V(52, C7, C7, 95), V(65, 23, 23, 46), V(5E, C3, C3, 9D), \
    V(28, 18, 18, 30), V(A1, 96, 96, 37), V(0F, 05, 05, 0A), V(B5, 9A, 9A, 2F), \
    V(09, 07, 07, 0E), V(36, 12, 12, 24), V(9B, 80, 80, 1B), V(3D, E2, E2, DF), \
    V(26, EB, EB, CD), V(69, 27, 27, 4E), V(CD, B2, B2, 7F), V(9F, 75, 75, EA), \
    V(1B, 09, 09, 12), V(9E, 83, 83, 1D), V(74, 2C, 2C, 58), V(2E, 1A, 1A, 34), \
    V(2D, 1B, 1B, 36), V(B2, 6E, 6E, DC), V(EE, 5A, 5A, B4), V(FB, A0, A0, 5B), \
    V(F6, 52, 52, A4), V(4D, 3B, 3B, 76), V(61, D6, D6, B7), V(CE, B3, B3, 7D), \
    V(7B, 29, 29, 52), V(3E, E3, E3, DD), V(71, 2F, 2F, 5E), V(97, 84, 84, 13), \
    V(F5, 53, 53, A6), V(68, D1, D1, B9), V(00, 00, 00, 00), V(2C, ED, ED, C1), \
    V(60, 20, 20, 40), V(1F, FC, FC, E3), V(C8, B1, B1, 79), V(ED, 5B, 5B, B6), \
    V(BE, 6A, 6A, D4), V(46, CB, CB, 8D), V(D9, BE, BE, 67), V(4B, 39, 39, 72), \
    V(DE, 4A, 4A, 94), V(D4, 4C, 4C, 98), V(E8, 58, 58, B0), V(4A, CF, CF, 85), \
    V(6B, D0, D0, BB), V(2A, EF, EF, C5), V(E5, AA, AA, 4F), V(16, FB, FB, ED), \
    V(C5, 43, 43, 86), V(D7, 4D, 4D, 9A), V(55, 33, 33, 66), V(94, 85, 85, 11), \
    V(CF, 45, 45, 8A), V(10, F9, F9, E9), V(06, 02, 02, 04), V(81, 7F, 7F, FE), \
    V(F0, 50, 50, A0), V(44, 3C, 3C, 78), V(BA, 9F, 9F, 25), V(E3, A8, A8, 4B), \
    V(F3, 51, 51, A2), V(FE, A3, A3, 5D), V(C0, 40, 40, 80), V(8A, 8F, 8F, 05), \
    V(AD, 92, 92, 3F), V(BC, 9D, 9D, 21), V(48, 38, 38, 70), V(04, F5, F5, F1), \
    V(DF, BC, BC, 63), V(C1, B6, B6, 77), V(75, DA, DA, AF), V(63, 21, 21, 42), \
    V(30, 10, 10, 20), V(1A, FF, FF, E5), V(0E, F3, F3, FD), V(6D, D2, D2, BF), \
    V(4C, CD, CD, 81), V(14, 0C, 0C, 18), V(35, 13, 13, 26), V(2F, EC, EC, C3), \
    V(E1, 5F, 5F, BE), V(A2, 97, 97, 35), V(CC, 44, 44, 88), V(39, 17, 17, 2E), \
    V(57, C4, C4, 93), V(F2, A7, A7, 55), V(82, 7E, 7E, FC), V(47, 3D, 3D, 7A), \
    V(AC, 64, 64, C8), V(E7, 5D, 5D, BA), V(2B, 19, 19, 32), V(95, 73, 73, E6), \
    V(A0, 60, 60, C0), V(98, 81, 81, 19), V(D1, 4F, 4F, 9E), V(7F, DC, DC, A3), \
    V(66, 22, 22, 44), V(7E, 2A, 2A, 54), V(AB, 90, 90, 3B), V(83, 88, 88, 0B), \
    V(CA, 46, 46, 8C), V(29, EE, EE, C7), V(D3, B8, B8, 6B), V(3C, 14, 14, 28), \
    V(79, DE, DE, A7), V(E2, 5E, 5E, BC), V(1D, 0B, 0B, 16), V(76, DB, DB, AD), \
    V(3B, E0, E0, DB), V(56, 32, 32, 64), V(4E, 3A, 3A, 74), V(1E, 0A, 0A, 14), \
    V(DB, 49, 49, 92), V(0A, 06, 06, 0C), V(6C, 24, 24, 48), V(E4, 5C, 5C, B8), \
    V(5D, C2, C2, 9F), V(6E, D3, D3, BD), V(EF, AC, AC, 43), V(A6, 62, 62, C4), \
    V(A8, 91, 91, 39), V(A4, 95, 95, 31), V(37, E4, E4, D3), V(8B, 79, 79, F2), \
    V(32, E7, E7, D5), V(43, C8, C8, 8B), V(59, 37, 37, 6E), V(B7, 6D, 6D, DA), \
    V(8C, 8D, 8D, 01), V(64, D5, D5, B1), V(D2, 4E, 4E, 9C), V(E0, A9, A9, 49), \
    V(B4, 6C, 6C, D8), V(FA, 56, 56, AC), V(07, F4, F4, F3), V(25, EA, EA, CF), \
    V(AF, 65, 65, CA), V(8E, 7A, 7A, F4), V(E9, AE, AE, 47), V(18, 08, 08, 10), \
    V(D5, BA, BA, 6F), V(88, 78, 78, F0), V(6F, 25, 25, 4A), V(72, 2E, 2E, 5C), \
    V(24, 1C, 1C, 38), V(F1, A6, A6, 57), V(C7, B4, B4, 73), V(51, C6, C6, 97), \
    V(23, E8, E8, CB), V(7C, DD, DD, A1), V(9C, 74, 74, E8), V(21, 1F, 1F, 3E), \
    V(DD, 4B, 4B, 96), V(DC, BD, BD, 61), V(86, 8B, 8B, 0D), V(85, 8A, 8A, 0F), \
    V(90, 70, 70, E0), V(42, 3E, 3E, 7C), V(C4, B5, B5, 71), V(AA, 66, 66, CC), \
    V(D8, 48, 48, 90), V(05, 03, 03, 06), V(01, F6, F6, F7), V(12, 0E, 0E, 1C), \
    V(A3, 61, 61, C2), V(5F, 35, 35, 6A), V(F9, 57, 57, AE), V(D0, B9, B9, 69), \
    V(91, 86, 86, 17), V(58, C1, C1, 99), V(27, 1D, 1D, 3A), V(B9, 9E, 9E, 27), \
    V(38, E1, E1, D9), V(13, F8, F8, EB), V(B3, 98, 98, 2B), V(33, 11, 11, 22), \
    V(BB, 69, 69, D2), V(70, D9, D9, A9), V(89, 8E, 8E, 07), V(A7, 94, 94, 33), \
    V(B6, 9B, 9B, 2D), V(22, 1E, 1E, 3C), V(92, 87, 87, 15), V(20, E9, E9, C9), \
    V(49, CE, CE, 87), V(FF, 55, 55, AA), V(78, 28, 28, 50), V(7A, DF, DF, A5), \
    V(8F, 8C, 8C, 03), V(F8, A1, A1, 59), V(80, 89, 89, 09), V(17, 0D, 0D, 1A), \
    V(DA, BF, BF, 65), V(31, E6, E6, D7), V(C6, 42, 42, 84), V(B8, 68, 68, D0), \
    V(C3, 41, 41, 82), V(B0, 99, 99, 29), V(77, 2D, 2D, 5A), V(11, 0F, 0F, 1E), \
    V(CB, B0, B0, 7B), V(FC, 54, 54, A8), V(D6, BB, BB, 6D), V(3A, 16, 16, 2C)

  #define V(a, b, c, d)    0x ## a ## b ## c ## d
static const uint32_t FT0[256] = {FT};
  #undef V

  #if !defined(MBEDTLS_AES_FEWER_TABLES)

   #define V(a, b, c, d)    0x ## b ## c ## d ## a
static const uint32_t FT1[256] = {FT};
   #undef V

   #define V(a, b, c, d)    0x ## c ## d ## a ## b
static const uint32_t FT2[256] = {FT};
   #undef V

   #define V(a, b, c, d)    0x ## d ## a ## b ## c
static const uint32_t FT3[256] = {FT};
   #undef V

  #endif                               /* !MBEDTLS_AES_FEWER_TABLES */

  #undef FT

/*
 * Reverse S-box
 */
static const unsigned char RSb[256] =
{
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38,
    0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87,
    0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D,
    0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2,
    0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA,
    0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A,
    0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02,
    0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA,
    0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85,
    0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89,
    0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20,
    0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31,
    0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D,
    0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0,
    0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26,
    0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

/*
 * Reverse tables
 */
  #define RT                                                                    \
                                                                                \
    V(50, A7, F4, 51), V(53, 65, 41, 7E), V(C3, A4, 17, 1A), V(96, 5E, 27, 3A), \
    V(CB, 6B, AB, 3B), V(F1, 45, 9D, 1F), V(AB, 58, FA, AC), V(93, 03, E3, 4B), \
    V(55, FA, 30, 20), V(F6, 6D, 76, AD), V(91, 76, CC, 88), V(25, 4C, 02, F5), \
    V(FC, D7, E5, 4F), V(D7, CB, 2A, C5), V(80, 44, 35, 26), V(8F, A3, 62, B5), \
    V(49, 5A, B1, DE), V(67, 1B, BA, 25), V(98, 0E, EA, 45), V(E1, C0, FE, 5D), \
    V(02, 75, 2F, C3), V(12, F0, 4C, 81), V(A3, 97, 46, 8D), V(C6, F9, D3, 6B), \
    V(E7, 5F, 8F, 03), V(95, 9C, 92, 15), V(EB, 7A, 6D, BF), V(DA, 59, 52, 95), \
    V(2D, 83, BE, D4), V(D3, 21, 74, 58), V(29, 69, E0, 49), V(44, C8, C9, 8E), \
    V(6A, 89, C2, 75), V(78, 79, 8E, F4), V(6B, 3E, 58, 99), V(DD, 71, B9, 27), \
    V(B6, 4F, E1, BE), V(17, AD, 88, F0), V(66, AC, 20, C9), V(B4, 3A, CE, 7D), \
    V(18, 4A, DF, 63), V(82, 31, 1A, E5), V(60, 33, 51, 97), V(45, 7F, 53, 62), \
    V(E0, 77, 64, B1), V(84, AE, 6B, BB), V(1C, A0, 81, FE), V(94, 2B, 08, F9), \
    V(58, 68, 48, 70), V(19, FD, 45, 8F), V(87, 6C, DE, 94), V(B7, F8, 7B, 52), \
    V(23, D3, 73, AB), V(E2, 02, 4B, 72), V(57, 8F, 1F, E3), V(2A, AB, 55, 66), \
    V(07, 28, EB, B2), V(03, C2, B5, 2F), V(9A, 7B, C5, 86), V(A5, 08, 37, D3), \
    V(F2, 87, 28, 30), V(B2, A5, BF, 23), V(BA, 6A, 03, 02), V(5C, 82, 16, ED), \
    V(2B, 1C, CF, 8A), V(92, B4, 79, A7), V(F0, F2, 07, F3), V(A1, E2, 69, 4E), \
    V(CD, F4, DA, 65), V(D5, BE, 05, 06), V(1F, 62, 34, D1), V(8A, FE, A6, C4), \
    V(9D, 53, 2E, 34), V(A0, 55, F3, A2), V(32, E1, 8A, 05), V(75, EB, F6, A4), \
    V(39, EC, 83, 0B), V(AA, EF, 60, 40), V(06, 9F, 71, 5E), V(51, 10, 6E, BD), \
    V(F9, 8A, 21, 3E), V(3D, 06, DD, 96), V(AE, 05, 3E, DD), V(46, BD, E6, 4D), \
    V(B5, 8D, 54, 91), V(05, 5D, C4, 71), V(6F, D4, 06, 04), V(FF, 15, 50, 60), \
    V(24, FB, 98, 19), V(97, E9, BD, D6), V(CC, 43, 40, 89), V(77, 9E, D9, 67), \
    V(BD, 42, E8, B0), V(88, 8B, 89, 07), V(38, 5B, 19, E7), V(DB, EE, C8, 79), \
    V(47, 0A, 7C, A1), V(E9, 0F, 42, 7C), V(C9, 1E, 84, F8), V(00, 00, 00, 00), \
    V(83, 86, 80, 09), V(48, ED, 2B, 32), V(AC, 70, 11, 1E), V(4E, 72, 5A, 6C), \
    V(FB, FF, 0E, FD), V(56, 38, 85, 0F), V(1E, D5, AE, 3D), V(27, 39, 2D, 36), \
    V(64, D9, 0F, 0A), V(21, A6, 5C, 68), V(D1, 54, 5B, 9B), V(3A, 2E, 36, 24), \
    V(B1, 67, 0A, 0C), V(0F, E7, 57, 93), V(D2, 96, EE, B4), V(9E, 91, 9B, 1B), \
    V(4F, C5, C0, 80), V(A2, 20, DC, 61), V(69, 4B, 77, 5A), V(16, 1A, 12, 1C), \
    V(0A, BA, 93, E2), V(E5, 2A, A0, C0), V(43, E0, 22, 3C), V(1D, 17, 1B, 12), \
    V(0B, 0D, 09, 0E), V(AD, C7, 8B, F2), V(B9, A8, B6, 2D), V(C8, A9, 1E, 14), \
    V(85, 19, F1, 57), V(4C, 07, 75, AF), V(BB, DD, 99, EE), V(FD, 60, 7F, A3), \
    V(9F, 26, 01, F7), V(BC, F5, 72, 5C), V(C5, 3B, 66, 44), V(34, 7E, FB, 5B), \
    V(76, 29, 43, 8B), V(DC, C6, 23, CB), V(68, FC, ED, B6), V(63, F1, E4, B8), \
    V(CA, DC, 31, D7), V(10, 85, 63, 42), V(40, 22, 97, 13), V(20, 11, C6, 84), \
    V(7D, 24, 4A, 85), V(F8, 3D, BB, D2), V(11, 32, F9, AE), V(6D, A1, 29, C7), \
    V(4B, 2F, 9E, 1D), V(F3, 30, B2, DC), V(EC, 52, 86, 0D), V(D0, E3, C1, 77), \
    V(6C, 16, B3, 2B), V(99, B9, 70, A9), V(FA, 48, 94, 11), V(22, 64, E9, 47), \
    V(C4, 8C, FC, A8), V(1A, 3F, F0, A0), V(D8, 2C, 7D, 56), V(EF, 90, 33, 22), \
    V(C7, 4E, 49, 87), V(C1, D1, 38, D9), V(FE, A2, CA, 8C), V(36, 0B, D4, 98), \
    V(CF, 81, F5, A6), V(28, DE, 7A, A5), V(26, 8E, B7, DA), V(A4, BF, AD, 3F), \
    V(E4, 9D, 3A, 2C), V(0D, 92, 78, 50), V(9B, CC, 5F, 6A), V(62, 46, 7E, 54), \
    V(C2, 13, 8D, F6), V(E8, B8, D8, 90), V(5E, F7, 39, 2E), V(F5, AF, C3, 82), \
    V(BE, 80, 5D, 9F), V(7C, 93, D0, 69), V(A9, 2D, D5, 6F), V(B3, 12, 25, CF), \
    V(3B, 99, AC, C8), V(A7, 7D, 18, 10), V(6E, 63, 9C, E8), V(7B, BB, 3B, DB), \
    V(09, 78, 26, CD), V(F4, 18, 59, 6E), V(01, B7, 9A, EC), V(A8, 9A, 4F, 83), \
    V(65, 6E, 95, E6), V(7E, E6, FF, AA), V(08, CF, BC, 21), V(E6, E8, 15, EF), \
    V(D9, 9B, E7, BA), V(CE, 36, 6F, 4A), V(D4, 09, 9F, EA), V(D6, 7C, B0, 29), \
    V(AF, B2, A4, 31), V(31, 23, 3F, 2A), V(30, 94, A5, C6), V(C0, 66, A2, 35), \
    V(37, BC, 4E, 74), V(A6, CA, 82, FC), V(B0, D0, 90, E0), V(15, D8, A7, 33), \
    V(4A, 98, 04, F1), V(F7, DA, EC, 41), V(0E, 50, CD, 7F), V(2F, F6, 91, 17), \
    V(8D, D6, 4D, 76), V(4D, B0, EF, 43), V(54, 4D, AA, CC), V(DF, 04, 96, E4), \
    V(E3, B5, D1, 9E), V(1B, 88, 6A, 4C), V(B8, 1F, 2C, C1), V(7F, 51, 65, 46), \
    V(04, EA, 5E, 9D), V(5D, 35, 8C, 01), V(73, 74, 87, FA), V(2E, 41, 0B, FB), \
    V(5A, 1D, 67, B3), V(52, D2, DB, 92), V(33, 56, 10, E9), V(13, 47, D6, 6D), \
    V(8C, 61, D7, 9A), V(7A, 0C, A1, 37), V(8E, 14, F8, 59), V(89, 3C, 13, EB), \
    V(EE, 27, A9, CE), V(35, C9, 61, B7), V(ED, E5, 1C, E1), V(3C, B1, 47, 7A), \
    V(59, DF, D2, 9C), V(3F, 73, F2, 55), V(79, CE, 14, 18), V(BF, 37, C7, 73), \
    V(EA, CD, F7, 53), V(5B, AA, FD, 5F), V(14, 6F, 3D, DF), V(86, DB, 44, 78), \
    V(81, F3, AF, CA), V(3E, C4, 68, B9), V(2C, 34, 24, 38), V(5F, 40, A3, C2), \
    V(72, C3, 1D, 16), V(0C, 25, E2, BC), V(8B, 49, 3C, 28), V(41, 95, 0D, FF), \
    V(71, 01, A8, 39), V(DE, B3, 0C, 08), V(9C, E4, B4, D8), V(90, C1, 56, 64), \
    V(61, 84, CB, 7B), V(70, B6, 32, D5), V(74, 5C, 6C, 48), V(42, 57, B8, D0)

  #define V(a, b, c, d)    0x ## a ## b ## c ## d
static const uint32_t RT0[256] = {RT};
  #undef V

  #if !defined(MBEDTLS_AES_FEWER_TABLES)

   #define V(a, b, c, d)    0x ## b ## c ## d ## a
static const uint32_t RT1[256] = {RT};
   #undef V

   #define V(a, b, c, d)    0x ## c ## d ## a ## b
static const uint32_t RT2[256] = {RT};
   #undef V

   #define V(a, b, c, d)    0x ## d ## a ## b ## c
static const uint32_t RT3[256] = {RT};
   #undef V

  #endif                               /* !MBEDTLS_AES_FEWER_TABLES */

  #undef RT

/*
 * Round constants
 */
static const uint32_t RCON[10] =
{
    0x00000001, 0x00000002, 0x00000004, 0x00000008,
    0x00000010, 0x00000020, 0x00000040, 0x00000080,
    0x0000001B, 0x00000036
};

 #else                                 /* MBEDTLS_AES_ROM_TABLES */

/*
 * Forward S-box & tables
 */
static unsigned char FSb[256];         // NOLINT(readability-magic-numbers)
static uint32_t      FT0[256];         // NOLINT(readability-magic-numbers)
  #if !defined(MBEDTLS_AES_FEWER_TABLES)
static uint32_t FT1[256];
static uint32_t FT2[256];
static uint32_t FT3[256];
  #endif                               /* !MBEDTLS_AES_FEWER_TABLES */

/*
 * Reverse S-box & tables
 */
static unsigned char RSb[256];
static uint32_t      RT0[256];
  #if !defined(MBEDTLS_AES_FEWER_TABLES)
static uint32_t RT1[256];
static uint32_t RT2[256];
static uint32_t RT3[256];
  #endif                               /* !MBEDTLS_AES_FEWER_TABLES */

/*
 * Round constants
 */
static uint32_t RCON[10];

/*
 * Tables generation code
 */
  #define ROTL8(x)     (((x) << 8) & 0xFFFFFFFF) | ((x) >> 24)               // NOLINT(readability-magic-numbers)
  #define XTIME(x)     (((x) << 1) ^ (((x) & 0x80) ? 0x1B : 0x00))           // NOLINT(readability-magic-numbers)
  #define MUL(x, y)    (((x) && (y)) ? pow[(log[(x)] + log[(y)]) % 255] : 0) // NOLINT(readability-magic-numbers)

static int aes_init_done = 0;

static void aes_gen_tables (void)
{
    int i;
    int x;
    int y;
    int z;
    int pow[256];
    int log[256];
    (void) (RT0);                      /* To remove unused variable warning */

    /*
     * compute pow and log tables over GF(2^8)
     */
    x = 1;
    for (i = 0; i < 256; i++)
    {
        pow[i] = x;
        log[x] = i;
        x      = (x ^ XTIME(x)) & 0xFF; // NOLINT(readability-magic-numbers)
    }

    /*
     * calculate the round constants
     */
    x = 1;
    for (i = 0; i < 10; i++)
    {
        RCON[i] = (uint32_t) x;
        x       = XTIME(x) & 0xFF;                // NOLINT(readability-magic-numbers)
    }

    /*
     * generate the forward and reverse S-boxes
     */
    FSb[0x00] = 0x63;                             // NOLINT(readability-magic-numbers)
    RSb[0x63] = 0x00;                             // NOLINT(readability-magic-numbers)

    for (i = 1; i < 256; i++)
    {
        x = pow[255 - log[i]];                    // NOLINT(readability-magic-numbers)

        y  = x; y = ((y << 1) | (y >> 7)) & 0xFF; // NOLINT(readability-magic-numbers)
        x ^= y; y = ((y << 1) | (y >> 7)) & 0xFF; // NOLINT(readability-magic-numbers)
        x ^= y; y = ((y << 1) | (y >> 7)) & 0xFF; // NOLINT(readability-magic-numbers)
        x ^= y; y = ((y << 1) | (y >> 7)) & 0xFF; // NOLINT(readability-magic-numbers)
        x ^= y ^ 0x63;                            // NOLINT(readability-magic-numbers)

        FSb[i] = (unsigned char) x;
        RSb[x] = (unsigned char) i;
    }

    /*
     * generate the forward and reverse tables
     */
    for (i = 0; i < 256; i++)
    {
        x = FSb[i];
        y = XTIME(x) & 0xFF;           // NOLINT(readability-magic-numbers)
        z = (y ^ x) & 0xFF;            // NOLINT(readability-magic-numbers)

        FT0[i] = ((uint32_t) y) ^
                 ((uint32_t) x << 8) ^
                 ((uint32_t) x << 16) ^
                 ((uint32_t) z << 24);

  #if !defined(MBEDTLS_AES_FEWER_TABLES)
        FT1[i] = ROTL8(FT0[i]);
        FT2[i] = ROTL8(FT1[i]);
        FT3[i] = ROTL8(FT2[i]);
  #endif                               /* !MBEDTLS_AES_FEWER_TABLES */

        x = RSb[i];

        RT0[i] = ((uint32_t) MUL(0x0E, x)) ^
                 ((uint32_t) MUL(0x09, x) << 8) ^
                 ((uint32_t) MUL(0x0D, x) << 16) ^
                 ((uint32_t) MUL(0x0B, x) << 24);

  #if !defined(MBEDTLS_AES_FEWER_TABLES)
        RT1[i] = ROTL8(RT0[i]);
        RT2[i] = ROTL8(RT1[i]);
        RT3[i] = ROTL8(RT2[i]);
  #endif                               /* !MBEDTLS_AES_FEWER_TABLES */
    }
}

  #undef ROTL8

 #endif                                /* MBEDTLS_AES_ROM_TABLES */

 #if defined(MBEDTLS_AES_FEWER_TABLES)

  #define ROTL8(x)        ((uint32_t) ((x) << 8) + (uint32_t) ((x) >> 24))
  #define ROTL16(x)       ((uint32_t) ((x) << 16) + (uint32_t) ((x) >> 16))
  #define ROTL24(x)       ((uint32_t) ((x) << 24) + (uint32_t) ((x) >> 8))

  #define AES_RT0(idx)    RT0[idx]
  #define AES_RT1(idx)    ROTL8(RT0[idx])
  #define AES_RT2(idx)    ROTL16(RT0[idx])
  #define AES_RT3(idx)    ROTL24(RT0[idx])

  #define AES_FT0(idx)    FT0[idx]
  #define AES_FT1(idx)    ROTL8(FT0[idx])
  #define AES_FT2(idx)    ROTL16(FT0[idx])
  #define AES_FT3(idx)    ROTL24(FT0[idx])

 #else                                 /* MBEDTLS_AES_FEWER_TABLES */

  #define AES_RT0(idx)    RT0[idx]
  #define AES_RT1(idx)    RT1[idx]
  #define AES_RT2(idx)    RT2[idx]
  #define AES_RT3(idx)    RT3[idx]

  #define AES_FT0(idx)    FT0[idx]
  #define AES_FT1(idx)    FT1[idx]
  #define AES_FT2(idx)    FT2[idx]
  #define AES_FT3(idx)    FT3[idx]

 #endif                                /* MBEDTLS_AES_FEWER_TABLES */

static void mbedtls_aes_init (mbedtls_aes_context * ctx)
{
    AES_VALIDATE(ctx != NULL);

    memset(ctx, 0, sizeof(mbedtls_aes_context));
}

static void mbedtls_aes_free (mbedtls_aes_context * ctx)
{
    if (ctx == NULL)
    {
        return;
    }

    mbedtls_platform_zeroize(ctx, sizeof(mbedtls_aes_context));
}

/*
 * AES key schedule (encryption)
 */

// #if !defined(MBEDTLS_AES_SETKEY_ENC_ALT)
static int mbedtls_aes_setkey_enc (mbedtls_aes_context * ctx, const unsigned char * key, unsigned int keybits)
{
    unsigned int i;
    uint32_t   * RK;

    AES_VALIDATE_RET(ctx != NULL);
    AES_VALIDATE_RET(key != NULL);
    ctx->nr = 14;

 #if !defined(MBEDTLS_AES_ROM_TABLES)
    if (aes_init_done == 0)
    {
        aes_gen_tables();
        aes_init_done = 1;
    }
 #endif

 #if defined(MBEDTLS_PADLOCK_C) && defined(MBEDTLS_PADLOCK_ALIGN16)
    if (aes_padlock_ace == -1)
    {
        aes_padlock_ace = mbedtls_padlock_has_support(MBEDTLS_PADLOCK_ACE);
    }

    if (aes_padlock_ace)
    {
        ctx->rk = RK = MBEDTLS_PADLOCK_ALIGN16(ctx->buf);
    }
    else
 #endif
    RK      = ctx->buf;
    ctx->rk = ctx->buf;

 #if defined(MBEDTLS_AESNI_C) && defined(MBEDTLS_HAVE_X86_64)
    if (mbedtls_aesni_has_support(MBEDTLS_AESNI_AES))
    {
        return mbedtls_aesni_setkey_enc((unsigned char *) ctx->rk, key, keybits);
    }
 #endif

    for (i = 0; i < (keybits >> 5); i++)
    {
        GET_UINT32_LE(RK[i], key, i << 2);
    }

    for (i = 0; i < 7; i++, RK += 8)
    {
        RK[8] = RK[0] ^ RCON[i] ^
                ((uint32_t) FSb[(RK[7] >> 8) & 0xFF]) ^        // NOLINT(readability-magic-numbers)
                ((uint32_t) FSb[(RK[7] >> 16) & 0xFF] << 8) ^  // NOLINT(readability-magic-numbers)
                ((uint32_t) FSb[(RK[7] >> 24) & 0xFF] << 16) ^ // NOLINT(readability-magic-numbers)
                ((uint32_t) FSb[(RK[7]) & 0xFF] << 24);        // NOLINT(readability-magic-numbers)

        RK[9]  = RK[1] ^ RK[8];
        RK[10] = RK[2] ^ RK[9];
        RK[11] = RK[3] ^ RK[10];

        RK[12] = RK[4] ^
                 ((uint32_t) FSb[(RK[11]) & 0xFF]) ^             // NOLINT(readability-magic-numbers)
                 ((uint32_t) FSb[(RK[11] >> 8) & 0xFF] << 8) ^   // NOLINT(readability-magic-numbers)
                 ((uint32_t) FSb[(RK[11] >> 16) & 0xFF] << 16) ^ // NOLINT(readability-magic-numbers)
                 ((uint32_t) FSb[(RK[11] >> 24) & 0xFF] << 24);  // NOLINT(readability-magic-numbers)

        RK[13] = RK[5] ^ RK[12];
        RK[14] = RK[6] ^ RK[13];
        RK[15] = RK[7] ^ RK[14];
    }

    return 0;
}

// #endif /* !MBEDTLS_AES_SETKEY_ENC_ALT */

 #define AES_FROUND(X0, X1, X2, X3, Y0, Y1, Y2, Y3) \
    do                                              \
    {                                               \
        (X0) = *RK++ ^ AES_FT0(((Y0)) & 0xFF) ^     \
               AES_FT1(((Y1) >> 8) & 0xFF) ^        \
               AES_FT2(((Y2) >> 16) & 0xFF) ^       \
               AES_FT3(((Y3) >> 24) & 0xFF);        \
                                                    \
        (X1) = *RK++ ^ AES_FT0(((Y1)) & 0xFF) ^     \
               AES_FT1(((Y2) >> 8) & 0xFF) ^        \
               AES_FT2(((Y3) >> 16) & 0xFF) ^       \
               AES_FT3(((Y0) >> 24) & 0xFF);        \
                                                    \
        (X2) = *RK++ ^ AES_FT0(((Y2)) & 0xFF) ^     \
               AES_FT1(((Y3) >> 8) & 0xFF) ^        \
               AES_FT2(((Y0) >> 16) & 0xFF) ^       \
               AES_FT3(((Y1) >> 24) & 0xFF);        \
                                                    \
        (X3) = *RK++ ^ AES_FT0(((Y3)) & 0xFF) ^     \
               AES_FT1(((Y0) >> 8) & 0xFF) ^        \
               AES_FT2(((Y1) >> 16) & 0xFF) ^       \
               AES_FT3(((Y2) >> 24) & 0xFF);        \
    } while (0)

 #define AES_RROUND(X0,                         \
                    X1,                         \
                    X2,                         \
                    X3,                         \
                    Y0,                         \
                    Y1,                         \
                    Y2,                         \
                    Y3)                         \
    do                                          \
    {                                           \
        (X0) = *RK++ ^ AES_RT0(((Y0)) & 0xFF) ^ \
               AES_RT1(((Y3) >> 8) & 0xFF) ^    \
               AES_RT2(((Y2) >> 16) & 0xFF) ^   \
               AES_RT3(((Y1) >> 24) & 0xFF);    \
                                                \
        (X1) = *RK++ ^ AES_RT0(((Y1)) & 0xFF) ^ \
               AES_RT1(((Y0) >> 8) & 0xFF) ^    \
               AES_RT2(((Y3) >> 16) & 0xFF) ^   \
               AES_RT3(((Y2) >> 24) & 0xFF);    \
                                                \
        (X2) = *RK++ ^ AES_RT0(((Y2)) & 0xFF) ^ \
               AES_RT1(((Y1) >> 8) & 0xFF) ^    \
               AES_RT2(((Y0) >> 16) & 0xFF) ^   \
               AES_RT3(((Y3) >> 24) & 0xFF);    \
                                                \
        (X3) = *RK++ ^ AES_RT0(((Y3)) & 0xFF) ^ \
               AES_RT1(((Y2) >> 8) & 0xFF) ^    \
               AES_RT2(((Y1) >> 16) & 0xFF) ^   \
               AES_RT3(((Y0) >> 24) & 0xFF);    \
    } while (0)

/*
 * AES-ECB block encryption
 */
static int mbedtls_internal_aes_encrypt (mbedtls_aes_context * ctx, const unsigned char input[16],
                                         unsigned char output[16])
{
    int        i;
    uint32_t * RK;
    uint32_t   X0;
    uint32_t   X1;
    uint32_t   X2;
    uint32_t   X3;
    uint32_t   Y0;
    uint32_t   Y1;
    uint32_t   Y2;
    uint32_t   Y3;

    RK = ctx->rk;

    GET_UINT32_LE(X0, input, 0); X0  ^= *RK++;
    GET_UINT32_LE(X1, input, 4); X1  ^= *RK++;
    GET_UINT32_LE(X2, input, 8); X2  ^= *RK++;
    GET_UINT32_LE(X3, input, 12); X3 ^= *RK++;

    for (i = (ctx->nr >> 1) - 1; i > 0; i--)
    {
        AES_FROUND(Y0, Y1, Y2, Y3, X0, X1, X2, X3);
        AES_FROUND(X0, X1, X2, X3, Y0, Y1, Y2, Y3);
    }

    AES_FROUND(Y0, Y1, Y2, Y3, X0, X1, X2, X3);

    X0 = *RK++ ^ \
         ((uint32_t) FSb[(Y0) & 0xFF]) ^             // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y1 >> 8) & 0xFF] << 8) ^   // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y2 >> 16) & 0xFF] << 16) ^ // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y3 >> 24) & 0xFF] << 24);  // NOLINT(readability-magic-numbers)

    X1 = *RK++ ^ \
         ((uint32_t) FSb[(Y1) & 0xFF]) ^             // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y2 >> 8) & 0xFF] << 8) ^   // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y3 >> 16) & 0xFF] << 16) ^ // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y0 >> 24) & 0xFF] << 24);  // NOLINT(readability-magic-numbers)

    X2 = *RK++ ^ \
         ((uint32_t) FSb[(Y2) & 0xFF]) ^             // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y3 >> 8) & 0xFF] << 8) ^   // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y0 >> 16) & 0xFF] << 16) ^ // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y1 >> 24) & 0xFF] << 24);  // NOLINT(readability-magic-numbers)

    X3 = *RK++ ^ \
         ((uint32_t) FSb[(Y3) & 0xFF]) ^             // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y0 >> 8) & 0xFF] << 8) ^   // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y1 >> 16) & 0xFF] << 16) ^ // NOLINT(readability-magic-numbers)
         ((uint32_t) FSb[(Y2 >> 24) & 0xFF] << 24);  // NOLINT(readability-magic-numbers)

    PUT_UINT32_LE(X0, output, 0);
    PUT_UINT32_LE(X1, output, 4);
    PUT_UINT32_LE(X2, output, 8);
    PUT_UINT32_LE(X3, output, 12);

    mbedtls_platform_zeroize(&X0, sizeof(X0));
    mbedtls_platform_zeroize(&X1, sizeof(X1));
    mbedtls_platform_zeroize(&X2, sizeof(X2));
    mbedtls_platform_zeroize(&X3, sizeof(X3));

    mbedtls_platform_zeroize(&Y0, sizeof(Y0));
    mbedtls_platform_zeroize(&Y1, sizeof(Y1));
    mbedtls_platform_zeroize(&Y2, sizeof(Y2));
    mbedtls_platform_zeroize(&Y3, sizeof(Y3));

    mbedtls_platform_zeroize(&RK, sizeof(RK));

    return 0;
}

/*
 * AES-ECB block encryption/decryption
 */
static int mbedtls_aes_crypt_ecb (mbedtls_aes_context * ctx,
                                  int                   mode,
                                  const unsigned char   input[16],
                                  unsigned char         output[16])
{
    AES_VALIDATE_RET(ctx != NULL);
    AES_VALIDATE_RET(input != NULL);
    AES_VALIDATE_RET(output != NULL);
    AES_VALIDATE_RET(mode == MBEDTLS_AES_ENCRYPT ||
                     mode == MBEDTLS_AES_DECRYPT);
    (void) mode; // Unused in some build configurations

 #if defined(MBEDTLS_AESNI_C) && defined(MBEDTLS_HAVE_X86_64)
    if (mbedtls_aesni_has_support(MBEDTLS_AESNI_AES))
    {
        return mbedtls_aesni_crypt_ecb(ctx, mode, input, output);
    }
 #endif

 #if defined(MBEDTLS_PADLOCK_C) && defined(MBEDTLS_HAVE_X86)
    if (aes_padlock_ace)
    {
        if (mbedtls_padlock_xcryptecb(ctx, mode, input, output) == 0)
        {
            return 0;
        }

        // If padlock data misaligned, we just fall back to
        // unaccelerated mode
        //
    }
 #endif

    return mbedtls_internal_aes_encrypt(ctx, input, output);
}

void sw_aes_256_enc_test (void)
{
    uint8_t input[128]    = {0xa5};               // NOLINT(readability-magic-numbers)
    uint8_t output[256]   = {0};                  // NOLINT(readability-magic-numbers)
    uint8_t aes256key[32] = {0x55};               // NOLINT(readability-magic-numbers)
    memset(input, 0xa5, 128);                     // NOLINT(readability-magic-numbers)
    memset(aes256key, 0x55, 32);                  // NOLINT(readability-magic-numbers)
    mbedtls_aes_context ctx;
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_enc(&ctx, aes256key, 256); // NOLINT(readability-magic-numbers)
    mbedtls_aes_crypt_ecb(&ctx, MBEDTLS_AES_ENCRYPT, input, output);
}

#endif                                            /* MBEDTLS_CTR_DRBG_C_ALT */
