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
#define SCE_RSA_SIG_SHA256_PREFIX_00    0x30
#define SCE_RSA_SIG_SHA256_PREFIX_01    0x31
#define SCE_RSA_SIG_SHA256_PREFIX_02    0x30
#define SCE_RSA_SIG_SHA256_PREFIX_03    0x0d
#define SCE_RSA_SIG_SHA256_PREFIX_04    0x06
#define SCE_RSA_SIG_SHA256_PREFIX_05    0x09
#define SCE_RSA_SIG_SHA256_PREFIX_06    0x60
#define SCE_RSA_SIG_SHA256_PREFIX_07    0x86
#define SCE_RSA_SIG_SHA256_PREFIX_08    0x48
#define SCE_RSA_SIG_SHA256_PREFIX_09    0x01
#define SCE_RSA_SIG_SHA256_PREFIX_10    0x65
#define SCE_RSA_SIG_SHA256_PREFIX_11    0x03
#define SCE_RSA_SIG_SHA256_PREFIX_12    0x04
#define SCE_RSA_SIG_SHA256_PREFIX_13    0x02
#define SCE_RSA_SIG_SHA256_PREFIX_14    0x01
#define SCE_RSA_SIG_SHA256_PREFIX_15    0x05
#define SCE_RSA_SIG_SHA256_PREFIX_16    0x00
#define SCE_RSA_SIG_SHA256_PREFIX_17    0x04
#define SCE_RSA_SIG_SHA256_PREFIX_18    0x20

#ifndef SCE_HEX_FF
 #define SCE_HEX_FF                     0xff
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static fsp_err_t calc_hash_data(uint8_t * p_mes, uint8_t * p_hash, uint32_t mes_len, uint8_t hash_type);
static fsp_err_t set_rsassapkcs_hash_data(sce_rsa_byte_data_t * p_message_hash,
                                          uint8_t               hash_type,
                                          uint32_t              rsa_key_byte_size,
                                          uint8_t             * data_buff);
