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
#define SCE_PRV_HASH_WORD_POS_ECDSA_P192    (2)                /* Hash data output position for ECDSA P-192. : (256 - 192) / 32 */
#define SCE_PRV_HASH_WORD_POS_ECDSA_P224    (1)                /* Hash data output position for ECDSA P-224. : (256 - 224) / 32 */
#define SCE_PRV_HASH_WORD_POS_ECDSA_P256    (0)                /* Hash data output position for ECDSA P-256. : (256 - 256) / 32 */
#define SCE_PRV_HASH_WORD_POS_ECDSA_P384    (0xFFFFFFFCUL)     /* For ECDSA P-384 : (256 - 384) / 32 */

/* Block length (in bytes) of ECDH */
#define SCE_PRV_INDATA_BYTEDATA_LEN         (32 * 4)           /* 32 words */
#define SCE_PRV_OTHER_INFO_BYTE_LEN_2B      ((7 + 16 * 1) * 4) /* 2 blocks */
#define SCE_PRV_OTHER_INFO_BYTE_LEN_3B      ((7 + 16 * 2) * 4) /* 3 blocks */
#define SCE_PRV_OTHER_INFO_BYTE_LEN_SUPP    (288)              /* suppPubInfo + suppPrivInfo */

#ifndef SCE_HEX_FF
 #define SCE_HEX_FF                         (0xFF)
#endif
#ifndef SCE_HEX_80
 #define SCE_HEX_80                         (0x80)
#endif
#ifndef SCE_DEC_64
 #define SCE_DEC_64                         (64)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* For R_SCE_ECDH_secp256r1_PublicKeyVerify */
typedef struct st_read_public_key
{
    uint32_t cmd;
    uint8_t  bytedata[SCE_PRV_INDATA_BYTEDATA_LEN];
} st_read_public_key_t;

/* For R_SCE_ECDH_secp256r1_KeyDerivation */
typedef struct st_key_derivation
{
    uint32_t keyindextype;
    uint32_t kdftype;
    uint32_t max_cnt_byte;
    uint8_t  paddedmsg[SCE_PRV_OTHER_INFO_BYTE_LEN_3B];
} st_key_derivation_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static fsp_err_t set_ecdsa_hash_data(sce_ecdsa_byte_data_t * p_message_hash,
                                     uint32_t              * data_buff,
                                     uint32_t                hash_word_pos);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static const SCE_KEY_INDEX_TYPE s_key_index_type[3] =
{
    SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH, SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH, SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_ECDH
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern uint32_t g_private_id_counter;
uint32_t        g_ecdh256_private_id;

/*******************************************************************************************************************//**
 * @addtogroup SCE_PROTECTED
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * When a message is specified in the first argument, message_hash->data_type, a SHA-256 hash of the message text
 * input as the first argument, message_hash->pdata, is calculated, and the signature text is written to the second
 * argument, signature, in accordance with secp192r1 using the private wrapped key input as the third argument,
 * wrapped_key.
 *
 * When a hash value is specified in the first argument, message_hash->data_type, the signature text for the first
 * 24 bytes of the SHA-256 hash value input to the first argument, message_hash->pdata, is written to the second
 * argument, signature, in accordance with secp192r1 using the private wrapped key input as the third argument,
 * wrapped_key.
 *
 * @param[in]     message_hash Message or hash value to which to attach signature
 *                             @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                              hash value
 *                             @arg message_hash->data_length : Specifies effective data length of the array
 *                                                              (Specify only when Message is selected)
 *                             @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                              (Message: 0 Hash value: 1)
 * @param[in,out] signature    Signature text storage destination information
 *                             @arg signature->pdata       : Specifies pointer to array storing signature text
 *                                                           The signature format is "0 padding (64 bits) || 
 *                                                           signature r (192 bits) || 0 padding (64 bits) || 
 *                                                           signature s (192 bits)".
 *                             @arg signature->data_length : Data length (byte units)
 * @param[in]     wrapped_key  Input wrapped key of secp192r1 private key.
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDSA_secp192r1_SignatureGenerate (sce_ecdsa_byte_data_t         * message_hash,
                                                   sce_ecdsa_byte_data_t         * signature,
                                                   sce_ecc_private_wrapped_key_t * wrapped_key)
{
    uint32_t  indata_cmd;
    uint32_t  curvetype;
    fsp_err_t error_code = FSP_SUCCESS;
    uint32_t  data_buff[SCE_PRV_HASH_WORD_POS_ECDSA_P192 + (HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE / sizeof(uint32_t))] =
    {
        0
    };

    error_code = set_ecdsa_hash_data(message_hash, data_buff, SCE_PRV_HASH_WORD_POS_ECDSA_P192);
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    indata_cmd = change_endian_long(SCE_ECC_KEY_LENGTH_192);
    curvetype  = change_endian_long(SCE_ECC_CURVE_TYPE_NIST);
    error_code = R_SCE_EcdsaSignatureGenerateSub(
        /* Casting uint32_t pointer is used for address. */
        &curvetype,
        &indata_cmd,
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) data_buff,
        (uint32_t *) signature->pdata);
    signature->data_length = HW_SCE_ECDSA_DATA_BYTE_SIZE;

    return error_code;
}

