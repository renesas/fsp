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

#include "common.h"

#if defined(MBEDTLS_RSA_C)

 #include "mbedtls/rsa.h"
 #include "mbedtls/oid.h"
 #include "mbedtls/platform_util.h"

 #include <string.h>

 #if defined(MBEDTLS_PKCS1_V21)
  #include "mbedtls/md.h"
 #endif

 #if defined(MBEDTLS_PKCS1_V15) && !defined(__OpenBSD__)
  #include <stdlib.h>
 #endif

 #if defined(MBEDTLS_PLATFORM_C)
  #include "mbedtls/platform.h"
  #include "mbedtls/error.h"
 #else
  #include <stdio.h>
  #define mbedtls_printf    printf
  #define mbedtls_calloc    calloc
  #define mbedtls_free      free
 #endif

 #if defined(MBEDTLS_RSA_ALT)
  #include "hw_sce_rsa_private.h"
  #include "hw_sce_ra_private.h"
  #include "hw_sce_private.h"

  #define RM_PSA_CRYPTO_RSA_KEY_PLAINTEXT    (0U)
  #define RM_PSA_CRYPTO_RSA_KEY_WRAPPED      (1U)
  #define RM_PSA_CRYPTO_DUMMY_KEY_BYTES      (20U)

  #if BSP_FEATURE_CRYPTO_HAS_SCE7
fsp_err_t HW_SCE_Rsa3072ModularExponentEncryptSub (const uint32_t * InData_KeyIndex,
                                                   const uint32_t * InData_Text,
                                                   uint32_t       * OutData_Text)
{
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);

    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Rsa4096ModularExponentEncryptSub (const uint32_t * InData_KeyIndex,
                                                   const uint32_t * InData_Text,
                                                   uint32_t       * OutData_Text)
{
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);

    return FSP_ERR_UNSUPPORTED;
}

  #endif

fsp_err_t HW_SCE_HRK_RSA_2048KeyGenerate(uint32_t   num_tries,
                                         uint32_t * OutData_KeyIndex,
                                         uint32_t * OutData_N,
                                         uint32_t * OutData_DomainParam);

fsp_err_t HW_SCE_HRK_RSA_2048KeyGenerate (uint32_t   num_tries,
                                          uint32_t * OutData_KeyIndex,
                                          uint32_t * OutData_N,
                                          uint32_t * OutData_DomainParam)

{
    sce_rsa2048_key_pair_index_t key_pair_index = {0};
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  local_dummy[RM_PSA_CRYPTO_DUMMY_KEY_BYTES / 4U];
    uint32_t  indata_key_type = 0;

    /* P.Q are the prime 1 and 2 fields that are in some cases generated when the private key is generated.
     * This was the case with W1D; but this information is not provided on the RA6M4.
     * There is no functional issue since the procedures do not require it for operation,
     * however mbedCrypto requires these fields to be non-zero in order for the private key_export to work.
     * These dummy values are placed into those fields to get past the non-zero check. */
    uint8_t dummy_P_Q[24] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};

    err =
        HW_SCE_GenerateRsa2048RandomKeyIndexSub(num_tries,
                                                &indata_key_type,
                                                (uint32_t *) &key_pair_index.pub_key.value,
                                                local_dummy,
                                                (uint32_t *) &key_pair_index.priv_key.value,
                                                local_dummy);

    if (FSP_SUCCESS == err)
    {
        memcpy(OutData_KeyIndex, &key_pair_index.priv_key.value, sizeof(key_pair_index.priv_key.value));
        memcpy(OutData_N, &key_pair_index.pub_key.value.key_n, sizeof(key_pair_index.pub_key.value.key_n));
        memcpy((uint8_t *) OutData_DomainParam, dummy_P_Q, sizeof(dummy_P_Q));
    }

    return err;
}

fsp_err_t HW_SCE_RSA_2048PrivateKeyDecrypt (const uint32_t * InData_Text,
                                            const uint32_t * InData_PrivateKey,
                                            const uint32_t * InData_N,
                                            uint32_t       * OutData_Text)

