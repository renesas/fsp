/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#if !defined(MBEDTLS_CONFIG_FILE)
 #include "mbedtls/config.h"
#else
 #include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_SHA256_C)

 #include "mbedtls/sha256.h"
 #include "mbedtls/platform_util.h"

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

 #define SHA256_VALIDATE_RET(cond) \
    MBEDTLS_INTERNAL_VALIDATE_RET(cond, MBEDTLS_ERR_SHA256_BAD_INPUT_DATA)
 #define SHA256_VALIDATE(cond)    MBEDTLS_INTERNAL_VALIDATE(cond)

 #if defined(MBEDTLS_SHA256_PROCESS_ALT)
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
int mbedtls_internal_sha256_process_ext (mbedtls_sha256_context * ctx,
                                         const unsigned char      data[SIZE_MBEDTLS_SHA256_PROCESS_BUFFER_BYTES],
                                         uint32_t                 len)
{
    SHA256_VALIDATE_RET(ctx != NULL);
    SHA256_VALIDATE_RET((const unsigned char *) data != NULL);

    if (FSP_SUCCESS !=
        HW_SCE_SHA256_UpdateHash((const uint32_t *) &data[0], BYTES_TO_WORDS(len), &ctx->state[0]))
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return 0;
}

/*******************************************************************************************************************//**
 * Uses the SCE to process the hash for SIZE_MBEDTLS_SHA256_PROCESS_BUFFER_BYTES bytes of data and returns the result.
 *
 *
 * @retval 0                                       Hash calculation was successful.
 * @retval MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED    Hash calculation with the SCE failed
 **********************************************************************************************************************/

int mbedtls_internal_sha256_process (mbedtls_sha256_context * ctx,
                                     const unsigned char      data[SIZE_MBEDTLS_SHA256_PROCESS_BUFFER_BYTES])
{
    SHA256_VALIDATE_RET(ctx != NULL);
    SHA256_VALIDATE_RET((const unsigned char *) data != NULL);

    if (FSP_SUCCESS !=
        HW_SCE_SHA256_UpdateHash((const uint32_t *) &data[0], BYTES_TO_WORDS(SIZE_MBEDTLS_SHA256_PROCESS_BUFFER_BYTES),
                                 &ctx->state[0]))
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return 0;
}

  #if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_sha256_process (mbedtls_sha256_context * ctx,
                             const unsigned char      data[SIZE_MBEDTLS_SHA256_PROCESS_BUFFER_BYTES])
{
    mbedtls_internal_sha256_process(ctx, data);
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_PSA_CRYPTO)
 **********************************************************************************************************************/
  #endif                               /* MBEDTLS_DEPRECATED_REMOVED */
 #endif                                /* MBEDTLS_SHA256_PROCESS_ALT */
#endif                                 /* MBEDTLS_SHA256_C */
