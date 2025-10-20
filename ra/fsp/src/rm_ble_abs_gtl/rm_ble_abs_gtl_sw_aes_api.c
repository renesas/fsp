/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include "rm_ble_abs_gtl_sw_aes_api.h"
#ifdef CRYPTO_ENABLED

/* Default IV */
static const uint8_t def_iv[AES_BLOCK_SIZE] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
crypto_env_t rm_ble_abs_gtl_aes_env;

/***********************************************************************************************************************
 * @brief Initialize the AES environment with user-supplied or default function pointers.
 * @param[in] keyset_func   Function pointer for key setup (can be NULL for default).
 * @param[in] encrypt_func  Function pointer for encryption (can be NULL for default).
 * @param[in] decrypt_func  Function pointer for decryption (can be NULL for default).
 **********************************************************************************************************************/

void rm_ble_abs_gtl_aes_init (keyset_func_t keyset_func, encrypt_func_t encrypt_func, decrypt_func_t decrypt_func)
{
    memset(&rm_ble_abs_gtl_aes_env, 0, sizeof(crypto_env_t));
    rm_ble_abs_gtl_aes_env.keyset_func  = keyset_func ? keyset_func : def_key_set_func;
    rm_ble_abs_gtl_aes_env.encrypt_func = encrypt_func ? encrypt_func : def_encrypt;
    rm_ble_abs_gtl_aes_env.decrypt_func = decrypt_func ? decrypt_func : def_decrypt;
}

/***********************************************************************************************************************
 * @brief Default key setup function for AES-128 CBC.
 * Copies the user key and IV into the global AES environment. If IV is not provided, uses the default IV.
 * @param[in] userkey   Pointer to the AES key (16 bytes).
 * @param[in] ivkey     Pointer to the IV (16 bytes), or NULL for default IV.
 * @param[in] mode      AES key size mode (only 128-bit supported).
 **********************************************************************************************************************/
void def_key_set_func (const uint8_t * userkey, const uint8_t * ivkey, AAES_MODE_KEY_SIZE mode)
{
    memcpy(rm_ble_abs_gtl_aes_env.user_key, userkey, USER_KEY_LEN);
    if (ivkey)
    {
        memcpy(rm_ble_abs_gtl_aes_env.iv_key, ivkey, AES_BLOCK_SIZE);
    }
    else
    {
        memcpy(rm_ble_abs_gtl_aes_env.iv_key, def_iv, AES_BLOCK_SIZE);
    }

    (void) mode;                       // only AES-128 supported
}

/***********************************************************************************************************************
 * @brief Encrypts input data using AES-128 CBC mode and prepends IV to output.
 * @param[out] out_buf   Output buffer for encrypted data (must have space for IV + ciphertext).
 * @param[in]  out_size  Size of the output buffer in bytes.
 * @param[in]  in_buf    Input buffer containing plaintext.
 * @param[in]  in_size   Size of the input buffer in bytes (must be multiple of AES block size).
 * @param[in]  usrkey    Pointer to the AES key (16 bytes).
 * @param[in]  iv        Pointer to the IV (16 bytes), or NULL to use environment IV.
 **********************************************************************************************************************/
fsp_err_t def_encrypt (uint8_t       * out_buf,
                       unsigned int    out_size,
                       const uint8_t * in_buf,
                       unsigned int    in_size,
                       const uint8_t * usrkey,
                       const uint8_t * iv)
{
    uint8_t result = 0;

    struct tc_aes_key_sched_struct key_sched;
    uint8_t local_iv[AES_BLOCK_SIZE];

    memcpy(local_iv, iv ? iv : rm_ble_abs_gtl_aes_env.iv_key, AES_BLOCK_SIZE);

    if (tc_aes128_set_encrypt_key(&key_sched, usrkey) != TC_CRYPTO_SUCCESS)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    result = (uint8_t) tc_cbc_mode_encrypt(out_buf, out_size, in_buf, in_size, local_iv, &key_sched);
    if (result != TC_CRYPTO_SUCCESS)
    {
        result = FSP_ERR_INVALID_ARGUMENT;
    }
    else
    {
        result = FSP_SUCCESS;
    }

    return (fsp_err_t) result;
}

/***********************************************************************************************************************
 * @brief Decrypts input data using AES-128 CBC mode, reading IV from first 16 bytes of input.
 * @param[out] out_buf   Output buffer for decrypted data.
 * @param[in]  out_size  Size of the output buffer in bytes.
 * @param[in]  in_buf    Input buffer containing IV + ciphertext.
 * @param[in]  in_size   Size of the input buffer in bytes (must be at least one block).
 * @param[in]  usrkey    Pointer to the AES key (16 bytes).
 **********************************************************************************************************************/
fsp_err_t def_decrypt (uint8_t       * out_buf,
                       unsigned int    out_size,
                       const uint8_t * in_buf,
                       unsigned int    in_size,
                       const uint8_t * usrkey)
{
    (void) out_size;                   // not used, kept for API consistency
    uint8_t result = 0;

    struct tc_aes_key_sched_struct key_sched;

    if (tc_aes128_set_decrypt_key(&key_sched, usrkey) != TC_CRYPTO_SUCCESS)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    result = (uint8_t) tc_cbc_mode_decrypt(out_buf,
                                           in_size - AES_BLOCK_SIZE,
                                           in_buf + AES_BLOCK_SIZE,
                                           in_size - AES_BLOCK_SIZE,
                                           in_buf,
                                           &key_sched);
    if (result != TC_CRYPTO_SUCCESS)
    {
        result = FSP_ERR_INVALID_ARGUMENT;
    }
    else
    {
        result = FSP_SUCCESS;
    }

    return (fsp_err_t) result;
}

#endif                                 // CRYPTO_ENABLED
