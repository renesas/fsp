/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#ifndef HW_SCE_RA_PRIVATE_HEADER_FILE
#define HW_SCE_RA_PRIVATE_HEADER_FILE

#include "hw_sce_aes_private.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

#define SIZE_AES_GCM_IN_DATA_BYTES                       (256)
#define SIZE_AES_GCM_IN_DATA_IV_LEN_BYTES                (16)
#define SIZE_AES_GCM_IN_DATA_IV_GCM_LEN_BYTES            (512)
#define SIZE_AES_GCM_IN_DATA_AAD_LEN_BYTES               (128)

#define SCE_AES_GCM_IN_DATA_IV_LEN_LOC                   (32)

#define SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION               (0x00000000U)
#define SCE_AES_IN_DATA_CMD_ECB_DECRYPTION               (0x00000001U)
#define SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION               (0x00000002U)
#define SCE_AES_IN_DATA_CMD_CBC_DECRYPTION               (0x00000003U)
#define SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION    (0x00000004U)

#define SCE_AES_IN_DATA_CMD_CCM_128_ENC_COMMON_INIT      (0U)
#define SCE_AES_IN_DATA_CMD_CCM_192_ENC_COMMON_INIT      (1U)
#define SCE_AES_IN_DATA_CMD_CCM_256_ENC_COMMON_INIT      (2U)
#define SCE_AES_IN_DATA_CMD_CCM_ENC_COUNTER_GENERATE     (3U)
#define SCE_AES_IN_DATA_CMD_CCM_ENC_FORMAT_A_DATA        (4U)
#define SCE_AES_IN_DATA_CMD_CCM_ENC_CTR_ENCRYPT          (5U)
#define SCE_AES_IN_DATA_CMD_CCM_ENC_GENERATE_TAG         (6U)
#define SCE_AES_IN_DATA_CMD_CCM_128_DEC_COMMON_INIT      (7U)
#define SCE_AES_IN_DATA_CMD_CCM_192_DEC_COMMON_INIT      (8U)
#define SCE_AES_IN_DATA_CMD_CCM_256_DEC_COMMON_INIT      (9U)
#define SCE_AES_IN_DATA_CMD_CCM_DEC_COUNTER_GENERATE     (10U)
#define SCE_AES_IN_DATA_CMD_CCM_DEC_CTR_DECRYPT          (11U)
#define SCE_AES_IN_DATA_CMD_CCM_DEC_FORMAT_A_DATA        (12U)
#define SCE_AES_IN_DATA_CMD_CCM_DEC_FORMAT_PAYLOAD       (13U)
#define SCE_AES_IN_DATA_CMD_CCM_DEC_GENERATE_TAG         (14U)

/* Wrapped keys not supported on RA2; these definitions are added to let the code compile. */
#define SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED              (1)
#define SIZE_AES_128BIT_KEYLEN_BYTES_WRAPPED             ((SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_128BIT_KEYLEN_WORDS_WRAPPED             ((SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED) / 32)

#define SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED              (2) /* 192 not supported on SCE5 */
#define SIZE_AES_192BIT_KEYLEN_BYTES_WRAPPED             ((SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_192BIT_KEYLEN_WORDS_WRAPPED             ((SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED) / 32)

#define SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED              (3)
#define SIZE_AES_256BIT_KEYLEN_BYTES_WRAPPED             ((SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_256BIT_KEYLEN_WORDS_WRAPPED             ((SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED) / 32)

#define R_AES_AESCNTH_INIT                               (0x8000UL) /*!< AESCNTH initialization: Initialization AES Circuit                                                               */
#define R_AES_AESCNTH_DEINIT                             (0x0000UL) /*!< AESCNTH deinitialization: Don’t Initialize AES Circuit                                                           */
#define R_AES_AESCNTL_GCM_MODE                           (0x00A0UL) /*!< AESCNTL: Assign bit of Cipher use Mode: GCM mode                                                                 */
#define R_AES_AESCNTL_128_DEC                            (0x0008UL) /*!< AESCNTL: Decryption 128 bit (Bit 0-3 Selection bit of Encryption/Decryption and Key Length)                      */

