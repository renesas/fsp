/**
 * \file gcm_alt.h
 *
 * \brief This file contains GCM ALT definitions and functions.
 *
 * The Galois/Counter Mode (GCM) for 128-bit block ciphers is defined
 * in <em>D. McGrew, J. Viega, The Galois/Counter Mode of Operation
 * (GCM), Natl. Inst. Stand. Technol.</em>
 *
 * For more information on GCM, see <em>NIST SP 800-38D: Recommendation for
 * Block Cipher Modes of Operation: Galois/Counter Mode (GCM) and GMAC</em>.
 *
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

#ifndef MBEDTLS_GCM_ALT_H
 #define MBEDTLS_GCM_ALT_H

 #if !defined(MBEDTLS_CONFIG_FILE)
  #include "mbedtls/config.h"
 #else
  #include MBEDTLS_CONFIG_FILE
 #endif

 #include "mbedtls/cipher.h"

 #include <stdint.h>

 #ifdef __cplusplus
extern "C" {
 #endif

/**
 * \brief          The GCM context structure.
 */
typedef struct mbedtls_gcm_context
{
    mbedtls_cipher_context_t cipher_ctx;    /*!< The cipher context used. */
    uint64_t                 HL[16];        /*!< Precalculated HTable low. */
    uint64_t                 HH[16];        /*!< Precalculated HTable high. */
    uint64_t                 len;           /*!< The total length of the encrypted data. */
    uint64_t                 add_len;       /*!< The total length of the additional data. */
    unsigned char            base_ectr[16]; /*!< The first ECTR for tag. */
    unsigned char            y[16];         /*!< The Y working value. */
    unsigned char            buf[16];       /*!< The buf working value. */
    int mode;                               /*!< The operation to perform:
                                             * MBEDTLS_GCM_ENCRYPT or
                                             * MBEDTLS_GCM_DECRYPT. */
} mbedtls_gcm_context;

 #define RM_PSA_CRYPTO_AES_LOOKUP_INDEX(bits)    (((bits) >> 6) - 2U)

int sce_gcm_crypt_and_tag(mbedtls_gcm_context * ctx,
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

#endif                                 /* gcm_alt.h */
