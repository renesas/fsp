/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "common.h"

#if defined(MBEDTLS_GCM_C)

 #include "mbedtls/gcm.h"
 #include "mbedtls/platform_util.h"
 #include "mbedtls/error.h"

 #include <string.h>

 #if defined(MBEDTLS_AESNI_C)
  #include "mbedtls/aesni.h"
 #endif

 #if defined(MBEDTLS_SELF_TEST) && defined(MBEDTLS_AES_C)
  #include "mbedtls/aes.h"
  #include "mbedtls/platform.h"
  #if !defined(MBEDTLS_PLATFORM_C)
   #include <stdio.h>
   #define mbedtls_printf    printf
  #endif                               /* MBEDTLS_PLATFORM_C */
 #endif                                /* MBEDTLS_SELF_TEST && MBEDTLS_AES_C */

 #if defined(MBEDTLS_GCM_ALT)
  #include "hw_sce_private.h"
  #include "hw_sce_aes_private.h"
  #include "hw_sce_ra_private.h"
  #include "aes_alt.h"
  #include "platform_alt.h"

  #define SCE9_AES_GCM_KEY_TYPE_GENERAL    (0)

/* Prepare GCM IV for encryption/decryption
 * Ref: https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38d.pdf
 * */
static fsp_err_t prepare_gcm_iv(uint8_t  * ivec,
                                uint32_t   ivec_len,
                                uint32_t * key_index,
                                uint32_t   key_index_word_size,
                                uint32_t * hashed_ivec);

static fsp_err_t prepare_gcm_iv (uint8_t  * ivec,
                                 uint32_t   ivec_len,
                                 uint32_t * key_index,
                                 uint32_t   key_index_word_size,
                                 uint32_t * hashed_ivec)
{
    uint32_t  hash_subkey[4]     = {0};
    uint32_t  hashed_ivec_tmp[4] = {0};
    uint32_t  zero[4]            = {0};
    uint32_t  ivec_length_rest   = 0;
    uint32_t  ivec_bit_len[4]    = {0};
    uint32_t  ivec_tmp[4]        = {0};
    fsp_err_t ret                = FSP_SUCCESS;
    uint32_t  dummy_iv[4]        = {0};
    uint32_t  indata_cmd         = change_endian_long(SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION);
    uint32_t  indata_key_type    = 0;
    fsp_err_t err                = FSP_SUCCESS;

    /* when iv_len is 12 (96 bit), aad 0x00000001 padding */
    if (12U == ivec_len)
    {
        /* If len(IV) = 96 then, hashed_ivec = (IV|| 31 bit 0 padding|| 1) */
        memcpy(hashed_ivec, ivec, 12U);
        hashed_ivec[3] = change_endian_long(0x00000001U);
    }
    /* when iv_len is not 12 (96 bit), aad ghash padding */
    else
    {
        /* Encrypt 4 words (128 bit) zeros with the AES key. The generated cipher is the hash subkey used by GHASH HW API. */
        if (key_index_word_size == 0U)
        {
            err = HW_SCE_Aes128EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, key_index, NULL, dummy_iv);

            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) &zero[0],
                                                     (uint32_t *) &hash_subkey[0],
                                                     BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            }

            ret = HW_SCE_Aes128EncryptDecryptFinalSub();
        }

  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
        else if (key_index_word_size == 1U)
        {
            err = HW_SCE_Aes192EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, key_index, NULL, dummy_iv);

            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) &zero[0],
                                                     (uint32_t *) &hash_subkey[0],
                                                     BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            }

            ret = HW_SCE_Aes192EncryptDecryptFinalSub();
        }
        else if (key_index_word_size == 2U)
        {
            err = HW_SCE_Aes256EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, key_index, NULL, dummy_iv);

            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) &zero[0],
                                                     (uint32_t *) &hash_subkey[0],
                                                     BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            }

            ret = HW_SCE_Aes256EncryptDecryptFinalSub();
        }
  #endif
        else
        {
            ret = FSP_ERR_UNSUPPORTED;
        }

        if (FSP_SUCCESS == ret)
        {
            if (MBEDTLS_MAX_BLOCK_LENGTH <= ivec_len)
            {
                /* Generate GHASH for all complete IV blocks within ivec_len */
                ret =
                    HW_SCE_GhashSub(hash_subkey, zero, (uint32_t *) ivec, hashed_ivec_tmp,
                                    (ivec_len / MBEDTLS_MAX_BLOCK_LENGTH) * BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
                if (FSP_SUCCESS == ret)
                {
                    ivec_length_rest = ivec_len % MBEDTLS_MAX_BLOCK_LENGTH;

                    /* Generate GHASH for all remaining partial IV block. Pad with 0 to create complete block. */
                    if (0U != ivec_length_rest)
                    {
                        memcpy(ivec_tmp, ivec + (ivec_len - ivec_length_rest), ivec_length_rest);
                        ret =
                            HW_SCE_GhashSub(hash_subkey, hashed_ivec_tmp, ivec_tmp, hashed_ivec_tmp,
                                            BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
                    }
                }
            }
            else
            {
                ret =
                    HW_SCE_GhashSub(hash_subkey, zero, (uint32_t *) ivec, hashed_ivec_tmp,
                                    BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            }

            /* Create 64bit IV length and perform GHASH using previously computed hashed_ivec_tmp */
            if (FSP_SUCCESS == ret)
            {
                /* calculate ivec bit length */
                ivec_bit_len[0] = 0U;
                ivec_bit_len[1] = 0U;

                /* Store carry in word 0 if the ivec_len is larger than 2^29 */
                ivec_bit_len[2] = change_endian_long(ivec_len >> 29U);
                ivec_bit_len[3] = change_endian_long(ivec_len << 3U);

                /* Compute GHASH(IV||0 padding||64bit IV length)*/
                ret =
                    HW_SCE_GhashSub(hash_subkey, hashed_ivec_tmp, ivec_bit_len, hashed_ivec,
                                    BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            }
        }
    }

    return ret;
}

/* AES-GCM Encryption/Decryption Init HW call table based on key size */
static const hw_sce_aes_gcm_crypt_init_t g_sce_aes_gcm_crypt_init[][2U] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes128GcmEncryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes128GcmDecryptInitSubGeneral,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes192GcmEncryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes192GcmDecryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes256GcmEncryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes256GcmDecryptInitSubGeneral,
  #endif
};

/* AES-GCM Encryption/Decryption Update AAD HW call table based on key size */
static const hw_sce_aes_gcm_update_aad_t g_sce_aes_gcm_update_aad[][2U] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes128GcmEncryptUpdateAADSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes128GcmDecryptUpdateAADSub,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes192GcmEncryptUpdateAADSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes192GcmDecryptUpdateAADSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes256GcmEncryptUpdateAADSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes256GcmDecryptUpdateAADSub,
  #endif
};

