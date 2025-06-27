/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#ifndef MBEDTLS_SHA3_ALT_H
 #define MBEDTLS_SHA3_ALT_H

 #include "common.h"
 #include "r_sce_if.h"

 #include <stddef.h>
 #include <stdint.h>

 #ifdef __cplusplus
extern "C" {
 #endif

 #define SIZE_MBEDTLS_SHA3_PROCESS_BUFFER_BYTES    144U
 #define SIZE_MBEDTLS_SHA3_OUTPUT_BUFFER_BYTES     64U

/**
 * \brief          The SHA-3 context structure.
 *
 *                 The structure is used SHA-3 checksum calculations.
 */
typedef struct
{
    uint64_t        state[25];                                         /*!< The intermediate digest state. */
    uint32_t        index;                                             /*!< Current position within the buffer. */
    uint16_t        olen;                                              /*!< Output length in bytes. */
    uint16_t        max_block_size;                                    /*!< Block size in bytes. */
    mbedtls_sha3_id sha3_type;                                         /*!< Type of SHA-3 operation. */
    uint32_t        total[2];                                          /*!< The number of bytes processed. */
    sce_hash_cmd_t  sce_operation_state;                               /*!< Current SCE operation state. */
 #if BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED
    uint32_t      rsip_internal_state[52];                             /*!< RSIP specific state array. */
    unsigned char rsip_buffer[SIZE_MBEDTLS_SHA3_PROCESS_BUFFER_BYTES]; /*!< Buffered data for RSIP procedure (max SHA3 rate is 200 bytes). */
    uint32_t      use_rsip_buffer;                                     /*!< Used to indicate if the rsip_buffer is to be used or not. */
    uint32_t      rsip_buffer_processed;                               /*!< Used to indicate if the rsip_buffer data is processed or not. */
 #endif
    unsigned char buffer[SIZE_MBEDTLS_SHA3_PROCESS_BUFFER_BYTES];      /*!< The data block being processed. */
} mbedtls_sha3_context;

int mbedtls_internal_sha3_process_ext(mbedtls_sha3_context * ctx,
                                      const unsigned char data[SIZE_MBEDTLS_SHA3_PROCESS_BUFFER_BYTES], uint32_t len);

 #ifdef __cplusplus
}
 #endif

#endif
