/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
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

#include "entropy.h"
#include "entropy_poll.h"

#include "platform.h"

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