/* AES-GCM Encryption/Decryption Update Transition HW call table based on key size */
static const hw_sce_aes_gcm_crypt_update_transition_t g_sce_aes_gcm_crypt_update_transition[][2U] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes128GcmEncryptUpdateTransitionSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes128GcmDecryptUpdateTransitionSub,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes192GcmEncryptUpdateTransitionSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes192GcmDecryptUpdateTransitionSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes256GcmEncryptUpdateTransitionSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes256GcmDecryptUpdateTransitionSub,
  #endif
};

/* AES-GCM Encryption/Decryption Update HW call table based on key size */
static const hw_sce_aes_gcm_crypt_update_t g_sce_aes_gcm_crypt_update[][2U] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes128GcmEncryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes128GcmDecryptUpdateSub,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes192GcmEncryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes192GcmDecryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes256GcmEncryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes256GcmDecryptUpdateSub,
  #endif
};

/* AES-GCM Encryption Final HW call table based on key size */
static const hw_sce_aes_gcm_encrypt_final_t g_sce_aes_gcm_encrypt_final[] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)] =
        HW_SCE_Aes128GcmEncryptFinalSub,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)] =
        HW_SCE_Aes192GcmEncryptFinalSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)] =
        HW_SCE_Aes256GcmEncryptFinalSub,
  #endif
};

/* AES-GCM Decryption Final HW call table based on key size */
static const hw_sce_aes_gcm_decrypt_final_t g_sce_aes_gcm_decrypt_final[] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)] =
        HW_SCE_Aes128GcmDecryptFinalSub,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)] =
        HW_SCE_Aes192GcmDecryptFinalSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)] =
        HW_SCE_Aes256GcmDecryptFinalSub,
  #endif
};

