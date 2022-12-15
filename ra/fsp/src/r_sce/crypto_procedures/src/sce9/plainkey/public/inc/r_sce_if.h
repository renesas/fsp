/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2015-2020 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_sce_if.h
 * Version      : 1.09
 * Description  : Interface definition for the r_sce module.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
// added for RA6M4 start
//#include "platform.h"
#include "bsp_api.h"
// added for RA6M4 end


/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

#ifndef R_SCE_IF_HEADER_FILE
#define R_SCE_IF_HEADER_FILE


// added for RA6M4 start
#if 0
// added for RA6M4 end

#if R_BSP_VERSION_MAJOR < 5
#error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif
#if (defined BSP_MCU_RX231 || defined BSP_MCU_RX23W) && (BSP_CFG_MCU_PART_VERSION == 0xB)  /* B */
#elif (defined BSP_MCU_RX66T || defined BSP_MCU_RX72T) && ((BSP_CFG_MCU_PART_FUNCTION == 0xE /* E */) || \
    (BSP_CFG_MCU_PART_FUNCTION == 0xF /* F */) || (BSP_CFG_MCU_PART_FUNCTION == 0x10 /* G */))
#elif (defined BSP_MCU_RX65N || defined BSP_MCU_RX651) && (BSP_CFG_MCU_PART_ENCRYPTION_INCLUDED == true)
#elif (defined BSP_MCU_RX72M || defined BSP_MCU_RX72N || defined BSP_MCU_RX66N) && \
    (BSP_CFG_MCU_PART_FUNCTION == 0x11 /* H */)
#else
#error "Your MCU does not support SCE functions. Please confirm BSP_MCU_xxx macro in r_bsp_config.h."
#endif  /* defined BSP_MCU_RX231 || defined BSP_MCU_RX23W && BSP_CFG_MCU_PART_VERSION == 0xB */

// added for RA6M4 start
#endif
// added for RA6M4 end

/* Version Number of API. */
#define SCE_VERSION_MAJOR    (1U)
#define SCE_VERSION_MINOR    (9U)

/* Various information. */
#define HW_SCE_SRAM_WORD_SIZE   (32U)
#define HW_SCE_SINST_WORD_SIZE  (140U)
#define HW_SCE_SINST2_WORD_SIZE (16U)
#define HW_SCE_SHEAP_WORD_SIZE  (1504U)
#define HW_SCE_MAC_SIZE         (16U)

/* For AES operation. */
#define HW_SCE_AES128_KEY_INDEX_WORD_SIZE     (9U)
#define HW_SCE_AES192_KEY_INDEX_WORD_SIZE     (13U)
#define HW_SCE_AES256_KEY_INDEX_WORD_SIZE     (13U)
#define HW_SCE_AES128XTS_KEY_INDEX_WORD_SIZE  (13U)
#define HW_SCE_AES256XTS_KEY_INDEX_WORD_SIZE  (21U)
#define HW_SCE_AES128_KEY_WORD_SIZE           (4U)
#define HW_SCE_AES192_KEY_WORD_SIZE           (8U)
#define HW_SCE_AES256_KEY_WORD_SIZE           (8U)
#define HW_SCE_AES128_KEY_BYTE_SIZE           (16U)
#define HW_SCE_AES192_KEY_BYTE_SIZE           (32U)
#define HW_SCE_AES256_KEY_BYTE_SIZE           (32U)
#define HW_SCE_AES_BLOCK_BYTE_SIZE            (16U)
#define HW_SCE_AES_BLOCK_BIT_SIZE             (128U)
#define HW_SCE_AES_CBC_IV_BYTE_SIZE           (16U)
#define HW_SCE_AES_CTR_ICOUNTER_BYTE_SIZE     (16U)
#define HW_SCE_AES_GCM_AAD_BLOCK_BYTE_SIZE    (16U)
#define HW_SCE_AES_CCM_B_FORMAT_BYTE_SIZE     (128U)
#define HW_SCE_AES_CCM_COUNTER_BYTE_SIZE      (16U)
#define HW_SCE_AES128XTS_KEY_BYTE_SIZE        (32U)
#define HW_SCE_AES256XTS_KEY_BYTE_SIZE        (64U)
#define HW_SCE_AES128XTS_KEY_BIT_SIZE         (256U)
#define HW_SCE_AES256XTS_KEY_BIT_SIZE         (512U)
#define HW_SCE_AES_XTS_IV_BYTE_SIZE           (16U)

/* For TDES operation. */
#define HW_SCE_TDES_KEY_INDEX_WORD_SIZE       (16U)
#define HW_SCE_TDES_BLOCK_BYTE_SIZE           (8U)
#define HW_SCE_TDES_CBC_IV_BYTE_SIZE          (8U)
#define HW_SCE_TDES_KEY_WORD_SIZE             (8U)
#define HW_SCE_TDES_KEY_BYTE_SIZE             (32U)

/* For ARC4 operation. */
#define HW_SCE_ARC4_KEY_INDEX_WORD_SIZE       (72U)
#define HW_SCE_ARC4_KEY_WORD_SIZE             (64U)
#define HW_SCE_ARC4_KEY_BYTE_SIZE             (256U)
#define HW_SCE_ARC4_BLOCK_BYTE_SIZE           (16U)

/* For SHA operation. */
#define HW_SCE_SHA1_HASH_LENGTH_BYTE_SIZE      (20U)
#define HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE    (32U)
#define HW_SCE_SHA384_HASH_LENGTH_BYTE_SIZE    (48U)

/* For MD5 operation. */
#define HW_SCE_MD5_HASH_LENGTH_BYTE_SIZE       (16U)

/* For HMAC operation. */
#define HW_SCE_HMAC_KEY_INDEX_BYTE_SIZE        (52U)
#define HW_SCE_HMAC_KEY_INDEX_WORD_SIZE        (13U)
#define HW_SCE_HMAC_KEY_BYTE_SIZE              (32U)

/* For RSA operation. */
#define HW_SCE_RSA_1024_KEY_N_LENGTH_BYTE_SIZE                  (128U)
#define HW_SCE_RSA_1024_KEY_E_LENGTH_BYTE_SIZE                  (4U)
#define HW_SCE_RSA_1024_KEY_D_LENGTH_BYTE_SIZE                  (128U)
#define HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE                  (256U)
#define HW_SCE_RSA_2048_KEY_E_LENGTH_BYTE_SIZE                  (4U)
#define HW_SCE_RSA_2048_KEY_D_LENGTH_BYTE_SIZE                  (256U)
#define HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE                  (96  * 4U)
#define HW_SCE_RSA_3072_KEY_E_LENGTH_BYTE_SIZE                  (4U)
#define HW_SCE_RSA_3072_KEY_D_LENGTH_BYTE_SIZE                  (96  * 4U)
#define HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE                  (128 * 4U)
#define HW_SCE_RSA_4096_KEY_E_LENGTH_BYTE_SIZE                  (4U)
#define HW_SCE_RSA_4096_KEY_D_LENGTH_BYTE_SIZE                  (128 * 4U)
#define HW_SCE_RSA_1024_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE   (1U)
#define HW_SCE_RSA_1024_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE   (36U)
#define HW_SCE_RSA_1024_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE  (1U)
#define HW_SCE_RSA_1024_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE  (68U)
#define HW_SCE_RSA_2048_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE   (1U)
#define HW_SCE_RSA_2048_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE   (68U)
#define HW_SCE_RSA_2048_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE  (1U)
#define HW_SCE_RSA_2048_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE  (132U)
#define HW_SCE_RSA_3072_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE   (1U)
#define HW_SCE_RSA_3072_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE   (4U)
#define HW_SCE_RSA_3072_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE  (1U)
#define HW_SCE_RSA_3072_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE  (132U)
#define HW_SCE_RSA_4096_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE   (1U)
#define HW_SCE_RSA_4096_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE   (4U)
#define HW_SCE_RSA_4096_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE  (1U)
#define HW_SCE_RSA_4096_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE  (132U)
#define HW_SCE_RSA_KEY_GENERATION_DUMMY_BYTE_SIZE               (12U)
#define HW_SCE_RSA1024_NE_KEY_BYTE_SIZE                         (144U)
#define HW_SCE_RSA1024_ND_KEY_BYTE_SIZE                         (256U)
#define HW_SCE_RSA2048_NE_KEY_BYTE_SIZE                         (272U)
#define HW_SCE_RSA2048_ND_KEY_BYTE_SIZE                         (512U)
#define HW_SCE_RSA3072_NE_KEY_BYTE_SIZE                         (96  * 4 + 16U)
#define HW_SCE_RSA3072_ND_KEY_BYTE_SIZE                         (192 * 4U)
#define HW_SCE_RSA4096_NE_KEY_BYTE_SIZE                         (128 * 4 + 16U)
#define HW_SCE_RSA4096_ND_KEY_BYTE_SIZE                         (256 * 4U)
#define HW_SCE_RSA1024_NE_KEY_INDEX_WORD_SIZE                   (73U)
#define HW_SCE_RSA1024_ND_KEY_INDEX_WORD_SIZE                   (101U)
#define HW_SCE_RSA2048_NE_KEY_INDEX_WORD_SIZE                   (137U)
#define HW_SCE_RSA2048_ND_KEY_INDEX_WORD_SIZE                   (197U)
#define HW_SCE_RSA3072_NE_KEY_INDEX_WORD_SIZE                   (105U)
#define HW_SCE_RSA3072_ND_KEY_INDEX_WORD_SIZE                   (197U)
#define HW_SCE_RSA4096_NE_KEY_INDEX_WORD_SIZE                   (137U)
#define HW_SCE_RSA4096_ND_KEY_INDEX_WORD_SIZE                   (261U)
#define HW_SCE_RSA1024_RANDOM_PUBLIC_KEY_INDEX_WORD_SIZE        (73U)
#define HW_SCE_RSA1024_RANDOM_PRIVATE_KEY_INDEX_WORD_SIZE       (101U)
#define HW_SCE_RSA2048_RANDOM_PUBLIC_KEY_INDEX_WORD_SIZE        (137U)
#define HW_SCE_RSA2048_RANDOM_PRIVATE_KEY_INDEX_WORD_SIZE       (197U)
//#define HW_SCE_RSA3072_RANDOM_PUBLIC_KEY_INDEX_WORD_SIZE        (140U)
//#define HW_SCE_RSA3072_RANDOM_PRIVATE_KEY_INDEX_WORD_SIZE       (200U)
//#define HW_SCE_RSA4096_RANDOM_PUBLIC_KEY_INDEX_WORD_SIZE        (140U)
//#define HW_SCE_RSA4096_RANDOM_PRIVATE_KEY_INDEX_WORD_SIZE       (200U)
#define HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE               (11U)
#define HW_SCE_RSA_1024_DATA_BYTE_SIZE                          (128U)
#define HW_SCE_RSA_2048_DATA_BYTE_SIZE                          (256U)
#define HW_SCE_RSA_3072_DATA_BYTE_SIZE                          (96  * 4U)
#define HW_SCE_RSA_4096_DATA_BYTE_SIZE                          (128 * 4U)
#define HW_SCE_RSA2048_RANDOM_PRIVATE_KEY_BYTE_SIZE             (64U * 4U)
#define HW_SCE_RSA2048_RANDOM_PUBLIC_KEY_BYTE_SIZE              (65U * 4U)

