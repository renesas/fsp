/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_ocrypto_port.h"
#include "hw_sce_private.h"
#include "hw_sce_trng_private.h"
#include "rm_ocrypto_port_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_WORDS    (4U)
#define RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_BYTES    ((RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_WORDS) * 4U)

/* Define the maximum number of attempts by the TRNG to generate dissimilar data. */
#define RM_PSA_CRYPTO_TRNG_MAX_ATTEMPTS           2

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/*******************************************************************************************************************/ /**
 * @addtogroup RM_OCRYPTO_PORT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Initialize the SCE.
 *
 * @retval  FSP_SUCCESS     SCE initialized successfully
 * @return                  See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                          return codes.
 *
 **********************************************************************************************************************/
fsp_err_t RM_OCRYPTO_PORT_Init ()
{
    return HW_SCE_McuSpecificInit();
}

/*******************************************************************************************************************//**
 * @brief Reads requested length of random data from the TRNG. Generate @p num_req_bytes of random bytes
 * and store them in @p p_rngbuf buffer.
 *
 * @param[out]  p_rngbuf                Pointer to buffer to store generated random number
 * @param[in]   num_req_bytes           How many bytes of random numbers to generate
 *
 * @retval      FSP_SUCCESS             Random number generation successful
 * @retval      FSP_ERR_ASSERTION       NULL input parameter(s).
 * @retval      FSP_ERR_CRYPTO_UNKNOWN  An unknown error occurred.
 *
 **********************************************************************************************************************/
fsp_err_t RM_OCRYPTO_PORT_TRNG_Read (uint8_t * const p_rngbuf, uint32_t num_req_bytes)
{
    fsp_err_t iret      = FSP_ERR_CRYPTO_UNKNOWN;
    uint32_t  nattempts = 0;
    uint32_t  local_buff[RM_PSA_CRYPTO_TRNG_REGISTER_SIZE_WORDS] = {0};
    uint8_t * p_rngbuf_pos = p_rngbuf;

#if RM_OCRYPTO_PORT_CFG_PARAM_CHECKING_ENABLE

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

/*******************************************************************************************************************/ /**
 * @} (end addtogroup RM_OCRYPTO_PORT)
 **********************************************************************************************************************/
