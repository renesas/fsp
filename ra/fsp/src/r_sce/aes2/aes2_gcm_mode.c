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
static void gcm_inc32 (unsigned char * counter_block)
{
    unsigned char result;

    /* Add one for last byte. */
    result            = (unsigned char) (counter_block[15] + 1);
    counter_block[15] = (unsigned char) (result & 0xFF);

    /* Handle carry. */
    result            = (unsigned char) ((result >> 8) + counter_block[14]);
    counter_block[14] = (unsigned char) (result & 0xFF);
    result            = (unsigned char) ((result >> 8) + counter_block[13]);
    counter_block[13] = (unsigned char) (result & 0xFF);
    result            = (unsigned char) ((result >> 8) + counter_block[12]);
    counter_block[12] = (unsigned char) (result & 0xFF);
}

fsp_err_t hw_gcm_calculation (uint8_t * input,
                              uint8_t * output,
                              uint32_t  data_len,
                              uint8_t * atag,
                              uint8_t * initial_vector,
                              uint32_t  iv_len,
                              uint8_t * aad,
                              uint32_t  aad_len)
{
    uint32_t  remaining_len                       = 0;
    uint32_t  block_len                           = 0;
    uint32_t  temp_value                          = 0;
    uint32_t  temp_len                            = 0;
    uint8_t   first_block_null_aad                = 0;
    uint8_t   Jn[SIZE_AES_BLOCK_BYTES]            = {0};
    uint8_t   J0[SIZE_AES_BLOCK_BYTES]            = {0};
    uint8_t   temp_block[SIZE_AES_BLOCK_BYTES]    = {0};
    uint32_t  local_in[SIZE_AES_BLOCK_BYTES / 4]  = {0};
    uint32_t  local_out[SIZE_AES_BLOCK_BYTES / 4] = {0};
    uint8_t * current_in_ptr;
    uint8_t * current_out_ptr;
    fsp_err_t status = FSP_SUCCESS;

    bool src_unaligned = !HW_32BIT_ALIGNED((uint32_t) input);
    bool dst_unaligned = !HW_32BIT_ALIGNED((uint32_t) output);

    current_in_ptr  = input;
    current_out_ptr = output;

    /* J0 Calculation from IV */
    if (iv_len == 12)
    {
        memcpy(J0, initial_vector, 12);
        J0[15] = 1;
    }
    else
    {
        uint8_t * iv_ptr = initial_vector;
        remaining_len = iv_len;

        R_AES_B->AESDCNTL |= R_AES_AESDCNTL_BIT_2 | R_AES_AESDCNTL_BIT_3;

        while (remaining_len > 0)
        {
            block_len = (remaining_len < 16) ? remaining_len : 16;

            if (block_len < 16)
            {
                memset(temp_block, 0, sizeof(temp_block));
                memcpy(temp_block, iv_ptr, block_len);
                hw_aes_start(temp_block, J0, 1);
            }
            else
            {
                hw_aes_start(iv_ptr, J0, 1);
            }

            iv_ptr        += block_len;
            remaining_len -= block_len;
        }

        uint64_t iv_bit_len  = (uint64_t) iv_len * 8;
        uint8_t  iv_data[16] = {0};
        for (int i = 0; i < 8; i++)
        {
            iv_data[15 - i] = (uint8_t) (iv_bit_len >> (8 * i));
        }

        hw_aes_start(iv_data, J0, 1);
    }

    /* Flow to Obtain J1 from J0 */
    memcpy(Jn, J0, 16);
    gcm_inc32(Jn);
    hw_aes_set_iv(Jn);

    /* Acquire hash value of AAD */
    if (aad_len > 0)
    {
        uint8_t * aad_ptr = aad;
        remaining_len = aad_len;

        R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_3 | R_AES_AESDCNTL_BIT_2;

        while (remaining_len > 0)
        {
            block_len = (remaining_len < SIZE_AES_BLOCK_BYTES) ? remaining_len : SIZE_AES_BLOCK_BYTES;

            if (block_len < SIZE_AES_BLOCK_BYTES)
            {
                memset(temp_block, 0, sizeof(temp_block));
                memcpy(temp_block, aad_ptr, block_len);
                hw_aes_start(temp_block, temp_block, 1);
            }
            else
            {
                hw_aes_start(aad_ptr, temp_block, 1);
            }

            aad_ptr       += block_len;
            remaining_len -= block_len;
        }
    }
    else
    {
        first_block_null_aad = 1;
    }

    /* Encryption Flow Start */
    if (data_len > 0)
    {
        remaining_len = data_len;

        R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_5;
        if (first_block_null_aad == 1)
        {
            first_block_null_aad = 0;
            R_AES_B->AESDCNTL   |= R_AES_AESDCNTL_BIT_3 | R_AES_AESDCNTL_BIT_2;
        }

        do
        {
            block_len = (remaining_len < SIZE_AES_BLOCK_BYTES) ? remaining_len : SIZE_AES_BLOCK_BYTES;
            if ((src_unaligned || dst_unaligned) && (block_len == SIZE_AES_BLOCK_BYTES))
            {
                if (src_unaligned)
                {
                    memset(local_in, 0, SIZE_AES_BLOCK_BYTES);
                    memcpy(local_in, current_in_ptr, block_len);
                    hw_aes_start((uint8_t *) local_in, (uint8_t *) local_out, 1);
                }
                else
                {
                    hw_aes_start(current_in_ptr, (uint8_t *) local_out, 1);
                }

                memcpy(current_out_ptr, local_out, block_len);
            }
            else if (block_len == SIZE_AES_BLOCK_BYTES)
            {
                hw_aes_start(current_in_ptr, current_out_ptr, 1);
            }
            else
            {
                temp_value         = block_len * 8;
                temp_value       <<= 8;
                temp_value        |= R_AES_AESDCNTL_BIT_4;
                R_AES_B->AESDCNTL |= (uint16_t) temp_value;

                memset(temp_block, 0, sizeof(temp_block));
                memcpy(temp_block, current_in_ptr, block_len);
                hw_aes_start(temp_block, (uint8_t *) local_out, 1);
                memcpy(current_out_ptr, local_out, block_len);
            }

            current_in_ptr  += block_len;
            current_out_ptr += block_len;
            remaining_len   -= block_len;

            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_5;
        } while (remaining_len > 0);
    }

    /* Encryption Flow End */

    /* Authentication Tag Creation Start */
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

    memset(atag, 0, 16);
    hw_aes_start(Jn, atag, 1);

    /* Authentication Tag Creation End */
    return status;
}