/* RSA HASH type. */
#define HW_SCE_RSA_HASH_MD5                                     (0x01)  /* MD5     */
#define HW_SCE_RSA_HASH_SHA1                                    (0x02)  /* SHA-1   */
#define HW_SCE_RSA_HASH_SHA256                                  (0x03)  /* SHA-256 */

/* For ECC operation. */
//#define HW_SCE_ECC_KEY_LENGTH_BYTE_SIZE                     (32U)
#define HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE    (1U)
#define HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE    (4U)
//#define HW_SCE_ECC_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE   (4U)
//#define HW_SCE_ECC_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE   (12U)
//#define HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE                     (64U)
//#define HW_SCE_ECC_P384_PUBLIC_KEY_BYTE_SIZE                (96U)
//#define HW_SCE_ECC_PRIVATE_KEY_BYTE_SIZE                    (32U)
//#define HW_SCE_ECC_P384_PRIVATE_KEY_BYTE_SIZE               (48U)
//#define HW_SCE_ECDSA_DATA_BYTE_SIZE                         (64U)
//#define HW_SCE_ECDSA_P384_DATA_BYTE_SIZE                    (96U)
//#define HW_SCE_SHARED_SECRET_KEY_INDEX_WORD_SIZE            (16U)
//#define HW_SCE_ALGORITHM_ID_ENCODED_DATA_BYTE_SIZE          (7U)
#define HW_SCE_ECC_KEY_LENGTH_BYTE_SIZE                     (112U)
#define HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO_WORD_SIZE     (1U)
#define HW_SCE_ECC_PRIVATE_KEY_MANAGEMENT_INFO_WORD_SIZE    (17U)
#define HW_SCE_ECC_P192_P224_P256_PUBLIC_KEY_BYTE_SIZE      (64U)
#define HW_SCE_ECC_P384_PUBLIC_KEY_BYTE_SIZE                (96U)
#define HW_SCE_ECC_PRIVATE_KEY_BYTE_SIZE                    (32U)
#define HW_SCE_ECC_P384_PRIVATE_KEY_BYTE_SIZE               (48U)
#define HW_SCE_ECDSA_DATA_BYTE_SIZE                         (64U)
#define HW_SCE_ECDSA_P384_DATA_BYTE_SIZE                    (96U)
#define HW_SCE_SHARED_SECRET_KEY_INDEX_WORD_SIZE            (13U)
#define HW_SCE_PRIVATE_KEY_WRAPPING_WORD_SIZE               (5U)
#define HW_SCE_ALGORITHM_ID_ENCODED_DATA_BYTE_SIZE          (7U)

/* For KeyWrap. */
#define HW_SCE_KEYWRAP_AES128   (0U)
#define HW_SCE_KEYWRAP_AES256   (2U)

/* For TLS. */
#define HW_SCE_TLS_RSA_NE_KEY_BYTE_SIZE                     (272U)
#define HW_SCE_TLS_RSA_NE_KEY_INDEX_WORD_SIZE               (140U)
#define HW_SCE_TLS_ROOT_PUBLIC_KEY_WORD_SIZE                (137U)
#define HW_SCE_TLS_P256_ECC_KEY_WORD_SIZE                   (16U)
#define HW_SCE_TLS_EPHEMERAL_ECDH_PUBLIC_KEY_WORD_SIZE      (16U)
#define HW_SCE_TLS_MASTER_SECRET_WORD_SIZE                  (20U)
#define HW_SCE_TLS_GENERATE_MAC_KEY_WORD_SIZE               (16U)
#define HW_SCE_TLS_GENERATE_AES128_CRYPTO_KEY_WORD_SIZE     (12U)
#define HW_SCE_TLS_GENERATE_AES256_CRYPTO_KEY_WORD_SIZE     (16U)
#define HW_SCE_TLS_GENERATE_VERIFY_DATA_BYTE_SIZE           (12U)
#define HW_SCE_TLS_RSA_WITH_AES_128_CBC_SHA                 (0U)
#define HW_SCE_TLS_RSA_WITH_AES_256_CBC_SHA                 (1U)
#define HW_SCE_TLS_RSA_WITH_AES_128_CBC_SHA256              (2U)
#define HW_SCE_TLS_RSA_WITH_AES_256_CBC_SHA256              (3U)
#define HW_SCE_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256      (4U)
#define HW_SCE_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256        (5U)
#define HW_SCE_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256      (6U)
#define HW_SCE_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256        (7U)
#define HW_SCE_TLS_GENERATE_CLIENT_VERIFY                   (0U)
#define HW_SCE_TLS_GENERATE_SERVER_VERIFY                   (1U)
#define HW_SCE_TLS_PUBLIC_KEY_TYPE_RSA2048                  (0U)
#define HW_SCE_TLS_PUBLIC_KEY_TYPE_ECDSA_P256               (2U)

/* TLS-HMAC. */
#define HW_SCE_TLS_HMAC_KEY_INDEX_BYTE_SIZE                 (64U)
#define HW_SCE_TLS_HMAC_KEY_INDEX_WORD_SIZE                 (16U)

/* TLS-AES. */
#define HW_SCE_TLS_AES128_KEY_INDEX_WORD_SIZE               (12U)
#define HW_SCE_TLS_AES256_KEY_INDEX_WORD_SIZE               (16U)

/* Key update. */
#define HW_SCE_UPDATE_KEY_RING_INDEX_WORD_SIZE              (16U)

/* Firmware update. */
#define HW_SCE_FIRMWARE_MAC_BYTE_SIZE           (16U)
#if defined BSP_MCU_RX231 || defined BSP_MCU_RX23W
#define HW_SCE_SECURE_BOOT_AREA_TOP             (0xFFFF8000)
#else
#define HW_SCE_SECURE_BOOT_AREA_TOP             (0xFFFF0000)
#endif  /* defined BSP_MCU_RX231 || defined BSP_MCU_RX23W */

#define SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD                    (0)
#define SCE_OEM_KEY_SIZE_AES128_INST_DATA_WORD                   (8)
#define SCE_OEM_KEY_SIZE_AES192_INST_DATA_WORD                   (12)
#define SCE_OEM_KEY_SIZE_AES256_INST_DATA_WORD                   (12)
#define SCE_OEM_KEY_SIZE_AES128_XTS_INST_DATA_WORD               (12)
#define SCE_OEM_KEY_SIZE_AES256_XTS_INST_DATA_WORD               (20)

#define SCE_OEM_KEY_SIZE_RSA1024_PUBLICK_KEY_INST_DATA_WORD      (40)
#define SCE_OEM_KEY_SIZE_RSA1024_PRIVATE_KEY_INST_DATA_WORD      (68)
#define SCE_OEM_KEY_SIZE_RSA2048_PUBLICK_KEY_INST_DATA_WORD      (72)
#define SCE_OEM_KEY_SIZE_RSA2048_PRIVATE_KEY_INST_DATA_WORD      (132)
#define SCE_OEM_KEY_SIZE_RSA3072_PUBLICK_KEY_INST_DATA_WORD      (104)
#define SCE_OEM_KEY_SIZE_RSA3072_PRIVATE_KEY_INST_DATA_WORD      (196)
#define SCE_OEM_KEY_SIZE_RSA4096_PUBLICK_KEY_INST_DATA_WORD      (136)
#define SCE_OEM_KEY_SIZE_RSA4096_PRIVATE_KEY_INST_DATA_WORD      (260)

