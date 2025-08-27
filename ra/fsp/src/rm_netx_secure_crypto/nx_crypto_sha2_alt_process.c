/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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
 * Typedef definitions
 ***********************************************************************************************************************/

/**
 * \brief          RSIP context structure.
 *
 *                 The structure is used to store RSIP variables for the
 *                 new SHA224/256 procedure in addition with NetxCrypto's
 *                 data struct NX_CRYPTO_SHA256.
 *                 This structure and its related pointer(s) is only used
 *                 within this file.
 */
typedef struct NX_CRYPTO_SHA256_STRUCT_EXTEND
{
    uint32_t is224;                                                  /*!< Determines which function to use:
                                                                      * 0: Use SHA-256, or 1: Use SHA-224. */
    sce_hash_cmd_t sce_operation_state;
 #if BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || \
    BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED
    uint32_t      rsip_internal_state[20];                           // RSIP specific state array
    unsigned char rsip_buffer[NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES]; /*!< buffered data for RSIP procedure. */
    uint32_t      use_rsip_buffer;                                   // Used to indicate if the rsip_buffer is to be used or not
    uint32_t      rsip_buffer_processed;                             // Used to indicate if the rsip_buffer data is processed or not
 #endif
} NX_CRYPTO_SHA256_EXTEND;

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
static UINT sce_nx_crypto_internal_sha256_process_ext(NX_CRYPTO_SHA256  * context,
                                                      const unsigned char data[NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES],
                                                      uint32_t            len);

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

    /* ULONG nx_sha256_word_array[64] is only used in software procedures
     * Therefore, the idea is to re-use its space to store additional info for rsip internal variables */
    NX_CRYPTO_SHA256_EXTEND * rsip_context = (NX_CRYPTO_SHA256_EXTEND *) &context->nx_sha256_word_array;

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

        rsip_context->is224 = 0;
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

        rsip_context->is224 = 1;
    }

    rsip_context->sce_operation_state = SCE_OEM_CMD_HASH_INIT_TO_SUSPEND;

    /* Return success.  */
    return NX_CRYPTO_SUCCESS;
}