/*******************************************************************************************************************//**
 * When a message is specified in the first argument, message_hash->data_type, a SHA-256 hash of the message text
 * input as the first argument, message_hash->pdata, is calculated, and the signature text is written to the second
 * argument, signature, in accordance with secp224r1 using the private wrapped key input as the third argument,
 * wrapped_key.
 *
 * When a hash value is specified in the first argument, message_hash->data_type, the signature text for the first
 * 28 bytes of the SHA-256 hash value input to the first argument, message_hash->pdata, is written to the second
 * argument, signature, in accordance with secp224r1 using the private wrapped key input as the third argument,
 * wrapped_key.
 *
 * @param[in]     message_hash Message or hash value to which to attach signature
 *                             @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                              hash value
 *                             @arg message_hash->data_length : Specifies effective data length of the array
 *                                                              (Specify only when Message is selected)
 *                             @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                              (Message: 0 Hash value: 1)
 * @param[in,out] signature    Signature text storage destination information
 *                             @arg signature->pdata       : Specifies pointer to array storing signature text
 *                                                           The signature format is "0 padding (32 bits) || 
 *                                                           signature r (224 bits) || 0 padding (32 bits) || 
 *                                                           signature s (224 bits)".
 *                             @arg signature->data_length : Data length (byte units)
 * @param[in]     wrapped_key  Input wrapped key of secp224r1 private key.
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDSA_secp224r1_SignatureGenerate (sce_ecdsa_byte_data_t         * message_hash,
                                                   sce_ecdsa_byte_data_t         * signature,
                                                   sce_ecc_private_wrapped_key_t * wrapped_key)
{
    uint32_t  indata_cmd;
    uint32_t  curvetype;
    fsp_err_t error_code = FSP_SUCCESS;
    uint32_t  data_buff[SCE_PRV_HASH_WORD_POS_ECDSA_P224 + (HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE / sizeof(uint32_t))] =
    {
        0
    };

    error_code = set_ecdsa_hash_data(message_hash, data_buff, SCE_PRV_HASH_WORD_POS_ECDSA_P224);
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    indata_cmd = change_endian_long(SCE_ECC_KEY_LENGTH_224);
    curvetype  = change_endian_long(SCE_ECC_CURVE_TYPE_NIST);
    error_code = R_SCE_EcdsaSignatureGenerateSub(
        /* Casting uint32_t pointer is used for address. */
        &curvetype,
        &indata_cmd,
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) data_buff,
        (uint32_t *) signature->pdata);
    signature->data_length = HW_SCE_ECDSA_DATA_BYTE_SIZE;

    return error_code;
}

/*******************************************************************************************************************//**
 * When a message is specified in the first argument, message_hash->data_type, a SHA-256 hash of the message text
 * input as the first argument, message_hash->pdata, is calculated, and the signature text is written to the second
 * argument, signature, in accordance with secp256r1 using the private wrapped key input as the third argument,
 * wrapped_key.
 *
 * When a hash value is specified in the first argument, message_hash->data_type, the signature text for the first
 * 32 bytes of the SHA-256 hash value input to the first argument, message_hash->pdata, is written to the second
 * argument, signature, in accordance with secp256r1 using the private wrapped key input as the third argument,
 * wrapped_key.
 *
 * @param[in]     message_hash Message or hash value to which to attach signature
 *                             @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                              hash value
 *                             @arg message_hash->data_length : Specifies effective data length of the array
 *                                                              (Specify only when Message is selected)
 *                             @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                              (Message: 0 Hash value: 1)
 * @param[in,out] signature    Signature text storage destination information
 *                             @arg signature->pdata       : Specifies pointer to array storing signature text
 *                                                           The signature format is "signature r (256 bits) ||
 *                                                           signature s (256 bits)".
 *                             @arg signature->data_length : Data length (byte units)
 * @param[in]     wrapped_key  Input wrapped key of secp256r1 private key.
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDSA_secp256r1_SignatureGenerate (sce_ecdsa_byte_data_t         * message_hash,
                                                   sce_ecdsa_byte_data_t         * signature,
                                                   sce_ecc_private_wrapped_key_t * wrapped_key)
{
    uint32_t  indata_cmd;
    uint32_t  curvetype;
    fsp_err_t error_code = FSP_SUCCESS;
    uint32_t  data_buff[SCE_PRV_HASH_WORD_POS_ECDSA_P256 + (HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE / sizeof(uint32_t))] =
    {
        0
    };

    error_code = set_ecdsa_hash_data(message_hash, data_buff, SCE_PRV_HASH_WORD_POS_ECDSA_P256);
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    indata_cmd = change_endian_long(SCE_ECC_KEY_LENGTH_256);
    curvetype  = change_endian_long(SCE_ECC_CURVE_TYPE_NIST);
    error_code = R_SCE_EcdsaSignatureGenerateSub(
        /* Casting uint32_t pointer is used for address. */
        &curvetype,
        &indata_cmd,
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) data_buff,
        (uint32_t *) signature->pdata);
    signature->data_length = HW_SCE_ECDSA_DATA_BYTE_SIZE;

    return error_code;
}

/*******************************************************************************************************************//**
 * When a message is specified in the first argument, message_hash->data_type, a SHA-384 hash of the message text
 * input as the first argument, message_hash->pdata, is calculated, and the signature text is written to the second
 * argument, signature, in accordance with secp384r1 using the private wrapped key input as the third argument,
 * wrapped_key.
 *
 * To use message input, prepare a user-defined function for SHA384.
 *
 * When a hash value is specified in the first argument, message_hash->data_type, the signature text for the first
 * 48 bytes of the SHA-384 hash value input to the first argument, message_hash->pdata, is written to the second
 * argument, signature, in accordance with secp384r1 using the private wrapped key input as the third argument,
 * wrapped_key.
 *
 * @param[in]     message_hash Message or hash value to which to attach signature
 *                             @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                              hash value
 *                             @arg message_hash->data_length : Specifies effective data length of the array
 *                                                              (Specify only when Message is selected)
 *                             @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                              (Message: 0 Hash value: 1)
 * @param[in,out] signature    Signature text storage destination information
 *                             @arg signature->pdata       : Specifies pointer to array storing signature text
 *                                                           The signature format is "signature r (384 bits) ||
 *                                                           signature s (384 bits)".
 *                             @arg signature->data_length : Data length (byte units)
 * @param[in]     wrapped_key  Input wrapped key of secp384r1 private key.
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDSA_secp384r1_SignatureGenerate (sce_ecdsa_byte_data_t         * message_hash,
                                                   sce_ecdsa_byte_data_t         * signature,
                                                   sce_ecc_private_wrapped_key_t * wrapped_key)
{
    uint32_t  curvetype;
    fsp_err_t error_code = FSP_SUCCESS;
    uint32_t  data_buff[(HW_SCE_SHA384_HASH_LENGTH_BYTE_SIZE / sizeof(uint32_t))] =
    {
        0
    };

    error_code = set_ecdsa_hash_data(message_hash, data_buff, SCE_PRV_HASH_WORD_POS_ECDSA_P384);
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    curvetype  = change_endian_long(SCE_ECC_CURVE_TYPE_NIST);
    error_code = R_SCE_EcdsaP384SignatureGenerateSub(
        /* Casting uint32_t pointer is used for address. */
        &curvetype,
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) data_buff,
        (uint32_t *) signature->pdata);
    signature->data_length = HW_SCE_ECDSA_P384_DATA_BYTE_SIZE;

    return error_code;
}

