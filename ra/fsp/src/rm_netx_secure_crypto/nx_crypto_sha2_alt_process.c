/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * File Name    : nx_crypto_sha2_alt_process.c
 * Description  : Functions interfacing with SCE
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_netx_secure_crypto_cfg.h"
#if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_SHA256_ALT)
 #include "nx_crypto_sha2.h"
 #include "rm_netx_secure_crypto.h"
 #include "hw_sce_hash_private.h"

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/* Use the padding array from the _alt file */
extern const UCHAR _nx_crypto_sha256_padding[64];

/*******************************************************************************************************************//**
 * @addtogroup RM_NETX_SECURE_CRYPTO
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/* Set up initial value based on SHA224 or SHA256. */
UINT sce_nx_crypto_sha256_initialize (NX_CRYPTO_SHA256 * context, UINT algorithm)
{
    /* Determine if the context is non-null.  */
    if (context == NX_CRYPTO_NULL)
    {
        return NX_CRYPTO_PTR_ERROR;
    }

    /* First, clear the bit count for this context.  */
    context->nx_sha256_bit_count[0] = 0; /* Clear the lower 32-bits of the count.*/
    context->nx_sha256_bit_count[1] = 0; /* Clear the upper 32-bits of the count.*/

    if ((algorithm == NX_CRYPTO_AUTHENTICATION_HMAC_SHA2_256) ||
        (algorithm == NX_CRYPTO_HASH_SHA256))
    {
        /* Initialize SHA-256 state. */
        context->nx_sha256_states[0] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0x6a09e667U); /* A H0 */
        context->nx_sha256_states[1] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0xbb67ae85U); /* B H1 */
        context->nx_sha256_states[2] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0x3c6ef372U); /* C H2 */
        context->nx_sha256_states[3] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0xa54ff53aU); /* D H3 */
        context->nx_sha256_states[4] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0x510e527fU); /* E H4 */
        context->nx_sha256_states[5] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0x9b05688cU); /* F H5 */
        context->nx_sha256_states[6] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0x1f83d9abU); /* G H6 */
        context->nx_sha256_states[7] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0x5be0cd19U); /* H H7 */
    }
    else
    {
        /* Initialize SHA-224 state. */
        context->nx_sha256_states[0] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0xc1059ed8U); /* A H0 */
        context->nx_sha256_states[1] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0x367cd507U); /* B H1 */
        context->nx_sha256_states[2] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0x3070dd17U); /* C H2 */
        context->nx_sha256_states[3] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0xf70e5939U); /* D H3 */
        context->nx_sha256_states[4] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0xffc00b31U); /* E H4 */
        context->nx_sha256_states[5] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0x68581511U); /* F H5 */
        context->nx_sha256_states[6] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0x64f98fa7U); /* G H6 */
        context->nx_sha256_states[7] = RM_NETX_CRYPTO_CHANGE_ULONG_ENDIAN(0xbefa4fa4U); /* H H7 */
    }

    /* Return success.  */
    return NX_CRYPTO_SUCCESS;
}

