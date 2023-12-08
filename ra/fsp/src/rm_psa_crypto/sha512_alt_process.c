/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#include "common.h"

#if defined(MBEDTLS_SHA512_C)

 #include "mbedtls/sha512.h"
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

 #if defined(MBEDTLS_SHA512_PROCESS_ALT)
  #include "hw_sce_hash_private.h"

  #define SHA512_VALIDATE_RET(cond)     \
    MBEDTLS_INTERNAL_VALIDATE_RET(cond, \
                                  MBEDTLS_ERR_SHA512_BAD_INPUT_DATA)

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
int mbedtls_internal_sha512_process_ext (mbedtls_sha512_context * ctx,
                                         const unsigned char      data[SIZE_MBEDTLS_SHA512_PROCESS_BUFFER_BYTES],
                                         uint32_t                 len)
{
    SHA512_VALIDATE_RET(ctx != NULL);
    SHA512_VALIDATE_RET((const unsigned char *) data != NULL);
    uint32_t   out_data[HW_SCE_SHA512_HASH_STATE_BUFFER_SIZE] = {0};
    uint32_t * outbuff_digest_ptr = out_data;
    uint32_t   sce_hash_type[1];
    uint32_t   sce_hash_cmd[1] = {change_endian_long((uint32_t) ctx->sce_operation_state)};
    uint32_t   InData_MsgLen[2];

    if (1 == ctx->is384)
    {
        sce_hash_type[0] = change_endian_long((uint32_t) SCE_OEM_CMD_HASH_TYPE_SHA384);
    }
    else
    {
        sce_hash_type[0] = change_endian_long((uint32_t) SCE_OEM_CMD_HASH_TYPE_SHA512);
    }

    if (SCE_OEM_CMD_HASH_INIT_TO_SUSPEND == ctx->sce_operation_state)
    {
        ctx->sce_operation_state     = SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND;
        ctx->rsip_internal_state[18] = change_endian_long((uint32_t) HW_SCE_LARGE_DATA_VALUE_0);
        ctx->rsip_internal_state[19] = change_endian_long((uint32_t) HW_SCE_LARGE_DATA_VALUE_1);

        if (FSP_SUCCESS !=
            HW_SCE_ShaGenerateMessageDigestSub(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0],
                                               &ctx->rsip_internal_state[18], &ctx->rsip_internal_state[0],
                                               outbuff_digest_ptr, &ctx->rsip_internal_state[0],
                                               BYTES_TO_WORDS(len)))
        {
            return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
        }
    }
    else if (SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND == ctx->sce_operation_state)
    {
        if (FSP_SUCCESS !=
            HW_SCE_ShaGenerateMessageDigestSub(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0], NULL,
                                               &ctx->rsip_internal_state[0], outbuff_digest_ptr,
                                               &ctx->rsip_internal_state[0], BYTES_TO_WORDS(len)))
        {
            return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
        }
    }
    else if (SCE_OEM_CMD_HASH_RESUME_TO_FINAL == ctx->sce_operation_state)
    {
        ctx->rsip_internal_state[16] = r_sce_byte_to_bit_convert_lower(ctx->total[0]);
        ctx->rsip_internal_state[17] = r_sce_byte_to_bit_convert_upper(ctx->total[0]);
        ctx->rsip_internal_state[18] = r_sce_byte_to_bit_convert_upper(len);
        ctx->rsip_internal_state[19] = r_sce_byte_to_bit_convert_lower(len);

        if (FSP_SUCCESS !=
            HW_SCE_ShaGenerateMessageDigestSub(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0], NULL,
                                               &ctx->rsip_internal_state[0], outbuff_digest_ptr,
                                               &ctx->rsip_internal_state[0], BYTES_TO_WORDS(len)))
        {
            return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
        }

        memcpy(&ctx->state[0], out_data, HW_SCE_SHA512_HASH_LENGTH_BYTE_SIZE);
    }
    else
    {
        /* One-shot case. */
        InData_MsgLen[0] = r_sce_byte_to_bit_convert_upper(ctx->total[0]);
        InData_MsgLen[1] = r_sce_byte_to_bit_convert_lower(ctx->total[0]);

        if (FSP_SUCCESS !=
            HW_SCE_ShaGenerateMessageDigestSub(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0], InData_MsgLen,
                                               &ctx->rsip_internal_state[0], outbuff_digest_ptr,
                                               &ctx->rsip_internal_state[0], BYTES_TO_WORDS(len)))
        {
            return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
        }

        memcpy(&ctx->state[0], out_data, HW_SCE_SHA512_HASH_LENGTH_BYTE_SIZE);
    }

    return 0;
}

 #endif                                /* MBEDTLS_SHA512_PROCESS_ALT */
#endif                                 /* MBEDTLS_SHA512_C */
