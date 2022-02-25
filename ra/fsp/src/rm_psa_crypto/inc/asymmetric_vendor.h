/**
 * \file ecp_alt.h
 *
 * \brief This file contains RSA Alternate definitions and functions.
 */

/*
 *  Copyright (C) 2006-2018, Arm Limited (or its affiliates), All Rights Reserved
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
 *  This file is part of Mbed TLS (https://tls.mbed.org)
 */
#ifndef ASYMMETRIC_VENDOR_H
#define ASYMMETRIC_VENDOR_H

#include "vendor.h"
#include "mbedtls/ecdsa.h"
#include "mbedtls/ecp.h"
#include "mbedtls/rsa.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

psa_status_t psa_remove_key_data_from_memory(psa_key_slot_t * slot);
psa_status_t psa_allocate_buffer_to_slot(psa_key_slot_t * slot, size_t buffer_length);

#if defined(MBEDTLS_ECP_ALT)
 #include "hw_sce_ecc_private.h"

/** Standard bit length to vendor type bit length translation.
 *
 * \param bit_length     Vendor bit length
 *
 * \return          Equivalent standard bit length.
 */

 #define PSA_ECC_BYTES_VENDOR_RAW(bit_length)                                                                      \
    ((bit_length) ==                                                                                               \
     PSA_BITS_TO_BYTES(ECC_256_PRIVATE_KEY_HRK_LENGTH_BITS) ? PSA_BITS_TO_BYTES(ECC_256_PRIVATE_KEY_LENGTH_BITS) : \
     (bit_length) ==                                                                                               \
     PSA_BITS_TO_BYTES(ECC_384_PRIVATE_KEY_HRK_LENGTH_BITS) ? PSA_BITS_TO_BYTES(ECC_384_PRIVATE_KEY_LENGTH_BITS) : \
     0)

/* Functions used directly from mbedCrypto */
mbedtls_ecp_group_id mbedtls_ecc_group_of_psa(psa_ecc_family_t curve, size_t byte_length);
psa_status_t         psa_import_ec_public_key(psa_ecc_family_t       curve,
                                              const uint8_t        * data,
                                              size_t                 data_length,
                                              mbedtls_ecp_keypair ** p_ecp);
psa_status_t psa_ecdsa_sign(mbedtls_ecp_keypair * ecp,
                            psa_algorithm_t       alg,
                            const uint8_t       * hash,
                            size_t                hash_length,
                            uint8_t             * signature,
                            size_t                signature_size,
                            size_t              * signature_length);
psa_status_t psa_ecdsa_verify(mbedtls_ecp_keypair * ecp,
                              const uint8_t       * hash,
                              size_t                hash_length,
                              const uint8_t       * signature,
                              size_t                signature_length);

/* Functions to support vendor defined format */
psa_status_t psa_import_ec_private_key_vendor(psa_ecc_family_t       curve,
                                              const uint8_t        * data,
                                              size_t                 data_length,
                                              mbedtls_ecp_keypair ** p_ecp);

/**
 * \brief           This function generates an ECP key in vendor format.
 *
 * \param grp_id    The ECP group identifier.
 * \param key       The destination key. This must be initialized.
 *
 * \return          \c 0 on success.
 * \return          An \c MBEDTLS_ERR_ECP_XXX or \c MBEDTLS_MPI_XXX error code
 *                  on failure.
 */
int ecp_gen_key_vendor(mbedtls_ecp_group_id grp_id, mbedtls_ecp_keypair * key);

psa_status_t psa_import_ecp_key(psa_key_slot_t * slot, const uint8_t * data, size_t data_length);
psa_status_t psa_export_ecp_key(psa_key_type_t        type,
                                mbedtls_ecp_keypair * ecp,
                                uint8_t             * data,
                                size_t                data_size,
                                size_t              * data_length);

#endif                                 /* MBEDTLS_ECP_ALT */

#if defined(MBEDTLS_RSA_ALT)
psa_status_t psa_export_rsa_key(psa_key_type_t        type,
                                mbedtls_rsa_context * rsa,
                                uint8_t             * data,
                                size_t                data_size,
                                size_t              * data_length);
psa_status_t psa_import_rsa_key(psa_key_slot_t * slot, const uint8_t * data, size_t data_length);
psa_status_t psa_read_rsa_exponent(const uint8_t * domain_parameters, size_t domain_parameters_size, int * exponent);
psa_status_t psa_rsa_sign(mbedtls_rsa_context * rsa,
                          psa_algorithm_t       alg,
                          const uint8_t       * hash,
                          size_t                hash_length,
                          uint8_t             * signature,
                          size_t                signature_size,
                          size_t              * signature_length);
psa_status_t psa_rsa_verify(mbedtls_rsa_context * rsa,
                            psa_algorithm_t       alg,
                            const uint8_t       * hash,
                            size_t                hash_length,
                            const uint8_t       * signature,
                            size_t                signature_length);

#endif                                 /* MBEDTLS_RSA_ALT */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* ASYMMETRIC_VENDOR_H */
