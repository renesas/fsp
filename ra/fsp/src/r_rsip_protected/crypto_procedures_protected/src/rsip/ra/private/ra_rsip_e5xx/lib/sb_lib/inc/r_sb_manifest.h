/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*!********************************************************************************************************************
* \file             : r_sb_manifest.h
* \par version      : 1.00
* \par Product Name : Renesas-SB-Lib FSBL Custom
* \par Device(s)    : Does not depend on specific hardware
* \par Description  : This file defines the macros, types, declarations in used the Manifest module.
**********************************************************************************************************************/

#ifndef R_SB_MANIFEST_H
/* Multiple inclusion protection macro */
#define R_SB_MANIFEST_H

/*=====================================================================================================================
 Public macro definitions
=====================================================================================================================*/
/*!********************************************************************
 * \addtogroup SBLIBManifestDefinesInternal
 * \{
 * \addtogroup  group_manifest_common
 * \addtogroup  group_codecert_flag
 * \addtogroup  group_tlv_type_class
 * \addtogroup  group_tlv_key_usetype
 * \addtogroup  group_tlv_hash_usetype
 * \addtogroup  group_tlv_sign_usetype
 * \addtogroup  group_tlv_sign_hashalgo
 * \addtogroup  group_tlv_sign_scheme
 * \addtogroup  group_tlv_mac_usetype
 * \addtogroup  group_tlv_crc_usetype
 * \addtogroup  group_tlv_crc_poly
 * \addtogroup  group_tlv_pc_usetype
 * \addtogroup  group_tlv_iv_usetype
 * \addtogroup  group_tlv_ici_usetype
 * \addtogroup  group_tlv_ici_cipher
 * \addtogroup  group_tlv_ici_key
 * \addtogroup  group_tlv_ici_iv
 * \addtogroup  group_tlv_crypto
 * \}*****************************************************************/
/**\addtogroup group_manifest_common ManifestCommon */
/*! \{*/
#define SB_PRV_MANI_HEADER_SIZE                         (32UL)              /**< Manifest header size */
#define SB_PRV_MANI_TLV_LEN_SIZE                        (4UL)               /**< Manifest TLV length size */
#define SB_PRV_TLV_TL_SIZE                              (4UL)               /**< TLV Type & Length size */
/*! \}*/

/** Code certificate header */
/**\addtogroup group_codecert_flag Code Certificate Flag */
/*! \{*/
#define SB_PRV_CODE_CERT_HEADER_FLAGS_IMG_CIPHER_ENC (0x00000001UL) /**< Image cipher enable */
#define SB_PRV_CODE_CERT_HEADER_FLAGS_TMP_IMG_DEC    (0x00000002UL) /**< Decrypt temporarily encrypted images enable */
#define SB_PRV_CODE_CERT_HEADER_FLAGS_SAVE_IMG_PK    (0x00000004UL) /**< Save Image PK Hash enable */
/*! \}*/

/** Type Class */
/**\addtogroup group_tlv_type_class TLV TypeClass */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_POS                  (28UL)                               /**< Type Class Bit Position */
#define SB_PRV_TLV_TYPE_CLS_KEY                  (0x0UL << (SB_PRV_TLV_TYPE_CLS_POS)) /**< Class Key */
#define SB_PRV_TLV_TYPE_CLS_HASH                 (0x1UL << (SB_PRV_TLV_TYPE_CLS_POS)) /**< Class Hash */
#define SB_PRV_TLV_TYPE_CLS_SIGN                 (0x2UL << (SB_PRV_TLV_TYPE_CLS_POS)) /**< Class Signature */
#define SB_PRV_TLV_TYPE_CLS_MAC                  (0x3UL << (SB_PRV_TLV_TYPE_CLS_POS)) /**< Class MAC */
#define SB_PRV_TLV_TYPE_CLS_CRC                  (0x4UL << (SB_PRV_TLV_TYPE_CLS_POS)) /**< Class CRC */
#define SB_PRV_TLV_TYPE_CLS_IV                   (0x5UL << (SB_PRV_TLV_TYPE_CLS_POS)) /**< Class IV */
#define SB_PRV_TLV_TYPE_CLS_PC                   (0xDUL << (SB_PRV_TLV_TYPE_CLS_POS)) /**< Class Product class */
#define SB_PRV_TLV_TYPE_CLS_ICI                  (0xEUL << (SB_PRV_TLV_TYPE_CLS_POS)) /**< Class Image Cipher info */
#define SB_PRV_TLV_TYPE_CLS_MAX                  (0xFUL << (SB_PRV_TLV_TYPE_CLS_POS)) /**< Type Class full bit */
#define SB_PRV_TLV_TYPE_CLS_MASK                 (SB_PRV_TLV_TYPE_CLS_MAX)            /**< Type Class mask */
/*! \}*/