/* Compute SHA calculation on 64 byte blocks and handle partial blocks. */
UINT sce_nx_crypto_sha256_update (NX_CRYPTO_SHA256 * context, UCHAR * input_ptr, UINT input_length)
{
    ULONG     current_bytes;
    ULONG     needed_fill_bytes;
    fsp_err_t ret         = FSP_ERR_ASSERTION;
    uint32_t  out_data[8] = {0};

    /* Determine if the context is non-null.  */
    if (context == NX_CRYPTO_NULL)
    {
        return NX_CRYPTO_PTR_ERROR;
    }

    /* Determine if there is a length.  */
    if (input_length == 0)
    {
        return NX_CRYPTO_SUCCESS;
    }

    /* Calculate the current byte count mod 64. Note the reason for the
     * shift by 3 is to account for the 8 bits per byte.  */
    current_bytes = (context->nx_sha256_bit_count[0] >> 3) & 0x3F;

    /* Calculate the current number of bytes needed to be filled.  */
    needed_fill_bytes = 64 - current_bytes;

    /* Update the total bit count based on the input length.  */
    context->nx_sha256_bit_count[0] += (input_length << 3);

    /* Determine if there is roll-over of the bit count into the MSW.  */
    if (context->nx_sha256_bit_count[0] < (input_length << 3))
    {
        /* Yes, increment the MSW of the bit count.  */
        context->nx_sha256_bit_count[1]++;
    }

    /* Update upper total bit count word.  */
    context->nx_sha256_bit_count[1] += (input_length >> 29);

    /* Check for a partial buffer that needs to be transformed.  */
    if ((current_bytes) && (input_length >= needed_fill_bytes))
    {
        /* Yes, we can complete the buffer and transform it.  */

        /* Copy the appropriate portion of the input buffer into the internal
         * buffer of the context.  */
        NX_CRYPTO_MEMCPY((void *) &(context->nx_sha256_buffer[current_bytes]), (void *) input_ptr, needed_fill_bytes); /* Use case of memcpy is verified. */

        /* Process the 64-byte (512 bit) buffer.  */
        ret = HW_SCE_Sha224256GenerateMessageDigestSub((uint32_t *) context->nx_sha256_states,
                                                       (uint32_t *) context->nx_sha256_buffer,
                                                       16,
                                                       out_data);
        NX_CRYPTO_MEMCPY((uint32_t *) context->nx_sha256_states, out_data, HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE);
        FSP_ERROR_RETURN((FSP_SUCCESS == ret), NX_CRYPTO_NOT_SUCCESSFUL);

        /* Adjust the pointers and length accordingly.  */
        input_length = input_length - needed_fill_bytes;
        input_ptr    = input_ptr + needed_fill_bytes;

        /* Clear the remaining bits, since the buffer was processed.  */
        current_bytes = 0;
    }

    if (input_length >= 64)
    {
        /* Process any and all whole blocks of input.  */
        uint32_t aligned_words = ((input_length >> 6) << 4);
        ret = HW_SCE_Sha224256GenerateMessageDigestSub((uint32_t *) context->nx_sha256_states,
                                                       (const uint32_t *) input_ptr,
                                                       aligned_words,
                                                       out_data);
        NX_CRYPTO_MEMCPY((uint32_t *) context->nx_sha256_states, out_data, HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE);
        FSP_ERROR_RETURN((FSP_SUCCESS == ret), NX_CRYPTO_NOT_SUCCESSFUL);

        input_length -= aligned_words << 2;
        input_ptr    += aligned_words << 2;
    }

    /* Determine if there is anything left.  */
    if (input_length)
    {
        /* Save the remaining bytes in the internal buffer after any remaining bytes
         * so that it is processed later.  */
        NX_CRYPTO_MEMCPY((void *) &(context->nx_sha256_buffer[current_bytes]), (void *) input_ptr, input_length); /* Use case of memcpy is verified. */
    }

    /* Return success.  */
    return NX_CRYPTO_SUCCESS;
}

/* Finalize SHA calculation and handle partial blocks. Return digest based on SHA224 or SHA256 */
UINT sce_nx_crypto_sha256_digest_calculate (NX_CRYPTO_SHA256 * context, UCHAR * digest, UINT algorithm)
{
    UCHAR bit_count_string[8];
    ULONG current_byte_count;
    ULONG padding_bytes;

    /* Move the lower portion of the bit count into the array.  */
    bit_count_string[0] = (UCHAR) (context->nx_sha256_bit_count[1] >> 24);
    bit_count_string[1] = (UCHAR) (context->nx_sha256_bit_count[1] >> 16);
    bit_count_string[2] = (UCHAR) (context->nx_sha256_bit_count[1] >> 8);
    bit_count_string[3] = (UCHAR) (context->nx_sha256_bit_count[1]);
    bit_count_string[4] = (UCHAR) (context->nx_sha256_bit_count[0] >> 24);
    bit_count_string[5] = (UCHAR) (context->nx_sha256_bit_count[0] >> 16);
    bit_count_string[6] = (UCHAR) (context->nx_sha256_bit_count[0] >> 8);
    bit_count_string[7] = (UCHAR) (context->nx_sha256_bit_count[0]);

    /* Calculate the current byte count.  */
    current_byte_count = (context->nx_sha256_bit_count[0] >> 3) & 0x3F;

    /* Calculate the padding bytes needed.  */
    padding_bytes = (current_byte_count < 56) ? (56 - current_byte_count) : (120 - current_byte_count);

    /* Add any padding required.  */
    sce_nx_crypto_sha256_update(context, (UCHAR *) _nx_crypto_sha256_padding, padding_bytes);

    /* Add the in the length.  */
    sce_nx_crypto_sha256_update(context, bit_count_string, 8);

    if ((algorithm == NX_CRYPTO_AUTHENTICATION_HMAC_SHA2_256) ||
        (algorithm == NX_CRYPTO_HASH_SHA256))
    {
        NX_CRYPTO_MEMCPY(digest, context->nx_sha256_states, 32);
    }
    else                               /* SHA224 */
    {
        NX_CRYPTO_MEMCPY(digest, context->nx_sha256_states, 28);
    }

 #ifdef NX_SECURE_KEY_CLEAR
    NX_CRYPTO_MEMSET(bit_count_string, 0, sizeof(bit_count_string));
 #endif                                /* NX_SECURE_KEY_CLEAR  */

    /* Return successful completion.  */
    return NX_CRYPTO_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/

#endif