/* AES-GCM operation using SCE9 HW procedures */
int sce_gcm_crypt_and_tag (mbedtls_gcm_context * ctx,
                           int                   mode,
                           size_t                length,
                           const unsigned char * iv,
                           size_t                iv_len,
                           const unsigned char * aad,
                           size_t                aad_len,
                           const unsigned char * input,
                           unsigned char       * output,
                           size_t                tag_len,
                           unsigned char       * tag)
{
    uint32_t              key_len_idx      = (uint32_t) RM_PSA_CRYPTO_AES_LOOKUP_INDEX(ctx->cipher_ctx.key_bitlen);
    mbedtls_aes_context * aes_ctx          = (mbedtls_aes_context *) ctx->cipher_ctx.cipher_ctx;
    fsp_err_t             err              = FSP_SUCCESS;
    uint32_t              aad_bit_size[2]  = {0};
    uint32_t              data_bit_size[2] = {0};
    uint32_t              hashed_ivec[4]   = {0};
    uint8_t               work_buffer[MBEDTLS_MAX_BLOCK_LENGTH] = {0};
    uint32_t              length_remaining = 0;
    uint32_t              input_length     = aad_len;
    uint32_t              key_type[1]      = {SCE9_AES_GCM_KEY_TYPE_GENERAL};
    uint8_t             * gcm_buffer;
    uint32_t              dummy_val[1] = {0};

    if ((tag_len > 16) || (tag_len < 4))
    {
        return MBEDTLS_ERR_GCM_BAD_INPUT;
    }

    /* Get the hashed IV for AES-GCM operations */
    prepare_gcm_iv((uint8_t *) iv, iv_len, aes_ctx->buf, key_len_idx, hashed_ivec);

    /* Encryption/Decryption Init */
    err = g_sce_aes_gcm_crypt_init[key_len_idx][mode](key_type, dummy_val, dummy_val, (uint32_t *) (aes_ctx->buf),
                                                      (uint32_t *) hashed_ivec, dummy_val);
    if (FSP_SUCCESS == err)
    {
        length_remaining = aad_len % MBEDTLS_MAX_BLOCK_LENGTH;
        input_length    -= length_remaining;

        g_sce_aes_gcm_update_aad[key_len_idx][mode]((uint32_t *) aad, BYTES_TO_WORDS(input_length));

        if (length_remaining)
        {
            /* Pad the last inclomplte block of aad data with zeroes to create a complete block */
            memcpy(work_buffer, &aad[input_length], length_remaining);
            g_sce_aes_gcm_update_aad[key_len_idx][mode]((uint32_t *) work_buffer,
                                                        BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
        }

        g_sce_aes_gcm_crypt_update_transition[key_len_idx][mode]();

        input_length     = length;
        length_remaining = length % MBEDTLS_MAX_BLOCK_LENGTH;
        input_length    -= length_remaining;

        if (input_length)
        {
            g_sce_aes_gcm_crypt_update[key_len_idx][mode]((uint32_t *) input, (uint32_t *) output,
                                                          BYTES_TO_WORDS(input_length));
        }

        if (length_remaining)
        {
            memset(work_buffer, 0, sizeof(work_buffer));

            /* Pad the last inclomplte block of plaintext/cipher data with zeroes to create a complete block */
            memcpy(work_buffer, &input[input_length], length_remaining);
            gcm_buffer = work_buffer;
        }
        else
        {
            gcm_buffer = (uint8_t *) input;
        }

        /* Set up bit sizes for AAD and plaintext/ciphertext */
        /* Store carry in word 0 if the aad_len is larger than 2^29 */
        aad_bit_size[0] = change_endian_long((aad_len & 0xe000000U) >> 29U);
        aad_bit_size[1] = change_endian_long(aad_len << 3U);

        /* Store carry in word 0 if the length is larger than 2^29 */
        data_bit_size[0] = change_endian_long((length & 0xe000000U) >> 29U);
        data_bit_size[1] = change_endian_long(length << 3U);
        if (mode == MBEDTLS_GCM_ENCRYPT)
        {
            err =
                g_sce_aes_gcm_encrypt_final[key_len_idx]((uint32_t *) gcm_buffer, data_bit_size, aad_bit_size,
                                                         (uint32_t *) &output[input_length], (uint32_t *) tag);
        }
        else
        {
            uint32_t tag_bit_size[1] = {0};
            uint32_t padded_tag[4]   = {0};
            tag_bit_size[0] = change_endian_long(tag_len);

            /* Zero pad the tag if tag length is less than 16 bytes */
            memcpy(padded_tag, tag, tag_len);
            err =
                g_sce_aes_gcm_decrypt_final[key_len_idx]((uint32_t *) gcm_buffer, data_bit_size,
                                                         aad_bit_size, (uint32_t *) padded_tag,
                                                         tag_bit_size, (uint32_t *) &output[input_length]);

            /* A DecryptFinal failure is a tag mismatch: report it as an authentication failure so
             * the PSA layer surfaces PSA_ERROR_INVALID_SIGNATURE, matching the multi-part
             * sce_gcm_verify() path. An Init/earlier-stage fault falls through to the HW-accel
             * error return below. */
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_GCM_AUTH_FAILED;
            }
        }
    }

    if (FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }
    else
    {
        return 0U;
    }
}