/*******************************************************************************************************************//**
 * When a message is specified in the second argument, message_hash->data_type, a SHA-256 hash of the message text
 * input as the second argument, message_hash->pdata, is calculated, and the signature text input to the first argument,
 * signature, is validated in accordance with secp192r1 using the public wrapped key input as the third argument,
 * wrapped_key.
 *
 * When a hash value is specified in the second argument, message_hash->data_type, the signature text for the first
 * 24 bytes of the SHA-256 hash value input to the second argument, message_hash->pdata, input to the first argument,
 * signature, is validated in accordance with secp192r1 using the public wrapped key input as the third argument,
 * wrapped_key.
 *
 * @param[in]     signature    Signature text information to be verified
 *                             @arg signature->pdata       : Specifies pointer to array storing signature text
 *                                                           The signature format is "0 padding (64 bits) || 
 *                                                           signature r (192 bits) || 0 padding (64 bits) || 
 *                                                           signature s (192 bits)".
 *                             @arg signature->data_length : Specifies the data length (byte units) (nonuse)
 * @param[in,out] message_hash Message or hash value to be verified
 *                             @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                              hash value
 *                             @arg message_hash->data_length : Specifies effective data length of the array
 *                                                              (Specify only when Message is selected)
 *                             @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                              (Message: 0 Hash value: 1)
 * @param[in]     wrapped_key  Input wrapped key of secp192r1 public key.
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred or signature verification failed.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDSA_secp192r1_SignatureVerify (sce_ecdsa_byte_data_t        * signature,
                                                 sce_ecdsa_byte_data_t        * message_hash,
                                                 sce_ecc_public_wrapped_key_t * wrapped_key)
{
    uint32_t  indata_cmd;
    uint32_t  curvetype;
    fsp_err_t error_code = FSP_SUCCESS;
    uint32_t  data_buff[SCE_PRV_HASH_WORD_POS_ECDSA_P192 + (HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE / sizeof(uint32_t))] =
    {
        0
    };

    error_code = set_ecdsa_hash_data(message_hash, data_buff, SCE_PRV_HASH_WORD_POS_ECDSA_P192);
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    indata_cmd = change_endian_long(SCE_ECC_KEY_LENGTH_192);
    curvetype  = change_endian_long(SCE_ECC_CURVE_TYPE_NIST);
    error_code = R_SCE_EcdsaSignatureVerificationSub(
        /* Casting uint32_t pointer is used for address. */
        &curvetype,
        &indata_cmd,
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) data_buff,
        (uint32_t *) signature->pdata);

    return error_code;
}

/*******************************************************************************************************************//**
 * When a message is specified in the second argument, message_hash->data_type, a SHA-256 hash of the message text
 * input as the second argument, message_hash->pdata, is calculated, and the signature text input to the first argument,
 * signature, is validated in accordance with secp224r1 using the public wrapped key input as the third argument,
 * wrapped_key.
 *
 * When a hash value is specified in the second argument, message_hash->data_type, the signature text for the first
 * 28 bytes of the SHA-256 hash value input to the second argument, message_hash->pdata, input to the first argument,
 * signature, is validated in accordance with secp224r1 using the public wrapped key input as the third argument,
 * wrapped_key.
 *
 * @param[in]     signature    Signature text information to be verified
 *                             @arg signature->pdata       : Specifies pointer to array storing signature text
 *                                                           The signature format is "0 padding (32 bits) || 
 *                                                           signature r (224 bits) || 0 padding (32 bits) || 
 *                                                           signature s (224 bits)".
 *                             @arg signature->data_length : Specifies the data length (byte units) (nonuse)
 * @param[in,out] message_hash Message or hash value to be verified
 *                             @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                              hash value
 *                             @arg message_hash->data_length : Specifies effective data length of the array
 *                                                              (Specify only when Message is selected)
 *                             @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                              (Message: 0 Hash value: 1)
 * @param[in]     wrapped_key  Input wrapped key of secp224r1 public key.
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred or signature verification failed.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDSA_secp224r1_SignatureVerify (sce_ecdsa_byte_data_t        * signature,
                                                 sce_ecdsa_byte_data_t        * message_hash,
                                                 sce_ecc_public_wrapped_key_t * wrapped_key)
{
    uint32_t  indata_cmd;
    uint32_t  curvetype;
    fsp_err_t error_code = FSP_SUCCESS;
    uint32_t  data_buff[SCE_PRV_HASH_WORD_POS_ECDSA_P224 + (HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE / sizeof(uint32_t))] =
    {
        0
    };

    error_code = set_ecdsa_hash_data(message_hash, data_buff, SCE_PRV_HASH_WORD_POS_ECDSA_P224);
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    indata_cmd = change_endian_long(SCE_ECC_KEY_LENGTH_224);
    curvetype  = change_endian_long(SCE_ECC_CURVE_TYPE_NIST);
    error_code = R_SCE_EcdsaSignatureVerificationSub(
        /* Casting uint32_t pointer is used for address. */
        &curvetype,
        &indata_cmd,
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) data_buff,
        (uint32_t *) signature->pdata);

    return error_code;
}

