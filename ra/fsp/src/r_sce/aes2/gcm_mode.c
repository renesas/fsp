/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/

#include <tinycrypt/gcm_mode.h>
#include "bsp_api.h"
#include "hw_sce_aes_private.h"
#include "hw_sce_ra_private.h"

#define TC_32BIT_ALIGNED(x)    !(x & 0x03)

/***********************************************************************************************************************
 * Global variables and functions
 ***********************************************************************************************************************/

fsp_err_t tc_gcm_calculation (uint8_t * input,
                              uint8_t * output,
                              uint32_t  data_len,
                              uint8_t * atag,
                              uint8_t * initial_vector,
                              uint32_t  iv_len,
                              uint8_t * aad,
                              uint32_t  aad_len)
{
    uint8_t   Jn[16];
    uint8_t   J0[16];
    uint8_t   data[16];
    uint8_t   temp;
    uint32_t  temp_len;
    uint32_t  temp1;
    uint32_t  len;
    uint8_t * ptr;
    uint8_t * ptr_out_temp;
    uint8_t * ptr_out;
    fsp_err_t status = FSP_SUCCESS;
    uint8_t   temp_output[TC_AES_BLOCK_SIZE];
    bool      src_unaligned = !TC_32BIT_ALIGNED((uint32_t) &input[0]);
    bool      dst_unaligned = !TC_32BIT_ALIGNED((uint32_t) &output[0]);
    uint8_t * buf_in        = input;
    uint8_t * buf_out       = output;
    uint8_t * p_in          = input;
    uint8_t * p_out         = output;
    uint8_t   local_in[TC_AES_BLOCK_SIZE];
    uint8_t   local_out[TC_AES_BLOCK_SIZE];

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
        R_AES_B->AESDCNTL |= R_AES_AESDCNTL_ASSIGN_DATA_DISABLE;
        do
        {
            len = 16;
            if (temp_len < 16)
            {
                len = temp_len;
            }

            temp_len -= len;
            tc_aes_start(ptr, &J0[0], 1);
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

        tc_aes_start(&data[0], &J0[0], 1);
    }

    /* Flow to Obtain J0 from IV End */
    /* Flow to Obtain J1 from J0 */

    memcpy(Jn, J0, 16);

    for (int16_t iLoop = 0; iLoop < 4; iLoop++)
    {
        temp = Jn[15 - iLoop];
        if (temp != 0xFF)              // NOLINT(readability-magic-numbers)
        {
            Jn[15 - iLoop] += 1;
            break;
        }

        Jn[15 - iLoop] = 0;
    }

    tc_aes_set_iv(Jn);

    /* Athentication Tag Creation Start */
    if (aad_len != 0)
    {
        /* Flow to Obtain AAD Hash Value Start */
        ptr                = aad;
        R_AES_B->AESDCNTL |= R_AES_AESDCNTL_BIT_2;
        temp_len           = aad_len;

        do
        {
            len = 16;
            if (temp_len < 16)
            {
                len = temp_len;
                memset(data, 0, (size_t) sizeof(data));
                memcpy(data, ptr, (size_t) len);
                tc_aes_start(&data[0], &data[0], 1);
            }
            else
            {
                tc_aes_start(ptr, &data[0], 1);
            }

            ptr      += len;
            temp_len -= len;
        } while (temp_len > 0);

        /* Flow to Obtain AAD Hash Value End */
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
                memcpy(&local_in[0], &buf_in[0], TC_AES_BLOCK_SIZE);
            }

            ptr_out_temp = &temp_output[0];
            temp1        = 0;
            len          = 16;
            if (temp_len < 16)
            {
                len     = temp_len;
                temp1   = temp_len * 8;
                temp1 <<= 8;
                temp1  |= R_AES_AESDCNTL_BIT_4;
            }

            temp_len         -= len;
            R_AES_B->AESDCNTL = ((uint16_t) temp1 | R_AES_AESDCNTL_BIT_5);
            if ((src_unaligned || dst_unaligned) && (temp_len > 0)) // unaligned data in normal block
            {
                tc_aes_start(p_in, p_out, 1);
                ptr_out += TC_AES_BLOCK_SIZE;
                if (dst_unaligned)
                {
                    memcpy(&buf_out[0], &p_out[0], TC_AES_BLOCK_SIZE);
                    buf_out += TC_AES_BLOCK_SIZE;
                }
                else
                {
                    p_out += TC_AES_BLOCK_SIZE;
                }

                if (src_unaligned)
                {
                    buf_in += TC_AES_BLOCK_SIZE;
                }
                else
                {
                    p_in += TC_AES_BLOCK_SIZE;
                }
            }
            else if (temp_len > 0)
            {
                tc_aes_start(ptr, ptr_out, 1);
                ptr_out += TC_AES_BLOCK_SIZE;
            }
            else
            {
                memset(data, 0, sizeof(data));
                memcpy(data, ptr, (size_t) len);
                tc_aes_start(&data[0], ptr_out_temp, 1);
                memcpy(ptr_out, &temp_output[0], (size_t) len);
                ptr_out_temp += TC_AES_BLOCK_SIZE;
                ptr_out      += TC_AES_BLOCK_SIZE;
            }

            ptr += len;
            for (int16_t iLoop = 0; iLoop < 4; iLoop++)
            {
                temp = Jn[15 - iLoop];
                if (temp == 0xFF)      // NOLINT(readability-magic-numbers)
                {
                    Jn[15 - iLoop] = 0;
                }
                else
                {
                    Jn[15 - iLoop] += 1;
                    break;
                }
            }

            tc_aes_set_iv(Jn);
        } while (temp_len > 0);
    }

    /* Encryption Flow End */

    if (aad_len != 0)
    {
        tc_aes_set_iv(J0);
        for (int16_t iLoop = 0; iLoop < 8; iLoop++)
        {
            temp_len       = aad_len * 8;
            temp_len     >>= (8 * iLoop);
            Jn[7 - iLoop]  = (uint8_t) temp_len;
            temp_len       = data_len * 8;
            temp_len     >>= (8 * iLoop);
            Jn[15 - iLoop] = (uint8_t) temp_len;
        }

        R_AES_B->AESDCNTL |= R_AES_AESDCNTL_BIT_6;
        tc_aes_start(&Jn[0], atag, 1);
    }

    /* Athentication Tag Creation End*/
    return status;
}
