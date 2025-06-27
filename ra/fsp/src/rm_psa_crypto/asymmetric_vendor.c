/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#include "common.h"

#if defined(MBEDTLS_PSA_CRYPTO_ACCEL_DRV_C)
 #include "asymmetric_vendor.h"
 #include "mbedtls/psa_util.h"

 #if defined(MBEDTLS_ECP_C)

  #if (defined(MBEDTLS_ECP_ALT)) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)))

/* Generate an ECP keypair in vendor defined format. */
int ecp_gen_key_vendor (mbedtls_ecp_group_id grp_id, mbedtls_ecp_keypair * key)
{
    int ret;

    if (key == NULL)
    {
        return MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
    }

    ret = mbedtls_ecp_group_load(&key->grp, grp_id);
    if (ret != 0)
    {
        return ret;
    }

/* Setup the vendor context flag.
 * Even though vendor_ctx is a void pointer since we only need true/false info
 * we are using the pointer as a bool instead */
    key->grp.vendor_ctx = (bool *) true;

    ret = mbedtls_ecp_gen_privkey(&key->grp, &key->d, NULL, NULL);

    if (!ret)
    {
        ret = mbedtls_ecp_mul(&key->grp, &key->Q, &key->d, &key->grp.G, NULL, NULL);
    }

    return ret;
}

/* Import a private key given as a byte string which is the private value
 * in big-endian order. */

psa_status_t psa_import_ec_private_key_vendor (psa_ecc_family_t       curve,
                                               const uint8_t        * data,
                                               size_t                 data_length,
                                               mbedtls_ecp_keypair ** p_ecp)
{
    psa_status_t          status = PSA_ERROR_CORRUPTION_DETECTED;
    mbedtls_ecp_keypair * ecp    = NULL;
    size_t                curve_bits;

    curve_bits = PSA_BYTES_TO_BITS(PSA_ECC_BYTES_VENDOR_RAW(data_length));
    mbedtls_ecp_group_id grp_id =
        mbedtls_ecc_group_from_psa(curve, curve_bits);

    *p_ecp = NULL;
    ecp    = mbedtls_calloc(1, sizeof(mbedtls_ecp_keypair));
    if (ecp == NULL)
    {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    mbedtls_ecp_keypair_init(ecp);

    /* Load the group. */
    status = mbedtls_to_psa_error(mbedtls_ecp_group_load(&ecp->grp, grp_id));
    if (status != PSA_SUCCESS)
    {
        goto exit;
    }

    /* Load the secret value. */
    status = mbedtls_to_psa_error(mbedtls_mpi_read_binary(&ecp->d, data, data_length));
    if (status != PSA_SUCCESS)
    {
        goto exit;
    }

    /* Validate the private key not done since we cannot validate the HW genenerated wrapped key. */

/* Setup the vendor context flag.
 * Even though vendor_ctx is a void pointer since we only need true/false info
 * we are using the pointer as a bool instead */
    ecp->grp.vendor_ctx = (bool *) true;

    /* Calculate the public key from the private key. */
    status =
        mbedtls_to_psa_error(mbedtls_ecp_mul(&ecp->grp, &ecp->Q, &ecp->d, &ecp->grp.G, NULL, NULL));
    if (status != PSA_SUCCESS)
    {
        goto exit;
    }

    *p_ecp = ecp;

    return PSA_SUCCESS;

exit:
    if (ecp != NULL)
    {
        mbedtls_ecp_keypair_free(ecp);
        mbedtls_free(ecp);
    }

    return status;
}

  #endif                               /* (defined(MBEDTLS_ECP_ALT)) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT))) */

 #endif /* MBEDTLS_ECP_C */

#endif                                 /* MBEDTLS_PSA_CRYPTO_ACCEL_DRV_C */
