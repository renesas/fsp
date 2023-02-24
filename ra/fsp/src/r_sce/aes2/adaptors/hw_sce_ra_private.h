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

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#ifndef HW_SCE_RA_PRIVATE_HEADER_FILE
#define HW_SCE_RA_PRIVATE_HEADER_FILE

#include "hw_sce_aes_private.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/
#define SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION               (0x00000000U)
#define SCE_AES_IN_DATA_CMD_ECB_DECRYPTION               (0x00000001U)
#define SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION               (0x00000002U)
#define SCE_AES_IN_DATA_CMD_CBC_DECRYPTION               (0x00000003U)
#define SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION    (0x00000004U)

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
uint32_t change_endian_long(uint32_t data);

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
void HW_SCE_Aes256EncryptDecryptUpdateSub(const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          const uint32_t   MAX_CNT);
fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub(void);

#endif                                 /* HW_SCE_RA_PRIVATE_HEADER_FILE */