#define SCE_OEM_KEY_SIZE_ECCP192_PUBLICK_KEY_INST_DATA_WORD      (20)
#define SCE_OEM_KEY_SIZE_ECCP192_PRIVATE_KEY_INST_DATA_WORD      (12)
#define SCE_OEM_KEY_SIZE_ECCP224_PUBLICK_KEY_INST_DATA_WORD      (20)
#define SCE_OEM_KEY_SIZE_ECCP224_PRIVATE_KEY_INST_DATA_WORD      (12)
#define SCE_OEM_KEY_SIZE_ECCP256_PUBLICK_KEY_INST_DATA_WORD      (20)
#define SCE_OEM_KEY_SIZE_ECCP256_PRIVATE_KEY_INST_DATA_WORD      (12)
#define SCE_OEM_KEY_SIZE_ECCP384_PUBLICK_KEY_INST_DATA_WORD      (28)
#define SCE_OEM_KEY_SIZE_ECCP384_PRIVATE_KEY_INST_DATA_WORD      (16)
#define SCE_OEM_KEY_SIZE_HMAC_SHA224_INST_DATA_WORD              (12)
#define SCE_OEM_KEY_SIZE_HMAC_SHA256_INST_DATA_WORD              (12)
#define SCE_OEM_KEY_SIZE_ECCP256R1_PUBLICK_KEY_INST_DATA_WORD    (20)
#define SCE_OEM_KEY_SIZE_ECCP256R1_PRIVATE_KEY_INST_DATA_WORD    (12)
#define SCE_OEM_KEY_SIZE_ECCP384R1_PUBLICK_KEY_INST_DATA_WORD    (28)
#define SCE_OEM_KEY_SIZE_ECCP384R1_PRIVATE_KEY_INST_DATA_WORD    (16)
#define SCE_OEM_KEY_SIZE_ECCP512R1_PUBLICK_KEY_INST_DATA_WORD    (36)
#define SCE_OEM_KEY_SIZE_ECCP512R1_PRIVATE_KEY_INST_DATA_WORD    (20)
#define SCE_OEM_KEY_SIZE_ECCSECP256K1_PUBLICK_KEY_INST_DATA_WORD (20)
#define SCE_OEM_KEY_SIZE_ECCSECP256K1_PRIVATE_KEY_INST_DATA_WORD (12)

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/
/* request type for Callback of firmware update */
typedef enum
{
    SCE_FW_CB_REQ_PRG_WT = 0U,
    SCE_FW_CB_REQ_PRG_RD,
    SCE_FW_CB_REQ_BUFF_CNT,
    SCE_FW_CB_REQ_PRG_WT_LAST_BLK,
    SCE_FW_CB_REQ_GET_UPDATE_PRG_CHKSUM,
    SCE_FW_CB_REQ_STORE_MAC,
    
} SCE_FW_CB_REQ_TYPE;

/* key index type */
typedef enum
{
    SCE_KEY_INDEX_TYPE_INVALID = 0U,
    SCE_KEY_INDEX_TYPE_AES128,
    SCE_KEY_INDEX_TYPE_AES192,
    SCE_KEY_INDEX_TYPE_AES256,
    SCE_KEY_INDEX_TYPE_TDES,
    SCE_KEY_INDEX_TYPE_HMAC_SHA1,
    SCE_KEY_INDEX_TYPE_HMAC_SHA256,
    SCE_KEY_INDEX_TYPE_RSA1024_PUBLIC,
    SCE_KEY_INDEX_TYPE_RSA1024_PRIVATE,
    SCE_KEY_INDEX_TYPE_RSA2048_PUBLIC,
    SCE_KEY_INDEX_TYPE_RSA2048_PRIVATE,
    SCE_KEY_INDEX_TYPE_RSA3072_PUBLIC,
    SCE_KEY_INDEX_TYPE_RSA3072_PRIVATE,
    SCE_KEY_INDEX_TYPE_RSA4096_PUBLIC,
    SCE_KEY_INDEX_TYPE_RSA4096_PRIVATE,
    SCE_KEY_INDEX_TYPE_AES128_FOR_TLS,
    SCE_KEY_INDEX_TYPE_AES192_FOR_TLS,
    SCE_KEY_INDEX_TYPE_AES256_FOR_TLS,
    SCE_KEY_INDEX_TYPE_HMAC_SHA1_FOR_TLS,
    SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_TLS,
    SCE_KEY_INDEX_TYPE_UPDATE_KEY_RING,
    SCE_KEY_INDEX_TYPE_TLS_CA_CERTIFICATION_PUBLIC_KEY,
    SCE_KEY_INDEX_TYPE_TLS_P256_ECC_KEY,
    SCE_KEY_INDEX_TYPE_ECC_P192_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P224_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P256_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P384_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P192_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_P224_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_P256_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_P384_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_P256R1_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P384R1_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P256R1_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_P384R1_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_SECP256K1_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_SECP256K1_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECDH_SHARED_SECRET,
    SCE_KEY_INDEX_TYPE_AES128_XTS,
    SCE_KEY_INDEX_TYPE_AES256_XTS,
    SCE_KEY_INDEX_TYPE_AES128_GCM_FOR_DLMS_COSEM,
    SCE_KEY_INDEX_TYPE_AES128_KEY_WRAP_FOR_DLMS_COSEM,
    SCE_KEY_INDEX_TYPE_AES192_GCM_FOR_DLMS_COSEM,
    SCE_KEY_INDEX_TYPE_AES192_KEY_WRAP_FOR_DLMS_COSEM,
} SCE_KEY_INDEX_TYPE;

// added for RA6M4 start
/* LIFE CYCLE */
typedef enum
{
    SCE_CM1 = 0,
    SCE_CM2,
    SCE_SSD,
    SCE_NSECSD,
    SCE_DPL,
    SCE_LCK_DBG,
    SCE_LCK_BOOT,
    SCE_RMA_REQ,
    SCE_RMA_ACK,
} lifecycle_t;

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

// added for RA6M4 end

typedef enum e_sce_oem_key_type
{
    SCE_OEM_KEY_TYPE_ENCRYPTED = 0,
    SCE_OEM_KEY_TYPE_PLAIN     = 1
} sce_oem_key_type_t;

/* Byte data structure */
typedef struct sce_byte_data
{
    uint8_t     *pdata;
    uint32_t    data_length;
    uint32_t    data_type;
} sce_byte_data_t;

/* RSA byte data structure */
typedef sce_byte_data_t sce_rsa_byte_data_t;

/* ECDSA byte data structure */
typedef sce_byte_data_t sce_ecdsa_byte_data_t;

/* AES key index data structure */
typedef struct sce_aes_key_index
{
    uint32_t type;
    /* AES128, AES192, AES256, AES128 for TLS, AES256 for TLS, AES128 for XTS, AES256 for XTS  are supported */
    uint32_t value[HW_SCE_AES256XTS_KEY_INDEX_WORD_SIZE];
} sce_aes_key_index_t;

/* TDES key index data structure */
typedef struct sce_tdes_key_index
{
    uint32_t type;
    uint32_t value[HW_SCE_TDES_KEY_INDEX_WORD_SIZE];    /* DES/TDES are supported */
} sce_tdes_key_index_t;

/* HMAC-SHA key index data structure */
typedef struct sce_hmac_sha_key_index
{
    uint32_t type;
    /* HMAC-SHA1, HMAC-SHA256, HMAC-SHA for TLS, HMAC-SHA256 for TLS are supported */
    uint32_t value[HW_SCE_TLS_HMAC_KEY_INDEX_WORD_SIZE];
} sce_hmac_sha_key_index_t;

/* RSA 1024bit public key index data structure */
typedef struct sce_rsa1024_public_key_index
{
    uint32_t type;
    struct
    {
        uint32_t    key_management_info1[HW_SCE_RSA_1024_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE];
        uint8_t     key_n[HW_SCE_RSA_1024_KEY_N_LENGTH_BYTE_SIZE];       /* plaintext */
        uint8_t     key_e[HW_SCE_RSA_1024_KEY_E_LENGTH_BYTE_SIZE];       /* plaintext */
        uint8_t     dummy[HW_SCE_RSA_KEY_GENERATION_DUMMY_BYTE_SIZE];    /* dummy data */
        uint32_t    key_management_info2[HW_SCE_RSA_1024_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE];
    }
    value;
} sce_rsa1024_public_key_index_t;

/* RSA 1024bit private key index data structure */
typedef struct sce_rsa1024_private_key_index
{
    uint32_t type;
    struct
    {
        uint32_t    key_management_info1[HW_SCE_RSA_1024_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE];
        uint8_t     key_n[HW_SCE_RSA_1024_KEY_N_LENGTH_BYTE_SIZE];    /* plaintext */
        uint32_t    key_management_info2[HW_SCE_RSA_1024_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE];
    }
    value;
} sce_rsa1024_private_key_index_t;

/* RSA 2048bit public key index data structure */
typedef struct sce_rsa2048_public_key_index
{
    uint32_t type;
    struct
    {
        uint32_t    key_management_info1[HW_SCE_RSA_2048_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE];
        uint8_t     key_n[HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE];       /* plaintext */
        uint8_t     key_e[HW_SCE_RSA_2048_KEY_E_LENGTH_BYTE_SIZE];       /* plaintext */
        uint8_t     dummy[HW_SCE_RSA_KEY_GENERATION_DUMMY_BYTE_SIZE];    /* dummy data */
        uint32_t    key_management_info2[HW_SCE_RSA_2048_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE];
    }
    value;
    struct
    {
        uint8_t     key[HW_SCE_RSA2048_RANDOM_PUBLIC_KEY_BYTE_SIZE];
    }
    plain_value;
    
} sce_rsa2048_public_key_index_t;