/*******************************************************************************************************************//**
 * When a message is specified in the second argument, message_hash->data_type, a SHA-256 hash of the message text
 * input as the second argument, message_hash->pdata, is calculated, and the signature text input to the first argument,
 * signature, is validated in accordance with secp256r1 using the public wrapped key input as the third argument,
 * wrapped_key.
 *
 * When a hash value is specified in the second argument, message_hash->data_type, the signature text for the first
 * 32 bytes of the SHA-256 hash value input to the second argument, message_hash->pdata, input to the first argument,
 * signature, is validated in accordance with secp256r1 using the public wrapped key input as the third argument,
 * wrapped_key.
 *
 * @param[in]     signature    Signature text information to be verified
 *                             @arg signature->pdata       : Specifies pointer to array storing signature text
 *                                                           The signature format is "signature r (256 bits) ||
 *                                                           signature s (256 bits)".
 *                             @arg signature->data_length : Specifies the data length (byte units) (nonuse)
 * @param[in,out] message_hash Message or hash value to be verified
 *                             @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                              hash value
 *                             @arg message_hash->data_length : Specifies effective data length of the array
 *                                                              (Specify only when Message is selected)
 *                             @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                              (Message: 0 Hash value: 1)
 * @param[in]     wrapped_key  Input wrapped key of secp256r1 public key.
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred or signature verification failed.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDSA_secp256r1_SignatureVerify (sce_ecdsa_byte_data_t        * signature,
                                                 sce_ecdsa_byte_data_t        * message_hash,
                                                 sce_ecc_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
    uint32_t  data_buff[SCE_PRV_HASH_WORD_POS_ECDSA_P256 + (HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE / sizeof(uint32_t))] =
    {
        0
    };

    error_code = set_ecdsa_hash_data(message_hash, data_buff, SCE_PRV_HASH_WORD_POS_ECDSA_P256);
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    error_code = R_SCE_EcdsaNistP256SignatureVerificationSub(
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) data_buff,
        (uint32_t *) signature->pdata);

    return error_code;
}

/*******************************************************************************************************************//**
 * When a message is specified in the second argument, message_hash->data_type, a SHA-256 hash of the message text
 * input as the second argument, message_hash->pdata, is calculated, and the signature text input to the first argument,
 * signature, is validated in accordance with secp384r1 using the public wrapped key input as the third argument,
 * wrapped_key.
 *
 * To use message input, prepare a user-defined function for SHA384.
 *
 * When a hash value is specified in the second argument, message_hash->data_type, the signature text for the first
 * 48 bytes of the SHA-256 hash value input to the second argument, message_hash->pdata, input to the first argument,
 * signature, is validated in accordance with secp384r1 using the public wrapped key input as the third argument,
 * wrapped_key.
 *
 * @param[in]     signature    Signature text information to be verified
 *                             @arg signature->pdata       : Specifies pointer to array storing signature text
 *                                                           The signature format is "signature r (384 bits) ||
 *                                                           signature s (384 bits)".
 *                             @arg signature->data_length : Specifies the data length (byte units) (nonuse)
 * @param[in,out] message_hash Message or hash value to be verified
 *                             @arg message_hash->pdata       : Specifies pointer to array storing the message or 
 *                                                              hash value
 *                             @arg message_hash->data_length : Specifies effective data length of the array
 *                                                              (Specify only when Message is selected)
 *                             @arg message_hash->data_type   : Selects the data type of message_hash
 *                                                              (Message: 0 Hash value: 1)
 * @param[in]     wrapped_key  Input wrapped key of secp384r1 public key.
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred or signature verification failed.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input data is invalid.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDSA_secp384r1_SignatureVerify (sce_ecdsa_byte_data_t        * signature,
                                                 sce_ecdsa_byte_data_t        * message_hash,
                                                 sce_ecc_public_wrapped_key_t * wrapped_key)
{
    uint32_t  curvetype;
    fsp_err_t error_code = FSP_SUCCESS;
    uint32_t  data_buff[(HW_SCE_SHA384_HASH_LENGTH_BYTE_SIZE / sizeof(uint32_t))] =
    {
        0
    };

    error_code = set_ecdsa_hash_data(message_hash, data_buff, SCE_PRV_HASH_WORD_POS_ECDSA_P384);
    if (FSP_SUCCESS != error_code)
    {
        return error_code;
    }

    curvetype  = change_endian_long(SCE_ECC_CURVE_TYPE_NIST);
    error_code = R_SCE_EcdsaP384SignatureVerificationSub(
        /* Casting uint32_t pointer is used for address. */
        &curvetype,
        (uint32_t *) &wrapped_key->value,
        (uint32_t *) data_buff,
        (uint32_t *) signature->pdata);

    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_ECDH_secp256r1_Init() function prepares to perform ECDH key exchange computation and writes the result to
 * the first argument, handle. The succeeding functions R_SCE_ECDH_secp256r1_PublicKeySign(),
 * R_SCE_ECDH_secp256r1_PublicKeyVerify(), R_SCE_ECDH_secp256r1_SharedSecretCalculate(),
 * and R_SCE_ECDH_secp256r1_KeyDerivation() use handle as an argument.
 *
 * Use the second argument, key_type, to select the type of ECDH key exchange. When ECDHE is selected,
 * the R_SCE_ECDH_secp256r1_PublicKeySign() function uses the SCE's random number generation functionality to generate
 * an secp256r1 key pair. When ECDH is selected, keys installed beforehand are used for key exchange.
 *
 * Input 1 as the third argument, use_key_id, to use key_id when key exchange is performed. key_id is for applications
 * conforming to the DLMS/COSEM standard for smart meters.
 *
 * @param[in,out] handle     ECDH handler (work area)
 * @param[in]     key_type   Key exchange type (0: ECDHE, 1: ECDH, 2:ECDH(AES-GCM-128 with IV))
 * @param[in]     use_key_id 0: key_id not used, 1: key_id used
 *
 * @retval FSP_SUCCESS                  Normal end
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER Input data is invalid.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDH_secp256r1_Init (sce_ecdh_handle_t * handle, uint32_t key_type, uint32_t use_key_id)
{
    fsp_err_t error_code = FSP_SUCCESS;
    if ((2 >= key_type) && (1 >= use_key_id))
    {
        memset(handle, 0, sizeof(sce_ecdh_handle_t));
        handle->flag_call_init = 1;
        g_private_id_counter++;
        g_ecdh256_private_id    = g_private_id_counter;
        handle->id              = g_ecdh256_private_id;
        handle->key_type        = key_type;
        handle->flag_use_key_id = use_key_id;
    }
    else
    {
        error_code = FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_ECDH_secp256r1_PublicKeySign() function calculates a signature for a public key user wrapped key used for
 * ECDH key exchange.
 *
 * If ECDHE is specified by the key_type argument of the R_SCE_ECDH_secp256r1_Init() function, the SCE's random number
 * generation functionality is used to generate an secp256r1 key pair. The public key is output to public_key
 * and the private key is output to wrapped_key.
 *
 * If ECDH is specified by the key_type argument of the R_SCE_ECDH_secp256r1_Init() function, the public key input
 * as ecc_public_wrapped_key is output to public_key and nothing is output to wrapped_key.
 *
 * The succeeding function R_SCE_ECDH_secp256r1_SharedSecretCalculate() uses the first argument, handle, as an argument.
 * R_SCE_ECDH_secp256r1_SharedSecretCalculate() function uses wrapped_key as input to calculate Z.
 *
 * @param[in,out] handle                  ECDH handler (work area)
 *                                        When using key_id, input handle->key_id after running R_SCE_ECDH_secp256r1_Init().
 * @param[in]     ecc_public_wrapped_key  For ECDHE, input a null pointer.
 *                                        For ECDH, input the wrapped key of a secp256r1 public key.
 * @param[in]     ecc_private_wrapped_key secp256r1 private key for signature generation
 * @param[in,out] public_key              User secp256r1 public key (512-bit) for key exchange.
 *                                        When using key_id,
 *                                        key_id (8-bit) || public key (512-bit) || 0 padding (24-bit)
 * @param[in,out] signature               Signature text storage destination information
 *                                        @arg signature->pdata       : Specifies pointer to array storing signature text.
 *                                                                      The signature format is "signature r (256 bits) ||
 *                                                                      signature s (256 bits)"
 *                                        @arg signature->data_length : Data length (in byte units)
 * @param[in,out] wrapped_key             For ECDHE, a private wrapped key generated from a random number.
 *                                        Not output for ECDH.
 * 
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDH_secp256r1_PublicKeySign (sce_ecdh_handle_t             * handle,
                                              sce_ecc_public_wrapped_key_t  * ecc_public_wrapped_key,
                                              sce_ecc_private_wrapped_key_t * ecc_private_wrapped_key,
                                              uint8_t                       * public_key,
                                              sce_ecdsa_byte_data_t         * signature,
                                              sce_ecc_private_wrapped_key_t * wrapped_key)
{
    uint32_t  indata_cmd    = 0;
    uint32_t  ecdh_key_type = 0;
    uint32_t  key_id        = 0;
    fsp_err_t error_code    = FSP_SUCCESS;

    if ((0 == handle->flag_call_init) || (1 == handle->flag_call_make_public))
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_ecdh256_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->flag_call_make_public = 1;

    if (1 == handle->key_type)
    {
        ecdh_key_type = change_endian_long(1);
    }

    if (1 == handle->flag_use_key_id)
    {
        indata_cmd = change_endian_long(1);
        key_id     = change_endian_long(handle->key_id & SCE_HEX_FF);
    }
    else
    {
        indata_cmd = change_endian_long(0);
    }

    error_code = R_SCE_EcdhMakePublicKeyPrivate(&indata_cmd,
                                                 &ecdh_key_type,
                                       /* Casting uint32_t pointer is used for address. */
                                                 (uint32_t *) &ecc_public_wrapped_key->value,
                                                 (uint32_t *) &ecc_private_wrapped_key->value,
                                                 &key_id,
                                       /* Casting uint32_t pointer is used for address. */
                                                 (uint32_t *) public_key,
                                                 (uint32_t *) signature->pdata,
                                                 (uint32_t *) &wrapped_key->value);
    signature->data_length = HW_SCE_ECDSA_DATA_BYTE_SIZE;
    if (1 != handle->key_type)
    {
        if (FSP_SUCCESS == error_code)
        {
            wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P256_PRIVATE;
        }
        else
        {
            wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
        }
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_ECDH_secp256r1_PublicKeyVerify() function verifies the signature of the secp256r1 public key of the other
 * ECDH key exchange party. If the signature is correct, it outputs the public wrapped key to the fifth argument.
 * The first argument, handle, is used as an argument in the subsequent function
 * R_SCE_ECDH_secp256r1_SharedSecretCalculate().
 * R_SCE_ECDH_secp256r1_SharedSecretCalculate() uses wrapped_key as input to calculate Z.
 *
 * @param[in,out] handle                 ECDH handler (work area)
 * @param[in]     ecc_public_wrapped_key Public wrapped key area for signature verification
 * @param[in]     public_key_data        secp256r1 public key (512-bit). When key_id is used:
 *                                       key_id (8-bit) || public key (512-bit)
 * @param[in]     signature              ECDSA secp256r1 signature of ecc_public_wrapped_key
 * @param[in,out] wrapped_key            wrapped key of ecc_public_wrapped_key
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred or signature verification failed.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDH_secp256r1_PublicKeyVerify (sce_ecdh_handle_t            * handle,
                                                sce_ecc_public_wrapped_key_t * ecc_public_wrapped_key,
                                                uint8_t                      * public_key_data,
                                                sce_ecdsa_byte_data_t        * signature,
                                                sce_ecc_public_wrapped_key_t * wrapped_key)
{
    st_read_public_key_t indata =
    {
        0
    };
    fsp_err_t error_code = FSP_SUCCESS;

    if ((0 == handle->flag_call_init) || (1 == handle->flag_call_read_public))
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_ecdh256_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->flag_call_read_public = 1;

    if (1 == handle->flag_use_key_id)
    {
        indata.cmd = change_endian_long(1);
        memcpy(indata.bytedata, public_key_data, 1 + HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE); /* key_id || QeU copy */
        indata.bytedata[1 + HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE] = SCE_HEX_80;             /* stop bit */
        indata.bytedata[SCE_PRV_INDATA_BYTEDATA_LEN - 2]     = 0x02;
        indata.bytedata[SCE_PRV_INDATA_BYTEDATA_LEN - 1]     = 0x08;                   /* message length is 520bit */
    }
    else
    {
        indata.cmd = change_endian_long(0);
        memcpy(indata.bytedata, public_key_data, HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE); /* QeU copy */
        indata.bytedata[HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE] = SCE_HEX_80;             /* stop bit */
        indata.bytedata[SCE_PRV_INDATA_BYTEDATA_LEN - 2] = 0x02;
        indata.bytedata[SCE_PRV_INDATA_BYTEDATA_LEN - 1] = 0x00;                   /* message length is 512bit */
    }

    error_code = R_SCE_EcdhReadPublicKeyPrivate(&indata.cmd,
                                                                                   /* Casting uint32_t pointer is used for address. */
                                                 (uint32_t *) &ecc_public_wrapped_key->value,
                                                 (uint32_t *) indata.bytedata,
                                                 (uint32_t *) signature->pdata,
                                                 (uint32_t *)
                                                 &wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P256_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_ECDH_secp256r1_PublicKeyReadWithoutSignature() function reads the secp256r1 public key of the other
 * ECDH key exchange party and outputs the public wrapped key to the third argument.
 * The first argument, handle, is used as an argument in the subsequent function
 * R_SCE_ECDH_secp256r1_SharedSecretCalculate().
 * R_SCE_ECDH_secp256r1_SharedSecretCalculate() uses wrapped_key as input to calculate Z.
 * This API does not verify signature of public_key_data, please protect this data by upper layer software.
 *
 * @param[in,out] handle                 ECDH handler (work area)
 * @param[in]     public_key_data        secp256r1 public key (512-bit). When key_id is used:
 *                                       key_id (8-bit) || public key (512-bit)
 * @param[in,out] wrapped_key            wrapped key of public_key_data
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 * @note Please note that this is slightly contrary to the protected mode policy as it omits signature verification.
**********************************************************************************************************************/
fsp_err_t R_SCE_ECDH_secp256r1_PublicKeyReadWithoutSignature(sce_ecdh_handle_t            * handle,
                                                             uint8_t                      * public_key_data,
                                                             sce_ecc_public_wrapped_key_t * wrapped_key)
{
    st_read_public_key_t indata =
    {
        0
    };
    fsp_err_t error_code = FSP_SUCCESS;

    if ((0 == handle->flag_call_init) || (1 == handle->flag_call_read_public))
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }
    if (handle->id != g_ecdh256_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->flag_call_read_public = 1;

    if (1 == handle->flag_use_key_id)
    {
        indata.cmd = change_endian_long(1);
        memcpy(indata.bytedata, public_key_data, 1 + HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE);  /* key_id || QeU copy */
        indata.bytedata[1 + HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE] = SCE_HEX_80;    /* stop bit */
        indata.bytedata[SCE_PRV_INDATA_BYTEDATA_LEN - 2] = 0x02;
        indata.bytedata[SCE_PRV_INDATA_BYTEDATA_LEN - 1] = 0x08;   /* message length is 520bit */
    }
    else
    {
        indata.cmd = change_endian_long(0);
        memcpy(indata.bytedata, public_key_data, HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE);  /* QeU copy */
        indata.bytedata[HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE] = SCE_HEX_80;    /* stop bit */
        indata.bytedata[SCE_PRV_INDATA_BYTEDATA_LEN - 2] = 0x02;
        indata.bytedata[SCE_PRV_INDATA_BYTEDATA_LEN - 1] = 0x00;   /* message length is 512bit */
    }

    error_code = R_SCE_EcdhReadPublicKeyWithoutSignaturePrivate(&indata.cmd,
                                                                                   /* Casting uint32_t pointer is used for address. */
                                                                 (uint32_t*)indata.bytedata,
                                                                 (uint32_t*)&wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P256_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }
    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_ECDH_secp256r1_SharedSecretCalculate() function uses the ECDH key exchange algorithm to output the
 * wrapped key of the shared secret Z derived from the public key of the other key exchange party and your own private
 * key.
 * Input as the second argument, ecc_public_wrapped_key, the public wrapped key whose signature was verified
 * by R_SCE_ECDH_secp256r1_PublicKeyVerify().
 * When key_type of R_SCE_ECDH_secp256r1_Init() is 0, input as the third argument, ecc_private_wrapped_key,
 * the private wrapped key generated from a random number by R_SCE_ECDH_secp256r1_PublicKeySign(), and when key_type is
 * other than 0, input the private wrapped key that forms a pair with the second argument of
 * R_SCE_ECDH_secp256r1_PublicKeySign().
 * The subsequent R_SCE_ECDH_secp256r1_KeyDerivation() function uses shared_secret_wrapped_key as key material
 * for outputting the wrapped key.
 *
 * @param[in,out] handle                    ECDH handler (work area)
 * @param[in]     ecc_public_wrapped_key    Public wrapped key whose signature was verified by
 *                                          R_SCE_ECDH_secp256r1_PublicKeyVerify()
 * @param[in]     ecc_private_wrapped_key   Private wrapped key
 * @param[in,out] shared_secret_wrapped_key Wrapped key of shared secret Z calculated by ECDH key exchange
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDH_secp256r1_SharedSecretCalculate (sce_ecdh_handle_t             * handle,
                                                      sce_ecc_public_wrapped_key_t  * ecc_public_wrapped_key,
                                                      sce_ecc_private_wrapped_key_t * ecc_private_wrapped_key,
                                                      sce_ecdh_wrapped_key_t        * shared_secret_wrapped_key)
{
    uint32_t  ecdh_key_type = 0;
    fsp_err_t error_code    = FSP_SUCCESS;

    if (0 == handle->flag_call_init)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }

    if (handle->id != g_ecdh256_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    handle->flag_call_shared_secret = 1;

    ecdh_key_type = change_endian_long(handle->key_type);

    error_code = R_SCE_EcdhCalculateSharedSecretIndexPrivate(&ecdh_key_type,
                                       /* Casting uint32_t pointer is used for address. */
                                                              (uint32_t *) &ecc_public_wrapped_key->value,
                                                              (uint32_t *) &ecc_private_wrapped_key->value,
                                                              (uint32_t *) &shared_secret_wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        if (3 == handle->key_type)
        {
            shared_secret_wrapped_key->type = SCE_KEY_INDEX_TYPE_AES128_GCM_WITH_IV;
        }
        else
        {
            shared_secret_wrapped_key->type = SCE_KEY_INDEX_TYPE_ECDH_SHARED_SECRET;
        }
    }
    else
    {
        shared_secret_wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * The R_SCE_ECDH_secp256r1_KeyDerivation() function uses the shared secret "Z (shared_secret_index)" calculated
 * by the R_SCE_ECDH_secp256r1_SharedSecretCalculate() function as the key material to derive the wrapped key
 * specified by the third argument, key_type. The key derivation algorithm is one-step key derivation as defined
 * in NIST SP800-56C. Either SHA-256 or SHA-256 HMAC is specified by the fourth argument, kdf_type.
 * When SHA-256 HMAC is specified, the wrapped key output by the R_SCE_SHA256HMAC_EncryptedKeyWrap() function
 * is specified as the seventh argument, salt_wrapped_key.
 * Enter a fixed value for deriving a key shared with the key exchange partner in the fifth argument, other_info.
 * A wrapped key corresponding to key_type is output as the eighth argument, wrapped_key. The correspondences
 * between the types of derived wrapped_key and the functions with which they can be used as listed below.
 *   - AES-128: All AES-128 Init functions
 *   - AES-256: All AES-256 Init functions
 *   - SHA256-HMAC: R_SCE_SHA256HMAC_GenerateInit() function and R_SCE_SHA256HMAC_VerifyInit() function
 *
 * @param[in,out] handle                    ECDH handler (work area)
 * @param[in]     shared_secret_wrapped_key Z wrapped key calculated by R_SCE_ECDH_secp256r1_SharedSecretCalculate
 * @param[in]     key_type                  Derived key type (0: AES-128, 1: AES-256, 2:SHA256-HMAC, 3: AES-GCM-128 with IV)
 * @param[in]     kdf_type                  Algorithm used for key derivation calculation (0: SHA-256, 1:SHA256-HMAC)
 * @param[in]     other_info                Additional data used for key derivation calculation:
 *                                          AlgorithmID || PartyUInfo || PartyVInfo
 * @param[in]     other_info_length         Data length of other_info (up to 147 byte units)
 * @param[in]     salt_wrapped_key          Salt wrapped key (Input NULL when kdf_type is 0.)
 * @param[in,out] wrapped_key               Wrapped key corresponding to key_type.
 *                                          When the value of key_type is 2, an SHA256-HMAC wrapped key is output.
 *                                          wrapped_key can be specified by casting the start address of the area reserved
 *                                          beforehand by the sce_hmac_sha_wrapped_key_t type with the
 *                                          (sce_aes_wrapped_key_t*) type.
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                              by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Invalid wrapped key was input.
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         An invalid handle was input.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECDH_secp256r1_KeyDerivation (sce_ecdh_handle_t          * handle,
                                              sce_ecdh_wrapped_key_t     * shared_secret_wrapped_key,
                                              uint32_t                     key_type,
                                              uint32_t                     kdf_type,
                                              uint8_t                    * other_info,
                                              uint32_t                     other_info_length,
                                              sce_hmac_sha_wrapped_key_t * salt_wrapped_key,
                                              sce_aes_wrapped_key_t      * wrapped_key)
{
    /* InData_PaddedMsg = AlgorithmID || PartyUInfo || PartyVInfo || 1 || 0padding || Message length(64bit)
     * Message length value = AlgorithmID bit length + PartyUInfo bit length + PartyVInfo bit length + 288bit
     * MAX_CNT(word) = 7 + 16n */

    fsp_err_t error_code = FSP_SUCCESS;
    st_key_derivation_t indata =
    {
        0
    };
    uint32_t message_bit_length = 0;

    if (0 == handle->flag_call_shared_secret)
    {
        return FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION;
    }
    handle->flag_call_init = 0;
    handle->flag_call_make_public = 0;
    handle->flag_call_read_public = 0;
    handle->flag_call_shared_secret = 0;
    if (handle->id != g_ecdh256_private_id)
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

     if (3 == key_type)
    {
        if (2 == handle->key_type)
        {
            memcpy(wrapped_key->value, shared_secret_wrapped_key->value, sizeof(wrapped_key->value));
            wrapped_key->type = SCE_KEY_INDEX_TYPE_AES128_GCM_WITH_IV;
        }
        else
        {
            wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
            error_code = FSP_ERR_CRYPTO_SCE_FAIL;
        }
        memset(handle, 0, sizeof(sce_ecdh_handle_t));
        return error_code;
    }

    /* 147 = SCE_PRV_OTHER_INFO_BYTE_LEN_3B - 9 */
    if (((2 < key_type) || (1 < kdf_type)) || ((SCE_PRV_OTHER_INFO_BYTE_LEN_3B - 9) < other_info_length))
    {
        return FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    message_bit_length = (other_info_length * 8) + SCE_PRV_OTHER_INFO_BYTE_LEN_SUPP;
    if (0 != kdf_type)
    {
        message_bit_length += (SCE_DEC_64 * 8);
    }

    memcpy(indata.paddedmsg, other_info, other_info_length);
    indata.paddedmsg[other_info_length] = SCE_HEX_80; /* stop bit */

    if ((SCE_PRV_OTHER_INFO_BYTE_LEN_2B - 9) >= other_info_length)
    {
        /* another block unnecessary */
        /* Casting uint32_t data to uint8_t data array. */
        indata.paddedmsg[SCE_PRV_OTHER_INFO_BYTE_LEN_2B - 4] = (uint8_t)((message_bit_length >> 24) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        indata.paddedmsg[SCE_PRV_OTHER_INFO_BYTE_LEN_2B - 3] = (uint8_t)((message_bit_length >> 16) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        indata.paddedmsg[SCE_PRV_OTHER_INFO_BYTE_LEN_2B - 2] = (uint8_t)((message_bit_length >> 8) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        indata.paddedmsg[SCE_PRV_OTHER_INFO_BYTE_LEN_2B - 1] = (uint8_t)((message_bit_length) & SCE_HEX_FF);
        indata.max_cnt_byte = SCE_PRV_OTHER_INFO_BYTE_LEN_2B;
    }
    else
    {
        /* Casting uint32_t data to uint8_t data array. */
        indata.paddedmsg[SCE_PRV_OTHER_INFO_BYTE_LEN_3B - 4] = (uint8_t)((message_bit_length >> 24) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        indata.paddedmsg[SCE_PRV_OTHER_INFO_BYTE_LEN_3B - 3] = (uint8_t)((message_bit_length >> 16) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        indata.paddedmsg[SCE_PRV_OTHER_INFO_BYTE_LEN_3B - 2] = (uint8_t)((message_bit_length >> 8) & SCE_HEX_FF);

        /* Casting uint32_t data to uint8_t data array. */
        indata.paddedmsg[SCE_PRV_OTHER_INFO_BYTE_LEN_3B - 1] = (uint8_t)((message_bit_length) & SCE_HEX_FF);
        indata.max_cnt_byte = SCE_PRV_OTHER_INFO_BYTE_LEN_3B;
    }

    indata.keyindextype = change_endian_long(key_type);
    indata.kdftype      = change_endian_long(kdf_type);

    error_code = R_SCE_EcdhKeyDerivationPrivate(&indata.keyindextype, shared_secret_wrapped_key->value, &indata.kdftype,
            /* Casting uint32_t pointer is used for address. */
            (uint32_t*)indata.paddedmsg, indata.max_cnt_byte >> 2, salt_wrapped_key->value, wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = s_key_index_type[key_type];
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    memset(handle, 0, sizeof(sce_ecdh_handle_t));

    return error_code;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCE_PROTECTED)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * For messages, SHA hash operation is performed and the hash value is set according to ECDSA.
 *
 * @param p_message_hash message or hash value information
 * @param data_buff      pointer to the hash value area, including 0 padding
 * @param hash_word_pos  hash value output word position from the beginning of the data_buff
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_PARAMETER         Input parameter illegal
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION An invalid function was called.
 **********************************************************************************************************************/
static fsp_err_t set_ecdsa_hash_data (sce_ecdsa_byte_data_t * p_message_hash,
                                      uint32_t              * data_buff,
                                      uint32_t                hash_word_pos)
{
    fsp_err_t            error_code    = FSP_SUCCESS;
    sce_sha_md5_handle_t ex_sha_handle =
    {
        0
    };
    uint32_t hash_length = 0;

    if (0 == p_message_hash->data_type)
    {
        if (SCE_PRV_HASH_WORD_POS_ECDSA_P384 != hash_word_pos)
        {
            R_SCE_SHA256_Init(&ex_sha_handle);
            error_code = R_SCE_SHA256_Update(&ex_sha_handle, p_message_hash->pdata, p_message_hash->data_length);
            if (FSP_SUCCESS == error_code)
            {
                /* Casting uint8_t pointer is used for address. */
                error_code = R_SCE_SHA256_Final(&ex_sha_handle, (uint8_t *) &data_buff[hash_word_pos], &hash_length);
            }
        }
        else
        {
#if SCE_USER_SHA_384_ENABLED != 0

            /* Casting uint8_t pointer is used for address. */
            if (0 !=
                SCE_USER_SHA_384_FUNCTION(p_message_hash->pdata, (uint8_t *) data_buff, p_message_hash->data_length))
#else
#endif                                 /* SCE_USER_SHA_384_ENABLED != 0 */
            {
                error_code = FSP_ERR_CRYPTO_SCE_FAIL;
            }
        }
    }
    else if (1 == p_message_hash->data_type)
    {
        if (SCE_PRV_HASH_WORD_POS_ECDSA_P384 != hash_word_pos)
        {
            memcpy(&data_buff[hash_word_pos],
                   p_message_hash->pdata,
                   HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE - hash_word_pos * sizeof(uint32_t));
        }
        else
        {
            memcpy(data_buff, p_message_hash->pdata, HW_SCE_SHA384_HASH_LENGTH_BYTE_SIZE);
        }
    }
    else
    {
        error_code = FSP_ERR_CRYPTO_SCE_PARAMETER;
    }

    return error_code;
}
