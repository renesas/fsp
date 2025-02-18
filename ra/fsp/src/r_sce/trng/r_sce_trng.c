/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "hw_sce_trng_private.h"

/*******************************************************************************************************************//**
 * 128bit Random Number Generation
 * @param      OutData_Text    The out data text
 * @retval FSP_SUCCESS      The operation completed successfully.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_RNG_Read (uint32_t * OutData_Text) {
    uint8_t * ptmp = (uint8_t *) OutData_Text;
    uint32_t  k;
    for (k = 0; k < 4; k++)            // read 4 words of random data similar (to make this API consistent with S7 and S3 implementation)
    {
        /* Set SGCEN bit and SGSTART bit */
        R_TRNG->TRNGSCR0_b.SGCEN   = 1;
        R_TRNG->TRNGSCR0_b.SGSTART = 1;

        /* Wait for RDRDY bit to be set */
        while (0 == R_TRNG->TRNGSCR0_b.RDRDY)
        {
        }

        /* Read generated random data */
        *ptmp++ = R_TRNG->TRNGSDR;
        *ptmp++ = R_TRNG->TRNGSDR;
        *ptmp++ = R_TRNG->TRNGSDR;
        *ptmp++ = R_TRNG->TRNGSDR;
    }

    return FSP_SUCCESS;
}
