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
#include <string.h>
#include "r_sce_private.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* GCM related */
#define GCM_IV_MAX_BYTE_SIZE      (12)
#define GCM_INPUT_DATA_TEXT       (1)
#define GCM_INPUT_DATA_AAD        (0)

/* Initialization function call state */
#define CALL_ONLY_INIT            (0)
#define CALL_ONLY_UPDATE_FINAL    (1)

/* Magic numbers */
#ifndef SCE_HEX_E000000
 #define SCE_HEX_E000000          0xe000000U
#endif
#ifndef SCE_DEC_110
 #define SCE_DEC_110              110
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static fsp_err_t prepare_gcm_iv(uint8_t               * initial_vector,
                                uint32_t                initial_vector_length,
                                sce_aes_wrapped_key_t * wrapped_key,
                                uint32_t                wrapped_key_word_size,
                                uint32_t              * hashed_ivec);
static void aes_ccm_b_counter_formatter(uint8_t  * nonce,
                                        uint32_t   nonce_len,
                                        uint8_t  * adata,
                                        uint8_t    a_len,
                                        uint32_t   payload_len,
                                        uint32_t   mac_len,
                                        uint8_t  * counter,
                                        uint8_t  * formatted_data,
                                        uint32_t * formatted_length);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern uint32_t g_private_id_counter;
uint32_t        g_aes128ecbenc_private_id;
uint32_t        g_aes128ecbdec_private_id;
uint32_t        g_aes256ecbenc_private_id;
uint32_t        g_aes256ecbdec_private_id;
uint32_t        g_aes128cbcenc_private_id;
uint32_t        g_aes128cbcdec_private_id;
uint32_t        g_aes256cbcenc_private_id;
uint32_t        g_aes256cbcdec_private_id;
uint32_t        g_aes128cmacgen_private_id;
uint32_t        g_aes128cmacver_private_id;
uint32_t        g_aes256cmacgen_private_id;
uint32_t        g_aes256cmacver_private_id;
uint32_t        g_aes128gcmenc_private_id;
uint32_t        g_aes128gcmdec_private_id;
uint32_t        g_aes256gcmenc_private_id;
uint32_t        g_aes256gcmdec_private_id;
uint32_t        g_aes128ccmenc_private_id;
uint32_t        g_aes128ccmdec_private_id;
uint32_t        g_aes256ccmenc_private_id;
uint32_t        g_aes256ccmdec_private_id;

/*******************************************************************************************************************//**
 * @addtogroup SCE_PROTECTED
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * The R_SCE_AES128ECB_EncryptInit() function performs preparations for the execution of an AES calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument
 * in the subsequent R_SCE_AES128ECB_EncryptUpdate() function and R_SCE_AES128ECB_EncryptFinal() function.
 *
 * @param[in,out] handle      AES handler (work area)
 * @param[in]     wrapped_key 128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal wrapped key.
 *
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128ECB_EncryptInit (sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key)
{
    memset(handle, 0, sizeof(sce_aes_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes128ecbenc_private_id = g_private_id_counter;
    handle->id                = g_aes128ecbenc_private_id;

    return R_SCE_Aes128EcbEncryptInitPrivate(wrapped_key);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128ECB_EncryptUpdate() function encrypts the second argument, plain, utilizing the key index stored
 * in the handle specified in the first argument, handle, and writes the ongoing status to this first argument.
 * In addition, it writes the encryption result to the third argument, cipher. After plaintext input is completed,
 * call R_SCE_AES128ECB_EncryptFinal().
 *
 * Specify areas for plain and cipher that do not overlap. For plain and cipher,
 * specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle       AES handler (work area)
 * @param[in]     plain        plaintext data area
 * @param[in,out] cipher       ciphertext data area
 * @param[in,out] plain_length plaintext data length (must be a multiple of 16)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128ECB_EncryptUpdate (sce_aes_handle_t * handle,
                                         uint8_t          * plain,
                                         uint8_t          * cipher,
                                         uint32_t           plain_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes128ecbenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    memcpy(handle->last_1_block_as_fraction,
           (plain + (plain_length / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE),
           (plain_length % HW_SCE_AES_BLOCK_BYTE_SIZE));
    handle->current_input_data_size = plain_length;

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes128EcbEncryptUpdatePrivate((uint32_t *) (plain), (uint32_t *) (cipher), plain_length >> 2);
}

/*******************************************************************************************************************//**
 * Using the handle specified in the first argument, handle, the R_SCE_AES128ECB_EncryptFinal() function writes
 * the calculation result to the second argument, cipher, and writes the length of the calculation result
 * to the third argument, cipher_length. The original intent was for a portion of the encryption
 * result that was not a multiple of 16 bytes to be written to the second argument.
 * However, as a result of the restriction that only multiples of 16 can be input to the Update function,
 * nothing is ever written to cipher, and 0 is always written to cipher_length. The arguments cipher and cipher_length
 * are provided for compatibility in anticipation of the time when this restriction is lifted.
 *
 * @param[in,out] handle        AES handler (work area)
 * @param[in,out] cipher        ciphertext data area (nothing ever written here)
 * @param[in,out] cipher_length ciphertext data length (0 always written here)
 *
 * @retval FSP_SUCCESS             Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128ECB_EncryptFinal (sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes128ecbenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    *cipher_length = 0;
    memset(handle, 0, sizeof(sce_aes_handle_t));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes128EcbEncryptFinalPrivate((uint32_t *) (cipher), cipher_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128ECB_DecryptInit() function performs preparations for the execution of an AES calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument
 * in the subsequent R_SCE_AES128ECB_DecryptUpdate() function and R_SCE_AES128ECB_DecryptFinal() function.
 *
 * @param[in,out] handle      AES handler (work area)
 * @param[in]     wrapped_key 128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal wrapped key.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128ECB_DecryptInit (sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key)
{
    memset(handle, 0, sizeof(sce_aes_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes128ecbdec_private_id = g_private_id_counter;
    handle->id                = g_aes128ecbdec_private_id;

    return R_SCE_Aes128EcbDecryptInitPrivate(wrapped_key);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128ECB_DecryptUpdate() function decrypts the second argument, cipher, utilizing the key index stored
 * in the handle specified in the first argument, handle, and writes the ongoing status to this first argument.
 * In addition, it writes the decryption result to the third argument, plain. After plaintext input is completed,
 * call R_SCE_AES128ECB_DecryptFinal().
 *
 * Specify areas for plain and cipher that do not overlap. For plain and cipher,
 * specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle        AES handler (work area)
 * @param[in]     cipher        ciphertext data area
 * @param[in,out] plain         plaintext data area
 * @param[in,out] cipher_length ciphertext data length (must be a multiple of 16)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128ECB_DecryptUpdate (sce_aes_handle_t * handle,
                                         uint8_t          * cipher,
                                         uint8_t          * plain,
                                         uint32_t           cipher_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes128ecbdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->current_input_data_size = cipher_length;
    memcpy(handle->last_1_block_as_fraction,
           (cipher + (cipher_length / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE),
           (cipher_length % HW_SCE_AES_BLOCK_BYTE_SIZE));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes128EcbDecryptUpdatePrivate((uint32_t *) (cipher), (uint32_t *) (plain), cipher_length >> 2);
}

/*******************************************************************************************************************//**
 * Using the handle specified in the first argument, handle, the R_SCE_AES128ECB_DecryptFinal() function writes
 * the calculation result to the second argument, plain, and writes the length of the calculation result
 * to the third argument, plain_length. The original intent was for a portion of the decryption
 * result that was not a multiple of 16 bytes to be written to the second argument.
 * However, as a result of the restriction that only multiples of 16 can be input to the Update function,
 * nothing is ever written to plain, and 0 is always written to plain_length. The arguments plain and plain_length
 * are provided for compatibility in anticipation of the time when this restriction is lifted.
 *
 * @param[in,out] handle       AES handler (work area)
 * @param[in,out] plain        plaintext data area (nothing ever written here)
 * @param[in,out] plain_length plaintext data length (0 always written here)
 *
 * @retval FSP_SUCCESS             Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128ECB_DecryptFinal (sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes128ecbdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    *plain_length = 0;
    memset(handle, 0, sizeof(sce_aes_handle_t));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes128EcbDecryptFinalPrivate((uint32_t *) (plain), plain_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256ECB_EncryptInit() function performs preparations for the execution of an AES calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument
 * in the subsequent R_SCE_AES256ECB_EncryptUpdate() function and R_SCE_AES256ECB_EncryptFinal() function.
 *
 * @param[in,out] handle      AES handler (work area)
 * @param[in]     wrapped_key 128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal wrapped key.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256ECB_EncryptInit (sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key)
{
    memset(handle, 0, sizeof(sce_aes_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes256ecbenc_private_id = g_private_id_counter;
    handle->id                = g_aes256ecbenc_private_id;

    return R_SCE_Aes256EcbEncryptInitPrivate(wrapped_key);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256ECB_EncryptUpdate() function encrypts the second argument, plain, utilizing the key index stored
 * in the handle specified in the first argument, handle, and writes the ongoing status to this first argument.
 * In addition, it writes the encryption result to the third argument, cipher. After plaintext input is completed,
 * call R_SCE_AES256ECB_EncryptFinal().
 *
 * Specify areas for plain and cipher that do not overlap. For plain and cipher,
 * specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle       AES handler (work area)
 * @param[in]     plain        plaintext data area
 * @param[in,out] cipher       ciphertext data area
 * @param[in,out] plain_length plaintext data length (must be a multiple of 16)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256ECB_EncryptUpdate (sce_aes_handle_t * handle,
                                         uint8_t          * plain,
                                         uint8_t          * cipher,
                                         uint32_t           plain_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes256ecbenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->current_input_data_size = plain_length;
    memcpy(handle->last_1_block_as_fraction,
           (plain + (plain_length / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE),
           (plain_length % HW_SCE_AES_BLOCK_BYTE_SIZE));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes256EcbEncryptUpdatePrivate((uint32_t *) (plain), (uint32_t *) (cipher), plain_length >> 2);
}

/*******************************************************************************************************************//**
 * Using the handle specified in the first argument, handle, the R_SCE_AES256ECB_EncryptFinal() function writes
 * the calculation result to the second argument, cipher, and writes the length of the calculation result
 * to the third argument, cipher_length. The original intent was for a portion of the encryption
 * result that was not a multiple of 16 bytes to be written to the second argument.
 * However, as a result of the restriction that only multiples of 16 can be input to the Update function,
 * nothing is ever written to cipher, and 0 is always written to cipher_length. The arguments cipher and cipher_length
 * are provided for compatibility in anticipation of the time when this restriction is lifted.
 *
 * @param[in,out] handle        AES handler (work area)
 * @param[in,out] cipher        ciphertext data area (nothing ever written here)
 * @param[in,out] cipher_length ciphertext data length (0 always written here)
 *
 * @retval FSP_SUCCESS             Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256ECB_EncryptFinal (sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes256ecbenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    *cipher_length = 0;
    memset(handle, 0, sizeof(sce_aes_handle_t));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes256EcbEncryptFinalPrivate((uint32_t *) (cipher), cipher_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128ECB_DecryptInit() function performs preparations for the execution of an AES calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument
 * in the subsequent R_SCE_AES128ECB_DecryptUpdate() function and R_SCE_AES128ECB_DecryptFinal() function.
 *
 * @param[in,out] handle      AES handler (work area)
 * @param[in]     wrapped_key 128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal wrapped key.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256ECB_DecryptInit (sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key)
{
    memset(handle, 0, sizeof(sce_aes_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes256ecbdec_private_id = g_private_id_counter;
    handle->id                = g_aes256ecbdec_private_id;
    return R_SCE_Aes256EcbDecryptInitPrivate(wrapped_key);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256ECB_DecryptUpdate() function decrypts the second argument, cipher, utilizing the key index stored
 * in the handle specified in the first argument, handle, and writes the ongoing status to this first argument.
 * In addition, it writes the decryption result to the third argument, plain. After plaintext input is completed,
 * call R_SCE_AES256ECB_DecryptFinal().
 *
 * Specify areas for plain and cipher that do not overlap. For plain and cipher,
 * specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle        AES handler (work area)
 * @param[in]     cipher        ciphertext data area
 * @param[in,out] plain         plaintext data area
 * @param[in,out] cipher_length ciphertext data length (must be a multiple of 16)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256ECB_DecryptUpdate (sce_aes_handle_t * handle,
                                         uint8_t          * cipher,
                                         uint8_t          * plain,
                                         uint32_t           cipher_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes256ecbdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->current_input_data_size = cipher_length;
    memcpy(handle->last_1_block_as_fraction,
           (cipher + (cipher_length / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE),
           (cipher_length % HW_SCE_AES_BLOCK_BYTE_SIZE));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes256EcbDecryptUpdatePrivate((uint32_t *) (cipher), (uint32_t *) (plain), cipher_length >> 2);
}

/*******************************************************************************************************************//**
 * Using the handle specified in the first argument, handle, the R_SCE_AES256ECB_DecryptFinal() function writes
 * the calculation result to the second argument, plain, and writes the length of the calculation result
 * to the third argument, plain_length. The original intent was for a portion of the decryption
 * result that was not a multiple of 16 bytes to be written to the second argument.
 * However, as a result of the restriction that only multiples of 16 can be input to the Update function,
 * nothing is ever written to plain, and 0 is always written to plain_length. The arguments plain and plain_length
 * are provided for compatibility in anticipation of the time when this restriction is lifted.
 *
 * @param[in,out] handle       AES handler (work area)
 * @param[in,out] plain        plaintext data area (nothing ever written here)
 * @param[in,out] plain_length plaintext data length (0 always written here)
 *
 * @retval FSP_SUCCESS             Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256ECB_DecryptFinal (sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes256ecbdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    *plain_length = 0;
    memset(handle, 0, sizeof(sce_aes_handle_t));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes256EcbDecryptFinalPrivate((uint32_t *) (plain), plain_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CBC_EncryptInit() function performs preparations for the execution of an AES calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument
 * in the subsequent R_SCE_AES128CBC_EncryptUpdate() function and R_SCE_AES128CBC_EncryptFinal() function.
 *
 * @param[in,out] handle         AES handler (work area)
 * @param[in]     wrapped_key    128-bit AES wrapped key
 * @param[in]     initial_vector initialization vector area (16byte)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal wrapped key.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CBC_EncryptInit (sce_aes_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * initial_vector)
{
    memset(handle, 0, sizeof(sce_aes_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes128cbcenc_private_id = g_private_id_counter;
    handle->id                = g_aes128cbcenc_private_id;
    memcpy(handle->current_initial_vector, initial_vector, sizeof(handle->current_initial_vector));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes128CbcEncryptInitPrivate(wrapped_key, (uint32_t *) (initial_vector));
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CBC_EncryptUpdate() function encrypts the second argument, plain, utilizing the key index stored
 * in the handle specified in the first argument, handle, and writes the ongoing status to this first argument.
 * In addition, it writes the encryption result to the third argument, cipher. After plaintext input is completed,
 * call R_SCE_AES128CBC_EncryptFinal().
 *
 * Specify areas for plain and cipher that do not overlap. For plain and cipher,
 * specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle       AES handler (work area)
 * @param[in]     plain        plaintext data area
 * @param[in,out] cipher       ciphertext data area
 * @param[in,out] plain_length plaintext data length (must be a multiple of 16)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CBC_EncryptUpdate (sce_aes_handle_t * handle,
                                         uint8_t          * plain,
                                         uint8_t          * cipher,
                                         uint32_t           plain_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes128cbcenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->current_input_data_size = plain_length;
    memcpy(handle->last_1_block_as_fraction,
           (plain + (plain_length / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE),
           (plain_length % HW_SCE_AES_BLOCK_BYTE_SIZE));

    /* Casting uint32_t pointer is used for address. */
    R_SCE_Aes128CbcEncryptUpdatePrivate((uint32_t *) (plain), (uint32_t *) (cipher), plain_length >> 2);
    memcpy(handle->current_initial_vector,
           (cipher + (plain_length - HW_SCE_AES_BLOCK_BYTE_SIZE)),
           HW_SCE_AES_CBC_IV_BYTE_SIZE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Using the handle specified in the first argument, handle, the R_SCE_AES128CBC_EncryptFinal() function writes
 * the calculation result to the second argument, cipher, and writes the length of the calculation result
 * to the third argument, cipher_length. The original intent was for a portion of the encryption
 * result that was not a multiple of 16 bytes to be written to the second argument.
 * However, as a result of the restriction that only multiples of 16 can be input to the Update function,
 * nothing is ever written to cipher, and 0 is always written to cipher_length. The arguments cipher and cipher_length
 * are provided for compatibility in anticipation of the time when this restriction is lifted.
 *
 * @param[in,out] handle        AES handler (work area)
 * @param[in,out] cipher        ciphertext data area (nothing ever written here)
 * @param[in,out] cipher_length ciphertext data length (0 always written here)
 *
 * @retval FSP_SUCCESS             Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CBC_EncryptFinal (sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes128cbcenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    *cipher_length = 0;
    memset(handle, 0, sizeof(sce_aes_handle_t));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes128CbcEncryptFinalPrivate((uint32_t *) (cipher), cipher_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CBC_DecryptInit() function performs preparations for the execution of an AES calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument
 * in the subsequent R_SCE_AES128CBC_DecryptUpdate() function and R_SCE_AES128CBC_DecryptFinal() function.
 *
 * @param[in,out] handle         AES handler (work area)
 * @param[in]     wrapped_key    128-bit AES wrapped key
 * @param[in]     initial_vector initialization vector area (16byte)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal wrapped key.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CBC_DecryptInit (sce_aes_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * initial_vector)
{
    memset(handle, 0, sizeof(sce_aes_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes128cbcdec_private_id = g_private_id_counter;
    handle->id                = g_aes128cbcdec_private_id;
    memcpy(handle->current_initial_vector, initial_vector, sizeof(handle->current_initial_vector));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes128CbcDecryptInitPrivate(wrapped_key, (uint32_t *) (handle->current_initial_vector));
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CBC_DecryptUpdate() function decrypts the second argument, cipher, utilizing the key index stored
 * in the handle specified in the first argument, handle, and writes the ongoing status to this first argument.
 * In addition, it writes the decryption result to the third argument, plain. After plaintext input is completed,
 * call R_SCE_AES128CBC_DecryptFinal().
 *
 * Specify areas for plain and cipher that do not overlap. For plain and cipher,
 * specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle        AES handler (work area)
 * @param[in]     cipher        ciphertext data area
 * @param[in,out] plain         plaintext data area
 * @param[in,out] cipher_length ciphertext data length (must be a multiple of 16)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CBC_DecryptUpdate (sce_aes_handle_t * handle,
                                         uint8_t          * cipher,
                                         uint8_t          * plain,
                                         uint32_t           cipher_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes128cbcdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->current_input_data_size = cipher_length;
    memcpy(handle->last_1_block_as_fraction,
           (cipher + (cipher_length / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE),
           (cipher_length % HW_SCE_AES_BLOCK_BYTE_SIZE));

    /* Casting uint32_t pointer is used for address. */
    R_SCE_Aes128CbcDecryptUpdatePrivate((uint32_t *) (cipher), (uint32_t *) (plain), cipher_length >> 2);
    memcpy(handle->current_initial_vector,
           (plain + (cipher_length - HW_SCE_AES_BLOCK_BYTE_SIZE)),
           HW_SCE_AES_CBC_IV_BYTE_SIZE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Using the handle specified in the first argument, handle, the R_SCE_AES128CBC_DecryptFinal() function writes
 * the calculation result to the second argument, plain, and writes the length of the calculation result
 * to the third argument, plain_length. The original intent was for a portion of the decryption
 * result that was not a multiple of 16 bytes to be written to the second argument.
 * However, as a result of the restriction that only multiples of 16 can be input to the Update function,
 * nothing is ever written to plain, and 0 is always written to plain_length. The arguments plain and plain_length
 * are provided for compatibility in anticipation of the time when this restriction is lifted.
 *
 * @param[in,out] handle       AES handler (work area)
 * @param[in,out] plain        plaintext data area (nothing ever written here)
 * @param[in,out] plain_length plaintext data length (0 always written here)
 *
 * @retval FSP_SUCCESS             Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CBC_DecryptFinal (sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes128cbcdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    *plain_length = 0;
    memset(handle, 0, sizeof(sce_aes_handle_t));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes128CbcDecryptFinalPrivate((uint32_t *) (plain), plain_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CBC_EncryptInit() function performs preparations for the execution of an AES calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument
 * in the subsequent R_SCE_AES256CBC_EncryptUpdate() function and R_SCE_AES256CBC_EncryptFinal() function.
 *
 * @param[in,out] handle         AES handler (work area)
 * @param[in]     wrapped_key    256-bit AES wrapped key
 * @param[in]     initial_vector initial vector area (16byte)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal wrapped key.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CBC_EncryptInit (sce_aes_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * initial_vector)
{
    memset(handle, 0, sizeof(sce_aes_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes256cbcenc_private_id = g_private_id_counter;
    handle->id                = g_aes256cbcenc_private_id;
    memcpy(handle->current_initial_vector, initial_vector, sizeof(handle->current_initial_vector));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes256CbcEncryptInitPrivate(wrapped_key, (uint32_t *) (handle->current_initial_vector));
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CBC_EncryptUpdate() function encrypts the second argument, plain, utilizing the key index stored
 * in the handle specified in the first argument, handle, and writes the ongoing status to this first argument.
 * In addition, it writes the encryption result to the third argument, cipher. After plaintext input is completed,
 * call R_SCE_AES256CBC_EncryptFinal().
 *
 * Specify areas for plain and cipher that do not overlap. For plain and cipher,
 * specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle       AES handler (work area)
 * @param[in]     plain        plaintext data area
 * @param[in,out] cipher       ciphertext data area
 * @param[in,out] plain_length plaintext data length (must be a multiple of 16)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CBC_EncryptUpdate (sce_aes_handle_t * handle,
                                         uint8_t          * plain,
                                         uint8_t          * cipher,
                                         uint32_t           plain_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes256cbcenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->current_input_data_size = plain_length;
    memcpy(handle->last_1_block_as_fraction,
           (plain + (plain_length / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE),
           (plain_length % HW_SCE_AES_BLOCK_BYTE_SIZE));

    /* Casting uint32_t pointer is used for address. */
    R_SCE_Aes256CbcEncryptUpdatePrivate((uint32_t *) (plain), (uint32_t *) (cipher), plain_length >> 2);
    memcpy(handle->current_initial_vector,
           cipher + (plain_length - HW_SCE_AES_BLOCK_BYTE_SIZE),
           HW_SCE_AES_CBC_IV_BYTE_SIZE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Using the handle specified in the first argument, handle, the R_SCE_AES256CBC_EncryptFinal() function writes
 * the calculation result to the second argument, cipher, and writes the length of the calculation result
 * to the third argument, cipher_length. The original intent was for a portion of the encryption
 * result that was not a multiple of 16 bytes to be written to the second argument.
 * However, as a result of the restriction that only multiples of 16 can be input to the Update function,
 * nothing is ever written to cipher, and 0 is always written to cipher_length. The arguments cipher and cipher_length
 * are provided for compatibility in anticipation of the time when this restriction is lifted.
 *
 * @param[in,out] handle        AES handler (work area)
 * @param[in,out] cipher        ciphertext data area (nothing ever written here)
 * @param[in,out] cipher_length ciphertext data length (0 always written here)
 *
 * @retval FSP_SUCCESS             Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CBC_EncryptFinal (sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes256cbcenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    *cipher_length = 0;
    memset(handle, 0, sizeof(sce_aes_handle_t));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes256CbcEncryptFinalPrivate((uint32_t *) (cipher), cipher_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CBC_DecryptInit() function performs preparations for the execution of an AES calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument
 * in the subsequent R_SCE_AES256CBC_DecryptUpdate() function and R_SCE_AES256CBC_DecryptFinal() function.
 *
 * @param[in,out] handle         AES handler (work area)
 * @param[in]     wrapped_key    256-bit AES wrapped key
 * @param[in]     initial_vector initialization vector area (16byte)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal wrapped key.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CBC_DecryptInit (sce_aes_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * initial_vector)
{
    memset(handle, 0, sizeof(sce_aes_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes256cbcdec_private_id = g_private_id_counter;
    handle->id                = g_aes256cbcdec_private_id;
    memcpy(handle->current_initial_vector, initial_vector, sizeof(handle->current_initial_vector));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes256CbcDecryptInitPrivate(wrapped_key, (uint32_t *) (handle->current_initial_vector));
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CBC_DecryptUpdate() function decrypts the second argument, cipher, utilizing the key index stored
 * in the handle specified in the first argument, handle, and writes the ongoing status to this first argument.
 * In addition, it writes the decryption result to the third argument, plain. After plaintext input is completed,
 * call R_SCE_AES256CBC_DecryptFinal().
 *
 * Specify areas for plain and cipher that do not overlap. For plain and cipher,
 * specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle        AES handler (work area)
 * @param[in]     cipher        ciphertext data area
 * @param[in,out] plain         plaintext data area
 * @param[in,out] cipher_length ciphertext data length (must be a multiple of 16)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CBC_DecryptUpdate (sce_aes_handle_t * handle,
                                         uint8_t          * cipher,
                                         uint8_t          * plain,
                                         uint32_t           cipher_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes256cbcdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->current_input_data_size = cipher_length;
    memcpy(handle->last_1_block_as_fraction,
           (cipher + (cipher_length / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE),
           (cipher_length % HW_SCE_AES_BLOCK_BYTE_SIZE));

    /* Casting uint32_t pointer is used for address. */
    R_SCE_Aes256CbcDecryptUpdatePrivate((uint32_t *) (cipher), (uint32_t *) (plain), cipher_length >> 2);
    memcpy(handle->current_initial_vector,
           plain + (cipher_length - HW_SCE_AES_BLOCK_BYTE_SIZE),
           HW_SCE_AES_CBC_IV_BYTE_SIZE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Using the handle specified in the first argument, handle, the R_SCE_AES256CBC_DecryptFinal() function writes
 * the calculation result to the second argument, plain, and writes the length of the calculation result
 * to the third argument, plain_length. The original intent was for a portion of the decryption
 * result that was not a multiple of 16 bytes to be written to the second argument.
 * However, as a result of the restriction that only multiples of 16 can be input to the Update function,
 * nothing is ever written to plain, and 0 is always written to plain_length. The arguments plain and plain_length
 * are provided for compatibility in anticipation of the time when this restriction is lifted.
 *
 * @param[in,out] handle       AES handler (work area)
 * @param[in,out] plain        plaintext data area (nothing ever written here)
 * @param[in,out] plain_length plaintext data length (0 always written here)
 *
 * @retval FSP_SUCCESS             Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CBC_DecryptFinal (sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length)
{
    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes256cbcdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    *plain_length = 0;
    memset(handle, 0, sizeof(sce_aes_handle_t));

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_Aes256CbcDecryptFinalPrivate((uint32_t *) (plain), plain_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128GCM_EncryptInit() function performs preparations for the execution of an GCM calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument in the subsequent
 * R_SCE_AES128GCM_EncryptUpdate() function and R_SCE_AES128GCM_EncryptFinal() function.
 *
 * @param[in,out] handle                AES-GCM handler (work area)
 * @param[in]     wrapped_key           128-bit AES wrapped key
 * @param[in]     initial_vector        initialization vector area (initial_vector_length byte)
 * @param[in]     initial_vector_length initialization vector length (1 ore more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128GCM_EncryptInit (sce_gcm_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * initial_vector,
                                       uint32_t                initial_vector_length)
{
    uint32_t hashed_ivec[4] =
    {
        0
    };
    fsp_err_t ercd = FSP_SUCCESS;

    if ((SCE_KEY_INDEX_TYPE_AES128 == wrapped_key->type) || (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == wrapped_key->type))
    {
        if (0 == initial_vector_length)
        {
            return FSP_ERR_CRYPTO_SCE_PARAMETER;
        }
    }
    else
    {
        if (SCE_KEY_INDEX_TYPE_AES128_FOR_TLS != wrapped_key->type)
        {
            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
    }

    memset(handle, 0, sizeof(sce_gcm_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes128gcmenc_private_id = g_private_id_counter;
    handle->id                = g_aes128gcmenc_private_id;
    if ((SCE_KEY_INDEX_TYPE_AES128 == wrapped_key->type) || (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == wrapped_key->type))
    {
        ercd = prepare_gcm_iv(initial_vector, initial_vector_length, wrapped_key, HW_SCE_AES128_KEY_INDEX_WORD_SIZE, hashed_ivec);
        if (FSP_SUCCESS != ercd)
        {
            memset(handle, 0, sizeof(sce_gcm_handle_t));

            return ercd;
        }
    }

    handle->flag_update_input_data = GCM_INPUT_DATA_AAD;

    return R_SCE_Aes128GcmEncryptInitPrivate(wrapped_key, hashed_ivec);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128GCM_EncryptUpdate() function encrypts the plaintext specified in the second argument, plain,
 * in GCM mode using the values specified for wrapped_key and initial_vector in R_SCE_AES128GCM_EncryptInit(),
 * along with the additional authentication data specified in the fifth argument, aad. Inside this function,
 * the data that is input by the user is buffered until the input values of aad and plain exceed 16 bytes.
 * After the input data from plain reaches 16 bytes or more, the encryption result is output
 * to the ciphertext data area specified in the third argument, cipher. The lengths of the plain and aad data to input
 * are respectively specified in the fourth argument, plain_data_length, and the sixth argument, aad_length. For these,
 * specify not the total byte count for the aad and plain input data, but rather the data length to input
 * when the user calls this function. If the input values plain and aad are not divisible by 16 bytes,
 * they will be padded inside the function. First process the data that is input from aad, and then process the data
 * that is input from plain. If aad data is input after starting to input plain data, an error will occur.
 * If aad data and plain data are input to this function at the same time, the aad data will be processed,
 * and then the function will transition to the plain data input state.
 *
 * Specify areas for plain and cipher that do not overlap. For plain, cipher, initial_vector, and aad, specify RAM addresses
 * that are multiples of 4
 *
 * @param[in,out] handle            AES-GCM handler (work area)
 * @param[in]     plain             plaintext data area
 * @param[in,out] cipher            ciphertext data area
 * @param[in]     plain_data_length plaintext data length (0 or more bytes)
 * @param[in]     aad               additional authentication data (aad_length byte)
 * @param[in]     aad_length        additional authentication data length (0 or more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         After the data from plain was input,
 *                                              an invalid handle was input from aad.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128GCM_EncryptUpdate (sce_gcm_handle_t * handle,
                                         uint8_t          * plain,
                                         uint8_t          * cipher,
                                         uint32_t           plain_data_length,
                                         uint8_t          * aad,
                                         uint32_t           aad_length)
{
    fsp_err_t ercd            = FSP_SUCCESS;
    uint32_t  length_rest     = 0;
    uint32_t  length_aad_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes128gcmenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (0 != aad_length)
    {
        if (GCM_INPUT_DATA_TEXT == handle->flag_update_input_data)
        {
            return FSP_ERR_CRYPTO_SCE_PARAMETER;
        }

        handle->all_received_aad_length += aad_length;
        if ((handle->buffering_aad_length + aad_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            memcpy((&handle->gcm_aad_buffer[0] + handle->buffering_aad_length),
                   aad,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

            /* Casting uint32_t pointer is used for address. */
            ercd = R_SCE_Aes128GcmEncryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                           HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
            length_aad_rest = aad_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);
            memset(handle->gcm_aad_buffer, 0, sizeof(handle->gcm_aad_buffer));
            if (length_aad_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
            {
                ercd = R_SCE_Aes128GcmEncryptUpdateAadPrivate(
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (aad + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length)),
                    ((length_aad_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
                length_aad_rest -= ((length_aad_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
            }

            handle->buffering_aad_length = 0;
            memcpy(handle->gcm_aad_buffer, aad + (aad_length - length_aad_rest), length_aad_rest);
            handle->buffering_aad_length = length_aad_rest;
        }
        else
        {
            memcpy(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length, aad, aad_length);
            handle->buffering_aad_length += aad_length;
        }
    }

    if (0 != plain_data_length)
    {
        if (GCM_INPUT_DATA_AAD == handle->flag_update_input_data)
        {
            handle->flag_update_input_data = GCM_INPUT_DATA_TEXT;
            if (0 != (handle->buffering_aad_length % HW_SCE_AES_BLOCK_BYTE_SIZE))
            {
                memset(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length,
                       0,
                       HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

                /* Casting uint32_t pointer is used for address. */
                ercd = R_SCE_Aes128GcmEncryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                               HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
                handle->buffering_aad_length = 0;
            }

            R_SCE_Aes128GcmEncryptUpdateTransitionPrivate();
        }

        handle->all_received_length += plain_data_length;
        if ((handle->buffering_length + plain_data_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            memcpy((&handle->gcm_buffer[0] + handle->buffering_length),
                   plain,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

            ercd = R_SCE_Aes128GcmEncryptUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (handle->gcm_buffer),
                HW_SCE_AES_BLOCK_BYTE_SIZE >> 2,
                (uint32_t *) (cipher));
            length_rest = plain_data_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
            memset(handle->gcm_buffer, 0, sizeof(handle->gcm_buffer));
            if (length_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
            {
                ercd = R_SCE_Aes128GcmEncryptUpdatePrivate(
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (plain + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                    ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2,
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (cipher + HW_SCE_AES_BLOCK_BYTE_SIZE));
                length_rest -= ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
            }

            handle->buffering_length = 0;
            memcpy(handle->gcm_buffer, plain + (plain_data_length - length_rest), length_rest);
            handle->buffering_length = length_rest;
        }
        else
        {
            memcpy(&handle->gcm_buffer[0] + handle->buffering_length, plain, plain_data_length);
            handle->buffering_length += plain_data_length;
        }
    }

    return ercd;
}

/*******************************************************************************************************************//**
 * If there is 16-byte fractional data indicated by the total data length of the value of plain that was input
 * by R_SCE_AES128GCM_EncryptUpdate (), the R_SCE_AES128GCM_EncryptFinal() function will output the result of encrypting
 * that fractional data to the ciphertext data area specified in the second argument, cipher. Here, the portion
 * that does not reach 16 bytes will be padded with zeros. The authentication tag is output to the fourth argument,
 * atag. For cipher and atag, specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle             AES-GCM handler (work area)
 * @param[in,out] cipher             ciphertext data area (cipher_data_length byte)
 * @param[in,out] cipher_data_length ciphertext data length (0 always written here)
 * @param[in,out] atag               authentication tag area
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128GCM_EncryptFinal (sce_gcm_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint32_t         * cipher_data_length,
                                        uint8_t          * atag)
{
    uint32_t aad_bit_size[2] =
    {
        0
    };
    uint32_t data_bit_size[2] =
    {
        0
    };
    fsp_err_t ercd = FSP_SUCCESS;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes128gcmenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (GCM_INPUT_DATA_AAD == handle->flag_update_input_data)
    {
        handle->flag_update_input_data = GCM_INPUT_DATA_TEXT;
        if (0 != (handle->buffering_aad_length % HW_SCE_AES_BLOCK_BYTE_SIZE))
        {
            memset(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length,
                   0,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

            /* Casting uint32_t pointer is used for address. */
            R_SCE_Aes128GcmEncryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                    HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
            handle->buffering_aad_length = 0;
        }

        R_SCE_Aes128GcmEncryptUpdateTransitionPrivate();
    }

    if ((0 != (handle->all_received_length % HW_SCE_AES_BLOCK_BYTE_SIZE)) || (0 == handle->all_received_length))
    {
        memset(handle->gcm_buffer + handle->buffering_length, 0,
               (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length));
    }

    aad_bit_size[0] = change_endian_long((handle->all_received_aad_length & SCE_HEX_E000000) >> 29U);
    aad_bit_size[1] = change_endian_long(handle->all_received_aad_length << 3U);

    data_bit_size[0]    = change_endian_long((handle->all_received_length & SCE_HEX_E000000) >> 29U);
    data_bit_size[1]    = change_endian_long(handle->all_received_length << 3U);
    *cipher_data_length = handle->all_received_length;

    ercd = R_SCE_Aes128GcmEncryptFinalPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) (handle->gcm_buffer),
        aad_bit_size,
        data_bit_size,
        (uint32_t *) cipher,
        (uint32_t *) atag);
    memset(handle, 0, sizeof(sce_gcm_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128GCM_DecryptInit() function performs preparations for the execution of an GCM calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument in the subsequent
 * R_SCE_AES128GCM_DecryptUpdate() function and R_SCE_AES128GCM_DecryptFinal() function.
 *
 * @param[in,out] handle                AES-GCM handler (work area)
 * @param[in]     wrapped_key           128-bit AES wrapped key
 * @param[in]     initial_vector        initialization vector area (initial_vector_length byte)
 * @param[in]     initial_vector_length initialization vector length (1 ore more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128GCM_DecryptInit (sce_gcm_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * initial_vector,
                                       uint32_t                initial_vector_length)
{
    uint32_t hashed_ivec[4] =
    {
        0
    };
    fsp_err_t ercd = FSP_SUCCESS;

    if ((SCE_KEY_INDEX_TYPE_AES128 == wrapped_key->type) || (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == wrapped_key->type))
    {
        if (0 == initial_vector_length)
        {
            return FSP_ERR_CRYPTO_SCE_PARAMETER;
        }
    }
    else
    {
        if ((SCE_KEY_INDEX_TYPE_AES128_FOR_TLS != wrapped_key->type)
        && (SCE_KEY_INDEX_TYPE_AES128_GCM_WITH_IV != wrapped_key->type))
        {
            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
    }

    memset(handle, 0, sizeof(sce_gcm_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes128gcmdec_private_id = g_private_id_counter;
    handle->id                = g_aes128gcmdec_private_id;
    if ((SCE_KEY_INDEX_TYPE_AES128 == wrapped_key->type) || (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == wrapped_key->type))
    {
        ercd = prepare_gcm_iv(initial_vector, initial_vector_length, wrapped_key, HW_SCE_AES128_KEY_INDEX_WORD_SIZE, hashed_ivec);
        if (FSP_SUCCESS != ercd)
        {
            memset(handle, 0, sizeof(sce_gcm_handle_t));

            return ercd;
        }
    }

    handle->flag_update_input_data = GCM_INPUT_DATA_AAD;

    return R_SCE_Aes128GcmDecryptInitPrivate(wrapped_key, hashed_ivec);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128GCM_DecryptUpdate() function decrypts the ciphertext specified in the second argument, cipher,
 * in GCM mode using the values specified for wrapped_key and initial_vector in R_SCE_AES128GCM_DecryptInit(),
 * along with the additional authentication data specified in the fifth argument, aad. Inside this function,
 * the data that is input by the user is buffered until the input values of aad and plain exceed 16 bytes.
 * After the input data from cipher reaches 16 bytes or more, the decryption result is output to the plaintext data area
 * specified in the third argument, plain. The lengths of the cipher and aad data to input are respectively specified
 * in the fourth argument, cipher_data_length, and the sixth argument, aad_length. For these, specify not the total byte count
 * for the aad and cipher input data, but rather the data length to input when the user calls this function.
 * If the input values cipher and aad are not divisible by 16 bytes, they will be padded inside the function.
 * First process the data that is input from aad, and then process the data that is input from cipher.
 * If aad data is input after starting to input cipher data, an error will occur. If aad data and cipher data are
 * input to this function at the same time, the aad data will be processed, and then the function will transition
 * to the cipher data input state.
 * Specify areas for plain and cipher that do not overlap. For plain, cipher, stage, initial_vector, and aad, specify RAM addresses
 * that are multiples of 4.
 *
 * @param[in,out] handle             AES-GCM handler (work area)
 * @param[in,out] cipher             ciphertext data area
 * @param[in]     plain              plaintext data area
 * @param[in]     cipher_data_length ciphertext data length (0 or more bytes)
 * @param[in]     aad                additional authentication data (aad_length byte)
 * @param[in]     aad_length         additional authentication data length (0 or more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         After the data from plain was input,
 *                                              an invalid handle was input from aad.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128GCM_DecryptUpdate (sce_gcm_handle_t * handle,
                                         uint8_t          * cipher,
                                         uint8_t          * plain,
                                         uint32_t           cipher_data_length,
                                         uint8_t          * aad,
                                         uint32_t           aad_length)
{
    fsp_err_t ercd            = FSP_SUCCESS;
    uint32_t  length_rest     = 0;
    uint32_t  length_aad_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes128gcmdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (0 != aad_length)
    {
        if (GCM_INPUT_DATA_TEXT == handle->flag_update_input_data)
        {
            return FSP_ERR_CRYPTO_SCE_PARAMETER;
        }

        handle->all_received_aad_length += aad_length;
        if ((handle->buffering_aad_length + aad_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            memcpy((&handle->gcm_aad_buffer[0] + handle->buffering_aad_length),
                   aad,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

            /* Casting uint32_t pointer is used for address. */
            ercd = R_SCE_Aes128GcmDecryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                           HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
            length_aad_rest = aad_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);
            memset(handle->gcm_aad_buffer, 0, sizeof(handle->gcm_aad_buffer));
            if (length_aad_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
            {
                ercd = R_SCE_Aes128GcmDecryptUpdateAadPrivate(
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (aad + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length)),
                    ((length_aad_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
                length_aad_rest -= ((length_aad_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
            }

            handle->buffering_aad_length = 0;
            memcpy(handle->gcm_aad_buffer, aad + (aad_length - length_aad_rest), length_aad_rest);
            handle->buffering_aad_length = length_aad_rest;
        }
        else
        {
            memcpy(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length, aad, aad_length);
            handle->buffering_aad_length += aad_length;
        }
    }

    if (0 != cipher_data_length)
    {
        if (GCM_INPUT_DATA_AAD == handle->flag_update_input_data)
        {
            handle->flag_update_input_data = GCM_INPUT_DATA_TEXT;
            if (0 != (handle->buffering_aad_length % HW_SCE_AES_BLOCK_BYTE_SIZE))
            {
                memset(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length,
                       0,
                       HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

                /* Casting uint32_t pointer is used for address. */
                ercd = R_SCE_Aes128GcmDecryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                               HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
                handle->buffering_aad_length = 0;
            }

            R_SCE_Aes128GcmDecryptUpdateTransitionPrivate();
        }

        handle->all_received_length += cipher_data_length;
        if ((handle->buffering_length + cipher_data_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            memcpy((&handle->gcm_buffer[0] + handle->buffering_length),
                   cipher,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

            ercd = R_SCE_Aes128GcmDecryptUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (handle->gcm_buffer),
                HW_SCE_AES_BLOCK_BYTE_SIZE >> 2,
                (uint32_t *) (plain));
            length_rest = cipher_data_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
            memset(handle->gcm_buffer, 0, sizeof(handle->gcm_buffer));
            if (length_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
            {
                ercd = R_SCE_Aes128GcmDecryptUpdatePrivate(
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (cipher + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                    ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2,
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (plain + HW_SCE_AES_BLOCK_BYTE_SIZE));
                length_rest -= ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
            }

            handle->buffering_length = 0;
            memcpy(handle->gcm_buffer, cipher + (cipher_data_length - length_rest), length_rest);
            handle->buffering_length = length_rest;
        }
        else
        {
            memcpy(&handle->gcm_buffer[0] + handle->buffering_length, cipher, cipher_data_length);
            handle->buffering_length += cipher_data_length;
        }
    }

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128GCM_DecryptFinal() function decrypts, in GCM mode, the fractional ciphertext specified
 * by R_SCE_AES128GCM_DecryptUpdate() that does not reach 16 bytes, and ends GCM decryption.
 * The encryption data and authentication tag are respectively output to the plaintext data area specified
 * in the second argument, plain, and the authentication tag area specified in the fourth argument, atag.
 * The decoded data length is output to the third argument, plain_data_length. If authentication fails,
 * the return value will be TSIP_ERR_AUTHENTICATION. For the fourth argument, atag, input 16 bytes or less.
 * If it is less than 16 bytes, it will be padded with zeros inside the function. For plain and atag,
 * specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle             AES-GCM handler (work area)
 * @param[in,out] plain              plaintext data area (cipher_data_length byte)
 * @param[in,out] plain_data_length  plaintext data length (0 always written here)
 * @param[in,out] atag               authentication tag area (atag_length byte)
 * @param[in]     atag_length        authentication tag length (4,8,12,13,14,15,16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION    Authentication failed
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128GCM_DecryptFinal (sce_gcm_handle_t * handle,
                                        uint8_t          * plain,
                                        uint32_t         * plain_data_length,
                                        uint8_t          * atag,
                                        uint32_t           atag_length)
{
    uint32_t aad_bit_size[2] =
    {
        0
    };
    uint32_t data_bit_size[2] =
    {
        0
    };
    uint32_t atag_length_tmp                 = 0;
    uint32_t atag_tmp[16 / sizeof(uint32_t)] =
    {
        0                              /* atag_tmp is initialized with 0. */
    };
    fsp_err_t ercd = FSP_SUCCESS;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes128gcmdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (((1 > atag_length) || (16 < atag_length)) || ((atag_length < 12) && (0 != (atag_length % 4))))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (GCM_INPUT_DATA_AAD == handle->flag_update_input_data)
    {
        handle->flag_update_input_data = GCM_INPUT_DATA_TEXT;
        if (0 != (handle->buffering_aad_length % HW_SCE_AES_BLOCK_BYTE_SIZE))
        {
            memset(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length,
                   0,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

            /* Casting uint32_t pointer is used for address. */
            R_SCE_Aes128GcmDecryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                    HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
            handle->buffering_aad_length = 0;
        }

        R_SCE_Aes128GcmDecryptUpdateTransitionPrivate();
    }

    if ((0 != (handle->all_received_length % HW_SCE_AES_BLOCK_BYTE_SIZE)) || (0 == handle->all_received_length))
    {
        memset(handle->gcm_buffer + handle->buffering_length, 0,
               (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length));
    }

    memcpy(atag_tmp, atag, atag_length);

    aad_bit_size[0] = change_endian_long((handle->all_received_aad_length & SCE_HEX_E000000) >> 29U);
    aad_bit_size[1] = change_endian_long(handle->all_received_aad_length << 3U);

    data_bit_size[0] = change_endian_long((handle->all_received_length & SCE_HEX_E000000) >> 29U);
    data_bit_size[1] = change_endian_long(handle->all_received_length << 3U);

    atag_length_tmp = change_endian_long(atag_length);

    *plain_data_length = handle->all_received_length;

    ercd = R_SCE_Aes128GcmDecryptFinalPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) handle->gcm_buffer,
        (uint32_t *) atag_tmp,
        aad_bit_size,
        data_bit_size,
        &atag_length_tmp,
        (uint32_t *) plain);
    memset(handle, 0, sizeof(sce_gcm_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256GCM_EncryptInit() function performs preparations for the execution of an GCM calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument in the subsequent
 * R_SCE_AES256GCM_EncryptUpdate() function and R_SCE_AES256GCM_EncryptFinal() function.
 *
 * @param[in,out] handle                AES-GCM handler (work area)
 * @param[in]     wrapped_key           256-bit AES wrapped key
 * @param[in]     initial_vector        initialization vector area (initial_vector_length byte)
 * @param[in]     initial_vector_length initialization vector length (1 ore more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256GCM_EncryptInit (sce_gcm_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * initial_vector,
                                       uint32_t                initial_vector_length)
{
    uint32_t hashed_ivec[4] =
    {
        0
    };
    fsp_err_t ercd = FSP_SUCCESS;

    if ((SCE_KEY_INDEX_TYPE_AES256 == wrapped_key->type) ||
        (SCE_KEY_INDEX_TYPE_AES256_GCM_FOR_DLMS_COSEM == wrapped_key->type))
    {
        if (0 == initial_vector_length)
        {
            return FSP_ERR_CRYPTO_SCE_PARAMETER;
        }
    }

    memset(handle, 0, sizeof(sce_gcm_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes256gcmenc_private_id = g_private_id_counter;
    handle->id                = g_aes256gcmenc_private_id;
    ercd = prepare_gcm_iv(initial_vector, initial_vector_length, wrapped_key, HW_SCE_AES256_KEY_INDEX_WORD_SIZE, hashed_ivec);
    if (FSP_SUCCESS != ercd)
    {
        memset(handle, 0, sizeof(sce_gcm_handle_t));

        return ercd;
    }

    handle->flag_update_input_data = GCM_INPUT_DATA_AAD;

    return R_SCE_Aes256GcmEncryptInitPrivate(wrapped_key, hashed_ivec);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256GCM_EncryptUpdate() function encrypts the plaintext specified in the second argument, plain,
 * in GCM mode using the values specified for wrapped_key and initial_vector in R_SCE_AES256GCM_EncryptInit(),
 * along with the additional authentication data specified in the fifth argument, aad. Inside this function,
 * the data that is input by the user is buffered until the input values of aad and plain exceed 16 bytes.
 * After the input data from plain reaches 16 bytes or more, the encryption result is output
 * to the ciphertext data area specified in the third argument, cipher. The lengths of the plain and aad data to input
 * are respectively specified in the fourth argument, plain_data_length, and the sixth argument, aad_length. For these,
 * specify not the total byte count for the aad and plain input data, but rather the data length to input
 * when the user calls this function. If the input values plain and aad are not divisible by 16 bytes,
 * they will be padded inside the function. First process the data that is input from aad, and then process the data
 * that is input from plain. If aad data is input after starting to input plain data, an error will occur.
 * If aad data and plain data are input to this function at the same time, the aad data will be processed,
 * and then the function will transition to the plain data input state.
 *
 * Specify areas for plain and cipher that do not overlap. For plain, cipher, initial_vector, and aad, specify RAM addresses
 * that are multiples of 4
 *
 * @param[in,out] handle            AES-GCM handler (work area)
 * @param[in]     plain             plaintext data area
 * @param[in,out] cipher            ciphertext data area
 * @param[in]     plain_data_length plaintext data length (0 or more bytes)
 * @param[in]     aad               additional authentication data (aad_length byte)
 * @param[in]     aad_length        additional authentication data length (0 or more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         After the data from plain was input,
 *                                              an invalid handle was input from aad.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256GCM_EncryptUpdate (sce_gcm_handle_t * handle,
                                         uint8_t          * plain,
                                         uint8_t          * cipher,
                                         uint32_t           plain_data_length,
                                         uint8_t          * aad,
                                         uint32_t           aad_length)
{
    fsp_err_t ercd            = FSP_SUCCESS;
    uint32_t  length_rest     = 0;
    uint32_t  length_aad_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes256gcmenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (0 != aad_length)
    {
        if (GCM_INPUT_DATA_TEXT == handle->flag_update_input_data)
        {
            return FSP_ERR_CRYPTO_SCE_PARAMETER;
        }

        handle->all_received_aad_length += aad_length;
        if ((handle->buffering_aad_length + aad_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            memcpy((&handle->gcm_aad_buffer[0] + handle->buffering_aad_length),
                   aad,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

            /* Casting uint32_t pointer is used for address. */
            ercd =
                R_SCE_Aes256GcmEncryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                        (HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
            length_aad_rest = aad_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);
            memset(handle->gcm_aad_buffer, 0, sizeof(handle->gcm_aad_buffer));
            if (length_aad_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
            {
                ercd = R_SCE_Aes256GcmEncryptUpdateAadPrivate(
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (aad + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length)),
                    ((length_aad_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
                length_aad_rest -= ((length_aad_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
            }

            handle->buffering_aad_length = 0;
            memcpy(handle->gcm_aad_buffer, aad + (aad_length - length_aad_rest), length_aad_rest);
            handle->buffering_aad_length = length_aad_rest;
        }
        else
        {
            memcpy(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length, aad, aad_length);
            handle->buffering_aad_length += aad_length;
        }
    }

    if (0 != plain_data_length)
    {
        if (GCM_INPUT_DATA_AAD == handle->flag_update_input_data)
        {
            handle->flag_update_input_data = GCM_INPUT_DATA_TEXT;
            if (0 != (handle->buffering_aad_length % HW_SCE_AES_BLOCK_BYTE_SIZE))
            {
                memset(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length,
                       0,
                       HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

                /* Casting uint32_t pointer is used for address. */
                ercd = R_SCE_Aes256GcmEncryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                               HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
                handle->buffering_aad_length = 0;
            }

            R_SCE_Aes256GcmEncryptUpdateTransitionPrivate();
        }

        handle->all_received_length += plain_data_length;
        if ((handle->buffering_length + plain_data_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            memcpy((&handle->gcm_buffer[0] + handle->buffering_length),
                   plain,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

            ercd = R_SCE_Aes256GcmEncryptUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (handle->gcm_buffer),
                HW_SCE_AES_BLOCK_BYTE_SIZE >> 2,
                (uint32_t *) (cipher));
            length_rest = plain_data_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
            memset(handle->gcm_buffer, 0, sizeof(handle->gcm_buffer));
            if (length_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
            {
                ercd = R_SCE_Aes256GcmEncryptUpdatePrivate(
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (plain + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                    ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2,
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (cipher + HW_SCE_AES_BLOCK_BYTE_SIZE));
                length_rest -= ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
            }

            handle->buffering_length = 0;
            memcpy(handle->gcm_buffer, plain + (plain_data_length - length_rest), length_rest);
            handle->buffering_length = length_rest;
        }
        else
        {
            memcpy(&handle->gcm_buffer[0] + handle->buffering_length, plain, plain_data_length);
            handle->buffering_length += plain_data_length;
        }
    }

    return ercd;
}

/*******************************************************************************************************************//**
 * If there is 16-byte fractional data indicated by the total data length of the value of plain that was input
 * by R_SCE_AES256GCM_EncryptUpdate (), the R_SCE_AES256GCM_EncryptFinal() function will output the result of encrypting
 * that fractional data to the ciphertext data area specified in the second argument, cipher. Here, the portion
 * that does not reach 16 bytes will be padded with zeros. The authentication tag is output to the fourth argument,
 * atag. For cipher and atag, specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle             AES-GCM handler (work area)
 * @param[in,out] cipher             ciphertext data area (cipher_data_length byte)
 * @param[in,out] cipher_data_length ciphertext data length (0 always written here)
 * @param[in,out] atag               authentication tag area
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256GCM_EncryptFinal (sce_gcm_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint32_t         * cipher_data_length,
                                        uint8_t          * atag)
{
    uint32_t aad_bit_size[2] =
    {
        0
    };
    uint32_t data_bit_size[2] =
    {
        0
    };
    fsp_err_t ercd = FSP_SUCCESS;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes256gcmenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (GCM_INPUT_DATA_AAD == handle->flag_update_input_data)
    {
        handle->flag_update_input_data = GCM_INPUT_DATA_TEXT;
        if (0 != (handle->buffering_aad_length % HW_SCE_AES_BLOCK_BYTE_SIZE))
        {
            memset(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length,
                   0,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

            /* Casting uint32_t pointer is used for address. */
            R_SCE_Aes256GcmEncryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                    HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
            handle->buffering_aad_length = 0;
        }

        R_SCE_Aes256GcmEncryptUpdateTransitionPrivate();
    }

    if ((0 != (handle->all_received_length % HW_SCE_AES_BLOCK_BYTE_SIZE)) || (0 == handle->all_received_length))
    {
        memset(handle->gcm_buffer + handle->buffering_length, 0,
               (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length));
    }

    aad_bit_size[0] = change_endian_long((handle->all_received_aad_length & SCE_HEX_E000000) >> 29U);
    aad_bit_size[1] = change_endian_long(handle->all_received_aad_length << 3U);

    data_bit_size[0]    = change_endian_long((handle->all_received_length & SCE_HEX_E000000) >> 29U);
    data_bit_size[1]    = change_endian_long(handle->all_received_length << 3U);
    *cipher_data_length = handle->all_received_length;

    ercd = R_SCE_Aes256GcmEncryptFinalPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) (handle->gcm_buffer),
        aad_bit_size,
        data_bit_size,
        (uint32_t *) cipher,
        (uint32_t *) atag);
    memset(handle, 0, sizeof(sce_gcm_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256GCM_DecryptInit() function performs preparations for the execution of an GCM calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument in the subsequent
 * R_SCE_AES256GCM_DecryptUpdate() function and R_SCE_AES256GCM_DecryptFinal() function.
 *
 * @param[in,out] handle                AES-GCM handler (work area)
 * @param[in]     wrapped_key           256-bit AES wrapped key
 * @param[in]     initial_vector        initialization vector area (initial_vector_length byte)
 * @param[in]     initial_vector_length initialization vector length (1 ore more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256GCM_DecryptInit (sce_gcm_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * initial_vector,
                                       uint32_t                initial_vector_length)
{
    uint32_t hashed_ivec[4] =
    {
        0
    };
    fsp_err_t ercd = FSP_SUCCESS;

    if (0 == initial_vector_length)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    memset(handle, 0, sizeof(sce_gcm_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes256gcmdec_private_id = g_private_id_counter;
    handle->id                = g_aes256gcmdec_private_id;
    memcpy(handle->wrapped_key.value, wrapped_key->value, HW_SCE_AES256_KEY_INDEX_WORD_SIZE * 4);
    ercd = prepare_gcm_iv(initial_vector, initial_vector_length, wrapped_key, HW_SCE_AES256_KEY_INDEX_WORD_SIZE, hashed_ivec);
    if (FSP_SUCCESS != ercd)
    {
        memset(handle, 0, sizeof(sce_gcm_handle_t));

        return ercd;
    }

    handle->flag_update_input_data = GCM_INPUT_DATA_AAD;

    return R_SCE_Aes256GcmDecryptInitPrivate(wrapped_key, hashed_ivec);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256GCM_DecryptUpdate() function decrypts the ciphertext specified in the second argument, cipher,
 * in GCM mode using the values specified for wrapped_key and initial_vector in R_SCE_AES256GCM_DecryptInit(),
 * along with the additional authentication data specified in the fifth argument, aad. Inside this function,
 * the data that is input by the user is buffered until the input values of aad and plain exceed 16 bytes.
 * After the input data from cipher reaches 16 bytes or more, the decryption result is output to the plaintext data area
 * specified in the third argument, plain. The lengths of the cipher and aad data to input are respectively specified
 * in the fourth argument, cipher_data_length, and the sixth argument, aad_length. For these, specify not the total byte count
 * for the aad and cipher input data, but rather the data length to input when the user calls this function.
 * If the input values cipher and aad are not divisible by 16 bytes, they will be padded inside the function.
 * First process the data that is input from aad, and then process the data that is input from cipher.
 * If aad data is input after starting to input cipher data, an error will occur. If aad data and cipher data are
 * input to this function at the same time, the aad data will be processed, and then the function will transition
 * to the cipher data input state.
 * Specify areas for plain and cipher that do not overlap. For plain, cipher, stage, initial_vector, and aad, specify RAM addresses
 * that are multiples of 4.
 *
 * @param[in,out] handle             AES-GCM handler (work area)
 * @param[in,out] cipher             ciphertext data area
 * @param[in]     plain              plaintext data area
 * @param[in]     cipher_data_length ciphertext data length (0 or more bytes)
 * @param[in]     aad                additional authentication data (aad_length byte)
 * @param[in]     aad_length         additional authentication data length (0 or more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         After the data from plain was input,
 *                                              an invalid handle was input from aad.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256GCM_DecryptUpdate (sce_gcm_handle_t * handle,
                                         uint8_t          * cipher,
                                         uint8_t          * plain,
                                         uint32_t           cipher_data_length,
                                         uint8_t          * aad,
                                         uint32_t           aad_length)
{
    fsp_err_t ercd            = FSP_SUCCESS;
    uint32_t  length_rest     = 0;
    uint32_t  length_aad_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes256gcmdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (0 != aad_length)
    {
        if (GCM_INPUT_DATA_TEXT == handle->flag_update_input_data)
        {
            return FSP_ERR_CRYPTO_SCE_PARAMETER;
        }

        handle->all_received_aad_length += aad_length;
        if ((handle->buffering_aad_length + aad_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            memcpy((&handle->gcm_aad_buffer[0] + handle->buffering_aad_length),
                   aad,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

            /* Casting uint32_t pointer is used for address. */
            ercd = R_SCE_Aes256GcmDecryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                           HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
            length_aad_rest = aad_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);
            memset(handle->gcm_aad_buffer, 0, sizeof(handle->gcm_aad_buffer));
            if (length_aad_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
            {
                ercd = R_SCE_Aes256GcmDecryptUpdateAadPrivate(
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (aad + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length)),
                    ((length_aad_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
                length_aad_rest -= ((length_aad_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
            }

            handle->buffering_aad_length = 0;
            memcpy(handle->gcm_aad_buffer, aad + (aad_length - length_aad_rest), length_aad_rest);
            handle->buffering_aad_length = length_aad_rest;
        }
        else
        {
            memcpy(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length, aad, aad_length);
            handle->buffering_aad_length += aad_length;
        }
    }

    if (0 != cipher_data_length)
    {
        if (GCM_INPUT_DATA_AAD == handle->flag_update_input_data)
        {
            handle->flag_update_input_data = GCM_INPUT_DATA_TEXT;
            if (0 != (handle->buffering_aad_length % HW_SCE_AES_BLOCK_BYTE_SIZE))
            {
                memset(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length,
                       0,
                       HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

                /* Casting uint32_t pointer is used for address. */
                ercd = R_SCE_Aes256GcmDecryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                               HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
                handle->buffering_aad_length = 0;
            }

            R_SCE_Aes256GcmDecryptUpdateTransitionPrivate();
        }

        handle->all_received_length += cipher_data_length;
        if ((handle->buffering_length + cipher_data_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            memcpy((&handle->gcm_buffer[0] + handle->buffering_length),
                   cipher,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

            ercd = R_SCE_Aes256GcmDecryptUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (handle->gcm_buffer),
                HW_SCE_AES_BLOCK_BYTE_SIZE >> 2,
                (uint32_t *) (plain));
            length_rest = cipher_data_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
            memset(handle->gcm_buffer, 0, sizeof(handle->gcm_buffer));
            if (length_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
            {
                ercd = R_SCE_Aes256GcmDecryptUpdatePrivate(
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (cipher + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                    ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2,
                    /* Casting uint32_t pointer is used for address. */
                    (uint32_t *) (plain + HW_SCE_AES_BLOCK_BYTE_SIZE));
                length_rest -= ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
            }

            handle->buffering_length = 0;
            memcpy(handle->gcm_buffer, cipher + (cipher_data_length - length_rest), length_rest);
            handle->buffering_length = length_rest;
        }
        else
        {
            memcpy(&handle->gcm_buffer[0] + handle->buffering_length, cipher, cipher_data_length);
            handle->buffering_length += cipher_data_length;
        }
    }

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256GCM_DecryptFinal() function decrypts, in GCM mode, the fractional ciphertext specified
 * by R_SCE_AES256GCM_DecryptUpdate() that does not reach 16 bytes, and ends GCM decryption.
 * The encryption data and authentication tag are respectively output to the plaintext data area specified
 * in the second argument, plain, and the authentication tag area specified in the fourth argument, atag.
 * The decoded data length is output to the third argument, plain_data_length. If authentication fails,
 * the return value will be TSIP_ERR_AUTHENTICATION. For the fourth argument, atag, input 16 bytes or less.
 * If it is less than 16 bytes, it will be padded with zeros inside the function. For plain and atag,
 * specify RAM addresses that are multiples of 4.
 *
 * @param[in,out] handle             AES-GCM handler (work area)
 * @param[in,out] plain              plaintext data area (cipher_data_length byte)
 * @param[in,out] plain_data_length  plaintext data length (0 always written here)
 * @param[in,out] atag               authentication tag area (atag_length byte)
 * @param[in]     atag_length        authentication tag length (4,8,12,13,14,15,16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION    Authentication failed
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256GCM_DecryptFinal (sce_gcm_handle_t * handle,
                                        uint8_t          * plain,
                                        uint32_t         * plain_data_length,
                                        uint8_t          * atag,
                                        uint32_t           atag_length)
{
    uint32_t aad_bit_size[2] =
    {
        0
    };
    uint32_t data_bit_size[2] =
    {
        0
    };
    uint32_t atag_length_tmp                 = 0;
    uint32_t atag_tmp[16 / sizeof(uint32_t)] =
    {
        0                              /* atag_tmp is initialized with 0. */
    };
    fsp_err_t ercd = FSP_SUCCESS;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes256gcmdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (((1 > atag_length) || (16 < atag_length)) || ((atag_length < 12) && (0 != (atag_length % 4))))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (GCM_INPUT_DATA_AAD == handle->flag_update_input_data)
    {
        handle->flag_update_input_data = GCM_INPUT_DATA_TEXT;
        if (0 != (handle->buffering_aad_length % HW_SCE_AES_BLOCK_BYTE_SIZE))
        {
            memset(&handle->gcm_aad_buffer[0] + handle->buffering_aad_length,
                   0,
                   HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_aad_length);

            /* Casting uint32_t pointer is used for address. */
            R_SCE_Aes256GcmDecryptUpdateAadPrivate((uint32_t *) (handle->gcm_aad_buffer),
                                                    HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
            handle->buffering_aad_length = 0;
        }

        R_SCE_Aes256GcmDecryptUpdateTransitionPrivate();
    }

    if ((0 != (handle->all_received_length % HW_SCE_AES_BLOCK_BYTE_SIZE)) || (0 == handle->all_received_length))
    {
        memset(handle->gcm_buffer + handle->buffering_length, 0,
               (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length));
    }

    memcpy(atag_tmp, atag, atag_length);

    aad_bit_size[0] = change_endian_long((handle->all_received_aad_length & SCE_HEX_E000000) >> 29U);
    aad_bit_size[1] = change_endian_long(handle->all_received_aad_length << 3U);

    data_bit_size[0] = change_endian_long((handle->all_received_length & SCE_HEX_E000000) >> 29U);
    data_bit_size[1] = change_endian_long(handle->all_received_length << 3U);

    atag_length_tmp = change_endian_long(atag_length);

    *plain_data_length = handle->all_received_length;

    ercd = R_SCE_Aes256GcmDecryptFinalPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) handle->gcm_buffer,
        (uint32_t *) atag_tmp,
        aad_bit_size,
        data_bit_size,
        &atag_length_tmp,
        (uint32_t *) plain);
    memset(handle, 0, sizeof(sce_gcm_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CCM_EncryptInit() function prepares to perform CCM computation and writes the result to the first
 * argument, handle. The succeeding functions R_SCE_AES128CCM_EncryptUpdate() and R_SCE_AES128CCM_EncryptFinal()
 * use handle as an argument.
 *
 * @param[in,out] handle         AES-CCM handler (work area)
 * @param[in]     wrapped_key    128-bit AES wrapped key
 * @param[in]     nonce          Nonce
 * @param[in]     nonce_length   Nonce data length (7 to 13 bytes)
 * @param[in]     adata          additional authentication data
 * @param[in]     a_length       additional authentication data length (0 to 110 bytes)
 * @param[in]     payload_length Payload length (any number of bytes)
 * @param[in]     mac_length     MAC length (4, 6, 8, 10, 12, 14, or 16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CCM_EncryptInit (sce_ccm_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * nonce,
                                       uint32_t                nonce_length,
                                       uint8_t               * adata,
                                       uint8_t                 a_length,
                                       uint32_t                payload_length,
                                       uint32_t                mac_length)
{
    uint32_t formatted_length = 0;

    memset(handle, 0, sizeof(sce_ccm_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes128ccmenc_private_id = g_private_id_counter;
    handle->id                = g_private_id_counter;
    memcpy(&handle->wrapped_key, wrapped_key, sizeof(sce_aes_wrapped_key_t));

    aes_ccm_b_counter_formatter(nonce,
                                nonce_length,
                                adata,
                                a_length,
                                payload_length,
                                mac_length,
                                handle->counter,
                                handle->formatted_data,
                                &formatted_length);

    return R_SCE_Aes128CcmEncryptInitPrivate(wrapped_key,
                                       /* Casting uint32_t pointer is used for address. */
                                              (uint32_t *) handle->counter,
                                              (uint32_t *) handle->formatted_data,
                                              formatted_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CCM_EncryptUpdate() function encrypts the plaintext specified in the second argument, plain,
 * in CCM mode using the values specified by wrapped_key, nonce, and adata in R_SCE_AES128CCM_EncryptInit().
 * This function buffers internally the data input by the user until the input value of plain exceeds 16 bytes.
 * Once the amount of plain input data is 16 bytes or greater, the encrypted result is output to cipher,
 * which is specified in the third argument. Use payload_length in R_SCE_AES128CCM_EncryptInit() to specify the total data
 * length of plain that will be input. Use plain_length in this function to specify the data length to be input
 * when the user calls this function. If the input value of plain is less than 16 bytes, the function performs
 * padding internally.
 *
 * Ensure that the areas allocated to plain and cipher do not overlap. Also, specify RAM addresses that are
 * multiples of 4 for plain and cipher.
 *
 * @param[in,out] handle       AES-CCM handler (work area)
 * @param[in]     plain        plaintext data area
 * @param[in,out] cipher       ciphertext data area
 * @param[in]     plain_length plaintext data length
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CCM_EncryptUpdate (sce_ccm_handle_t * handle,
                                         uint8_t          * plain,
                                         uint8_t          * cipher,
                                         uint32_t           plain_length)
{
    uint32_t length_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes128ccmenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->all_received_length += plain_length;
    if ((handle->buffering_length + plain_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
    {
        memcpy((&handle->ccm_buffer[0] + handle->buffering_length),
               plain,
               HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

        /* Casting uint32_t pointer is used for address. */
        R_SCE_Aes128CcmEncryptUpdatePrivate((uint32_t *) handle->ccm_buffer,
                                             (uint32_t *) cipher,
                                             HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
        length_rest = plain_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
        if (length_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            R_SCE_Aes128CcmEncryptUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (plain + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                (uint32_t *)
                (cipher + HW_SCE_AES_BLOCK_BYTE_SIZE),
                ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
            length_rest -= ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
        }

        handle->buffering_length = 0;
        memset(handle->ccm_buffer, 0, sizeof(handle->ccm_buffer));
        memcpy(handle->ccm_buffer, plain + (plain_length - length_rest), length_rest);
        handle->buffering_length = length_rest;
    }
    else
    {
        memcpy(&handle->ccm_buffer[0] + handle->buffering_length, plain, plain_length);
        handle->buffering_length += plain_length;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * If the data length of plain input in R_SCE_AES128CCM_EncryptUpdate() results in leftover data after 16 bytes,
 * the R_SCE_AES128CCM_EncryptFinal() function outputs the leftover encrypted data to cipher, which is specified
 * in the second argument. The MAC value is output to the fourth argument, mac. Set the fifth argument, mac_length
 * to the same value as that specified for the argument mac_length in Aes128CcmEncryptInit(). Also, specify RAM addresses
 * that are multiples of 4 for cipher and mac.
 *
 * @param[in,out] handle        AES-CCM handler (work area)
 * @param[in,out] cipher        ciphertext data area
 * @param[in,out] cipher_length ciphertext data length
 * @param[in,out] mac           MAC area
 * @param[in]     mac_length    MAC length (4, 6, 8, 10, 12, 14, or 16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CCM_EncryptFinal (sce_ccm_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint32_t         * cipher_length,
                                        uint8_t          * mac,
                                        uint32_t           mac_length)
{
    fsp_err_t ercd                           = FSP_SUCCESS;
    uint32_t  length_tmp                     = 0;
    uint32_t  mac_length_tmp                 = 0;
    uint32_t  mac_tmp[16 / sizeof(uint32_t)] =
    {
        0
    };
    uint32_t cipher_tmp[16 / sizeof(uint32_t)] =
    {
        0
    };

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes128ccmenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    mac_length_tmp = (((handle->formatted_data[0] >> 3) & 0x07UL) * 2UL) + 2UL;
    if ((mac_length != mac_length_tmp) || (2 == mac_length_tmp))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    length_tmp = change_endian_long(handle->all_received_length);
    ercd       = R_SCE_Aes128CcmEncryptFinalPrivate(&length_tmp,
                                       /* Casting uint32_t pointer is used for address. */
                                                     (uint32_t *) handle->ccm_buffer,
                                                     (uint32_t *) cipher_tmp,
                                                     (uint32_t *) mac_tmp);
    if (FSP_SUCCESS == ercd)
    {
        *cipher_length = handle->all_received_length;
        memcpy(mac, mac_tmp, mac_length);
        memcpy(cipher, cipher_tmp, (handle->all_received_length & 0x0000000F));
    }

    memset(handle, 0, sizeof(sce_ccm_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CCM_DecryptInit() function prepares to perform CCM computation and writes the result to the first
 * argument, handle. The succeeding functions R_SCE_AES128CCM_DecryptUpdate() and R_SCE_AES128CCM_DecryptFinal()
 * use handle as an argument.
 *
 * @param[in,out] handle         AES-CCM handler (work area)
 * @param[in]     wrapped_key    128-bit AES wrapped key
 * @param[in]     nonce          Nonce
 * @param[in]     nonce_length   Nonce data length (7 to 13 bytes)
 * @param[in]     adata          additional authentication data
 * @param[in]     a_length       additional authentication data length (0 to 110 bytes)
 * @param[in]     payload_length Payload length (any number of bytes)
 * @param[in]     mac_length     MAC length (4, 6, 8, 10, 12, 14, or 16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CCM_DecryptInit (sce_ccm_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * nonce,
                                       uint32_t                nonce_length,
                                       uint8_t               * adata,
                                       uint8_t                 a_length,
                                       uint32_t                payload_length,
                                       uint32_t                mac_length)
{
    uint32_t formatted_length = 0;

    memset(handle, 0, sizeof(sce_ccm_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes128ccmdec_private_id = g_private_id_counter;
    handle->id                = g_private_id_counter;
    memcpy(&handle->wrapped_key, wrapped_key, sizeof(sce_aes_wrapped_key_t));

    aes_ccm_b_counter_formatter(nonce,
                                nonce_length,
                                adata,
                                a_length,
                                payload_length,
                                mac_length,
                                handle->counter,
                                handle->formatted_data,
                                &formatted_length);

    return R_SCE_Aes128CcmDecryptInitPrivate(wrapped_key,
                                       /* Casting uint32_t pointer is used for address. */
                                              (uint32_t *) handle->counter,
                                              (uint32_t *) handle->formatted_data,
                                              formatted_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CCM_DecryptUpdate() function decrypts the ciphertext specified by the second argument, cipher,
 * in CCM mode using the values specified by wrapped_key, nonce, and adata in in R_SCE_AES128CCM_DecryptInit().
 * This function buffers internally the data input by the user until the input value of cipher exceeds 16 bytes.
 * Once the amount of cipher input data is 16 bytes or greater, the decrypted result is output to plain,
 * which is specified in the third argument. Use payload_length in R_SCE_AES128CCM_DecryptInit() to specify the total data
 * length of cipher that will be input. Use cipher_length in this function to specify the data length to be input
 * when the user calls this function. If the input value of cipher is less than 16 bytes, the function performs
 * padding internally.
 *
 * Ensure that the areas allocated to cipher and plain do not overlap. Also, specify RAM addresses that are
 * multiples of 4 for cipher and plain.
 *
 * @param[in,out] handle        AES-CCM handler (work area)
 * @param[in]     cipher        ciphertext data area
 * @param[in,out] plain         plaintext data area
 * @param[in]     cipher_length ciphertext data length
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CCM_DecryptUpdate (sce_ccm_handle_t * handle,
                                         uint8_t          * cipher,
                                         uint8_t          * plain,
                                         uint32_t           cipher_length)
{
    uint32_t length_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes128ccmdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->all_received_length += cipher_length;
    if ((handle->buffering_length + cipher_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
    {
        memcpy((&handle->ccm_buffer[0] + handle->buffering_length),
               cipher,
               HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

        /* Casting uint32_t pointer is used for address. */
        R_SCE_Aes128CcmDecryptUpdatePrivate((uint32_t *) handle->ccm_buffer,
                                             (uint32_t *) plain,
                                             HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
        length_rest = cipher_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
        if (length_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            R_SCE_Aes128CcmDecryptUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (cipher + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                (uint32_t *)
                (plain + HW_SCE_AES_BLOCK_BYTE_SIZE),
                ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
            length_rest -= ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
        }

        handle->buffering_length = 0;
        memset(handle->ccm_buffer, 0, sizeof(handle->ccm_buffer));
        memcpy(handle->ccm_buffer, cipher + (cipher_length - length_rest), length_rest);
        handle->buffering_length = length_rest;
    }
    else
    {
        memcpy(&handle->ccm_buffer[0] + handle->buffering_length, cipher, cipher_length);
        handle->buffering_length += cipher_length;
    }

    return FSP_SUCCESS;
}

/*******************************
 * End of function HW_SCE_Aes128CcmDecryptUpdate
 *******************************/

/*******************************************************************************************************************//**
 * If the data length of cipher input in R_SCE_AES128GCM_DecryptUpdate() results in leftover data after 16 bytes,
 * the R_SCE_AES128GCM_DecryptFinal() function outputs the leftover decrypted data to cipher, which is specified
 * in the second argument. In addition, the function verifies the fourth argument, mac. Set the fifth argument,
 * mac_length, to the same value as that specified for the argument mac_length in Aes128CcmDecryptInit().
 *
 * @param[in,out] handle       AES-CCM handler (work area)
 * @param[in,out] plain        plaintext data area
 * @param[in,out] plain_length plaintext data length
 * @param[in]     mac          MAC area
 * @param[in]     mac_length   MAC length (4, 6, 8, 10, 12, 14, or 16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error, or authentication failed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CCM_DecryptFinal (sce_ccm_handle_t * handle,
                                        uint8_t          * plain,
                                        uint32_t         * plain_length,
                                        uint8_t          * mac,
                                        uint32_t           mac_length)
{
    fsp_err_t ercd                           = FSP_SUCCESS;
    uint32_t  length_tmp                     = 0;
    uint32_t  mac_length_tmp                 = 0;
    uint32_t  mac_tmp[16 / sizeof(uint32_t)] =
    {
        0
    };
    uint32_t plain_tmp[16 / sizeof(uint32_t)] =
    {
        0
    };

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes128ccmdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    mac_length_tmp = (((handle->formatted_data[0] >> 3UL) & 0x07UL) * 2UL) + 2UL;
    if ((mac_length != mac_length_tmp) || (2 == mac_length_tmp))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    length_tmp     = change_endian_long(handle->all_received_length);
    mac_length_tmp = change_endian_long(mac_length);
    memcpy(mac_tmp, mac, mac_length);
    ercd = R_SCE_Aes128CcmDecryptFinalPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) handle->ccm_buffer,
        &length_tmp,
        (uint32_t *) mac_tmp,
        &mac_length_tmp,
        (uint32_t *) plain_tmp);
    if (FSP_SUCCESS == ercd)
    {
        *plain_length = handle->all_received_length;
        memcpy(plain, plain_tmp, (handle->all_received_length & 0x0000000F));
    }

    memset(handle, 0, sizeof(sce_ccm_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CCM_EncryptInit() function prepares to perform CCM computation and writes the result to the first
 * argument, handle. The succeeding functions R_SCE_AES256CCM_EncryptUpdate() and R_SCE_AES256CCM_EncryptFinal()
 * use handle as an argument.
 *
 * @param[in,out] handle         AES-CCM handler (work area)
 * @param[in]     wrapped_key    256-bit AES wrapped key
 * @param[in]     nonce          Nonce
 * @param[in]     nonce_length   Nonce data length (7 to 13 bytes)
 * @param[in]     adata          additional authentication data
 * @param[in]     a_length       additional authentication data length (0 to 110 bytes)
 * @param[in]     payload_length Payload length (any number of bytes)
 * @param[in]     mac_length     MAC length (4, 6, 8, 10, 12, 14, or 16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CCM_EncryptInit (sce_ccm_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * nonce,
                                       uint32_t                nonce_length,
                                       uint8_t               * adata,
                                       uint8_t                 a_length,
                                       uint32_t                payload_length,
                                       uint32_t                mac_length)
{
    uint32_t formatted_length = 0;

    memset(handle, 0, sizeof(sce_ccm_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes256ccmenc_private_id = g_private_id_counter;
    handle->id                = g_private_id_counter;
    memcpy(&handle->wrapped_key, wrapped_key, sizeof(sce_aes_wrapped_key_t));

    aes_ccm_b_counter_formatter(nonce,
                                nonce_length,
                                adata,
                                a_length,
                                payload_length,
                                mac_length,
                                handle->counter,
                                handle->formatted_data,
                                &formatted_length);

    return R_SCE_Aes256CcmEncryptInitPrivate(wrapped_key,
                                       /* Casting uint32_t pointer is used for address. */
                                              (uint32_t *) handle->counter,
                                              (uint32_t *) handle->formatted_data,
                                              formatted_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CCM_EncryptUpdate() function encrypts the plaintext specified in the second argument, plain,
 * in CCM mode using the values specified by wrapped_key, nonce, and adata in R_SCE_AES256CCM_EncryptInit().
 * This function buffers internally the data input by the user until the input value of plain exceeds 16 bytes.
 * Once the amount of plain input data is 16 bytes or greater, the encrypted result is output to cipher,
 * which is specified in the third argument. Use payload_length in R_SCE_AES256CCM_EncryptInit() to specify the total data
 * length of plain that will be input. Use plain_length in this function to specify the data length to be input
 * when the user calls this function. If the input value of plain is less than 16 bytes, the function performs
 * padding internally.
 *
 * Ensure that the areas allocated to plain and cipher do not overlap. Also, specify RAM addresses that are
 * multiples of 4 for plain and cipher.
 *
 * @param[in,out] handle       AES-CCM handler (work area)
 * @param[in]     plain        plaintext data area
 * @param[in,out] cipher       ciphertext data area
 * @param[in]     plain_length plaintext data length
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CCM_EncryptUpdate (sce_ccm_handle_t * handle,
                                         uint8_t          * plain,
                                         uint8_t          * cipher,
                                         uint32_t           plain_length)
{
    uint32_t length_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes256ccmenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->all_received_length += plain_length;
    if ((handle->buffering_length + plain_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
    {
        memcpy((&handle->ccm_buffer[0] + handle->buffering_length),
               plain,
               HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

        /* Casting uint32_t pointer is used for address. */
        R_SCE_Aes256CcmEncryptUpdatePrivate((uint32_t *) handle->ccm_buffer,
                                             (uint32_t *) cipher,
                                             HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
        length_rest = plain_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
        if (length_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            R_SCE_Aes256CcmEncryptUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (plain + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                (uint32_t *)
                (cipher + HW_SCE_AES_BLOCK_BYTE_SIZE),
                ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
            length_rest -= ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
        }

        handle->buffering_length = 0;
        memset(handle->ccm_buffer, 0, sizeof(handle->ccm_buffer));
        memcpy(handle->ccm_buffer, plain + (plain_length - length_rest), length_rest);
        handle->buffering_length = length_rest;
    }
    else
    {
        memcpy(&handle->ccm_buffer[0] + handle->buffering_length, plain, plain_length);
        handle->buffering_length += plain_length;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * If the data length of plain input in R_SCE_AES256CCM_EncryptUpdate() results in leftover data after 16 bytes,
 * the R_SCE_AES256CCM_EncryptFinal() function outputs the leftover encrypted data to cipher, which is specified
 * in the second argument. The MAC value is output to the fourth argument, mac. Set the fifth argument, mac_length
 * to the same value as that specified for the argument mac_length in Aes256CcmEncryptInit(). Also, specify RAM addresses
 * that are multiples of 4 for cipher and mac.
 *
 * @param[in,out] handle        AES-CCM handler (work area)
 * @param[in,out] cipher        ciphertext data area
 * @param[in,out] cipher_length ciphertext data length
 * @param[in,out] mac           MAC area
 * @param[in]     mac_length    MAC length (4, 6, 8, 10, 12, 14, or 16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CCM_EncryptFinal (sce_ccm_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint32_t         * cipher_length,
                                        uint8_t          * mac,
                                        uint32_t           mac_length)
{
    fsp_err_t ercd                           = FSP_SUCCESS;
    uint32_t  length_tmp                     = 0;
    uint32_t  mac_length_tmp                 = 0;
    uint32_t  mac_tmp[16 / sizeof(uint32_t)] =
    {
        0
    };
    uint32_t cipher_tmp[16 / sizeof(uint32_t)] =
    {
        0
    };

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes256ccmenc_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    mac_length_tmp = (((handle->formatted_data[0] >> 3UL) & 0x07UL) * 2UL) + 2UL;
    if ((mac_length != mac_length_tmp) || (2 == mac_length_tmp))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    length_tmp = change_endian_long(handle->all_received_length);
    ercd       = R_SCE_Aes256CcmEncryptFinalPrivate(&length_tmp,
                                       /* Casting uint32_t pointer is used for address. */
                                                     (uint32_t *) handle->ccm_buffer,
                                                     (uint32_t *) cipher_tmp,
                                                     (uint32_t *) mac_tmp);
    if (FSP_SUCCESS == ercd)
    {
        *cipher_length = handle->all_received_length;
        memcpy(mac, mac_tmp, mac_length);
        memcpy(cipher, cipher_tmp, (handle->all_received_length & 0x0000000F));
    }

    memset(handle, 0, sizeof(sce_ccm_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CCM_DecryptInit() function prepares to perform CCM computation and writes the result to the first
 * argument, handle. The succeeding functions R_SCE_AES256CCM_DecryptUpdate() and R_SCE_AES256CCM_DecryptFinal()
 * use handle as an argument.
 *
 * @param[in,out] handle         AES-CCM handler (work area)
 * @param[in]     wrapped_key    256-bit AES wrapped key
 * @param[in]     nonce          Nonce
 * @param[in]     nonce_length   Nonce data length (7 to 13 bytes)
 * @param[in]     adata          additional authentication data
 * @param[in]     a_length       additional authentication data length (0 to 110 bytes)
 * @param[in]     payload_length Payload length (any number of bytes)
 * @param[in]     mac_length     MAC length (4, 6, 8, 10, 12, 14, or 16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CCM_DecryptInit (sce_ccm_handle_t      * handle,
                                       sce_aes_wrapped_key_t * wrapped_key,
                                       uint8_t               * nonce,
                                       uint32_t                nonce_length,
                                       uint8_t               * adata,
                                       uint8_t                 a_length,
                                       uint32_t                payload_length,
                                       uint32_t                mac_length)
{
    uint32_t formatted_length = 0;

    memset(handle, 0, sizeof(sce_ccm_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes256ccmdec_private_id = g_private_id_counter;
    handle->id                = g_private_id_counter;
    memcpy(&handle->wrapped_key, wrapped_key, sizeof(sce_aes_wrapped_key_t));

    aes_ccm_b_counter_formatter(nonce,
                                nonce_length,
                                adata,
                                a_length,
                                payload_length,
                                mac_length,
                                handle->counter,
                                handle->formatted_data,
                                &formatted_length);

    return R_SCE_Aes256CcmDecryptInitPrivate(wrapped_key,
                                       /* Casting uint32_t pointer is used for address. */
                                              (uint32_t *) handle->counter,
                                              (uint32_t *) handle->formatted_data,
                                              formatted_length);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CCM_DecryptUpdate() function decrypts the ciphertext specified by the second argument, cipher,
 * in CCM mode using the values specified by wrapped_key, nonce, and adata in in R_SCE_AES256CCM_DecryptInit().
 * This function buffers internally the data input by the user until the input value of cipher exceeds 16 bytes.
 * Once the amount of cipher input data is 16 bytes or greater, the decrypted result is output to plain,
 * which is specified in the third argument. Use payload_length in R_SCE_AES256CCM_DecryptInit() to specify the total data
 * length of cipher that will be input. Use cipher_length in this function to specify the data length to be input
 * when the user calls this function. If the input value of cipher is less than 16 bytes, the function performs
 * padding internally.
 *
 * Ensure that the areas allocated to cipher and plain do not overlap. Also, specify RAM addresses that are
 * multiples of 4 for cipher and plain.
 *
 * @param[in,out] handle        AES-CCM handler (work area)
 * @param[in]     cipher        ciphertext data area
 * @param[in,out] plain         plaintext data area
 * @param[in]     cipher_length ciphertext data length
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CCM_DecryptUpdate (sce_ccm_handle_t * handle,
                                         uint8_t          * cipher,
                                         uint8_t          * plain,
                                         uint32_t           cipher_length)
{
    uint32_t length_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes256ccmdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->all_received_length += cipher_length;
    if ((handle->buffering_length + cipher_length) >= HW_SCE_AES_BLOCK_BYTE_SIZE)
    {
        memcpy((&handle->ccm_buffer[0] + handle->buffering_length),
               cipher,
               HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

        /* Casting uint32_t pointer is used for address. */
        R_SCE_Aes256CcmDecryptUpdatePrivate((uint32_t *) handle->ccm_buffer,
                                             (uint32_t *) plain,
                                             HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
        length_rest = cipher_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
        if (length_rest >= HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            R_SCE_Aes256CcmDecryptUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (cipher + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                (uint32_t *)
                (plain + HW_SCE_AES_BLOCK_BYTE_SIZE),
                ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
            length_rest -= ((length_rest / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
        }

        handle->buffering_length = 0;
        memset(handle->ccm_buffer, 0, sizeof(handle->ccm_buffer));
        memcpy(handle->ccm_buffer, cipher + (cipher_length - length_rest), length_rest);
        handle->buffering_length = length_rest;
    }
    else
    {
        memcpy(&handle->ccm_buffer[0] + handle->buffering_length, cipher, cipher_length);
        handle->buffering_length += cipher_length;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * If the data length of cipher input in R_SCE_AES256GCM_DecryptUpdate() results in leftover data after 16 bytes,
 * the R_SCE_AES256GCM_DecryptFinal() function outputs the leftover decrypted data to cipher, which is specified
 * in the second argument. In addition, the function verifies the fourth argument, mac. Set the fifth argument,
 * mac_length, to the same value as that specified for the argument mac_length in Aes256CcmDecryptInit().
 *
 * @param[in,out] handle       AES-CCM handler (work area)
 * @param[in,out] plain        plaintext data area
 * @param[in,out] plain_length plaintext data length
 * @param[in]     mac          MAC area
 * @param[in]     mac_length   MAC length (4, 6, 8, 10, 12, 14, or 16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error, or authentication failed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CCM_DecryptFinal (sce_ccm_handle_t * handle,
                                        uint8_t          * plain,
                                        uint32_t         * plain_length,
                                        uint8_t          * mac,
                                        uint32_t           mac_length)
{
    fsp_err_t ercd                           = FSP_SUCCESS;
    uint32_t  length_tmp                     = 0;
    uint32_t  mac_length_tmp                 = 0;
    uint32_t  mac_tmp[16 / sizeof(uint32_t)] =
    {
        0
    };
    uint32_t plain_tmp[16 / sizeof(uint32_t)] =
    {
        0
    };

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes256ccmdec_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    mac_length_tmp = (((handle->formatted_data[0] >> 3UL) & 0x07UL) * 2UL) + 2UL;
    if ((mac_length != mac_length_tmp) || (2 == mac_length_tmp))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    length_tmp     = change_endian_long(handle->all_received_length);
    mac_length_tmp = change_endian_long(mac_length);
    memcpy(mac_tmp, mac, mac_length);
    ercd = R_SCE_Aes256CcmDecryptFinalPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) handle->ccm_buffer,
        &length_tmp,
        (uint32_t *) mac_tmp,
        &mac_length_tmp,
        (uint32_t *) plain_tmp);
    if (FSP_SUCCESS == ercd)
    {
        *plain_length = handle->all_received_length;
        memcpy(plain, plain_tmp, (handle->all_received_length & 0x0000000F));
    }

    memset(handle, 0, sizeof(sce_ccm_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CMAC_GenerateInit() function performs preparations for the execution of an CMAC calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument in the subsequent
 * R_SCE_AES128CMAC_GenerateUpdate() function and R_SCE_AES128CMAC_GenerateFinal() function.
 *
 * @param[in,out] handle      AES-CMAC handler (work area)
 * @param[in]     wrapped_key 128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CMAC_GenerateInit (sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key)
{
    memset(handle, 0, sizeof(sce_cmac_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes128cmacgen_private_id = g_private_id_counter;
    handle->id                 = g_aes128cmacgen_private_id;
    memcpy(handle->wrapped_key.value, wrapped_key->value, HW_SCE_AES128_KEY_INDEX_WORD_SIZE * 4);
    memset(handle->cmac_buffer, 0, sizeof(handle->cmac_buffer));

    return R_SCE_Aes128CmacGenerateInitPrivate(wrapped_key);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CMAC_GenerateUpdate() function performs MAC value generation based on the message specified
 * in the second argument, message, using the value specified for wrapped_key in R_SCE_AES128CMAC_GenerateInit().
 * Inside this function, the data that is input by the user is buffered until the input value of message
 * exceeds 16 bytes. The length of the message data to input is specified in the third argument, message_len.
 * For these, input not the total byte count for message input data, but rather the message data length
 * to input when the user calls this function. If the input value, message, is not a multiple of 16 bytes,
 * it will be padded within the function. For message, specify a RAM address that are multiples of 4.
 *
 * @param[in,out] handle         AES-CMAC handler (work area)
 * @param[in]     message        message data area (message_length byte)
 * @param[in]     message_length message data length (0 or more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CMAC_GenerateUpdate (sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length)
{
    uint32_t length_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes128cmacgen_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->all_received_length += message_length;
    if ((handle->buffering_length + message_length) > HW_SCE_AES_BLOCK_BYTE_SIZE)
    {
        memcpy((&handle->cmac_buffer[0] + handle->buffering_length),
               message,
               HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

        /* Casting uint32_t pointer is used for address. */
        R_SCE_Aes128CmacGenerateUpdatePrivate((uint32_t *) (handle->cmac_buffer), HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
        length_rest = message_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
        memset(handle->cmac_buffer, 0, sizeof(handle->cmac_buffer));
        if (length_rest > HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            R_SCE_Aes128CmacGenerateUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (message + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                (((length_rest - 1) / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
            length_rest -= (((length_rest - 1) / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
        }

        handle->buffering_length = 0;
        memcpy(handle->cmac_buffer, message + (message_length - length_rest), length_rest);
        handle->buffering_length = length_rest;
    }
    else
    {
        memcpy(&handle->cmac_buffer[0] + handle->buffering_length, message, message_length);
        handle->buffering_length += message_length;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CMAC_GenerateFinal() function outputs the MAC value to the MAC data area specified
 * in the second argument, mac, and ends CMAC mode.
 *
 * @param[in,out] handle AES-CMAC handler (work area)
 * @param[in,out] mac    MAC data area (16byte)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION    Not used.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CMAC_GenerateFinal (sce_cmac_handle_t * handle, uint8_t * mac)
{
    fsp_err_t ercd = FSP_SUCCESS;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes128cmacgen_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if ((0 != (handle->buffering_length % HW_SCE_AES_BLOCK_BYTE_SIZE)) || (0 == handle->all_received_length))
    {
        handle->cmac_buffer[handle->buffering_length] = 1 << 7;
        memset(handle->cmac_buffer + (handle->buffering_length + 1), 0,
               HW_SCE_AES_BLOCK_BYTE_SIZE - (handle->buffering_length + 1));
    }

    ercd = R_SCE_Aes128CmacGenerateFinalPrivate(handle->all_received_length,
                                       /* Casting uint32_t pointer is used for address. */
                                                 (uint32_t *) (handle->cmac_buffer),
                                                 (uint32_t *) (mac));
    memset(handle, 0, sizeof(sce_cmac_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CMAC_VerifyInit() function performs preparations for the execution of a CMAC calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argumentin the subsequent
 * R_SCE_AES128CMAC_VerifyUpdate() function and R_SCE_AES128CMAC_VerifyFinal() function.
 *
 * @param[in,out] handle      AES-CMAC handler (work area)
 * @param[in]     wrapped_key 128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CMAC_VerifyInit (sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key)
{
    memset(handle, 0, sizeof(sce_cmac_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes128cmacver_private_id = g_private_id_counter;
    handle->id                 = g_aes128cmacver_private_id;
    memcpy(handle->wrapped_key.value, wrapped_key->value, HW_SCE_AES128_KEY_INDEX_WORD_SIZE * 4);
    memset(handle->cmac_buffer, 0, sizeof(handle->cmac_buffer));

    return R_SCE_Aes128CmacVerifyInitPrivate(wrapped_key);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CMAC_VerifyUpdate() function performs MAC value generation based on the message specified
 * in the second argument, message, using the value specified for wrapped_key in R_SCE_AES128CMAC_VerifyInit().
 * Inside this function, the data that is input by the user is buffered until the input value of message
 * exceeds 16 bytes. The length of the message data to input is specified in the third argument, message_len.
 * For these, input not the total byte count for message input data, but rather the message data length to input
 * when the user calls this function. If the input value, message, is not a multiple of 16 bytes,
 * it will be padded within the function. For message, specify a RAM address that are multiples of 4.
 *
 * @param[in,out] handle         AES-CMAC handler (work area)
 * @param[in]     message        message data area (message_length byte)
 * @param[in]     message_length message data length (0 or more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CMAC_VerifyUpdate (sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length)
{
    uint32_t length_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes128cmacver_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->all_received_length += message_length;
    if ((handle->buffering_length + message_length) > HW_SCE_AES_BLOCK_BYTE_SIZE)
    {
        memcpy((&handle->cmac_buffer[0] + handle->buffering_length),
               message,
               HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

        /* Casting uint32_t pointer is used for address. */
        R_SCE_Aes128CmacVerifyUpdatePrivate((uint32_t *) (handle->cmac_buffer), HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
        length_rest = message_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
        memset(handle->cmac_buffer, 0, sizeof(handle->cmac_buffer));
        if (length_rest > HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            R_SCE_Aes128CmacVerifyUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (message + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                (((length_rest - 1) / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
            length_rest -= (((length_rest - 1) / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
        }

        handle->buffering_length = 0;
        memcpy(handle->cmac_buffer, message + (message_length - length_rest), length_rest);
        handle->buffering_length = length_rest;
    }
    else
    {
        memcpy(&handle->cmac_buffer[0] + handle->buffering_length, message, message_length);
        handle->buffering_length += message_length;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES128CMAC_VerifyFinal() function inputs the MAC value in the MAC data area specified
 * in the second argument, mac, and verifies the MAC value. If authentication fails, the return value will be
 * TSIP_ERR_AUTHENTICATION. If the MAC value is less than 16 bytes, it will be padded with zeros inside the function.
 *
 * @param[in,out] handle     AES-CMAC handler (work area)
 * @param[in,out] mac        MAC data area (mac_length byte)
 * @param[in,out] mac_length MAC data length (2 to 16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION    Authentication failed
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128CMAC_VerifyFinal (sce_cmac_handle_t * handle, uint8_t * mac, uint32_t mac_length)
{
    fsp_err_t ercd = FSP_SUCCESS;
    uint32_t  mac_tmp[16 / sizeof(uint32_t)] =
    {
        0                              /* mac_tmp is initialized with 0. */
    };
    uint32_t mac_length_bit = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes128cmacver_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if ((2 > mac_length) || (mac_length > HW_SCE_AES_BLOCK_BYTE_SIZE))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if ((0 != (handle->buffering_length % HW_SCE_AES_BLOCK_BYTE_SIZE)) || (0 == handle->all_received_length))
    {
        handle->cmac_buffer[handle->buffering_length] = 1 << 7;
        memset(handle->cmac_buffer + (handle->buffering_length + 1), 0,
               HW_SCE_AES_BLOCK_BYTE_SIZE - (handle->buffering_length + 1));
    }

    memcpy(mac_tmp, mac, mac_length);
    mac_length_bit = change_endian_long(mac_length * 8);

    ercd = R_SCE_Aes128CmacVerifyFinalPrivate(handle->all_received_length,
                                       /* Casting uint32_t pointer is used for address. */
                                               (uint32_t *) handle->cmac_buffer,
                                               (uint32_t *) mac_tmp,
                                               &mac_length_bit);
    memset(handle, 0, sizeof(sce_cmac_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CMAC_GenerateInit() function performs preparations for the execution of an CMAC calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argument in the subsequent
 * R_SCE_AES256CMAC_GenerateUpdate() function and R_SCE_AES256CMAC_GenerateFinal() function.
 *
 * @param[in,out] handle      AES-CMAC handler (work area)
 * @param[in]     wrapped_key 256-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CMAC_GenerateInit (sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key)
{
    memset(handle, 0, sizeof(sce_cmac_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes256cmacgen_private_id = g_private_id_counter;
    handle->id                 = g_aes256cmacgen_private_id;
    memcpy(handle->wrapped_key.value, wrapped_key->value, HW_SCE_AES256_KEY_INDEX_WORD_SIZE * 4);
    memset(handle->cmac_buffer, 0, sizeof(handle->cmac_buffer));

    return R_SCE_Aes256CmacGenerateInitPrivate(wrapped_key);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CMAC_GenerateUpdate() function performs MAC value generation based on the message specified
 * in the second argument, message, using the value specified for wrapped_key in R_SCE_AES256CMAC_GenerateInit().
 * Inside this function, the data that is input by the user is buffered until the input value of message
 * exceeds 16 bytes. The length of the message data to input is specified in the third argument, message_len.
 * For these, input not the total byte count for message input data, but rather the message data length
 * to input when the user calls this function. If the input value, message, is not a multiple of 16 bytes,
 * it will be padded within the function. For message, specify a RAM address that are multiples of 4.
 *
 * @param[in,out] handle         AES-CMAC handler (work area)
 * @param[in]     message        message data area (message_length byte)
 * @param[in]     message_length message data length (0 or more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CMAC_GenerateUpdate (sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length)
{
    uint32_t length_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes256cmacgen_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->all_received_length += message_length;
    if ((handle->buffering_length + message_length) > HW_SCE_AES_BLOCK_BYTE_SIZE)
    {
        memcpy((&handle->cmac_buffer[0] + handle->buffering_length),
               message,
               HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

        /* Casting uint32_t pointer is used for address. */
        R_SCE_Aes256CmacGenerateUpdatePrivate((uint32_t *) (handle->cmac_buffer), HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
        length_rest = message_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
        memset(handle->cmac_buffer, 0, sizeof(handle->cmac_buffer));
        if (length_rest > HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            R_SCE_Aes256CmacGenerateUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (message + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                (((length_rest - 1) / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
            length_rest -= (((length_rest - 1) / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
        }

        handle->buffering_length = 0;
        memcpy(handle->cmac_buffer, message + (message_length - length_rest), length_rest);
        handle->buffering_length = length_rest;
    }
    else
    {
        memcpy(&handle->cmac_buffer[0] + handle->buffering_length, message, message_length);
        handle->buffering_length += message_length;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CMAC_GenerateFinal() function outputs the MAC value to the MAC data area specified
 * in the second argument, mac, and ends CMAC mode.
 *
 * @param[in,out] handle AES-CMAC handler (work area)
 * @param[in,out] mac    MAC data area (16byte)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION    Not used.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CMAC_GenerateFinal (sce_cmac_handle_t * handle, uint8_t * mac)
{
    fsp_err_t ercd = FSP_SUCCESS;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes256cmacgen_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if ((0 != (handle->buffering_length % HW_SCE_AES_BLOCK_BYTE_SIZE)) || (0 == handle->all_received_length))
    {
        handle->cmac_buffer[handle->buffering_length] = 1 << 7;
        memset(handle->cmac_buffer + (handle->buffering_length + 1), 0,
               HW_SCE_AES_BLOCK_BYTE_SIZE - (handle->buffering_length + 1));
    }

    ercd = R_SCE_Aes256CmacGenerateFinalPrivate(handle->all_received_length,
                                       /* Casting uint32_t pointer is used for address. */
                                                 (uint32_t *) (handle->cmac_buffer),
                                                 (uint32_t *) (mac));
    memset(handle, 0, sizeof(sce_cmac_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CMAC_VerifyInit() function performs preparations for the execution of a CMAC calculation,
 * and writes the result to the first argument, handle. The value of handle is used as an argumentin the subsequent
 * R_SCE_AES256CMAC_VerifyUpdate() function and R_SCE_AES256CMAC_VerifyFinal() function.
 *
 * @param[in,out] handle      AES-CMAC handler (work area)
 * @param[in]     wrapped_key 256-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CMAC_VerifyInit (sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key)
{
    memset(handle, 0, sizeof(sce_cmac_handle_t));
    handle->flag_call_init = CALL_ONLY_UPDATE_FINAL;
    g_private_id_counter++;
    g_aes256cmacver_private_id = g_private_id_counter;
    handle->id                 = g_aes256cmacver_private_id;
    memcpy(handle->wrapped_key.value, wrapped_key->value, HW_SCE_AES256_KEY_INDEX_WORD_SIZE * 4);
    memset(handle->cmac_buffer, 0, sizeof(handle->cmac_buffer));

    return R_SCE_Aes256CmacVerifyInitPrivate(wrapped_key);
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CMAC_VerifyUpdate() function performs MAC value generation based on the message specified
 * in the second argument, message, using the value specified for wrapped_key in R_SCE_AES256CMAC_VerifyInit().
 * Inside this function, the data that is input by the user is buffered until the input value of message
 * exceeds 16 bytes. The length of the message data to input is specified in the third argument, message_len.
 * For these, input not the total byte count for message input data, but rather the message data length to input
 * when the user calls this function. If the input value, message, is not a multiple of 16 bytes,
 * it will be padded within the function. For message, specify a RAM address that are multiples of 4.
 *
 * @param[in,out] handle         AES-CMAC handler (work area)
 * @param[in]     message        message data area (message_length byte)
 * @param[in]     message_length message data length (0 or more bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CMAC_VerifyUpdate (sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length)
{
    uint32_t length_rest = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_aes256cmacver_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->all_received_length += message_length;
    if ((handle->buffering_length + message_length) > HW_SCE_AES_BLOCK_BYTE_SIZE)
    {
        memcpy((&handle->cmac_buffer[0] + handle->buffering_length),
               message,
               HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);

        /* Casting uint32_t pointer is used for address. */
        R_SCE_Aes256CmacVerifyUpdatePrivate((uint32_t *) (handle->cmac_buffer), HW_SCE_AES_BLOCK_BYTE_SIZE >> 2);
        length_rest = message_length - (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length);
        memset(handle->cmac_buffer, 0, sizeof(handle->cmac_buffer));
        if (length_rest > HW_SCE_AES_BLOCK_BYTE_SIZE)
        {
            R_SCE_Aes256CmacVerifyUpdatePrivate(
                /* Casting uint32_t pointer is used for address. */
                (uint32_t *) (message + (HW_SCE_AES_BLOCK_BYTE_SIZE - handle->buffering_length)),
                (((length_rest - 1) / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE) >> 2);
            length_rest -= (((length_rest - 1) / HW_SCE_AES_BLOCK_BYTE_SIZE) * HW_SCE_AES_BLOCK_BYTE_SIZE);
        }

        handle->buffering_length = 0;
        memcpy(handle->cmac_buffer, message + (message_length - length_rest), length_rest);
        handle->buffering_length = length_rest;
    }
    else
    {
        memcpy(&handle->cmac_buffer[0] + handle->buffering_length, message, message_length);
        handle->buffering_length += message_length;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * The R_SCE_AES256CMAC_VerifyFinal() function inputs the MAC value in the MAC data area specified
 * in the second argument, mac, and verifies the MAC value. If authentication fails, the return value will be
 * TSIP_ERR_AUTHENTICATION. If the MAC value is less than 16 bytes, it will be padded with zeros inside the function.
 *
 * @param[in,out] handle     AES-CMAC handler (work area)
 * @param[in,out] mac        MAC data area (mac_length byte)
 * @param[in,out] mac_length MAC data length (2 to 16 bytes)
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION    Authentication failed
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256CMAC_VerifyFinal (sce_cmac_handle_t * handle, uint8_t * mac, uint32_t mac_length)
{
    fsp_err_t ercd = FSP_SUCCESS;
    uint32_t  mac_tmp[16 / sizeof(uint32_t)] =
    {
        0                              /* mac_tmp is initialized with 0. */
    };
    uint32_t mac_length_bit = 0;

    if (CALL_ONLY_INIT == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    handle->flag_call_init = CALL_ONLY_INIT;
    if (handle->id != g_aes256cmacver_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if ((2 > mac_length) || (mac_length > HW_SCE_AES_BLOCK_BYTE_SIZE))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if ((0 != (handle->buffering_length % HW_SCE_AES_BLOCK_BYTE_SIZE)) || (0 == handle->all_received_length))
    {
        handle->cmac_buffer[handle->buffering_length] = 1 << 7;
        memset(handle->cmac_buffer + (handle->buffering_length + 1), 0,
               HW_SCE_AES_BLOCK_BYTE_SIZE - (handle->buffering_length + 1));
    }

    memcpy(mac_tmp, mac, mac_length);
    mac_length_bit = change_endian_long(mac_length * 8);

    ercd = R_SCE_Aes256CmacVerifyFinalPrivate(handle->all_received_length,
                                       /* Casting uint32_t pointer is used for address. */
                                               (uint32_t *) handle->cmac_buffer,
                                               (uint32_t *) mac_tmp,
                                               &mac_length_bit);
    memset(handle, 0, sizeof(sce_cmac_handle_t));

    return ercd;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCE_PROTECTED)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Generation of input parameter for R_SCE_AESXXXGCM_XXX function.
 *
 * @param[in]     initial_vector        Input initial vector.
 * @param[in]     initial_vector_length Input initial vector byte size.
 * @param[in]     wrapped_key           Wrapped key area.
 * @param[in]     wrapped_key_word_size Wrapped key word size.
 * @param[in,out] hashed_ivec           Output initialization vector( using length of initial_vector_length as a condition)
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 *********************************************************************************************************************/
static fsp_err_t prepare_gcm_iv (uint8_t               * initial_vector,
                                 uint32_t                initial_vector_length,
                                 sce_aes_wrapped_key_t * wrapped_key,
                                 uint32_t                wrapped_key_word_size,
                                 uint32_t              * hashed_ivec)
{
    uint32_t hash_subkey[4] =
    {
        0
    };
    uint32_t hashed_ivec_tmp[4] =
    {
        0
    };
    uint32_t zero[4] =
    {
        0
    };
    uint32_t ivec_length_rest = 0;
    uint32_t ivec_bit_len[4]  =
    {
        0
    };
    uint32_t ivec_tmp[4] =
    {
        0
    };
    fsp_err_t ret = FSP_SUCCESS;

    /* when iv_len is 12 (96 bit), add 0x00000001 padding */
    if (12U == initial_vector_length)
    {
        memcpy(hashed_ivec, initial_vector, 12U);
        hashed_ivec[3] = change_endian_long(0x00000001U);
    }
    /* when iv_len is not 12 (96 bit), add ghash padding */
    else
    {
        uint32_t indata_keytype = 0; /* For normal */
        uint32_t indata_cmd = 0;

        /* generate hash_subkey */
        indata_cmd = change_endian_long(0); /* ECB-Encrypt command */
        if (HW_SCE_AES128_KEY_INDEX_WORD_SIZE == wrapped_key_word_size)
        {
            if (SCE_KEY_INDEX_TYPE_AES128 == wrapped_key->type)
            {
                if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == wrapped_key->type)
                {
                    indata_keytype = change_endian_long(2); /* For ECDH */
                }
                ret = R_SCE_Aes128EncryptDecryptInitSub(&indata_keytype, &indata_cmd, wrapped_key->value, zero);
                if (FSP_SUCCESS == ret)
                {
                    R_SCE_Aes128EncryptDecryptUpdateSub(zero, hash_subkey, 4);
                    ret = R_SCE_Aes128EncryptDecryptFinalSub();
                }
            }
        }
        else    /* if (SCE_KEY_INDEX_TYPE_AES256 == key_index_word_size) */
        {
            if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == wrapped_key->type)
            {
                indata_keytype = change_endian_long(2); /* For ECDH */
            }
            ret = R_SCE_Aes256EncryptDecryptInitSub(&indata_keytype, &indata_cmd, wrapped_key->value, zero);
            if (FSP_SUCCESS == ret)
            {
                R_SCE_Aes256EncryptDecryptUpdateSub(zero, hash_subkey, 4);
                ret = R_SCE_Aes256EncryptDecryptFinalSub();
            }
        }

        if (FSP_SUCCESS == ret)
        {
            if (16 <= initial_vector_length)
            {
                /* Casting uint32_t pointer is used for address. */
                ret =
                    R_SCE_Ghash(hash_subkey, zero, (uint32_t *) initial_vector, hashed_ivec_tmp,
                                 (initial_vector_length / 16U) * 4);
                if (FSP_SUCCESS == ret)
                {
                    ivec_length_rest = initial_vector_length % 16;
                    if (0 != ivec_length_rest)
                    {
                        memcpy(ivec_tmp, initial_vector + (initial_vector_length - ivec_length_rest), ivec_length_rest);

                        /* Casting uint32_t pointer is used for address. */
                        ret = R_SCE_Ghash(hash_subkey, hashed_ivec_tmp, ivec_tmp, hashed_ivec_tmp, 4);
                    }
                }
            }
            else
            {
                memcpy(ivec_tmp, initial_vector, initial_vector_length);

                /* Casting uint32_t pointer is used for address. */
                ret = R_SCE_Ghash(hash_subkey, zero, ivec_tmp, hashed_ivec_tmp, 4);
            }

            if (FSP_SUCCESS == ret)
            {
                /* calculate ivec bit length */
                ivec_bit_len[0] = 0U;
                ivec_bit_len[1] = 0U;
                ivec_bit_len[2] = change_endian_long(initial_vector_length >> 29U); /* need endian change when big endian */
                ivec_bit_len[3] = change_endian_long(initial_vector_length << 3U);  /* need endian change when big endian */

                ret = R_SCE_Ghash(hash_subkey, hashed_ivec_tmp, ivec_bit_len, hashed_ivec, 4);
            }
        }
    }

    return ret;
}

/*******************************************************************************************************************//**
 * Formatting and counter generation.
 *
 * @param[in]     nonce            Nonce.
 * @param[in]     nonce_len        Nonce data length(byte).
 * @param[in]     adata            Associated data.
 * @param[in]     a_len            Associated data length(byte).
 * @param[in]     payload_len      Payload length(byte).
 * @param[in]     mac_len          MAC data length(byte).
 * @param[in,out] counter          Counter blocks area.
 * @param[in,out] formatted_data   Formatted data area.
 * @param[in,out] formatted_length Formatted data length.
 *********************************************************************************************************************/
static void aes_ccm_b_counter_formatter (uint8_t  * nonce,
                                         uint32_t   nonce_len,
                                         uint8_t  * adata,
                                         uint8_t    a_len,
                                         uint32_t   payload_len,
                                         uint32_t   mac_len,
                                         uint8_t  * counter,
                                         uint8_t  * formatted_data,
                                         uint32_t * formatted_length)
{
    uint8_t  flag                 = 0;
    uint8_t  mac_len_tmp          = 0;
    uint8_t  q_len                = 0;
    uint32_t formatted_length_tmp = 0;

    /* Out of range check */
    if (((7 > nonce_len) || (13 < nonce_len)) ||
        (((4 > mac_len) || (16 < mac_len)) || ((0 != (mac_len % 2)) || (SCE_DEC_110 < a_len))))
    {
        return;
    }

    /* formatting flag section in formatted data B */
    if (0 < a_len)
    {
        flag = 1 << 6;
    }

    mac_len_tmp = (uint8_t) ((mac_len - 2) / 2);
    mac_len_tmp = (uint8_t) (mac_len_tmp << 3);
    flag       |= mac_len_tmp;
    q_len       = (uint8_t) (15 - nonce_len);
    flag       |= (uint8_t) (q_len - 1);
    formatted_data[formatted_length_tmp] = flag;
    formatted_length_tmp++;

    /* adding nonce to formatted data B */
    memcpy(formatted_data + formatted_length_tmp, nonce, nonce_len);
    formatted_length_tmp += 11;
    if (12 <= nonce_len)
    {
        formatted_length_tmp++;
    }

    if (13 <= nonce_len)
    {
        formatted_length_tmp++;
    }

    /* adding Q to formatted data B */
    do
    {
        /* Casting uint32_t data to uint8_t data array. */
        formatted_data[formatted_length_tmp] = (uint8_t) (payload_len >> (8 * (15 - formatted_length_tmp)));
        formatted_length_tmp++;
    } while (16 != formatted_length_tmp);

    /* adding Adata to formatted data B */
    if (0 < a_len)
    {
        formatted_length_tmp++;
        formatted_data[formatted_length_tmp] = a_len;
        formatted_length_tmp++;
        memcpy(formatted_data + formatted_length_tmp, adata, a_len);
        formatted_length_tmp += a_len;
        if (0 != (formatted_length_tmp % HW_SCE_AES_BLOCK_BYTE_SIZE))
        {
            formatted_length_tmp += (HW_SCE_AES_BLOCK_BYTE_SIZE - (formatted_length_tmp % HW_SCE_AES_BLOCK_BYTE_SIZE));
        }
    }

    *formatted_length = formatted_length_tmp >> 2;

    /* formatting flag section in counter0 */
    flag       = (uint8_t) (q_len - 1);
    counter[0] = flag;

    /* adding nonce to counter0 */
    memcpy(counter + 1, nonce, nonce_len);
}
