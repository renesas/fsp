/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*!********************************************************************************************************************
* \file             : r_cip_drv_api.h
* \par version      : 1.00
* \par Product Name : Renesas-SB-Lib
* \par Device(s)    : Does not depend on specific hardware
* \par Description  : This file defines the public macros, types and declarations in used the Crypto IP Driver.
**********************************************************************************************************************/
#ifndef R_CIP_DRV_API_H
#define R_CIP_DRV_API_H

#include <stdint.h>

/*=====================================================================================================================
 Public macro definitions
=====================================================================================================================*/
/* return value */
#define CIP_DRV_RET_PASS                      ((cip_drv_ret_t)0x55555555UL) /* Successful completion */
#define CIP_DRV_RET_SAME_IMAGE_VERSION        ((cip_drv_ret_t)0x55005501UL) /* The same version as the current
                                                                               image version was entered */
#define CIP_DRV_RET_FAIL                      ((cip_drv_ret_t)0xAAAA0001UL) /* Abnormal termination */
#define CIP_DRV_RET_RESOURCE_CONFLICT         ((cip_drv_ret_t)0xAAAA0002UL) /* Resource collision occurs because
                                                                               resources required for this process are
                                                                               used by other processes */
#define CIP_DRV_RET_RETRY                     ((cip_drv_ret_t)0xAAAA0003UL) /* Retryable error */
#define CIP_DRV_RET_AUTH_FAIL                 ((cip_drv_ret_t)0xAAAA0004UL) /* Verification failed */
#define CIP_DRV_RET_UNSUPPORTED_ALGORITHM     ((cip_drv_ret_t)0xAAAA0005UL) /* Unsupported algorithm */
#define CIP_DRV_RET_LOWER_IMAGE_VERSION       ((cip_drv_ret_t)0xAAAA0006UL) /* A version lower than the current
                                                                               image version has been entered */
#define CIP_DRV_RET_PARAM_ERROR               ((cip_drv_ret_t)0xAAAA0007UL) /* Parameter error */

#define CIP_DRV_RET_KEY_SET_FAIL              ((cip_drv_ret_t)0xAAAA0008UL) /* Parameter error */
#define CIP_DRV_RET_TAMPER_DETECT             ((cip_drv_ret_t)0xAAAA0009UL) /* Tamper detect error */
#define CIP_DRV_RET_CRC_MISMATCH              ((cip_drv_ret_t)0xAAAA000AUL) /* CRC mismatch */

/* Root of Trust type */
#define CIP_DRV_KEY_CERT_PK_CMP_SRC_ROT       (0UL)
#define CIP_DRV_KEY_CERT_PK_CMP_SRC_IMG_PK    (1UL)


/* HASH algorithm */
#define CIP_DRV_HASH_ALGO_NONE              (0UL)
#define CIP_DRV_HASH_ALGO_SHA2_224          (1UL)
#define CIP_DRV_HASH_ALGO_SHA2_256          (2UL)
#define CIP_DRV_HASH_ALGO_SHA2_384          (3UL)
#define CIP_DRV_HASH_ALGO_SHA2_512          (4UL)
#define CIP_DRV_HASH_ALGO_SHA3_224          (5UL)
#define CIP_DRV_HASH_ALGO_SHA3_256          (6UL)
#define CIP_DRV_HASH_ALGO_SHA3_384          (7UL)
#define CIP_DRV_HASH_ALGO_SHA3_512          (8UL)

/* MAC algorithm */
#define CIP_DRV_MAC_ALGO_NONE               (0UL)
#define CIP_DRV_MAC_ALGO_HMAC_SHA2_224      (1UL)
#define CIP_DRV_MAC_ALGO_HMAC_SHA2_256      (2UL)
#define CIP_DRV_MAC_ALGO_HMAC_SHA2_384      (3UL)
#define CIP_DRV_MAC_ALGO_HMAC_SHA2_512      (4UL)
#define CIP_DRV_MAC_ALGO_HMAC_SHA3_224      (5UL)
#define CIP_DRV_MAC_ALGO_HMAC_SHA3_256      (6UL)
#define CIP_DRV_MAC_ALGO_HMAC_SHA3_384      (7UL)
#define CIP_DRV_MAC_ALGO_HMAC_SHA3_512      (8UL)
#define CIP_DRV_MAC_ALGO_CMAC_AES_128       (9UL)
#define CIP_DRV_MAC_ALGO_CMAC_AES_192       (10UL)
#define CIP_DRV_MAC_ALGO_CMAC_AES_256       (11UL)

/* Signature algorithm */
#define CIP_DRV_SIGN_ALGO_NONE              (0UL)
#define CIP_DRV_SIGN_ALGO_ECDSA_P192        (1UL)
#define CIP_DRV_SIGN_ALGO_ECDSA_P224        (2UL)
#define CIP_DRV_SIGN_ALGO_ECDSA_P256        (3UL)
#define CIP_DRV_SIGN_ALGO_ECDSA_P384        (4UL)
#define CIP_DRV_SIGN_ALGO_ECDSA_P521        (5UL)
#define CIP_DRV_SIGN_ALGO_ECDSA_BP192R1     (6UL)
#define CIP_DRV_SIGN_ALGO_ECDSA_BP224R1     (7UL)
#define CIP_DRV_SIGN_ALGO_ECDSA_BP256R1     (8UL)
#define CIP_DRV_SIGN_ALGO_ECDSA_BP384R1     (9UL)
#define CIP_DRV_SIGN_ALGO_ECDSA_BP512R1     (10UL)
#define CIP_DRV_SIGN_ALGO_EDDSA_ED25519     (11UL)
#define CIP_DRV_SIGN_ALGO_EDDSA_ED448       (12UL)
#define CIP_DRV_SIGN_ALGO_RSA1024           (13UL)
#define CIP_DRV_SIGN_ALGO_RSA2048           (14UL)
#define CIP_DRV_SIGN_ALGO_RSA3072           (15UL)
#define CIP_DRV_SIGN_ALGO_RSA4096           (16UL)


/* Signature scheme */
#define CIP_DRV_SCHEME_NONE                 (0UL)
#define CIP_DRV_SCHEME_RSASSA_PKCS1_V1_5    (1UL)
#define CIP_DRV_SCHEME_RSASSA_PSS           (2UL)

/* Cipher algorithm */
#define CIP_DRV_CIPHER_ALGO_NONE            (0UL)
#define CIP_DRV_CIPHER_ALGO_AES128          (1UL)
#define CIP_DRV_CIPHER_ALGO_AES192          (2UL)
#define CIP_DRV_CIPHER_ALGO_AES256          (3UL)

/* Cipher mode */
#define CIP_DRV_CIPHER_MODE_NONE            (0UL)
#define CIP_DRV_CIPHER_MODE_ECB             (1UL)
#define CIP_DRV_CIPHER_MODE_CBC             (2UL)
#define CIP_DRV_CIPHER_MODE_CFB             (3UL)
#define CIP_DRV_CIPHER_MODE_OFB             (4UL)
#define CIP_DRV_CIPHER_MODE_CTR             (5UL)

/* Key select */
#define CIP_DRV_CIPHER_INFO_KEY_SEL_DEFAULT         (0x00000000UL)
#define CIP_DRV_CIPHER_INFO_KEY_SEL_DEV_UNIQUE      (0x00010000UL)
#define CIP_DRV_CIPHER_INFO_KEY_SEL_INSTALLED       (0x00020000UL)

/* IV select */
#define CIP_DRV_CIPHER_INFO_IV_SEL_DEFAULT          (0x00000000UL)
#define CIP_DRV_CIPHER_INFO_IV_SEL_DEV_UNIQUE       (0x00010000UL)
#define CIP_DRV_CIPHER_INFO_IV_SEL_INSTALLED        (0x00020000UL)
#define CIP_DRV_CIPHER_INFO_IV_SEL_STORED_CODE_CERT (0x00030000UL)

/* Cipher timinig */
#define CIP_DRV_CIPHER_TIMING_NONE                  (0UL)
#define CIP_DRV_CIPHER_TIMING_BEFORE_VERIFY         (1UL)
#define CIP_DRV_CIPHER_TIMING_AFTER_VERIFY          (2UL)

/*=====================================================================================================================
 Public type definitions
=====================================================================================================================*/
/* cip_drv return type */
typedef uint32_t cip_drv_ret_t;

/* MAC verification parameter */
typedef struct
{
    uint32_t        mac_algo;
    const uint32_t* p_mac;
    uint32_t        mac_len;
    const uint32_t* p_code_cert;
    uint32_t        code_cert_len;
    const uint32_t* p_img;
    uint32_t        img_len;
    uint32_t        is_save_img_pk;
    const uint32_t* p_sign_pk;
    uint32_t        sign_pk_len;
} st_cip_drv_mac_param_t;

/* Certificate chain verification KeyCert parameter */
typedef struct
{
    uint32_t        key_cert_pk_cmp_src;
    uint32_t        img_pk_hash_algo;
    const uint32_t* p_img_pk_hash;
    uint32_t        img_pk_hash_len;
    uint32_t        sign_algo;
    uint32_t        sign_hash_algo;
    uint32_t        sign_scheme;
    const uint32_t* p_sign_pk;
    uint32_t        sign_pk_len;
    const uint32_t* p_sign;
    uint32_t        sign_len;
    const uint32_t* p_key_cert;
    uint32_t        key_cert_sign_len;
} st_cip_drv_cc_key_cert_param_t;

/* Certificate chain verification CodeCert parameter */
typedef struct
{
    uint32_t        sign_algo;
    uint32_t        sign_hash_algo;
    uint32_t        sign_scheme;
    const uint32_t* p_sign_pk;
    uint32_t        sign_pk_len;
    const uint32_t* p_sign;
    uint32_t        sign_len;
    const uint32_t* p_code_cert;
    uint32_t        code_cert_len;
    uint32_t        code_cert_sign_len;
    const uint32_t* p_img;
    uint32_t        img_len;
    uint32_t        img_hash_algo;
    const uint32_t* p_img_hash;
    uint32_t        img_hash_len;
    uint32_t        is_save_img_pk;
} st_cip_drv_cc_code_cert_param_t;

/* image cipher parameter */
typedef struct
{
    uint32_t        timing;
    const uint32_t* p_img_src;
    uint32_t*       p_img_dst;
    uint32_t        img_len;
    uint32_t        cipher_algo;
    uint32_t        cipher_mode;
    uint32_t        key_select;
    uint32_t        iv_select;
    const uint32_t* p_iv;
    uint32_t        iv_len;
}st_cip_drv_cipher_img_param_t;

/* CRC check parameter */
typedef struct
{
    uint32_t         crc_algo;
    const uint32_t * p_crc;
    const uint32_t * p_img;
    uint32_t         img_len;
} st_cip_drv_crc_param_t;


/*=====================================================================================================================
 Public global variables
=====================================================================================================================*/

/*=====================================================================================================================
 Public global functions
=====================================================================================================================*/
extern cip_drv_ret_t R_CIP_DRV_PrcDeriveMacKeyFromHuk(void);
extern cip_drv_ret_t R_CIP_DRV_PrcCheckIntegrity(const st_cip_drv_cc_key_cert_param_t*  const p_cc_key_cert_param,
                                                    const st_cip_drv_cc_code_cert_param_t* const p_cc_code_cert_param,
                                                    const st_cip_drv_cipher_img_param_t* const p_dec_tmp_img_param,
                                                    const st_cip_drv_cipher_img_param_t* const p_enc_img_param,
                                                    const uint32_t mac_algo, uint32_t* const p_tag);
extern cip_drv_ret_t R_CIP_DRV_CheckImageVersion(const uint32_t image_version,
                                                    const uint32_t build_num);

#endif /* R_CIP_DRV_API_H */
/*=====================================================================================================================
 End of File
=====================================================================================================================*/
