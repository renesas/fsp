/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * File Name    : nx_crypto_ecdsa_alt_process.c
 * Description  : Functions interfacing with SCE
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_netx_secure_crypto_cfg.h"
#if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_ECC_ALT)
 #include "nx_crypto_ecdsa.h"
 #include "hw_sce_private.h"
 #include "hw_sce_ra_private.h"
 #include "hw_sce_ecc_private.h"
 #include "rm_netx_secure_crypto.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #define RM_NETX_SECURE_CRYPTO_P384_CURVE_SIZE_BYTES    (384U >> 3U)
 #define RM_NETX_SECURE_CRYPTO_P256_CURVE_SIZE_BYTES    (256U >> 3U)
 #define RM_NETX_SECURE_CRYPTO_P224_CURVE_SIZE_BYTES    (224U >> 3U)

/*******************************************************************************************************************//**
 * @addtogroup RM_NETX_SECURE_CRYPTO
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * ECDSA Signature Generate.
 * Using standatd plain private key OR Wrapped private key generate the signature of input hash.
 * @retval NX_CRYPTO_SUCCESS              Signature generation was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       Failed to generate the signature for the input hash.
 **********************************************************************************************************************/
UINT sce_nx_crypto_ecdsa_sign (NX_CRYPTO_EC * curve,
                               UCHAR        * hash,
                               UINT           hash_length,
                               UCHAR        * private_key,
                               UINT           private_key_length,
                               UCHAR        * signature_r,
                               UINT         * r_size,
                               UCHAR        * signature_s,
                               UINT         * s_size)
{
    fsp_err_t     err                = FSP_SUCCESS;
    uint32_t      cmd                = 0;
    sce_oem_cmd_t key_command        = SCE_OEM_CMD_ECC_P256_PRIVATE;
    uint32_t      curve_type         = SCE_ECC_CURVE_TYPE_NIST;
    UINT          curve_size         = (curve->nx_crypto_ec_bits) >> 3;
    uint32_t      zero_padding_words = 0;
    *r_size = 0;
    *s_size = 0;
    uint32_t wrapped_private_key[(RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(
                                      RM_NETX_SECURE_CRYPTO_P384_CURVE_SIZE_BYTES)) / 4U] = {0};

    /* May need to 0 pad the private key. This is also used to 0 pad the digest. */
    uint8_t work_buffer[RM_NETX_SECURE_CRYPTO_P384_CURVE_SIZE_BYTES * 2] = {0};

    /* Due to the padding logic in the NX stack the signature buffers will not be word aligned.
     * Create local buffers to store the generated signature and copy those to the byte aligned signature buffers.
     * */
    uint32_t sign[RM_NETX_SECURE_CRYPTO_LARGEST_SUPPORTED_SIGNATURE_COORDINATE_SIZE_WORDS * 2U] = {0};

    switch (curve_type)                /* Adding this for future expandability to BP and K curves */
    {
        case SCE_ECC_CURVE_TYPE_NIST:
        {
            /* Set the OEM key command and verify API command for (224/256 curves) */
            switch (curve->nx_crypto_ec_id)
            {
                case NX_CRYPTO_EC_SECP384R1:
                {
                    key_command = SCE_OEM_CMD_ECC_P384_PRIVATE;

                    /* cmd is unused */
                    /* Initialization value of zero_padding_words */
                    break;
                }

                case NX_CRYPTO_EC_SECP256R1:
                {
                    /* Initialization value of key_command, cmd, zero_padding_words */
                    break;
                }

                case NX_CRYPTO_EC_SECP224R1:
                {
                    key_command = SCE_OEM_CMD_ECC_P224_PRIVATE;
                    cmd         =
                        RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(RM_NETX_SECURE_CRYPTO_ECC_224_CURVE_OPERATION);
                    zero_padding_words = 1;
                    break;
                }

                default:
                {
                    return NX_CRYTPO_MISSING_ECC_CURVE;
                }
            }

            break;
        }

        default:
        {
            return NX_CRYTPO_MISSING_ECC_CURVE;
        }
    }

    if ((private_key_length == RM_NETX_SECURE_CRYPTO_BITS_TO_BYTES(ECC_256_PRIVATE_KEY_LENGTH_BITS)) ||
        (private_key_length == RM_NETX_SECURE_CRYPTO_BITS_TO_BYTES(ECC_224_PRIVATE_KEY_LENGTH_BITS)) ||
        (private_key_length == RM_NETX_SECURE_CRYPTO_BITS_TO_BYTES(ECC_384_PRIVATE_KEY_LENGTH_BITS)))
    {
        NX_CRYPTO_MEMCPY(&work_buffer[4 * zero_padding_words], private_key, curve_size);

        /* Install the plaintext private key to get the wrapped key */
        err = HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                                key_command,
                                                NULL,
                                                NULL,
                                                (const uint8_t *) work_buffer,
                                                wrapped_private_key);
        FSP_ERROR_RETURN((FSP_SUCCESS == err), NX_CRYPTO_NOT_SUCCESSFUL);
        memset(work_buffer, 0, RM_NETX_SECURE_CRYPTO_P384_CURVE_SIZE_BYTES * 2U);
    }
    /* Wrapped key for 192, 224 and 256 bit ECC curves is of the same length (ECC_256_PRIVATE_KEY_HRK_LENGTH_WORDS) */
    else if ((private_key_length ==
              RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(
                                                               ECC_256_PRIVATE_KEY_LENGTH_WORDS)))
             ||
             (private_key_length ==
              RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(
                                                               ECC_384_PRIVATE_KEY_LENGTH_WORDS))))
    {
        /* Valid wrapped private key size */
        NX_CRYPTO_MEMCPY(wrapped_private_key, private_key, private_key_length);
    }
    else
    {
        return NX_CRYPTO_SIZE_ERROR;
    }

    /* The hash input (buf) should have a length of at least the curve size:
     * nist.fips.186-4: " A hash function that provides a lower security strength than
     * the security strength associated with the bit length of 'n' ordinarily should not be used, since this
     * would reduce the security strength of the digital signature process to a level no greater than that
     * provided by the hash function."
     * However, the SCE HW functions only parse hash of exactly curve_bytes length so
     * *-Any larger hash data will be truncated.
     * *-Any smaller data will be 0-padded to the LEFT.
     *//* Start after 8 bytes to prevent another memory adjustment for 224 and 192 bit curves. This will serve as 0 padding offset.
     * The 'digest' buffer is large enough to accomadate this extra 0 padding for 224 and 192 bit curves.
     * There will be no 0 padding for 256 and 384 bit curves.
     */
    uint32_t idx = (curve_size > hash_length) ? (curve_size - hash_length) : 0;
    NX_CRYPTO_MEMCPY(&work_buffer[idx + 8U], hash, hash_length);
    uint32_t digest_offset = 8U - (zero_padding_words * 4U);

    switch (curve->nx_crypto_ec_id)
    {
 
        case NX_CRYPTO_EC_SECP384R1:
        {
            /* digest - No 0 padding, skip the first 2 '0' words */
            err =
                HW_SCE_EcdsaP384SignatureGenerateSub(&curve_type, wrapped_private_key, (uint32_t *) &work_buffer[digest_offset],
                                                     sign);
            break;
        }

        /* digest - 1 word 0 padding, skip the first '0' word */
        case NX_CRYPTO_EC_SECP224R1:

        /* digest - No 0 padding, skip the first 2 '0' words */
        case NX_CRYPTO_EC_SECP256R1:
        {
            err =
                HW_SCE_EcdsaSignatureGenerateSub(&curve_type, &cmd, wrapped_private_key,
                                                 (uint32_t *) &work_buffer[digest_offset], sign);
            break;
        }

        default:
        {
            break;
        }
    }

    FSP_ERROR_RETURN((FSP_SUCCESS == err), NX_CRYPTO_NOT_SUCCESSFUL);

    /* Copy the signature into the user buffer */
    NX_CRYPTO_MEMCPY(signature_r, &sign[zero_padding_words], curve_size);
    NX_CRYPTO_MEMCPY(signature_s, &sign[(curve_size / 4U) + (zero_padding_words * 2)], curve_size);
    *r_size = curve_size;
    *s_size = curve_size;

    return NX_CRYPTO_SUCCESS;
}

