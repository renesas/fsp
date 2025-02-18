/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "common.h"

#include "mbedtls/error.h"
#include "mbedtls/entropy.h"
#include "entropy_poll.h"

#include "mbedtls/platform.h"

#if defined(MBEDTLS_ENTROPY_HARDWARE_ALT)
 #include "rm_psa_crypto.h"

/*******************************************************************************************************************//**
 * Reads a random value from the TRNG.
 *
 * Example:
 * @snippet rm_psa_crypto_example.c PSA_CRYPTO-SHA256
 *
 * @retval 0                                    Initialization was successful.
 * @retval MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED HW_SCE_RNG_Read failed to generate 128-bit (16-byte) random number
 *                                              in RM_PSA_CRYPTO_TRNG_MAX_ATTEMPTS number of attempts.
 **********************************************************************************************************************/
int mbedtls_hardware_poll (void * data, unsigned char * output, size_t len, size_t * olen)
{
    ((void) data);

    if (FSP_SUCCESS != RM_PSA_CRYPTO_TRNG_Read(output, len, (uint32_t *) olen))
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return 0;
}

#endif                                 /* MBEDTLS_ENTROPY_HARDWARE_ALT */
