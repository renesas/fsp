/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "common.h"

#if defined(MBEDTLS_CCM_C)

 #include "mbedtls/ccm.h"
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

 #if defined(MBEDTLS_CCM_ALT)
  #include "hw_sce_private.h"
  #include "hw_sce_aes_private.h"
  #include "hw_sce_ra_private.h"
  #include "aes_alt.h"
  #include "platform_alt.h"

  #define SCE9_AES_CCM_KEY_TYPE_GENERAL    (0)
  #define ROUNDOFF_TO_BLOCK_SIZE(BLOCK_SIZE, DATA_SIZE)    (BLOCK_SIZE * ((DATA_SIZE + (BLOCK_SIZE - 1)) / BLOCK_SIZE))

/* AES-CCM Encryption Init HW call table based on key size */
static const hw_sce_aes_ccm_encrypt_init_t g_sce_aes_ccm_encrypt_init[] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)] =
        HW_SCE_Aes128CcmEncryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)] =
        HW_SCE_Aes192CcmEncryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)] =
        HW_SCE_Aes256CcmEncryptInitSubGeneral,
};

/* AES-CCM Decryption Init HW call table based on key size */
static const hw_sce_aes_ccm_decrypt_init_t g_sce_aes_ccm_decrypt_init[] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)] =
        HW_SCE_Aes128CcmDecryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)] =
        HW_SCE_Aes192CcmDecryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)] =
        HW_SCE_Aes256CcmDecryptInitSubGeneral,
};

/* AES-CCM Encryption/Decryption Update HW call table based on key size */
static const hw_sce_aes_ccm_crypt_update_t g_sce_aes_ccm_crypt_update[][2U] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_CCM_ENCRYPT] =
        HW_SCE_Aes128CcmEncryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_CCM_DECRYPT] =
        HW_SCE_Aes128CcmDecryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_CCM_ENCRYPT] =
        HW_SCE_Aes192CcmEncryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_CCM_DECRYPT] =
        HW_SCE_Aes192CcmDecryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_CCM_ENCRYPT] =
        HW_SCE_Aes256CcmEncryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_CCM_DECRYPT] =
        HW_SCE_Aes256CcmDecryptUpdateSub,
};

/* AES-CCM Encryption Final HW call table based on key size */
static const hw_sce_aes_ccm_encrypt_final_t g_sce_aes_ccm_encrypt_final[] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)] =
        HW_SCE_Aes128CcmEncryptFinalSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)] =
        HW_SCE_Aes192CcmEncryptFinalSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)] =
        HW_SCE_Aes256CcmEncryptFinalSub,
};

/* AES-CCM Decryption Final HW call table based on key size */
static const hw_sce_aes_ccm_decrypt_final_t g_sce_aes_ccm_decrypt_final[] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)] =
        HW_SCE_Aes128CcmDecryptFinalSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)] =
        HW_SCE_Aes192CcmDecryptFinalSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)] =
        HW_SCE_Aes256CcmDecryptFinalSub,
};

static int ccm_counter_block_format (mbedtls_ccm_context * ctx,
                                     const unsigned char * iv,
                                     size_t                iv_len,
                                     uint8_t             * b_format_buffer)
{
    /* Ensure iv length is within bounds */
    if ((iv_len < 7) || (iv_len > 13))
    {
        return MBEDTLS_ERR_CCM_BAD_INPUT;
    }

    /* Counter block formatting. */

    /*
     * Prepare counter block for encryption:
     * 0        .. 0        flags
     * 1        .. iv_len   nonce (aka iv)
     * iv_len+1 .. 15       counter
     *
     * With flags as (bits):
     * 7 .. 3   0
     * 2 .. 0   q - 1
     */
    ctx->q = 16 - 1 - (unsigned char) iv_len;

    memset(ctx->ctr, 0, 16);
    ctx->ctr[0] = ctx->q - 1;
    memcpy(ctx->ctr + 1, iv, iv_len);
    memset(ctx->ctr + 1 + iv_len, 0, ctx->q);

    memcpy(&b_format_buffer[1], iv, iv_len);

    return 0;
}

