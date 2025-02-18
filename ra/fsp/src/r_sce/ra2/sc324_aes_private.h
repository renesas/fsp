/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef SC324_AES_PRIVATE_H
#define SC324_AES_PRIVATE_H

#include <stdint.h>
#include "bsp_api.h"

typedef enum e_hw_sc324_aes_modes
{
    SC324_AES_ECB = 0,
    SC324_AES_CBC = 1,
    SC324_AES_CTR = 2,
} hw_sc324_aes_modes_t;

typedef enum e_hw_sc324_aes_keysize
{
    SC324_AES_KEYSIZE_128 = 0,
    SC324_AES_KEYSIZE_256 = 1
} hw_sc324_aes_keysizes_t;

typedef enum e_hw_sc324_aes_encrypt_flag
{
    SC324_AES_ENCRYPT = 0,
    SC324_AES_DECRYPT = 1
} hw_sc324_aes_encrypt_flag_t;

typedef struct st_hw_sc324_aes_cfg
{
    hw_sc324_aes_keysizes_t keysize;
    hw_sc324_aes_modes_t    mode;
} hw_sc324_aes_cfg_t;

typedef struct st_hw_sc324_aes_ctrl
{
    hw_sc324_aes_keysizes_t     keysize;
    hw_sc324_aes_modes_t        mode;
    hw_sc324_aes_encrypt_flag_t encrypt_flag;
} hw_sc324_aes_ctrl_t;

fsp_err_t hw_sc324_aes_kernel_process_data(hw_sc324_aes_ctrl_t * p_ctrl,
                                           const uint32_t      * InData_Key,
                                           const uint32_t      * InData_IV,
                                           const uint32_t        num_words,
                                           const uint32_t      * InData_Text,
                                           uint32_t            * OutData_Text,
                                           uint32_t            * OutData_IV);

#endif                                 /* SC324_AES_PRIVATE_H */