{
    FSP_PARAMETER_NOT_USED(InData_PrivateKey);
    fsp_err_t err = FSP_SUCCESS;

    /* Create storage to hold the generated OEM key index */
    sce_rsa2048_private_key_index_t encrypted_rsa_key;

    /*This function requires the plaintext RSA key is provided in a single buffer in the order:
     * Public Key (N) of size RSA_MODULUS_SIZE_BYTES(x)
     * Private Key (D) of size private_key_size_bytes
     * The buffer in mbedtls_rsa_private() already contains the data in that format, so InData_N
     * is directly provided to this function.
     */
    err =
        HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN, SCE_OEM_CMD_RSA2048_PRIVATE, NULL, NULL,
                                          (const uint8_t *) InData_N, (uint32_t *) &encrypted_rsa_key.value);

    if (FSP_SUCCESS == err)
    {
        err = HW_SCE_Rsa2048ModularExponentDecryptSub((uint32_t *) &encrypted_rsa_key.value, InData_Text, OutData_Text);
    }

    return err;
}

fsp_err_t HW_SCE_HRK_RSA_2048PrivateKeyDecrypt (const uint32_t * InData_Text,
                                                const uint32_t * InData_KeyIndex,
                                                const uint32_t * InData_N,
                                                uint32_t       * OutData_Text)

{
    FSP_PARAMETER_NOT_USED(InData_N);

    fsp_err_t err = FSP_SUCCESS;

    err = HW_SCE_Rsa2048ModularExponentDecryptSub((uint32_t *) InData_KeyIndex, InData_Text, OutData_Text);

    return err;
}

fsp_err_t HW_SCE_RSA_2048KeyGenerate (uint32_t   num_tries,
                                      uint32_t * OutData_PrivateKey,
                                      uint32_t * OutData_N,
                                      uint32_t * OutData_DomainParam)

{
    sce_rsa2048_key_pair_index_t key_pair_index = {0};
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  local_dummy[RM_PSA_CRYPTO_DUMMY_KEY_BYTES / 4U];
    uint32_t  indata_key_type = SCE_OEM_KEY_TYPE_PLAIN;

    /* P.Q are the prime 1 and 2 fields that are in some cases generated when the private key is generated.
     * This was the case with W1D; but this information is not provided on the RA6M4.
     * There is no functional issue since the procedures do not require it for operation,
     * however mbedCrypto requires these fields to be non-zero in order for the private key_export to work.
     * These dummy values are placed into those fields to get past the non-zero check. */
    uint8_t dummy_P_Q[24] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};

    err =
        HW_SCE_GenerateRsa2048RandomKeyIndexSub(num_tries,
                                                &indata_key_type,
                                                local_dummy,
                                                (uint32_t *) &key_pair_index.pub_key.plain_value,
                                                local_dummy,
                                                (uint32_t *) &key_pair_index.priv_key.plain_value);

    if (FSP_SUCCESS == err)
    {
        memcpy(OutData_PrivateKey, &key_pair_index.priv_key.plain_value, sizeof(key_pair_index.priv_key.plain_value));
        memcpy(OutData_N, &key_pair_index.pub_key.plain_value, sizeof(key_pair_index.pub_key.value.key_n));
        memcpy((uint8_t *) OutData_DomainParam, dummy_P_Q, sizeof(dummy_P_Q));
    }

    return err;
}

static const hw_sce_rsa_generatekey_t g_rsa_keygen_lookup[2] =
{
  #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_RSA_FORMAT)
    [RM_PSA_CRYPTO_RSA_KEY_PLAINTEXT] =
        HW_SCE_RSA_2048KeyGenerate,
  #endif
  #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_RSA_FORMAT)
    [RM_PSA_CRYPTO_RSA_KEY_WRAPPED] =
        HW_SCE_HRK_RSA_2048KeyGenerate,
  #endif
};

static const hw_sce_rsa_private_decrypt_t g_rsa_private_decrypt_lookup[2] =
{
  #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_RSA_FORMAT)
    [RM_PSA_CRYPTO_RSA_KEY_PLAINTEXT] =
        HW_SCE_RSA_2048PrivateKeyDecrypt,
  #endif
  #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_RSA_FORMAT)
    [RM_PSA_CRYPTO_RSA_KEY_WRAPPED] =
        HW_SCE_HRK_RSA_2048PrivateKeyDecrypt,
  #endif
};

/* Parameter validation macros */
  #define RSA_VALIDATE_RET(cond) \
    MBEDTLS_INTERNAL_VALIDATE_RET(cond, MBEDTLS_ERR_RSA_BAD_INPUT_DATA)
  #define RSA_VALIDATE(cond) \
    MBEDTLS_INTERNAL_VALIDATE(cond)

  #if defined(MBEDTLS_GENPRIME)

