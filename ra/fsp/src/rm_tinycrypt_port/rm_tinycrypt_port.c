/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_tinycrypt_port.h"
#include "hw_sce_private.h"
#include "hw_sce_trng_private.h"
#include "rm_tinycrypt_port_cfg.h"
#include "tinycrypt/ecc_platform_specific.h"
#include "tinycrypt/constants.h"

#define RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_WORDS    (4U)
#define RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES    ((RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_WORDS) * 4U)

/* Define the maximum number of attempts by the TRNG to generate dissimilar data. */
#define RM_PSA_CRYPTO_TRNG_MAX_ATTEMPTS           2

/*******************************************************************************************************************/ /**
 * @addtogroup RM_TINYCRYPT_PORT
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize the SCE.
 **********************************************************************************************************************/
fsp_err_t RM_TINCYRYPT_PORT_Init ()
{
    return HW_SCE_McuSpecificInit();
}

/*******************************************************************************************************************//**
 * @brief Reads requested length of random data from the TRNG. Generate `num_req_bytes` of random bytes
 * and store them in `p_rngbuf` buffer.
 *
 * @retval FSP_SUCCESS             Random number generation successful
 * @retval FSP_ERR_ASSERTION       NULL input parameter(s).
 * @retval FSP_ERR_CRYPTO_UNKNOWN  An unknown error occurred.
 * @return                         See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                         return codes.
 *
 **********************************************************************************************************************/
fsp_err_t RM_TINCYRYPT_PORT_TRNG_Read (uint8_t * const p_rngbuf, uint32_t num_req_bytes)
{
    fsp_err_t iret      = FSP_ERR_CRYPTO_UNKNOWN;
    uint32_t  nattempts = 0;
    uint32_t  local_buff[RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_WORDS] = {0};
    uint8_t * p_rngbuf_pos = p_rngbuf;

#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* Verify parameters are valid */
    FSP_ASSERT(p_rngbuf);
    FSP_ASSERT(num_req_bytes);
#endif

    for ( ;
          num_req_bytes > (uint32_t) RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES;
          num_req_bytes -= (uint32_t) RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES)
    {
        for (nattempts = 0; nattempts < RM_PSA_CRYPTO_TRNG_MAX_ATTEMPTS; nattempts++)
        {
            /* Read 16 bytes of random data from SCE TRNG hardware toa 32-bit aligned buffer. */
            iret = HW_SCE_RNG_Read(local_buff);

            if (iret != FSP_SUCCESS)
            {
                return iret;
            }
        }

        memcpy(p_rngbuf_pos, local_buff, RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES);
        p_rngbuf_pos += RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES;
    }

    for (nattempts = 0; nattempts < RM_PSA_CRYPTO_TRNG_MAX_ATTEMPTS; nattempts++)
    {
        /* Read 16 bytes of random data from SCE TRNG hardware */
        iret = HW_SCE_RNG_Read(local_buff);

        if (iret != FSP_SUCCESS)
        {
            return iret;
        }
    }

    memcpy(p_rngbuf_pos, local_buff, num_req_bytes);

    return iret;
}

/*******************************************************************************************************************//**
 * @brief Implements the Cryptographically Secure Pseudo-Random Number Generator function required
 * byt TinyCrypt.
 *
 * @retval TC_CRYPTO_SUCCESS                          Random number generation successful
 * @retval TC_CRYPTO_FAIL                   Random number generation failed.
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *         * RM_TINCYRYPT_PORT_TRNG_Read
 *
 **********************************************************************************************************************/

int default_CSPRNG (uint8_t * dest, unsigned int size)
{
    int tc_return = TC_CRYPTO_SUCCESS;;
    if (FSP_SUCCESS == RM_TINCYRYPT_PORT_TRNG_Read(dest, size))
    {
        tc_return = TC_CRYPTO_SUCCESS;
    }
    else
    {
        tc_return = TC_CRYPTO_FAIL;
    }

    return tc_return;
}

/*******************************************************************************************************************/ /**
 * @} (end addtogroup RM_TINYCRYPT_PORT)
 **********************************************************************************************************************/