/** Use type of KEY class */
/**\addtogroup group_tlv_key_usetype TLV KEY UseType */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_KEY_UT_POS          (24UL)                                    /**< Use Type Bit Position */
#define SB_PRV_TLV_TYPE_CLS_KEY_UT_OEM_ROOT_PK  (0x0UL << (SB_PRV_TLV_TYPE_CLS_KEY_UT_POS)) /**< OEM root public key */
#define SB_PRV_TLV_TYPE_CLS_KEY_UT_IMG_PK       (0x1UL << (SB_PRV_TLV_TYPE_CLS_KEY_UT_POS)) /**< Image public key */
#define SB_PRV_TLV_TYPE_CLS_KEY_UT_MAX          (0xFUL << (SB_PRV_TLV_TYPE_CLS_KEY_UT_POS)) /**< Use Type full bit */
#define SB_PRV_TLV_TYPE_CLS_KEY_UT_MASK         (SB_PRV_TLV_TYPE_CLS_KEY_UT_MAX)            /**< Use Type mask */
/*! \}*/

/** Use type of HASH class */
/**\addtogroup group_tlv_hash_usetype TLV HASH UseType */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_HASH_UT_POS      (24UL)                                       /**< Use Type Bit Position */
#define SB_PRV_TLV_TYPE_CLS_HASH_UT_IMG_PK   (0x0UL << (SB_PRV_TLV_TYPE_CLS_HASH_UT_POS)) /**< Image public key Hash */
#define SB_PRV_TLV_TYPE_CLS_HASH_UT_IMG      (0x1UL << (SB_PRV_TLV_TYPE_CLS_HASH_UT_POS)) /**< Image Hash */
#define SB_PRV_TLV_TYPE_CLS_HASH_UT_ENCIMG   (0x2UL << (SB_PRV_TLV_TYPE_CLS_HASH_UT_POS)) /**< Encrypt Image Hash */
#define SB_PRV_TLV_TYPE_CLS_HASH_UT_MAX      (0xFUL << (SB_PRV_TLV_TYPE_CLS_HASH_UT_POS)) /**< Use Type full bit */
#define SB_PRV_TLV_TYPE_CLS_HASH_UT_MASK     (SB_PRV_TLV_TYPE_CLS_HASH_UT_MAX)            /**< Use Type mask */
/*! \}*/

/** Use type of Signature class */
/**\addtogroup group_tlv_sign_usetype TLV SIGN UseType */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_SIGN_UT_POS                    (24UL)                         /**< Use Type Bit Position */
/** Certificate Signature */
#define SB_PRV_TLV_TYPE_CLS_SIGN_UT_CERT                   (0x0UL << (SB_PRV_TLV_TYPE_CLS_SIGN_UT_POS))
/** Code Certificate + Image Signature */
#define SB_PRV_TLV_TYPE_CLS_SIGN_UT_CODE_CERT_AND_IMG      (0x5UL << (SB_PRV_TLV_TYPE_CLS_SIGN_UT_POS))
/** Code Certificate + Encrypted Image Signature */
#define SB_PRV_TLV_TYPE_CLS_SIGN_UT_CODE_CERT_AND_ENCIMG   (0x6UL << (SB_PRV_TLV_TYPE_CLS_SIGN_UT_POS))
/** Use Type full bit */
#define SB_PRV_TLV_TYPE_CLS_SIGN_UT_MAX                    (0xFUL << (SB_PRV_TLV_TYPE_CLS_SIGN_UT_POS))
#define SB_PRV_TLV_TYPE_CLS_SIGN_UT_MASK                   (SB_PRV_TLV_TYPE_CLS_SIGN_UT_MAX)      /**< Use Type mask */
/*! \}*/

/** Hash Algorithm of Signature class */
/**\addtogroup group_tlv_sign_hashalgo TLV SIGN HashAlgorithm */
/*! \{*/
/**< Hash Algorithm Bit Position */
#define SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_POS             (10UL)
/** SHA2-224 */
#define SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_224        (0x0UL << (SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))
/** SHA2-256 */
#define SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_256        (0x1UL << (SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))
/** SHA2-384 */
#define SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_384        (0x2UL << (SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))
/** SHA2-512 */
#define SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_512        (0x3UL << (SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))
/** SHA3-224 */
#define SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_224        (0x4UL << (SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))
/** SHA3-256 */
#define SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_256        (0x5UL << (SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))
/** SHA3-384 */
#define SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_384        (0x6UL << (SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))
/** SHA3-512 */
#define SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_512        (0x7UL << (SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))
/** Hash Algorithm full bit */
#define SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_MAX             (0xFUL << (SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_POS))
/** Hash Algorithm mask */
#define SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_MASK            (SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_MAX)
/*! \}*/

/** Scheme of Signature class */
/**\addtogroup group_tlv_sign_scheme TLV SIGN Scheme */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_POS                (8UL)                            /**< Scheme Bit Position */
/** RSASSA-PKCS1_v1_5 */
#define SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_RSASSA_PKCS1_V1_5  (0x0UL << (SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_POS))
/** RSASSA-PSS */
#define SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_RSASSA_PSS         (0x1UL << (SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_POS))
/** Scheme full bit */
#define SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_MAX                (0x3UL << (SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_POS))
#define SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_MASK               (SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_MAX)    /**< Scheme mask */
/*! \}*/

/** Use type of MAC class */
/**\addtogroup group_tlv_mac_usetype TLV MAC UseType */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_MAC_UT_POS                     (24UL)                         /**< Use Type Bit Position */
/** Code Certificate + Image MAC */
#define SB_PRV_TLV_TYPE_CLS_MAC_UT_CODE_CERT_AND_IMG       (0x0UL << (SB_PRV_TLV_TYPE_CLS_MAC_UT_POS))
/** Code Certificate + Encrypted Image MAC */
#define SB_PRV_TLV_TYPE_CLS_MAC_UT_CODE_CERT_AND_ENCIMG    (0x1UL << (SB_PRV_TLV_TYPE_CLS_MAC_UT_POS))
/** Use Type full bit */
#define SB_PRV_TLV_TYPE_CLS_MAC_UT_MAX                     (0xFUL << (SB_PRV_TLV_TYPE_CLS_MAC_UT_POS))
#define SB_PRV_TLV_TYPE_CLS_MAC_UT_MASK                    (SB_PRV_TLV_TYPE_CLS_MAC_UT_MAX)       /**< Use Type mask */
/*! \}*/

/** Use type of CRC class */
/**\addtogroup group_tlv_crc_usetype TLV CRC UseType */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_CRC_UT_POS           (24UL)                                   /**< Use Type Bit Position */
#define SB_PRV_TLV_TYPE_CLS_CRC_UT_IMG           (0x0UL << (SB_PRV_TLV_TYPE_CLS_CRC_UT_POS))  /**< Image CRC */
#define SB_PRV_TLV_TYPE_CLS_CRC_UT_MAX           (0xFUL << (SB_PRV_TLV_TYPE_CLS_CRC_UT_POS))  /**< Use Type full bit */
#define SB_PRV_TLV_TYPE_CLS_CRC_UT_MASK          (SB_PRV_TLV_TYPE_CLS_CRC_UT_MAX)             /**< Use Type mask */
/*! \}*/

/** Polynomial of CRC class */
/**\addtogroup group_tlv_crc_poly TLV CRC Polynomial */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_CRC_POLY_POS      (20UL)                                    /**< Polynomial Bit Position */
#define SB_PRV_TLV_TYPE_CLS_CRC_POLY_MAX      (0xFUL << (SB_PRV_TLV_TYPE_CLS_CRC_POLY_POS)) /**< Polynomial full bit */
#define SB_PRV_TLV_TYPE_CLS_CRC_POLY_MASK     (SB_PRV_TLV_TYPE_CLS_CRC_POLY_MAX)            /**< Polynomial mask */
/*! \}*/

/** Use type of Product Class(PC) class */
/**\addtogroup group_tlv_pc_usetype TLV Product Class UseType */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_PC_UT_POS              (24UL)                                 /**< Use Type Bit Position */
#define SB_PRV_TLV_TYPE_CLS_PC_UT_VENDER_ID        (0x0UL << (SB_PRV_TLV_TYPE_CLS_PC_UT_POS)) /**< Vender ID */
#define SB_PRV_TLV_TYPE_CLS_PC_UT_PRODUCT_ID       (0x1UL << (SB_PRV_TLV_TYPE_CLS_PC_UT_POS)) /**< Product ID */
#define SB_PRV_TLV_TYPE_CLS_PC_UT_MAX              (0xFUL << (SB_PRV_TLV_TYPE_CLS_PC_UT_POS)) /**< Use Type full bit */
#define SB_PRV_TLV_TYPE_CLS_PC_UT_MASK             (SB_PRV_TLV_TYPE_CLS_PC_UT_MAX)            /**< Use Type mask */
/*! \}*/

/** Use type of IV class */
/**\addtogroup group_tlv_iv_usetype TLV IV UseType */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_IV_UT_POS              (24UL)                                 /**< Use Type Bit Position */
#define SB_PRV_TLV_TYPE_CLS_IV_UT_IMG_CIPHER       (0x0UL << (SB_PRV_TLV_TYPE_CLS_IV_UT_POS)) /**< Image Cipher IV */
#define SB_PRV_TLV_TYPE_CLS_IV_UT_TMP_IMG_DEC      (0x1UL << (SB_PRV_TLV_TYPE_CLS_IV_UT_POS)) /**< Temporary
                                                                                                   Image Cipher IV */
#define SB_PRV_TLV_TYPE_CLS_IV_UT_MAX              (0xFUL << (SB_PRV_TLV_TYPE_CLS_IV_UT_POS)) /**< Use Type full bit */
#define SB_PRV_TLV_TYPE_CLS_IV_UT_MASK             (SB_PRV_TLV_TYPE_CLS_IV_UT_MAX)            /**< Use Type mask */
/*! \}*/

/** Use type of Image Cipher Info(ICI) class */
/**\addtogroup group_tlv_ici_usetype TLV Image Cipher Info UseType */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_ICI_UT_POS            (24UL)                                  /**< Use Type Bit Position */
/** Image Encryption/Decryption Information */
#define SB_PRV_TLV_TYPE_CLS_ICI_UT_IMG_ENC_DEC    (0x0UL << (SB_PRV_TLV_TYPE_CLS_ICI_UT_POS))
/** Temporary Image Decryption Information */
#define SB_PRV_TLV_TYPE_CLS_ICI_UT_TMP_IMG_DEC    (0x1UL << (SB_PRV_TLV_TYPE_CLS_ICI_UT_POS))
#define SB_PRV_TLV_TYPE_CLS_ICI_UT_MAX            (0xFUL << (SB_PRV_TLV_TYPE_CLS_ICI_UT_POS)) /**< Use Type full bit */
#define SB_PRV_TLV_TYPE_CLS_ICI_UT_MASK           (SB_PRV_TLV_TYPE_CLS_ICI_UT_MAX)            /**< Use Type mask */
/*! \}*/

/** Cipher mode of Image Cipher Info(ICI) class */
/**\addtogroup group_tlv_ici_cipher TLV Image Cipher Info CipherMode */
/*! \{*/
#define SB_PRV_TLV_TYPE_CLS_ICI_MODE_POS     (10UL)                                    /**< Cipher mode Bit Position */
#define SB_PRV_TLV_TYPE_CLS_ICI_MODE_ECB     (0x0UL << (SB_PRV_TLV_TYPE_CLS_ICI_MODE_POS)) /**< Mode ECB */
#define SB_PRV_TLV_TYPE_CLS_ICI_MODE_CBC     (0x1UL << (SB_PRV_TLV_TYPE_CLS_ICI_MODE_POS)) /**< Mode CBC */
#define SB_PRV_TLV_TYPE_CLS_ICI_MODE_CFB     (0x2UL << (SB_PRV_TLV_TYPE_CLS_ICI_MODE_POS)) /**< Mode CFB */
#define SB_PRV_TLV_TYPE_CLS_ICI_MODE_OFB     (0x3UL << (SB_PRV_TLV_TYPE_CLS_ICI_MODE_POS)) /**< Mode OFB */
#define SB_PRV_TLV_TYPE_CLS_ICI_MODE_CTR     (0x4UL << (SB_PRV_TLV_TYPE_CLS_ICI_MODE_POS)) /**< Mode CTR */
#define SB_PRV_TLV_TYPE_CLS_ICI_MODE_MAX     (0xFUL << (SB_PRV_TLV_TYPE_CLS_ICI_MODE_POS)) /**< Cipher mode full bit */
#define SB_PRV_TLV_TYPE_CLS_ICI_MODE_MASK    (SB_PRV_TLV_TYPE_CLS_ICI_MODE_MAX)            /**< Cipher mode mask */
/*! \}*/

/** Key Select of Image Cipher Info(ICI) class value */
/**\addtogroup group_tlv_ici_key TLV Image Cipher Info KeySelect */
/*! \{*/
#define SB_PRV_TLV_VALUE_ICI_KEY_SEL_DEAULT             (0x00000000UL)   /**< Device Default key */
#define SB_PRV_TLV_VALUE_ICI_KEY_SEL_DEV_UNIQUE         (0x00010000UL)   /**< Device Unique key */
#define SB_PRV_TLV_VALUE_ICI_KEY_SEL_INSTALLED          (0x00020000UL)   /**< Installed key */
/*! \}*/

/** IV Select of Image Cipher Info(ICI) class value */
/**\addtogroup group_tlv_ici_iv TLV Image Cipher Info IVSelect */
/*! \{*/
#define SB_PRV_TLV_VALUE_ICI_IV_SEL_DEAULT              (0x00000000UL)   /**< Device Default IV */
#define SB_PRV_TLV_VALUE_ICI_IV_SEL_DEV_UNIQUE          (0x00010000UL)   /**< Device Unique IV */
#define SB_PRV_TLV_VALUE_ICI_IV_SEL_INSTALLED           (0x00020000UL)   /**< Installed IV */
#define SB_PRV_TLV_VALUE_ICI_IV_SEL_STORED_CODE_CERT    (0x00030000UL)   /**< Use IV stored in code certificate */
/*! \}*/

/** Cryptographic algorithm */
/**\addtogroup group_tlv_crypto TLV CryptoAlgorithm */
/*! \{*/
/** Cryptographic Algorithm Bit Position */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS                    (14UL)
/** AES-128 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_AES128                 (0x0000UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** AES-192 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_AES192                 (0x0001UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** AES-256 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_AES256                 (0x0002UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** RSA 1024 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA1024                (0x0010UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** RSA 2048 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA2048                (0x0011UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** RSA 3072 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA3072                (0x0012UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** RSA 4096 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA4096                (0x0013UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** ECC NIST P-192 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P192               (0x0020UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** ECC NIST P-224 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P224               (0x0021UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** ECC NIST P-256 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P256               (0x0022UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** ECC NIST P-384 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P384               (0x0023UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** ECC NIST P-521 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P521               (0x0024UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** ECC BrainpoolP192 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP192R1            (0x0030UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** ECC BrainpoolP224 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP224R1            (0x0031UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** ECC BrainpoolP256 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP256R1            (0x0032UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** ECC BrainpoolP384 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP384R1            (0x0033UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** ECC BrainpoolP512 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP512R1            (0x0034UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** Curve25519 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_CURVE25519             (0x0040UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** Curve448 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_CURVE448               (0x0041UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** SHA2-224 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_224               (0x0050UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** SHA2-256 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_256               (0x0051UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** SHA2-384 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_384               (0x0052UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** SHA2-512 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_512               (0x0053UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** SHA3-224 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_224               (0x0054UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** SHA3-256 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_256               (0x0055UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** SHA3-384 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_384               (0x0056UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** SHA3-512 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_512               (0x0057UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** HMAC SHA2-224 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_HMAC_SHA2_224          (0x0060UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** HMAC SHA2-256 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_HMAC_SHA2_256          (0x0061UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** HMAC SHA2-384 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_HMAC_SHA2_384          (0x0062UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** HMAC SHA2-512 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_HMAC_SHA2_512          (0x0063UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** HMAC SHA3-224 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_HMAC_SHA3_224          (0x0064UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** HMAC SHA3-256 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_HMAC_SHA3_256          (0x0065UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** HMAC SHA3-384 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_HMAC_SHA3_384          (0x0066UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** HMAC SHA3-512 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_HMAC_SHA3_512          (0x0067UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** CMAC AES-128 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_CMAC_AES128            (0x0070UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** CMAC AES-192 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_CMAC_AES192            (0x0071UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** CMAC AES-256 */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_CMAC_AES256            (0x0072UL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** Algorithm full bit */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_MAX                    (0x03FFUL << (SB_PRV_TLV_TYPE_CRYPTO_ALGO_POS))
/** Algorithm mask */
#define SB_PRV_TLV_TYPE_CRYPTO_ALGO_MASK                   (SB_PRV_TLV_TYPE_CRYPTO_ALGO_MAX)
/*! \}*/

/*=====================================================================================================================
 Public type definitions
=====================================================================================================================*/
/*!********************************************************************
 * \addtogroup SBLIBManifestTypesInternal
 * \{******************************************************************/
/** Key Certificate structure */
typedef struct
{
    const st_sb_key_cert_header_t * p_header;    /**< Header information address */
    uint32_t                        tlv_len;     /**< TLV length */
    const uint8_t *                 p_tlv_top;   /**< Start address of TLV field */
} st_sb_key_cert_t;

/** Image Cipher Info value structure */
typedef struct
{
    uint32_t key_sel;                       /**< Specify the key used for encrypting / decrypting images */
    uint32_t iv_sel;                        /**< Specify the IV to be used for image encryption / decryption */
    uint32_t dest_addr;                     /**< Image output destination address after decryption */
} st_sb_img_cip_info_val_t;
/*! \}*/

/*=====================================================================================================================
 Public global variables
=====================================================================================================================*/

/*=====================================================================================================================
 Public global functions
=====================================================================================================================*/
extern sb_ret_t r_sb_mani_set_key_cert_st (const uint8_t * const p_key_cert, st_sb_key_cert_t * const p_key_cert_st);
extern sb_ret_t r_sb_mani_set_code_cert_st (const uint8_t * const p_code_cert,
                                            st_sb_code_cert_t * const p_code_cert_st);
extern sb_ret_t r_sb_mani_chk_key_cert (const st_sb_key_cert_t * const p_key_cert_st, const uint32_t key_cert_len_max);
extern sb_ret_t r_sb_mani_chk_code_cert (const st_sb_code_cert_t * const p_code_cert_st,
                                        const uint32_t code_cert_len_max);
extern sb_ret_t r_sb_mani_parse_tlvs (const uint8_t * const p_top, const uint32_t tlv_len,
                                    const uint32_t num_of_search_type,
                                    const st_sb_search_tlv_type_t * const p_search_types, st_sb_tlv_t * const p_tlvs);

#endif /* R_SB_MANIFEST_H */
/*=====================================================================================================================
 End of File
=====================================================================================================================*/