/*
 * Generate an RSA keypair
 */
int mbedtls_rsa_gen_key (mbedtls_rsa_context * ctx,
                         int (* f_rng)(void *, unsigned char *, size_t),
                         void * p_rng,
                         unsigned int nbits,
                         int exponent)
{
    (void) nbits;
    (void) exponent;
    int ret = 0;
    RSA_VALIDATE_RET(ctx != NULL);
    (void) f_rng;
    (void) p_rng;

    uint8_t  * p_additional_key_info_8 = NULL;
    uint32_t * p_common_buff_32        = NULL;

    uint32_t private_key_size_bytes = RSA_MODULUS_SIZE_BYTES(2048);
    uint32_t public_key_size_bytes  = RSA_MODULUS_SIZE_BYTES(2048);
    FSP_PARAMETER_NOT_USED(private_key_size_bytes);

   #if defined(MBEDTLS_CHECK_PARAMS)

    /* HW can only generate public exponent of 65537 */
    if (exponent != RSA_PUBLIC_EXPONENT_BE)
    {
        return MBEDTLS_ERR_RSA_BAD_INPUT_DATA;
    }

    /* We only support RSA2048 now*/
    if (nbits != RSA_2048_BITS)
    {
        return MBEDTLS_ERR_RSA_BAD_INPUT_DATA;
    }
   #endif

    if (true == (bool) ctx->vendor_ctx)
    {
        private_key_size_bytes = RSA_WRAPPED_PRIVATE_KEY_SIZE_BYTES(2048);
    }

    /* Calloc pointers created to remove clang warnings */
    uint32_t * p_rsa_private_exponent = NULL;
    uint32_t * p_rsa_public_modulus   = NULL;
    uint32_t * p_additional_key_info  = NULL;

    hw_sce_rsa_generatekey_t p_hw_sce_rsa_generatekey = NULL;
    uint8_t rsa_public_exponent[4] = {0x00, 0x01, 0x00, 0x01};

    p_hw_sce_rsa_generatekey = g_rsa_keygen_lookup[(uint32_t) ctx->vendor_ctx];
    if (NULL == p_hw_sce_rsa_generatekey)
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    if (ret == 0)
    {
        /* Obtain a 32-bit aligned block of memory. It will be used for all the following items in this order:
         * Private Key D of size private_key_size_bytes
         * Public Modulus N of size public_key_size_bytes
         * Any additional info:
         *  With old procedures: CRT parameters Dq|Q|Dp|P|Qp each of size RSA_PARAMETERS_SIZE_BYTES(x)
         *  With new procedures: none. */
        p_common_buff_32 =
            (uint32_t *) mbedtls_calloc((private_key_size_bytes +
                                         (public_key_size_bytes + RSA_ADDITIONAL_KEY_INFO_SIZE_BYTES(2048))) / 4,
                                        sizeof(uint32_t));

        if (NULL == p_common_buff_32)
        {
            return MBEDTLS_ERR_MPI_ALLOC_FAILED;
        }

        p_rsa_private_exponent  = p_common_buff_32;
        p_rsa_public_modulus    = p_rsa_private_exponent + (private_key_size_bytes / 4);
        p_additional_key_info   = p_rsa_public_modulus + (public_key_size_bytes / 4);
        p_additional_key_info_8 = (uint8_t *) p_additional_key_info;

        if (FSP_SUCCESS !=
            p_hw_sce_rsa_generatekey(SCE_RSA_NUM_TRIES_20480, p_rsa_private_exponent, p_rsa_public_modulus,
                                     p_additional_key_info))
        {
            ret = MBEDTLS_ERR_RSA_KEY_GEN_FAILED;
        }
        /* Copy the public key data into the context */

        else if (0 !=
                 mbedtls_mpi_read_binary(&ctx->N, (uint8_t *) p_rsa_public_modulus, public_key_size_bytes))

        {
            ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
        }
        /* Copy the public exponent into the context */
        else if (0 !=
                 mbedtls_mpi_read_binary(&ctx->E, (unsigned char *) &rsa_public_exponent, 4))
        {
            ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
        }
        /* Copy the private key into the context */
        else if (0 !=
                 mbedtls_mpi_read_binary(&ctx->D, (uint8_t *) p_rsa_private_exponent, private_key_size_bytes))
        {
            ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
        }
        /* With old procedures:
         * The generated domain parameters are in the format:
         * d mod (q-1) || q || d mod (p-1) || p || (1/q) mod p
         * Import these elements into the mbedtls_rsa_context structure
         * We are not using CRT so d mode (q-1), d mode (p-1) and (1/q) mod p are ignored
         * With new procedures:
         *  These values are not generated by HW and are reading other data from the
         *  generated buffer. This can be removed entirely later, but will require updating
         *  ARM code to ignore these fields.
         * */
        else if (0 !=
                 mbedtls_mpi_read_binary(&ctx->Q, p_additional_key_info_8, RSA_PARAMETERS_SIZE_BYTES(2048)))
        {
            ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
        }
        else if (0 !=
                 mbedtls_mpi_read_binary(&ctx->P, p_additional_key_info_8, RSA_PARAMETERS_SIZE_BYTES(2048)))
        {
            ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
        }
        else
        {
            ret = 0;
        }

        /* Clear out the allocated buffer memory */
        memset(p_common_buff_32,
               0,
               (private_key_size_bytes +
                (public_key_size_bytes + RSA_ADDITIONAL_KEY_INFO_SIZE_BYTES(2048))));

        /* Free the allocated memory */
        mbedtls_free(p_common_buff_32);

        ctx->len = mbedtls_mpi_size(&ctx->N);

        if (ret != 0)
        {
            mbedtls_rsa_free(ctx);
        }
    }

    return ret;
}

  #endif                               /* MBEDTLS_GENPRIME */