/* RSA 2048bit private key index data structure */
typedef struct sce_rsa2048_private_key_index
{
    uint32_t type;
    struct
    {
        uint32_t    key_management_info1[HW_SCE_RSA_2048_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE];
        uint8_t     key_n[HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE];    /* plaintext */
        uint32_t    key_management_info2[HW_SCE_RSA_2048_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE];
    }
    value;
    struct
    {
        uint8_t     key[HW_SCE_RSA2048_RANDOM_PRIVATE_KEY_BYTE_SIZE];
    }
    plain_value;
} sce_rsa2048_private_key_index_t;

/* RSA 3072bit public key index data structure */
typedef struct sce_rsa3072_public_key_index
{
    uint32_t type;
    struct
    {
        uint32_t    key_management_info1[HW_SCE_RSA_3072_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE];
        uint8_t     key_n[HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE];       /* plaintext */
        uint8_t     key_e[HW_SCE_RSA_3072_KEY_E_LENGTH_BYTE_SIZE];       /* plaintext */
        uint8_t     dummy[HW_SCE_RSA_KEY_GENERATION_DUMMY_BYTE_SIZE];    /* dummy data */
        uint32_t    key_management_info2[HW_SCE_RSA_3072_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE];
    }
    value;
} sce_rsa3072_public_key_index_t;

/* RSA 3072bit private key index data structure */
typedef struct sce_rsa3072_private_key_index
{
    uint32_t type;
    struct
    {
        uint32_t    key_management_info1[HW_SCE_RSA_3072_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE];
        uint8_t     key_n[HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE];    /* plaintext */
        uint32_t    key_management_info2[HW_SCE_RSA_3072_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE];
    }
    value;
} sce_rsa3072_private_key_index_t;

/* RSA 4096bit public key index data structure */
typedef struct sce_rsa4096_public_key_index
{
    uint32_t type;
    struct
    {
        uint32_t    key_management_info1[HW_SCE_RSA_4096_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE];
        uint8_t     key_n[HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE];       /* plaintext */
        uint8_t     key_e[HW_SCE_RSA_4096_KEY_E_LENGTH_BYTE_SIZE];       /* plaintext */
        uint8_t     dummy[HW_SCE_RSA_KEY_GENERATION_DUMMY_BYTE_SIZE];    /* dummy data */
        uint32_t    key_management_info2[HW_SCE_RSA_4096_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE];
    }
    value;
} sce_rsa4096_public_key_index_t;

/* RSA 4096bit private key index data structure */
typedef struct sce_rsa4096_private_key_index
{
    uint32_t type;
    struct
    {
        uint32_t    key_management_info1[HW_SCE_RSA_4096_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE];
        uint8_t     key_n[HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE];    /* plaintext */
        uint32_t    key_management_info2[HW_SCE_RSA_4096_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE];
    }
    value;
} sce_rsa4096_private_key_index_t;

/* RSA 1024bit key index pair structure */
typedef struct sce_rsa1024_key_pair_index
{
    sce_rsa1024_private_key_index_t    priv_key;
    sce_rsa1024_public_key_index_t     pub_key;
} sce_rsa1024_key_pair_index_t;

/* RSA 2048bit key index pair structure */
typedef struct sce_rsa2048_key_pair_index
{
    sce_rsa2048_private_key_index_t    priv_key;
    sce_rsa2048_public_key_index_t     pub_key;
} sce_rsa2048_key_pair_index_t;

/* RSA 3072bit key index pair structure */
typedef struct sce_rsa3072_key_pair_index
{
    sce_rsa3072_private_key_index_t    priv_key;
    sce_rsa3072_public_key_index_t     pub_key;
} sce_rsa3072_key_pair_index_t;

/* RSA 4096bit key index pair structure */
typedef struct sce_rsa4096_key_pair_index
{
    sce_rsa4096_private_key_index_t    priv_key;
    sce_rsa4096_public_key_index_t     pub_key;
} sce_rsa4096_key_pair_index_t;

/* ECC P-192/224/256 public key index data structure */
typedef struct sce_ecc_public_key_index
{
    uint32_t type;
    struct
    {
        uint32_t    key_management_info1[HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE];
        uint8_t     key_q[HW_SCE_ECC_P192_P224_P256_PUBLIC_KEY_BYTE_SIZE];
        uint32_t    key_management_info2[HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE];
    }
    value;
    struct
    {
        uint8_t     key[HW_SCE_ECC_P192_P224_P256_PUBLIC_KEY_BYTE_SIZE];
    }
    plain_value;
} sce_ecc_public_key_index_t;

/* ECC P-384 public key index data structure */
typedef struct sce_ecc384_public_key_index
{
    uint32_t type;
    struct
    {
        uint32_t    key_management_info1[HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE];
        uint8_t     key_q[HW_SCE_ECC_P384_PUBLIC_KEY_BYTE_SIZE];
        uint32_t    key_management_info2[HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE];
    }
    value;
    struct
    {
        uint8_t     key[HW_SCE_ECC_P384_PUBLIC_KEY_BYTE_SIZE];
    }
    plain_value;
} sce_ecc384_public_key_index_t;

/* ECC P-192/224/256 private key index data structure */
typedef struct sce_ecc_private_key_index
{
    uint32_t type;
    uint32_t value[HW_SCE_ECC_PRIVATE_KEY_MANAGEMENT_INFO_WORD_SIZE];
} sce_ecc_private_key_index_t;

/* ECC P-192/224/256 key index pair structure */
typedef struct sce_ecc_key_pair_index
{
    sce_ecc_private_key_index_t    priv_key;
    sce_ecc_public_key_index_t     pub_key;
} sce_ecc_key_pair_index_t;

/* ECDH key index data structure */
typedef struct sce_ecdh_key_index
{
    uint32_t type;
    uint32_t value[HW_SCE_SHARED_SECRET_KEY_INDEX_WORD_SIZE];
} sce_ecdh_key_index_t;

/* TLS CA certification public key index data structure */
typedef struct sce_tls_ca_certification_public_key_index
{
    uint32_t type;
    uint32_t value[HW_SCE_TLS_ROOT_PUBLIC_KEY_WORD_SIZE];
} sce_tls_ca_certification_public_key_index_t;

/* TLS P-256 ECC key index data structure */
typedef struct sce_tls_p256_ecc_key_index
{
    uint32_t type;
    uint32_t value[HW_SCE_TLS_P256_ECC_KEY_WORD_SIZE];
} sce_tls_p256_ecc_key_index_t;

/* Update key ring index data structure */
typedef struct sce_update_key_ring
{
    uint32_t type;
    uint32_t value[HW_SCE_UPDATE_KEY_RING_INDEX_WORD_SIZE];
} sce_update_key_ring_t;


/* The work area for AES */
typedef struct sce_aes_handle
{
    uint32_t                id;
    sce_aes_key_index_t     key_index;
    uint32_t                current_input_data_size;
    uint8_t                 last_1_block_as_fraction[HW_SCE_AES_BLOCK_BYTE_SIZE];
    uint8_t                 last_2_block_as_fraction[HW_SCE_AES_BLOCK_BYTE_SIZE * 2];
    uint8_t                 current_ivec[HW_SCE_AES_CBC_IV_BYTE_SIZE];
    uint8_t                 current_icounter[HW_SCE_AES_CTR_ICOUNTER_BYTE_SIZE];
    uint8_t                 flag_call_init;
} sce_aes_handle_t;

/* The work area for TDES */
typedef struct sce_tdes_handle
{
    uint32_t                id;
    sce_tdes_key_index_t   key_index;
    uint32_t                current_input_data_size;
    uint8_t                 last_1_block_as_fraction[HW_SCE_TDES_BLOCK_BYTE_SIZE];
    uint8_t                 current_ivec[HW_SCE_TDES_CBC_IV_BYTE_SIZE*2];
    uint8_t                 flag_call_init;
} sce_tdes_handle_t;

/* The work area for MD5 */
typedef struct sce_sha_md5_handle
{
    uint32_t id;
    uint8_t  sha_buffer[HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE * 4];
    uint32_t all_received_length;
    uint32_t buffering_length;
    /* SHA1(20byte), SHA256(32byte), MD5(16byte) are supported */
    uint8_t  current_hash[HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE];
    uint8_t  flag_call_init;
} sce_sha_md5_handle_t;

/* The work area for HMAC-SHA */
typedef struct sce_hmac_sha_handle
{
    uint32_t                    id;
    sce_hmac_sha_key_index_t   key_index;
    uint8_t                     hmac_buffer[HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE * 4];
    uint32_t                    all_received_length;
    uint32_t                    buffering_length;
    uint8_t                     flag_call_init;
} sce_hmac_sha_handle_t;

/* The work area for CMAC */
typedef struct sce_cmac_handle
{
    uint32_t                id;
    sce_aes_key_index_t    key_index;
    uint8_t                 cmac_buffer[HW_SCE_AES_BLOCK_BYTE_SIZE];
    uint32_t                all_received_length;
    uint32_t                buffering_length;
    uint8_t                 flag_call_init;
} sce_cmac_handle_t;

/* The work area for GCM */
typedef struct sce_gcm_handle
{
    uint32_t                id;
    sce_aes_key_index_t    key_index;
    uint8_t                 gcm_buffer[HW_SCE_AES_BLOCK_BYTE_SIZE];
    uint8_t                 gcm_aad_buffer[HW_SCE_AES_GCM_AAD_BLOCK_BYTE_SIZE];
    uint32_t                all_received_length;
    uint32_t                all_received_aad_length;
    uint32_t                buffering_length;
    uint32_t                buffering_aad_length;
    uint8_t                 flag_call_init;
    uint8_t                 flag_update_input_data;
} sce_gcm_handle_t;

