/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "common.h"

#include "vendor.h"
#include "asymmetric_vendor.h"
#include "aes_vendor.h"
#include "mbedtls/error.h"
#include "mbedtls/psa_util.h"

uint32_t ecp_load_key_size(bool wrapped_mode_ctx, const mbedtls_ecp_group * grp);

psa_status_t vendor_bitlength_to_raw_bitlength (psa_key_type_t type, size_t vendor_bits, size_t * raw_bits)
{
    (void) vendor_bits;
    (void) raw_bits;
    (void) type;
    psa_status_t status = PSA_SUCCESS;
#if defined(MBEDTLS_AES_C) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))

    /* Check if the key is of AES type */
    if (PSA_KEY_TYPE_IS_AES(type))
    {
/* Check that the bit size is acceptable for the key type
 * Wrapped 192 key support is differentiated from 256 wrapped key support by increasing its size by 32 bits.
 * These 32 bits are prepended and are not used by the crypto primitives (which continue to use 416 bits as the wrapped
 * key length for both the keys). */
        *raw_bits = PSA_AES_BITS_VENDOR_RAW(vendor_bits);
        if (0 == *raw_bits)
        {
            status = PSA_ERROR_NOT_SUPPORTED;
        }
    }
    else
#endif
    {
        status = PSA_ERROR_NOT_SUPPORTED;
    }

    return status;
}

/** Calculate the size of the vendor key in the given slot, in bits.
 *
 * \param[in] slot      A key slot containing a transparent key.
 *
 * \return The key size in bits, calculated from the key data.
 */
static psa_key_bits_t calculate_key_bits_vendor (const psa_key_slot_t * slot)
{
    size_t bits = 0;                   /* return 0 on an empty slot */

    if (PSA_KEY_TYPE_IS_UNSTRUCTURED(slot->attr.type))
    {
        bits = PSA_BYTES_TO_BITS(slot->key.bytes);
    }

#if defined(MBEDTLS_RSA_C)
    else if (PSA_KEY_TYPE_IS_RSA(slot->attr.type))
    {
        bits = PSA_BYTES_TO_BITS(slot->key.bytes);
    }
#endif                                 /* defined(MBEDTLS_RSA_C) */
#if defined(MBEDTLS_ECP_C)
    else if (PSA_KEY_TYPE_IS_ECC(slot->attr.type))
    {
        bits = PSA_BYTES_TO_BITS(slot->key.bytes);
    }
#endif                                 /* defined(MBEDTLS_ECP_C) */
    else
    {
        bits = 0;
    }

    /* We know that the size fits in psa_key_bits_t thanks to checks
     * when the key was created. */
    return (psa_key_bits_t) bits;
}

/*************crypto_accel_driver.h implementations follow***************************/

/*
 * This function is based off of psa_generate_key_internal() in mbedCrypto.
 */
psa_status_t psa_generate_key_vendor (psa_key_slot_t                        * slot,
                                      size_t                                  bits,
                                      const psa_key_production_parameters_t * params,
                                      size_t                                  params_data_length)
{
    (void) slot;
    (void) bits;

    /* Only used for RSA */
    (void) params;
    (void) params_data_length;

    psa_status_t status = PSA_ERROR_NOT_SUPPORTED;

    if ((params == NULL) && (params_data_length != 0))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

#if defined(MBEDTLS_AES_ALT) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
    if (PSA_KEY_TYPE_IS_UNSTRUCTURED(slot->attr.type))
    {
        status = prepare_raw_data_slot_vendor(slot->attr.type, bits, &slot->key);
        if (status != PSA_SUCCESS)
        {
            return status;
        }

        status = psa_generate_symmetric_vendor(slot->attr.type, bits, slot->key.data, slot->key.bytes);
        if (status != PSA_SUCCESS)
        {
            return status;
        }
    }
    else
#endif                                 /* defined(MBEDTLS_AES_ALT) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT))) */
#if defined(MBEDTLS_RSA_C) && defined(MBEDTLS_RSA_ALT) && \
    ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_RSA_FORMAT)))
    if (PSA_KEY_TYPE_IS_RSA_KEY_PAIR_WRAPPED(slot->attr.type))
    {
        mbedtls_rsa_context * rsa;
        int      ret                   = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
        int      exponent              = 65537; // NOLINT(readability-magic-numbers)
        uint32_t export_der_size_bytes = 0;

        if (bits == RSA_1024_BITS)
        {
            export_der_size_bytes = RSA_WRAPPED_1024_EXPORTED_DER_SIZE_BYTES;
        }
        else if (bits == RSA_2048_BITS)
        {
            export_der_size_bytes = RSA_WRAPPED_2048_EXPORTED_DER_SIZE_BYTES;
        }
        else if (bits == RSA_3072_BITS)
        {
            export_der_size_bytes = RSA_WRAPPED_3072_EXPORTED_DER_SIZE_BYTES;
        }
        else if (bits == RSA_4096_BITS)
        {
            export_der_size_bytes = RSA_WRAPPED_4096_EXPORTED_DER_SIZE_BYTES;
        }
        else
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }

        /* Accept only byte - aligned keys, for the same reasons as *
         * in psa_import_rsa_key (). */
        if (bits % 8 != 0)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }

        if (params_data_length != 0)
        {
            status = psa_rsa_read_exponent(params->data, params_data_length, &exponent);
            if (status != PSA_SUCCESS)
            {
                return status;
            }
        }

        rsa = mbedtls_calloc(1, sizeof(*rsa));
        if (rsa == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }

        mbedtls_rsa_init(rsa);

        /* Setup the vendor context flag.
         * Even though vendor_ctx is a void pointer since we only need true/false info
         * we are using the pointer as a bool instead */
        rsa->vendor_ctx = (bool *) true;

        ret = mbedtls_rsa_gen_key(rsa, NULL, NULL, (unsigned int) bits, exponent);
        if (ret != 0)
        {
            mbedtls_rsa_free(rsa);
            mbedtls_free(rsa);

            return ret;
        }

        /* The key is stored in an export representation (DER format) in the slot.
         * Only RSA 2048 key generation is currently supported.
         * There is a check in the key generation stage above this that will succeed only for RSA 2048 case. */
        status = psa_allocate_buffer_to_slot(slot, export_der_size_bytes);
        if (status != PSA_SUCCESS)
        {
            mbedtls_rsa_free(rsa);
            mbedtls_free(rsa);

            return status;
        }

        status = mbedtls_psa_rsa_export_key(slot->attr.type,
                                            rsa,
                                            slot->key.data,
                                            export_der_size_bytes,
                                            &slot->key.bytes);
        mbedtls_rsa_free(rsa);
        mbedtls_free(rsa);

        if (status != PSA_SUCCESS)
        {
            psa_remove_key_data_from_memory(slot);
        }
    }
    else