/* Compute SHA calculation on 64 byte blocks and handle partial blocks. */
UINT sce_nx_crypto_sha256_update (NX_CRYPTO_SHA256 * context, UCHAR * input_ptr, UINT input_length)
{
    ULONG     current_bytes;
    ULONG     needed_fill_bytes;
    uint32_t sha256_block_aligned_size;
    NX_CRYPTO_SHA256_EXTEND * rsip_context = (NX_CRYPTO_SHA256_EXTEND *) &context->nx_sha256_word_array;

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

#if !(BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED) 
    rsip_context->sce_operation_state = SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND;
    
    /* Check for a partial buffer that needs to be transformed.  */
    if ((current_bytes) && (input_length >= needed_fill_bytes))
    {
        /* Yes, we can complete the buffer and transform it.  */

        /* Copy the appropriate portion of the input buffer into the internal
         * buffer of the context.  */
        NX_CRYPTO_MEMCPY((void *) &(context->nx_sha256_buffer[current_bytes]), (void *) input_ptr, needed_fill_bytes); /* Use case of memcpy is verified. */

        /* Process the 64-byte (512 bit) buffer.  */
        if (NX_CRYPTO_SUCCESS != sce_nx_crypto_internal_sha256_process_ext(context, context->nx_sha256_buffer, NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES)) 
        {
            return NX_CRYPTO_NOT_SUCCESSFUL;
        }

        /* Adjust the pointers and length accordingly.  */
        input_length = input_length - needed_fill_bytes;
        input_ptr    = input_ptr + needed_fill_bytes;

        /* Clear the remaining bits, since the buffer was processed.  */
        current_bytes = 0;
    }

    if (input_length >= 64)
    {
        /* Process any and all whole blocks of input.  */
        sha256_block_aligned_size = input_length / NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES;
        
        if (NX_CRYPTO_SUCCESS != sce_nx_crypto_internal_sha256_process_ext(context, input_ptr, sha256_block_aligned_size * NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES))
            return NX_CRYPTO_NOT_SUCCESSFUL;
        
        input_length -= (sha256_block_aligned_size * NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES);
        input_ptr += (sha256_block_aligned_size * NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES);
    }
#else // !(BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)
   uint32_t sha256_block_aligned_size_mod;

    /* Check for a partial buffer that needs to be transformed.  */
    if ((current_bytes) && (input_length >= needed_fill_bytes))
    {
        /* Yes, we can complete the buffer and transform it.  */

        /* Copy the appropriate portion of the input buffer into the internal
         * buffer of the context.  */
        NX_CRYPTO_MEMCPY((void *) &(context->nx_sha256_buffer[current_bytes]), (void *) input_ptr, needed_fill_bytes); /* Use case of memcpy is verified. */

        /* Adjust the pointers and length accordingly.  */
        input_length = input_length - needed_fill_bytes;
        input_ptr    = input_ptr + needed_fill_bytes;

        /* Clear the remaining bits, since the buffer was processed.  */
        current_bytes = 0;

        /* If there is data in the rsip_buffer that must be processed first before the context buffer. */
        if ((1U == rsip_context->use_rsip_buffer) && (0U == rsip_context->rsip_buffer_processed))
        {
            if (NX_CRYPTO_SUCCESS != sce_nx_crypto_internal_sha256_process_ext(context, rsip_context->rsip_buffer, NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES))
            {
                return NX_CRYPTO_NOT_SUCCESSFUL;
            }
            rsip_context->rsip_buffer_processed = 1U;
            rsip_context->use_rsip_buffer = 0U;
        }

        /* Process the data in the context buffer. */
        if (NX_CRYPTO_SUCCESS != sce_nx_crypto_internal_sha256_process_ext(context, context->nx_sha256_buffer, NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES)) {
            return NX_CRYPTO_NOT_SUCCESSFUL;
        }
    }

    if (input_length >= 64)
    {
        sha256_block_aligned_size_mod = input_length / NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES;
        sha256_block_aligned_size = sha256_block_aligned_size_mod;
        input_length = input_length - (sha256_block_aligned_size_mod * NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES);

        /* Check to see if there will be unaligned data to be buffered.
        If there is no unaligned data to be buffered, then in case of the RSIP-E51A,
        64 bytes (SHA256 block size) of data will be buffered and processed when the finish() is called. */
        /* If all the data is aligned, copy over the final 64 bytes for later processing. */
        if (input_length > 0)
        {
            /* If there was previously buffered data in this buffer, process that first. */
             if ((1U == rsip_context->use_rsip_buffer) && (0U == rsip_context->rsip_buffer_processed))
            {
                if (NX_CRYPTO_SUCCESS != sce_nx_crypto_internal_sha256_process_ext(context, rsip_context->rsip_buffer, NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES))
                {
                    return NX_CRYPTO_NOT_SUCCESSFUL;
                }
                rsip_context->rsip_buffer_processed = 1U;
                rsip_context->use_rsip_buffer = 0U;
            }
            rsip_context->rsip_buffer_processed = 1U;
            rsip_context->use_rsip_buffer = 0U;
        }
        else
        {
            if ((1U == rsip_context->use_rsip_buffer) && (0U == rsip_context->rsip_buffer_processed))
            {
                if (NX_CRYPTO_SUCCESS != sce_nx_crypto_internal_sha256_process_ext(context, rsip_context->rsip_buffer, NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES))
                {
                    return NX_CRYPTO_NOT_SUCCESSFUL;
                }
                rsip_context->rsip_buffer_processed = 1U;
                rsip_context->use_rsip_buffer = 0U;
            }
            uint32_t final_block_start = (sha256_block_aligned_size_mod * NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES) - NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES;
            memcpy(rsip_context->rsip_buffer, input_ptr + final_block_start, NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES);
            sha256_block_aligned_size_mod -= 1U;
            rsip_context->use_rsip_buffer = 1U;
            rsip_context->rsip_buffer_processed = 0U;
        }

        if ((input_length > NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES) || (sha256_block_aligned_size_mod > 0U))
        {
            if (NX_CRYPTO_SUCCESS != sce_nx_crypto_internal_sha256_process_ext(context, input_ptr, sha256_block_aligned_size_mod * NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES))
                return NX_CRYPTO_NOT_SUCCESSFUL;

            input_ptr += (sha256_block_aligned_size * NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES);
        }
    }
#endif // !(BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED) 

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
#if !(BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)
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

 #ifdef NX_SECURE_KEY_CLEAR
    NX_CRYPTO_MEMSET(bit_count_string, 0, sizeof(bit_count_string));
 #endif                                /* NX_SECURE_KEY_CLEAR  */
#else // !(BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)

    NX_CRYPTO_SHA256_EXTEND * rsip_context = (NX_CRYPTO_SHA256_EXTEND *) &context->nx_sha256_word_array;
    uint32_t used = (context->nx_sha256_bit_count[0] >> 3) & 0x3F;

    /* If there is no unaligned data in the context buffer. */
    if (0 == used)
    {
        /* If there is aligned data buffered in the rsip buffer, process that.*/
        if ((1U == rsip_context->use_rsip_buffer) && (0U == rsip_context->rsip_buffer_processed))
        {
            if (SCE_OEM_CMD_HASH_INIT_TO_SUSPEND == rsip_context->sce_operation_state)
            {
                rsip_context->sce_operation_state = SCE_OEM_CMD_HASH_ONESHOT;
            }
            else if (rsip_context->sce_operation_state == SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND)
            {
                rsip_context->sce_operation_state = SCE_OEM_CMD_HASH_RESUME_TO_FINAL;
            }

            if (NX_CRYPTO_SUCCESS !=
                sce_nx_crypto_internal_sha256_process_ext(context, rsip_context->rsip_buffer,
                                                          NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES))
            {
                return NX_CRYPTO_NOT_SUCCESSFUL;
            }

            rsip_context->rsip_buffer_processed = 1U;
            rsip_context->use_rsip_buffer       = 0U;
        }
        else
        {
            /* If there is no data in the unaligned context buffer and no data in the aligned buffer
             * then this is case of 0 total length passed in. */
            rsip_context->sce_operation_state = SCE_OEM_CMD_HASH_ONESHOT;
            if (NX_CRYPTO_SUCCESS != sce_nx_crypto_internal_sha256_process_ext(context, rsip_context->rsip_buffer, 0))
            {
                return NX_CRYPTO_NOT_SUCCESSFUL;
            }
        }
    }
    else
    {
        if ((1U == rsip_context->use_rsip_buffer) && (0U == rsip_context->rsip_buffer_processed))
        {
            if (SCE_OEM_CMD_HASH_INIT_TO_SUSPEND != rsip_context->sce_operation_state)
            {
                rsip_context->sce_operation_state = SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND;
            }

            if (NX_CRYPTO_SUCCESS !=
                sce_nx_crypto_internal_sha256_process_ext(context, rsip_context->rsip_buffer,
                                                          NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES))
            {
                return NX_CRYPTO_NOT_SUCCESSFUL;
            }

            rsip_context->rsip_buffer_processed = 1U;
            rsip_context->use_rsip_buffer       = 0U;
        }

        if (SCE_OEM_CMD_HASH_INIT_TO_SUSPEND == rsip_context->sce_operation_state)
        {
            rsip_context->sce_operation_state = SCE_OEM_CMD_HASH_ONESHOT;
        }
        else
        {
            rsip_context->sce_operation_state = SCE_OEM_CMD_HASH_RESUME_TO_FINAL;
        }

        if (NX_CRYPTO_SUCCESS != sce_nx_crypto_internal_sha256_process_ext(context, context->nx_sha256_buffer, used))
        {
            return NX_CRYPTO_NOT_SUCCESSFUL;
        }
    }
#endif // !(BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)

    if ((algorithm == NX_CRYPTO_AUTHENTICATION_HMAC_SHA2_256) ||
        (algorithm == NX_CRYPTO_HASH_SHA256))
    {
        NX_CRYPTO_MEMCPY(digest, context->nx_sha256_states, 32);
    }
    else                               /* SHA224 */
    {
        NX_CRYPTO_MEMCPY(digest, context->nx_sha256_states, 28);
    }

    /* Return successful completion.  */
    return NX_CRYPTO_SUCCESS;
}