/* The work area for CCM */
typedef struct sce_ccm_handle
{
    uint32_t                id;
    sce_aes_key_index_t    key_index;
    uint8_t                 formatted_data[HW_SCE_AES_CCM_B_FORMAT_BYTE_SIZE];
    uint8_t                 counter[HW_SCE_AES_CCM_COUNTER_BYTE_SIZE];
    uint8_t                 ccm_buffer[HW_SCE_AES_BLOCK_BYTE_SIZE];
    uint32_t                all_received_length;
    uint32_t                buffering_length;
    uint8_t                 flag_call_init;
} sce_ccm_handle_t;

/* The work area for ECDH */
typedef struct sce_ecdh_handle
{
    uint32_t                id;
    uint32_t                flag_use_key_id;
    uint32_t                key_id;
    uint32_t                key_type;
    uint8_t                 flag_call_init;
    uint8_t                 flag_call_make_public;
    uint8_t                 flag_call_read_public;
    uint8_t                 flag_call_shared_secret;
} sce_ecdh_handle_t;

/* The work area for firmware update */
typedef struct sce_firmware_generate_mac_resume_handle
{
    uint32_t iLoop;
    uint32_t counter;
    uint32_t previous_counter;
    bool     use_resume_flag;
} sce_firmware_generate_mac_resume_handle_t;

/* The callback function pointer type for HW_SCE_GenerateFirmwareMAC */
typedef void (*SCE_GEN_MAC_CB_FUNC_T) (SCE_FW_CB_REQ_TYPE req_type, uint32_t iLoop, uint32_t *counter,
        uint32_t *InData_UpProgram, uint32_t *OutData_Program, uint32_t MAX_CNT);

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/
fsp_err_t HW_SCE_Open(lifecycle_t lifecycle, sce_tls_ca_certification_public_key_index_t *key_index_1,
        sce_update_key_ring_t *key_index_2);
fsp_err_t HW_SCE_Close(void);
void HW_SCE_SoftwareReset(void);
fsp_err_t HW_SCE_SelfCheck2(void);
fsp_err_t HW_SCE_SelfCheck3(void);

// added for RA6M4 start
fsp_err_t HW_SCE_FwIntegrityCheck(void);
fsp_err_t HW_SCE_UpdateOemKeyIndex(lifecycle_t lifecycle, sce_oem_cmd_t key_type, uint8_t *iv, uint8_t *encrypted_oem_key, uint32_t *key_index);

// added for RA6M4 end

