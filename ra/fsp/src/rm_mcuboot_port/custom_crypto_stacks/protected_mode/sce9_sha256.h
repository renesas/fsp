/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef __BOOTUTIL_CRYPTO_SCE9_SHA256_H_
 #define __BOOTUTIL_CRYPTO_SCE9_SHA256_H_

 #include "r_sce.h"
 #define BOOTUTIL_CRYPTO_SHA256_BLOCK_SIZE           (64)
 #define BOOTUTIL_CRYPTO_SHA256_DIGEST_SIZE_BYTES    (32)

 #include <stdint.h>

 #ifdef __cplusplus
extern "C" {
 #endif

typedef struct sce_sha_md5_handle bootutil_sha_context;
static inline void bootutil_sha_init (bootutil_sha_context * ctx)
{
    R_SCE_SHA256_Init(ctx);
}

static inline void bootutil_sha_drop (bootutil_sha_context * ctx)
{
    (void) ctx;
}

static inline int bootutil_sha_update (bootutil_sha_context * ctx, const void * data, uint32_t data_len)
{
    fsp_err_t fsp_err = FSP_SUCCESS;
    fsp_err = R_SCE_SHA256_Update(ctx, (uint8_t *) data, data_len);
    if (fsp_err != FSP_SUCCESS)
    {
        return -1;
    }

    return 0;
}

static inline int bootutil_sha_finish (bootutil_sha_context * ctx, uint8_t * output)
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
