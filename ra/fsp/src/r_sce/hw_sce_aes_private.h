/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef HW_SCE_AES_PRIVATE_H
#define HW_SCE_AES_PRIVATE_H

#include <stdint.h>
#include "bsp_api.h"

/* AES key lengths defined for SCE operations. */
#define SIZE_AES_128BIT_KEYLEN_BITS                      (128)
#define SIZE_AES_128BIT_KEYLEN_BYTES                     ((SIZE_AES_128BIT_KEYLEN_BITS) / 8)
#define SIZE_AES_128BIT_KEYLEN_WORDS                     ((SIZE_AES_128BIT_KEYLEN_BITS) / 32)

#define SIZE_AES_192BIT_KEYLEN_BITS                      (192)
#define SIZE_AES_192BIT_KEYLEN_BYTES                     ((SIZE_AES_192BIT_KEYLEN_BITS) / 8)
#define SIZE_AES_192BIT_KEYLEN_WORDS                     ((SIZE_AES_192BIT_KEYLEN_BITS) / 32)

#define SIZE_AES_256BIT_KEYLEN_BITS                      (256)
#define SIZE_AES_256BIT_KEYLEN_BYTES                     ((SIZE_AES_256BIT_KEYLEN_BITS) / 8)
#define SIZE_AES_256BIT_KEYLEN_WORDS                     ((SIZE_AES_256BIT_KEYLEN_BITS) / 32)

#define SIZE_AES_BLOCK_BITS                              (128U)
#define SIZE_AES_BLOCK_BYTES                             ((SIZE_AES_BLOCK_BITS) / 8)
#define SIZE_AES_BLOCK_WORDS                             ((SIZE_AES_BLOCK_BITS) / 32)

#define SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION               (0x00000000U)
#define SCE_AES_IN_DATA_CMD_ECB_DECRYPTION               (0x00000001U)
#define SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION               (0x00000002U)
#define SCE_AES_IN_DATA_CMD_CBC_DECRYPTION               (0x00000003U)
#define SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION    (0x00000004U)

typedef struct st_sce_data
{
    uint32_t   length;
    uint32_t * p_data;
} r_sce_data_t;

typedef fsp_err_t (* hw_sce_cmac_init_t)(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
typedef void      (* hw_sce_cmac_update_t)(const uint32_t InData_Text[], const uint32_t MAX_CNT);
typedef fsp_err_t (* hw_sce_cmac_final_t)(const uint32_t InData_Cmd[], const uint32_t InData_Text[],
                                          const uint32_t InData_DataT[], const uint32_t InData_DataTLen[],
                                          uint32_t OutData_DataT[]);

typedef fsp_err_t (* hw_sce_aes_gcm_crypt_init_t)(uint32_t * InData_KeyType, uint32_t * InData_DataType,
                                                  uint32_t * InData_Cmd, uint32_t * InData_KeyIndex,
                                                  uint32_t * InData_IV, uint32_t * InData_SeqNum);
typedef void (* hw_sce_aes_gcm_update_aad_t)(const uint32_t * InData_DataA, const uint32_t MAX_CNT);
typedef void (* hw_sce_aes_gcm_crypt_update_transition_t)(void);
typedef void (* hw_sce_aes_gcm_crypt_update_t)(const uint32_t * InData_Text, uint32_t * OutData_Text,
                                               const uint32_t MAX_CNT);
typedef fsp_err_t (* hw_sce_aes_gcm_encrypt_final_t)(const uint32_t * InData_Text, const uint32_t * InData_TextLen,
                                                     const uint32_t * InData_DataALen, uint32_t * OutData_Text,
                                                     uint32_t * OutData_DataT);
typedef fsp_err_t (* hw_sce_aes_gcm_decrypt_final_t)(const uint32_t * InData_Text, const uint32_t * InData_TextLen,
                                                     const uint32_t * InData_DataALen, const uint32_t * InData_DataT,
                                                     const uint32_t * InData_DataTLen,
                                                     uint32_t * OutData_Text);
typedef fsp_err_t (* hw_sce_aes_ccm_encrypt_init_t)(uint32_t * InData_KeyType, uint32_t * InData_DataType,
                                                    uint32_t * InData_Cmd, uint32_t * InData_TextLen,
                                                    uint32_t * InData_KeyIndex, uint32_t * InData_IV,
                                                    uint32_t * InData_Header, uint32_t * InData_SeqNum,
                                                    uint32_t Header_Len);
typedef fsp_err_t (* hw_sce_aes_ccm_decrypt_init_t)(uint32_t * InData_KeyType, uint32_t * InData_DataType,
                                                    uint32_t * InData_Cmd, uint32_t * InData_TextLen,
                                                    uint32_t * InData_MACLength, uint32_t * InData_KeyIndex,
                                                    uint32_t * InData_IV, uint32_t * InData_Header,
                                                    uint32_t * InData_SeqNum, uint32_t Header_Len);

typedef void (* hw_sce_aes_ccm_crypt_update_t)(const uint32_t * InData_Text, uint32_t * OutData_Text,
                                               const uint32_t MAX_CNT);
typedef fsp_err_t (* hw_sce_aes_ccm_encrypt_final_t)(const uint32_t * InData_Text, const uint32_t * InData_TextLen,
                                                     uint32_t * OutData_Text, uint32_t * OutData_MAC);
typedef fsp_err_t (* hw_sce_aes_ccm_decrypt_final_t)(const uint32_t * InData_Text, const uint32_t * InData_TextLen,
                                                     const uint32_t * InData_MAC, const uint32_t * InData_MACLength,
                                                     uint32_t * OutData_Text);
typedef fsp_err_t (* hw_sce_aes_ecb_encrypt_using_encrypted_key)(const uint32_t * InData_KeyIndex,
                                                                 const uint32_t num_words, const uint32_t * InData_Text,
                                                                 uint32_t * OutData_Text);

extern fsp_err_t HW_SCE_AES_128EcbEncrypt(const uint32_t * InData_Key,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_128EcbDecrypt(const uint32_t * InData_Key,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_128CbcEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_128CbcDecrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_128CtrEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_128XtsEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t * InData_Len,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_128XtsDecrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t * InData_Len,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_192EcbEncrypt(const uint32_t * InData_Key,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_192EcbDecrypt(const uint32_t * InData_Key,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_192CbcEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_192CbcDecrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_192CtrEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256EcbEncrypt(const uint32_t * InData_Key,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_256EcbDecrypt(const uint32_t * InData_Key,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_256CbcEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256CbcDecrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256CtrEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256XtsEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t * InData_Len,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256XtsDecrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t * InData_Len,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_GenerateAes128RandomKeyIndexSub(uint32_t * OutData_KeyIndex);
extern fsp_err_t HW_SCE_AES_128CreateEncryptedKey(uint32_t * OutData_KeyIndex);

extern fsp_err_t HW_SCE_AES_128EcbEncryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_128EcbDecryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_128CbcEncryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t * InData_IV,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text,
                                                           uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_128CbcDecryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t * InData_IV,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text,
                                                           uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_128CtrEncryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t * InData_IV,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text,
                                                           uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_GenerateAes192RandomKeyIndexSub(uint32_t * OutData_KeyIndex);
extern fsp_err_t HW_SCE_AES_192CreateEncryptedKey(uint32_t * OutData_KeyIndex);

extern fsp_err_t HW_SCE_AES_192EcbEncryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_192EcbDecryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_192CbcEncryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t * InData_IV,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text,
                                                           uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_192CbcDecryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t * InData_IV,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text,
                                                           uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_192CtrEncryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t * InData_IV,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text,
                                                           uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_GenerateAes256RandomKeyIndexSub(uint32_t * OutData_KeyIndex);
extern fsp_err_t HW_SCE_AES_256CreateEncryptedKey(uint32_t * OutData_KeyIndex);

extern fsp_err_t HW_SCE_AES_256EcbEncryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_256EcbDecryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_256CbcEncryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t * InData_IV,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text,
                                                           uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256CbcDecryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t * InData_IV,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text,
                                                           uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256CtrEncryptUsingEncryptedKey(const uint32_t * InData_KeyIndex,
                                                           const uint32_t * InData_IV,
                                                           const uint32_t   num_words,
                                                           const uint32_t * InData_Text,
                                                           uint32_t       * OutData_Text,
                                                           uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_Aes128EncryptDecryptInit(const uint32_t * InData_Cmd,
                                                 const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_IV);

extern void HW_SCE_Aes128EncryptDecryptUpdate(const uint32_t * InData_Text,
                                              uint32_t       * OutData_Text,
                                              const uint32_t   num_words);

extern fsp_err_t HW_SCE_Aes128EncryptDecryptFinal(void);

extern fsp_err_t HW_SCE_Aes192EncryptDecryptInit(const uint32_t * InData_Cmd,
                                                 const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_IV);

extern void HW_SCE_Aes192EncryptDecryptUpdate(const uint32_t * InData_Text,
                                              uint32_t       * OutData_Text,
                                              const uint32_t   num_words);

extern fsp_err_t HW_SCE_Aes192EncryptDecryptFinal(void);

extern fsp_err_t HW_SCE_Aes256EncryptDecryptInit(const uint32_t * InData_Cmd,
                                                 const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_IV);

extern void HW_SCE_Aes256EncryptDecryptUpdate(const uint32_t * InData_Text,
                                              uint32_t       * OutData_Text,
                                              const uint32_t   num_words);

extern fsp_err_t HW_SCE_Aes256EncryptDecryptFinal(void);

fsp_err_t HW_SCE_Aes128EcbEncryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes128EcbDecryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes192EcbEncryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes192EcbDecryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes256EcbEncryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes256EcbDecryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes128CbcEncryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes128CbcDecryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes192CbcEncryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes192CbcDecryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes256CbcEncryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes256CbcDecryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes128CtrEncryptDecryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes192CtrEncryptDecryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes256CtrEncryptDecryptInitSubGeneral(uint32_t * InData_KeyIndex, uint32_t * InData_IV);

void HW_SCE_Aes128EncryptDecryptUpdateSub(const uint32_t * InData_Text, uint32_t * OutData_Text,
                                          const uint32_t MAX_CNT);

fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub(void);

#endif                                 /* HW_SCE_AES_PRIVATE_H */