#endif                                 /* defined(MBEDTLS_RSA_C) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_RSA_FORMAT))) */

#if defined(MBEDTLS_ECP_C) && defined(MBEDTLS_ECP_ALT) && \
    ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)))
    if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR_WRAPPED(slot->attr.type))
    {
        psa_ecc_family_t     curve     = PSA_KEY_TYPE_ECC_GET_FAMILY(slot->attr.type);
        uint32_t             ecc_bytes = 0;
        size_t               olen      = 0;
        mbedtls_ecp_group_id grp_id    =
            mbedtls_ecc_group_from_psa(curve, bits);
        const mbedtls_ecp_curve_info * curve_info =
            mbedtls_ecp_curve_info_from_grp_id(grp_id);
        mbedtls_ecp_keypair * ecp;
        int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
        if (params_data_length != 0)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }

        if ((grp_id == MBEDTLS_ECP_DP_NONE) || (curve_info == NULL))
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }

        ecp = mbedtls_calloc(1, sizeof(*ecp));
        if (ecp == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }

        mbedtls_ecp_keypair_init(ecp);
        ret = ecp_gen_key_vendor(grp_id, ecp);
        if (ret != 0)
        {
            mbedtls_ecp_keypair_free(ecp);
            mbedtls_free(ecp);

            return ret;
        }

        /* The key is stored in an export representation (DER format) in the slot. */
        ecc_bytes = RM_PSA_CRYPTO_ECC_KEY_WRAPPED_SIZE_BYTES(slot->attr.bits);
        status    = psa_allocate_buffer_to_slot(slot, ecc_bytes);
        if (status != PSA_SUCCESS)
        {
            mbedtls_ecp_keypair_free(ecp);
            mbedtls_free(ecp);

            return status;
        }

        status = mbedtls_to_psa_error(mbedtls_ecp_write_key_ext(ecp, &olen, slot->key.data, ecc_bytes));

        mbedtls_ecp_keypair_free(ecp);
        mbedtls_free(ecp);

        if (status != PSA_SUCCESS)
        {
            memset(slot->key.data, 0, ecc_bytes);
            psa_remove_key_data_from_memory(slot);
        }
    }
    else
#endif                                 /* MBEDTLS_ECP_C && MBEDTLS_ECP_ALT && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_RSA_FORMAT))) */
    {
        status = PSA_ERROR_NOT_SUPPORTED;
    }

    return status;                     // NOLINT(readability-misleading-indentation)
}

/** Import key data into a slot. `slot->attr.type` must have been set
 * previously. This function assumes that the slot does not contain
 * any key material yet. On failure, the slot content is unchanged. */