static int ccm_authetication_block_format (mbedtls_ccm_context * ctx,
                                           const unsigned char * aad,
                                           size_t                aad_len,
                                           size_t                plaintext_len,
                                           size_t                tag_len,
                                           uint8_t             * b_format_buffer,
                                           uint32_t            * format_buffer_length)
{
    size_t          len_left = 0;
    unsigned char   i;
    volatile size_t header_size          = 0;
    size_t          header_data_expected = 0;

    /*
     * Check length requirements: SP800-38C A.1
     * Additional requirement: a < 2^16 - 2^8 to simplify the code.
     * 'length' checked later (when writing it to the first block)
     *
     * Also, loosen the requirements to enable support for CCM* (IEEE 802.15.4).
     */
    if ((tag_len == 2) || (tag_len > 16) || (tag_len % 2 != 0))
    {
        return MBEDTLS_ERR_CCM_BAD_INPUT;
    }

    /* MbedTLS supports aad length which is less than 0xFF00, but is further limited by the size
     * of the hardware buffer that is used to hold the header data.
     * As per the SP800-38C document, the encoded size of aad and the aad data is placed from the
     * 2nd block (i.e, B1, B2, etc).
     *
     * B0                Initial block with FLAG, Nonce and Payload length.
     * B1                (2 bytes for encoded aad length + aad data)
     *                   aad data is added to further blocks and rounded
     *                   off to block size with zero padding, if required.
     */
    header_data_expected += HW_SCE_AES_BLOCK_BYTE_SIZE;
    header_data_expected += ROUNDOFF_TO_BLOCK_SIZE(HW_SCE_AES_BLOCK_BYTE_SIZE, (2U + aad_len));

    if (header_data_expected > HW_SCE_AES_CCM_B_FORMAT_BYTE_SIZE)
    {
        return MBEDTLS_ERR_CCM_BAD_INPUT;
    }

    ctx->plaintext_len = plaintext_len;
    ctx->add_len       = aad_len;
    ctx->tag_len       = tag_len;

    *b_format_buffer |= (ctx->add_len > 0) << 6;
    *b_format_buffer |= ((ctx->tag_len - 2) / 2) << 3;
    *b_format_buffer |= ctx->q - 1;

    for (i = 0, len_left = ctx->plaintext_len; i < ctx->q; i++, len_left >>= 8)
    {
        b_format_buffer[15 - i] = MBEDTLS_BYTE_0(len_left);
    }

    if (len_left > 0)
    {
        return MBEDTLS_ERR_CCM_BAD_INPUT;
    }

    header_size += HW_SCE_AES_BLOCK_BYTE_SIZE;

    if (ctx->add_len > 0U)
    {
        b_format_buffer[header_size] = (unsigned char) ((ctx->add_len >> 8) & 0xFF);
        header_size++;
        b_format_buffer[header_size] = (unsigned char) ((ctx->add_len) & 0xFF);

        header_size++;
        memcpy(&b_format_buffer[header_size], aad, aad_len);
        header_size += aad_len;
        header_size  = ROUNDOFF_TO_BLOCK_SIZE(HW_SCE_AES_BLOCK_BYTE_SIZE, header_size);
    }

    /* Header size to be specified in words. */
    *format_buffer_length = header_size >> 2;

    return 0;
}