/*******************************************************************************************************************//**
 * Uses the SCE to process the hash for len size of data and returns the result.
 *
 *
 * @retval NX_CRYPTO_SUCCESS           Hash calculation was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL    Hash calculation with the SCE failed
 **********************************************************************************************************************/
static UINT sce_nx_crypto_internal_sha256_process_ext (NX_CRYPTO_SHA256  * context,
                                                       const unsigned char data[NX_CRYPTO_SHA2_BLOCK_SIZE_IN_BYTES],
                                                       uint32_t            len)
{
    NX_CRYPTO_SHA256_EXTEND * rsip_context = (NX_CRYPTO_SHA256_EXTEND *) &context->nx_sha256_word_array;
    uint32_t   out_data[HW_SCE_SHA256_HASH_STATE_BUFFER_SIZE] = {0};
    uint32_t * outbuff_digest_ptr = out_data;
    uint32_t   sce_hash_type[1];
    uint32_t   sce_hash_cmd[1] = {(uint32_t) rsip_context->sce_operation_state};
    uint32_t   InData_MsgLen[2];

    if (1 == rsip_context->is224)
    {
        sce_hash_type[0] = change_endian_long((uint32_t) SCE_OEM_CMD_HASH_TYPE_SHA224);
    }
    else
    {
        sce_hash_type[0] = change_endian_long((uint32_t) SCE_OEM_CMD_HASH_TYPE_SHA256);
    }

  #if BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || \
    BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED
    if (SCE_OEM_CMD_HASH_INIT_TO_SUSPEND == rsip_context->sce_operation_state)
    {
        rsip_context->sce_operation_state     = SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND;
        rsip_context->rsip_internal_state[18] = change_endian_long((uint32_t) HW_SCE_LARGE_DATA_VALUE_0);
        rsip_context->rsip_internal_state[19] = change_endian_long((uint32_t) HW_SCE_LARGE_DATA_VALUE_1);

        if (FSP_SUCCESS !=
            HW_SCE_ShaGenerateMessageDigestSubGeneral(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0],
                                                      &rsip_context->rsip_internal_state[18],
                                                      &rsip_context->rsip_internal_state[0], outbuff_digest_ptr,
                                                      &rsip_context->rsip_internal_state[0],
                                                      RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(len), NULL))
        {
            return NX_CRYPTO_NOT_SUCCESSFUL;
        }
    }
    else if (SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND == rsip_context->sce_operation_state)
    {
        if (FSP_SUCCESS !=
            HW_SCE_ShaGenerateMessageDigestSubGeneral(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0], NULL,
                                                      &rsip_context->rsip_internal_state[0], outbuff_digest_ptr,
                                                      &rsip_context->rsip_internal_state[0],
                                                      RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(len), NULL))
        {
            return NX_CRYPTO_NOT_SUCCESSFUL;
        }
    }
    else if (SCE_OEM_CMD_HASH_RESUME_TO_FINAL == rsip_context->sce_operation_state)
    {
 #if BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED
        rsip_context->rsip_internal_state[16] = (uint32_t) context->nx_sha256_bit_count[0];
 #endif
        rsip_context->rsip_internal_state[17] = (uint32_t) context->nx_sha256_bit_count[1];
        rsip_context->rsip_internal_state[18] = r_sce_byte_to_bit_convert_upper(len);
        rsip_context->rsip_internal_state[19] = r_sce_byte_to_bit_convert_lower(len);
        if (FSP_SUCCESS !=
            HW_SCE_ShaGenerateMessageDigestSubGeneral(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0], NULL,
                                                      &rsip_context->rsip_internal_state[0], outbuff_digest_ptr,
                                                      &rsip_context->rsip_internal_state[0],
                                                      RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(len), NULL))
        {
            return NX_CRYPTO_NOT_SUCCESSFUL;
        }

        memcpy(&context->nx_sha256_states[0], out_data, HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE);
    }
    else
    {
        /* One-shot case. */
        InData_MsgLen[0] = (uint32_t) context->nx_sha256_bit_count[1];
        InData_MsgLen[1] = (uint32_t) context->nx_sha256_bit_count[0];

        if (FSP_SUCCESS !=
            HW_SCE_ShaGenerateMessageDigestSubGeneral(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0], InData_MsgLen,
                                                      &rsip_context->rsip_internal_state[0], outbuff_digest_ptr,
                                                      &rsip_context->rsip_internal_state[0],
                                                      RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(len), NULL))
        {
            return NX_CRYPTO_NOT_SUCCESSFUL;
        }

        memcpy(&context->nx_sha256_states[0], out_data, HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE);
    }

  #else
    InData_MsgLen[0] = RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(len);
    if (FSP_SUCCESS !=
        HW_SCE_ShaGenerateMessageDigestSubGeneral(sce_hash_type, sce_hash_cmd, (uint32_t *) &data[0], InData_MsgLen,
                                                  NULL, outbuff_digest_ptr, NULL, RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(len), (uint32_t *) &context->nx_sha256_states[0]))
    {
        return NX_CRYPTO_NOT_SUCCESSFUL;
    }
    memcpy(&context->nx_sha256_states[0], out_data, HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE);
  #endif

    return NX_CRYPTO_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/

#endif
