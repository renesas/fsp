/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name    : r_cip_drv_if.h
 * Description  : Interface definition for the RSIP driver for RA8M1 module.
 ***********************************************************************************************************************
 * Supported Device : RA8M1(RA8x1)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <stdint.h>

#ifndef R_CIP_HEADER_FILE
#define R_CIP_HEADER_FILE

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* Version Number of API. */
#define CIP_VERSION_MAJOR                    (1u)
#define CIP_VERSION_MINOR                    (3u)

#define R_CIP_SRAM_WORD_SIZE                 (256u)
#define R_CIP_SFLASH_WORD_SIZE               (200u)

#define R_CIP_HUK_INDEX_WORD_SIZE            (12u)
#define R_CIP_OEM_KEY_INDEX_WORD_SIZE        (9u)
#define R_CIP_PASSWORD_BYTE_SIZE             (64u)
#define R_CIP_MAC_BYTE_SIZE                  (32u)
#define R_CIP_CHALLENGE_BYTE_SIZE            (32u)

#define R_CIP_KEY_UPDATE_KEY_INST_WORD_SIZE  (12u)
#define R_CIP_KEY_UPDATE_KEY_INDEX_WORD_SIZE (13u)

/* Return error codes */
/* return value */
#define CIP_DRV_RET_SUCCESS                   ((cip_drv_err_t)0x55555555UL) /* Successful completion */
#define CIP_DRV_RET_ERR_FAIL                  ((cip_drv_err_t)0xAAAA0001UL) /* Abnormal termination */
#define CIP_DRV_RET_ERR_RESOURCE_CONFLICT     ((cip_drv_err_t)0xAAAA0002UL) /* Resource collision occurs because
                                                                               resources required for this process are
                                                                               used by other processes */
#define CIP_DRV_RET_ERR_RETRY                 ((cip_drv_err_t)0xAAAA0003UL) /* Retryable error */
#define CIP_DRV_RET_ERR_AUTH_FAIL             ((cip_drv_err_t)0xAAAA0004UL) /* Verification failed */
#define CIP_DRV_RET_UNSUPPORTED_ALGORITHM     ((cip_drv_ret_t)0xAAAA0005UL) /* Unsupported algorithm */
#define CIP_DRV_RET_LOWER_IMAGE_VERSION       ((cip_drv_ret_t)0xAAAA0006UL) /* A version lower than the current
                                                                               image version has been entered */
#define CIP_DRV_RET_PARAM_ERROR               ((cip_drv_ret_t)0xAAAA0007UL) /* Parameter error */

#define CIP_DRV_RET_ERR_KEY_SET_FAIL          ((cip_drv_err_t)0xAAAA0008UL) /* Invalid key generation information */
#define CIP_DRV_RET_TAMPER_DETECT             ((cip_drv_ret_t)0xAAAA0009UL) /* Tampering was detected */

#define CIP_DRV_CALL_ONLY_INIT                (0)
#define CIP_DRV_CALL_ONLY_UPDATE_FINAL        (1)
#define CIP_DRV_AES_BLOCK_BYTE_SIZE           (16)
#define CIP_DRV_FORMAT_DATA_SIZE              (CIP_DRV_AES_BLOCK_BYTE_SIZE)
#define CIP_DRV_CCM_BUF_SIZE                  (CIP_DRV_AES_BLOCK_BYTE_SIZE*2)

#define CIP_DRV_CCM_B_FORMAT_BYTE_SIZE        (128u)
#define CIP_DRV_CCM_COUNTER_BYTE_SIZE         (16u)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/* cip_drv return type */
typedef uint32_t cip_drv_err_t;

/* Data structure for decrypting ciphertext */
typedef struct {
    uint32_t                id;
    uint8_t                 formatted_data[CIP_DRV_CCM_B_FORMAT_BYTE_SIZE];
    uint8_t                 counter[CIP_DRV_CCM_COUNTER_BYTE_SIZE];
    uint8_t                 ccm_buffer[CIP_DRV_CCM_BUF_SIZE];
    uint32_t                all_received_length;
    uint32_t                buffering_length;
    uint8_t                 flag_call_init;
} ship_ccm_handle_t;

/* LIFE CYCLE */
typedef enum
{
    CIP_CM1 = 0,
    CIP_CM2,
    CIP_OEM = 4,
    CIP_RMA_REQ = 7,
    CIP_RMA_ACK,
    CIP_RMA_RET,
} lifecycle_t;

/* AUTHENTIC COMMAND*/
typedef enum
{
    CIP_AUTH_CM1_CMD = 0,
    CIP_AUTH_AL2_CMD,
    CIP_AUTH_AL1_CMD,
    CIP_AUTH_RMA_CMD,
    CIP_AUTH_RMA_ACK_CMD,
} auth_cmd_t;

/* OEM key type */
typedef enum
{
    CIP_OEM_KEY_TYPE_AUTH_CM1 = 0,
    CIP_OEM_KEY_TYPE_AUTH_AL2,
    CIP_OEM_KEY_TYPE_AUTH_AL1,
    CIP_OEM_KEY_TYPE_AUTH_RMA,
    CIP_OEM_KEY_TYPE_AUTH_RMA_ACK,
    CIP_OEM_KEY_TYPE_AES128,
    CIP_OEM_KEY_TYPE_AES192,
    CIP_OEM_KEY_TYPE_AES256,
    CIP_OEM_KEY_TYPE_AES128_XTS,
    CIP_OEM_KEY_TYPE_AES256_XTS,
    CIP_OEM_KEY_TYPE_RSA1024_PUBLIC,
    CIP_OEM_KEY_TYPE_RSA1024_PRIVATE,
    CIP_OEM_KEY_TYPE_RSA2048_PUBLIC,
    CIP_OEM_KEY_TYPE_RSA2048_PRIVATE,
    CIP_OEM_KEY_TYPE_RSA3072_PUBLIC,
    CIP_OEM_KEY_TYPE_RSA3072_PRIVATE,
    CIP_OEM_KEY_TYPE_RSA4096_PUBLIC,
    CIP_OEM_KEY_TYPE_RSA4096_PRIVATE,
    CIP_OEM_KEY_TYPE_ECC_P192_PUBLIC,
    CIP_OEM_KEY_TYPE_ECC_P192_PRIVATE,
    CIP_OEM_KEY_TYPE_ECC_P224_PUBLIC,
    CIP_OEM_KEY_TYPE_ECC_P224_PRIVATE,
    CIP_OEM_KEY_TYPE_ECC_P256_PUBLIC,
    CIP_OEM_KEY_TYPE_ECC_P256_PRIVATE,
    CIP_OEM_KEY_TYPE_ECC_P384_PUBLIC,
    CIP_OEM_KEY_TYPE_ECC_P384_PRIVATE,
    CIP_OEM_KEY_TYPE_HMAC_SHA224,
    CIP_OEM_KEY_TYPE_HMAC_SHA256,
    CIP_OEM_KEY_TYPE_ECC_P256R1_PUBLIC,
    CIP_OEM_KEY_TYPE_ECC_P256R1_PRIVATE,
    CIP_OEM_KEY_TYPE_ECC_P384R1_PUBLIC,
    CIP_OEM_KEY_TYPE_ECC_P384R1_PRIVATE,
    CIP_OEM_KEY_TYPE_ECC_P512R1_PUBLIC,
    CIP_OEM_KEY_TYPE_ECC_P512R1_PRIVATE,
    CIP_OEM_KEY_TYPE_ECC_SECP256K1_PUBLIC,
    CIP_OEM_KEY_TYPE_ECC_SECP256K1_PRIVATE,
    CIP_OEM_KEY_TYPE_ECC_P521_PUBLIC,
    CIP_OEM_KEY_TYPE_ECC_P521_PRIVATE,
    CIP_OEM_KEY_TYPE_ED25519_PUBLIC,
    CIP_OEM_KEY_TYPE_ED25519_PRIVATE,
    CIP_OEM_KEY_TYPE_HMAC_SHA384,
    CIP_OEM_KEY_TYPE_HMAC_SHA512,
    CIP_OEM_KEY_TYPE_HMAC_SHA512_224,
    CIP_OEM_KEY_TYPE_HMAC_SHA512_256,
    CIP_OEM_KEY_TYPE_NUM,
    CIP_OEM_KEY_TYPE_OEM_ROOT_PK = 0xfdU,
    CIP_OEM_KEY_TYPE_RSA2048_PUBLIC_TLS,
    CIP_OEM_KEY_TYPE_KEY_UPDATE_KEY,
} oem_key_type_t;

#define USERKEYNUM (CIP_OEM_KEY_TYPE_NUM + 3)

/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/


#endif /* R_CIP_HEADER_FILE */