psa_status_t psa_import_key_into_slot_vendor (const psa_key_attributes_t * attributes,
                                              psa_key_slot_t             * slot,
                                              const uint8_t              * data,
                                              size_t                       data_length,
                                              mbedtls_svc_key_id_t       * key,
                                              bool                         write_to_persistent_memory)
{
    psa_status_t status = PSA_ERROR_NOT_SUPPORTED;
    size_t       bits   = slot->attr.bits;
    (void) slot;
    (void) data;
    (void) data_length;
    (void) key;
    FSP_PARAMETER_NOT_USED(attributes);

#if defined(MBEDTLS_AES_ALT) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
    if (PSA_KEY_TYPE_IS_UNSTRUCTURED(slot->attr.type))
    {
        size_t bit_size = PSA_BYTES_TO_BITS(data_length);

        /* Ensure that the bytes-to-bit conversion didn't overflow. */
        if (data_length > SIZE_MAX / 8)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }

        /* Enforce a size limit, and in particular ensure that the bit
         * size fits in its representation type. */
        if (bit_size > PSA_MAX_KEY_BITS)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }

        status = prepare_raw_data_slot_vendor(slot->attr.type, bit_size, &slot->key);
        if (status != PSA_SUCCESS)
        {
            return status;
        }

        if (data_length != 0)
        {
            memcpy(slot->key.data, data, data_length);
        }
    }
    else
#endif                                 /* defined(MBEDTLS_AES_ALT) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT))) */
#if defined(MBEDTLS_ECP_C) && defined(MBEDTLS_ECP_ALT) && \
    ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)))
    if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(slot->attr.type))
    {
        status = psa_allocate_buffer_to_slot(slot, data_length);

        if (status != PSA_SUCCESS)
        {
            return status;
        }

        status = mbedtls_psa_ecp_import_key(attributes,
                                            data,
                                            data_length,
                                            slot->key.data,
                                            slot->key.bytes,
                                            &slot->key.bytes,
                                            &bits);
    }
    else
#endif                                 /* MBEDTLS_ECP_C  && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT))) */

#if defined(MBEDTLS_RSA_C) && defined(MBEDTLS_RSA_ALT) && defined(MBEDTLS_PK_PARSE_C) && \
    ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_RSA_FORMAT)))
    if (PSA_KEY_TYPE_IS_RSA(slot->attr.type))
    {
        status = psa_allocate_buffer_to_slot(slot, data_length);

        if (status != PSA_SUCCESS)
        {
            return status;
        }

        status = mbedtls_psa_rsa_import_key(attributes,
                                            data,
                                            data_length,
                                            slot->key.data,
                                            slot->key.bytes,
                                            &slot->key.bytes,
                                            &bits);
    }
    else
#endif                                 /* defined(MBEDTLS_RSA_C) && defined(MBEDTLS_PK_PARSE_C) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_RSA_FORMAT))) */
    {
        status = PSA_ERROR_NOT_SUPPORTED;
    }

    if (status == PSA_SUCCESS)         // NOLINT(readability-misleading-indentation)
    {
        /* Enforce a size limit, and in particular ensure that the bit
         * size fits in its representation type.*/
        if (bits > PSA_MAX_KEY_BITS)
        {
            status = PSA_ERROR_NOT_SUPPORTED;
        }
        else
        {
            /* Write the actual key size to the slot.
             * psa_start_key_creation() wrote the size declared by the
             * caller, which may be 0 (meaning unspecified) or wrong. */
            slot->attr.bits = calculate_key_bits_vendor(slot);

            if (true == write_to_persistent_memory)
            {
                status = psa_finish_key_creation(slot, NULL, key);
            }
        }
    }

    return status;
}

/*
 * This function is based off of psa_finish_key_creation() in mbedCrypto.
 */

psa_status_t psa_finish_key_creation_vendor (psa_key_slot_t * slot)
{
    (void) slot;
    psa_status_t status = PSA_SUCCESS;
#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C)
    size_t buffer_size = 0;
 #if defined(MBEDTLS_AES_C) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))

    /* Check if the key is of AES type */
    if (PSA_KEY_TYPE_IS_AES(slot->attr.type))
    {
        buffer_size = slot->key.bytes;
    }
    else
 #endif                                // defined(MBEDTLS_AES_C) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
    {
        buffer_size = slot->key.bytes;
    }

    if (buffer_size == 0)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    uint8_t * buffer = mbedtls_calloc(1, buffer_size);
    size_t    length = 0;
    if (buffer == NULL)
    {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    psa_key_type_t type = slot->attr.type;

    if (PSA_KEY_TYPE_IS_UNSTRUCTURED(type) ||
        PSA_KEY_TYPE_IS_RSA(type) ||
        PSA_KEY_TYPE_IS_ECC(type))
    {
        status = psa_export_key_buffer_internal(slot->key.data, slot->key.bytes, buffer, buffer_size, &length);

        if (status == PSA_SUCCESS)
        {
            status = psa_save_persistent_key(&slot->attr, buffer, length);
        }
    }

    mbedtls_platform_zeroize(buffer, buffer_size);
    mbedtls_free(buffer);
#endif                                 // defined (MBEDTLS_PSA_CRYPTO_STORAGE_C)
    return status;
}
