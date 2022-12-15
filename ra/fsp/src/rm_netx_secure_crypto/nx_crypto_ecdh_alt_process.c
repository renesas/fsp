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
 * File Name    : nx_crypto_ecdh_alt_process.c
 * Description  : Functions interfacing with SCE
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_netx_secure_crypto_cfg.h"
#if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_ECC_ALT)
 #include "rm_netx_secure_crypto.h"
 #include "nx_crypto_ecdh.h"
 #include "hw_sce_ecc_private.h"
 #include "hw_sce_private.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #define RM_NETX_SECURE_CRYPTO_ECC_192_224_256_PLAIN_PADDED_PRIVATE_KEY_SIZE_BYTES    (32U)
 #define RM_NETX_SECURE_CRYPTO_ECC_384_WRAPPED_KEY_SIZE_BYTES                         (17U * 4U)
 #define RM_NETX_SECURE_CRYPTO_ECC_256_PLAIN_PUBLIC_KEY_SIZE_BYTES                    (64U)
 #define RM_NETX_SECURE_CRYPTO_ECC_224_COORDINATE_SIZE_BYTES                          (28U)

/*******************************************************************************************************************//**
 * @addtogroup RM_NETX_SECURE_CRYPTO
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * ECDH Key private key import.
 * Check public key size.
 * Set shared secret size.
 * @note plain/wrapped private key can be imported.
 * @note plain/formatted public key can be length checked.
 * @retval NX_CRYPTO_SUCCESS              Key was imported successfully.
 * @retval NX_CRYPTO_SIZE_ERROR           Invalid public/private key size.
 * @retval NX_CRYPTO_INVALID_KEY          Invalid ECC keys.
 * @retval NX_CRYTPO_MISSING_ECC_CURVE    ECDH operation not HW accelerated for the input curve.
 **********************************************************************************************************************/
UINT sce_nx_crypto_ecdh_key_pair_import (NX_CRYPTO_ECDH * ecdh_ptr,
                                         NX_CRYPTO_EC   * curve,
                                         UCHAR          * local_private_key_ptr,
                                         ULONG            local_private_key_len,
                                         ULONG            local_public_key_len)
{
    uint32_t * wrapped_private_key_ptr = NULL;
    uint8_t  * plain_private_key_ptr   = local_private_key_ptr;
    uint32_t   curve_size_bytes        = ((curve->nx_crypto_ec_bits + 7) >> 3);
    uint32_t   plain_private_key_len   = curve_size_bytes;
    uint32_t   wrapped_key_len         =
        (curve->nx_crypto_ec_id == NX_CRYPTO_EC_SECP384R1) ? RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(
                                                                                                              ECC_384_PRIVATE_KEY_LENGTH_WORDS))
        :
        RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(
                                                         ECC_256_PRIVATE_KEY_LENGTH_WORDS));
    uint32_t key_len = plain_private_key_len;

    /* public key length check is updated as the user may enter plain public key directly
     * or public key + SCE generated MAC previously exported on this device.
     * This additional key info is 20 bytes in size.
     */
    uint32_t public_key_len = 1 + (curve_size_bytes << 1);
    if ((local_public_key_len != public_key_len) &&
        (local_public_key_len != (public_key_len - RM_NETX_SECURE_CRYPTO_FORMATTED_ECC_PUBLIC_KEY_ADJUST)))
    {

        /* The key length passed neither matches the standard ECC public key nor the SCE9/7 formatted key length */
        return NX_CRYPTO_SIZE_ERROR;
    }

    /* Clear the private key buffer. */
    NX_CRYPTO_MEMSET(ecdh_ptr->nx_crypto_ecdh_private_key_buffer, 0,
                     sizeof(ecdh_ptr->nx_crypto_ecdh_private_key_buffer));

    uint32_t local_private_wrapped_key[RM_NETX_SECURE_CRYPTO_LARGEST_FORMATTED_ECC_PUBLIC_KEY_WORDS]     = {0};
    uint8_t  padded_plain_key[RM_NETX_SECURE_CRYPTO_ECC_192_224_256_PLAIN_PADDED_PRIVATE_KEY_SIZE_BYTES] = {0};

    /* Check if the user is trying to import a plain private key */
    if (plain_private_key_len == local_private_key_len)
    {
        sce_oem_cmd_t oem_cmd = SCE_OEM_CMD_NUM;
        switch (curve->nx_crypto_ec_id)
        {
            case NX_CRYPTO_EC_SECP384R1:
            {
                oem_cmd = SCE_OEM_CMD_ECC_P384_PRIVATE;
                break;
            }

            case NX_CRYPTO_EC_SECP256R1:
            {
                oem_cmd = SCE_OEM_CMD_ECC_P256_PRIVATE;
                break;
            }

            case NX_CRYPTO_EC_SECP224R1:
            {
                oem_cmd = SCE_OEM_CMD_ECC_P224_PRIVATE;

                /* Add 4 bytes of zero padding before the private key as expected by SCE */
                NX_CRYPTO_MEMCPY(&padded_plain_key[4], local_private_key_ptr, local_private_key_len);
                plain_private_key_ptr = padded_plain_key;
                break;
            }

            default:
            {
                return NX_CRYTPO_MISSING_ECC_CURVE;
            }
        }

        /* Install the plaintext private key to get the wrapped private key */
        if (FSP_SUCCESS !=
            HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN, oem_cmd, NULL, NULL,
                                              (const uint8_t *) plain_private_key_ptr, local_private_wrapped_key))
        {
            return NX_CRYPTO_INVALID_KEY;
        }

        wrapped_private_key_ptr = local_private_wrapped_key;
        key_len                 = wrapped_key_len; /* Wrapped key size from plain key size */
    }
    else if (wrapped_key_len == local_private_key_len)
    {
        wrapped_private_key_ptr = (uint32_t *) local_private_key_ptr;
        key_len                 = wrapped_key_len;
    }
    else
    {
        return NX_CRYPTO_SIZE_ERROR;
    }

    NX_CRYPTO_MEMCPY(ecdh_ptr->nx_crypto_ecdh_private_key_buffer, wrapped_private_key_ptr, key_len);

    /* Assign the desired key size based on the chosen elliptic curve. This is the shared secret size */
    ecdh_ptr->nx_crypto_ecdh_key_size = curve->nx_crypto_ec_bits >> 3U;

    return NX_CRYPTO_SUCCESS;
}