fsp_err_t HW_SCE_GenerateAes128KeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv, uint8_t *encrypted_key,
        sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateAes192KeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv, uint8_t *encrypted_key,
        sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateAes256KeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv, uint8_t *encrypted_key,
        sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateTdesKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv, uint8_t *encrypted_key,
        sce_tdes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa1024PublicKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_rsa1024_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa1024PrivateKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_rsa1024_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa2048PublicKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_rsa2048_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa2048PrivateKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_rsa2048_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa3072PublicKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_rsa3072_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa3072PrivateKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_rsa3072_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa4096PublicKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_rsa4096_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa4096PrivateKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_rsa4096_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateTlsRsaPublicKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_tls_ca_certification_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP192PublicKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP224PublicKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP256PublicKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP384PublicKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP192PrivateKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP224PrivateKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP256PrivateKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP384PrivateKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateSha1HmacKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_hmac_sha_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateSha256HmacKeyIndex(uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_hmac_sha_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateTlsP256EccKeyIndex(sce_tls_p256_ecc_key_index_t *tls_p256_ecc_key_index,
        uint8_t *ephemeral_ecdh_public_key);
fsp_err_t HW_SCE_GenerateAes128RandomKeyIndex(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateAes192RandomKeyIndex(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateAes256RandomKeyIndex(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateAes128XtsRandomKeyIndex(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateAes256XtsRandomKeyIndex(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa1024RandomKeyIndex(sce_rsa1024_key_pair_index_t *key_pair_index);
fsp_err_t HW_SCE_GenerateRsa2048RandomKeyIndex(sce_rsa2048_key_pair_index_t *key_pair_index);
fsp_err_t HW_SCE_GenerateRsa3072RandomKeyIndex(sce_rsa3072_key_pair_index_t *key_pair_index);
fsp_err_t HW_SCE_GenerateRsa4096RandomKeyIndex(sce_rsa4096_key_pair_index_t *key_pair_index);
fsp_err_t HW_SCE_GenerateTdesRandomKeyIndex(sce_tdes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP192RandomKeyIndex(uint32_t *indata_curvetype, sce_ecc_key_pair_index_t *key_pair_index);
fsp_err_t HW_SCE_GenerateEccP224RandomKeyIndex(uint32_t *indata_curvetype, sce_ecc_key_pair_index_t *key_pair_index);
fsp_err_t HW_SCE_GenerateEccP256RandomKeyIndex(uint32_t *indata_curvetype, sce_ecc_key_pair_index_t *key_pair_index);
fsp_err_t HW_SCE_GenerateEccP384RandomKeyIndex(uint32_t *indata_curvetype, sce_ecc_key_pair_index_t *key_pair_index);
fsp_err_t HW_SCE_GenerateRandomNumber(uint32_t *random);
fsp_err_t HW_SCE_GenerateUpdateKeyRingKeyIndex(lifecycle_t lifecycle, uint8_t *encrypted_provisioning_key, uint8_t *iv,
        uint8_t *encrypted_key, sce_update_key_ring_t *key_index);
uint32_t HW_SCE_GetVersion(void);

fsp_err_t HW_SCE_GenerateAes128PlainKeyIndex(uint8_t *plain_key, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateAes192PlainKeyIndex(uint8_t *plain_key, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateAes256PlainKeyIndex(uint8_t *plain_key, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateAes128XtsPlainKeyIndex(uint8_t *plain_key, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateAes256XtsPlainKeyIndex(uint8_t *plain_key, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa2048PublicPlainKeyIndex(uint8_t *plain_key, sce_rsa2048_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa2048PrivatePlainKeyIndex(uint8_t *plain_key, sce_rsa2048_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa3072PublicPlainKeyIndex(uint8_t *plain_key, sce_rsa3072_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa3072PrivatePlainKeyIndex(uint8_t *plain_key, sce_rsa3072_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa4096PublicPlainKeyIndex(uint8_t *plain_key, sce_rsa4096_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateRsa4096PrivatePlainKeyIndex(uint8_t *plain_key, sce_rsa4096_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP224PublicPlainKeyIndex(uint8_t *plain_key, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP256PublicPlainKeyIndex(uint8_t *plain_key, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP384PublicPlainKeyIndex(uint8_t *plain_key, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP224PrivatePlainKeyIndex(uint8_t *plain_key, sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP256PrivatePlainKeyIndex(uint8_t *plain_key, sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP384PrivatePlainKeyIndex(uint8_t *plain_key, sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateSha256HmacPlainKeyIndex(uint8_t *plain_key, sce_hmac_sha_key_index_t *key_index);

fsp_err_t HW_SCE_GenerateEccP256r1PublicPlainKeyIndex(uint8_t *plain_key, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP384r1PublicPlainKeyIndex(uint8_t *plain_key, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP256r1PrivatePlainKeyIndex(uint8_t *plain_key, sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccP384r1PrivatePlainKeyIndex(uint8_t *plain_key, sce_ecc_private_key_index_t *key_index);

fsp_err_t HW_SCE_GenerateEccSecp256k1PublicPlainKeyIndex(uint8_t *plain_key, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_GenerateEccSecp256k1PrivatePlainKeyIndex(uint8_t *plain_key, sce_ecc_private_key_index_t *key_index);

fsp_err_t HW_SCE_UpdateAes128KeyIndex(lifecycle_t lifecycle, uint8_t *iv, uint8_t *encrypted_key, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateAes192KeyIndex(lifecycle_t lifecycle, uint8_t *iv, uint8_t *encrypted_key, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateAes256KeyIndex(lifecycle_t lifecycle, uint8_t *iv, uint8_t *encrypted_key, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateAes128XtsKeyIndex(lifecycle_t lifecycle, uint8_t *iv, uint8_t *encrypted_key, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateAes256XtsKeyIndex(lifecycle_t lifecycle, uint8_t *iv, uint8_t *encrypted_key, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateTdesKeyIndex(uint8_t *iv, uint8_t *encrypted_key, sce_tdes_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateRsa1024PublicKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_rsa1024_public_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateRsa1024PrivateKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_rsa1024_private_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateRsa2048PublicKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_rsa2048_public_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateRsa2048PrivateKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_rsa2048_private_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateRsa3072PublicKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_rsa3072_public_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateRsa3072PrivateKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_rsa3072_private_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateRsa4096PublicKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_rsa4096_public_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateRsa4096PrivateKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_rsa4096_private_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateTlsRsaPublicKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_tls_ca_certification_public_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateEccP192PublicKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateEccP224PublicKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateEccP256PublicKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateEccP384PublicKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateEccP192PrivateKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateEccP224PrivateKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateEccP256PrivateKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateEccP384PrivateKeyIndex(uint8_t *iv, uint8_t *encrypted_key,
        sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_Ecc256ScalarMultiplication(uint32_t *InData_CurveType, uint32_t *InData_Cmd,
        uint32_t *InData_KeyIndex, uint32_t *InData_PubKey, uint32_t *OutData_R);
fsp_err_t HW_SCE_Ecc384ScalarMultiplication(uint32_t *InData_CurveType,
        uint32_t *InData_KeyIndex, uint32_t *InData_PubKey, uint32_t *OutData_R);
fsp_err_t HW_SCE_UpdateSha1HmacKeyIndex(uint8_t *iv, uint8_t *encrypted_key, sce_hmac_sha_key_index_t *key_index);
fsp_err_t HW_SCE_UpdateSha256HmacKeyIndex(uint8_t *iv, uint8_t *encrypted_key, sce_hmac_sha_key_index_t *key_index);

fsp_err_t HW_SCE_StartUpdateFirmware(void);
fsp_err_t HW_SCE_GenerateFirmwareMAC(uint32_t *InData_KeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_UpProgram, uint32_t *InData_IV, uint32_t *OutData_Program, uint32_t MAX_CNT,
        SCE_GEN_MAC_CB_FUNC_T p_callback,
        sce_firmware_generate_mac_resume_handle_t *sce_firmware_generate_mac_resume_handle);
fsp_err_t HW_SCE_VerifyFirmwareMAC(uint32_t *InData_Program, uint32_t MAX_CNT, uint32_t *InData_MAC);

fsp_err_t HW_SCE_Aes128EcbEncryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes128EcbEncryptUpdate(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes128EcbEncryptFinal(sce_aes_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length);
fsp_err_t HW_SCE_Aes128EcbDecryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes128EcbDecryptUpdate(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes128EcbDecryptFinal(sce_aes_handle_t *handle, uint8_t *plain, uint32_t *plain_length);
fsp_err_t HW_SCE_Aes128CbcEncryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_Aes128CbcEncryptUpdate(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes128CbcEncryptFinal(sce_aes_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length);
fsp_err_t HW_SCE_Aes128CbcDecryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_Aes128CbcDecryptUpdate(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes128CbcDecryptFinal(sce_aes_handle_t *handle, uint8_t *plain, uint32_t *plain_length);

fsp_err_t HW_SCE_Aes192EcbEncryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes192EcbEncryptUpdate(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes192EcbEncryptFinal(sce_aes_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length);
fsp_err_t HW_SCE_Aes192EcbDecryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes192EcbDecryptUpdate(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes192EcbDecryptFinal(sce_aes_handle_t *handle, uint8_t *plain, uint32_t *plain_length);
fsp_err_t HW_SCE_Aes192CbcEncryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_Aes192CbcEncryptUpdate(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes192CbcEncryptFinal(sce_aes_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length);
fsp_err_t HW_SCE_Aes192CbcDecryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_Aes192CbcDecryptUpdate(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes192CbcDecryptFinal(sce_aes_handle_t *handle, uint8_t *plain, uint32_t *plain_length);

fsp_err_t HW_SCE_Aes256EcbEncryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes256EcbEncryptUpdate(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes256EcbEncryptFinal(sce_aes_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length);
fsp_err_t HW_SCE_Aes256EcbDecryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes256EcbDecryptUpdate(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes256EcbDecryptFinal(sce_aes_handle_t *handle, uint8_t *plain, uint32_t *plain_length);
fsp_err_t HW_SCE_Aes256CbcEncryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_Aes256CbcEncryptUpdate(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes256CbcEncryptFinal(sce_aes_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length);
fsp_err_t HW_SCE_Aes256CbcDecryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_Aes256CbcDecryptUpdate(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes256CbcDecryptFinal(sce_aes_handle_t *handle, uint8_t *plain, uint32_t *plain_length);

fsp_err_t HW_SCE_Aes128CtrEncryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *icounter);
fsp_err_t HW_SCE_Aes128CtrEncryptUpdate(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes128CtrEncryptFinal(sce_aes_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length);
fsp_err_t HW_SCE_Aes128CtrDecryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *icounter);
fsp_err_t HW_SCE_Aes128CtrDecryptUpdate(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes128CtrDecryptFinal(sce_aes_handle_t *handle, uint8_t *plain, uint32_t *plain_length);

fsp_err_t HW_SCE_Aes192CtrEncryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *icounter);
fsp_err_t HW_SCE_Aes192CtrEncryptUpdate(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes192CtrEncryptFinal(sce_aes_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length);
fsp_err_t HW_SCE_Aes192CtrDecryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *icounter);
fsp_err_t HW_SCE_Aes192CtrDecryptUpdate(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes192CtrDecryptFinal(sce_aes_handle_t *handle, uint8_t *plain, uint32_t *plain_length);

fsp_err_t HW_SCE_Aes256CtrEncryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *icounter);
fsp_err_t HW_SCE_Aes256CtrEncryptUpdate(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes256CtrEncryptFinal(sce_aes_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length);
fsp_err_t HW_SCE_Aes256CtrDecryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *icounter);
fsp_err_t HW_SCE_Aes256CtrDecryptUpdate(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes256CtrDecryptFinal(sce_aes_handle_t *handle, uint8_t *plain, uint32_t *plain_length);

fsp_err_t HW_SCE_Aes128XtsEncryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_Aes128XtsEncryptUpdate(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t text_bitlen);
fsp_err_t HW_SCE_Aes128XtsEncryptFinal(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t text_bitlen);
fsp_err_t HW_SCE_Aes128XtsDecryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_Aes128XtsDecryptUpdate(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t text_bitlen);
fsp_err_t HW_SCE_Aes128XtsDecryptFinal(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t text_bitlen);
fsp_err_t HW_SCE_Aes256XtsEncryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_Aes256XtsEncryptUpdate(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t text_bitlen);
fsp_err_t HW_SCE_Aes256XtsEncryptFinal(sce_aes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t text_bitlen);
fsp_err_t HW_SCE_Aes256XtsDecryptInit(sce_aes_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_Aes256XtsDecryptUpdate(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t text_bitlen);
fsp_err_t HW_SCE_Aes256XtsDecryptFinal(sce_aes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t text_bitlen);

fsp_err_t HW_SCE_Aes128GcmEncryptInit(sce_gcm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec,
        uint32_t ivec_len);
fsp_err_t HW_SCE_Aes128GcmEncryptUpdate(sce_gcm_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_data_len, uint8_t *aad, uint32_t aad_len);
fsp_err_t HW_SCE_Aes128GcmEncryptFinal(sce_gcm_handle_t *handle, uint8_t *cipher, uint32_t *cipher_data_len,
        uint8_t *atag);
fsp_err_t HW_SCE_Aes128GcmDecryptInit(sce_gcm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec,
        uint32_t ivec_len);
fsp_err_t HW_SCE_Aes128GcmDecryptUpdate(sce_gcm_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_data_len, uint8_t *aad, uint32_t aad_len);
fsp_err_t HW_SCE_Aes128GcmDecryptFinal(sce_gcm_handle_t *handle, uint8_t *plain, uint32_t *plain_data_len,
        uint8_t *atag, uint32_t atag_len);

fsp_err_t HW_SCE_Aes192GcmEncryptInit(sce_gcm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec,
        uint32_t ivec_len);
fsp_err_t HW_SCE_Aes192GcmEncryptUpdate(sce_gcm_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_data_len, uint8_t *aad, uint32_t aad_len);
fsp_err_t HW_SCE_Aes192GcmEncryptFinal(sce_gcm_handle_t *handle, uint8_t *cipher, uint32_t *cipher_data_len,
        uint8_t *atag);
fsp_err_t HW_SCE_Aes192GcmDecryptInit(sce_gcm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec,
        uint32_t ivec_len);
fsp_err_t HW_SCE_Aes192GcmDecryptUpdate(sce_gcm_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_data_len, uint8_t *aad, uint32_t aad_len);
fsp_err_t HW_SCE_Aes192GcmDecryptFinal(sce_gcm_handle_t *handle, uint8_t *plain, uint32_t *plain_data_len,
        uint8_t *atag, uint32_t atag_len);

fsp_err_t HW_SCE_Aes256GcmEncryptInit(sce_gcm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec,
        uint32_t ivec_len);
fsp_err_t HW_SCE_Aes256GcmEncryptUpdate(sce_gcm_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_data_len, uint8_t *aad, uint32_t aad_len);
fsp_err_t HW_SCE_Aes256GcmEncryptFinal(sce_gcm_handle_t *handle, uint8_t *cipher, uint32_t *cipher_data_len,
        uint8_t *atag);
fsp_err_t HW_SCE_Aes256GcmDecryptInit(sce_gcm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *ivec,
        uint32_t ivec_len);
fsp_err_t HW_SCE_Aes256GcmDecryptUpdate(sce_gcm_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_data_len, uint8_t *aad, uint32_t aad_len);
fsp_err_t HW_SCE_Aes256GcmDecryptFinal(sce_gcm_handle_t *handle, uint8_t *plain, uint32_t *plain_data_len,
        uint8_t *atag, uint32_t atag_len);

fsp_err_t HW_SCE_Aes128CcmEncryptInit(sce_ccm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *nonce,
        uint32_t nonce_len, uint8_t *adata, uint8_t a_len, uint32_t payload_len, uint32_t mac_len);
fsp_err_t HW_SCE_Aes128CcmEncryptUpdate(sce_ccm_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes128CcmEncryptFinal(sce_ccm_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length,
        uint8_t *mac, uint32_t mac_length);
fsp_err_t HW_SCE_Aes128CcmDecryptInit(sce_ccm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *nonce,
        uint32_t nonce_len, uint8_t *adata, uint8_t a_len, uint32_t payload_len, uint32_t mac_len);
fsp_err_t HW_SCE_Aes128CcmDecryptUpdate(sce_ccm_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes128CcmDecryptFinal(sce_ccm_handle_t *handle, uint8_t *plain, uint32_t *plain_length,
        uint8_t *mac, uint32_t mac_length);

fsp_err_t HW_SCE_Aes192CcmEncryptInit(sce_ccm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *nonce,
        uint32_t nonce_len, uint8_t *adata, uint8_t a_len, uint32_t payload_len, uint32_t mac_len);
fsp_err_t HW_SCE_Aes192CcmEncryptUpdate(sce_ccm_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes192CcmEncryptFinal(sce_ccm_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length,
        uint8_t *mac, uint32_t mac_length);
fsp_err_t HW_SCE_Aes192CcmDecryptInit(sce_ccm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *nonce,
        uint32_t nonce_len, uint8_t *adata, uint8_t a_len, uint32_t payload_len, uint32_t mac_len);
fsp_err_t HW_SCE_Aes192CcmDecryptUpdate(sce_ccm_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes192CcmDecryptFinal(sce_ccm_handle_t *handle, uint8_t *plain, uint32_t *plain_length,
        uint8_t *mac, uint32_t mac_length);

fsp_err_t HW_SCE_Aes256CcmEncryptInit(sce_ccm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *nonce,
        uint32_t nonce_len, uint8_t *adata, uint8_t a_len, uint32_t payload_len, uint32_t mac_len);
fsp_err_t HW_SCE_Aes256CcmEncryptUpdate(sce_ccm_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_Aes256CcmEncryptFinal(sce_ccm_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length,
        uint8_t *mac, uint32_t mac_length);
fsp_err_t HW_SCE_Aes256CcmDecryptInit(sce_ccm_handle_t *handle, sce_aes_key_index_t *key_index, uint8_t *nonce,
        uint32_t nonce_len, uint8_t *adata, uint8_t a_len, uint32_t payload_len, uint32_t mac_len);
fsp_err_t HW_SCE_Aes256CcmDecryptUpdate(sce_ccm_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_Aes256CcmDecryptFinal(sce_ccm_handle_t *handle, uint8_t *plain, uint32_t *plain_length,
        uint8_t *mac, uint32_t mac_length);

fsp_err_t HW_SCE_Aes128CmacGenerateInit(sce_cmac_handle_t *handle, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes128CmacGenerateUpdate(sce_cmac_handle_t *handle, uint8_t *message, uint32_t message_length);
fsp_err_t HW_SCE_Aes128CmacGenerateFinal(sce_cmac_handle_t *handle, uint8_t *mac);
fsp_err_t HW_SCE_Aes128CmacVerifyInit(sce_cmac_handle_t *handle, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes128CmacVerifyUpdate(sce_cmac_handle_t *handle, uint8_t *message, uint32_t message_length);
fsp_err_t HW_SCE_Aes128CmacVerifyFinal(sce_cmac_handle_t *handle, uint8_t *mac, uint32_t mac_length);
fsp_err_t HW_SCE_Aes256CmacGenerateInit(sce_cmac_handle_t *handle, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes256CmacGenerateUpdate(sce_cmac_handle_t *handle, uint8_t *message, uint32_t message_length);
fsp_err_t HW_SCE_Aes256CmacGenerateFinal(sce_cmac_handle_t *handle, uint8_t *mac);
fsp_err_t HW_SCE_Aes256CmacVerifyInit(sce_cmac_handle_t *handle, sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes256CmacVerifyUpdate(sce_cmac_handle_t *handle, uint8_t *message, uint32_t message_length);
fsp_err_t HW_SCE_Aes256CmacVerifyFinal(sce_cmac_handle_t *handle, uint8_t *mac, uint32_t mac_length);

fsp_err_t HW_SCE_TdesEcbEncryptInit(sce_tdes_handle_t *handle, sce_tdes_key_index_t *key_index);
fsp_err_t HW_SCE_TdesEcbEncryptUpdate(sce_tdes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_TdesEcbEncryptFinal(sce_tdes_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length);
fsp_err_t HW_SCE_TdesEcbDecryptInit(sce_tdes_handle_t *handle, sce_tdes_key_index_t *key_index);
fsp_err_t HW_SCE_TdesEcbDecryptUpdate(sce_tdes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_TdesEcbDecryptFinal(sce_tdes_handle_t *handle, uint8_t *plain, uint32_t *plain_length);
fsp_err_t HW_SCE_TdesCbcEncryptInit(sce_tdes_handle_t *handle, sce_tdes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_TdesCbcEncryptUpdate(sce_tdes_handle_t *handle, uint8_t *plain, uint8_t *cipher,
        uint32_t plain_length);
fsp_err_t HW_SCE_TdesCbcEncryptFinal(sce_tdes_handle_t *handle, uint8_t *cipher, uint32_t *cipher_length);
fsp_err_t HW_SCE_TdesCbcDecryptInit(sce_tdes_handle_t *handle, sce_tdes_key_index_t *key_index, uint8_t *ivec);
fsp_err_t HW_SCE_TdesCbcDecryptUpdate(sce_tdes_handle_t *handle, uint8_t *cipher, uint8_t *plain,
        uint32_t cipher_length);
fsp_err_t HW_SCE_TdesCbcDecryptFinal(sce_tdes_handle_t *handle, uint8_t *plain, uint32_t *plain_length);

fsp_err_t HW_SCE_Md5Init(sce_sha_md5_handle_t *handle);
fsp_err_t HW_SCE_Md5Update(sce_sha_md5_handle_t *handle, uint8_t *message, uint32_t message_length);
fsp_err_t HW_SCE_Md5Final(sce_sha_md5_handle_t *handle, uint8_t *digest, uint32_t *digest_length);

fsp_err_t HW_SCE_Sha1Init(sce_sha_md5_handle_t *handle);
fsp_err_t HW_SCE_Sha1Update(sce_sha_md5_handle_t *handle, uint8_t *message, uint32_t message_length);
fsp_err_t HW_SCE_Sha1Final(sce_sha_md5_handle_t *handle, uint8_t *digest, uint32_t *digest_length);
fsp_err_t HW_SCE_Sha256Init(sce_sha_md5_handle_t *handle);
fsp_err_t HW_SCE_Sha256Update(sce_sha_md5_handle_t *handle, uint8_t *message, uint32_t message_length);
fsp_err_t HW_SCE_Sha256Final(sce_sha_md5_handle_t *handle, uint8_t *digest, uint32_t *digest_length);

fsp_err_t HW_SCE_Sha1HmacGenerateInit(sce_hmac_sha_handle_t *handle, sce_hmac_sha_key_index_t *key_index);
fsp_err_t HW_SCE_Sha1HmacGenerateUpdate(sce_hmac_sha_handle_t *handle, uint8_t *message, uint32_t message_length);
fsp_err_t HW_SCE_Sha1HmacGenerateFinal(sce_hmac_sha_handle_t *handle, uint8_t *mac);
fsp_err_t HW_SCE_Sha256HmacGenerateInit(sce_hmac_sha_handle_t *handle, sce_hmac_sha_key_index_t *key_index);
fsp_err_t HW_SCE_Sha256HmacGenerateUpdate(sce_hmac_sha_handle_t *handle, uint8_t *message,
        uint32_t message_length);
fsp_err_t HW_SCE_Sha256HmacGenerateFinal(sce_hmac_sha_handle_t *handle, uint8_t *mac);
fsp_err_t HW_SCE_Sha1HmacVerifyInit(sce_hmac_sha_handle_t *handle, sce_hmac_sha_key_index_t *key_index);
fsp_err_t HW_SCE_Sha1HmacVerifyUpdate(sce_hmac_sha_handle_t *handle, uint8_t *message, uint32_t message_length);
fsp_err_t HW_SCE_Sha1HmacVerifyFinal(sce_hmac_sha_handle_t *handle, uint8_t *mac, uint32_t mac_length);
fsp_err_t HW_SCE_Sha256HmacVerifyInit(sce_hmac_sha_handle_t *handle, sce_hmac_sha_key_index_t *key_index);
fsp_err_t HW_SCE_Sha256HmacVerifyUpdate(sce_hmac_sha_handle_t *handle, uint8_t *message, uint32_t message_length);
fsp_err_t HW_SCE_Sha256HmacVerifyFinal(sce_hmac_sha_handle_t *handle, uint8_t *mac, uint32_t mac_length);

fsp_err_t HW_SCE_RsassaPkcs1024SignatureGenerate(sce_rsa_byte_data_t *message_hash,
        sce_rsa_byte_data_t *signature, sce_rsa1024_private_key_index_t *key_index, uint8_t hash_type);
fsp_err_t HW_SCE_RsassaPkcs1024SignatureVerification(sce_rsa_byte_data_t *signature,
        sce_rsa_byte_data_t *message_hash, sce_rsa1024_public_key_index_t *key_index, uint8_t hash_type);
fsp_err_t HW_SCE_RsassaPkcs2048SignatureGenerate(sce_rsa_byte_data_t *message_hash,
        sce_rsa_byte_data_t *signature, sce_rsa2048_private_key_index_t *key_index, uint8_t hash_type);
fsp_err_t HW_SCE_RsassaPkcs2048SignatureVerification(sce_rsa_byte_data_t *signature,
        sce_rsa_byte_data_t *message_hash, sce_rsa2048_public_key_index_t *key_index, uint8_t hash_type);
fsp_err_t HW_SCE_RsassaPkcs3072SignatureGenerate(sce_rsa_byte_data_t *message_hash,
        sce_rsa_byte_data_t *signature, sce_rsa3072_private_key_index_t *key_index, uint8_t hash_type);
fsp_err_t HW_SCE_RsassaPkcs3072SignatureVerification(sce_rsa_byte_data_t *signature,
        sce_rsa_byte_data_t *message_hash, sce_rsa3072_public_key_index_t *key_index, uint8_t hash_type);
fsp_err_t HW_SCE_RsassaPkcs4096SignatureGenerate(sce_rsa_byte_data_t *message_hash,
        sce_rsa_byte_data_t *signature, sce_rsa4096_private_key_index_t *key_index, uint8_t hash_type);
fsp_err_t HW_SCE_RsassaPkcs4096SignatureVerification(sce_rsa_byte_data_t *signature,
        sce_rsa_byte_data_t *message_hash, sce_rsa4096_public_key_index_t *key_index, uint8_t hash_type);

fsp_err_t HW_SCE_RsaesPkcs1024Encrypt(sce_rsa_byte_data_t *plain, sce_rsa_byte_data_t *cipher,
        sce_rsa1024_public_key_index_t *key_index);
fsp_err_t HW_SCE_RsaesPkcs1024Decrypt(sce_rsa_byte_data_t *cipher, sce_rsa_byte_data_t *plain,
        sce_rsa1024_private_key_index_t *key_index);
fsp_err_t HW_SCE_RsaesPkcs2048Encrypt(sce_rsa_byte_data_t *plain, sce_rsa_byte_data_t *cipher,
        sce_rsa2048_public_key_index_t *key_index);
fsp_err_t HW_SCE_RsaesPkcs2048Decrypt(sce_rsa_byte_data_t *cipher, sce_rsa_byte_data_t *plain,
        sce_rsa2048_private_key_index_t *key_index);
fsp_err_t HW_SCE_RsaesPkcs3072Encrypt(sce_rsa_byte_data_t *plain, sce_rsa_byte_data_t *cipher,
        sce_rsa3072_public_key_index_t *key_index);
fsp_err_t HW_SCE_RsaesPkcs3072Decrypt(sce_rsa_byte_data_t *cipher, sce_rsa_byte_data_t *plain,
        sce_rsa3072_private_key_index_t *key_index);
fsp_err_t HW_SCE_RsaesPkcs4096Encrypt(sce_rsa_byte_data_t *plain, sce_rsa_byte_data_t *cipher,
        sce_rsa4096_public_key_index_t *key_index);
fsp_err_t HW_SCE_RsaesPkcs4096Decrypt(sce_rsa_byte_data_t *cipher, sce_rsa_byte_data_t *plain,
        sce_rsa4096_private_key_index_t *key_index);

fsp_err_t HW_SCE_TlsRootCertificateVerification(uint32_t public_key_type, uint8_t *certificate,
        uint32_t certificate_length, uint32_t public_key_n_start_position, uint32_t public_key_n_end_position,
        uint32_t public_key_e_start_position, uint32_t public_key_e_end_position, uint8_t *signature,
        uint32_t *encrypted_root_public_key);
fsp_err_t HW_SCE_TlsCertificateVerification(uint32_t public_key_type, uint32_t *encrypted_input_public_key,
        uint8_t *certificate, uint32_t certificate_length, uint8_t *signature, uint32_t public_key_n_start_position,
        uint32_t public_key_n_end_position, uint32_t public_key_e_start_position, uint32_t public_key_e_end_position,
        uint32_t *encrypted_output_public_key);
fsp_err_t HW_SCE_TlsGeneratePreMasterSecret(uint32_t *sce_pre_master_secret);
fsp_err_t HW_SCE_TlsGenerateMasterSecret(uint32_t select_cipher_suite, uint32_t *sce_pre_master_secret,
        uint8_t *client_random, uint8_t *server_random, uint32_t *sce_master_secret);
fsp_err_t HW_SCE_TlsEncryptPreMasterSecretWithRsa2048PublicKey(uint32_t *encrypted_public_key,
        uint32_t *sce_pre_master_secret, uint8_t *encrypted_pre_master_secret);
fsp_err_t HW_SCE_TlsGenerateSessionKey(uint32_t select_cipher_suite, uint32_t *sce_master_secret,
        uint8_t *client_random, uint8_t *server_random, uint8_t* nonce_explicit,
        sce_hmac_sha_key_index_t *client_mac_key_index, sce_hmac_sha_key_index_t *server_mac_key_index,
        sce_aes_key_index_t *client_crypto_key_index, sce_aes_key_index_t *server_crypto_key_index,
        uint8_t *client_iv, uint8_t *server_iv);
fsp_err_t HW_SCE_TlsGenerateVerifyData(uint32_t select_verify_data, uint32_t *sce_master_secret,
        uint8_t *hand_shake_hash, uint8_t *verify_data);
fsp_err_t HW_SCE_TlsGeneratePreMasterSecretWithEccP256Key(uint32_t *encrypted_public_key,
        sce_tls_p256_ecc_key_index_t *tls_p256_ecc_key_index, uint32_t *sce_pre_master_secret);
fsp_err_t HW_SCE_TlsServersEphemeralEcdhPublicKeyRetrieves(uint32_t public_key_type, uint8_t *client_random,
        uint8_t *server_random, uint8_t *server_ephemeral_ecdh_public_key, uint8_t *server_key_exchange_signature,
        uint32_t *encrypted_public_key, uint32_t *encrypted_ephemeral_ecdh_public_key);

fsp_err_t HW_SCE_EcdsaP192SignatureGenerate(sce_ecdsa_byte_data_t *message_hash, sce_ecdsa_byte_data_t *signature,
        sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_EcdsaP224SignatureGenerate(uint32_t *indata_curvetype, sce_ecdsa_byte_data_t *message_hash, sce_ecdsa_byte_data_t *signature,
        sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_EcdsaP256SignatureGenerate(uint32_t *indata_curvetype, sce_ecdsa_byte_data_t *message_hash, sce_ecdsa_byte_data_t *signature,
        sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_EcdsaP384SignatureGenerate(uint32_t *indata_curvetype, sce_ecdsa_byte_data_t *message_hash, sce_ecdsa_byte_data_t *signature,
        sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_EcdsaP192SignatureVerification(sce_ecdsa_byte_data_t *signature,
        sce_ecdsa_byte_data_t *message_hash, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_EcdsaP224SignatureVerification(uint32_t *indata_curvetype, sce_ecdsa_byte_data_t *signature,
        sce_ecdsa_byte_data_t *message_hash, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_EcdsaP256SignatureVerification(uint32_t *indata_curvetype, sce_ecdsa_byte_data_t *signature,
        sce_ecdsa_byte_data_t *message_hash, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_EcdsaP384SignatureVerification(uint32_t *indata_curvetype, sce_ecdsa_byte_data_t *signature,
        sce_ecdsa_byte_data_t *message_hash, sce_ecc_public_key_index_t *key_index);

fsp_err_t HW_SCE_RSA_IF_HASH(uint8_t *p_mes, uint8_t *p_hash, uint32_t mes_len, uint8_t hash_type);

fsp_err_t HW_SCE_EcdhInit(sce_ecdh_handle_t *handle, uint32_t key_type, uint32_t use_key_id);
fsp_err_t HW_SCE_EcdhReadPublicKey(sce_ecdh_handle_t *handle, sce_ecc_public_key_index_t *public_key_index,
        uint8_t *public_key_data, sce_ecdsa_byte_data_t *signature, sce_ecc_public_key_index_t *key_index);
fsp_err_t HW_SCE_EcdhMakePublicKey(sce_ecdh_handle_t *handle, sce_ecc_public_key_index_t *public_key_index,
        sce_ecc_private_key_index_t *private_key_index, uint8_t *public_key, sce_ecdsa_byte_data_t *signature,
        sce_ecc_private_key_index_t *key_index);
fsp_err_t HW_SCE_EcdhCalculateSharedSecretIndex(sce_ecdh_handle_t *handle,
        sce_ecc_public_key_index_t *public_key_index, sce_ecc_private_key_index_t *private_key_index,
        sce_ecdh_key_index_t *shared_secret_index);
fsp_err_t HW_SCE_EcdhKeyDerivation(sce_ecdh_handle_t *handle, sce_ecdh_key_index_t *shared_secret_index,
        uint32_t algorithm_id, uint8_t *other_info, uint32_t other_info_length, sce_aes_key_index_t *key_index);

fsp_err_t HW_SCE_Aes128KeyWrap(sce_aes_key_index_t *wrap_key_index, uint32_t target_key_type,
        sce_aes_key_index_t *target_key_index, uint32_t *wrapped_key);
fsp_err_t HW_SCE_Aes256KeyWrap(sce_aes_key_index_t *wrap_key_index, uint32_t target_key_type,
        sce_aes_key_index_t *target_key_index, uint32_t *wrapped_key);
fsp_err_t HW_SCE_Aes128KeyUnwrap(sce_aes_key_index_t *wrap_key_index, uint32_t target_key_type,
        uint32_t *wrapped_key, sce_aes_key_index_t *target_key_index);
fsp_err_t HW_SCE_Aes256KeyUnwrap(sce_aes_key_index_t *wrap_key_index, uint32_t target_key_type,
        uint32_t *wrapped_key, sce_aes_key_index_t *target_key_index);

#endif /* R_SCE_IF_HEADER_FILE */