/***********************************************************************************************************************
 * ECDSA Signature Verify.
 * Using standatd plain public key, signature verify the input hash.
 * @retval NX_CRYPTO_SUCCESS              Signature verify was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       Failed to verify the signature.
 **********************************************************************************************************************/
UINT sce_nx_crypto_ecdsa_verify (NX_CRYPTO_EC * curve,
                                 UCHAR        * hash,
                                 UINT           hash_length,
                                 UCHAR        * public_key,
                                 UCHAR        * signature_r,
                                 UINT           r_size,
                                 UCHAR        * signature_s,
                                 UINT           s_size)
{
    fsp_err_t     err                    = FSP_SUCCESS;
    uint32_t      cmd                    = 0;
    uint32_t      curve_type             = SCE_ECC_CURVE_TYPE_NIST;
    UINT          curve_size             = (curve->nx_crypto_ec_bits) >> 3;
    sce_oem_cmd_t key_command            = SCE_OEM_CMD_ECC_P256_PUBLIC;
    uint32_t      zero_padding_words     = 0;
    uint32_t      padded_coordinate_size = RM_NETX_SECURE_CRYPTO_P256_CURVE_SIZE_BYTES;

    /* For case where the R and S components of signature start with one or more 0s the inherent encoding eliminates them.
     * These need to be readded at the time of re-creating the signature value.
     * The difference between the curve size and the R/S length is the number of 0 byte prefex omitted.
     */
    uint32_t signature_r_repad_length = curve_size - r_size;
    uint32_t signature_s_repad_length = curve_size - s_size;

    /* Due to the padding logic in the NX stack the signature buffers will not be word alogned.
     * Create word aligned local buffers to store the input signature from the byte aligned user signature buffers.
     * */
    uint32_t sign[RM_NETX_SECURE_CRYPTO_LARGEST_SUPPORTED_SIGNATURE_SIZE_WORDS] = {0};

    /* Similarly, the public key input will not be word aligned due to the ASN1 constant */
    uint32_t pub_key[RM_NETX_SECURE_CRYPTO_LARGEST_SUPPORTED_PUBLIC_KEY_SIZE_WORDS]             = {0};
    uint32_t formatted_public_key[RM_NETX_SECURE_CRYPTO_LARGEST_FORMATTED_ECC_PUBLIC_KEY_WORDS] = {0};

    /* The hash input (buf) should have a length of at least the curve size:
     * nist.fips.186-4: " A hash function that provides a lower security strength than
     * the security strength associated with the bit length of 'n' ordinarily should not be used, since this
     * would reduce the security strength of the digital signature process to a level no greater than that
     * provided by the hash function."
     * However, the SCE HW functions only parse hash of exactly curve_bytes length so
     * *-Any larger hash data will be truncated.
     * *-Any smaller data will be 0-padded to the LEFT.
     *//* Allocate largest buffer size we support */
    uint8_t  digest[RM_NETX_SECURE_CRYPTO_LARGEST_SUPPORTED_SIGNATURE_SIZE_WORDS * 4U] = {0};
    uint32_t idx = (curve_size > hash_length) ? (curve_size - hash_length) : 0;

    /* Start after 8 bytes to prevent another memory adjustment for 224 and 192 bit curves. This will serve as 0 padding offset.
     * The 'digest' buffer is large enough to accomadate this extra 0 padding for 224 and 192 bit curves.
     * There will be no 0 padding for 256 and 384 bit curves.
     */
    NX_CRYPTO_MEMCPY(&digest[idx + 8U], hash, hash_length);

    switch (curve_type)                /* Adding this for future expandability to BP and K curves */
    {
        case SCE_ECC_CURVE_TYPE_NIST:
        {
            /* Set the OEM key command and verify API command for (224/256 curves) */
            switch (curve->nx_crypto_ec_id)
            {
                case NX_CRYPTO_EC_SECP384R1:
                {
                    key_command            = SCE_OEM_CMD_ECC_P384_PUBLIC;
                    padded_coordinate_size = RM_NETX_SECURE_CRYPTO_P384_CURVE_SIZE_BYTES;

                    /* cmd is unused */
                    /* Initialization value of zero_padding_words */
                    break;
                }

                case NX_CRYPTO_EC_SECP256R1:
                {
                    /* Initialization value of key_command, cmd, zero_padding_words */
                    break;
                }

                case NX_CRYPTO_EC_SECP224R1:
                {
                    key_command = SCE_OEM_CMD_ECC_P224_PUBLIC;
                    cmd         =
                        RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(RM_NETX_SECURE_CRYPTO_ECC_224_CURVE_OPERATION);
                    zero_padding_words = 1;
                    break;
                }

                default:
                {
                    return NX_CRYTPO_MISSING_ECC_CURVE;
                }
            }

            break;
        }

        default:
        {
            return NX_CRYTPO_MISSING_ECC_CURVE;
        }
    }

    NX_CRYPTO_MEMCPY(&pub_key[zero_padding_words], public_key, curve_size);
    NX_CRYPTO_MEMCPY(&pub_key[(padded_coordinate_size / 4U) + zero_padding_words], &public_key[curve_size], curve_size);

    /* Copy the signature into the local buffer
     * Advance signature_r_repad_length/signature_s_repad_length number of bytes to re-pad with 0s.
     */
    NX_CRYPTO_MEMCPY(((uint8_t *) &sign[zero_padding_words]) + signature_r_repad_length, signature_r, r_size);
    NX_CRYPTO_MEMCPY(((uint8_t *) &sign[(padded_coordinate_size / 4U) + zero_padding_words]) + signature_s_repad_length,
                     signature_s,
                     s_size);

    /* Install the plaintext public key to get the formatted public key */
    err = HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                            key_command,
                                            NULL,
                                            NULL,
                                            (const uint8_t *) pub_key,
                                            formatted_public_key);

    FSP_ERROR_RETURN((FSP_SUCCESS == err), NX_CRYPTO_NOT_SUCCESSFUL);
    uint32_t digest_offset = 8U - (zero_padding_words * 4U);

    /* Verify procedure selection based on ECC curve (type & size) */
    switch (curve->nx_crypto_ec_id)
    {
        case NX_CRYPTO_EC_SECP384R1:
        {
            /* digest - No 0 padding, skip the first 2 '0' words */
            err =
                HW_SCE_EcdsaP384SignatureVerificationSub(&curve_type, formatted_public_key, (uint32_t *) &digest[digest_offset],
                                                         sign);
            break;
        }

        /* digest - 1 word 0 padding, skip the first '0' word */
        case NX_CRYPTO_EC_SECP224R1:

        /* digest - No 0 padding, skip the first 2 '0' words */
        case NX_CRYPTO_EC_SECP256R1:
        {
            err =
                HW_SCE_EcdsaSignatureVerificationSub(&curve_type, &cmd, formatted_public_key,
                                                     (uint32_t *) &digest[digest_offset], sign);
            break;
        }

        default:
        {
            break;
        }
    }

    FSP_ERROR_RETURN((FSP_SUCCESS == err), NX_CRYPTO_NOT_SUCCESSFUL);

    return NX_CRYPTO_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/
#endif