#define R_AES_AESCNTL_CBC_128_ENC                        (0x0000UL) /*!< AESCNTL: Encryption - CBC mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CBC_192_ENC                        (0x0002UL) /*!< AESCNTL: Encryption - CBC mode - 192 bits                                                                        */
#define R_AES_AESCNTL_CBC_256_ENC                        (0x0004UL) /*!< AESCNTL: Encryption - CBC mode - 256 bits                                                                        */
#define R_AES_AESCNTL_CBC_128_DEC                        (0x0008UL) /*!< AESCNTL: Decryption - CBC mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CBC_192_DEC                        (0x000AUL) /*!< AESCNTL: Decryption - CBC mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CBC_256_DEC                        (0x000CUL) /*!< AESCNTL: Decryption - CBC mode - 128 bits                                                                        */

#define R_AES_AESCNTL_ECB_128_ENC                        (0x0010UL) /*!< AESCNTL: Encryption - ECB mode - 128 bits                                                                        */
#define R_AES_AESCNTL_ECB_192_ENC                        (0x0012UL) /*!< AESCNTL: Encryption - ECB mode - 192 bits                                                                        */
#define R_AES_AESCNTL_ECB_256_ENC                        (0x0014UL) /*!< AESCNTL: Encryption - ECB mode - 256 bits                                                                        */
#define R_AES_AESCNTL_ECB_128_DEC                        (0x0018UL) /*!< AESCNTL: Decryption - ECB mode - 128 bits                                                                        */
#define R_AES_AESCNTL_ECB_192_DEC                        (0x001AUL) /*!< AESCNTL: Decryption - ECB mode - 128 bits                                                                        */
#define R_AES_AESCNTL_ECB_256_DEC                        (0x001CUL) /*!< AESCNTL: Decryption - ECB mode - 128 bits                                                                        */

#define R_AES_AESCNTL_CTR_128_ENC                        (0x0040UL) /*!< AESCNTL: Encryption - CTR mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CTR_192_ENC                        (0x0042UL) /*!< AESCNTL: Encryption - CTR mode - 192 bits                                                                        */
#define R_AES_AESCNTL_CTR_256_ENC                        (0x0044UL) /*!< AESCNTL: Encryption - CTR mode - 256 bits                                                                        */
#define R_AES_AESCNTL_CTR_128_DEC                        (0x0048UL) /*!< AESCNTL: Decryption - CTR mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CTR_192_DEC                        (0x004AUL) /*!< AESCNTL: Decryption - CTR mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CTR_256_DEC                        (0x004CUL) /*!< AESCNTL: Decryption - CTR mode - 128 bits                                                                        */

#define R_AES_AESCNTL_CMAC_128_ENC                       (0x0080UL) /*!< AESCNTL: Encryption - CMAC mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CMAC_192_ENC                       (0x0082UL) /*!< AESCNTL: Encryption - CMAC mode - 192 bits                                                                        */
#define R_AES_AESCNTL_CMAC_256_ENC                       (0x0084UL) /*!< AESCNTL: Encryption - CMAC mode - 256 bits                                                                        */
#define R_AES_AESCNTL_CMAC_128_DEC                       (0x0088UL) /*!< AESCNTL: Decryption - CMAC mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CMAC_192_DEC                       (0x008AUL) /*!< AESCNTL: Decryption - CMAC mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CMAC_256_DEC                       (0x008CUL) /*!< AESCNTL: Decryption - CMAC mode - 128 bits                                                                        */

#define R_AES_AESCNTL_GCM_128_ENC                        (0x00A0UL) /*!< AESCNTL: Encryption - GCM mode - 128 bits                                                                        */
#define R_AES_AESCNTL_GCM_192_ENC                        (0x00A2UL) /*!< AESCNTL: Encryption - GCM mode - 192 bits                                                                        */
#define R_AES_AESCNTL_GCM_256_ENC                        (0x00A4UL) /*!< AESCNTL: Encryption - GCM mode - 256 bits                                                                        */
#define R_AES_AESCNTL_GCM_128_DEC                        (0x00A8UL) /*!< AESCNTL: Decryption - GCM mode - 128 bits                                                                        */
#define R_AES_AESCNTL_GCM_192_DEC                        (0x00AAUL) /*!< AESCNTL: Decryption - GCM mode - 128 bits                                                                        */
#define R_AES_AESCNTL_GCM_256_DEC                        (0x00ACUL) /*!< AESCNTL: Decryption - GCM mode - 128 bits                                                                        */

#define R_AES_AESCNTL_CCM_128_ENC                        (0x00C0UL) /*!< AESCNTL: Encryption - CCM mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CCM_192_ENC                        (0x00C2UL) /*!< AESCNTL: Encryption - CCM mode - 192 bits                                                                        */
#define R_AES_AESCNTL_CCM_256_ENC                        (0x00C4UL) /*!< AESCNTL: Encryption - CCM mode - 256 bits                                                                        */
#define R_AES_AESCNTL_CCM_128_DEC                        (0x00C8UL) /*!< AESCNTL: Decryption - CCM mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CCM_192_DEC                        (0x00CAUL) /*!< AESCNTL: Decryption - CCM mode - 128 bits                                                                        */
#define R_AES_AESCNTL_CCM_256_DEC                        (0x00CCUL) /*!< AESCNTL: Decryption - CCM mode - 128 bits                                                                        */

#define R_AES_AESDCNTL_BIT_2_3_MODE_1                    (0x0008UL) /*!< AESDCNTL: Key update assign bit: Enable + First block contents control assign bit: Use (AES-ECB, AES-GCM)        */
#define R_AES_AESDCNTL_BIT_2_3_MODE_2                    (0x000CUL) /*!< AESDCNTL: Key update assign bit: Enable + First block contents control assign bit: Not use (AES-CBC, AES-CTR)    */
#define R_AES_AESDCNTL_CALCULATE_START                   (0x0003UL) /*!< AESDCNTL: Start AES calculation - Start reflect AES Encryption/Decryption calculation result to AESODATnRegister */
#define R_AES_AESDCNTL_BIT_2                             (0x0004UL) /*!< AESDCNTL: Bit 2                                                                                                  */
#define R_AES_AESDCNTL_BIT_3                             (0x0008UL) /*!< AESDCNTL: Bit 3                                                                                                  */
#define R_AES_AESDCNTL_BIT_4                             (0x0010UL) /*!< AESDCNTL: Bit 4                                                                                                  */
#define R_AES_AESDCNTL_BIT_5                             (0x0020UL) /*!< AESDCNTL: Bit 5                                                                                                  */
#define R_AES_AESDCNTL_BIT_6                             (0x0040UL) /*!< AESDCNTL: Bit 6                                                                                                  */

#define R_AES_AESDCNTL_FIST_SET                          (0x0004UL) /*!< AESDCNTL: FIRST = 1: The result of the previous calculation is not used for the calculation of the first block   */
#define R_AES_AESDCNTL_NEW_KEY_SET                       (0x0008UL) /*!< AESDCNTL: NEW_KEY = 1: Key data are updated using the data set in the AESKEYn registers                          */
#define R_AES_AESDCNTL_ATTR_CCM_MODE_1                   (0x0020UL) /*!< AESDCNTL: ATTR[2:0] = 001: The input data as the parameter B0 of the formatting function                         */
#define R_AES_AESDCNTL_ATTR_CCM_MODE_2                   (0x0040UL) /*!< AESDCNTL: ATTR[2:0] = 010: In encryption: Setting prohibited, In decryption: A ciphertext                        */
#define R_AES_AESDCNTL_ATTR_CCM_MODE_3                   (0x0060UL) /*!< AESDCNTL: ATTR[2:0] = 011: The input data as A (associated data) of the formatting function                      */
#define R_AES_AESDCNTL_ATTR_CCM_MODE_4                   (0x0080UL) /*!< AESDCNTL: ATTR[2:0] = 100: Indicating the input data are a plaintext                                             */
#define R_AES_AESDCNTL_ATTR_CCM_MODE_5                   (0x0000UL) /*!< AESDCNTL: ATTR[2:0] = 000: In encryption: The dummy input data used for calculation of T XOR MSBTlen(S0)
                                                                     *                              In decryption: Setting prohibited                                                     */
