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
 **********************************************************************************************************************/
#include <r_sce_private.h>
#include <string.h>

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Block length (in bytes) of SHA */
#define SHA_BLOCK8_LEN            (64U)

/* Initialization function call state */
#define CALL_ONLY_INIT            (0)
#define CALL_ONLY_UPDATE_FINAL    (1)

#ifndef SCE_HEX_FF
 #define SCE_HEX_FF               0xff
#endif
#ifndef SCE_HEX_80
 #define SCE_HEX_80               0x80
#endif
#ifndef SCE_DEC_32
 #define SCE_DEC_32               32
#endif
#ifndef SCE_DEC_64
 #define SCE_DEC_64               64
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern uint32_t g_private_id_counter;
uint32_t        g_sha256_private_id;
uint32_t        g_sha256hmacgen_private_id;
uint32_t        g_sha256hmacver_private_id;

/*******************************************************************************************************************//**
 * @addtogroup SCE_PROTECTED
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * The R_SCE_SHA256_Init() function performs preparations for the execution of an SHA-256 hash calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument in the subsequent
 * R_SCE_SHA256_Update() function and R_SCE_SHA256_Final() function.
 *
 * @param[in,out] handle SHA handler (work area)
 *
 * @retval FSP_SUCCESS Normal termination
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_SHA256_Init (sce_sha_md5_handle_t * handle)
{
    memset(handle, 0, sizeof(sce_sha_md5_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_sha256_private_id = g_private_id_counter;
    handle->id          = g_sha256_private_id;
    memset(handle->sha_buffer, 0, sizeof(handle->sha_buffer));

    return R_SCE_Sha256InitPrivate(handle);
}

/*******************************************************************************************************************//**
 * The R_SCE_SHA256_Update() function calculates a hash value based on the second argument, message,
 * and the third argument, message_length, and writes the ongoing status to the first argument, handle.
 * After message input is completed, call R_SCE_SHA256_Final().
 *
 * @param[in,out] handle         SHA handler (work area)
 * @param[in]     message        message data area
 * @param[in]     message_length message data length
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_SHA256_Update (sce_sha_md5_handle_t * handle, uint8_t * message, uint32_t message_length)
{
    fsp_err_t ercd        = FSP_SUCCESS;
    uint32_t  length_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_sha256_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->all_received_length += message_length;
    if ((handle->buffering_length + message_length) >= SHA_BLOCK8_LEN)
    {
        memcpy(handle->sha_buffer + handle->buffering_length, message, SHA_BLOCK8_LEN - handle->buffering_length);

        /*Casting uint32_t pointer is used for address.*/
        ercd        = R_SCE_Sha256UpdatePrivate(handle, (uint32_t *) (handle->sha_buffer), SHA_BLOCK8_LEN >> 2);
        length_rest = message_length - (SHA_BLOCK8_LEN - handle->buffering_length);
        memset(handle->sha_buffer, 0, sizeof(handle->sha_buffer));
        if (length_rest >= SHA_BLOCK8_LEN)
        {
            ercd = R_SCE_Sha256UpdatePrivate(handle,
                                       /* Casting uint32_t pointer is used for address. */
                                              (uint32_t *) (message + (SHA_BLOCK8_LEN - handle->buffering_length)),
                                              ((length_rest / SHA_BLOCK8_LEN) * SHA_BLOCK8_LEN) >> 2);
            length_rest -= ((length_rest / SHA_BLOCK8_LEN) * SHA_BLOCK8_LEN);
        }

        handle->buffering_length = 0;
        memcpy(handle->sha_buffer, message + (message_length - length_rest), length_rest);
        handle->buffering_length = length_rest;
    }
    else
    {
        memcpy(handle->sha_buffer + handle->buffering_length, message, message_length);
        handle->buffering_length += message_length;
    }

    return ercd;
}

