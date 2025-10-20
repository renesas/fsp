/**
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

/* UNCRUSTIFY-OFF */

#include "common.h"

#if defined(MBEDTLS_CHACHA20_C)

#include "mbedtls/chacha20.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"

#include <stddef.h>
#include <string.h>

#include "mbedtls/platform.h"

#if defined(MBEDTLS_CHACHA20_ALT)
  #include "hw_sce_private.h"
  #include "hw_sce_aes_private.h"
  #include "hw_sce_ra_private.h"
  #include "chacha20_alt.h"
  #include "platform_alt.h"

int mbedtls_internal_chacha20_init(mbedtls_chacha20_context * ctx, size_t size)
{
    uint32_t indata_key_type = 1U;
    uint32_t indata_textlen[1];
    indata_textlen[0] = (uint32_t) size;

    if(FSP_SUCCESS != HW_SCE_Chacha20InitSub(&indata_key_type, NULL, &ctx->state[4], &ctx->state[12],
    		&ctx->state[13], indata_textlen))
    {
    	return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return 0;
}

int mbedtls_internal_chacha20_update(mbedtls_chacha20_context * ctx, const unsigned char * input, unsigned char * output, size_t size)
{
    fsp_err_t err                = FSP_SUCCESS;
    uint32_t indata_key_type[1] = {change_endian_long(0x00000001)};

    err = HW_SCE_Chacha20InitSub(indata_key_type, NULL, &ctx->state[4], &ctx->state[12], &ctx->state[13], (uint32_t const *) &size);
    if(FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }
    HW_SCE_Chacha20UpdateSub(NULL, (uint32_t *)  output, 0);
    err = HW_SCE_Chacha20FinalSub((uint32_t *) input, (uint32_t *) output, BYTES_TO_WORDS(size));
    return err;
}

#endif /* MBEDTLS_CHACHA20_ALT */
#endif /* !MBEDTLS_CHACHA20_C */
