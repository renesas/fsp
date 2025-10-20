/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef SW_AES_API_H
#define SW_AES_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_ble_abs_gtl_storage.h"
#ifdef CRYPTO_ENABLED
 #include <stdint.h>
 #include <string.h>
 #include <stdbool.h>
 #include "r_ble_api.h"
 #include "tinycrypt/aes.h"
 #include "tinycrypt/cbc_mode.h"
 #include "tinycrypt/constants.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #define USER_KEY_LEN      16
 #define AES_BLOCK_SIZE    16

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/// AES key size modes (only 128 supported)
typedef enum
{
    AES_MODE_128_ = 128
} AAES_MODE_KEY_SIZE;

/***********************************************************************************************************************
 * Public Function Prototypes
 ***********************************************************************************************************************/
typedef void      (* keyset_func_t)(const uint8_t * userkey, const uint8_t * ivkey, AAES_MODE_KEY_SIZE mode);
typedef fsp_err_t (* encrypt_func_t)(uint8_t * out_buf, unsigned int out_size, const uint8_t * in_buf,
                                     unsigned int in_size, const uint8_t * usrkey, const uint8_t * iv);
typedef fsp_err_t (* decrypt_func_t)(uint8_t * out_buf, unsigned int out_size, const uint8_t * in_buf,
                                     unsigned int in_size, const uint8_t * usrkey);
typedef void (* aes_done_cb_t)(uint8_t status);

typedef struct
{
    uint8_t user_key[USER_KEY_LEN];
    uint8_t iv_key[AES_BLOCK_SIZE];

    keyset_func_t  keyset_func;
    encrypt_func_t encrypt_func;
    decrypt_func_t decrypt_func;
    aes_done_cb_t  aes_done_cb;
} crypto_env_t;

/* Global AES environment */
extern crypto_env_t rm_ble_abs_gtl_aes_env;

/* Initialization */
void rm_ble_abs_gtl_aes_init(keyset_func_t keyset_func, encrypt_func_t encrypt_func, decrypt_func_t decrypt_func);

/* Default implementations */
void      def_key_set_func(const uint8_t * userkey, const uint8_t * ivkey, AAES_MODE_KEY_SIZE mode);
fsp_err_t def_encrypt(uint8_t       * out_buf,
                      unsigned int    out_size,
                      const uint8_t * in_buf,
                      unsigned int    in_size,
                      const uint8_t * usrkey,
                      const uint8_t * iv);
fsp_err_t def_decrypt(uint8_t       * out_buf,
                      unsigned int    out_size,
                      const uint8_t * in_buf,
                      unsigned int    in_size,
                      const uint8_t * usrkey);

#endif                                 // CRYPTO_ENABLED
#endif
