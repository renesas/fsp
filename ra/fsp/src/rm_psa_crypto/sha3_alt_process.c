/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "common.h"

#if defined(MBEDTLS_SHA3_C)

 #include "mbedtls/sha3.h"
 #include "mbedtls/platform_util.h"
 #include "mbedtls/error.h"
 #include <string.h>

 #if defined(MBEDTLS_PLATFORM_C)
  #include "mbedtls/platform.h"
 #else
  #include <stdio.h>
  #include <stdlib.h>
  #define mbedtls_printf    printf
  #define mbedtls_calloc    calloc
  #define mbedtls_free      free
 #endif                                /* MBEDTLS_PLATFORM_C */

 #if defined(MBEDTLS_SHA3_PROCESS_ALT)
  #include "hw_sce_hash_private.h"

/*******************************************************************************************************************//**
 * @addtogroup RM_PSA_CRYPTO
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Uses the SCE to process the hash for len size of data and returns the result.
 *
 *
 * @retval 0                                       Hash calculation was successful.
 * @retval MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED    Hash calculation with the SCE failed
 **********************************************************************************************************************/
int mbedtls_internal_sha3_process_ext (mbedtls_sha3_context * ctx,
                                       const unsigned char data[SIZE_MBEDTLS_SHA3_PROCESS_BUFFER_BYTES], uint32_t len)
{
  #if BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED
    uint32_t   out_data[SIZE_MBEDTLS_SHA3_OUTPUT_BUFFER_BYTES / 4] = {0}; /* Buffer for output (sufficient for SHA3-512) */
    uint32_t * outbuff_digest_ptr = out_data;
    uint32_t   sce_hash_type[1];
    uint32_t   sce_hash_cmd[1] = {((uint32_t) ctx->sce_operation_state)};
    uint32_t   InData_MsgLen[2];

    for (uint32_t i = 0; i < len; i += 4)
    {
        MBEDTLS_PUT_UINT32_BE(*(uint32_t *) &data[i], (unsigned char *) &data[i], 0);
    }

    /* Determine SHA3 variant based on output length */
    switch (ctx->sha3_type)
    {
        case MBEDTLS_SHA3_224:
        {
            sce_hash_type[0] = change_endian_long((uint32_t) SCE_OEM_CMD_HASH_TYPE_SHA3_224);
            break;
        }

        case MBEDTLS_SHA3_256:
        {
            sce_hash_type[0] = change_endian_long((uint32_t) SCE_OEM_CMD_HASH_TYPE_SHA3_256);
            break;
        }

        case MBEDTLS_SHA3_384:
        {
            sce_hash_type[0] = change_endian_long((uint32_t) SCE_OEM_CMD_HASH_TYPE_SHA3_384);
            break;
        }

        case MBEDTLS_SHA3_512:
        {
            sce_hash_type[0] = change_endian_long((uint32_t) SCE_OEM_CMD_HASH_TYPE_SHA3_512);
            break;
        }

        default:

            return MBEDTLS_ERR_SHA3_BAD_INPUT_DATA;
    }

    if (SCE_OEM_CMD_HASH_INIT_TO_SUSPEND == ctx->sce_operation_state)
    {
        ctx->sce_operation_state = SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND;
        InData_MsgLen[0]         = r_sce_byte_to_bit_convert_upper(ctx->total[0]);
        InData_MsgLen[1]         = r_sce_byte_to_bit_convert_lower(ctx->total[0]);
        if (FSP_SUCCESS !=
            HW_SCE_Sha3GenerateMessageDigestSubAdaptor(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0],
                                                       InData_MsgLen, (uint32_t *) &ctx->state[0], outbuff_digest_ptr,
                                                       (uint32_t *) &ctx->rsip_internal_state[0],
                                                       BYTES_TO_WORDS(len)))
        {
            return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
        }
    }
    else if (SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND == ctx->sce_operation_state)
    {
        if (FSP_SUCCESS !=
            HW_SCE_Sha3GenerateMessageDigestSubAdaptor(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0], NULL,
                                                       (uint32_t *) &ctx->rsip_internal_state[0], outbuff_digest_ptr,
                                                       (uint32_t *) &ctx->rsip_internal_state[0],
                                                       BYTES_TO_WORDS(len)))
        {
            return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
        }
    }
    else if (SCE_OEM_CMD_HASH_RESUME_TO_FINAL == ctx->sce_operation_state)
    {
        if (FSP_SUCCESS !=
            HW_SCE_Sha3GenerateMessageDigestSubAdaptor(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0], NULL,
                                                       (uint32_t *) &ctx->rsip_internal_state[0], outbuff_digest_ptr,
                                                       (uint32_t *) &ctx->rsip_internal_state[0],
                                                       BYTES_TO_WORDS(len)))
        {
            return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
        }

        /* Copy digest to state */
        memcpy(&ctx->state[0], out_data, ctx->olen);
    }
    else
    {
        /* One-shot case */
        InData_MsgLen[0] = r_sce_byte_to_bit_convert_upper(ctx->total[0]);
        InData_MsgLen[1] = r_sce_byte_to_bit_convert_lower(ctx->total[0]);

        if (FSP_SUCCESS !=
            HW_SCE_Sha3GenerateMessageDigestSubAdaptor(sce_hash_type, sce_hash_cmd, (uint32_t const *) &data[0],
                                                       InData_MsgLen, &ctx->rsip_internal_state[0], outbuff_digest_ptr,
                                                       &ctx->rsip_internal_state[0],
                                                       BYTES_TO_WORDS(len)))

        {
            return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
        }

        /* Copy digest to state */
        memcpy(&ctx->state[0], out_data, ctx->olen);
    }

    return 0;
  #else
    (void) ctx;
    (void) data;
    (void) len;

    return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
  #endif
}

 #endif                                /* MBEDTLS_SHA3_PROCESS_ALT */
#endif                                 /* MBEDTLS_SHA3_C */
