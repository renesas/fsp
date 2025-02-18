/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "common.h"

#if defined(MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT)
 #include "mbedtls/platform.h"
 #include "mbedtls/error.h"
 #include "hw_sce_private.h"

 #if defined(CONFIG_MEDTLS_USE_AFR_MEMORY) && defined(MBEDTLS_PLATFORM_MEMORY) && \
    !(defined(MBEDTLS_PLATFORM_CALLOC_MACRO) && defined(MBEDTLS_PLATFORM_FREE_MACRO))
extern void * mbedtls_platform_calloc(size_t nmemb, size_t size);
extern void   mbedtls_platform_free(void * ptr);

 #endif

 #ifdef MBEDTLS_THREADING_ALT
  #include "threading_alt.h"
 #endif

/*******************************************************************************************************************//**
 * @addtogroup RM_PSA_CRYPTO
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This function initializes the SCE and the TRNG. It **must** be invoked before the crypto library can be used.
 * This implementation is used if MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT is defined.
 *
 * Example:
 * @snippet rm_psa_crypto_example.c PSA_CRYPTO-PLATFORM-SETUP
 *
 * @retval 0                                        Initialization was successful.
 * @retval MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED     SCE Initialization error.
 **********************************************************************************************************************/
int mbedtls_platform_setup (mbedtls_platform_context * ctx)
{
    (void) ctx;

    fsp_err_t iret = FSP_ERR_CRYPTO_SCE_FAIL;

 #if defined(CONFIG_MEDTLS_USE_AFR_MEMORY) && defined(MBEDTLS_PLATFORM_MEMORY) && \
    !(defined(MBEDTLS_PLATFORM_CALLOC_MACRO) && defined(MBEDTLS_PLATFORM_FREE_MACRO))
    mbedtls_platform_set_calloc_free(mbedtls_platform_calloc, mbedtls_platform_free);
 #endif

 #ifdef MBEDTLS_THREADING_ALT
    mbedtls_platform_threading_init();
 #endif

    iret = HW_SCE_McuSpecificInit();

    if (iret != FSP_SUCCESS)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return 0;
}

/*******************************************************************************************************************//**
 * This implementation is used if MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT is defined.
 * It is intended to de-initialize any items that were initialized in the mbedtls_platform_setup() function, but
 * currently is only a placeholder function.
 *
 * Example:
 * @snippet rm_psa_crypto_example.c PSA_CRYPTO-PLATFORM-TEARDOWN
 *
 * @retval  N/A
 **********************************************************************************************************************/
void mbedtls_platform_teardown (mbedtls_platform_context * ctx)
{
    (void) ctx;

    // Nothing to do to close the SCE
    // Nothing to do to close the TRNG
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_PSA_CRYPTO)
 **********************************************************************************************************************/

#endif                                 /* MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT */
