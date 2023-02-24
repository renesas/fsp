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
 * File Name    : rm_netx_secure_crypto.c
 * Description  : TRNG
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_netx_secure_crypto.h"
#include "rm_netx_secure_crypto_cfg.h"
#include "hw_sce_trng_private.h"
#if (1 == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_ECC_ALT)
 #include "hw_sce_ecc_private.h"
#endif
#include "hw_sce_private.h"

/*******************************************************************************************************************//**
 * @addtogroup RM_NETX_SECURE_CRYPTO
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/
#if (1 == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_TRNG_ALT)

/***********************************************************************************************************************
 * Alternate implementation of Standard C Library 'rand' function.
 * Uses HW TRNG to generate 4 bytes of random number.
 *
 * @retval True random number            TRNG was successful.
 * @retval 0                             Failed to generate random number.
 **********************************************************************************************************************/
int rand (void)
{
    uint32_t  random_number[4U] = {0};
    fsp_err_t err               = HW_SCE_RNG_Read(random_number);

    if (FSP_SUCCESS != err)
    {
        return 0;
    }

    return (int) random_number[0];
}

/***********************************************************************************************************************
 * Alternate implementation of Standard C Library 'srand' function.
 * Re-seeding is not supported by the HW. This function does nothing.
 **********************************************************************************************************************/
void srand (unsigned int seed)
{
    FSP_PARAMETER_NOT_USED(seed);
}

#endif

#if (1 == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_ECC_ALT)

/***********************************************************************************************************************
 * ECC Key Generate helper function for ECDSA and ECDH APIs.
 * @note This fucntion must not be called directly by the user application.
 * Output: (Wrapped private key || Uncompressed public key) where Uncompressed public key starts with 0x04.
 * @retval NX_CRYPTO_SUCCESS              Key generation was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       Key Generation was not successful.
 * @retval NX_CRYPTO_SIZE_ERROR           Input buffer length is not sufficient.
 * @retval NX_CRYTPO_MISSING_ECC_CURVE    Unsupported ECC curve.
 **********************************************************************************************************************/
uint32_t rm_netx_secure_crypto_ecc_key_pair_generate (uint32_t   curve_id,
                                                      uint32_t   curve_size,
                                                      uint8_t  * output,
                                                      uint32_t   output_length_in_byte,
                                                      uint32_t * actual_output_length)
{
    uint32_t wrapped_key[RM_NETX_SECURE_CRYPTO_LARGEST_FORMATTED_ECC_PUBLIC_KEY_WORDS] = {0};
    uint32_t wrapped_key_length = (curve_id == NX_CRYPTO_EC_SECP384R1) ? RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(
                                                                                                                          ECC_384_PRIVATE_KEY_LENGTH_WORDS))
                                  :
                                  RM_NETX_SECURE_CRYPTO_ECC_WRAPPED_KEY_ADJUST(RM_NETX_SECURE_CRYPTO_WORDS_TO_BYTES(
                                                                                   ECC_256_PRIVATE_KEY_LENGTH_WORDS));
    uint32_t  curve_type = SCE_ECC_CURVE_TYPE_NIST;
    uint32_t  cmd        = 0x0;
    fsp_err_t err        = FSP_SUCCESS;

    /* Check output buffer size. */
    if ((1U + (curve_size << 1) + wrapped_key_length) > output_length_in_byte)
    {
        return NX_CRYPTO_SIZE_ERROR;
    }

    output[wrapped_key_length] = 0x04; /* Uncompressed representation */

    /* Generate ECC key pair based on the curve type & size */
    if (curve_id == NX_CRYPTO_EC_SECP384R1)
    {
        sce_ecc384_public_key_index_t public_key = {0};
        uint32_t indata_key_type                 = 0;
        err =
            HW_SCE_GenerateEccP384RandomKeyIndexSub(&curve_type, &indata_key_type, (uint32_t *) &public_key.value,
                                                    (uint32_t *) &public_key.plain_value, (uint32_t *) wrapped_key,
                                                    (uint32_t *) &public_key.plain_value);

        NX_CRYPTO_MEMCPY(output, wrapped_key, wrapped_key_length);
        NX_CRYPTO_MEMCPY(&output[wrapped_key_length + 1], public_key.value.key_q, curve_size);
        NX_CRYPTO_MEMCPY(&output[wrapped_key_length + 1 + curve_size], &public_key.value.key_q[curve_size], curve_size);
    }
    else if (curve_id == NX_CRYPTO_EC_SECP256R1)
    {
        sce_ecc_public_key_index_t public_key = {0};
        uint32_t indata_key_type              = 0;
        err =
            HW_SCE_GenerateEccRandomKeyIndexSub(&curve_type, &cmd, &indata_key_type, (uint32_t *) &public_key.value,
                                                (uint32_t *) &public_key.plain_value, (uint32_t *) wrapped_key,
                                                (uint32_t *) &public_key.plain_value);
        NX_CRYPTO_MEMCPY(output, wrapped_key, wrapped_key_length);
        NX_CRYPTO_MEMCPY(&output[wrapped_key_length + 1], public_key.value.key_q, curve_size);
        NX_CRYPTO_MEMCPY(&output[wrapped_key_length + 1 + curve_size], &public_key.value.key_q[curve_size], curve_size);
    }
    else if (curve_id == NX_CRYPTO_EC_SECP224R1)
    {
        sce_ecc_public_key_index_t public_key = {0};
        cmd = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(RM_NETX_SECURE_CRYPTO_ECC_224_CURVE_OPERATION);
        uint32_t indata_key_type = 0;
        err =
            HW_SCE_GenerateEccRandomKeyIndexSub(&curve_type, &cmd, &indata_key_type, (uint32_t *) &public_key.value,
                                                (uint32_t *) &public_key.plain_value, (uint32_t *) wrapped_key,
                                                (uint32_t *) &public_key.plain_value);

        /* This generates the public key as:
         * 4/16-bytes key info|| 4-bytes 0s || 28 bytes x-coordinate || 4-bytes 0s || 28 bytes y-coordinate || 16-bytes key info
         */

        NX_CRYPTO_MEMCPY(output, wrapped_key, wrapped_key_length);
        NX_CRYPTO_MEMCPY(&output[wrapped_key_length + 1], public_key.value.key_q, curve_size);
        NX_CRYPTO_MEMCPY(&output[wrapped_key_length + 1 + curve_size], &public_key.value.key_q[curve_size], curve_size);
    }
    else
    {
        return NX_CRYTPO_MISSING_ECC_CURVE;
    }

    FSP_ERROR_RETURN((FSP_SUCCESS == err), NX_CRYPTO_NOT_SUCCESSFUL);

    /* plain public key length */
    *actual_output_length = 1 + (curve_size << 1) + wrapped_key_length;

    return NX_CRYPTO_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/
