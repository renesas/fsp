/**
 * \file cmac_alt.h
 *
 * \brief This file contains CMAC definitions and functions.
 *
 * The Cipher-based Message Authentication Code (CMAC) Mode for
 * Authentication is defined in <em>RFC-4493: The AES-CMAC Algorithm</em>.
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

#ifndef MBEDTLS_CMAC_ALT_H
#define MBEDTLS_CMAC_ALT_H
#include "mbedtls/private_access.h"

#include "mbedtls/build_info.h"

#include "mbedtls/cipher.h"

#ifdef __cplusplus
extern "C" {
#endif


#if defined(MBEDTLS_CMAC_ALT)

#define RM_PSA_CRYPTO_CMAC_LOOKUP_INDEX(bits)    ((bits) - 2U)

typedef enum e_sce_mbedtls_cmac_operation_state
{
    SCE_MBEDTLS_CMAC_OPERATION_STATE_INIT = 0,
    SCE_MBEDTLS_CMAC_OPERATION_STATE_UPDATE
} sce_mbedtls_cmac_operation_state_t;

/**
 * The CMAC context structure.
 */
struct mbedtls_cmac_context_t
{
    /** The internal state of the CMAC algorithm.  */
    unsigned char       MBEDTLS_PRIVATE(state)[MBEDTLS_CIPHER_BLKSIZE_MAX];

    /** Unprocessed data - either data that was not block aligned and is still
     *  pending processing, or the final block. */
    unsigned char       MBEDTLS_PRIVATE(unprocessed_block)[MBEDTLS_CIPHER_BLKSIZE_MAX];

    /** The length of data pending processing. */
    size_t              MBEDTLS_PRIVATE(unprocessed_len);
    
	sce_mbedtls_cmac_operation_state_t       MBEDTLS_PRIVATE(vendor_state);

};

#endif  /* MBEDTLS_CMAC_ALT */


#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_CMAC_ALT_H */