fsp_err_t HW_SCE_RSA_4096PublicKeyEncrypt (const uint32_t * InData_Text,
                                           const uint32_t * InData_PublicKey,
                                           const uint32_t * InData_N,
                                           uint32_t       * OutData_Text)

{
    fsp_err_t err = FSP_SUCCESS;

    /* Create storage to hold the generated OEM key index */
    sce_rsa4096_public_key_index_t formatted_rsa_public_key_output;
    uint8_t formatted_rsa_public_key_input[HW_SCE_RSA4096_NE_KEY_BYTE_SIZE] = {0};
    memcpy(&formatted_rsa_public_key_input[0], InData_N, HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE);
    memcpy(&formatted_rsa_public_key_input[HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE],
           InData_PublicKey,
           HW_SCE_RSA_4096_KEY_E_LENGTH_BYTE_SIZE);

    err =
        HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                          SCE_OEM_CMD_RSA4096_PUBLIC,
                                          NULL,
                                          NULL,
                                          (const uint8_t *) &formatted_rsa_public_key_input,
                                          (uint32_t *) &formatted_rsa_public_key_output.value);

    if (FSP_SUCCESS == err)
    {
        err = HW_SCE_Rsa4096ModularExponentEncryptSub((uint32_t *) &formatted_rsa_public_key_output.value,
                                                      InData_Text,
                                                      OutData_Text);
    }

    return err;
}

fsp_err_t HW_SCE_RSA_3072PublicKeyEncrypt (const uint32_t * InData_Text,
                                           const uint32_t * InData_PublicKey,
                                           const uint32_t * InData_N,
                                           uint32_t       * OutData_Text)

{
    fsp_err_t err = FSP_SUCCESS;

    /* Create storage to hold the generated OEM key index */
    sce_rsa3072_public_key_index_t formatted_rsa_public_key_output;
    uint8_t formatted_rsa_public_key_input[HW_SCE_RSA3072_NE_KEY_BYTE_SIZE] = {0};
    memcpy(&formatted_rsa_public_key_input[0], InData_N, HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE);
    memcpy(&formatted_rsa_public_key_input[HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE],
           InData_PublicKey,
           HW_SCE_RSA_3072_KEY_E_LENGTH_BYTE_SIZE);

    err =
        HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                          SCE_OEM_CMD_RSA3072_PUBLIC,
                                          NULL,
                                          NULL,
                                          (const uint8_t *) &formatted_rsa_public_key_input,
                                          (uint32_t *) &formatted_rsa_public_key_output.value);

    if (FSP_SUCCESS == err)
    {
        err = HW_SCE_Rsa3072ModularExponentEncryptSub((uint32_t *) &formatted_rsa_public_key_output.value,
                                                      InData_Text,
                                                      OutData_Text);
    }

    return err;
}

