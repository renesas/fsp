/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#ifndef MBEDTLS_PLATFORM_ALT_H
#define MBEDTLS_PLATFORM_ALT_H
#if defined(MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT)

#define BYTES_TO_WORDS(x) (((x + 3) >> 2))
/**
 * \brief   The platform context structure.
 *
 * \note    This structure may be used to assist platform-specific
 *          setup or teardown operations.
 */
typedef struct mbedtls_platform_context
{
    char dummy; /**< A placeholder member, as empty structs are not portable. */
}
mbedtls_platform_context;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
#endif /* MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT */
#endif /* platform_alt.h */