/***********************************************************************************************************************
 * ECDH Key private key export. .
 * @note Only wrapped private key will be exported.
 * @retval NX_CRYPTO_SUCCESS              Key was exported successfully.
 * @retval NX_CRYPTO_SIZE_ERROR           Private key buffer is not large enough to hold the wrapped key.
 **********************************************************************************************************************/
UINT sce_nx_crypto_ecdh_private_key_export (NX_CRYPTO_ECDH * ecdh_ptr,
                                            UCHAR          * local_private_key_ptr,
                                            ULONG            local_private_key_len,
                                            ULONG          * actual_local_private_key_len)
{
    /* Check to make sure the buffer is large enough to hold the private key. */
    uint32_t key_length =
        RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(((ecdh_ptr->nx_crypto_ecdh_curve->nx_crypto_ec_bits + 7) >> 3)); /* Add 20 bytes for wrapped key */
    if (local_private_key_len < key_length)
    {
        return NX_CRYPTO_SIZE_ERROR;
    }

    NX_CRYPTO_MEMCPY(local_private_key_ptr, ecdh_ptr->nx_crypto_ecdh_private_key_buffer, key_length);
    *actual_local_private_key_len = key_length;

    return NX_CRYPTO_SUCCESS;
}

/***********************************************************************************************************************
 * ECDH Setup.
 * Generate ECC key pair. Store the wrapped private key in the context and export the public key (unformatted)
 * @retval NX_CRYPTO_SUCCESS              Key was exported successfully.
 * @retval NX_CRYPTO_SIZE_ERROR           Public key buffer is not large enough to hold the formatted public key.
 **********************************************************************************************************************/
UINT sce_nx_crypto_ecdh_setup (NX_CRYPTO_ECDH * ecdh_ptr,
                               UCHAR          * local_public_key_ptr,
                               ULONG          * actual_local_public_key_len,
                               NX_CRYPTO_EC   * curve)
{
    uint32_t ret_key_len        = 0;
    uint32_t curve_size         = ((curve->nx_crypto_ec_bits + 7) >> 3);
    uint32_t wrapped_key_length =
        (curve->nx_crypto_ec_id == NX_CRYPTO_EC_SECP384R1) ? RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(
                                                                                                              ECC_384_PRIVATE_KEY_LENGTH_WORDS))
        :
        RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(
                                                         ECC_256_PRIVATE_KEY_LENGTH_WORDS));
    uint32_t key_length =
        RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE) +
        HW_SCE_ECC_P384_PUBLIC_KEY_BYTE_SIZE + RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(
            HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE) + wrapped_key_length;
    uint32_t key[(RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(
                                                                   ECC_384_PRIVATE_KEY_LENGTH_WORDS)) / 4U) +
                 HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE + 1U +
                 (HW_SCE_ECC_P384_PUBLIC_KEY_BYTE_SIZE / 4U) + HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE] = {0};
    uint32_t status =
        rm_netx_secure_crypto_ecc_key_pair_generate(curve->nx_crypto_ec_id,
                                                    curve_size,
                                                    (uint8_t *) key,
                                                    key_length,
                                                    &ret_key_len);
    if (status != NX_CRYPTO_SUCCESS)
    {
        return status;
    }

    /* Store the generated wrapped key in the ecdh context */
    NX_CRYPTO_MEMCPY(ecdh_ptr->nx_crypto_ecdh_private_key_buffer, key, wrapped_key_length);
    ecdh_ptr->nx_crypto_ecdh_key_size = wrapped_key_length;
    NX_CRYPTO_MEMCPY(local_public_key_ptr, &key[wrapped_key_length / 4U], ((curve_size << 1U) + 1U));

    /* plain public key length */
    *actual_local_public_key_len = 1 + (curve_size << 1);

    return NX_CRYPTO_SUCCESS;
}

/***********************************************************************************************************************
 * ECDH Shared secret compute. [Scalar Multiply]
 * @retval NX_CRYPTO_SUCCESS              Key was exported successfully.
 * @retval NX_CRYPTO_SIZE_ERROR           Public key buffer is not large enough to hold the formatted public key.
 **********************************************************************************************************************/
UINT sce_nx_crypto_ecdh_compute_secret (NX_CRYPTO_ECDH * ecdh_ptr,
                                        UCHAR          * share_secret_key_ptr,
                                        ULONG          * actual_share_secret_key_len,
                                        UCHAR          * remote_public_key)
{
    NX_CRYPTO_EC * curve      = ecdh_ptr->nx_crypto_ecdh_curve;
    uint32_t       curve_type = SCE_ECC_CURVE_TYPE_NIST;
    uint32_t       cmd        = 0x0;
    fsp_err_t      err        = FSP_SUCCESS;

    uint32_t pub_key[HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE + (HW_SCE_ECC_P384_PUBLIC_KEY_BYTE_SIZE / 4U) +
                     HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE] = {0};
    NX_CRYPTO_MEMCPY(pub_key, &remote_public_key[1], ((((curve->nx_crypto_ec_bits + 7) >> 3) << 1)));

    /* Generate ECC key pair based on the curve type & size */
    if (curve->nx_crypto_ec_id == NX_CRYPTO_EC_SECP384R1)
    {
        err = HW_SCE_Ecc384ScalarMultiplicationSub(&curve_type,
                                                   (uint32_t *) ecdh_ptr->nx_crypto_ecdh_private_key_buffer,
                                                   pub_key,
                                                   (uint32_t *) share_secret_key_ptr);
    }
    else if (curve->nx_crypto_ec_id == NX_CRYPTO_EC_SECP256R1)
    {
        err = HW_SCE_Ecc256ScalarMultiplicationSub(&curve_type,
                                                   &cmd,
                                                   (uint32_t *) ecdh_ptr->nx_crypto_ecdh_private_key_buffer,
                                                   pub_key,
                                                   (uint32_t *) share_secret_key_ptr);
    }
    else if (curve->nx_crypto_ec_id == NX_CRYPTO_EC_SECP224R1)
    {
        cmd = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(RM_NETX_SECURE_CRYPTO_ECC_224_CURVE_OPERATION);

        /* Buffer to store the padded (unformatted) public key as expected by SCE */
        uint8_t padded_plain_public_key[RM_NETX_SECURE_CRYPTO_ECC_256_PLAIN_PUBLIC_KEY_SIZE_BYTES] = {0};

        /* Copy x-coordinate with 4 bytes padding. Exclude 0x04 ASN constant */
        memcpy(&padded_plain_public_key[4U], pub_key, RM_NETX_SECURE_CRYPTO_ECC_224_COORDINATE_SIZE_BYTES);

        /* Copy y-coordinate after the above with 4 bytes padding. */
        memcpy(&padded_plain_public_key[4U + RM_NETX_SECURE_CRYPTO_ECC_224_COORDINATE_SIZE_BYTES + 4U],
               &pub_key[RM_NETX_SECURE_CRYPTO_ECC_224_COORDINATE_SIZE_BYTES / 4U],
               RM_NETX_SECURE_CRYPTO_ECC_224_COORDINATE_SIZE_BYTES);

        err = HW_SCE_Ecc256ScalarMultiplicationSub(&curve_type,
                                                   &cmd,
                                                   (uint32_t *) ecdh_ptr->nx_crypto_ecdh_private_key_buffer,
                                                   (uint32_t *) padded_plain_public_key,
                                                   (uint32_t *) share_secret_key_ptr);
    }
    else
    {
        return NX_CRYTPO_MISSING_ECC_CURVE;
    }

    FSP_ERROR_RETURN((FSP_SUCCESS == err), NX_CRYPTO_NOT_SUCCESSFUL);

    *actual_share_secret_key_len = ((curve->nx_crypto_ec_bits + 7) >> 3);

    return NX_CRYPTO_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/
#endif