static uint32_t  get_keyn_size(uint32_t * prsa_key_index, uint32_t key_max_size);
static fsp_err_t get_rand_rsaes_pkcs(uint32_t rand_size, uint8_t * prand_data);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static uint8_t gs_rsa_sig_sha256_prefix[] =
{
    SCE_RSA_SIG_SHA256_PREFIX_00,
    SCE_RSA_SIG_SHA256_PREFIX_01,
    SCE_RSA_SIG_SHA256_PREFIX_02,
    SCE_RSA_SIG_SHA256_PREFIX_03,
    SCE_RSA_SIG_SHA256_PREFIX_04,
    SCE_RSA_SIG_SHA256_PREFIX_05,
    SCE_RSA_SIG_SHA256_PREFIX_06,
    SCE_RSA_SIG_SHA256_PREFIX_07,
    SCE_RSA_SIG_SHA256_PREFIX_08,
    SCE_RSA_SIG_SHA256_PREFIX_09,
    SCE_RSA_SIG_SHA256_PREFIX_10,
    SCE_RSA_SIG_SHA256_PREFIX_11,
    SCE_RSA_SIG_SHA256_PREFIX_12,
    SCE_RSA_SIG_SHA256_PREFIX_13,
    SCE_RSA_SIG_SHA256_PREFIX_14,
    SCE_RSA_SIG_SHA256_PREFIX_15,
    SCE_RSA_SIG_SHA256_PREFIX_16,
    SCE_RSA_SIG_SHA256_PREFIX_17,
    SCE_RSA_SIG_SHA256_PREFIX_18
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup SCE_PROTECTED
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * The R_SCE_RSASSA_PKCS1024_SignatureGenerate() function generates, in accordance with RSASSA-PKCS1-V1_5, a signature
 * from the message text or hash value that is input in the first argument, message_hash, using the private wrapped
 * key input to the third argument, wrapped_key, and writes the signature text to the second argument, signature.
 * When a message is specified in the first argument, message_hash->data_type, a hash value is calculated for
 * the message as specified by the fourth argument, hash_type. When specifying a hash value in the first argument,
 * message_hash->data_type, a hash value calculated with a hash algorithm as specified by the fourth argument,
 * hash_type, must be input to message_hash->pdata.
 *
 * @param[in]     message_hash Message or hash value to which to attach signature
 *                             @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                              hash value
 *                             @arg message_hash->data_length : Specifies effective data length of the array
 *                                                              (Specify only when Message is selected)
 *                             @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                              (Message: 0 Hash value: 1)
 * @param[in,out] signature    Signature text storage destination information
 *                             @arg signature->pdata       : Specifies pointer to array storing the signature text
 *                             @arg signature->data_length : data length
 * @param[in]     wrapped_key  Inputs the 1024-bit RSA private wrapped key.
 * @param[in]     hash_type    Only HW_SCE_RSA_HASH_SHA256 is supported
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSASSA_PKCS1024_SignatureGenerate (sce_rsa_byte_data_t               * message_hash,
                                                   sce_rsa_byte_data_t               * signature,
                                                   sce_rsa1024_private_wrapped_key_t * wrapped_key,
                                                   uint8_t                             hash_type)
{
    fsp_err_t error_code = FSP_SUCCESS;
    uint8_t   data_buff[HW_SCE_RSA_1024_DATA_BYTE_SIZE] =
    {
        0
    };

    error_code = set_rsassapkcs_hash_data(message_hash, hash_type, HW_SCE_RSA_1024_DATA_BYTE_SIZE, data_buff);
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    error_code = R_SCE_Rsa1024ModularExponentDecryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (data_buff),
        (uint32_t *) (signature->pdata));

    signature->data_length = HW_SCE_RSA_1024_DATA_BYTE_SIZE;

    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_RSASSA_PKCS1024_SignatureVerify() function verifies, in accordance with RSASSA-PKCS1-V1_5, the signature text
 * input to the first argument signature, and the message text or hash value input to the second argument,
 * message_hash, using the public wrapped key input to the third argument, wrapped_key. When a message is specified
 * in the second argument, message_hash->data_type, a hash value is calculated using the public wrapped key input to
 * the third argument, wrapped_key, and as specified by the fourth argument, hash_type. When specifying a hash value
 * in the second argument, message_hash->data_type, a hash value calculated with a hash algorithm as specified by the
 * fourth argument, hash_type, must be input to message_hash->pdata.
 *
 * @param[in] signature    Signature text information to verify
 *                         @arg signature->pdata       : Specifies pointer to array storing the signature text
 *                         @arg signature->data_length : Specifies effective data length of the array
 * @param[in] message_hash Message text or hash value to verify
 *                         @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                          hash value
 *                         @arg message_hash->data_length : Specifies effective data length of the array
 *                                                          (Specify only when Message is selected)
 *                         @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                          (Message: 0 Hash value: 1)
 * @param[in] wrapped_key  Inputs the 1024-bit RSA public wrapped key.
 * @param[in] hash_type    Only HW_SCE_RSA_HASH_SHA256 is supported
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION    Authentication failed
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSASSA_PKCS1024_SignatureVerify (sce_rsa_byte_data_t              * signature,
                                                 sce_rsa_byte_data_t              * message_hash,
                                                 sce_rsa1024_public_wrapped_key_t * wrapped_key,
                                                 uint8_t                            hash_type)
{
    fsp_err_t error_code = FSP_SUCCESS;
    uint8_t   data_buff[HW_SCE_RSA_1024_DATA_BYTE_SIZE] =
    {
        0
    };
    uint8_t decrypt_data[HW_SCE_RSA_1024_DATA_BYTE_SIZE] =
    {
        0
    };
    uint32_t data_ptr = 0;

    data_ptr = HW_SCE_RSA_1024_DATA_BYTE_SIZE - signature->data_length;
    memcpy(data_buff + data_ptr, signature->pdata, signature->data_length);

    error_code = R_SCE_Rsa1024ModularExponentEncryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (data_buff),
        (uint32_t *) (decrypt_data));
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    error_code = set_rsassapkcs_hash_data(message_hash, hash_type, HW_SCE_RSA_1024_DATA_BYTE_SIZE, data_buff);
    if (FSP_SUCCESS == error_code)
    {
        if (memcmp(data_buff, decrypt_data, HW_SCE_RSA_1024_DATA_BYTE_SIZE))
        {
            error_code = FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_RSAES_PKCS1024_Encrypt() function RSA-encrypts the plaintext input to the first argument, plain,
 * according to RSAES-PKCS1-V1_5. It writes the encryption result to the second argument, cipher.
 *
 * @param[in]     plain       plaintext
 *                            @arg plain->pdata       : Specifies pointer to array containing plaintext.
 *                            @arg plain->data_length : Specifies valid data length of plaintext array.
 *                                                      data size <= public key n size - 11
 * @param[in,out] cipher      ciphertext
 *                            @arg cipher->pdata       : Specifies pointer to array containing ciphertext.
 *                            @arg cipher->data_length : Inputs ciphertext buffer size.
 *                                                       Outputs valid data length after encryption 
 *                                                       (public key n size).
 * @param[in]     wrapped_key Inputs the 1024-bit RSA public wrapped key.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Incorrect wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSAES_PKCS1024_Encrypt (sce_rsa_byte_data_t              * plain,
                                        sce_rsa_byte_data_t              * cipher,
                                        sce_rsa1024_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t ercd = FSP_SUCCESS;
    uint8_t   input_data_arry[HW_SCE_RSA_1024_DATA_BYTE_SIZE] =
    {
        0
    };
    uint8_t output_data_arry[HW_SCE_RSA_1024_DATA_BYTE_SIZE] =
    {
        0
    };
    uint32_t key_size = 0;
    uint32_t ptr      = 0;

    /* Casting uint32_t pointer is used for address. */
    key_size = get_keyn_size((uint32_t *) &wrapped_key->value.key_n, HW_SCE_RSA_1024_DATA_BYTE_SIZE);
    if (key_size < HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if ((plain->data_length) > (key_size - HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (cipher->data_length < key_size)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    cipher->data_length = key_size;

    /***   RSAES-PKCS#1_V1.5 format   ***/
    /*       (1)   |  (2)   | (3)  |  (4)   | (5) */
    /* EM = [0x00] | [0x02] | [PS] | [0x00] | [M] */
    ptr = HW_SCE_RSA_1024_DATA_BYTE_SIZE - key_size;
    input_data_arry[ptr] = 0x00;
    ptr++;
    input_data_arry[ptr] = 0x02;
    ptr++;

    get_rand_rsaes_pkcs(((key_size - plain->data_length) - 3), &input_data_arry[ptr]);
    ptr += ((key_size - plain->data_length) - 3);
    input_data_arry[ptr] = 0x00;
    ptr++;

    memcpy(&input_data_arry[ptr], plain->pdata, plain->data_length);

    ercd = R_SCE_Rsa1024ModularExponentEncryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (input_data_arry),
        (uint32_t *) (output_data_arry));
    memcpy(cipher->pdata, &output_data_arry[HW_SCE_RSA_1024_DATA_BYTE_SIZE - key_size], cipher->data_length);

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_RSAES_PKCS1024_Decrypt() function RSA-decrypts the ciphertext input to the first argument, cipher,
 * according to RSAES-PKCS1-V1_5. It writes the decryption result to the second argument, plain.
 *
 * @param[in]     cipher      ciphertext
 *                            @arg cipher->pdata       : Specifies pointer to array containing ciphertext.
 *                            @arg cipher->data_length : Inputs ciphertext buffer size.
 *                                                       Outputs valid data length after encryption 
 *                                                       (public key n size).
 * @param[in,out] plain       plaintext
 *                            @arg plain->pdata       : Specifies pointer to array containing plaintext.
 *                            @arg plain->data_length : Inputs plaintext buffer size.
 *                                                      The following size is required.
 *                                                      Plaintext buffer size >= public key n size -11.
 *                                                      Outputs valid data length after decryption 
 *                                                      (public key n size).
 * @param[in]     wrapped_key Inputs the 1024-bit RSA private wrapped key.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Incorrect wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSAES_PKCS1024_Decrypt (sce_rsa_byte_data_t               * cipher,
                                        sce_rsa_byte_data_t               * plain,
                                        sce_rsa1024_private_wrapped_key_t * wrapped_key)
{
    fsp_err_t ercd = FSP_SUCCESS;
    uint8_t   input_data_arry[HW_SCE_RSA_1024_DATA_BYTE_SIZE] =
    {
        0
    };
    uint8_t output_data_arry[HW_SCE_RSA_1024_DATA_BYTE_SIZE] =
    {
        0
    };
    uint32_t  key_size   = 0;
    uint32_t  ptr        = 0;
    uint32_t  ptr_start  = 0;
    uint8_t * p_start    = 0;
    uint8_t * p_zero_ptr = 0;

    /* Casting uint32_t pointer is used for address. */
    key_size = get_keyn_size((uint32_t *) &wrapped_key->value.key_n, HW_SCE_RSA_1024_DATA_BYTE_SIZE);
    if (key_size < HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (cipher->data_length != key_size)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (plain->data_length < (key_size - HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    memcpy(&input_data_arry[HW_SCE_RSA_1024_DATA_BYTE_SIZE - key_size], cipher->pdata, cipher->data_length);
    ercd = R_SCE_Rsa1024ModularExponentDecryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (input_data_arry),
        (uint32_t *) (output_data_arry));
    if (FSP_SUCCESS != ercd)
    {
        return ercd;
    }

    /***   RSAES-PKCS#1_V1.5 format   ***/
    /*       (1)   |  (2)   | (3)  |  (4)   | (5) */
    /* EM = [0x00] | [0x02] | [PS] | [0x00] | [M] */
    ptr       = HW_SCE_RSA_1024_DATA_BYTE_SIZE - key_size;
    ptr_start = ptr;

    /* (1) */
    if (0x00 != output_data_arry[ptr])
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    ptr++;

    /* (2) */
    if (0x02 != output_data_arry[ptr])
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    ptr++;

    /* (3) and (4) */
    p_start = &output_data_arry[ptr];

    /* Casting uint8_t pointer is used for address. */
    p_zero_ptr = (uint8_t *) memchr(p_start, 0x00, key_size - 2); /* "2" is (1)+(2) */
    if (NULL == p_zero_ptr)
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    if ((HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE - 3) > (uint32_t) (p_zero_ptr - p_start))
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    ptr += (uint32_t) ((p_zero_ptr - p_start) + 1);

    plain->data_length = key_size - (ptr - ptr_start);
    memcpy(plain->pdata, &output_data_arry[ptr], plain->data_length);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * The R_SCE_RSASSA_PKCS2048_SignatureGenerate() function generates, in accordance with RSASSA-PKCS1-V1_5, a signature
 * from the message text or hash value that is input in the first argument, message_hash, using the private wrapped
 * key input to the third argument, wrapped_key, and writes the signature text to the second argument, signature.
 * When a message is specified in the first argument, message_hash->data_type, a hash value is calculated for
 * the message as specified by the fourth argument, hash_type. When specifying a hash value in the first argument,
 * message_hash->data_type, a hash value calculated with a hash algorithm as specified by the fourth argument,
 * hash_type, must be input to message_hash->pdata.
 *
 * @param[in]     message_hash Message or hash value to which to attach signature
 *                             @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                              hash value
 *                             @arg message_hash->data_length : Specifies effective data length of the array
 *                                                              (Specify only when Message is selected)
 *                             @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                              (Message: 0 Hash value: 1)
 * @param[in,out] signature    Signature text storage destination information
 *                             @arg signature->pdata       : Specifies pointer to array storing the signature text
 *                             @arg signature->data_length : data length
 * @param[in]     wrapped_key  Inputs the 2048-bit RSA private wrapped key.
 * @param[in]     hash_type    Only HW_SCE_RSA_HASH_SHA256 is supported
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSASSA_PKCS2048_SignatureGenerate (sce_rsa_byte_data_t               * message_hash,
                                                   sce_rsa_byte_data_t               * signature,
                                                   sce_rsa2048_private_wrapped_key_t * wrapped_key,
                                                   uint8_t                             hash_type)
{
    fsp_err_t error_code = FSP_SUCCESS;
    uint8_t   data_buff[HW_SCE_RSA_2048_DATA_BYTE_SIZE] =
    {
        0
    };

    error_code = set_rsassapkcs_hash_data(message_hash, hash_type, HW_SCE_RSA_2048_DATA_BYTE_SIZE, data_buff);
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    error_code = R_SCE_Rsa2048ModularExponentDecryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (data_buff),
        (uint32_t *) (signature->pdata));

    signature->data_length = HW_SCE_RSA_2048_DATA_BYTE_SIZE;

    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_RSASSA_PKCS2048_SignatureVerify() function verifies, in accordance with RSASSA-PKCS1-V1_5, the signature text
 * input to the first argument signature, and the message text or hash value input to the second argument,
 * message_hash, using the public wrapped key input to the third argument, wrapped_key. When a message is specified
 * in the second argument, message_hash->data_type, a hash value is calculated using the public wrapped key input to
 * the third argument, wrapped_key, and as specified by the fourth argument, hash_type. When specifying a hash value
 * in the second argument, message_hash->data_type, a hash value calculated with a hash algorithm as specified by the
 * fourth argument, hash_type, must be input to message_hash->pdata.
 *
 * @param[in] signature    Signature text information to verify
 *                         @arg signature->pdata       : Specifies pointer to array storing the signature text
 *                         @arg signature->data_length : Specifies effective data length of the array
 * @param[in] message_hash Message text or hash value to verify
 *                         @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                          hash value
 *                         @arg message_hash->data_length : Specifies effective data length of the array
 *                                                          (Specify only when Message is selected)
 *                         @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                          (Message: 0 Hash value: 1)
 * @param[in] wrapped_key  Inputs the 1024-bit RSA public wrapped key.
 * @param[in] hash_type    Only HW_SCE_RSA_HASH_SHA256 is supported
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION    Authentication failed
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSASSA_PKCS2048_SignatureVerify (sce_rsa_byte_data_t              * signature,
                                                 sce_rsa_byte_data_t              * message_hash,
                                                 sce_rsa2048_public_wrapped_key_t * wrapped_key,
                                                 uint8_t                            hash_type)
{
    fsp_err_t error_code = FSP_SUCCESS;
    uint8_t   data_buff[HW_SCE_RSA_2048_DATA_BYTE_SIZE] =
    {
        0
    };
    uint8_t decrypt_data[HW_SCE_RSA_2048_DATA_BYTE_SIZE] =
    {
        0
    };
    uint32_t data_ptr = 0;

    data_ptr = HW_SCE_RSA_2048_DATA_BYTE_SIZE - signature->data_length;
    memcpy(data_buff + data_ptr, signature->pdata, signature->data_length);

    error_code = R_SCE_Rsa2048ModularExponentEncryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (data_buff),
        (uint32_t *) (decrypt_data));
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    error_code = set_rsassapkcs_hash_data(message_hash, hash_type, HW_SCE_RSA_2048_DATA_BYTE_SIZE, data_buff);
    if (FSP_SUCCESS == error_code)
    {
        if (memcmp(data_buff, decrypt_data, HW_SCE_RSA_2048_DATA_BYTE_SIZE))
        {
            error_code = FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_RSASSA_PKCS3072_SignatureVerify() function verifies, in accordance with RSASSA-PKCS1-V1_5, the signature text
 * input to the first argument signature, and the message text or hash value input to the second argument,
 * message_hash, using the public wrapped key input to the third argument, wrapped_key. When a message is specified
 * in the second argument, message_hash->data_type, a hash value is calculated using the public wrapped key input to
 * the third argument, wrapped_key, and as specified by the fourth argument, hash_type. When specifying a hash value
 * in the second argument, message_hash->data_type, a hash value calculated with a hash algorithm as specified by the
 * fourth argument, hash_type, must be input to message_hash->pdata.
 *
 * @param[in] signature    Signature text information to verify
 *                         @arg signature->pdata       : Specifies pointer to array storing the signature text
 *                         @arg signature->data_length : Specifies effective data length of the array
 * @param[in] message_hash Message text or hash value to verify
 *                         @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                          hash value
 *                         @arg message_hash->data_length : Specifies effective data length of the array
 *                                                          (Specify only when Message is selected)
 *                         @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                          (Message: 0 Hash value: 1)
 * @param[in] wrapped_key  Inputs the 3072-bit RSA public wrapped key.
 * @param[in] hash_type    Only HW_SCE_RSA_HASH_SHA256 is supported
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION    Authentication failed
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSASSA_PKCS3072_SignatureVerify (sce_rsa_byte_data_t              * signature,
                                                 sce_rsa_byte_data_t              * message_hash,
                                                 sce_rsa3072_public_wrapped_key_t * wrapped_key,
                                                 uint8_t                            hash_type)
{
    fsp_err_t error_code = FSP_SUCCESS;
    uint8_t   data_buff[HW_SCE_RSA_3072_DATA_BYTE_SIZE] =
    {
        0
    };
    uint8_t decrypt_data[HW_SCE_RSA_3072_DATA_BYTE_SIZE] =
    {
        0
    };
    uint32_t data_ptr = 0;

    data_ptr = HW_SCE_RSA_3072_DATA_BYTE_SIZE - signature->data_length;
    memcpy(data_buff + data_ptr, signature->pdata, signature->data_length);

    error_code = R_SCE_Rsa3072ModularExponentEncryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (data_buff),
        (uint32_t *) (decrypt_data));
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    error_code = set_rsassapkcs_hash_data(message_hash, hash_type, HW_SCE_RSA_3072_DATA_BYTE_SIZE, data_buff);
    if (FSP_SUCCESS == error_code)
    {
        if (memcmp(data_buff, decrypt_data, HW_SCE_RSA_3072_DATA_BYTE_SIZE))
        {
            error_code = FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_RSASSA_PKCS4096_SignatureVerify() function verifies, in accordance with RSASSA-PKCS1-V1_5, the signature text
 * input to the first argument signature, and the message text or hash value input to the second argument,
 * message_hash, using the public wrapped key input to the third argument, wrapped_key. When a message is specified
 * in the second argument, message_hash->data_type, a hash value is calculated using the public wrapped key input to
 * the third argument, wrapped_key, and as specified by the fourth argument, hash_type. When specifying a hash value
 * in the second argument, message_hash->data_type, a hash value calculated with a hash algorithm as specified by the
 * fourth argument, hash_type, must be input to message_hash->pdata.
 *
 * @param[in] signature    Signature text information to verify
 *                         @arg signature->pdata       : Specifies pointer to array storing the signature text
 *                         @arg signature->data_length : Specifies effective data length of the array
 * @param[in] message_hash Message text or hash value to verify
 *                         @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                          hash value
 *                         @arg message_hash->data_length : Specifies effective data length of the array
 *                                                          (Specify only when Message is selected)
 *                         @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                          (Message: 0 Hash value: 1)
 * @param[in] wrapped_key  Inputs the 1024-bit RSA public wrapped key.
 * @param[in] hash_type    Only HW_SCE_RSA_HASH_SHA256 is supported
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION    Authentication failed
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSASSA_PKCS4096_SignatureVerify (sce_rsa_byte_data_t              * signature,
                                                 sce_rsa_byte_data_t              * message_hash,
                                                 sce_rsa4096_public_wrapped_key_t * wrapped_key,
                                                 uint8_t                            hash_type)
{
    fsp_err_t error_code = FSP_SUCCESS;
    uint8_t   data_buff[HW_SCE_RSA_4096_DATA_BYTE_SIZE] =
    {
        0
    };
    uint8_t decrypt_data[HW_SCE_RSA_4096_DATA_BYTE_SIZE] =
    {
        0
    };
    uint32_t data_ptr = 0;

    data_ptr = HW_SCE_RSA_4096_DATA_BYTE_SIZE - signature->data_length;
    memcpy(data_buff + data_ptr, signature->pdata, signature->data_length);

    error_code = R_SCE_Rsa4096ModularExponentEncryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (data_buff),
        (uint32_t *) (decrypt_data));
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    error_code = set_rsassapkcs_hash_data(message_hash, hash_type, HW_SCE_RSA_4096_DATA_BYTE_SIZE, data_buff);
    if (FSP_SUCCESS == error_code)
    {
        if (memcmp(data_buff, decrypt_data, HW_SCE_RSA_4096_DATA_BYTE_SIZE))
        {
            error_code = FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_RSAES_PKCS2048_Encrypt() function RSA-encrypts the plaintext input to the first argument, plain,
 * according to RSAES-PKCS1-V1_5. It writes the encryption result to the second argument, cipher.
 *
 * @param[in]     plain       plaintext
 *                            @arg plain->pdata       : Specifies pointer to array containing plaintext.
 *                            @arg plain->data_length : Specifies valid data length of plaintext array.
 *                                                      data size <= public key n size - 11
 * @param[in,out] cipher      ciphertext
 *                            @arg cipher->pdata       : Specifies pointer to array containing ciphertext.
 *                            @arg cipher->data_length : Inputs ciphertext buffer size.
 *                                                       Outputs valid data length after encryption 
 *                                                       (public key n size).
 * @param[in]     wrapped_key Inputs the 2048-bit RSA public wrapped key.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Incorrect wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSAES_PKCS2048_Encrypt (sce_rsa_byte_data_t              * plain,
                                        sce_rsa_byte_data_t              * cipher,
                                        sce_rsa2048_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t ercd = FSP_SUCCESS;
    uint8_t   input_data_arry[HW_SCE_RSA_2048_DATA_BYTE_SIZE] =
    {
        0
    };
    uint8_t output_data_arry[HW_SCE_RSA_2048_DATA_BYTE_SIZE] =
    {
        0
    };
    uint32_t key_size = 0;
    uint32_t ptr      = 0;

    /* Casting uint32_t pointer is used for address. */
    key_size = get_keyn_size((uint32_t *) &wrapped_key->value.key_n, HW_SCE_RSA_2048_DATA_BYTE_SIZE);
    if (key_size < HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if ((plain->data_length) > (key_size - HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (cipher->data_length < key_size)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    cipher->data_length = key_size;

    /***   RSAES-PKCS#1_V1.5 format   ***/
    /*       (1)   |  (2)   | (3)  |  (4)   | (5) */
    /* EM = [0x00] | [0x02] | [PS] | [0x00] | [M] */
    ptr = HW_SCE_RSA_2048_DATA_BYTE_SIZE - key_size;
    input_data_arry[ptr] = 0x00;
    ptr++;
    input_data_arry[ptr] = 0x02;
    ptr++;

    get_rand_rsaes_pkcs(((key_size - plain->data_length) - 3), &input_data_arry[ptr]);
    ptr += ((key_size - plain->data_length) - 3);
    input_data_arry[ptr] = 0x00;
    ptr++;

    memcpy(&input_data_arry[ptr], plain->pdata, plain->data_length);

    ercd = R_SCE_Rsa2048ModularExponentEncryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (input_data_arry),
        (uint32_t *) (output_data_arry));
    memcpy(cipher->pdata, &output_data_arry[HW_SCE_RSA_2048_DATA_BYTE_SIZE - key_size], cipher->data_length);

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_RSAES_PKCS2048_Decrypt() function RSA-decrypts the ciphertext input to the first argument, cipher,
 * according to RSAES-PKCS1-V1_5. It writes the decryption result to the second argument, plain.
 *
 * @param[in]     cipher      ciphertext
 *                            @arg cipher->pdata       : Specifies pointer to array containing ciphertext.
 *                            @arg cipher->data_length : Inputs ciphertext buffer size.
 *                                                       Outputs valid data length after encryption 
 *                                                       (public key n size).
 * @param[in,out] plain       plaintext
 *                            @arg plain->pdata       : Specifies pointer to array containing plaintext.
 *                            @arg plain->data_length : Inputs plaintext buffer size.
 *                                                      The following size is required.
 *                                                      Plaintext buffer size >= public key n size -11.
 *                                                      Outputs valid data length after decryption 
 *                                                      (public key n size).
 * @param[in]     wrapped_key Inputs the 1024-bit RSA private wrapped key.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Incorrect wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSAES_PKCS2048_Decrypt (sce_rsa_byte_data_t               * cipher,
                                        sce_rsa_byte_data_t               * plain,
                                        sce_rsa2048_private_wrapped_key_t * wrapped_key)
{
    fsp_err_t ercd = FSP_SUCCESS;
    uint8_t   input_data_arry[HW_SCE_RSA_2048_DATA_BYTE_SIZE] =
    {
        0
    };
    uint8_t output_data_arry[HW_SCE_RSA_2048_DATA_BYTE_SIZE] =
    {
        0
    };
    uint32_t  key_size   = 0;
    uint32_t  ptr        = 0;
    uint32_t  ptr_start  = 0;
    uint8_t * p_start    = 0;
    uint8_t * p_zero_ptr = 0;

    /* Casting uint32_t pointer is used for address. */
    key_size = get_keyn_size((uint32_t *) &wrapped_key->value.key_n, HW_SCE_RSA_2048_DATA_BYTE_SIZE);
    if (key_size < HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (cipher->data_length != key_size)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (plain->data_length < (key_size - HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    memcpy(&input_data_arry[HW_SCE_RSA_2048_DATA_BYTE_SIZE - key_size], cipher->pdata, cipher->data_length);
    ercd = R_SCE_Rsa2048ModularExponentDecryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (input_data_arry),
        (uint32_t *) (output_data_arry));
    if (FSP_SUCCESS != ercd)
    {
        return ercd;
    }

    /***   RSAES-PKCS#1_V1.5 format   ***/
    /*       (1)   |  (2)   | (3)  |  (4)   | (5) */
    /* EM = [0x00] | [0x02] | [PS] | [0x00] | [M] */
    ptr       = HW_SCE_RSA_2048_DATA_BYTE_SIZE - key_size;
    ptr_start = ptr;

    /* (1) */
    if (0x00 != output_data_arry[ptr])
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    ptr++;

    /* (2) */
    if (0x02 != output_data_arry[ptr])
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    ptr++;

    /* (3) and (4) */
    p_start = &output_data_arry[ptr];

    /* Casting uint8_t pointer is used for address. */
    p_zero_ptr = (uint8_t *) memchr(p_start, 0x00, key_size - 2); /* "2" is (1)+(2) */
    if (NULL == p_zero_ptr)
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    if ((HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE - 3) > (uint32_t) (p_zero_ptr - p_start))
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    ptr += (uint32_t) ((p_zero_ptr - p_start) + 1);

    plain->data_length = key_size - (ptr - ptr_start);
    memcpy(plain->pdata, &output_data_arry[ptr], plain->data_length);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * The R_SCE_RSAES_PKCS3072_Encrypt() function RSA-encrypts the plaintext input to the first argument, plain,
 * according to RSAES-PKCS1-V1_5. It writes the encryption result to the second argument, cipher.
 *
 * @param[in]     plain       plaintext
 *                            @arg plain->pdata       : Specifies pointer to array containing plaintext.
 *                            @arg plain->data_length : Specifies valid data length of plaintext array.
 *                                                      data size <= public key n size - 11
 * @param[in,out] cipher      ciphertext
 *                            @arg cipher->pdata       : Specifies pointer to array containing ciphertext.
 *                            @arg cipher->data_length : Inputs ciphertext buffer size.
 *                                                       Outputs valid data length after encryption 
 *                                                       (public key n size).
 * @param[in]     wrapped_key Inputs the 3072-bit RSA public wrapped key.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Incorrect wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSAES_PKCS3072_Encrypt (sce_rsa_byte_data_t              * plain,
                                        sce_rsa_byte_data_t              * cipher,
                                        sce_rsa3072_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t ercd = FSP_SUCCESS;
    uint8_t   input_data_arry[HW_SCE_RSA_3072_DATA_BYTE_SIZE] =
    {
        0
    };
    uint8_t output_data_arry[HW_SCE_RSA_3072_DATA_BYTE_SIZE] =
    {
        0
    };
    uint32_t key_size = 0;
    uint32_t ptr      = 0;

    /* Casting uint32_t pointer is used for address. */
    key_size = get_keyn_size((uint32_t *) &wrapped_key->value.key_n, HW_SCE_RSA_3072_DATA_BYTE_SIZE);
    if (key_size < HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if ((plain->data_length) > (key_size - HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (cipher->data_length < key_size)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    cipher->data_length = key_size;

    /***   RSAES-PKCS#1_V1.5 format   ***/
    /*       (1)   |  (2)   | (3)  |  (4)   | (5) */
    /* EM = [0x00] | [0x02] | [PS] | [0x00] | [M] */
    ptr = HW_SCE_RSA_3072_DATA_BYTE_SIZE - key_size;
    input_data_arry[ptr] = 0x00;
    ptr++;
    input_data_arry[ptr] = 0x02;
    ptr++;

    get_rand_rsaes_pkcs(((key_size - plain->data_length) - 3), &input_data_arry[ptr]);
    ptr += ((key_size - plain->data_length) - 3);
    input_data_arry[ptr] = 0x00;
    ptr++;

    memcpy(&input_data_arry[ptr], plain->pdata, plain->data_length);

    ercd = R_SCE_Rsa3072ModularExponentEncryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (input_data_arry),
        (uint32_t *) (output_data_arry));
    memcpy(cipher->pdata, &output_data_arry[HW_SCE_RSA_3072_DATA_BYTE_SIZE - key_size], cipher->data_length);

    return ercd;
}

/*******************************************************************************************************************//**
 * The R_SCE_RSAES_PKCS4096_Encrypt() function RSA-encrypts the plaintext input to the first argument, plain,
 * according to RSAES-PKCS1-V1_5. It writes the encryption result to the second argument, cipher.
 *
 * @param[in]     plain       plaintext
 *                            @arg plain->pdata       : Specifies pointer to array containing plaintext.
 *                            @arg plain->data_length : Specifies valid data length of plaintext array.
 *                                                      data size <= public key n size - 11
 * @param[in,out] cipher      ciphertext
 *                            @arg cipher->pdata       : Specifies pointer to array containing ciphertext.
 *                            @arg cipher->data_length : Inputs ciphertext buffer size.
 *                                                       Outputs valid data length after encryption 
 *                                                       (public key n size).
 * @param[in]     wrapped_key Inputs the 4096-bit RSA public wrapped key.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Incorrect wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is illegal.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSAES_PKCS4096_Encrypt (sce_rsa_byte_data_t              * plain,
                                        sce_rsa_byte_data_t              * cipher,
                                        sce_rsa4096_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t ercd = FSP_SUCCESS;
    uint8_t   input_data_arry[HW_SCE_RSA_4096_DATA_BYTE_SIZE] =
    {
        0
    };
    uint8_t output_data_arry[HW_SCE_RSA_4096_DATA_BYTE_SIZE] =
    {
        0
    };
    uint32_t key_size = 0;
    uint32_t ptr      = 0;

    /* Casting uint32_t pointer is used for address. */
    key_size = get_keyn_size((uint32_t *) &wrapped_key->value.key_n, HW_SCE_RSA_4096_DATA_BYTE_SIZE);
    if (key_size < HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if ((plain->data_length) > (key_size - HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (cipher->data_length < key_size)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    cipher->data_length = key_size;

    /***   RSAES-PKCS#1_V1.5 format   ***/
    /*       (1)   |  (2)   | (3)  |  (4)   | (5) */
    /* EM = [0x00] | [0x02] | [PS] | [0x00] | [M] */
    ptr = HW_SCE_RSA_4096_DATA_BYTE_SIZE - key_size;
    input_data_arry[ptr] = 0x00;
    ptr++;
    input_data_arry[ptr] = 0x02;
    ptr++;

    get_rand_rsaes_pkcs(((key_size - plain->data_length) - 3), &input_data_arry[ptr]);
    ptr += ((key_size - plain->data_length) - 3);
    input_data_arry[ptr] = 0x00;
    ptr++;

    memcpy(&input_data_arry[ptr], plain->pdata, plain->data_length);

    ercd = R_SCE_Rsa4096ModularExponentEncryptPrivate(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) (input_data_arry),
        (uint32_t *) (output_data_arry));
    memcpy(cipher->pdata, &output_data_arry[HW_SCE_RSA_4096_DATA_BYTE_SIZE - key_size], cipher->data_length);

    return ercd;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCE_PROTECTED)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Hash message text according to the hash type.
 *
 * @param p_mes     message text
 * @param p_hash    pointer of hash data
 * @param mes_len   message size(byte)
 * @param hash_type hash type
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input parameter illegal
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 **********************************************************************************************************************/
static fsp_err_t calc_hash_data (uint8_t * p_mes, uint8_t * p_hash, uint32_t mes_len, uint8_t hash_type)
{
    fsp_err_t            error_code    = FSP_SUCCESS;
    sce_sha_md5_handle_t ex_sha_handle =
    {
        0
    };
    uint32_t hash_length = 0;

    if (HW_SCE_RSA_HASH_SHA256 == hash_type)
    {
        R_SCE_SHA256_Init(&ex_sha_handle);
        error_code = R_SCE_SHA256_Update(&ex_sha_handle, p_mes, mes_len);
        if (FSP_SUCCESS != error_code)
        {
            return error_code;
        }

        error_code = R_SCE_SHA256_Final(&ex_sha_handle, p_hash, &hash_length);
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * Prefix the hash of the message according to RSASSA-PKCS1-V1_5.
 *
 * @param p_message_hash    message text or hash value
 * @param hash_type         hash type
 * @param rsa_key_byte_size RSA data size
 * @param data_buff         pointer of Sig data
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input parameter illegal
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 **********************************************************************************************************************/
static fsp_err_t set_rsassapkcs_hash_data (sce_rsa_byte_data_t * p_message_hash,
                                           uint8_t               hash_type,
                                           uint32_t              rsa_key_byte_size,
                                           uint8_t             * data_buff)
{
    fsp_err_t           error_code = FSP_SUCCESS;
    sce_rsa_byte_data_t prefix     =
    {
        0
    };
    uint32_t hash_data_buff[HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE / sizeof(uint32_t)] =
    {
        0
    };
    uint32_t hash_length = 0;
    uint32_t data_ptr    = 0;

    if ((HW_SCE_RSA_HASH_SHA256 < hash_type) || (1 < p_message_hash->data_type))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    if (0 == p_message_hash->data_type)
    {
        /* Casting uint8_t pointer is used for address. */
        error_code = calc_hash_data(p_message_hash->pdata,
                                    (uint8_t *) hash_data_buff,
                                    p_message_hash->data_length,
                                    hash_type);
        if (FSP_SUCCESS != error_code)
        {
            return error_code;
        }
    }

    if (HW_SCE_RSA_HASH_SHA256 == hash_type)
    {
        prefix.pdata       = gs_rsa_sig_sha256_prefix;
        prefix.data_length = sizeof(gs_rsa_sig_sha256_prefix);
        hash_length        = HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE;
    }

    data_buff[0] = 0x00;
    data_buff[1] = 0x01;
    data_ptr     = ((rsa_key_byte_size - prefix.data_length) - hash_length) - 1;
    memset(data_buff + 2, SCE_HEX_FF, data_ptr);
    data_buff[data_ptr] = 0x0;
    data_ptr++;
    memcpy(data_buff + data_ptr, prefix.pdata, prefix.data_length);
    data_ptr += prefix.data_length;
    if (0 == p_message_hash->data_type)
    {
        memcpy(data_buff + data_ptr, hash_data_buff, hash_length);
    }
    else                               /* if (1 == p_message_hash->data_type) */
    {
        memcpy(data_buff + data_ptr, p_message_hash->pdata, hash_length);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get key n size from RSA key index
 *
 * @param prsa_key_index RSA key index
 * @param key_max_size   key data max byte size
 *
 * @return key_size
 **********************************************************************************************************************/
static uint32_t get_keyn_size (uint32_t * prsa_key_index, uint32_t key_max_size)
{
    bool get_output_data_length = false;

    /* Casting uint8_t pointer is used for address. */
    uint8_t * p_rsa_key_n_data = (uint8_t *) prsa_key_index;
    uint32_t  key_size_tmp     = 0;

    key_size_tmp = key_max_size;
    for (uint32_t i = 0; i < (key_max_size); i++)
    {
        if (!get_output_data_length)
        {
            if (0 == p_rsa_key_n_data[i])
            {
                key_size_tmp--;
            }
            else
            {
                get_output_data_length = true;
            }
        }
    }

    return key_size_tmp;
}

/*******************************************************************************************************************//**
 * In accordance with RSAES-PKCS1-V1_5 to obtain random number data of rand_size that does not contain 0.
 *
 * @param rand_size  random data size
 * @param prand_data random data area pointer
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 **********************************************************************************************************************/
static fsp_err_t get_rand_rsaes_pkcs (uint32_t rand_size, uint8_t * prand_data)
{
    fsp_err_t ercd         = FSP_SUCCESS;
    uint8_t   rand_tmp[16] =
    {
        0
    };
    uint32_t rest_size = rand_size;
    uint32_t rand_ptr  = 0;
    uint32_t i         = 0;

    while (rest_size)
    {
#if defined RSA_ENC_TEST_MODE
        memset(rand_tmp, SCE_HEX_FF, sizeof(rand_tmp));
#else

        /* Casting uint32_t pointer is used for address. */
        ercd = R_SCE_RandomNumberGenerate((uint32_t *) rand_tmp);
        if (FSP_SUCCESS != ercd)
        {
            break;
        }
#endif                                 /* defined RSA_ENC_TEST_MODE */
        for (i = 0; i < 16; i++)
        {
            if (0 != rand_tmp[i])
            {
                prand_data[rand_ptr] = rand_tmp[i];
                rand_ptr++;
                rest_size--;
            }

            if (0 == rest_size)
            {
                break;
            }
        }
    }

    return ercd;
}
