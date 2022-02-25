/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef HW_SCE_AES_PRIVATE_H
#define HW_SCE_AES_PRIVATE_H

#include <stdint.h>
#include "bsp_api.h"

/* AES key lengths defined for SCE operations. */
#define SIZE_AES_128BIT_KEYLEN_BITS             (128)
#define SIZE_AES_128BIT_KEYLEN_BYTES            ((SIZE_AES_128BIT_KEYLEN_BITS) / 8)
#define SIZE_AES_128BIT_KEYLEN_WORDS            ((SIZE_AES_128BIT_KEYLEN_BITS) / 32)

#define SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED     (288)
#define SIZE_AES_128BIT_KEYLEN_BYTES_WRAPPED    ((SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_128BIT_KEYLEN_WORDS_WRAPPED    ((SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED) / 32)

#define SIZE_AES_192BIT_KEYLEN_BITS             (192)
#define SIZE_AES_192BIT_KEYLEN_BYTES            ((SIZE_AES_192BIT_KEYLEN_BITS) / 8)
#define SIZE_AES_192BIT_KEYLEN_WORDS            ((SIZE_AES_192BIT_KEYLEN_BITS) / 32)

#define SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED     (448) /* Added 32 bits here to differentiate 192 wrapped key from 256 wrapped key in the psa_crypto stack. */
#define SIZE_AES_192BIT_KEYLEN_BYTES_WRAPPED    ((SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_192BIT_KEYLEN_WORDS_WRAPPED    ((SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED) / 32)

#define SIZE_AES_256BIT_KEYLEN_BITS             (256)
#define SIZE_AES_256BIT_KEYLEN_BYTES            ((SIZE_AES_256BIT_KEYLEN_BITS) / 8)
#define SIZE_AES_256BIT_KEYLEN_WORDS            ((SIZE_AES_256BIT_KEYLEN_BITS) / 32)

#define SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED     (416)
#define SIZE_AES_256BIT_KEYLEN_BYTES_WRAPPED    ((SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_256BIT_KEYLEN_WORDS_WRAPPED    ((SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED) / 32)

#define SIZE_AES_BLOCK_BITS                     (128)
#define SIZE_AES_BLOCK_BYTES                    (128 / 8)
#define SIZE_AES_BLOCK_WORDS                    ((SIZE_AES_BLOCK_BITS) / 32)

typedef struct st_sce_data
{
    uint32_t   length;
    uint32_t * p_data;
} r_sce_data_t;

typedef fsp_err_t (* hw_sce_aes_gcm_crypt_init_t)(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex,
                                                  uint32_t * InData_IV);
typedef void      (* hw_sce_aes_gcm_update_aad_t)(uint32_t * InData_DataA, uint32_t MAX_CNT);
typedef void      (* hw_sce_aes_gcm_crypt_update_transition_t)(void);
typedef void      (* hw_sce_aes_gcm_crypt_update_t)(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
typedef fsp_err_t (* hw_sce_aes_gcm_encrypt_final_t)(uint32_t * InData_Text, uint32_t * InData_DataALen,
                                                     uint32_t * InData_TextLen, uint32_t * OutData_Text,
                                                     uint32_t * OutData_DataT);
typedef fsp_err_t (* hw_sce_aes_gcm_decrypt_final_t)(uint32_t * InData_Text, uint32_t * InData_DataT,
                                                     uint32_t * InData_DataALen, uint32_t * InData_TextLen,
                                                     uint32_t * InData_DataTLen, uint32_t * OutData_Text);
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

fsp_err_t HW_SCE_Aes256GcmEncryptInitSubGeneral(uint32_t * InData_KeyType,
                                                uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes256GcmDecryptInitSubGeneral(uint32_t * InData_KeyType,
                                                uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes128EcbEncryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes128EcbDecryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes192EcbEncryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes192EcbDecryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes256EcbEncryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes256EcbDecryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes128CbcEncryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes128CbcDecryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes192CbcEncryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes192CbcDecryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes256CbcEncryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes256CbcDecryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes128CtrEncryptDecryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                       uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes192CtrEncryptDecryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                       uint32_t * InData_IV);

fsp_err_t HW_SCE_Aes256CtrEncryptDecryptInitSubGeneral(uint32_t * InData_KeyIndex,
                                                       uint32_t * InData_IV);

#endif                                 /* HW_SCE_AES_PRIVATE_H */
