/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

#include "bsp_api.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

#ifndef R_SCE_IF_HEADER_FILE
 #define R_SCE_IF_HEADER_FILE

 #define HW_SCE_AES128XTS_KEY_BIT_SIZE    (256U)
 #define HW_SCE_AES256XTS_KEY_BIT_SIZE    (512U)

/* OEM Command */
typedef enum e_sce_oem_cmd
{
    SCE_OEM_CMD_AES128 = 5,
    SCE_OEM_CMD_AES192,
    SCE_OEM_CMD_AES256,
    SCE_OEM_CMD_AES128_XTS,
    SCE_OEM_CMD_AES256_XTS,
    SCE_OEM_CMD_RSA1024_PUBLIC,
    SCE_OEM_CMD_RSA1024_PRIVATE,
    SCE_OEM_CMD_RSA2048_PUBLIC,
    SCE_OEM_CMD_RSA2048_PRIVATE,
    SCE_OEM_CMD_RSA3072_PUBLIC,
    SCE_OEM_CMD_RSA3072_PRIVATE,
    SCE_OEM_CMD_RSA4096_PUBLIC,
    SCE_OEM_CMD_RSA4096_PRIVATE,
    SCE_OEM_CMD_ECC_P192_PUBLIC,
    SCE_OEM_CMD_ECC_P192_PRIVATE,
    SCE_OEM_CMD_ECC_P224_PUBLIC,
    SCE_OEM_CMD_ECC_P224_PRIVATE,
    SCE_OEM_CMD_ECC_P256_PUBLIC,
    SCE_OEM_CMD_ECC_P256_PRIVATE,
    SCE_OEM_CMD_ECC_P384_PUBLIC,
    SCE_OEM_CMD_ECC_P384_PRIVATE,
    SCE_OEM_CMD_HMAC_SHA224,
    SCE_OEM_CMD_HMAC_SHA256,
    SCE_OEM_CMD_ECC_P256R1_PUBLIC,
    SCE_OEM_CMD_ECC_P256R1_PRIVATE,
    SCE_OEM_CMD_ECC_P384R1_PUBLIC,
    SCE_OEM_CMD_ECC_P384R1_PRIVATE,
    SCE_OEM_CMD_ECC_P512R1_PUBLIC,
    SCE_OEM_CMD_ECC_P512R1_PRIVATE,
    SCE_OEM_CMD_ECC_SECP256K1_PUBLIC,
    SCE_OEM_CMD_ECC_SECP256K1_PRIVATE,
    SCE_OEM_CMD_NUM
} sce_oem_cmd_t;

typedef enum e_sce_oem_key_type
{
    SCE_OEM_KEY_TYPE_ENCRYPTED = 0,
    SCE_OEM_KEY_TYPE_PLAIN     = 1
} sce_oem_key_type_t;

#endif                                 /* R_SCE_IF_HEADER_FILE */