#define R_AES_AESDCNTL_ATTR_CCM_MODE_6                   (0x00A0UL) /*!< AESDCNTL: ATTR[2:0] = 101: In encryption: Setting prohibited
                                                                     *                              In decryption: The input data to be calculated by T XOR MSBTlen(S0)                   */

#define R_AES_AESSTSL_BIT_5                              (0x0020UL) /*!< AESSTSL: Bit 5: Status Bit to show AES operation status                                                          */
#define R_AES_AESSTSL_CALCULATE_COMPLETED                (0x0003UL) /*!< AESSTSL: Bit 0-1: Status Bit to show AES Encryption/Decryption completion                                        */
#define R_AES_AESSTSCL_DATA_CLEAN                        (0x0003UL) /*!< AESSTSCL: Bit 0-1: clear bit1.0 state in AES Status Register                                                     */

#define R_AES_AESDCNTH_EXECUTE_TAG_CALCULATION           (0x0002UL) /*!< AESDCNTH: Bit 1 = 1: The calculation of tag is executed, and result is stored in the AESODATn registers          */
#define R_AES_AESDCNTH_NOT_EXECUTE_TAG_CALCULATION       (0x0000UL) /*!< AESDCNTH: Bit 1 = 0: Don't execute calculation of tag                                                            */

#define HW_AES_DATA_FIT_TO_BLOCK_SIZE(x)    ((uint32_t) x & 0xFFFFFFF0)
#define HW_AES_DATA_GET_LAST_REMAINS(x)     ((uint32_t) x & 0x0000000F)
#define HW_32BIT_ALIGNED(x)                 !(x & 0x03)

/**********************************************************************************************************************
 * Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/
uint32_t  change_endian_long(uint32_t data);
void      hw_aes_set_key(uint8_t * key, uint32_t KeyLen);
void      hw_aes_set_iv(uint8_t * initialize_vetor);
fsp_err_t hw_aes_start(uint8_t * input, uint8_t * output, uint32_t block);
void      hw_aes_ccm_mode_start(uint8_t * input, uint8_t * output, uint32_t block);
fsp_err_t hw_gcm_calculation(uint8_t * input,
                             uint8_t * output,
                             uint32_t  data_len,
                             uint8_t * atag,
                             uint8_t * initial_vector,
                             uint32_t  iv_len,
                             uint8_t * aad,
                             uint32_t  aad_len);

void HW_SCE_AesCcmDecryptCounterGenerate(uint32_t InData_TextLength,
                                         uint32_t InData_Hdrlen,
                                         uint32_t InData_MacLength,
                                         uint32_t InData_IVLength);

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub(const uint32_t * InData_KeyType,
                                             const uint32_t * InData_Cmd,
                                             const uint32_t * InData_KeyIndex,
                                             const uint32_t * InData_IV);

void HW_SCE_Aes128EncryptDecryptUpdateSub(const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          const uint32_t   MAX_CNT);
fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub(void);

fsp_err_t HW_SCE_Aes192EncryptDecryptInitSub(const uint32_t * InData_Cmd,
                                             const uint32_t * InData_KeyIndex,
                                             const uint32_t * InData_IV);
void HW_SCE_Aes192EncryptDecryptUpdateSub(const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          const uint32_t   MAX_CNT);
fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub(void);
fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub(const uint32_t * InData_KeyType,
                                             const uint32_t * InData_Cmd,
                                             const uint32_t * InData_KeyIndex,
                                             const uint32_t * InData_IV);
fsp_err_t HW_SCE_Aes256EncryptDecryptInitSubAdaptor(const uint32_t InData_KeyMode[],
                                                    const uint32_t InData_Cmd[],
                                                    const uint32_t InData_KeyIndex[],
                                                    const uint32_t InData_Key[],
                                                    const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes128EncryptDecryptInitSubAdaptor(const uint32_t InData_KeyMode[],
                                                    const uint32_t InData_Cmd[],
                                                    const uint32_t InData_KeyIndex[],
                                                    const uint32_t InData_Key[],
                                                    const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes192EncryptDecryptInitSubAdaptor(const uint32_t InData_KeyMode[],
                                                    const uint32_t InData_Cmd[],
                                                    const uint32_t InData_KeyIndex[],
                                                    const uint32_t InData_Key[],
                                                    const uint32_t InData_IV[]);
void HW_SCE_Aes256EncryptDecryptUpdateSub(const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          const uint32_t   MAX_CNT);
fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub(void);

fsp_err_t HW_SCE_Aes128GcmEncryptInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV);
void      HW_SCE_Aes128GcmEncryptUpdateAADSub(uint32_t * InData_DataA, uint32_t MAX_CNT);
void      HW_SCE_Aes128GcmEncryptUpdateTransitionSub(void);
void      HW_SCE_Aes128GcmEncryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128GcmEncryptFinalSub(uint32_t * InData_Text,
                                          uint32_t * InData_DataALen,
                                          uint32_t * InData_TextLen,
                                          uint32_t * OutData_Text,
                                          uint32_t * OutData_DataT);
fsp_err_t HW_SCE_Aes128GcmDecryptInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV);
void      HW_SCE_Aes128GcmDecryptUpdateAADSub(uint32_t * InData_DataA, uint32_t MAX_CNT);
void      HW_SCE_Aes128GcmDecryptUpdateTransitionSub(void);
void      HW_SCE_Aes128GcmDecryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128GcmDecryptFinalSub(uint32_t * InData_Text,
                                          uint32_t * InData_DataT,
                                          uint32_t * InData_DataALen,
                                          uint32_t * InData_TextLen,
                                          uint32_t * InData_DataTLen,
                                          uint32_t * OutData_Text);

fsp_err_t HW_SCE_Aes192GcmEncryptInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV);
void      HW_SCE_Aes192GcmEncryptUpdateAADSub(uint32_t * InData_DataA, uint32_t MAX_CNT);
void      HW_SCE_Aes192GcmEncryptUpdateTransitionSub(void);
void      HW_SCE_Aes192GcmEncryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192GcmEncryptFinalSub(uint32_t * InData_Text,
                                          uint32_t * InData_DataALen,
                                          uint32_t * InData_TextLen,
                                          uint32_t * OutData_Text,
                                          uint32_t * OutData_DataT);
fsp_err_t HW_SCE_Aes192GcmDecryptInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV);
void      HW_SCE_Aes192GcmDecryptUpdateAADSub(uint32_t * InData_DataA, uint32_t MAX_CNT);
void      HW_SCE_Aes192GcmDecryptUpdateTransitionSub(void);
void      HW_SCE_Aes192GcmDecryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192GcmDecryptFinalSub(uint32_t * InData_Text,
                                          uint32_t * InData_DataT,
                                          uint32_t * InData_DataALen,
                                          uint32_t * InData_TextLen,
                                          uint32_t * InData_DataTLen,
                                          uint32_t * OutData_Text);

fsp_err_t HW_SCE_Aes256GcmEncryptInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV);
void      HW_SCE_Aes256GcmEncryptUpdateAADSub(uint32_t * InData_DataA, uint32_t MAX_CNT);
void      HW_SCE_Aes256GcmEncryptUpdateTransitionSub(void);
void      HW_SCE_Aes256GcmEncryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256GcmEncryptFinalSub(uint32_t * InData_Text,
                                          uint32_t * InData_DataALen,
                                          uint32_t * InData_TextLen,
                                          uint32_t * OutData_Text,
                                          uint32_t * OutData_DataT);
fsp_err_t HW_SCE_Aes256GcmDecryptInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV);
void      HW_SCE_Aes256GcmDecryptUpdateAADSub(uint32_t * InData_DataA, uint32_t MAX_CNT);
void      HW_SCE_Aes256GcmDecryptUpdateTransitionSub(void);
void      HW_SCE_Aes256GcmDecryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256GcmDecryptFinalSub(uint32_t * InData_Text,
                                          uint32_t * InData_DataT,
                                          uint32_t * InData_DataALen,
                                          uint32_t * InData_TextLen,
                                          uint32_t * InData_DataTLen,
                                          uint32_t * OutData_Text);
fsp_err_t HW_SCE_AES_128CtrEncrypt(const uint32_t * InData_Key,
                                   const uint32_t * InData_IV,
                                   const uint32_t   num_words,
                                   const uint32_t * InData_Text,
                                   uint32_t       * OutData_Text,
                                   uint32_t       * OutData_IV);
fsp_err_t HW_SCE_AES_192CtrEncrypt(const uint32_t * InData_Key,
                                   const uint32_t * InData_IV,
                                   const uint32_t   num_words,
                                   const uint32_t * InData_Text,
                                   uint32_t       * OutData_Text,
                                   uint32_t       * OutData_IV);
fsp_err_t HW_SCE_AES_256CtrEncrypt(const uint32_t * InData_Key,
                                   const uint32_t * InData_IV,
                                   const uint32_t   num_words,
                                   const uint32_t * InData_Text,
                                   uint32_t       * OutData_Text,
                                   uint32_t       * OutData_IV);
fsp_err_t HW_SCE_AES_128CtrDecrypt(const uint32_t * InData_Key,
                                   const uint32_t * InData_IV,
                                   const uint32_t   num_words,
                                   const uint32_t * InData_Text,
                                   uint32_t       * OutData_Text);
fsp_err_t HW_SCE_AES_192CtrDecrypt(const uint32_t * InData_Key,
                                   const uint32_t * InData_IV,
                                   const uint32_t   num_words,
                                   const uint32_t * InData_Text,
                                   uint32_t       * OutData_Text);
fsp_err_t HW_SCE_AES_256CtrDecrypt(const uint32_t * InData_Key,
                                   const uint32_t * InData_IV,
                                   const uint32_t   num_words,
                                   const uint32_t * InData_Text,
                                   uint32_t       * OutData_Text);

fsp_err_t HW_SCE_Aes128CcmEncryptInitSub(const uint32_t InData_KeyType[],
                                         const uint32_t InData_DataType[],
                                         const uint32_t InData_Cmd[],
                                         const uint32_t InData_TextLen[],
                                         const uint32_t InData_KeyIndex[],
                                         const uint32_t InData_IV[],
                                         const uint32_t InData_Header[],
                                         const uint32_t InData_SeqNum[],
                                         const uint32_t Header_Len);

fsp_err_t HW_SCE_Aes192CcmEncryptInitSub(const uint32_t InData_KeyType[],
                                         const uint32_t InData_DataType[],
                                         const uint32_t InData_Cmd[],
                                         const uint32_t InData_TextLen[],
                                         const uint32_t InData_KeyIndex[],
                                         const uint32_t InData_IV[],
                                         const uint32_t InData_Header[],
                                         const uint32_t InData_SeqNum[],
                                         const uint32_t Header_Len);

fsp_err_t HW_SCE_Aes256CcmEncryptInitSub(const uint32_t InData_KeyType[],
                                         const uint32_t InData_DataType[],
                                         const uint32_t InData_Cmd[],
                                         const uint32_t InData_TextLen[],
                                         const uint32_t InData_KeyIndex[],
                                         const uint32_t InData_IV[],
                                         const uint32_t InData_Header[],
                                         const uint32_t InData_SeqNum[],
                                         const uint32_t Header_Len);

void HW_SCE_Aes128CcmEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);

void HW_SCE_Aes192CcmEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);

void HW_SCE_Aes256CcmEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);

fsp_err_t HW_SCE_Aes128CcmEncryptFinalSub(const uint32_t InData_Text[], uint32_t OutData_Text[],
                                          uint32_t OutData_MAC[]);

fsp_err_t HW_SCE_Aes192CcmEncryptFinalSub(const uint32_t InData_Text[], uint32_t OutData_Text[],
                                          uint32_t OutData_MAC[]);

fsp_err_t HW_SCE_Aes256CcmEncryptFinalSub(const uint32_t InData_Text[], uint32_t OutData_Text[],
                                          uint32_t OutData_MAC[]);

fsp_err_t HW_SCE_Aes128CcmDecryptInitSub(const uint32_t InData_KeyType[],
                                         const uint32_t InData_DataType[],
                                         const uint32_t InData_Cmd[],
                                         const uint32_t InData_TextLen[],
                                         const uint32_t InData_MACLength[],
                                         const uint32_t InData_KeyIndex[],
                                         const uint32_t InData_IV[],
                                         const uint32_t InData_Header[],
                                         const uint32_t InData_SeqNum[],
                                         const uint32_t Header_Len);

fsp_err_t HW_SCE_Aes192CcmDecryptInitSub(const uint32_t InData_KeyType[],
                                         const uint32_t InData_DataType[],
                                         const uint32_t InData_Cmd[],
                                         const uint32_t InData_TextLen[],
                                         const uint32_t InData_MACLength[],
                                         const uint32_t InData_KeyIndex[],
                                         const uint32_t InData_IV[],
                                         const uint32_t InData_Header[],
                                         const uint32_t InData_SeqNum[],
                                         const uint32_t Header_Len);

fsp_err_t HW_SCE_Aes256CcmDecryptInitSub(const uint32_t InData_KeyType[],
                                         const uint32_t InData_DataType[],
                                         const uint32_t InData_Cmd[],
                                         const uint32_t InData_TextLen[],
                                         const uint32_t InData_MACLength[],
                                         const uint32_t InData_KeyIndex[],
                                         const uint32_t InData_IV[],
                                         const uint32_t InData_Header[],
                                         const uint32_t InData_SeqNum[],
                                         const uint32_t Header_Len);

void HW_SCE_Aes128CcmDecryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);

void HW_SCE_Aes192CcmDecryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);

void HW_SCE_Aes256CcmDecryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);

fsp_err_t HW_SCE_Aes128CcmDecryptFinalSub(const uint32_t InData_Text[],
                                          const uint32_t InData_TextLen[],
                                          const uint32_t InData_MAC[],
                                          const uint32_t InData_MACLength[],
                                          uint32_t       OutData_Text[]);

fsp_err_t HW_SCE_Aes192CcmDecryptFinalSub(const uint32_t InData_Text[],
                                          const uint32_t InData_TextLen[],
                                          const uint32_t InData_MAC[],
                                          const uint32_t InData_MACLength[],
                                          uint32_t       OutData_Text[]);

fsp_err_t HW_SCE_Aes256CcmDecryptFinalSub(const uint32_t InData_Text[],
                                          const uint32_t InData_TextLen[],
                                          const uint32_t InData_MAC[],
                                          const uint32_t InData_MACLength[],
                                          uint32_t       OutData_Text[]);

fsp_err_t HW_SCE_Aes128GcmEncryptInitSubGeneral(uint32_t * InData_KeyType,
                                                uint32_t * InData_DataType,
                                                uint32_t * InData_Cmd,
                                                uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV,
                                                uint32_t * InData_SeqNum);
fsp_err_t HW_SCE_Aes128GcmDecryptInitSubGeneral(uint32_t * InData_KeyType,
                                                uint32_t * InData_DataType,
                                                uint32_t * InData_Cmd,
                                                uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV,
                                                uint32_t * InData_SeqNum);
fsp_err_t HW_SCE_Aes192GcmDecryptInitSubGeneral(uint32_t * InData_KeyType,
                                                uint32_t * InData_DataType,
                                                uint32_t * InData_Cmd,
                                                uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV,
                                                uint32_t * InData_SeqNum);
fsp_err_t HW_SCE_Aes192GcmEncryptInitSubGeneral(uint32_t * InData_KeyType,
                                                uint32_t * InData_DataType,
                                                uint32_t * InData_Cmd,
                                                uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV,
                                                uint32_t * InData_SeqNum);
fsp_err_t HW_SCE_Aes256GcmDecryptInitSubGeneral(uint32_t * InData_KeyType,
                                                uint32_t * InData_DataType,
                                                uint32_t * InData_Cmd,
                                                uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV,
                                                uint32_t * InData_SeqNum);
fsp_err_t HW_SCE_Aes256GcmEncryptInitSubGeneral(uint32_t * InData_KeyType,
                                                uint32_t * InData_DataType,
                                                uint32_t * InData_Cmd,
                                                uint32_t * InData_KeyIndex,
                                                uint32_t * InData_IV,
                                                uint32_t * InData_SeqNum);

#endif                                 /* HW_SCE_RA_PRIVATE_HEADER_FILE */
