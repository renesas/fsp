/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#ifndef MBEDTLS_SHA512_ALT_H
 #define MBEDTLS_SHA512_ALT_H

 #include "common.h"
 #include "r_sce_if.h"

 #include <stddef.h>
 #include <stdint.h>

 #ifdef __cplusplus
extern "C" {
 #endif

 #define SIZE_MBEDTLS_SHA512_PROCESS_BUFFER_BYTES    128U

/**
 * \brief          The SHA-512 context structure.
 *
 *                 The structure is used both for SHA-512 and for SHA-224
 *                 checksum calculations. The choice between these two is
 *                 made in the call to mbedtls_sha512_starts_ret().
 */
typedef struct mbedtls_sha512_context
{
    uint64_t      total[2];                                              /*!< The number of Bytes processed.  */
    uint64_t      state[8];                                              /*!< The intermediate digest state.  */
    unsigned char buffer[SIZE_MBEDTLS_SHA512_PROCESS_BUFFER_BYTES];      /*!< The data block being processed. */
    int           is384;                                                 /*!< Determines which function to use:
                                                                          * 0: Use SHA-512, or 1: Use SHA-384. */
    uint32_t       used;                                                 // Used to indicate if the final block has user data or only padding
    sce_hash_cmd_t sce_operation_state;
 #if BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || \
    BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED
    uint32_t      rsip_internal_state[20];                               // RSIP specific state array
    unsigned char rsip_buffer[SIZE_MBEDTLS_SHA512_PROCESS_BUFFER_BYTES]; /*!< buffered data for RSIP procedure. */
    uint32_t      use_rsip_buffer;                                       // Used to indicate if the rsip_buffer is to be used or not
    uint32_t      rsip_buffer_processed;                                 // Used to indicate if the rsip_buffer data is processed or not
 #endif
} mbedtls_sha512_context;

int mbedtls_internal_sha512_process_ext(mbedtls_sha512_context * ctx,
                                        const unsigned char      data[SIZE_MBEDTLS_SHA512_PROCESS_BUFFER_BYTES],
                                        uint32_t                 len);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* mbedtls_sha512.h */
