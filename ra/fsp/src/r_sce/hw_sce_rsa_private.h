/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef HW_SCE_RSA_PRIVATE_H
#define HW_SCE_RSA_PRIVATE_H

/**********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include "bsp_api.h"
#include "hw_sce_common.h"

typedef fsp_err_t (* hw_sce_rsa_generatekey_t)(uint32_t num_tries, uint32_t * OutData_KeyIndex, uint32_t * OutData_N,
                                               uint32_t * OutData_DomainParam);

typedef fsp_err_t (* hw_sce_rsa_private_decrypt_t)(const uint32_t * InData_Text, const uint32_t * InData_KeyIndex,
                                                   const uint32_t * InData_N, uint32_t * OutData_Text);

typedef fsp_err_t (* hw_sce_rsa_public_encrypt_t)(const uint32_t * InData_Text, const uint32_t * InData_PublicKey,
                                                  const uint32_t * InData_N, uint32_t * OutData_Text);

fsp_err_t HW_SCE_RSA_4096PublicKeyEncrypt(const uint32_t * InData_Text,
                                          const uint32_t * InData_PublicKey,
                                          const uint32_t * InData_N,
                                          uint32_t       * OutData_Text);

fsp_err_t HW_SCE_RSA_3072PublicKeyEncrypt(const uint32_t * InData_Text,
                                          const uint32_t * InData_PublicKey,
                                          const uint32_t * InData_N,
                                          uint32_t       * OutData_Text);

fsp_err_t HW_SCE_RSA_2048PublicKeyEncrypt(const uint32_t * InData_Text,
                                          const uint32_t * InData_PublicKey,
                                          const uint32_t * InData_N,
                                          uint32_t       * OutData_Text);

fsp_err_t HW_SCE_RSA_2048PrivateKeyDecrypt(const uint32_t * InData_Text,
                                           const uint32_t * InData_PrivateKey,
                                           const uint32_t * InData_N,
                                           uint32_t       * OutData_Text);

fsp_err_t HW_SCE_RSA_2048KeyGenerate(uint32_t   num_tries,
                                     uint32_t * OutData_PrivateKey,
                                     uint32_t * OutData_N,
                                     uint32_t * OutData_DomainParam);

fsp_err_t HW_SCE_HRK_RSA_2048PrivateKeyDecrypt(const uint32_t * InData_Text,
                                               const uint32_t * InData_KeyIndex,
                                               const uint32_t * InData_N,
                                               uint32_t       * OutData_Text);

fsp_err_t HW_SCE_RSA_1024PublicKeyEncrypt(const uint32_t * InData_Text,
                                          const uint32_t * InData_PublicKey,
                                          const uint32_t * InData_N,
                                          uint32_t       * OutData_Text);

fsp_err_t HW_SCE_RSA_1024PrivateKeyDecrypt(const uint32_t * InData_Text,
                                           const uint32_t * InData_PrivateKey,
                                           const uint32_t * InData_N,
                                           uint32_t       * OutData_Text);

fsp_err_t HW_SCE_RSA_1024KeyGenerate(uint32_t   num_tries,
                                     uint32_t * OutData_PrivateKey,
                                     uint32_t * OutData_N,
                                     uint32_t * OutData_DomainParam);

fsp_err_t HW_SCE_HRK_RSA_1024PrivateKeyDecrypt(const uint32_t * InData_Text,
                                               const uint32_t * InData_KeyIndex,
                                               const uint32_t * InData_N,
                                               uint32_t       * OutData_Text);

#endif                                 /* HW_SCE_RSA_PRIVATE_H */