/* ===================================================================================
 * HW-accelerated multi-part AES-GCM (held-open SCE GCM session)
 *
 * Drives the SAME SCE GCM primitives as the one-shot sce_gcm_crypt_and_tag(), but split
 * across the PSA setup/update/finish calls. The SCE GCM session is held open for the
 * lifetime of the operation - no other SCE operation may run between starts() and
 * finish()/free(). Sub-block (partial) data is buffered in ctx->buf; only whole 16-byte
 * blocks are handed to the HW UpdateAAD/Update primitives. The trailing partial block and
 * the length block are processed by Final. The counter and GHASH state persist in the
 * held-open session for the whole operation.
 * =================================================================================== */

/* End the AAD phase and switch the engine into the text phase. Similar to the one-shot, which
 * always issues an UpdateAAD (even empty) before the switch to the text phase. */
static void sce_gcm_aad_to_text (mbedtls_gcm_context * ctx, uint32_t key_len_idx, int mode)
{
    uint32_t words = 0U;

    /* This data is always a sub-block remainder so should never overrun MBEDTLS_MAX_BLOCK_LENGTH. */
    if (ctx->sce_buf_len >= MBEDTLS_MAX_BLOCK_LENGTH)
    {
        ctx->sce_buf_len = 0U;         /* fail safe which will cause an error rather than underflow the memset */
    }

    if (ctx->sce_buf_len != 0U)
    {
        /* zero-pad the final partial AAD block to a whole block */
        memset(ctx->buf + ctx->sce_buf_len, 0, MBEDTLS_MAX_BLOCK_LENGTH - ctx->sce_buf_len);
        words = BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH);
    }

    g_sce_aes_gcm_update_aad[key_len_idx][mode]((uint32_t *) ctx->buf, words);
    ctx->sce_buf_len = 0U;

    g_sce_aes_gcm_crypt_update_transition[key_len_idx][mode]();
    ctx->sce_stage = SCE_MBEDTLS_GCM_OPERATION_STATE_TEXT;
}

