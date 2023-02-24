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

/***********************************************************************************************************************
 * File Name    : nx_crypto_rsa_alt_process.c
 * Description  : Functions interfacing with SCE
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_netx_secure_crypto_cfg.h"
#if ((1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_RSA_2048_ALT) || \
    (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_RSA_3072_ALT) ||  \
    (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_RSA_4096_ALT))
 #include "nx_crypto_rsa.h"
 #include "hw_sce_private.h"
 #include "hw_sce_ra_private.h"
 #include "hw_sce_rsa_private.h"
 #include "rm_netx_secure_crypto.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #define RM_NETX_SECURE_CRYPTO_RSA_EXPONENT_LENGTH_BYTES    (4U)

/*******************************************************************************************************************//**
 * @addtogroup RM_NETX_SECURE_CRYPTO
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * RSA Operation - Encryption/Decryption
 * This function performs an RSA encryption/decryption operation based on the exponent length input (public/private key).
 * Wrapped or plain private key can be provided.
 * Unformatted/standard public key must be provided.
 * @retval NX_CRYPTO_SUCCESS              Encryption/decryption operation was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       Encryption/decryption operation failed.
 * @retval NX_CRYPTO_UNSUPPORTED_KEY_SIZE Unsupported key size based on the exponent length passed.
 * @retval NX_CRYPTO_SIZE_ERROR           Invalid modulus length.
 **********************************************************************************************************************/