fsp_err_t HW_SCE_RSA_2048PublicKeyEncrypt (const uint32_t * InData_Text,
                                           const uint32_t * InData_PublicKey,
                                           const uint32_t * InData_N,
                                           uint32_t       * OutData_Text)

{
    fsp_err_t err = FSP_SUCCESS;

    /* Create storage to hold the generated OEM key index */
    sce_rsa2048_public_key_index_t formatted_rsa_public_key_output;
    uint8_t formatted_rsa_public_key_input[HW_SCE_RSA2048_NE_KEY_BYTE_SIZE] = {0};
    memcpy(&formatted_rsa_public_key_input[0], InData_N, HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE);
    memcpy(&formatted_rsa_public_key_input[HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE],
           InData_PublicKey,
           HW_SCE_RSA_2048_KEY_E_LENGTH_BYTE_SIZE);

    err =
        HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                          SCE_OEM_CMD_RSA2048_PUBLIC,
                                          NULL,
                                          NULL,
                                          (const uint8_t *) &formatted_rsa_public_key_input,
                                          (uint32_t *) &formatted_rsa_public_key_output.value);

    if (FSP_SUCCESS == err)
    {
        err = HW_SCE_Rsa2048ModularExponentEncryptSub((uint32_t *) &formatted_rsa_public_key_output.value,
                                                      InData_Text,
                                                      OutData_Text);
    }

    return err;
}

/*
 * Do an RSA public key operation
 */
volatile mbedtls_rsa_context * rsa_temp_ctx;
int mbedtls_rsa_public (mbedtls_rsa_context * ctx, const unsigned char * input, unsigned char * output)
{
    uint32_t  temp_E = 0U;
    fsp_err_t iret;
    uint32_t  public_key_size_bytes = ctx->len;

    hw_sce_rsa_public_encrypt_t p_hw_sce_rsa_public_encrypt;

    // TODO: temporary implementation.
    if (ctx->len == RSA_MODULUS_SIZE_BYTES(RSA_2048_BITS))
    {
        p_hw_sce_rsa_public_encrypt = HW_SCE_RSA_2048PublicKeyEncrypt;
    }

  #if BSP_FEATURE_CRYPTO_HAS_SCE9
   #if RM_PSA_CRYPTO_CFG_RSA3K_ENABLED
    else if (ctx->len == RSA_MODULUS_SIZE_BYTES(RSA_3072_BITS))
    {
        p_hw_sce_rsa_public_encrypt = HW_SCE_RSA_3072PublicKeyEncrypt;
    }
   #endif
   #if RM_PSA_CRYPTO_CFG_RSA4K_ENABLED
    else if (ctx->len == RSA_MODULUS_SIZE_BYTES(RSA_4096_BITS))
    {
        p_hw_sce_rsa_public_encrypt = HW_SCE_RSA_4096PublicKeyEncrypt;
    }
   #endif
  #endif
    else
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    rsa_temp_ctx = ctx;

    /* Calloc pointer created to remove clang warnings */
    uint32_t * p_calloc_temp_buff_N = NULL;

    /* If the size of N is not equal to the modulus size, then that is because of the leading 00 (sign field) from the ASN1 import
     * Use openssl asn1parse -in private1.pem (in !test folder) to see asn1 format of key */
    if (ctx->N.n != (ctx->len / (sizeof(mbedtls_mpi_uint))))
    {
        /* There should be only 1 extra value (00) at the beginning; otherwise the key is in an unexpected format */
        if ((ctx->N.n - 1) != (ctx->len / (sizeof(mbedtls_mpi_uint))))
        {
            return MBEDTLS_ERR_RSA_BAD_INPUT_DATA;
        }
    }

    /* Reverse byte order for E */
    temp_E = __REV(*ctx->E.p);

    /* Obtain a 32-bit aligned block of memory to pass key data to the SCE */
    p_calloc_temp_buff_N = (uint32_t *) mbedtls_calloc(public_key_size_bytes / 4, sizeof(uint32_t));
    if (p_calloc_temp_buff_N == NULL)
    {
        return MBEDTLS_ERR_MPI_ALLOC_FAILED;;
    }

    /* Write N into the buffer in reverse */
    mbedtls_mpi_write_binary(&ctx->N, (uint8_t *) p_calloc_temp_buff_N, public_key_size_bytes);

    iret = FSP_ERR_CRYPTO_CONTINUE;
    for ( ; FSP_ERR_CRYPTO_CONTINUE == iret; )
    {
        iret = p_hw_sce_rsa_public_encrypt((uint32_t *) input, &temp_E, p_calloc_temp_buff_N, (uint32_t *) output);
    }

    /* Free the allocated buffer */
    mbedtls_free(p_calloc_temp_buff_N);
    if (0 != iret)
    {
        return MBEDTLS_ERR_RSA_PUBLIC_FAILED;
    }

    return 0;
}