int sce_gcm_starts (mbedtls_gcm_context * ctx, int mode, const unsigned char * iv, size_t iv_len)
{
    uint32_t              key_len_idx    = (uint32_t) RM_PSA_CRYPTO_AES_LOOKUP_INDEX(ctx->cipher_ctx.key_bitlen);
    mbedtls_aes_context * aes_ctx        = (mbedtls_aes_context *) ctx->cipher_ctx.cipher_ctx;
    uint32_t              hashed_ivec[4] = {0};
    uint32_t              key_type[1]    = {SCE9_AES_GCM_KEY_TYPE_GENERAL};
    uint32_t              dummy_val[1]   = {0};
    fsp_err_t             err;

    /* Compute J0 / hashed IV (HW for non-96-bit IV), then open the HW GCM session. */
    prepare_gcm_iv((uint8_t *) iv, iv_len, aes_ctx->buf, key_len_idx, hashed_ivec);

    err = g_sce_aes_gcm_crypt_init[key_len_idx][mode](key_type, dummy_val, dummy_val,
                                                      (uint32_t *) (aes_ctx->buf),
                                                      (uint32_t *) hashed_ivec, dummy_val);
    if (FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    ctx->mode        = (unsigned char) mode;
    ctx->len         = 0;
    ctx->add_len     = 0;
    ctx->sce_buf_len = 0U;
    ctx->sce_stage   = SCE_MBEDTLS_GCM_OPERATION_STATE_AAD;

    return 0;
}

int sce_gcm_update_ad (mbedtls_gcm_context * ctx, const unsigned char * add, size_t add_len)
{
    uint32_t              key_len_idx = (uint32_t) RM_PSA_CRYPTO_AES_LOOKUP_INDEX(ctx->cipher_ctx.key_bitlen);
    int                   mode        = (int) ctx->mode;
    const unsigned char * p           = add;
    size_t                offset      = ctx->sce_buf_len;
    size_t                whole;

    ctx->add_len += add_len;

    /* Complete a previously-staged partial AAD block. */
    if (offset != 0U)
    {
        size_t take = MBEDTLS_MAX_BLOCK_LENGTH - offset;
        if (take > add_len)
        {
            take = add_len;
        }

        memcpy(ctx->buf + offset, p, take);
        offset += take; p += take; add_len -= take;
        if (offset == MBEDTLS_MAX_BLOCK_LENGTH)
        {
            g_sce_aes_gcm_update_aad[key_len_idx][mode]((uint32_t *) ctx->buf,
                                                        BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            offset = 0U;
        }

        ctx->sce_buf_len = (unsigned char) offset;
    }

    /* Absorb all whole blocks in one HW call. */
    whole = add_len & ~(size_t) (MBEDTLS_MAX_BLOCK_LENGTH - 1U);
    if (whole != 0U)
    {
        g_sce_aes_gcm_update_aad[key_len_idx][mode]((uint32_t *) p, BYTES_TO_WORDS(whole));
        p += whole; add_len -= whole;
    }

    /* Stage the remainder (< one block). */
    if (add_len != 0U)
    {
        memcpy(ctx->buf + ctx->sce_buf_len, p, add_len);
        ctx->sce_buf_len = (unsigned char) (ctx->sce_buf_len + add_len);
    }

    return 0;
}

int sce_gcm_update (mbedtls_gcm_context * ctx,
                    const unsigned char * input,
                    size_t                input_length,
                    unsigned char       * output,
                    size_t                output_size,
                    size_t              * output_length)
{
    uint32_t              key_len_idx = (uint32_t) RM_PSA_CRYPTO_AES_LOOKUP_INDEX(ctx->cipher_ctx.key_bitlen);
    int                   mode        = (int) ctx->mode;
    const unsigned char * p           = input;
    unsigned char       * out         = output;
    size_t                emitted     = 0;
    size_t                offset;
    size_t                whole;

    (void) output_size;
    *output_length = 0;

    /* First non-empty text update ends the AAD phase (one-way transition). A zero-length
     * update does not transition, so a trailing partial AAD block can still accept more AAD. */
    if ((ctx->sce_stage == SCE_MBEDTLS_GCM_OPERATION_STATE_AAD) && (input_length != 0U))
    {
        sce_gcm_aad_to_text(ctx, key_len_idx, mode);
    }

    if (input_length == 0U)
    {
        return 0;
    }

    ctx->len += input_length;
    offset    = ctx->sce_buf_len;

    /* Complete a previously-staged partial text block. Its ciphertext is emitted at the
     * start of this call's output (the staged input bytes were never emitted previously). */
    if (offset != 0U)
    {
        size_t take = MBEDTLS_MAX_BLOCK_LENGTH - offset;
        if (take > input_length)
        {
            take = input_length;
        }

        memcpy(ctx->buf + offset, p, take);
        offset += take; p += take; input_length -= take;
        if (offset == MBEDTLS_MAX_BLOCK_LENGTH)
        {
            g_sce_aes_gcm_crypt_update[key_len_idx][mode]((uint32_t *) ctx->buf, (uint32_t *) out,
                                                          BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            out += MBEDTLS_MAX_BLOCK_LENGTH; emitted += MBEDTLS_MAX_BLOCK_LENGTH; offset = 0U;
        }

        ctx->sce_buf_len = (unsigned char) offset;
    }

    /* Process all whole blocks in one HW call. */
    whole = input_length & ~(size_t) (MBEDTLS_MAX_BLOCK_LENGTH - 1U);
    if (whole != 0U)
    {
        g_sce_aes_gcm_crypt_update[key_len_idx][mode]((uint32_t *) p, (uint32_t *) out,
                                                      BYTES_TO_WORDS(whole));
        out += whole; emitted += whole; p += whole; input_length -= whole;
    }

    /* Stage the remainder (< one block) for finish(). */
    if (input_length != 0U)
    {
        memcpy(ctx->buf + ctx->sce_buf_len, p, input_length);
        ctx->sce_buf_len = (unsigned char) (ctx->sce_buf_len + input_length);
    }

    *output_length = emitted;

    return 0;
}

int sce_gcm_finish (mbedtls_gcm_context * ctx,
                    unsigned char       * output,
                    size_t                output_size,
                    size_t              * output_length,
                    unsigned char       * tag,
                    size_t                tag_len)
{
    uint32_t  key_len_idx      = (uint32_t) RM_PSA_CRYPTO_AES_LOOKUP_INDEX(ctx->cipher_ctx.key_bitlen);
    int       mode             = (int) ctx->mode;
    uint32_t  aad_bit_size[2]  = {0};
    uint32_t  data_bit_size[2] = {0};
    size_t    aad_len          = (size_t) ctx->add_len;
    size_t    length           = (size_t) ctx->len;
    fsp_err_t err;

    (void) output_size;

    if ((tag_len > 16) || (tag_len < 4))
    {
        return MBEDTLS_ERR_GCM_BAD_INPUT;
    }

    /* No text supplied (GMAC / empty plaintext): still need the AAD->text transition. */
    if (ctx->sce_stage == SCE_MBEDTLS_GCM_OPERATION_STATE_AAD)
    {
        sce_gcm_aad_to_text(ctx, key_len_idx, mode);
    }

    /* Zero-pad the final partial block (0..15 staged bytes). For block-aligned totals
     * sce_buf_len == 0 and the HW ignores this block (data_bit_size is a 128-bit multiple). */
    memset(ctx->buf + ctx->sce_buf_len, 0, MBEDTLS_MAX_BLOCK_LENGTH - ctx->sce_buf_len);

    aad_bit_size[0]  = change_endian_long((aad_len & 0xe000000U) >> 29U);
    aad_bit_size[1]  = change_endian_long(aad_len << 3U);
    data_bit_size[0] = change_endian_long((length & 0xe000000U) >> 29U);
    data_bit_size[1] = change_endian_long(length << 3U);

    if (mode == MBEDTLS_GCM_ENCRYPT)
    {
        err = g_sce_aes_gcm_encrypt_final[key_len_idx]((uint32_t *) ctx->buf, data_bit_size,
                                                       aad_bit_size, (uint32_t *) output,
                                                       (uint32_t *) tag);
    }
    else
    {
        uint32_t tag_bit_size[1] = {0};
        uint32_t padded_tag[4]   = {0};
        tag_bit_size[0] = change_endian_long(tag_len);
        memcpy(padded_tag, tag, tag_len);
        err = g_sce_aes_gcm_decrypt_final[key_len_idx]((uint32_t *) ctx->buf, data_bit_size,
                                                       aad_bit_size, (uint32_t *) padded_tag,
                                                       tag_bit_size, (uint32_t *) output);
    }

    *output_length   = ctx->sce_buf_len; /* the final partial block, emitted by Final */
    ctx->sce_buf_len = 0U;
    ctx->sce_stage   = SCE_MBEDTLS_GCM_OPERATION_STATE_IDLE;

    if (FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return 0;
}

/* Decrypt verify. Unlike finish(), the SCE DecryptFinal verifies the tag internally, so the
 * expected_tag is fed in here (the PSA verify wrapper provides it). Emits the final plaintext
 * partial block and returns with auth pass/fail. */
int sce_gcm_verify (mbedtls_gcm_context * ctx,
                    unsigned char       * output,
                    size_t                output_size,
                    size_t              * output_length,
                    const unsigned char * expected_tag,
                    size_t                tag_len)
{
    uint32_t  key_len_idx      = (uint32_t) RM_PSA_CRYPTO_AES_LOOKUP_INDEX(ctx->cipher_ctx.key_bitlen);
    int       mode             = (int) ctx->mode; /* MBEDTLS_GCM_DECRYPT */
    uint32_t  aad_bit_size[2]  = {0};
    uint32_t  data_bit_size[2] = {0};
    uint32_t  tag_bit_size[1]  = {0};
    uint32_t  padded_tag[4]    = {0};
    size_t    aad_len          = (size_t) ctx->add_len;
    size_t    length           = (size_t) ctx->len;
    fsp_err_t err;

    (void) output_size;

    if ((tag_len > 16) || (tag_len < 4))
    {
        return MBEDTLS_ERR_GCM_BAD_INPUT;
    }

    if (ctx->sce_stage == SCE_MBEDTLS_GCM_OPERATION_STATE_AAD)
    {
        sce_gcm_aad_to_text(ctx, key_len_idx, mode);
    }

    memset(ctx->buf + ctx->sce_buf_len, 0, MBEDTLS_MAX_BLOCK_LENGTH - ctx->sce_buf_len);

    aad_bit_size[0]  = change_endian_long((aad_len & 0xe000000U) >> 29U);
    aad_bit_size[1]  = change_endian_long(aad_len << 3U);
    data_bit_size[0] = change_endian_long((length & 0xe000000U) >> 29U);
    data_bit_size[1] = change_endian_long(length << 3U);
    tag_bit_size[0]  = change_endian_long(tag_len);
    memcpy(padded_tag, expected_tag, tag_len);

    err = g_sce_aes_gcm_decrypt_final[key_len_idx]((uint32_t *) ctx->buf, data_bit_size,
                                                   aad_bit_size, (uint32_t *) padded_tag,
                                                   tag_bit_size, (uint32_t *) output);

    *output_length   = ctx->sce_buf_len;
    ctx->sce_buf_len = 0U;
    ctx->sce_stage   = SCE_MBEDTLS_GCM_OPERATION_STATE_IDLE;

    if (FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_GCM_AUTH_FAILED;
    }

    return 0;
}

void sce_gcm_free_session (mbedtls_gcm_context * ctx)
{
    uint32_t key_len_idx = 0;
    int      mode;
    uint32_t aad_bit_size[2]  = {0};
    uint32_t data_bit_size[2] = {0};
    size_t   aad_len;
    size_t   length;
    uint8_t  dummy_out[MBEDTLS_MAX_BLOCK_LENGTH] = {0};
    uint32_t dummy_tag[4] = {0};

    /* Drain a still-open HW GCM session (e.g. psa_aead_abort before finish) so the SCE is
     * returned to idle for the next operation. No-op for an already-finished operation. */
    if ((ctx == NULL) || (ctx->sce_stage == SCE_MBEDTLS_GCM_OPERATION_STATE_IDLE))
    {
        return;
    }

    key_len_idx = (uint32_t) RM_PSA_CRYPTO_AES_LOOKUP_INDEX(ctx->cipher_ctx.key_bitlen);
    mode        = (int) ctx->mode;
    aad_len     = (size_t) ctx->add_len;
    length      = (size_t) ctx->len;

    if (ctx->sce_stage == SCE_MBEDTLS_GCM_OPERATION_STATE_AAD)
    {
        sce_gcm_aad_to_text(ctx, key_len_idx, mode);
    }

    memset(ctx->buf + ctx->sce_buf_len, 0, MBEDTLS_MAX_BLOCK_LENGTH - ctx->sce_buf_len);
    aad_bit_size[0]  = change_endian_long((aad_len & 0xe000000U) >> 29U);
    aad_bit_size[1]  = change_endian_long(aad_len << 3U);
    data_bit_size[0] = change_endian_long((length & 0xe000000U) >> 29U);
    data_bit_size[1] = change_endian_long(length << 3U);

    if (mode == MBEDTLS_GCM_ENCRYPT)
    {
        (void) g_sce_aes_gcm_encrypt_final[key_len_idx]((uint32_t *) ctx->buf, data_bit_size,
                                                        aad_bit_size, (uint32_t *) dummy_out,
                                                        (uint32_t *) dummy_tag);
    }
    else
    {
        uint32_t tag_bit_size[1] = {0};
        uint32_t padded_tag[4]   = {0};
        tag_bit_size[0] = change_endian_long(16U);
        (void) g_sce_aes_gcm_decrypt_final[key_len_idx]((uint32_t *) ctx->buf, data_bit_size,
                                                        aad_bit_size, (uint32_t *) padded_tag,
                                                        tag_bit_size, (uint32_t *) dummy_out);
    }

    ctx->sce_buf_len = 0U;
    ctx->sce_stage   = SCE_MBEDTLS_GCM_OPERATION_STATE_IDLE;
}

 #endif                                /* MBEDTLS_GCM_ALT */

#endif                                 /* MBEDTLS_GCM_C */