UINT sce_nx_crypto_rsa_operation (const UCHAR * exponent,
                                  UINT          exponent_length,
                                  const UCHAR * modulus,
                                  UINT          modulus_length,
                                  const UCHAR * input,
                                  UINT          input_length,
                                  UCHAR       * output)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Check exponent length to determine key type and format */
    if (exponent_length <= RM_NETX_SECURE_CRYPTO_RSA_EXPONENT_LENGTH_BYTES)
    {
        UINT modulus_size_max = 0;
 #if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_RSA_4096_ALT)
        uint32_t aligned_modulus[HW_SCE_RSA_4096_KEY_D_LENGTH_BYTE_SIZE / sizeof(uint32_t)] = {0};
        modulus_size_max = (UINT) HW_SCE_RSA_4096_KEY_D_LENGTH_BYTE_SIZE;
 #elif (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_RSA_3072_ALT)
        uint32_t aligned_modulus[HW_SCE_RSA_3072_KEY_D_LENGTH_BYTE_SIZE / sizeof(uint32_t)] = {0};
        modulus_size_max = (UINT) HW_SCE_RSA_3072_KEY_D_LENGTH_BYTE_SIZE;
 #else
        uint32_t aligned_modulus[HW_SCE_RSA_2048_KEY_D_LENGTH_BYTE_SIZE / sizeof(uint32_t)] = {0};
        modulus_size_max = (UINT) HW_SCE_RSA_2048_KEY_D_LENGTH_BYTE_SIZE;
 #endif
        FSP_ERROR_RETURN((modulus_size_max >= modulus_length), NX_CRYPTO_SIZE_ERROR);
        NX_CRYPTO_MEMCPY(aligned_modulus, modulus, modulus_length);

        /* Unformatted public key : This is an Encryption operation */
        uint8_t padded_exponent[4U] = {0};
        NX_CRYPTO_MEMCPY(&padded_exponent[RM_NETX_SECURE_CRYPTO_RSA_EXPONENT_LENGTH_BYTES - exponent_length],
                         exponent,
                         exponent_length);

        /* Check for modulus size to determine RSA size */
        switch (modulus_length)
        {
            case HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE:
            {
 #if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_RSA_4096_ALT)
                uint32_t aligned_work_buffer[HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE / sizeof(uint32_t)] = {0};
                NX_CRYPTO_MEMCPY(aligned_work_buffer, input, sizeof(aligned_work_buffer));

                /* Create storage to hold the generated OEM key index */
                sce_rsa4096_public_key_index_t formatted_rsa_public_key_output;
                uint8_t formatted_rsa_public_key_input[HW_SCE_RSA4096_NE_KEY_BYTE_SIZE] = {0};
                NX_CRYPTO_MEMCPY(&formatted_rsa_public_key_input[0],
                                 (uint32_t *) aligned_modulus,
                                 HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE);
                NX_CRYPTO_MEMCPY(&formatted_rsa_public_key_input[HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE],
                                 (uint32_t *) padded_exponent,
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
                    err =
                        HW_SCE_Rsa4096ModularExponentEncryptSub((uint32_t *) &formatted_rsa_public_key_output.value,
                                                                (uint32_t *) aligned_work_buffer,
                                                                (uint32_t *) aligned_work_buffer);
                }
                NX_CRYPTO_MEMCPY(output, aligned_work_buffer, sizeof(aligned_work_buffer));
 #endif
                break;
            }

            case HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE:
            {
 #if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_RSA_3072_ALT)
                uint32_t aligned_work_buffer[HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE / sizeof(uint32_t)] = {0};
                NX_CRYPTO_MEMCPY(aligned_work_buffer, input, sizeof(aligned_work_buffer));

                /* Create storage to hold the generated OEM key index */
                sce_rsa3072_public_key_index_t formatted_rsa_public_key_output;
                uint8_t formatted_rsa_public_key_input[HW_SCE_RSA3072_NE_KEY_BYTE_SIZE] = {0};
                NX_CRYPTO_MEMCPY(&formatted_rsa_public_key_input[0],
                                 (uint32_t *) aligned_modulus,
                                 HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE);
                NX_CRYPTO_MEMCPY(&formatted_rsa_public_key_input[HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE],
                                 (uint32_t *) padded_exponent,
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
                    err =
                        HW_SCE_Rsa3072ModularExponentEncryptSub((uint32_t *) &formatted_rsa_public_key_output.value,
                                                                (uint32_t *) aligned_work_buffer,
                                                                (uint32_t *) aligned_work_buffer);
                }
                NX_CRYPTO_MEMCPY(output, aligned_work_buffer, sizeof(aligned_work_buffer));
 #endif
                break;
            }

            case HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE:
            {
 #if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_RSA_2048_ALT)
                uint32_t aligned_work_buffer[HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE / sizeof(uint32_t)] = {0};
                NX_CRYPTO_MEMCPY(aligned_work_buffer, input, sizeof(aligned_work_buffer));

                /* Create storage to hold the generated OEM key index */
                sce_rsa2048_public_key_index_t formatted_rsa_public_key_output;
                uint8_t formatted_rsa_public_key_input[HW_SCE_RSA2048_NE_KEY_BYTE_SIZE] = {0};
                NX_CRYPTO_MEMCPY(&formatted_rsa_public_key_input[0],
                                 aligned_modulus,
                                 HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE);
                NX_CRYPTO_MEMCPY(&formatted_rsa_public_key_input[HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE],
                                 (uint32_t *) padded_exponent,
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
                    err =
                        HW_SCE_Rsa2048ModularExponentEncryptSub((uint32_t *) &formatted_rsa_public_key_output.value,
                                                                (uint32_t *) aligned_work_buffer,
                                                                (uint32_t *) aligned_work_buffer);
                }
                NX_CRYPTO_MEMCPY(output, aligned_work_buffer, sizeof(aligned_work_buffer));
 #endif
                break;
            }

            default:
            {
                return NX_CRYPTO_UNSUPPORTED_KEY_SIZE;
            }
        }
    }

 #if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_RSA_2048_ALT)
    else if (HW_SCE_RSA_2048_KEY_D_LENGTH_BYTE_SIZE == exponent_length)
    {
        uint32_t key[HW_SCE_RSA2048_ND_KEY_BYTE_SIZE >> 2U] = {0};
        uint32_t aligned_work_buffer[HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE / sizeof(uint32_t)] = {0};
        NX_CRYPTO_MEMCPY(aligned_work_buffer, input, sizeof(aligned_work_buffer));
        NX_CRYPTO_MEMCPY(key, modulus, modulus_length);
        NX_CRYPTO_MEMCPY(&key[modulus_length >> 2U], exponent, exponent_length);

        /* Plain private key: This is a decryption operation */
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
                                              (const uint8_t *) key, (uint32_t *) &encrypted_rsa_key.value);

        if (FSP_SUCCESS == err)
        {
            err = HW_SCE_Rsa2048ModularExponentDecryptSub((uint32_t *) &encrypted_rsa_key.value,
                                                          (uint32_t *) aligned_work_buffer,
                                                          (uint32_t *) aligned_work_buffer);
        }

        NX_CRYPTO_MEMCPY(output, aligned_work_buffer, sizeof(aligned_work_buffer));
    }
    /* This is a special case where the entire wrapped key is passed through the exponent parameter */
    else if (RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(HW_SCE_RSA2048_ND_KEY_INDEX_WORD_SIZE) == exponent_length)
    {
        /* Input parameters are expected to be word aligned here as this section is executed when
         * the user application directly. NetX Secure does not get to this section.
         */

        /* Check the input message length to ensure its not larger than the modulus size.
         * Note: Since the wrapped key (and not the plain modulus) is passed during init API,
         * a larger length is allowed by the caller during the operation API.
         * (Wrapped key length is larger than plain modulus length)
         * Verify length to preserve security. */
        if (input_length > HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE)
        {
            return NX_CRYPTO_PTR_ERROR;
        }

        /* Wrapped private key : This is a decryption operation. */
        err = HW_SCE_Rsa2048ModularExponentDecryptSub((uint32_t *) exponent, (uint32_t *) input, (uint32_t *) output);
    }
 #endif
    else
    {
        return NX_CRYPTO_UNSUPPORTED_KEY_SIZE;
    }
    FSP_ERROR_RETURN((FSP_SUCCESS == err), NX_CRYPTO_NOT_SUCCESSFUL);

    return NX_CRYPTO_SUCCESS;
}

#endif
