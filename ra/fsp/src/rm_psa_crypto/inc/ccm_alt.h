/**
 * \file ccm_alt.h
 *
 * \brief This file provides an API for the CCM ALT authenticated encryption
 *        mode for block ciphers.
 *
 * CCM combines Counter mode encryption with CBC-MAC authentication
 * for 128-bit block ciphers.
 *
 * Input to CCM includes the following elements:
 * <ul><li>Payload - data that is both authenticated and encrypted.</li>
 * <li>Associated data (Adata) - data that is authenticated but not
 * encrypted, For example, a header.</li>
 * <li>Nonce - A unique value that is assigned to the payload and the
 * associated data.</li></ul>
 *
 * Definition of CCM:
 * http://csrc.nist.gov/publications/nistpubs/800-38C/SP800-38C_updated-July20_2007.pdf
 * RFC 3610 "Counter with CBC-MAC (CCM)"
 *
 * Related:
 * RFC 5116 "An Interface and Algorithms for Authenticated Encryption"
 *
 * Definition of CCM*:
 * IEEE 802.15.4 - IEEE Standard for Local and metropolitan area networks
 * Integer representation is fixed most-significant-octet-first order and
 * the representation of octets is most-significant-bit-first order. This is
 * consistent with RFC 3610.
 */
/*
 *  Copyright The Mbed TLS Contributors
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
 */

#ifndef MBEDTLS_CCM_ALT_H
#define MBEDTLS_CCM_ALT_H
#include "mbedtls/private_access.h"

#include "mbedtls/build_info.h"

#include "mbedtls/cipher.h"

#include "psa/crypto_types.h"

#include "hw_sce_ra_private.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief    The CCM context-type definition. The CCM context is passed
 *           to the APIs called.
 */
typedef struct mbedtls_ccm_context
{
    unsigned char MBEDTLS_PRIVATE(y)[16];    /*!< The Y working buffer */
    unsigned char MBEDTLS_PRIVATE(ctr)[16];  /*!< The counter buffer */
    mbedtls_cipher_context_t MBEDTLS_PRIVATE(cipher_ctx);    /*!< The cipher context used. */
    size_t MBEDTLS_PRIVATE(plaintext_len);   /*!< Total plaintext length */
    size_t MBEDTLS_PRIVATE(add_len);         /*!< Total authentication data length */
    size_t MBEDTLS_PRIVATE(tag_len);         /*!< Total tag length */
    size_t MBEDTLS_PRIVATE(processed);       /*!< Track how many bytes of input data
                                                  were processed (chunked input).
                                                  Used independently for both auth data
                                                  and plaintext/ciphertext.
                                                  This variable is set to zero after
                                                  auth data input is finished. */
    unsigned char MBEDTLS_PRIVATE(q);        /*!< The Q working value */
    unsigned char MBEDTLS_PRIVATE(mode);     /*!< The operation to perform:
                                              * MBEDTLS_CCM_ENCRYPT or
                                              * MBEDTLS_CCM_DECRYPT or
                                              * MBEDTLS_CCM_STAR_ENCRYPT or
                                              * MBEDTLS_CCM_STAR_DECRYPT. */
    int MBEDTLS_PRIVATE(state);              /*!< Working value holding context's
                                                  state. Used for chunked data
                                                  input */
    bool vendor_flag;
}
mbedtls_ccm_context;

 #define RM_PSA_CRYPTO_AES_LOOKUP_INDEX(bits)    (((bits) >> 6) - 2U)

int sce_ccm_crypt_and_tag(mbedtls_ccm_context * ctx,
                          int                   mode,
                          size_t                length,
                          const unsigned char * iv,
                          size_t                iv_len,
                          const unsigned char * aad,
                          size_t                aad_len,
                          const unsigned char * input,
                          unsigned char       * output,
                          size_t                tag_len,
                          unsigned char       * tag);


#ifdef __cplusplus
}
#endif

/* Functions to support vendor defined format */
psa_status_t vendor_bitlength_to_raw_bitlength(psa_key_type_t type, size_t vendor_bits, size_t * raw_bits);

void psa_aead_setup_vendor (void * ctx);

#endif /* MBEDTLS_CCM_ALT_H */