/* AES-CCM operation using SCE9 HW procedures */
int sce_ccm_crypt_and_tag (mbedtls_ccm_context * ctx,
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
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

    uint32_t              key_len_idx         = RM_PSA_CRYPTO_AES_LOOKUP_INDEX(ctx->cipher_ctx.key_bitlen);
    mbedtls_aes_context * aes_ctx             = (mbedtls_aes_context *) ctx->cipher_ctx.cipher_ctx;
    fsp_err_t             err                 = FSP_SUCCESS;
    uint32_t              key_type[1]         = {SCE9_AES_CCM_KEY_TYPE_GENERAL};
    uint32_t              indata_cmd[1]       = {0};
    uint32_t              indata_type[1]      = {0};
    uint32_t              indata_textlen[1]   = {0};
    uint32_t              indata_maclength[1] = {0};
    uint32_t              indata_seqnum[1]    = {0};
    uint32_t              header_length       = 0;
    uint32_t              input_length        = 0;
    uint32_t              offset_length       = 0;
    uint8_t               work_buffer[HW_SCE_AES_CCM_B_FORMAT_BYTE_SIZE] = {0};
    uint8_t               mac_buff[HW_SCE_MAC_SIZE] = {0};

    indata_textlen[0]   = change_endian_long(length);
    indata_maclength[0] = change_endian_long(tag_len);

    memset(work_buffer, 0, HW_SCE_AES_CCM_B_FORMAT_BYTE_SIZE);

    /* CCM expects non-empty tag.
     * CCM* allows empty tag. For CCM* without tag, ignore plaintext length.
     */
    if (tag_len == 0)
    {
        if ((mode == MBEDTLS_CCM_STAR_ENCRYPT) || (mode == MBEDTLS_CCM_STAR_DECRYPT))
        {
            length = 0;
        }
        else
        {
            return MBEDTLS_ERR_CCM_BAD_INPUT;
        }
    }

    if ((ret = ccm_counter_block_format(ctx, iv, iv_len, work_buffer)) != 0)
    {
        return ret;
    }

    if ((ret = ccm_authetication_block_format(ctx, aad, aad_len, length, tag_len, work_buffer, &header_length)) != 0U)
    {
        return ret;
    }

    if (MBEDTLS_CCM_ENCRYPT == mode)
    {
        err = g_sce_aes_ccm_encrypt_init[key_len_idx](key_type, indata_type, indata_cmd, indata_textlen,
                                                      (uint32_t *) (aes_ctx->buf), (uint32_t *) &ctx->ctr[0],
                                                      (uint32_t *) work_buffer, indata_seqnum,
                                                      header_length);
    }
    else
    {
        err = g_sce_aes_ccm_decrypt_init[key_len_idx](key_type, indata_type, indata_cmd, indata_textlen,
                                                      (uint32_t *) indata_maclength, (uint32_t *) (aes_ctx->buf),
                                                      (uint32_t *) &ctx->ctr[0], (uint32_t *) work_buffer,
                                                      indata_seqnum, header_length);
    }

    offset_length = length % MBEDTLS_MAX_BLOCK_LENGTH;
    input_length  = length - offset_length;

    if (input_length)
    {
        g_sce_aes_ccm_crypt_update[key_len_idx][mode]((uint32_t *) input,
                                                      (uint32_t *) output,
                                                      BYTES_TO_WORDS(input_length));
    }

    memset(work_buffer, 0, HW_SCE_AES_CCM_B_FORMAT_BYTE_SIZE);
    if (0 != offset_length)
    {
        memcpy(work_buffer, &input[input_length], offset_length);
    }

    if (MBEDTLS_CCM_ENCRYPT == mode)
    {
        memset(mac_buff, 0, HW_SCE_MAC_SIZE);
        err = g_sce_aes_ccm_encrypt_final[key_len_idx]((uint32_t *) work_buffer, indata_textlen,
                                                       (uint32_t *) &output[input_length], (uint32_t *) mac_buff);
        memcpy(tag, mac_buff, tag_len);
    }
    else
    {
        memset(mac_buff, 0, HW_SCE_MAC_SIZE);
        memcpy(mac_buff, tag, tag_len);
        err = g_sce_aes_ccm_decrypt_final[key_len_idx]((uint32_t *) work_buffer, indata_textlen,
                                                       (uint32_t *) mac_buff, (uint32_t *) indata_maclength,
                                                       (uint32_t *) &output[input_length]);
    }

    if (FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_CCM_AUTH_FAILED;
    }

    return ret;
}

 #endif                                /* !MBEDTLS_CCM_ALT */

#endif                                 /* MBEDTLS_CCM_C */
