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

#ifndef __BOOTUTIL_CRYPTO_SCE9_SHA256_H_
 #define __BOOTUTIL_CRYPTO_SCE9_SHA256_H_

 #include "r_sce.h"
 #define BOOTUTIL_CRYPTO_SHA256_BLOCK_SIZE           (64)
 #define BOOTUTIL_CRYPTO_SHA256_DIGEST_SIZE_BYTES    (32)

 #include <stdint.h>

 #ifdef __cplusplus
extern "C" {
 #endif

typedef struct sce_sha_md5_handle bootutil_sha256_context;
static inline void bootutil_sha256_init (bootutil_sha256_context * ctx)
{
    R_SCE_SHA256_Init(ctx);
}

static inline void bootutil_sha256_drop (bootutil_sha256_context * ctx)
{
    (void) ctx;
}

static inline int bootutil_sha256_update (bootutil_sha256_context * ctx, const void * data, uint32_t data_len)
{
    fsp_err_t fsp_err = FSP_SUCCESS;
    fsp_err = R_SCE_SHA256_Update(ctx, (uint8_t *) data, data_len);
    if (fsp_err != FSP_SUCCESS)
    {
        return -1;
    }

    return 0;
}

static inline int bootutil_sha256_finish (bootutil_sha256_context * ctx, uint8_t * output)
{
    fsp_err_t fsp_err       = FSP_SUCCESS;
    uint32_t  digest_length = 0;

    fsp_err = R_SCE_SHA256_Final(ctx, output, &digest_length);
    if (fsp_err != FSP_SUCCESS)
    {
        return -1;
    }

    return 0;
}

 #ifdef __cplusplus
}
 #endif

#endif                                 /* __BOOTUTIL_CRYPTO_SCE9_SHA256_H_ */
