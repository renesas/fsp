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

 #include "common.h"

 #include "mbedtls/cipher.h"
 
 #include "psa/crypto_types.h"

 #include "hw_sce_ra_private.h"

 #include <stdint.h>

 #ifdef __cplusplus
extern "C" {
 #endif

#if defined(MBEDTLS_GCM_LARGE_TABLE)
#define MBEDTLS_GCM_HTABLE_SIZE 256
#else
#define MBEDTLS_GCM_HTABLE_SIZE 16
#endif

/* HW multi-part GCM session state (see the sce_gcm_* functions in gcm_alt_process.c). */
typedef enum e_sce_mbedtls_gcm_operation_state
{
    SCE_MBEDTLS_GCM_OPERATION_STATE_IDLE = 0,   /*!< No HW GCM session open.            */
    SCE_MBEDTLS_GCM_OPERATION_STATE_AAD,        /*!< Session open, absorbing AAD.       */
    SCE_MBEDTLS_GCM_OPERATION_STATE_TEXT        /*!< Session open, processing text.     */
} sce_mbedtls_gcm_operation_state_t;

/**
 * \brief          The GCM context structure.
 */
typedef struct mbedtls_gcm_context
{
#if defined(MBEDTLS_BLOCK_CIPHER_C)
    mbedtls_block_cipher_context_t MBEDTLS_PRIVATE(block_cipher_ctx);  /*!< The cipher context used. */
#else
    mbedtls_cipher_context_t MBEDTLS_PRIVATE(cipher_ctx);    /*!< The cipher context used. */
#endif
    uint64_t MBEDTLS_PRIVATE(H)[MBEDTLS_GCM_HTABLE_SIZE][2]; /*!< Precalculated HTable. */
    uint64_t MBEDTLS_PRIVATE(len);                           /*!< The total length of the encrypted data. */
    uint64_t MBEDTLS_PRIVATE(add_len);                       /*!< The total length of the additional data. */
    unsigned char MBEDTLS_PRIVATE(base_ectr)[16];            /*!< The first ECTR for tag. */
    unsigned char MBEDTLS_PRIVATE(y)[16];                    /*!< The Y working value. */
    unsigned char MBEDTLS_PRIVATE(buf)[16];                  /*!< The buf working value. */
    unsigned char MBEDTLS_PRIVATE(mode);                     /*!< The operation to perform:
                                                              MBEDTLS_GCM_ENCRYPT or
                                                              MBEDTLS_GCM_DECRYPT. */
    unsigned char MBEDTLS_PRIVATE(acceleration);             /*!< The acceleration to use. */
	bool vendor_flag;
	sce_mbedtls_gcm_operation_state_t sce_stage; /*!< HW multi-part session state.     */
	unsigned char sce_buf_len;   /*!< HW multi-part: bytes staged in buf[] (0..15). */
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

/* HW-accelerated multi-part AES-GCM (held-open SCE session). */
int  sce_gcm_starts(mbedtls_gcm_context * ctx, int mode,
                    const unsigned char * iv, size_t iv_len);
int  sce_gcm_update_ad(mbedtls_gcm_context * ctx,
                       const unsigned char * add, size_t add_len);
int  sce_gcm_update(mbedtls_gcm_context * ctx,
                    const unsigned char * input, size_t input_length,
                    unsigned char * output, size_t output_size, size_t * output_length);
int  sce_gcm_finish(mbedtls_gcm_context * ctx,
                    unsigned char * output, size_t output_size, size_t * output_length,
                    unsigned char * tag, size_t tag_len);
/* Decrypt verify: feeds the expected_tag to the HW DecryptFinal (which verifies internally).
 * Returns 0 on auth success, MBEDTLS_ERR_GCM_AUTH_FAILED on mismatch. */
int  sce_gcm_verify(mbedtls_gcm_context * ctx,
                    unsigned char * output, size_t output_size, size_t * output_length,
                    const unsigned char * expected_tag, size_t tag_len);
void sce_gcm_free_session(mbedtls_gcm_context * ctx);

 #ifdef __cplusplus
}
 #endif
 
 /* Functions to support vendor defined format */
psa_status_t vendor_bitlength_to_raw_bitlength(psa_key_type_t type, size_t vendor_bits, size_t * raw_bits);

void psa_aead_setup_vendor (void * ctx);

#endif                                 /* gcm_alt.h */