/*
 * Do an RSA private key operation
 */

int mbedtls_rsa_private (mbedtls_rsa_context * ctx,
                         int (* f_rng)(void *, unsigned char *, size_t),
                         void * p_rng,
                         const unsigned char * input,
                         unsigned char * output)
{
    (void) f_rng;
    (void) p_rng;
    fsp_err_t err;
    int       ret = 0;
    uint32_t  private_key_size_bytes = ctx->len;
    hw_sce_rsa_private_decrypt_t p_hw_sce_rsa_private_decrypt = NULL;

    if (true == (bool) ctx->vendor_ctx)
    {
        private_key_size_bytes = RSA_WRAPPED_PRIVATE_KEY_SIZE_BYTES(ctx->len * 8U);
    }

    /* Calloc 32-bit pointer created to remove clang warnings */
    uint32_t * p_calloc_temp_buff_N = NULL;
    uint32_t * p_calloc_temp_buff_D = NULL;
    uint32_t * p_common_buff_32     = NULL;

    RSA_VALIDATE_RET(ctx != NULL);
    RSA_VALIDATE_RET(input != NULL);
    RSA_VALIDATE_RET(output != NULL);

    /* If the size of N is not equal to the modulus size, then that is because of the leading 00 (sign field) from the ASN1 import
     * Use openssl asn1parse -in private1.pem to see asn1 format of a .pem key */
    if (ctx->N.n != (ctx->len / (sizeof(mbedtls_mpi_uint))))
    {
        /* There should be only 1 extra value (00) at the beginning; otherwise the key is in an unexpected format */
        if ((ctx->N.n - 1) != (ctx->len / (sizeof(mbedtls_mpi_uint))))
        {
            return MBEDTLS_ERR_RSA_BAD_INPUT_DATA;
        }
    }

    p_hw_sce_rsa_private_decrypt = g_rsa_private_decrypt_lookup[(bool) ctx->vendor_ctx];
    if (NULL == p_hw_sce_rsa_private_decrypt)
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    /* Obtain a common 32-bit aligned buffer. It will be used for all the following items in this order:
     * Public Key (N) of size RSA_MODULUS_SIZE_BYTES(x)
     * Private Key (D) of size private_key_size_bytes
     */
    p_common_buff_32 = mbedtls_calloc(((ctx->len + private_key_size_bytes) / 4), sizeof(uint32_t));

    if (NULL == p_common_buff_32)
    {
        return MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }

    p_calloc_temp_buff_N = p_common_buff_32;
    p_calloc_temp_buff_D = p_calloc_temp_buff_N + (ctx->len / 4);

    /* Write N into the buffer in reverse */
    if (0 != mbedtls_mpi_write_binary(&ctx->N, (uint8_t *) p_calloc_temp_buff_N, ctx->len))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    /* Write D into the buffer in reverse */
    else if (0 != mbedtls_mpi_write_binary(&ctx->D, (uint8_t *) p_calloc_temp_buff_D, private_key_size_bytes))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    else
    {
        err = FSP_ERR_CRYPTO_CONTINUE;
        for ( ; FSP_ERR_CRYPTO_CONTINUE == err; )
        {
            err =
                p_hw_sce_rsa_private_decrypt((uint32_t *) input,
                                             p_calloc_temp_buff_D,
                                             p_calloc_temp_buff_N,
                                             (uint32_t *) output);
        }

        if (err != 0)
        {
            ret = MBEDTLS_ERR_RSA_PRIVATE_FAILED;
        }
    }

    /* Clear out the allocated buffer memory */
    memset(p_common_buff_32, 0, ((RSA_MODULUS_SIZE_BYTES(2048) + private_key_size_bytes)));
    mbedtls_free(p_common_buff_32);

    return ret;
}

 #endif                                /* !MBEDTLS_RSA_ALT */

#endif                                 /* MBEDTLS_RSA_C */