/*******************************************************************************************************************//**
 * Using the handle specified in the first argument, handle, the R_SCE_SHA256_Final() function writes the calculation
 * result to the second argument, digest, and writes the length of the calculation result to the third argument,
 * digest_length.
 *
 * @param[in,out] handle        SHA handler (work area)
 * @param[in,out] digest        hasha data area
 * @param[in,out] digest_length hash data length (32bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_SHA256_Final (sce_sha_md5_handle_t * handle, uint8_t * digest, uint32_t * digest_length)
{
    uint32_t  max_cnt_byte = 0;
    fsp_err_t ercd         = FSP_SUCCESS;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_sha256_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->sha_buffer[handle->buffering_length] = SCE_HEX_80;
    if ((SHA_BLOCK8_LEN - handle->buffering_length) >= 9) /* another block unnecessary */
    {
        memset(handle->sha_buffer + (handle->buffering_length + 1), 0,
               (SHA_BLOCK8_LEN - 4) - (handle->buffering_length + 1));

        /* According c., but support only l < 2**32 case */
        /* Casting uint32_t data to uint8_t data array. */
        handle->sha_buffer[SHA_BLOCK8_LEN - 4] = (uint8_t) ((handle->all_received_length * 8) >> 24);

        /* Casting uint32_t data to uint8_t data array. */
        handle->sha_buffer[SHA_BLOCK8_LEN - 3] = (uint8_t) (((handle->all_received_length * 8) >> 16) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->sha_buffer[SHA_BLOCK8_LEN - 2] = (uint8_t) (((handle->all_received_length * 8) >> 8) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->sha_buffer[SHA_BLOCK8_LEN - 1] = (uint8_t) ((handle->all_received_length * 8) & SCE_HEX_FF);
        max_cnt_byte = SHA_BLOCK8_LEN;
    }
    else
    {
        /* another block necessary */
        memset(handle->sha_buffer + (handle->buffering_length + 1), 0,
               ((2 * SHA_BLOCK8_LEN) - 4) - (handle->buffering_length + 1));

        /* Casting uint32_t data to uint8_t data array. */
        handle->sha_buffer[(2 * SHA_BLOCK8_LEN) - 4] = (uint8_t) ((handle->all_received_length * 8) >> 24);

        /* Casting uint32_t data to uint8_t data array. */
        handle->sha_buffer[(2 * SHA_BLOCK8_LEN) -
                           3] = (uint8_t) (((handle->all_received_length * 8) >> 16) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->sha_buffer[(2 * SHA_BLOCK8_LEN) -
                           2] = (uint8_t) (((handle->all_received_length * 8) >> 8) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->sha_buffer[(2 * SHA_BLOCK8_LEN) - 1] = (uint8_t) ((handle->all_received_length * 8) & SCE_HEX_FF);
        max_cnt_byte = 2 * SHA_BLOCK8_LEN;
    }

    ercd = R_SCE_Sha256FinalPrivate(handle,
                                       /* Casting uint32_t pointer is used for address. */
                                     (uint32_t *) (handle->sha_buffer),
                                     max_cnt_byte >> 2,
                                     (uint32_t *) (digest),
                                     digest_length);
    handle->all_received_length = 0;
    handle->buffering_length    = 0;
    memset(handle->sha_buffer, 0, sizeof(handle->sha_buffer));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_SHA256HMAC_GenerateInit() function uses the second argument wrapped_key to prepare for execution of
 * SHA256-HMAC calculation, then writes the result to the first argument handle. The argument handle is used
 * by the subsequent R_SCE_SHA256HMAC_GenerateUpdate() function or R_SCE_SHA256HMAC_GenerateFinal() function.
 *
 * @param[in,out] handle        SHA-HMAC handler (work area)
 * @param[in]     wrapped_key   MAC wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      An invalid MAC wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_SHA256HMAC_GenerateInit (sce_hmac_sha_handle_t * handle, sce_hmac_sha_wrapped_key_t * wrapped_key)
{
    memset(handle, 0, sizeof(sce_hmac_sha_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_sha256hmacgen_private_id = g_private_id_counter;
    handle->id                 = g_sha256hmacgen_private_id;
    memcpy(&handle->wrapped_key, wrapped_key, sizeof(sce_hmac_sha_wrapped_key_t));

    return R_SCE_Sha256HmacGenerateInitPrivate(handle, wrapped_key);
}

/*******************************************************************************************************************//**
 * The R_SCE_SHA256HMAC_GenerateUpdate() function uses the handle specified by the first argument handle,
 * calculates a hash value from the second argument message and third argument message_length, then writes
 * the intermediate result to the first argument handle. After message input finishes,
 * call the R_SCE_SHA256HMAC_GenerateFinal() function.
 *
 * @param[in,out] handle         SHA-HMAC handle (work area)
 * @param[in]     message        Message area
 * @param[in]     message_length Message length
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_SHA256HMAC_GenerateUpdate (sce_hmac_sha_handle_t * handle, uint8_t * message, uint32_t message_length)
{
    fsp_err_t ercd        = FSP_SUCCESS;
    uint32_t  length_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_sha256hmacgen_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->all_received_length += message_length;
    if ((handle->buffering_length + message_length) >= SHA_BLOCK8_LEN)
    {
        memcpy((&handle->hmac_buffer[0] + handle->buffering_length), message,
               SHA_BLOCK8_LEN - handle->buffering_length);

        /*Casting uint32_t pointer is used for address.*/
        ercd = R_SCE_Sha256HmacGenerateUpdatePrivate(handle,
                                                      (uint32_t *) (handle->hmac_buffer),
                                                      (SHA_BLOCK8_LEN) >> 2);
        length_rest = message_length - (SHA_BLOCK8_LEN - handle->buffering_length);
        memset(handle->hmac_buffer, 0, sizeof(handle->hmac_buffer));
        if (length_rest >= SHA_BLOCK8_LEN)
        {
            ercd = R_SCE_Sha256HmacGenerateUpdatePrivate(handle,
                                       /* Casting uint32_t pointer is used for address. */
                                                          (uint32_t *) (message +
                                                                        (SHA_BLOCK8_LEN - handle->buffering_length)),
                                                          ((length_rest / SHA_BLOCK8_LEN) * SHA_BLOCK8_LEN) >> 2);
            length_rest -= ((length_rest / SHA_BLOCK8_LEN) * SHA_BLOCK8_LEN);
        }

        handle->buffering_length = 0;
        memcpy(handle->hmac_buffer, message + (message_length - length_rest), length_rest);
        handle->buffering_length = length_rest;
    }
    else
    {
        memcpy(&handle->hmac_buffer[0] + handle->buffering_length, message, message_length);
        handle->buffering_length += message_length;
    }

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_SHA256HMAC_GenerateFinal() function uses the handle specified by the first argument handle and
 * writes the calculation result to the second argument mac.
 *
 * @param[in,out] handle SHA-HMAC handle (work area)
 * @param[in,out] mac    HMAC area (32 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_SHA256HMAC_GenerateFinal (sce_hmac_sha_handle_t * handle, uint8_t * mac)
{
    uint32_t  max_cnt_byte = 0;
    fsp_err_t ercd         = FSP_SUCCESS;
    uint32_t  length_tmp   = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_sha256hmacgen_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->hmac_buffer[handle->buffering_length] = SCE_HEX_80;
    length_tmp = handle->all_received_length + SCE_DEC_64;
    if ((SHA_BLOCK8_LEN - handle->buffering_length) >= 9) /* another block unnecessary */
    {
        memset(handle->hmac_buffer + (handle->buffering_length + 1), 0,
               (SHA_BLOCK8_LEN - 4) - (handle->buffering_length + 1));

        /* According c., but support only l < 2**32 case */
        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[SHA_BLOCK8_LEN - 4] = (uint8_t) ((length_tmp * 8) >> 24);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[SHA_BLOCK8_LEN - 3] = (uint8_t) (((length_tmp * 8) >> 16) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[SHA_BLOCK8_LEN - 2] = (uint8_t) (((length_tmp * 8) >> 8) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[SHA_BLOCK8_LEN - 1] = (uint8_t) ((length_tmp * 8) & SCE_HEX_FF);
        max_cnt_byte = SHA_BLOCK8_LEN;
    }
    else                               /* another block necessary */
    {
        memset(handle->hmac_buffer + (handle->buffering_length + 1), 0,
               ((2 * SHA_BLOCK8_LEN) - 4) - (handle->buffering_length + 1));

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[(2 * SHA_BLOCK8_LEN) - 4] = (uint8_t) ((length_tmp * 8) >> 24);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[(2 * SHA_BLOCK8_LEN) - 3] = (uint8_t) (((length_tmp * 8) >> 16) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[(2 * SHA_BLOCK8_LEN) - 2] = (uint8_t) (((length_tmp * 8) >> 8) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[(2 * SHA_BLOCK8_LEN) - 1] = (uint8_t) ((length_tmp * 8) & SCE_HEX_FF);
        max_cnt_byte = 2 * SHA_BLOCK8_LEN;
    }

    /*Casting uint32_t pointer is used for address.*/
    R_SCE_Sha256HmacGenerateUpdatePrivate(handle, (uint32_t *) (handle->hmac_buffer), (max_cnt_byte) >> 2);

    /*Casting uint32_t pointer is used for address.*/
    ercd = R_SCE_Sha256HmacGenerateFinalPrivate(handle, (uint32_t *) (mac));
    handle->all_received_length = 0;
    handle->buffering_length    = 0;
    memset(handle->hmac_buffer, 0, sizeof(handle->hmac_buffer));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_SHA256HMAC_VerifyInit() function uses the second argument wrapped_key to prepare for execution of
 * SHA256-HMAC calculation, then writes the result to the first argument handle. The argument handle is used
 * by the subsequent R_SCE_SHA256HMAC_VerifyUpdate() function or R_SCE_SHA256HMAC_VerifyFinal() function.
 *
 * @param[in,out] handle        SHA-HMAC handler (work area)
 * @param[in]     wrapped_key   MAC wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      An invalid MAC wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_SHA256HMAC_VerifyInit (sce_hmac_sha_handle_t * handle, sce_hmac_sha_wrapped_key_t * wrapped_key)
{
    memset(handle, 0, sizeof(sce_hmac_sha_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_sha256hmacver_private_id = g_private_id_counter;
    handle->id                 = g_sha256hmacver_private_id;
    memcpy(&handle->wrapped_key, wrapped_key, sizeof(sce_hmac_sha_wrapped_key_t));

    return R_SCE_Sha256HmacVerifyInitPrivate(handle, wrapped_key);
}

/*******************************************************************************************************************//**
 * The R_SCE_SHA256HMAC_VerifyUpdate() function uses the handle specified by the first argument handle, calculates
 * a hash value from the second argument message and third argument message_length, then writes the intermediate
 * result to the first argument handle. After message input finishes, call the R_SCE_SHA256HMAC_VerifyFinal() function.
 *
 * @param[in,out] handle         SHA-HMAC handle (work area)
 * @param[in]     message        Message area
 * @param[in]     message_length Message length
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_SHA256HMAC_VerifyUpdate (sce_hmac_sha_handle_t * handle, uint8_t * message, uint32_t message_length)
{
    fsp_err_t ercd        = FSP_SUCCESS;
    uint32_t  length_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_sha256hmacver_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->all_received_length += message_length;
    if ((handle->buffering_length + message_length) >= SHA_BLOCK8_LEN)
    {
        memcpy((&handle->hmac_buffer[0] + handle->buffering_length), message,
               SHA_BLOCK8_LEN - handle->buffering_length);

        /*Casting uint32_t pointer is used for address.*/
        ercd = R_SCE_Sha256HmacVerifyUpdatePrivate(handle,
                                                    (uint32_t *) (handle->hmac_buffer),
                                                    (SHA_BLOCK8_LEN) >> 2);
        length_rest = message_length - (SHA_BLOCK8_LEN - handle->buffering_length);
        memset(handle->hmac_buffer, 0, sizeof(handle->hmac_buffer));
        if (length_rest >= SHA_BLOCK8_LEN)
        {
            ercd = R_SCE_Sha256HmacVerifyUpdatePrivate(handle,
                                       /* Casting uint32_t pointer is used for address. */
                                                        (uint32_t *) (message +
                                                                      (SHA_BLOCK8_LEN - handle->buffering_length)),
                                                        ((length_rest / SHA_BLOCK8_LEN) * SHA_BLOCK8_LEN) >> 2);
            length_rest -= ((length_rest / SHA_BLOCK8_LEN) * SHA_BLOCK8_LEN);
        }

        handle->buffering_length = 0;
        memcpy(handle->hmac_buffer, message + (message_length - length_rest), length_rest);
        handle->buffering_length = length_rest;
    }
    else
    {
        memcpy(&handle->hmac_buffer[0] + handle->buffering_length, message, message_length);
        handle->buffering_length += message_length;
    }

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_SHA256HMAC_VerifyFinal() function uses the handle specified by the first argument handle and verifies
 * the mac value from the second argument mac and third argument mac_length. Input a value in bytes from
 * 4 to 32 as mac_length.
 *
 * @param[in,out] handle     SHA-HMAC handle (work area)
 * @param[in]     mac        HMAC area
 * @param[in]     mac_length HMAC length
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_SHA256HMAC_VerifyFinal (sce_hmac_sha_handle_t * handle, uint8_t * mac, uint32_t mac_length)
{
    uint32_t  max_cnt_byte        = 0;
    fsp_err_t ercd                = FSP_SUCCESS;
    uint32_t  length_tmp          = 0;
    uint32_t  mac_length_tmp      = 0;
    uint8_t   mac_tmp[SCE_DEC_32] =
    {
        0
    };

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_sha256hmacver_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->hmac_buffer[handle->buffering_length] = SCE_HEX_80;
    length_tmp = handle->all_received_length + SCE_DEC_64;
    if ((SHA_BLOCK8_LEN - handle->buffering_length) >= 9) /* another block unnecessary */
    {
        memset(handle->hmac_buffer + (handle->buffering_length + 1), 0,
               (SHA_BLOCK8_LEN - 4) - (handle->buffering_length + 1));

        /* According c., but support only l < 2**32 case */
        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[SHA_BLOCK8_LEN - 4] = (uint8_t) ((length_tmp * 8) >> 24);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[SHA_BLOCK8_LEN - 3] = (uint8_t) (((length_tmp * 8) >> 16) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[SHA_BLOCK8_LEN - 2] = (uint8_t) (((length_tmp * 8) >> 8) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[SHA_BLOCK8_LEN - 1] = (uint8_t) ((length_tmp * 8) & SCE_HEX_FF);
        max_cnt_byte = SHA_BLOCK8_LEN;
    }
    else                               /* another block necessary */
    {
        memset(handle->hmac_buffer + (handle->buffering_length + 1), 0,
               ((2 * SHA_BLOCK8_LEN) - 4) - (handle->buffering_length + 1));

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[(2 * SHA_BLOCK8_LEN) - 4] = (uint8_t) ((length_tmp * 8) >> 24);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[(2 * SHA_BLOCK8_LEN) - 3] = (uint8_t) (((length_tmp * 8) >> 16) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[(2 * SHA_BLOCK8_LEN) - 2] = (uint8_t) (((length_tmp * 8) >> 8) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        handle->hmac_buffer[(2 * SHA_BLOCK8_LEN) - 1] = (uint8_t) ((length_tmp * 8) & SCE_HEX_FF);
        max_cnt_byte = 2 * SHA_BLOCK8_LEN;
    }

    memcpy(mac_tmp, mac, mac_length);
    if ((4 <= mac_length) && (mac_length <= SCE_DEC_32))
    {
        memset(mac_tmp + mac_length, 0, sizeof(mac_tmp) - mac_length);
    }
    else
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    mac_length_tmp = change_endian_long(mac_length);

    /*Casting uint32_t pointer is used for address.*/
    R_SCE_Sha256HmacVerifyUpdatePrivate(handle, (uint32_t *) (handle->hmac_buffer), (max_cnt_byte) >> 2);

    /*Casting uint32_t pointer is used for address.*/
    ercd = R_SCE_Sha256HmacVerifyFinalPrivate(handle, (uint32_t *) (mac_tmp), &mac_length_tmp);
    handle->all_received_length = 0;
    handle->buffering_length    = 0;
    memset(handle->hmac_buffer, 0, sizeof(handle->hmac_buffer));

    return ercd;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCE_PROTECTED)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
