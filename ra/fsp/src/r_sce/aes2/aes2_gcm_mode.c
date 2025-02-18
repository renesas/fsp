/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/

#include "bsp_api.h"
#include "hw_sce_aes_private.h"
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
 * Global variables and functions
 ***********************************************************************************************************************/

fsp_err_t hw_gcm_calculation (uint8_t * input,
                              uint8_t * output,
                              uint32_t  data_len,
                              uint8_t * atag,
                              uint8_t * initial_vector,
                              uint32_t  iv_len,
                              uint8_t * aad,
                              uint32_t  aad_len)
{
    uint32_t  len                             = 0;
    uint32_t  temp_len                        = 0;
    uint32_t  temp_value                      = 0;
    uint8_t   first_block_null_aad            = 0;
    uint8_t   Jn[16]                          = {0};
    uint8_t   J0[16]                          = {0};
    uint8_t   data[16]                        = {0};
    uint8_t   local_in[SIZE_AES_BLOCK_BYTES]  = {0};
    uint8_t   local_out[SIZE_AES_BLOCK_BYTES] = {0};
    uint8_t * ptr;
    uint8_t * ptr_out_temp;
    uint8_t * ptr_out;
    fsp_err_t status = FSP_SUCCESS;
    uint8_t   temp_output[SIZE_AES_BLOCK_BYTES];
    bool      src_unaligned = !HW_32BIT_ALIGNED((uint32_t) &input[0]);
    bool      dst_unaligned = !HW_32BIT_ALIGNED((uint32_t) &output[0]);
    uint8_t * buf_in        = input;
    uint8_t * buf_out       = output;
    uint8_t * p_in          = input;
    uint8_t * p_out         = output;

    if (src_unaligned)
    {
        memset(local_in, 0, (size_t) sizeof(local_in));
        p_in = &local_in[0];
    }

    if (dst_unaligned)
    {
        p_out = &local_out[0];
    }

    if ((uint8_t) iv_len == 12)
    {
        memcpy(&J0, initial_vector, 12);
        J0[15] = 1;
    }
    else
    {
        ptr                = initial_vector;
        temp_len           = iv_len;
        R_AES_B->AESDCNTL |= R_AES_AESDCNTL_BIT_2 | R_AES_AESDCNTL_BIT_3;
        do
        {
            len = 16;
            if (temp_len < 16)
            {
                len = temp_len;
            }

            temp_len -= len;
            hw_aes_start(ptr, &J0[0], 1);
            ptr += len;
        } while (temp_len > 0);

        for (int16_t iLoop = 0; iLoop < 8; iLoop++)
        {
            data[iLoop] = 0;
        }

        for (int16_t iLoop = 0; iLoop < 8; iLoop++)
        {
            temp_len         = (uint32_t) ((uint8_t) iv_len * 8);
            temp_len       >>= (8 * iLoop);
            data[15 - iLoop] = (uint8_t) temp_len;
        }

        hw_aes_start(&data[0], &J0[0], 1);
    }

    /* Flow to Obtain J0 from IV End */
    /* Flow to Obtain J1 from J0 */

    memcpy(Jn, J0, 16);

    for (int16_t iLoop = 0; iLoop < 4; iLoop++)
    {
        temp_value = Jn[15 - iLoop];
        if (temp_value != 0xFF)        // NOLINT(readability-magic-numbers)
        {
            Jn[15 - iLoop] += 1;
            break;
        }

        Jn[15 - iLoop] = 0;
    }

    hw_aes_set_iv(Jn);

    /* Athentication Tag Creation Start */
    if (aad_len != 0)
    {
        /* Flow to Obtain AAD Hash Value Start */
        ptr                = aad;
        temp_len           = aad_len;
        R_AES_B->AESDCNTL |= R_AES_AESDCNTL_BIT_2;

        do
        {
            len = 16;
            if (temp_len < 16)
            {
                len = temp_len;
                memset(data, 0, (size_t) sizeof(data));
                memcpy(data, ptr, (size_t) len);
                hw_aes_start(&data[0], &data[0], 1);
            }
            else
            {
                hw_aes_start(ptr, &data[0], 1);
            }

            ptr      += len;
            temp_len -= len;
        } while (temp_len > 0);

        /* Flow to Obtain AAD Hash Value End */
    }
    else
    {
        first_block_null_aad = 1;
    }

    /* Encryption Flow Start */
    if (data_len != 0)
    {
        ptr      = input;
        ptr_out  = output;
        temp_len = data_len;
        do
        {
            if (src_unaligned)
            {
                memcpy(&local_in[0], &buf_in[0], SIZE_AES_BLOCK_BYTES);
            }

            ptr_out_temp = &temp_output[0];
            temp_value   = 0;
            len          = SIZE_AES_BLOCK_BYTES;
            if (temp_len < SIZE_AES_BLOCK_BYTES)
            {
                len          = temp_len;
                temp_value   = temp_len * 8;
                temp_value <<= 8;
                temp_value  |= R_AES_AESDCNTL_BIT_4;
            }

            temp_len         -= len;
            R_AES_B->AESDCNTL = ((uint16_t) temp_value | R_AES_AESDCNTL_BIT_5);
            if (first_block_null_aad == 1)
            {
                first_block_null_aad = 0;
                R_AES_B->AESDCNTL   |= R_AES_AESDCNTL_BIT_2;
            }

            if ((src_unaligned || dst_unaligned) && (temp_len > 0)) // unaligned data in normal block
            {
                hw_aes_start(p_in, p_out, 1);
                ptr_out += SIZE_AES_BLOCK_BYTES;
                if (dst_unaligned)
                {
                    memcpy(&buf_out[0], &p_out[0], SIZE_AES_BLOCK_BYTES);
                    buf_out += SIZE_AES_BLOCK_BYTES;
                }
                else
                {
                    p_out += SIZE_AES_BLOCK_BYTES;
                }

                if (src_unaligned)
                {
                    buf_in += SIZE_AES_BLOCK_BYTES;
                }
                else
                {
                    p_in += SIZE_AES_BLOCK_BYTES;
                }
            }
            else if (temp_len > 0)
            {
                hw_aes_start(ptr, ptr_out, 1);
                ptr_out += SIZE_AES_BLOCK_BYTES;
            }
            else
            {
                memset(data, 0, sizeof(data));
                memcpy(data, ptr, (size_t) len);
                hw_aes_start(&data[0], ptr_out_temp, 1);
                memcpy(ptr_out, &temp_output[0], (size_t) len);
                ptr_out_temp += SIZE_AES_BLOCK_BYTES;
                ptr_out      += SIZE_AES_BLOCK_BYTES;
            }

            ptr += len;
            for (int16_t iLoop = 0; iLoop < 4; iLoop++)
            {
                temp_value = Jn[15 - iLoop];
                if (temp_value == 0xFF) // NOLINT(readability-magic-numbers)
                {
                    Jn[15 - iLoop] = 0;
                }
                else
                {
                    Jn[15 - iLoop] += 1;
                    break;
                }
            }

            hw_aes_set_iv(Jn);
        } while (temp_len > 0);
    }

    /* Encryption Flow End */

    hw_aes_set_iv(J0);
    for (int16_t iLoop = 0; iLoop < 8; iLoop++)
    {
        temp_len       = aad_len * 8;
        temp_len     >>= (8 * iLoop);
        Jn[7 - iLoop]  = (uint8_t) temp_len;
        temp_len       = data_len * 8;
        temp_len     >>= (8 * iLoop);
        Jn[15 - iLoop] = (uint8_t) temp_len;
    }

    if (((uint8_t) iv_len == 12) && (aad_len == 0) && (data_len == 0))
    {
        R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2 | R_AES_AESDCNTL_BIT_3 | R_AES_AESDCNTL_BIT_6;
    }
    else if (((uint8_t) iv_len != 12) && (aad_len == 0) && (data_len == 0))
    {
        R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2 | R_AES_AESDCNTL_BIT_6;
    }
    else
    {
        R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_6;
    }

    hw_aes_start(&Jn[0], atag, 1);

    /* Athentication Tag Creation End*/
    return status;
}
