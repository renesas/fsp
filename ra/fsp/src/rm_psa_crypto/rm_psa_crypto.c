/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "common.h"

#if defined(MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT)
 #include "mbedtls/platform.h"
 #include "rm_psa_crypto.h"

 #define RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_WORDS    (4U)
 #define RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES    ((RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_WORDS) * 4U)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static fsp_err_t rm_generate_16byte_random_data(uint8_t * const prevbuff, uint8_t * const currbuff);

/*******************************************************************************************************************//**
 * @brief Reads requested length of random data from the TRNG. Generate `nbytes` of random bytes
 * and store them in `p_rngbuf` buffer.
 *
 * @retval FSP_SUCCESS                          Random number generation successful
 * @retval FSP_ERR_ASSERTION                    NULL input parameter(s).
 * @retval FSP_ERR_CRYPTO_UNKNOWN               An unknown error occurred.
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *         * s_generate_16byte_random_data
 *
 **********************************************************************************************************************/
fsp_err_t RM_PSA_CRYPTO_TRNG_Read (uint8_t * const p_rngbuf, uint32_t num_req_bytes, uint32_t * p_num_gen_bytes)
{
    fsp_err_t iret = FSP_ERR_CRYPTO_UNKNOWN;
    uint8_t   prevbuff[RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES] = {0}; // local buffer for random data
    uint8_t   currbuff[RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES] = {0}; // local buffer for random data
    uint8_t * p_local_rngbuf = p_rngbuf;

 #if SCE_CFG_PARAM_CHECKING_ENABLE

    /* Verify parameters are valid */
    FSP_ASSERT(p_rngbuf);
    FSP_ASSERT(num_req_bytes);
 #endif
    *p_num_gen_bytes = 0;
    for ( ;
          num_req_bytes > (uint32_t) RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES;
          num_req_bytes -= (uint32_t) RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES)
    {
        iret = rm_generate_16byte_random_data(prevbuff, currbuff);
        if (iret != FSP_SUCCESS)
        {
            return iret;
        }

        memcpy(prevbuff, currbuff, RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES);
        memcpy(p_local_rngbuf, currbuff, RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES);
        *p_num_gen_bytes += RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES;
        p_local_rngbuf   += RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES;
    }

    iret = rm_generate_16byte_random_data(prevbuff, currbuff);
    memcpy(p_local_rngbuf, currbuff, num_req_bytes);
    *p_num_gen_bytes += num_req_bytes;

    return iret;
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Generate 16-bytes of random data using the SCE TRNG hardware block.
 *
 * This function makes RM_PSA_CRYPTO_TRNG_MAX_ATTEMPTS to generate 16-bytes of random data using the
 * SCE TRNG block. If successful, the buffer `currbuff` will be updated with newly generated
 * 16-byte block. This data will be different from previously generated 16-byte block (`prevbuff`).
 *
 *
 * @retval FSP_SUCCESS                          Successful generation of 16-byte random data.
 * @retval FSP_ERR_CRYPTO_UNKNOWN               Fatal error, unable to generate 16-byte random data that differs from the
 *                                              previously generated 16-byte block.
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *         * HW_SCE_RNG_Read
 **********************************************************************************************************************/
static fsp_err_t rm_generate_16byte_random_data (uint8_t * const prevbuff, uint8_t * const currbuff)
{
    fsp_err_t iret      = FSP_ERR_CRYPTO_UNKNOWN;
    uint32_t  nattempts = 0;
    for ( ; nattempts < RM_PSA_CRYPTO_TRNG_MAX_ATTEMPTS; nattempts++)
    {
        /* read 16 bytes of random data from SCE TRNG hardware */
        iret = HW_SCE_RNG_Read((uint32_t *) currbuff);

        if (iret != FSP_SUCCESS)
        {
            return iret;
        }

        if (0 == memcmp(currbuff, prevbuff, RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES))
        {
            /* Loopback and retry random number generation if the
             * generated data is the same as the previous data */
            iret = FSP_ERR_CRYPTO_UNKNOWN;
        }
        else
        {
            iret = FSP_SUCCESS;
            break;
        }
    }

    return iret;
}

 #if defined(MBEDTLS_CHECK_PARAMS)
  #include "mbedtls/platform_util.h"

/*
 * Log function that is invoked if MBEDTLS_CHECK_PARAMS is enabled and an error occurs.
 * fsp_error_log() could be used, but the mbedCrypto failure_condition value
 * will not match with fsp_err_t.
 */
void mbedtls_param_failed (const char * failure_condition, const char * file, int line)
{
    FSP_PARAMETER_NOT_USED(failure_condition);
    FSP_PARAMETER_NOT_USED(file);
    FSP_PARAMETER_NOT_USED(line);
}

 #endif

 #if defined(MBEDTLS_PLATFORM_SETBUF_MACRO)

void dummy_setbuf (void * stream, char * buf)
{
    ((void) stream);
    ((void) buf);
}

 #endif                                /* MBEDTLS_PLATFORM_SETBUF_MACRO */

#if defined(__ARMCC_VERSION)
void exit (int x) {
    FSP_PARAMETER_NOT_USED(x);
    while (1)
    {
        ;
    }
}

#endif

#endif                                 /* MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT */
