/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*!********************************************************************************************************************
* \file             : r_sb_sb.c
* \par version      : 1.00
* \par Product Name : Renesas-SB-Lib FSBL Custom
* \par Device(s)    : Does not depend on specific hardware
* \par Description  : This file implements the SecureBoot module APIs.
**********************************************************************************************************************/

/*!***********************************************************
 * \addtogroup  SBLIBSecureBoot
 * \{
 * \addtogroup  SBLIBSecureBootAPIs              SecureBoot APIs
 * \addtogroup  SBLIBSecureBootDefinesInternal   SecureBoot Internal Definitions
 * \addtogroup  SBLIBSecureBootAPIsInternal      SecureBoot Internal APIs
 * \}********************************************************/

/*=====================================================================================================================
 Includes <System Includes> , "Project Includes"
=====================================================================================================================*/
#include <stddef.h>
#include "r_cip_drv_api.h"
#include "r_sb_build_config.h"
#include "r_sb_api.h"
#include "r_sb_manifest.h"
#include "r_sb_cmn.h"
#include "r_sb_cmn_drv.h"
#include "r_sb_sb.h"

/*=====================================================================================================================
 Private macro definitions
=====================================================================================================================*/
/*!********************************************************************
 * \addtogroup SBLIBSecureBootDefinesInternal
 * \{
 * \addtogroup  group_tlv_search_type
 * \addtogroup  group_tlv_search_kc
 * \addtogroup  group_tlv_search_sb_cc
 * \addtogroup  group_tlv_search_ci
 * \addtogroup  group_tlv_search_sb_mac
 * \}*****************************************************************/

/** Search by certificate chain verification */
/**\addtogroup group_tlv_search_type TLV search type and mask */
/*! \{*/
/** Class & Use type of OEM root public key */
#define SB_PRV_TLV_KEY_OEM_ROOT_PK_TYPE (SB_PRV_TLV_TYPE_CLS_KEY  | SB_PRV_TLV_TYPE_CLS_KEY_UT_OEM_ROOT_PK)
/** Class & Use type of Image public key */
#define SB_PRV_TLV_KEY_IMG_PK_TYPE      (SB_PRV_TLV_TYPE_CLS_KEY  | SB_PRV_TLV_TYPE_CLS_KEY_UT_IMG_PK)
/** Class mask & Use type mask of key */
#define SB_PRV_TLV_KEY_MASK             (SB_PRV_TLV_TYPE_CLS_MASK | SB_PRV_TLV_TYPE_CLS_KEY_UT_MASK)

/** Class & Use type of Image public key hash */
#define SB_PRV_TLV_HASH_IMG_PK_TYPE     (SB_PRV_TLV_TYPE_CLS_HASH | SB_PRV_TLV_TYPE_CLS_HASH_UT_IMG_PK)
/** Class & Use type of Image hash */
#define SB_PRV_TLV_HASH_IMG_TYPE        (SB_PRV_TLV_TYPE_CLS_HASH | SB_PRV_TLV_TYPE_CLS_HASH_UT_IMG)
/** Class & Use type of Image hash */
#define SB_PRV_TLV_HASH_ENCIMG_TYPE     (SB_PRV_TLV_TYPE_CLS_HASH | SB_PRV_TLV_TYPE_CLS_HASH_UT_ENCIMG)
/** Class mask & Use type mask of Image public key hash */
#define SB_PRV_TLV_HASH_MASK            (SB_PRV_TLV_TYPE_CLS_MASK | SB_PRV_TLV_TYPE_CLS_HASH_UT_MASK)

/** Class & Use type of Key Certificate signature */
#define SB_PRV_TLV_SIGN_CERT_TYPE        (SB_PRV_TLV_TYPE_CLS_SIGN | SB_PRV_TLV_TYPE_CLS_SIGN_UT_CERT)
/** Class & Use type of Code Certificate and image signature */
#define SB_PRV_TLV_SIGN_CERT_IMG_TYPE    (SB_PRV_TLV_TYPE_CLS_SIGN | SB_PRV_TLV_TYPE_CLS_SIGN_UT_CODE_CERT_AND_IMG)
/** Class & Use type of Code Certificate and encryption image signature */
#define SB_PRV_TLV_SIGN_CERT_ENCIMG_TYPE (SB_PRV_TLV_TYPE_CLS_SIGN | SB_PRV_TLV_TYPE_CLS_SIGN_UT_CODE_CERT_AND_ENCIMG)
/** Class mask & Use type mask of signature */
#define SB_PRV_TLV_SIGN_MASK             (SB_PRV_TLV_TYPE_CLS_MASK | SB_PRV_TLV_TYPE_CLS_SIGN_UT_MASK)

/** Class & Use type of Code Certificate + Image MAC */
#define SB_PRV_TLV_MAC_CERT_IMG_TYPE        (SB_PRV_TLV_TYPE_CLS_MAC  | SB_PRV_TLV_TYPE_CLS_MAC_UT_CODE_CERT_AND_IMG)
/** Class & Use type of Code Certificate + Encrypted Image MAC */
#define SB_PRV_TLV_MAC_CERT_ENCIMG_TYPE     (SB_PRV_TLV_TYPE_CLS_MAC  | SB_PRV_TLV_TYPE_CLS_MAC_UT_CODE_CERT_AND_ENCIMG)
/** Class mask & Use type mask of MAC */
#define SB_PRV_TLV_MAC_MASK                 (SB_PRV_TLV_TYPE_CLS_MASK | SB_PRV_TLV_TYPE_CLS_MAC_UT_MASK)

/** Class & Use type of Image Cipher IV */
#define SB_PRV_TLV_IMG_CIP_IV_TYPE          (SB_PRV_TLV_TYPE_CLS_IV   | SB_PRV_TLV_TYPE_CLS_IV_UT_IMG_CIPHER)
/** Class & Use type of Temp Image Decryption IV */
#define SB_PRV_TLV_CI_TMP_IMG_DEC_IV_TYPE   (SB_PRV_TLV_TYPE_CLS_IV   | SB_PRV_TLV_TYPE_CLS_IV_UT_TMP_IMG_DEC)
/** Class mask & Use type mask of Temp Image Decryption IV */
#define SB_PRV_TLV_IV_MASK                  (SB_PRV_TLV_TYPE_CLS_MASK | SB_PRV_TLV_TYPE_CLS_IV_UT_MASK)

/** Class & Use type of Image Cipher Info */
#define SB_PRV_TLV_IMG_CIP_INFO_TYPE        (SB_PRV_TLV_TYPE_CLS_ICI  | SB_PRV_TLV_TYPE_CLS_ICI_UT_IMG_ENC_DEC)
/** Class & Use type of Temp Image Decryption Info */
#define SB_PRV_TLV_CI_TMP_IMG_DEC_INFO_TYPE (SB_PRV_TLV_TYPE_CLS_ICI  | SB_PRV_TLV_TYPE_CLS_ICI_UT_TMP_IMG_DEC)
/** Class mask & Use type mask of Image Cipher Info */
#define SB_PRV_TLV_ICI_MASK                 (SB_PRV_TLV_TYPE_CLS_MASK | SB_PRV_TLV_TYPE_CLS_ICI_UT_MASK)
/*! \}*/

/** key certificate TLV to search SecureBoot & CheckIntegrity */
/**\addtogroup group_tlv_search_kc TLV search Key Certificate */
/*! \{*/
#define SB_PRV_TLV_KEY_CERT_KEY_OEM_ROOT_PK_IDX  (0U)  /**< Index of OEM root public key */
#define SB_PRV_TLV_KEY_CERT_KEY_IMG_PK_IDX       (1U)  /**< Index of Image public key */
#define SB_PRV_TLV_KEY_CERT_HASH_IMG_PK_IDX      (2U)  /**< Index of Image public key hash */
#define SB_PRV_TLV_KEY_CERT_SIGN_CERT_IDX        (3U)  /**< Index of Key Certificate signature */
#define SB_PRV_TLV_KEY_CERT_NUM                  (4U)  /**< Number of Key Certificate TLVs */
/*! \}*/

/** code certificate TLV to search by SecureBoot(certificate chain verification) */
/**\addtogroup group_tlv_search_sb_cc TLV search Code Certificate for Certificate Chain verification */
/*! \{*/
#define SB_PRV_TLV_CC_CODE_CERT_KEY_IMG_PK_IDX   (0U)  /**< Index of Image public key */
#define SB_PRV_TLV_CC_CODE_CERT_HASH_IMG_IDX     (1U)  /**< Index of Image hash */
#define SB_PRV_TLV_CC_CODE_CERT_HASH_ENCIMG_IDX  (2U)  /**< Index of encryption image hash */
#define SB_PRV_TLV_CC_CODE_CERT_IMG_CIP_INFO_IDX (3U)  /**< Index of Image Cipher Info */
#define SB_PRV_TLV_CC_CODE_CERT_IMG_CIP_IV_IDX   (4U)  /**< Index of Image Cipher IV */
#define SB_PRV_TLV_CC_CODE_CERT_SIGN_CERT_IDX    (5U)  /**< Index of Certificate signature */
#define SB_PRV_TLV_CC_CODE_CERT_SIGN_IMG_IDX     (6U)  /**< Index of Code Certificate and image signature */
#define SB_PRV_TLV_CC_CODE_CERT_SIGN_ENCIMG_IDX  (7U)  /**< Index of Code Certificate and encryption image signature */
#define SB_PRV_TLV_CC_CODE_CERT_NUM              (8U)  /**< Number of Code Certificate TLVs for SecureBoot */
/*! \}*/

/** code certificate TLV to search by SecureBoot(MAC verification) */
/**\addtogroup group_tlv_search_sb_mac TLV search Code certificate for MAC verification */
/*! \{*/
#define SB_PRV_TLV_MAC_IMG_CIP_INFO_IDX             (0U)  /**< Index number of Image Cipher Info */
#define SB_PRV_TLV_MAC_IMG_CIP_IV_IDX               (1U)  /**< Index number of Image Cipher IV */
#if (SB_CFG_SB_CERT_CHAIN_USE_IMG_PK == 1U) /* (Use only when SB_CFG_SB_CERT_CHAIN_USE_IMG_PK is Enable) */
#define SB_PRV_TLV_MAC_KEY_IMG_PK_IDX               (2U)  /**< Index number of Image public key */
#define SB_PRV_TLV_MAC_NUM                          (3U)  /**< Number of Code Certificate TLVs for MAC verify */
#else /* #if (SB_CFG_SB_CERT_CHAIN_USE_IMG_PK == 1U) */
#define SB_PRV_TLV_MAC_NUM                          (2U)  /**< Number of Code Certificate TLVs for MAC verify */
#endif /* #if (SB_CFG_SB_CERT_CHAIN_USE_IMG_PK == 1U) */
/*! \}*/

/** code certificate TLV to search by CheckIntegrity */
/**\addtogroup group_tlv_search_ci TLV search Code Certificate for CheckIntegrity */
/*! \{*/
#define SB_PRV_TLV_CI_CODE_CERT_KEY_IMG_PK_IDX       (0U) /**< Index of Image public key */
#define SB_PRV_TLV_CI_CODE_CERT_HASH_IMG_IDX         (1U) /**< Index of Image hash */
#define SB_PRV_TLV_CI_CODE_CERT_IMG_CIP_INFO_IDX     (2U) /**< Index of Image Cipher Info */
#define SB_PRV_TLV_CI_CODE_CERT_IMG_CIP_IV_IDX       (3U) /**< Index of Image Cipher IV */
#define SB_PRV_TLV_CI_CODE_CERT_TMP_IMG_DEC_INFO_IDX (4U) /**< Index of Temp Image Decryption Info */
#define SB_PRV_TLV_CI_CODE_CERT_TMP_IMG_DEC_IV_IDX   (5U) /**< Index of Temp Image Decryption IV */
#define SB_PRV_TLV_CI_CODE_CERT_SIGN_CERT_IDX        (6U) /**< Index of Certificate signature */
#define SB_PRV_TLV_CI_CODE_CERT_SIGN_IMG_IDX         (7U) /**< Index of Code Certificate and image signature */
#define SB_PRV_TLV_CI_CODE_CERT_NUM                  (8U) /**< Number of Code Certificate TLVs for CheckIntegrity */
/*! \}*/

/*=====================================================================================================================
 Private type definitions
=====================================================================================================================*/

/*=====================================================================================================================
 Public global variables
=====================================================================================================================*/

/*=====================================================================================================================
 Private global variables
=====================================================================================================================*/

/*=====================================================================================================================
 Private function prototypes
=====================================================================================================================*/

#if (SB_CFG_CHECK_INTEGRITY == 1U)
static sb_ret_t sb_check_check_integrity_tlv (const st_sb_tlv_t * const p_key_cert_tlvs,
                                            const st_sb_tlv_t * const p_code_cert_tlvs);
#endif /* (SB_CFG_CHECK_INTEGRITY == 1U) */

#if (SB_CFG_SB_CERT_CHAIN_VERIFICATION == 1U) || (SB_CFG_CHECK_INTEGRITY == 1U)
static sb_ret_t sb_get_cc_tlv (const st_sb_key_cert_t * const p_key_cert_st,
                                const st_sb_code_cert_t * const p_code_cert_st,
                                const st_sb_search_tlv_type_t * const p_search_tlv_key_cert,
                                const uint32_t search_tlv_key_cert_num,
                                const st_sb_search_tlv_type_t * const p_search_tlv_code_cert,
                                const uint32_t search_tlv_code_cert_num,
                                st_sb_tlv_t * const p_key_cert_tlvs,
                                st_sb_tlv_t * const p_code_cert_tlvs);
#endif /* (SB_CFG_SB_CERT_CHAIN_VERIFICATION == 1U) || (SB_CFG_CHECK_INTEGRITY == 1U) */

/*=====================================================================================================================
 Public function definitions
=====================================================================================================================*/

/**********************************************************************************************************************
* Function Name : r_sb_sb_check_integrity
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBSecureBootAPIsInternal
 * \brief       Verify the integrity of the image by certificate chain verification and create a MAC
 *              for the Code Certificate and the image with a HUK derived key
 * \param       [in]   p_key_cert_st           Start address of Key Certificate Structure
 * \param       [in]   p_code_cert_st          Start address of Code Certificate Structure
 * \param       [in]   mac_type                MAC algorithm type used to generate the MAC of the code certificate
 * \param       [out]  p_tag                   Specify MAC tag storage address
 * \return
 *  - #SB_RET_SUCCESS:                          Successful completion
 *  - #SB_RET_SAME_IMAGE_VERSION:               An image with the same version as the current image version is
 *                                              installed
 *  - #SB_RET_ERR_INTERNAL_FAIL:                Internal processing failed
 *  - #SB_RET_ERR_MANI_TLV_FIELD_ERR:              Missing required TLV field
 *  - #SB_RET_ERR_MANI_TLV_INVALID_LEN:         The length of the TLV field has a size that exceeds the end of
 *                                              the manifest.
 *  - #SB_RET_ERR_MANI_MISMATCH_SIGN_ALGORITHM: There is a wrong combination of signature algorithms
 *  - #SB_RET_ERR_MANI_UNSUPPORTED_ALGORITHM:      There is a wrong combination of signature algorithms
 *  - #SB_RET_ERR_CRYPTO_FAIL:                     Encryption failed
 *  - #SB_RET_ERR_CRYPTO_AUTH_FAIL:                Verification failed
 *  - #SB_RET_ERR_CRYPTO_UNSUPPORTED_ALGORITHM:    Unsupported algorithm
 *  - #SB_RET_ERR_CRYPTO_PARAM_ERR:                Parameter error
 *  - #SB_RET_ERR_LOWER_IMAGE_VERSION:          An image version lower than the current image version is installed
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - R_CIP_DRV_CheckImageVersion
 *  - R_CIP_DRV_PrcDeriveMacKeyFromHuk
 *  - R_CIP_DRV_PrcCheckIntegrity
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Check the value by parsing the TLV from the manifest
 *      - Parse the Image Cipher info TLV of the code certificate and check the value
 *      - Implement the following as a glitch countermeasure :
 *        - Add a flow counter before and after calling R_CIP_DRV_PrcCheckIntegrity
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# Initialize the variable cip_ret with CIP_DRV_RET_LOWER_IMAGE_VERSION
 * -# Initialize the variable ret_ver with #SB_RET_ERR_LOWER_IMAGE_VERSION
 * -# Set TLV search condition of Key Certificate to search_tlv_key_cert
 * -# Set TLV search condition of Code Certificate to search_tlv_code_cert
 * -# Set TLV search condition of Image Cipher Info to search_tlv_enc_img
 * -# If (NULL != p_key_cert_st) && (NULL != p_code_cert_st) && (NULL != p_code_cert_st->p_header) && (NULL != p_tag)
 *   -# Get TLV for key certificate and code certificate with #sb_get_cc_tlv
 *   -# Set function result to ret
 *   -# If #SB_RET_SUCCESS == ret
 *     -# To clear ret, set #SB_RET_ERR_INTERNAL_FAIL to ret
 *     -# Check certificate chain verification tlv with #sb_check_check_integrity_tlv
 *     -# If #SB_RET_SUCCESS == ret
 *       -# To clear ret, set #SB_RET_ERR_INTERNAL_FAIL to ret
 *       -# Set key certificate driver parameters with #r_sb_cmn_drv_set_cc_key_cert_param
 *       -# Set function result to ret
 *       -# If #SB_RET_SUCCESS == ret
 *         -# To clear ret, set #SB_RET_ERR_INTERNAL_FAIL to ret
 *         -# If the certificate signature value of the code certificate is not NULL
 *           -# Set the start address of the certificate signature TLV to p_code_cert_sign_tlv.
 *           -# Set the start address of the Image hash TLV  to p_img_hash_tlv.
 *         -# Else
 *           -# Set the start address of the Encrypted Image Signature TLV to p_code_cert_sign_tlv.
 *           -# Set null to p_img_hash_tlv
 *         -# Set code certificate driver parameters with #r_sb_cmn_drv_set_cc_code_cert_param
 *         -# Set function result to ret
 *         -# If #SB_RET_SUCCESS == ret
 *           -# To clear ret, set #SB_RET_ERR_INTERNAL_FAIL to ret
 *           -# If (p_code_cert_st->p_header->flags & #SB_PRV_CODE_CERT_HEADER_FLAGS_IMG_CIPHER_ENC)
 *             -# <B>--- If #SB_CFG_IMAGE_ENC_DEC is enabled ---</B>
 *             -# Set the address of img_param to p_img_param
 *             -# Set Image Cipher Info parameters with #r_sb_cmn_drv_set_cipher_img_param
 *             -# Set function result to ret
 *             -# <B>--- Else #SB_CFG_IMAGE_ENC_DEC is enabled ---</B>
 *             -# Set #SB_RET_ERR_UNSUPPORTED_FUNCTION to ret
 *             -# <B>--- Endif #SB_CFG_IMAGE_ENC_DEC is enabled ---</B>
 *           -# Else
 *             -# Set NULL to p_img_param
 *             -# Set ret to #SB_RET_SUCCESS
 *           -# If #SB_RET_SUCCESS == ret
 *             -# If (p_code_cert_st->p_header->flags & #SB_PRV_CODE_CERT_HEADER_FLAGS_TMP_IMG_DEC)
 *               -# <B>--- If #SB_CFG_IMAGE_ENC_DEC is enabled ---</B>
 *               -# Set the address of tmp_img_param to p_tmp_img_param
 *               -# Set Image Cipher Info parameters with #r_sb_cmn_drv_set_cipher_img_param
 *               -# Set function result to ret
 *               -# <B>--- Else #SB_CFG_IMAGE_ENC_DEC is enabled ---</B>
 *               -# Set #SB_RET_ERR_UNSUPPORTED_FUNCTION to ret
 *               -# <B>--- Endif #SB_CFG_IMAGE_ENC_DEC is enabled ---</B>
 *             -# Else
 *               -# Set NULL to p_tmp_img_param
 *             -# If #SB_RET_SUCCESS == ret
 *               -# To clear ret, set ret to #SB_RET_ERR_INTERNAL_FAIL
 *               -# Call SB-Driver API R_CIP_DRV_CheckImageVersion
 *               -# Set SB-Driver API result to cip_ret
 *               -# Get the return code from the value of cpi_ret with #r_sb_cmn_drv_get_sb_ret_from_cip_ret
 *               -# Set function result to ret_ver
 *               -# To clear ret, set cip_ret to CIP_DRV_RET_FAIL
 *               -# If (#SB_RET_SUCCESS == ret_ver) || (#SB_RET_SAME_IMAGE_VERSION == ret_ver)
 *                 -# Call SB-Driver API R_CIP_DRV_PrcDeriveMacKeyFromHuk
 *                 -# Set SB-Driver API result to cip_ret
 *                 -# Get the return code from the value of cpi_ret with #r_sb_cmn_drv_get_sb_ret_from_cip_ret
 *                 -# Set function result to ret
 *                 -# If #SB_RET_SUCCESS == ret
 *                   -# Get MAC algorithm with #r_sb_cmn_drv_get_mac_algo_from_sb_mac_type
 *                   -# Set function result to mac_algo
 *                   -# To clear ret, set #SB_RET_ERR_INTERNAL_FAIL to ret and set CIP_DRV_RET_FAIL to cip_ret
 *                   -# Add #SB_PRV_CMN_FC_CHECKINTEGRITY_CNT to flow counter with #r_sb_cmn_fc_add_counter
 *                   -# Call SB-Driver API R_CIP_DRV_PrcCheckIntegrity
 *                   -# Set SB-Driver API result to cip_ret
 *                   -# Get the return code from the value of cpi_ret with #r_sb_cmn_drv_get_sb_ret_from_cip_ret
 *                   -# Set function result to ret
 *                   -# Add #SB_PRV_CMN_FC_CHECKINTEGRITY_CNT to flow counter with #r_sb_cmn_fc_add_counter
 *                   -# If #SB_RET_SUCCESS == ret
 *                     -# Set ret_ver to ret
 *                   -# Else
 *                     -# Do nothing
 *                 -# Else
 *                   -# Do nothing
 *               -# Else
 *                 -# Set ret_ver to ret
 *             -# Else
 *               -# Do nothing
 *           -# Else
 *             -# Do nothing
 *         -# Else
 *           -# Do nothing
 *       -# Else
 *         -# Do nothing
 *     -# Else
 *       -# Do nothing
 *   -# Else
 *     -# Do nothing
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * Note: The call graph below dose not include SB-Driver APIs.
 * \callgraph
 *********************************************************************************************************************/
#if (SB_CFG_CHECK_INTEGRITY == 1U)
sb_ret_t r_sb_sb_check_integrity(const st_sb_key_cert_t* const p_key_cert_st,
                                    const st_sb_code_cert_t* const p_code_cert_st,
                                    const e_sb_mac_type_t mac_type, uint32_t* const p_tag)
{
    /*-----------------------------------------------------------------------------------------------------------------
     Local variables
    -----------------------------------------------------------------------------------------------------------------*/
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    sb_ret_t                        ret_ver = SB_RET_ERR_LOWER_IMAGE_VERSION;   /* for version check */
    cip_drv_ret_t                   cip_ret = CIP_DRV_RET_LOWER_IMAGE_VERSION;
    uint32_t                        mac_algo;
    st_sb_tlv_t                     key_cert_tlvs[SB_PRV_TLV_KEY_CERT_NUM];
    st_sb_tlv_t                     code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_NUM];
    const st_sb_tlv_t *             p_code_cert_sign_tlv;
    const st_sb_tlv_t *             p_img_hash_tlv;
    st_cip_drv_cc_key_cert_param_t  key_cert_param;
    st_cip_drv_cc_code_cert_param_t code_cert_param;
    st_cip_drv_cipher_img_param_t * p_img_param;
    st_cip_drv_cipher_img_param_t * p_tmp_img_param;
#if (SB_CFG_IMAGE_ENC_DEC == 1U)
    st_cip_drv_cipher_img_param_t   img_param;
    st_cip_drv_cipher_img_param_t   tmp_img_param;
#endif /* (SB_CFG_IMAGE_ENC_DEC == 1U) */
    const st_sb_tlv_t *             p_key_cert_signer_pk_tlv;

    const st_sb_search_tlv_type_t search_tlv_key_cert[SB_PRV_TLV_KEY_CERT_NUM] =
    {
        {SB_PRV_TLV_KEY_OEM_ROOT_PK_TYPE,   SB_PRV_TLV_KEY_MASK},   /* KEY_CERT_KEY_OEM_ROOT_PK_IDX */
        {SB_PRV_TLV_KEY_IMG_PK_TYPE,        SB_PRV_TLV_KEY_MASK},   /* KEY_CERT_KEY_IMG_PK_IDX */
        {SB_PRV_TLV_HASH_IMG_PK_TYPE,       SB_PRV_TLV_HASH_MASK},  /* KEY_CERT_HASH_IMG_PK_IDX */
        {SB_PRV_TLV_SIGN_CERT_TYPE,         SB_PRV_TLV_SIGN_MASK}   /* KEY_CERT_SIGN_CERT_IDX */
    };

    const st_sb_search_tlv_type_t search_tlv_code_cert[SB_PRV_TLV_CI_CODE_CERT_NUM] =
    {
        {SB_PRV_TLV_KEY_IMG_PK_TYPE,            SB_PRV_TLV_KEY_MASK},   /* CI_CODE_CERT_KEY_IMG_PK_IDX */
        {SB_PRV_TLV_HASH_IMG_TYPE,              SB_PRV_TLV_HASH_MASK},  /* CI_CODE_CERT_HASH_IMG_IDX */
        {SB_PRV_TLV_IMG_CIP_INFO_TYPE,          SB_PRV_TLV_ICI_MASK},   /* CI_CODE_CERT_IMG_CIP_INFO_IDX */
        {SB_PRV_TLV_IMG_CIP_IV_TYPE,            SB_PRV_TLV_IV_MASK},    /* CI_CODE_CERT_IMG_CIP_IV_IDX */
        {SB_PRV_TLV_CI_TMP_IMG_DEC_INFO_TYPE,   SB_PRV_TLV_ICI_MASK},   /* CI_CODE_CERT_TMP_IMG_DEC_INFO_IDX */
        {SB_PRV_TLV_CI_TMP_IMG_DEC_IV_TYPE,     SB_PRV_TLV_IV_MASK},    /* CI_CODE_CERT_TMP_IMG_DEC_IV_IDX */
        {SB_PRV_TLV_SIGN_CERT_TYPE,             SB_PRV_TLV_SIGN_MASK},  /* CI_CODE_CERT_SIGN_CERT_IDX */
        {SB_PRV_TLV_SIGN_CERT_IMG_TYPE,         SB_PRV_TLV_SIGN_MASK}   /* CI_CODE_CERT_SIGN_IMG_IDX */
    };

    /*-----------------------------------------------------------------------------------------------------------------
     Function body
    -----------------------------------------------------------------------------------------------------------------*/
    if ((NULL != p_key_cert_st) && (NULL != p_code_cert_st) && (NULL != p_code_cert_st->p_header) && (NULL != p_tag))
    {
        /* Get TLVs */
        ret = sb_get_cc_tlv(p_key_cert_st, p_code_cert_st,
                            search_tlv_key_cert, SB_PRV_TLV_KEY_CERT_NUM,
                            search_tlv_code_cert, SB_PRV_TLV_CI_CODE_CERT_NUM,
                            key_cert_tlvs, code_cert_tlvs);
        if (SB_RET_SUCCESS == ret)
        {
            /* Clear ret */
            ret = SB_RET_ERR_INTERNAL_FAIL;
            (void) ret;

            /* Check cert chain tlv */
            ret = sb_check_check_integrity_tlv(key_cert_tlvs, code_cert_tlvs);
            if (SB_RET_SUCCESS == ret)
            {
                /* Clear ret */
                ret = SB_RET_ERR_INTERNAL_FAIL;
                (void) ret;

                /* Select kye cert signer public key TLV */
                p_key_cert_signer_pk_tlv = (NULL == key_cert_tlvs[SB_PRV_TLV_KEY_CERT_KEY_OEM_ROOT_PK_IDX].p_val) ?
                                            (&key_cert_tlvs[SB_PRV_TLV_KEY_CERT_KEY_IMG_PK_IDX]) :
                                            (&key_cert_tlvs[SB_PRV_TLV_KEY_CERT_KEY_OEM_ROOT_PK_IDX]);

                /* Set key certificate driver parameters */
                ret = r_sb_cmn_drv_set_cc_key_cert_param(p_key_cert_st,
                                                            &key_cert_tlvs[SB_PRV_TLV_KEY_CERT_HASH_IMG_PK_IDX],
                                                            p_key_cert_signer_pk_tlv,
                                                            &key_cert_tlvs[SB_PRV_TLV_KEY_CERT_SIGN_CERT_IDX],
                                                            &key_cert_param);
                if (SB_RET_SUCCESS == ret)
                {
                    /* Clear ret */
                    ret = SB_RET_ERR_INTERNAL_FAIL;
                    (void) ret;

                    /* Set code certificate driver parameters */
                    if (NULL != code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_SIGN_CERT_IDX].p_val)
                    {
                        p_code_cert_sign_tlv = &code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_SIGN_CERT_IDX];
                        p_img_hash_tlv = &code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_HASH_IMG_IDX];
                    }
                    else  /* NULL != code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_SIGN_IMG_IDX].p_val */
                    {
                        p_code_cert_sign_tlv = &code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_SIGN_IMG_IDX];
                        p_img_hash_tlv = NULL;  /* Does not use image hash TLV */
                    }

                    /* Set code certificate driver parameters */
                    ret = r_sb_cmn_drv_set_cc_code_cert_param(p_code_cert_st,
                                                                p_code_cert_st->p_header->dest_addr,
                                                                &code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_KEY_IMG_PK_IDX],
                                                                p_code_cert_sign_tlv,
                                                                p_img_hash_tlv,
                                                                &code_cert_param);
                    if (SB_RET_SUCCESS == ret)
                    {
                        /* Clear ret */
                        ret = SB_RET_ERR_INTERNAL_FAIL;
                        (void) ret;

                        /* Set driver parameters of image cipher */
                        if ((p_code_cert_st->p_header->flags & SB_PRV_CODE_CERT_HEADER_FLAGS_IMG_CIPHER_ENC) != 0UL)
                        {
#if (SB_CFG_IMAGE_ENC_DEC == 1U)
                            p_img_param = &img_param;
                            ret = r_sb_cmn_drv_set_cipher_img_param(p_code_cert_st,
                                                            &code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_IMG_CIP_INFO_IDX],
                                                            &code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_IMG_CIP_IV_IDX],
                                                            SB_PRV_TRUE,
                                                            CIP_DRV_CIPHER_TIMING_AFTER_VERIFY,
                                                            p_img_param);
#else /* !(SB_CFG_IMAGE_ENC_DEC == 1U) */
                            /* Code decryption not supported */
                            ret = SB_RET_ERR_UNSUPPORTED_FUNCTION;
#endif /* (SB_CFG_IMAGE_ENC_DEC == 1U) */
                        }
                        else
                        {
                            p_img_param = NULL;

                            /* Set ret to the success code */
                            ret = SB_RET_SUCCESS;
                        }

                        if (SB_RET_SUCCESS == ret)
                        {
                            /* Set driver parameters of temporary image decryption */
                            if ((p_code_cert_st->p_header->flags & SB_PRV_CODE_CERT_HEADER_FLAGS_TMP_IMG_DEC) != 0UL)
                            {
#if (SB_CFG_IMAGE_ENC_DEC == 1U)
                                p_tmp_img_param = &tmp_img_param;
                                ret = r_sb_cmn_drv_set_cipher_img_param(p_code_cert_st,
                                                    &code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_TMP_IMG_DEC_INFO_IDX],
                                                    &code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_TMP_IMG_DEC_IV_IDX],
                                                    SB_PRV_TRUE,
                                                    CIP_DRV_CIPHER_TIMING_BEFORE_VERIFY,
                                                    p_tmp_img_param);
#else /* !(SB_CFG_IMAGE_ENC_DEC == 1U) */
                                /* Code decryption not supported */
                                ret = SB_RET_ERR_UNSUPPORTED_FUNCTION;
#endif /* (SB_CFG_IMAGE_ENC_DEC == 1U) */
                            }
                            else
                            {
                                p_tmp_img_param = NULL;
                            }

                            if (SB_RET_SUCCESS == ret)
                            {
                                /* Clear ret */
                                ret = SB_RET_ERR_INTERNAL_FAIL;
                                (void) ret;

                                /* Check image version */
                                cip_ret = R_CIP_DRV_CheckImageVersion(p_code_cert_st->p_header->img_version,
                                                                        p_code_cert_st->p_header->build_num);
                                ret_ver = r_sb_cmn_drv_get_sb_ret_from_cip_ret(cip_ret);

                                /* Clear ret */
                                cip_ret = CIP_DRV_RET_FAIL;
                                (void) cip_ret;

                                if ((SB_RET_SUCCESS == ret_ver) || (SB_RET_SAME_IMAGE_VERSION == ret_ver))
                                {
                                    /* Call derive MAC Key from HUK */
                                    cip_ret = R_CIP_DRV_PrcDeriveMacKeyFromHuk();
                                    ret = r_sb_cmn_drv_get_sb_ret_from_cip_ret(cip_ret);
                                    if (SB_RET_SUCCESS == ret)
                                    {
                                        /* get MAC algorithm */
                                        mac_algo = r_sb_cmn_drv_get_mac_algo_from_sb_mac_type(mac_type);

                                        /* Clear ret */
                                        cip_ret = CIP_DRV_RET_AUTH_FAIL;
                                        (void) cip_ret;
                                        ret = SB_RET_ERR_INTERNAL_FAIL;
                                        (void) ret;

                                        /* Add verify count to flow counter */
                                        r_sb_cmn_fc_add_counter(SB_PRV_CMN_FC_CHECKINTEGRITY_CNT);

                                        /* Call check integrity */
                                        cip_ret = R_CIP_DRV_PrcCheckIntegrity(&key_cert_param,
                                                                                &code_cert_param,
                                                                                p_tmp_img_param,
                                                                                p_img_param,
                                                                                mac_algo,
                                                                                p_tag);
                                        ret = r_sb_cmn_drv_get_sb_ret_from_cip_ret(cip_ret);
                                        r_sb_cmn_fc_add_counter(SB_PRV_CMN_FC_CHECKINTEGRITY_CNT);
                                        if(SB_RET_SUCCESS == ret)
                                        {
                                            /* Set version check result(SUCCESS or SAME_IMAGE_VERSION) to ret */
                                            ret = ret_ver;
                                        }
                                        else
                                        {
                                            /* Do nothing */
                                        }
                                    }
                                    else
                                    {
                                        /* Do nothing */
                                    }
                                }
                                else
                                {
                                    /* Set version check result to ret */
                                    ret = ret_ver;
                                }
                            }
                            else
                            {
                                /* Do nothing */
                            }
                        }
                        else
                        {
                            /* Do nothing */
                        }
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
                else
                {
                    /* Do nothing */
                }
            }
            else
            {
                /* Do nothing */
            }
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /* If there are null arguments, return SB_RET_ERR_INTERNAL_FAIL */
    }

    return ret;
}
#endif /* (SB_CFG_CHECK_INTEGRITY == 1U) */
/**********************************************************************************************************************
* End of function r_sb_sb_check_integrity()
**********************************************************************************************************************/

/*=====================================================================================================================
 Private function definitions
=====================================================================================================================*/

/**********************************************************************************************************************
* Function Name : sb_check_check_integrity_tlv
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBSecureBootAPIsInternal
 * \brief       Check the obtained TLV of Check Integrity
 * \param       [in]   p_key_cert_tlvs         Start address of Key Certificate TLVs
 * \param       [in]   p_code_cert_tlvs        Start address of Code Certificate TLVs
 * \return
 *  - #SB_RET_SUCCESS:                          Successful completion
 *  - #SB_RET_ERR_INTERNAL_FAIL:                Internal processing failed
 *  - #SB_RET_ERR_UNSUPPORTED_FUNCTION:         Unsupported function executed
 *  - #SB_RET_ERR_MANI_TLV_FIELD_ERR:           Missing required TLV fields
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Check that the TLV of the key certificate has Image public key Hash and Key Certificate signature
 *      - Confirm that the OEM root public key or Image public key is specified in the key class TLV of the
 *        key certificate. (NG if both are specified)
 *      - Confirm that Code Certificate TLV has signature verification public key
 *      - Confirm that Code Certificate TLV has signature
 *      - Confirm that Code Certificate TLV has image hash (When only the certificate is to be signed)
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# If (NULL != p_key_cert_tlvs) && (NULL != p_code_cert_tlvs)
 *   -# If the value of Image public key hash TLV of the key certificate is not NULL and
 *      the value of Key Certificate signature TLV is not NULL
 *     -# If the value of the OEM_ROOT_PK TLV of the key certificate is not NULL and
 *        the value of the Image public key TLV is NULL, or \n
 *        if the value of the OEM_ROOT_PK TLV of the key certificate is NULL and
 *        the value of the Image public key TLV is not NULL
 *       -# If the value of Image public key TLV of the code certificate is not NULL
 *         -# If only one of the following is non-NULL \n
 *            Certificate Signature TLV \n
 *            Certificate and Image Signature TLV \n
 *           -# If Signature TLV is Certificate only
 *             -# If only one of the following is non-NULL \n
 *                Image Hash TLV \n
 *               -# TLV field OK. Set ret to #SB_RET_SUCCESS
 *             -# Else
 *               -# Set ret to #SB_RET_ERR_MANI_TLV_FIELD_ERR
 *           -# Else
 *             -# TLV field OK. Set ret to #SB_RET_SUCCESS
 *         -# Else
 *           -# Set ret to #SB_RET_ERR_MANI_TLV_FIELD_ERR
 *         -# Else
 *           -# Set ret to #SB_RET_ERR_MANI_TLV_FIELD_ERR
 *       -# Else
 *         -# Set ret to #SB_RET_ERR_MANI_TLV_FIELD_ERR
 *     -# Else
 *       -# Set ret to #SB_RET_ERR_MANI_TLV_FIELD_ERR
 *   -# Else
 *     -# Set ret to #SB_RET_ERR_MANI_TLV_FIELD_ERR
 *   -# <B>--- If #SB_CFG_SB_CERT_CHAIN_USE_IMG_PK is disabled ---</B>
 *   -# If (SB_RET_SUCCESS == ret) &&
 *          (NULL != p_key_cert_tlvs[SB_PRV_TLV_KEY_CERT_KEY_IMG_PK_IDX].p_val)
 *     -# Set ret to #SB_RET_ERR_UNSUPPORTED_FUNCTION
 *   -# Else
 *     -# Do nothing
 *   -# <B>--- Endif #SB_CFG_SB_CERT_CHAIN_USE_IMG_PK is disabled ---</B>
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
#if (SB_CFG_CHECK_INTEGRITY == 1U)
static sb_ret_t sb_check_check_integrity_tlv(const st_sb_tlv_t* const p_key_cert_tlvs,
                                        const st_sb_tlv_t* const p_code_cert_tlvs)
{
    /*-----------------------------------------------------------------------------------------------------------------
     Local variables
    -----------------------------------------------------------------------------------------------------------------*/
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    /*-----------------------------------------------------------------------------------------------------------------
     Function body
    -----------------------------------------------------------------------------------------------------------------*/
    if ((NULL != p_key_cert_tlvs) && (NULL != p_code_cert_tlvs))
    {
        /* Check request TLV in key cert */
        if ((NULL != p_key_cert_tlvs[SB_PRV_TLV_KEY_CERT_HASH_IMG_PK_IDX].p_val) &&
            (NULL != p_key_cert_tlvs[SB_PRV_TLV_KEY_CERT_SIGN_CERT_IDX].p_val))
        {
            /*  Check select TLV in key cert */
            if (((NULL != p_key_cert_tlvs[SB_PRV_TLV_KEY_CERT_KEY_OEM_ROOT_PK_IDX].p_val) &&
                (NULL == p_key_cert_tlvs[SB_PRV_TLV_KEY_CERT_KEY_IMG_PK_IDX].p_val))  ||
                ((NULL == p_key_cert_tlvs[SB_PRV_TLV_KEY_CERT_KEY_OEM_ROOT_PK_IDX].p_val) &&
                (NULL != p_key_cert_tlvs[SB_PRV_TLV_KEY_CERT_KEY_IMG_PK_IDX].p_val)) )
            {
                /*  Check requeste TLV in code cert */
                if (NULL != p_code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_KEY_IMG_PK_IDX].p_val)
                {
                    /*  Check select TLV in code cert */
                    if (((NULL != p_code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_SIGN_CERT_IDX].p_val) &&
                        (NULL == p_code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_SIGN_IMG_IDX].p_val))  ||
                        ((NULL == p_code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_SIGN_CERT_IDX].p_val) &&
                        (NULL != p_code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_SIGN_IMG_IDX].p_val)) )
                    {
                        if (NULL != p_code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_SIGN_CERT_IDX].p_val)
                        {
                            if (NULL != p_code_cert_tlvs[SB_PRV_TLV_CI_CODE_CERT_HASH_IMG_IDX].p_val)
                            {
                                /* TLV field OK. Set ret to the success code */
                                ret = SB_RET_SUCCESS;
                            }
                            else
                            {
                                ret = SB_RET_ERR_MANI_TLV_FIELD_ERR;
                            }
                        }
                        else
                        {
                            /* TLV field OK. Set ret to the success code */
                            ret = SB_RET_SUCCESS;
                        }
                    }
                    else
                    {
                        ret = SB_RET_ERR_MANI_TLV_FIELD_ERR;
                    }
                }
                else
                {
                    ret = SB_RET_ERR_MANI_TLV_FIELD_ERR;
                }
            }
            else
            {
                ret = SB_RET_ERR_MANI_TLV_FIELD_ERR;
            }
        }
        else
        {
            ret = SB_RET_ERR_MANI_TLV_FIELD_ERR;
        }
#if (SB_CFG_SB_CERT_CHAIN_USE_IMG_PK == 0U)
        if((SB_RET_SUCCESS == ret) &&
            (NULL != p_key_cert_tlvs[SB_PRV_TLV_KEY_CERT_KEY_IMG_PK_IDX].p_val))
        {
            ret = SB_RET_ERR_UNSUPPORTED_FUNCTION;
        }
        else
        {
            /* Do nothing */
        }
#endif /* (SB_CFG_SB_CERT_CHAIN_USE_IMG_PK == 0U) */
    }
    else
    {
        /* Since this function is only called from within the library, this route is not usually taken */
    }

    return ret;
}
#endif /* (SB_CFG_CHECK_INTEGRITY == 1U) */
/**********************************************************************************************************************
* End of function sb_check_check_integrity_tlv()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : sb_get_cc_tlv
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBSecureBootAPIsInternal
 * \brief       Search key certificate and code certificate TLVs and confirm the obtained TLVs
 * \param       [in]   p_key_cert_st               Start address of Key Certificate Structure
 * \param       [in]   p_code_cert_st              Start address of Code Certificate Structure
 * \param       [in]   p_search_tlv_key_cert       Start address of Key certificate TLVs search information
 * \param       [in]   search_tlv_key_cert_num     Number of Key certificates TLV to search
 * \param       [in]   p_search_tlv_code_cert      Start address of Code certificate TLVs search information
 * \param       [in]   search_tlv_code_cert_num    Number of Code certificates TLV to search
 * \param       [out]  p_key_cert_tlvs             Output address of Key certificate TLVs
 * \param       [out]  p_code_cert_tlvs            Output address of Code certificate TLVs
 * \return
 *  - #SB_RET_SUCCESS:                          Successful completion
 *  - #SB_RET_ERR_INTERNAL_FAIL:                Internal processing failed
 *  - #SB_RET_ERR_MANI_TLV_FIELD_ERR:           Missing required TLV fields
 *  - #SB_RET_ERR_MANI_TLV_INVALID_LEN:         The length of the TLV field has a size that exceeds the end of
 *                                              the manifest.
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Parse the Key certificate TLV based on the search conditions passed in the arguments
 *      - Parse the Code certificate TLV based on the search conditions passed in the arguments
 *      - Check if the parsed TLV information is correct
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# If (NULL != p_key_cert_st) && (NULL != p_code_cert_st) && (NULL != p_search_tlv_key_cert) &&
 *       (NULL != p_search_tlv_code_cert) && (NULL != p_key_cert_tlvs) && (NULL != p_code_cert_tlvs)
 *   -# Parse the key certificate TLV with #r_sb_mani_parse_tlvs
 *   -# Set function result to ret
 *   -# If #SB_RET_SUCCESS == ret
 *     -# To clear ret, set #SB_RET_ERR_INTERNAL_FAIL to ret.
 *     -# Parse the code certificate TLV with #r_sb_mani_parse_tlvs
 *     -# Set function result to ret
 *   -# Else
 *     -# Do nothing
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
#if (SB_CFG_SB_CERT_CHAIN_VERIFICATION == 1U) || (SB_CFG_CHECK_INTEGRITY == 1U)
static sb_ret_t sb_get_cc_tlv(const st_sb_key_cert_t* const p_key_cert_st,
                                const st_sb_code_cert_t* const p_code_cert_st,
                                const st_sb_search_tlv_type_t* const p_search_tlv_key_cert,
                                const uint32_t search_tlv_key_cert_num,
                                const st_sb_search_tlv_type_t* const p_search_tlv_code_cert,
                                const uint32_t search_tlv_code_cert_num,
                                st_sb_tlv_t* const p_key_cert_tlvs,
                                st_sb_tlv_t* const p_code_cert_tlvs)
{
    /*-----------------------------------------------------------------------------------------------------------------
     Local variables
    -----------------------------------------------------------------------------------------------------------------*/
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    /*-----------------------------------------------------------------------------------------------------------------
     Function body
    -----------------------------------------------------------------------------------------------------------------*/
    /* Check NULL argument */
    if ((NULL != p_key_cert_st) && (NULL != p_code_cert_st) && (NULL != p_search_tlv_key_cert) &&
        (NULL != p_search_tlv_code_cert) && (NULL != p_key_cert_tlvs) && (NULL != p_code_cert_tlvs))
    {
        /* Get Key cert TLVs */
        ret = r_sb_mani_parse_tlvs(p_key_cert_st->p_tlv_top, p_key_cert_st->tlv_len, search_tlv_key_cert_num,
                                p_search_tlv_key_cert, p_key_cert_tlvs);
        if (SB_RET_SUCCESS == ret)
        {
            /* Clear ret */
            ret = SB_RET_ERR_INTERNAL_FAIL;
            (void) ret;

            ret = r_sb_mani_parse_tlvs(p_code_cert_st->p_tlv_top, p_code_cert_st->tlv_len, search_tlv_code_cert_num,
                                    p_search_tlv_code_cert, p_code_cert_tlvs);
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /* Since this function is only called from within the library, this route is not usually taken */
    }

    return ret;
}
#endif /* (SB_CFG_SB_CERT_CHAIN_VERIFICATION == 1U) || (SB_CFG_CHECK_INTEGRITY == 1U) */
/**********************************************************************************************************************
* End of function sb_get_cc_tlv()
**********************************************************************************************************************/

/*=====================================================================================================================
 End of file
=====================================================================================================================*/
