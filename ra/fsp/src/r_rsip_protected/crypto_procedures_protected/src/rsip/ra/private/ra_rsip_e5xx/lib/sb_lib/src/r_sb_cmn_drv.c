/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*!********************************************************************************************************************
* \file             : r_sb_cmn_drv.c
* \par version      : 1.00
* \par Product Name : Renesas-SB-Lib FSBL Custom
* \par Device(s)    : Does not depend on specific hardware
* \par Description  : This file implements common APIs for the CIP(CryptoIP) driver.
**********************************************************************************************************************/

/*!***********************************************************
 * \addtogroup  SBLIBCommon
 * \{
 * \addtogroup  SBLIBCommonDefines           Common Definitions
 * \addtogroup  SBLIBCommonTypes             Common Types
 * \addtogroup  SBLIBCommonAPIs              Common APIs
 * \addtogroup  SBLIBCommonDefinesInternal   Common Internal Definitions
 * \addtogroup  SBLIBCommonTypesInternal     Common Internal Types
 * \addtogroup  SBLIBCommonVariablesInternal Common Internal Variables
 * \addtogroup  SBLIBCommonAPIsInternal      Common Internal APIs
 * \}********************************************************/

/*=====================================================================================================================
 Includes <System Includes> , "Project Includes"
=====================================================================================================================*/
#include <stddef.h>
#include "r_cip_drv_api.h"
#include "r_sb_build_config.h"
#include "r_sb_api.h"
#include "r_sb_cmn.h"
#include "r_sb_manifest.h"
#include "r_sb_cmn_drv.h"

/*=====================================================================================================================
 Private macro definitions
=====================================================================================================================*/
/*!********************************************************************
 * \addtogroup SBLIBCommonDefinesInternal
 * \{******************************************************************/
#define SB_PRV_RET_UPPER_MASK                   (0xFFFF0000UL)   /**< Mask the upper 16 bits of the return value */
#define SB_PRV_RET_LOWER_MASK                   (0x0000FFFFUL)   /**< Mask the lower 16 bits of the return value */
#define SB_PRV_RET_ERROR_BITS                   (0xAAAA0000UL)   /**< Bits of error return value */

#define SB_PRV_RET_UNSUPPORTED_ALGO             (0xFFFFFFFFUL)   /**< Unsupported algorithm specified */
/*! \}*/

/*=====================================================================================================================
 Private type definitions
=====================================================================================================================*/
/*!********************************************************************
 * \addtogroup SBLIBCommonTypesInternal
 * \{******************************************************************/
/*! \}*/

/*=====================================================================================================================
 Public global variables
=====================================================================================================================*/
/*!********************************************************************
 * \addtogroup SBLIBCommonVariablesInternal
 * \{******************************************************************/

/*! \}*/

/*=====================================================================================================================
 Private global variables
=====================================================================================================================*/
/*!********************************************************************
 * \addtogroup SBLIBCommonVariablesInternal
 * \{******************************************************************/

/*! \}*/

/*=====================================================================================================================
 Private function prototypes
=====================================================================================================================*/
static uint32_t cmn_drv_get_hash_algo (const uint32_t type);
static uint32_t cmn_drv_get_sign_hash_algo (const uint32_t type);
static uint32_t cmn_drv_get_sign_algo (const uint32_t type);
static uint32_t cmn_drv_get_sign_scheme (const uint32_t type, const uint32_t sign_algo);
static uint32_t cmn_drv_get_img_cip_info_algo (const uint32_t type);
static uint32_t cmn_drv_get_img_cip_info_mode (const uint32_t type);

/*=====================================================================================================================
 Public function definitions
=====================================================================================================================*/
/**********************************************************************************************************************
* Function Name : r_sb_cmn_drv_set_cc_key_cert_param
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Setting key certificate parameter with in Certificate Chain verification
 * \param       [in]   p_key_cert_st           Start address of Key Certificate Structure
 * \param       [in]   p_img_pk_hash_tlv       Start address of Image public key hash TLV
 * \param       [in]   p_sign_pk_tlv           Start address of Signature public key TLV
 * \param       [in]   p_sign_tlv              Start address of Signature TLV
 * \param       [out]  p_cc_key_cert_param     Starting address of the structure for setting the
 *                                             key certificate parameters used in the certificate chain
 * \return
 *  - #SB_RET_SUCCESS:                             Successful completion
 *  - #SB_RET_ERR_INTERNAL_FAIL:                   Internal processing failed
 *  - #SB_RET_ERR_MANI_MISMATCH_SIGN_ALGORITHM:    There is a wrong combination of signature algorithms
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Convert Manifest information to SB-Driver definition and set it in parameter structure given as argument
 *      - This parameter is used in the following SB-Driver API
 *        - R_CIP_DRV_PrcVerifyCertChain
 *        - R_CIP_DRV_PrcCheckIntegrity
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# If (NULL != p_key_cert_st) && (NULL != p_img_pk_hash_tlv) && (NULL != p_sign_pk_tlv) &&
 *       (NULL != p_sign_tlv) && (NULL != p_cc_key_cert_param)
 *   -# Get Signature public key algorithm with #cmn_drv_get_sign_algo and set to key_algo
 *   -# If (p_sign_pk_tlv->type & #SB_PRV_TLV_TYPE_CLS_SIGN_UT_MASK) == #SB_PRV_TLV_TYPE_CLS_KEY_UT_OEM_ROOT_PK
 *     -# Set p_cc_key_cert_param->key_cert_pk_cmp_src to CIP_DRV_KEY_CERT_PK_CMP_SRC_ROT
 *   -# Else
 *     -# Set p_cc_key_cert_param->key_cert_pk_cmp_src to CIP_DRV_KEY_CERT_PK_CMP_SRC_IMG_PK
 *   -# Get hash algorithm with #cmn_drv_get_hash_algo
 *   -# Set p_cc_key_cert_param->img_pk_hash_algo to function result
 *   -# Cast the p_img_pk_hash_tlv->p_val to uint32_t* type and set it to p_cc_key_cert_param->p_img_pk_hash
 *   -# Set p_cc_key_cert_param->img_pk_hash_len to p_img_pk_hash_tlv->byte_len
 *   -# Get sign algorithm with #cmn_drv_get_sign_algo
 *   -# Set p_cc_key_cert_param->sign_algo to function result
 *   -# Get sign hash algorithm with #cmn_drv_get_sign_hash_algo
 *   -# Set p_cc_key_cert_param->sign_hash_algo to function result
 *   -# Get sign scheme with #cmn_drv_get_sign_scheme
 *   -# Set p_cc_key_cert_param->sign_scheme to function result
 *   -# Cast the p_sign_pk_tlv->p_val to uint32_t* type and set it to p_cc_key_cert_param->p_sign_pk
 *   -# Set p_cc_key_cert_param->sign_pk_len to p_sign_pk_tlv->byte_len
 *   -# Cast the p_sign_tlv->p_val to uint32_t* type and set it to p_cc_key_cert_param->p_sign
 *   -# Set p_cc_key_cert_param->sign_len to p_sign_tlv->byte_len
 *   -# Cast the p_key_cert_st->p_header to uint32_t* type and set it to p_cc_key_cert_param->p_key_cert
 *   -# Calculate the signing target size of the key certificate and set it to p_cc_key_cert_param->key_cert_sign_len
 *   -# If (SB_PRV_RET_UNSUPPORTED_ALGO == key_algo) ||
 *         (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_key_cert_param->img_pk_hash_algo) ||
 *         (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_key_cert_param->sign_algo) ||
 *         (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_key_cert_param->sign_hash_algo) ||
 *         (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_key_cert_param->sign_scheme)
 *     -# Set ret to #SB_RET_ERR_MANI_MISMATCH_SIGN_ALGORITHM
 *   -# Else
 *     -# If p_cc_key_cert_param->sign_algo != key_algo
 *       -# Set ret to #SB_RET_ERR_MANI_MISMATCH_SIGN_ALGORITHM
 *     -# Else
 *       -# Set ret to #SB_RET_SUCCESS
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
sb_ret_t r_sb_cmn_drv_set_cc_key_cert_param(const st_sb_key_cert_t* const p_key_cert_st,
                                            const st_sb_tlv_t* const p_img_pk_hash_tlv,
                                            const st_sb_tlv_t* const p_sign_pk_tlv,
                                            const st_sb_tlv_t* const p_sign_tlv,
                                            st_cip_drv_cc_key_cert_param_t* const p_cc_key_cert_param)
{
    /*-----------------------------------------------------------------------------------------------------------------
     Local variables
    -----------------------------------------------------------------------------------------------------------------*/
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    uint32_t key_algo;

    /*-----------------------------------------------------------------------------------------------------------------
     Function body
    -----------------------------------------------------------------------------------------------------------------*/
    if ((NULL != p_key_cert_st) && (NULL != p_img_pk_hash_tlv) && (NULL != p_sign_pk_tlv) &&
        (NULL != p_sign_tlv) && (NULL != p_cc_key_cert_param))
    {
        key_algo = cmn_drv_get_sign_algo(p_sign_pk_tlv->type);
        if ((p_sign_pk_tlv->type & SB_PRV_TLV_TYPE_CLS_SIGN_UT_MASK) == SB_PRV_TLV_TYPE_CLS_KEY_UT_OEM_ROOT_PK)
        {
            p_cc_key_cert_param->key_cert_pk_cmp_src = CIP_DRV_KEY_CERT_PK_CMP_SRC_ROT;
        }
        else
        {
            p_cc_key_cert_param->key_cert_pk_cmp_src = CIP_DRV_KEY_CERT_PK_CMP_SRC_IMG_PK;
        }

        p_cc_key_cert_param->img_pk_hash_algo = cmn_drv_get_hash_algo(p_img_pk_hash_tlv->type);
        p_cc_key_cert_param->p_img_pk_hash = p_img_pk_hash_tlv->p_val;
        p_cc_key_cert_param->img_pk_hash_len = p_img_pk_hash_tlv->byte_len;
        p_cc_key_cert_param->sign_algo = cmn_drv_get_sign_algo(p_sign_tlv->type);
        p_cc_key_cert_param->sign_hash_algo = cmn_drv_get_sign_hash_algo(p_sign_tlv->type);
        p_cc_key_cert_param->sign_scheme = cmn_drv_get_sign_scheme(p_sign_tlv->type, p_cc_key_cert_param->sign_algo);
        p_cc_key_cert_param->p_sign_pk = p_sign_pk_tlv->p_val;
        p_cc_key_cert_param->sign_pk_len = p_sign_pk_tlv->byte_len;
        p_cc_key_cert_param->p_sign = p_sign_tlv->p_val;
        p_cc_key_cert_param->sign_len = p_sign_tlv->byte_len;
        p_cc_key_cert_param->p_key_cert = (const uint32_t*)p_key_cert_st->p_header; /* Casting from pointer to
                                                                                    pointer is no problem */
        /* Key Cert signature length = Key Cert length - Key Cert signature TLV length */
        p_cc_key_cert_param->key_cert_sign_len = (SB_PRV_MANI_HEADER_SIZE + SB_PRV_MANI_TLV_LEN_SIZE +
                                            p_key_cert_st->tlv_len) - (SB_PRV_TLV_TL_SIZE + p_sign_tlv->byte_len);

        /* Check algorithm */
        if ((SB_PRV_RET_UNSUPPORTED_ALGO == key_algo) ||
            (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_key_cert_param->img_pk_hash_algo) ||
            (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_key_cert_param->sign_algo) ||
            (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_key_cert_param->sign_hash_algo) ||
            (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_key_cert_param->sign_scheme))
        {
            /* Unsupported algorithm */
            ret = SB_RET_ERR_MANI_UNSUPPORTED_ALGORITHM;
        }
        else
        {
            if (p_cc_key_cert_param->sign_algo != key_algo)
            {
                /* There is a wrong combination of signature algorithms */
                ret = SB_RET_ERR_MANI_MISMATCH_SIGN_ALGORITHM;
            }
            else
            {
                /* Set ret to the success code */
                ret = SB_RET_SUCCESS;
            }
        }
    }
    else
    {
        /* If there are null arguments, return SB_RET_ERR_INTERNAL_FAIL */
    }

    return ret;
}
/**********************************************************************************************************************
* End of function r_sb_cmn_drv_set_cc_key_cert_param()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : r_sb_cmn_drv_set_cc_code_cert_param
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Setting code certificate parameter with in Certificate Chain verification
 * \param       [in]   p_code_cert_st         Start address of Code Certificate Structure
 * \param       [in]   img_addr               Address of the target image
 * \param       [in]   p_sign_pk_tlv          Start address of Signature public key TLV
 * \param       [in]   p_sign_tlv             Start address of Signature TLV
 * \param       [in]   p_img_hash_tlv         Start address of image hash TLV
 * \param       [out]  p_cc_code_cert_param   Starting address of the structure for setting the
 *                                            code certificate parameters used in the certificate chain
 * \return
 *  - #SB_RET_SUCCESS:                             Successful completion
 *  - #SB_RET_ERR_INTERNAL_FAIL:                   Internal processing failed
 *  - #SB_RET_ERR_MANI_MISMATCH_SIGN_ALGORITHM:    There is a wrong combination of signature algorithms
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Convert Manifest information to SB-Driver definition and set it in parameter structure given as argument
 *      - This parameter is used in the following SB-Driver API
 *        - R_CIP_DRV_PrcVerifyCertChain
 *        - R_CIP_DRV_PrcCheckIntegrity
 *      - If build configuration #SB_CFG_SB_CERT_CHAIN_USE_IMG_PK is enabled,
 *        save the hash of the IMG PK of the code certificate

 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# If (NULL != p_code_cert_st) && (NULL != p_code_cert_st->p_header) && (NULL != p_sign_pk_tlv) &&
 *       (NULL != p_sign_tlv) && (NULL != p_cc_code_cert_param)
 *   -# Get Signature public key algorithm with #cmn_drv_get_sign_algo and set to key_algo
 *   -# Get sign algorithm with #cmn_drv_get_sign_algo
 *   -# Set function result to p_cc_code_cert_param->sign_algo
 *   -# Get sign hash algorithm with #cmn_drv_get_sign_hash_algo
 *   -# Set function result to p_cc_code_cert_param->sign_hash_algo
 *   -# Get sign scheme with #cmn_drv_get_sign_scheme
 *   -# Set function result to p_cc_code_cert_param->sign_scheme
 *   -# Cast the p_sign_pk_tlv->p_val to uint32_t* type and set it to p_cc_code_cert_param->p_sign_pk
 *   -# Set p_sign_pk_tlv->byte_len to p_cc_code_cert_param->sign_pk_len
 *   -# Cast the p_sign_tlv->p_val to uint32_t* type and set it to p_cc_code_cert_param->p_sign
 *   -# Set p_sign_tlv->byte_len to p_cc_code_cert_param->sign_len
 *   -# Cast the p_code_cert_st->p_header to uint32_t* type and set it to p_cc_code_cert_param->p_code_cert
 *   -# Calculate the size of the code certificate and set it to p_cc_code_cert_param->code_cert_len
 *   -# Calculate the signing target size of the code certificate and
 *      set it to p_cc_code_cert_param->code_cert_sign_len
 *   -# Set p_code_cert_st->p_header->dest_addr to img_addr
 *   -# Set img_addr to p_cc_code_cert_param->p_img
 *   -# Set p_code_cert_st->p_header->img_len to p_cc_code_cert_param->img_len
 *   -# If (NULL != p_img_hash_tlv)
 *     -# Set cmn_drv_get_hash_algo(p_img_hash_tlv->type) to p_cc_code_cert_param->img_hash_algo
 *     -# Set p_img_hash_tlv->p_val to p_cc_code_cert_param->p_img_hash
 *     -# Set p_img_hash_tlv->byte_len to p_cc_code_cert_param->img_hash_len
 *   -# Else
 *     -# Set CIP_DRV_HASH_ALGO_NONE to p_cc_code_cert_param->img_hash_algo
 *     -# Set NULL to p_cc_code_cert_param->p_img_hash
 *     -# Set 0UL to p_cc_code_cert_param->img_hash_len
 *   -# <B>--- If #SB_CFG_SB_CERT_CHAIN_USE_IMG_PK is enabled ---</B>
 *   -# If (p_code_cert_st->p_header->flags & #SB_PRV_CODE_CERT_HEADER_FLAGS_SAVE_IMG_PK) != 0UL
 *     -# Set 1 to p_cc_code_cert_param->is_save_img_pk
 *   -# Else
 *     -# set 0 to p_cc_code_cert_param->is_save_img_pk
 *   -# <B>--- Else #SB_CFG_SB_CERT_CHAIN_USE_IMG_PK is enabled ---</B>
 *   -# Set 0 to p_cc_code_cert_param->is_save_img_pk
 *   -# <B>--- Endif #SB_CFG_SB_CERT_CHAIN_USE_IMG_PK is enabled ---</B>
 *   -# If (SB_PRV_RET_UNSUPPORTED_ALGO == key_algo) ||
 *         (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_code_cert_param->sign_algo) ||
 *         (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_code_cert_param->sign_hash_algo) ||
 *         (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_code_cert_param->sign_scheme) ||
 *         (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_code_cert_param->img_hash_algo)
 *     -# Set #SB_RET_ERR_MANI_MISMATCH_SIGN_ALGORITHM to ret
 *   -# Else
 *     -# If p_cc_code_cert_param->sign_algo != key_algo
 *       -# Set #SB_RET_ERR_MANI_MISMATCH_SIGN_ALGORITHM to ret
 *     -# Else
 *       -# Set ret to #SB_RET_SUCCESS
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
sb_ret_t r_sb_cmn_drv_set_cc_code_cert_param(const st_sb_code_cert_t* const p_code_cert_st,
                                                const uint32_t img_addr,
                                                const st_sb_tlv_t* const p_sign_pk_tlv,
                                                const st_sb_tlv_t* const p_sign_tlv,
                                                const st_sb_tlv_t* const p_img_hash_tlv,
                                                st_cip_drv_cc_code_cert_param_t* const p_cc_code_cert_param)
{
    /*-----------------------------------------------------------------------------------------------------------------
     Local variables
    -----------------------------------------------------------------------------------------------------------------*/
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    volatile uintptr_t tmp_img_addr;
    uint32_t           key_algo;

    /*-----------------------------------------------------------------------------------------------------------------
     Function body
    -----------------------------------------------------------------------------------------------------------------*/
    if ((NULL != p_code_cert_st) && (NULL != p_code_cert_st->p_header) && (NULL != p_sign_pk_tlv) &&
        (NULL != p_sign_tlv) && (NULL != p_cc_code_cert_param))
    {
        key_algo = cmn_drv_get_sign_algo(p_sign_pk_tlv->type);
        p_cc_code_cert_param->sign_algo = cmn_drv_get_sign_algo(p_sign_tlv->type);
        p_cc_code_cert_param->sign_hash_algo = cmn_drv_get_sign_hash_algo(p_sign_tlv->type);
        p_cc_code_cert_param->sign_scheme = cmn_drv_get_sign_scheme(p_sign_tlv->type,
                                                                    p_cc_code_cert_param->sign_algo);
        p_cc_code_cert_param->p_sign_pk = p_sign_pk_tlv->p_val;
        p_cc_code_cert_param->sign_pk_len = p_sign_pk_tlv->byte_len;
        p_cc_code_cert_param->p_sign = p_sign_tlv->p_val;
        p_cc_code_cert_param->sign_len = p_sign_tlv->byte_len;
        p_cc_code_cert_param->p_code_cert = (const uint32_t*)p_code_cert_st->p_header; /* Casting from pointer
                                                                                        to pointer is no problem */
        p_cc_code_cert_param->code_cert_len = SB_PRV_MANI_HEADER_SIZE + SB_PRV_MANI_TLV_LEN_SIZE +
                                                p_code_cert_st->tlv_len;
        p_cc_code_cert_param->code_cert_sign_len = p_cc_code_cert_param->code_cert_len
                                                    - (SB_PRV_TLV_TL_SIZE + p_sign_tlv->byte_len);
        /* Assign the address set in dest_addr once to a uintptr_t type variable
            (32/64bit MPU countermeasures) */
        tmp_img_addr = img_addr;
        p_cc_code_cert_param->p_img = (const uint32_t*)tmp_img_addr; /* Casts that do not exceed
                                                                        the size of the type are fine */
        p_cc_code_cert_param->img_len = p_code_cert_st->p_header->img_len;
        if (NULL != p_img_hash_tlv)
        {
            p_cc_code_cert_param->img_hash_algo = cmn_drv_get_hash_algo(p_img_hash_tlv->type);
            p_cc_code_cert_param->p_img_hash = p_img_hash_tlv->p_val;
            p_cc_code_cert_param->img_hash_len = p_img_hash_tlv->byte_len;
        }
        else
        {
            p_cc_code_cert_param->img_hash_algo = CIP_DRV_HASH_ALGO_NONE;
            p_cc_code_cert_param->p_img_hash = NULL;
            p_cc_code_cert_param->img_hash_len = 0UL;
        }
#if (SB_CFG_SB_CERT_CHAIN_USE_IMG_PK == 1U) /* (Use only when SB_CFG_SB_CERT_CHAIN_USE_IMG_PK is Enable) */
        if ((p_code_cert_st->p_header->flags & SB_PRV_CODE_CERT_HEADER_FLAGS_SAVE_IMG_PK) != 0UL)
        {
            p_cc_code_cert_param->is_save_img_pk = 1UL;
        }
        else
        {
            p_cc_code_cert_param->is_save_img_pk = 0UL;
        }
#else  /* !(SB_CFG_SB_CERT_CHAIN_USE_IMG_PK == 1U) */
        p_cc_code_cert_param->is_save_img_pk = 0UL;
#endif /* !(SB_CFG_SB_CERT_CHAIN_USE_IMG_PK == 1U) */

        /* Check algorithm */
        if ((SB_PRV_RET_UNSUPPORTED_ALGO == key_algo) ||
            (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_code_cert_param->sign_algo) ||
            (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_code_cert_param->sign_hash_algo) ||
            (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_code_cert_param->sign_scheme) ||
            (SB_PRV_RET_UNSUPPORTED_ALGO == p_cc_code_cert_param->img_hash_algo))
        {
            /* Unsupported algorithm */
            ret = SB_RET_ERR_MANI_UNSUPPORTED_ALGORITHM;
        }
        else
        {
            if (p_cc_code_cert_param->sign_algo != key_algo)
            {
                /* There is a wrong combination of signature algorithms */
                ret = SB_RET_ERR_MANI_MISMATCH_SIGN_ALGORITHM;
            }
            else
            {
                /* Set ret to the success code */
                ret = SB_RET_SUCCESS;
            }
        }
    }
    else
    {
        /* If there are null arguments, return SB_RET_ERR_INTERNAL_FAIL */
    }

    return ret;
}
/**********************************************************************************************************************
* End of function r_sb_cmn_drv_set_cc_code_cert_param()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : r_sb_cmn_drv_set_cipher_img_param
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Setting Image Cipher Information parameters
 * \param       [in]   p_code_cert_st         Start address of Code Certificate Structure
 * \param       [in]   p_img_cip_info         Start address of Signature public key TLV
 * \param       [in]   p_img_cip_iv           Start address of Signature TLV
 * \param       [in]   is_overwrite_image     Whether to overwrite Image
 *                                            - #SB_PRV_TRUE:  Overwrite
 *                                            - #SB_PRV_FALSE: Do not overwrite
 * \param       [in]   timing                 Cipher timing viewed from signature verification
 * \param       [out]  p_cipher_img_param     Starting address of the structure for setting image cipher parameters
 * \return
 *  - #SB_RET_SUCCESS:                             Successful completion
 *  - #SB_RET_ERR_INTERNAL_FAIL:                   Internal processing failed
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Convert Manifest information to SB-Driver definition and set it in parameter structure given as argument
 *      - This parameter is used in the following SB-Driver API
 *        - R_CIP_DRV_PrcDecryptImage
 *        - R_CIP_DRV_PrcCheckIntegrity
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# If (NULL != p_code_cert_st) && (NULL != p_code_cert_st->p_header) && (NULL != p_img_cip_info) &&
 *       (NULL != p_cipher_img_param) && (NULL != p_img_cip_iv)
 *   -# Set p_cipher_img_param->timing to timing
 *   -# Set img_addr to p_code_cert_st->p_header->dest_addr
 *   -# Set p_cipher_img_param->p_img_src to img_addr
 *   -# Set p_cipher_img_param->img_len to p_code_cert_st->p_header->img_len
 *   -# Cast the p_img_cip_iv->p_val to uint32_t* type and set it to p_cipher_img_param->p_iv
 *   -# Set p_cipher_img_param->iv_len to p_img_cip_iv->byte_len
 *   -# If (NULL == p_img_cip_info->p_val)
 *     -# Set p_cipher_img_param->p_img_dst to img_addr
 *     -# Set p_cipher_img_param->cipher_algo to CIP_DRV_CIPHER_ALGO_NONE
 *     -# Set p_cipher_img_param->cipher_mode to CIP_DRV_CIPHER_MODE_NONE
 *     -# Set p_cipher_img_param->key_select to CIP_DRV_CIPHER_INFO_KEY_SEL_DEFAULT
 *     -# Set p_cipher_img_param->iv_select to CIP_DRV_CIPHER_INFO_IV_SEL_DEFAULT
 *   -# Else
 *     -# Cast the p_img_cip_info->p_val to const #st_sb_img_cip_info_val_t* type and set it to p_img_cip_info_val
 *     -# Get Cipher algorithm with #cmn_drv_get_img_cip_info_algo
 *     -# Set p_cipher_img_param->cipher_algo to function result
 *     -# Get Cipher mode with #cmn_drv_get_img_cip_info_mode
 *     -# Set p_cipher_img_param->cipher_mode to function result
 *     -# Set p_cipher_img_param->key_select to p_img_cip_info_val->key_sel
 *     -# Set p_cipher_img_param->iv_select to p_img_cip_info_val->iv_sel
 *     -# If #SB_PRV_TRUE == is_overwrite_image
 *       -# Set p_cipher_img_param->p_img_dst to p_cipher_img_param->p_img_src
 *     -# Else
 *       -# Set img_addr to p_img_cip_info_val->dest_addr
 *       -# Set p_cipher_img_param->p_img_dst to img_addr
 *   -# If (#SB_PRV_RET_UNSUPPORTED_ALGO == p_cipher_img_param->cipher_algo) ||
 *         (#SB_PRV_RET_UNSUPPORTED_ALGO == p_cipher_img_param->cipher_mode))
 *     -# Set ret to #SB_RET_ERR_MANI_UNSUPPORTED_ALGORITHM
 *   -# Else
 *     -# Set ret to #SB_RET_SUCCESS
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
sb_ret_t r_sb_cmn_drv_set_cipher_img_param(const st_sb_code_cert_t* const p_code_cert_st,
                                            const st_sb_tlv_t* const p_img_cip_info,
                                            const st_sb_tlv_t* const p_img_cip_iv,
                                            const sb_bool_t          is_overwrite_image,
                                            const uint32_t           timing,
                                            st_cip_drv_cipher_img_param_t* const p_cipher_img_param)
{
    /*-----------------------------------------------------------------------------------------------------------------
     Local variables
    -----------------------------------------------------------------------------------------------------------------*/
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    const    st_sb_img_cip_info_val_t * p_img_cip_info_val;
    volatile uintptr_t                  img_addr;

    /*-----------------------------------------------------------------------------------------------------------------
     Function body
    -----------------------------------------------------------------------------------------------------------------*/
    if ((NULL != p_code_cert_st) && (NULL != p_code_cert_st->p_header) && (NULL != p_img_cip_info) &&
        (NULL != p_cipher_img_param) && (NULL != p_img_cip_iv))
    {
        /* Set common parameters */
        p_cipher_img_param->timing = timing;
        /* Assign the address set in dest_addr once to a uintptr_t type variable
            (32/64bit MPU countermeasures) */
        img_addr = p_code_cert_st->p_header->dest_addr;
        /* Casts that do not exceed the size of the type are fine */
        p_cipher_img_param->p_img_src = (const uint32_t*)img_addr;
        p_cipher_img_param->img_len   = p_code_cert_st->p_header->img_len;
        p_cipher_img_param->p_iv  = p_img_cip_iv->p_val;
        p_cipher_img_param->iv_len  = p_img_cip_iv->byte_len;

        if (NULL == p_img_cip_info->p_val)
        {
            /* Overwrite image */
            p_cipher_img_param->p_img_dst   = (uint32_t*)img_addr;

            /* Use Device default parameters */
            p_cipher_img_param->cipher_algo = CIP_DRV_CIPHER_ALGO_NONE;
            p_cipher_img_param->cipher_mode = CIP_DRV_CIPHER_MODE_NONE;
            p_cipher_img_param->key_select  = CIP_DRV_CIPHER_INFO_KEY_SEL_DEFAULT;
            p_cipher_img_param->iv_select   = CIP_DRV_CIPHER_INFO_IV_SEL_DEFAULT;
        }
        else
        {
            /* Use TLV parameters */
            p_img_cip_info_val = (const st_sb_img_cip_info_val_t*)(p_img_cip_info->p_val); /* Casting from pointer
                                                                                            to pointer is no problem */
            p_cipher_img_param->cipher_algo = cmn_drv_get_img_cip_info_algo(p_img_cip_info->type);
            p_cipher_img_param->cipher_mode = cmn_drv_get_img_cip_info_mode(p_img_cip_info->type);
            p_cipher_img_param->key_select  = p_img_cip_info_val->key_sel;
            p_cipher_img_param->iv_select   = p_img_cip_info_val->iv_sel;
            if (SB_PRV_TRUE == is_overwrite_image)
            {
                /* Casts that do not exceed the size of the type are fine */
                p_cipher_img_param->p_img_dst   = (uint32_t*)img_addr;
            }
            else
            {
                /* Assign the address set in dest_addr once to a uintptr_t type variable
                    (32/64bit MPU countermeasures) */
                img_addr = p_img_cip_info_val->dest_addr;
                /* Casts that do not exceed the size of the type are fine */
                p_cipher_img_param->p_img_dst   = (uint32_t*)img_addr;
            }
        }
        /* Check algorithm */
        if ((SB_PRV_RET_UNSUPPORTED_ALGO == p_cipher_img_param->cipher_algo) ||
            (SB_PRV_RET_UNSUPPORTED_ALGO == p_cipher_img_param->cipher_mode))
        {
            /* Unsupported algorithm */
            ret = SB_RET_ERR_MANI_UNSUPPORTED_ALGORITHM;
        }
        else
        {
            /* Set ret to the success code */
            ret = SB_RET_SUCCESS;
        }
    }
    else
    {
        /* If there are null arguments, return SB_RET_ERR_INTERNAL_FAIL */
    }

    return ret;
}
/**********************************************************************************************************************
* End of function r_sb_cmn_drv_set_cipher_img_param()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : r_sb_cmn_drv_get_sb_ret_from_cip_ret
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Returns the return code corresponding to the return code of cipher driver
 * \param       [in]   cip_ret                Cipher Driver return code
 * \return
 *  - #SB_RET_SUCCESS:                             Successful completion
 *  - #SB_RET_SAME_IMAGE_VERSION:                  An image of the same version as the current version is
 *                                                 input(verification completed successfully)
 *  - #SB_RET_ERR_INTERNAL_FAIL:                   Internal processing failed
 *  - #SB_RET_ERR_CRYPTO_FAIL:                     Encryption failed
 *  - #SB_RET_ERR_CRYPTO_AUTH_FAIL:                Verification failed
 *  - #SB_RET_ERR_CRYPTO_UNSUPPORTED_ALGORITHM:    Unsupported algorithm
 *  - #SB_RET_ERR_CRYPTO_RESOURCE_CONFLICT:        CryptoIP resources are being used by other resources
 *  - #SB_RET_ERR_CRYPTO_PARAM_ERR:                Parameter error
 *  - #SB_RET_ERR_LOWER_IMAGE_VERSION:             Image version lower than the current image version is installed
 *  - #SB_RET_ERR_CRC_MISMATCH                     CRC mismatch
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Returns the return code corresponding to the return code of cipher driver
 *      - Implement the following as a glitch countermeasure :
 *        - Set success return value in two steps
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# Initialize the variable tmp_ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# switch cip_ret
 *   -# cip_ret == CIP_DRV_RET_PASS
 *     -# Set (#SB_RET_SUCCESS & #SB_PRV_RET_UPPER_MASK) to ret
 *   -# cip_ret == CIP_DRV_RET_SAME_IMAGE_VERSION
 *     -# Set (#SB_RET_SAME_IMAGE_VERSION & #SB_PRV_RET_UPPER_MASK) to ret
 *   -# cip_ret == CIP_DRV_RET_AUTH_FAIL,             Set ret to #SB_RET_ERR_CRYPTO_AUTH_FAIL
 *   -# cip_ret == CIP_DRV_RET_UNSUPPORTED_ALGORITHM, Set ret to #SB_RET_ERR_CRYPTO_UNSUPPORTED_ALGORITHM
 *   -# cip_ret == CIP_DRV_RET_RESOURCE_CONFLICT,     Set ret to #SB_RET_ERR_CRYPTO_RESOURCE_CONFLICT
 *   -# cip_ret == CIP_DRV_RET_LOWER_IMAGE_VERSION,   Set ret to #SB_RET_ERR_LOWER_IMAGE_VERSION
 *   -# cip_ret == CIP_DRV_RET_PARAM_ERROR,           Set ret to #SB_RET_ERR_CRYPTO_PARAM_ERR
 *   -# cip_ret == CIP_DRV_RET_CRC_MISMATCH,          Set ret to #SB_RET_ERR_CRC_MISMATCH
 *   -# default, Set ret to #SB_RET_ERR_CRYPTO_FAIL
 * -# switch cip_ret
 *   -# cip_ret == CIP_DRV_RET_PASS
 *     -# Set ret to (#SB_RET_SUCCESS & #SB_PRV_RET_LOWER_MASK)
 *   -# cip_ret == CIP_DRV_RET_SAME_IMAGE_VERSION
 *     -# Set ret to (#SB_RET_SAME_IMAGE_VERSION & #SB_PRV_RET_LOWER_MASK)
 *   -# default
 *     -# In case of error, do nothing because the return value has already been set
 * -# If (ret & #SB_PRV_RET_ERROR_BITS) != #SB_PRV_RET_ERROR_BITS
 *   -# If (#SB_RET_SUCCESS == ret) || (#SB_RET_SAME_IMAGE_VERSION == ret)
 *     -# Do nothing
 *   -# Else
 *     -# Set ret to #SB_RET_ERR_INTERNAL_FAIL
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
sb_ret_t r_sb_cmn_drv_get_sb_ret_from_cip_ret(const cip_drv_ret_t cip_ret)
{
    /*-----------------------------------------------------------------------------------------------------------------
     Local variables
    -----------------------------------------------------------------------------------------------------------------*/
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    volatile sb_ret_t tmp_ret = SB_RET_ERR_INTERNAL_FAIL;

    /*-----------------------------------------------------------------------------------------------------------------
     Function body
    -----------------------------------------------------------------------------------------------------------------*/
    switch (cip_ret)
    {
        case CIP_DRV_RET_PASS:
            tmp_ret = (SB_RET_SUCCESS & SB_PRV_RET_UPPER_MASK);
            break;
        case CIP_DRV_RET_SAME_IMAGE_VERSION:
            tmp_ret = (SB_RET_SAME_IMAGE_VERSION & SB_PRV_RET_UPPER_MASK);
            break;
        case CIP_DRV_RET_AUTH_FAIL:
            tmp_ret = SB_RET_ERR_CRYPTO_AUTH_FAIL;
            break;
        case CIP_DRV_RET_UNSUPPORTED_ALGORITHM:
            tmp_ret = SB_RET_ERR_CRYPTO_UNSUPPORTED_ALGORITHM;
            break;
        case CIP_DRV_RET_RESOURCE_CONFLICT:
            tmp_ret = SB_RET_ERR_CRYPTO_RESOURCE_CONFLICT;
            break;
        case CIP_DRV_RET_LOWER_IMAGE_VERSION:
            tmp_ret = SB_RET_ERR_LOWER_IMAGE_VERSION;
            break;
        case CIP_DRV_RET_PARAM_ERROR:
            tmp_ret = SB_RET_ERR_CRYPTO_PARAM_ERR;
            break;
        case CIP_DRV_RET_CRC_MISMATCH:
            tmp_ret = SB_RET_ERR_CRC_MISMATCH;
            break;
        default:
            tmp_ret = SB_RET_ERR_CRYPTO_FAIL;
            break;
    }

    switch (cip_ret)
    {
        case CIP_DRV_RET_PASS:
            tmp_ret |= (SB_RET_SUCCESS & SB_PRV_RET_LOWER_MASK);
            break;
        case CIP_DRV_RET_SAME_IMAGE_VERSION:
            tmp_ret |= (SB_RET_SAME_IMAGE_VERSION & SB_PRV_RET_LOWER_MASK);
            break;
        default:
            /* In case of error, do nothing because the return value has already been set */
            break;
    }

    /* Check route is passed */
    ret = tmp_ret;
    if ((ret & SB_PRV_RET_ERROR_BITS) != SB_PRV_RET_ERROR_BITS)
    {
        if ((SB_RET_SUCCESS == ret) || (SB_RET_SAME_IMAGE_VERSION == ret))
        {
            /* In case of two SUCCESS route is passed. Do nothing */
        }
        else
        {
            /* In case of only one SUCCESS route is passed, set INTERNAL_FAIL to ret */
            ret = SB_RET_ERR_INTERNAL_FAIL;

        }
    }
    else
    {
        /* In case of ERROR route is passed. Do nothing */
    }

    return ret;
}
/**********************************************************************************************************************
* End of function r_sb_cmn_drv_get_sb_ret_from_cip_ret()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : r_sb_cmn_drv_get_mac_algo_from_sb_mac_type
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Get MAC Algorithm
 * \param       [in]   mac_type                MAC Algorithm type
 * \return
 *  - CIP_DRV_MAC_ALGO_HMAC_SHA2_224:             MAC Algorithm HMAC SHA2-224
 *  - CIP_DRV_MAC_ALGO_HMAC_SHA2_256:             MAC Algorithm HMAC SHA2-256
 *  - CIP_DRV_MAC_ALGO_HMAC_SHA2_384:             MAC Algorithm HMAC SHA2-384
 *  - CIP_DRV_MAC_ALGO_HMAC_SHA2_512:             MAC Algorithm HMAC SHA2-512
 *  - CIP_DRV_MAC_ALGO_HMAC_SHA3_224:             MAC Algorithm HMAC SHA3-224
 *  - CIP_DRV_MAC_ALGO_HMAC_SHA3_256:             MAC Algorithm HMAC SHA3-256
 *  - CIP_DRV_MAC_ALGO_HMAC_SHA3_384:             MAC Algorithm HMAC SHA3-384
 *  - CIP_DRV_MAC_ALGO_HMAC_SHA3_512:             MAC Algorithm HMAC SHA3-512
 *  - CIP_DRV_MAC_ALGO_CMAC_AES_128:              MAC Algorithm CMAC AES-128
 *  - CIP_DRV_MAC_ALGO_CMAC_AES_192:              MAC Algorithm CMAC AES-192
 *  - CIP_DRV_MAC_ALGO_CMAC_AES_256:              MAC Algorithm CMAC AES-256
 *  - SB_PRV_RET_UNSUPPORTED_ALGO:                Unsupported algorithm specified
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Returns the MAC algorithm according to the argument
 *      - Convert SB-Lib MAC type to Crypto IP-Driver MAC algorithm value
 *      - This function gets the MAC algorithm value of Crypto IP-Driver from the MAC type of #e_sb_mac_type_t type
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with CIP_DRV_MAC_ALGO_NONE
 * -# switch mac_type
 *   -# mac_type == #SB_MAC_TYPE_HMAC_SHA2_224, Set CIP_DRV_MAC_ALGO_HMAC_SHA2_224 to mac_algo
 *   -# mac_type == #SB_MAC_TYPE_HMAC_SHA2_256, Set CIP_DRV_MAC_ALGO_HMAC_SHA2_256 to mac_algo
 *   -# mac_type == #SB_MAC_TYPE_HMAC_SHA2_384, Set CIP_DRV_MAC_ALGO_HMAC_SHA2_384 to mac_algo
 *   -# mac_type == #SB_MAC_TYPE_HMAC_SHA2_512, Set CIP_DRV_MAC_ALGO_HMAC_SHA2_512 to mac_algo
 *   -# mac_type == #SB_MAC_TYPE_HMAC_SHA3_224, Set CIP_DRV_MAC_ALGO_HMAC_SHA3_224 to mac_algo
 *   -# mac_type == #SB_MAC_TYPE_HMAC_SHA3_256, Set CIP_DRV_MAC_ALGO_HMAC_SHA3_256 to mac_algo
 *   -# mac_type == #SB_MAC_TYPE_HMAC_SHA3_384, Set CIP_DRV_MAC_ALGO_HMAC_SHA3_384 to mac_algo
 *   -# mac_type == #SB_MAC_TYPE_HMAC_SHA3_512, Set CIP_DRV_MAC_ALGO_HMAC_SHA3_512 to mac_algo
 *   -# mac_type == #SB_MAC_TYPE_CMAC_AES_128,  Set CIP_DRV_MAC_ALGO_CMAC_AES_128  to mac_algo
 *   -# mac_type == #SB_MAC_TYPE_CMAC_AES_192,  Set CIP_DRV_MAC_ALGO_CMAC_AES_192  to mac_algo
 *   -# mac_type == #SB_MAC_TYPE_CMAC_AES_256,  Set CIP_DRV_MAC_ALGO_CMAC_AES_256  to mac_algo
 *   -# In the default case,                    do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
uint32_t r_sb_cmn_drv_get_mac_algo_from_sb_mac_type(const e_sb_mac_type_t mac_type)
{
    uint32_t mac_algo = CIP_DRV_MAC_ALGO_NONE;

    switch (mac_type)
    {
        case SB_MAC_TYPE_HMAC_SHA2_224:
            mac_algo = CIP_DRV_MAC_ALGO_HMAC_SHA2_224;
            break;
        case SB_MAC_TYPE_HMAC_SHA2_256:
            mac_algo = CIP_DRV_MAC_ALGO_HMAC_SHA2_256;
            break;
        case SB_MAC_TYPE_HMAC_SHA2_384:
            mac_algo = CIP_DRV_MAC_ALGO_HMAC_SHA2_384;
            break;
        case SB_MAC_TYPE_HMAC_SHA2_512:
            mac_algo = CIP_DRV_MAC_ALGO_HMAC_SHA2_512;
            break;
        case SB_MAC_TYPE_HMAC_SHA3_224:
            mac_algo = CIP_DRV_MAC_ALGO_HMAC_SHA3_224;
            break;
        case SB_MAC_TYPE_HMAC_SHA3_256:
            mac_algo = CIP_DRV_MAC_ALGO_HMAC_SHA3_256;
            break;
        case SB_MAC_TYPE_HMAC_SHA3_384:
            mac_algo = CIP_DRV_MAC_ALGO_HMAC_SHA3_384;
            break;
        case SB_MAC_TYPE_HMAC_SHA3_512:
            mac_algo = CIP_DRV_MAC_ALGO_HMAC_SHA3_512;
            break;
        case SB_MAC_TYPE_CMAC_AES_128:
            mac_algo = CIP_DRV_MAC_ALGO_CMAC_AES_128;
            break;
        case SB_MAC_TYPE_CMAC_AES_192:
            mac_algo = CIP_DRV_MAC_ALGO_CMAC_AES_192;
            break;
        case SB_MAC_TYPE_CMAC_AES_256:
            mac_algo = CIP_DRV_MAC_ALGO_CMAC_AES_256;
            break;
        default: /* In the default case, return CIP_DRV_MAC_ALGO_NONE */
            break;
    }

    return mac_algo;
}
/**********************************************************************************************************************
* End of function r_sb_cmn_drv_get_mac_algo_from_sb_mac_type()
**********************************************************************************************************************/

/*=====================================================================================================================
 Private function definitions
=====================================================================================================================*/
/**********************************************************************************************************************
* Function Name : cmn_drv_get_hash_algo
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Get Hash Algorithm
 * \param       [in]   type                   Hash Algorithm type
 * \return
 *  - CIP_DRV_HASH_ALGO_SHA2_224:                 Hash Algorithm SHA2-224
 *  - CIP_DRV_HASH_ALGO_SHA2_256:                 Hash Algorithm SHA2-256
 *  - CIP_DRV_HASH_ALGO_SHA2_384:                 Hash Algorithm SHA2-384
 *  - CIP_DRV_HASH_ALGO_SHA2_512:                 Hash Algorithm SHA2-512
 *  - CIP_DRV_HASH_ALGO_SHA3_224:                 Hash Algorithm SHA3-224
 *  - CIP_DRV_HASH_ALGO_SHA3_256:                 Hash Algorithm SHA3-256
 *  - CIP_DRV_HASH_ALGO_SHA3_384:                 Hash Algorithm SHA3-384
 *  - CIP_DRV_HASH_ALGO_SHA3_512:                 Hash Algorithm SHA3-512
 *  - SB_PRV_RET_UNSUPPORTED_ALGO:                Unsupported algorithm specified
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Returns the hash algorithm according to the argument
 *      - Convert SB-Lib HASH type to Crypto IP-Driver HASH algorithm value
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_PRV_RET_UNSUPPORTED_ALGO
 * -# switch (type & #SB_PRV_TLV_TYPE_CRYPTO_ALGO_MASK)
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_224, Set CIP_DRV_HASH_ALGO_SHA2_224 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_256, Set CIP_DRV_HASH_ALGO_SHA2_256 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_384, Set CIP_DRV_HASH_ALGO_SHA2_384 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_512, Set CIP_DRV_HASH_ALGO_SHA2_512 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_224, Set CIP_DRV_HASH_ALGO_SHA3_224 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_256, Set CIP_DRV_HASH_ALGO_SHA3_256 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_384, Set CIP_DRV_HASH_ALGO_SHA3_384 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_512, Set CIP_DRV_HASH_ALGO_SHA3_512 to hash_algo
 *   -# In the default case,                           do nothing
 * -# Return hash_algo
 *
 * \callgraph
 *********************************************************************************************************************/
static uint32_t cmn_drv_get_hash_algo(const uint32_t type)
{
    uint32_t hash_algo = SB_PRV_RET_UNSUPPORTED_ALGO;

    switch (type & SB_PRV_TLV_TYPE_CRYPTO_ALGO_MASK)
    {
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_224:
            hash_algo = CIP_DRV_HASH_ALGO_SHA2_224;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_256:
            hash_algo = CIP_DRV_HASH_ALGO_SHA2_256;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_384:
            hash_algo = CIP_DRV_HASH_ALGO_SHA2_384;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA2_512:
            hash_algo = CIP_DRV_HASH_ALGO_SHA2_512;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_224:
            hash_algo = CIP_DRV_HASH_ALGO_SHA3_224;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_256:
            hash_algo = CIP_DRV_HASH_ALGO_SHA3_256;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_384:
            hash_algo = CIP_DRV_HASH_ALGO_SHA3_384;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_SHA3_512:
            hash_algo = CIP_DRV_HASH_ALGO_SHA3_512;
            break;
        default: /* In the default case, return SB_PRV_RET_UNSUPPORTED_ALGO */
            break;
    }

    return hash_algo;
}
/**********************************************************************************************************************
* End of function cmn_drv_get_hash_algo()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : cmn_drv_get_sign_hash_algo
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Get Signature Hash Algorithm
 * \param       [in]   type                   Signature Hash Algorithm type
 * \return
 *  - CIP_DRV_HASH_ALGO_SHA2_224:                 Hash Algorithm SHA2-224
 *  - CIP_DRV_HASH_ALGO_SHA2_256:                 Hash Algorithm SHA2-256
 *  - CIP_DRV_HASH_ALGO_SHA2_384:                 Hash Algorithm SHA2-384
 *  - CIP_DRV_HASH_ALGO_SHA2_512:                 Hash Algorithm SHA2-512
 *  - CIP_DRV_HASH_ALGO_SHA3_224:                 Hash Algorithm SHA3-224
 *  - CIP_DRV_HASH_ALGO_SHA3_256:                 Hash Algorithm SHA3-256
 *  - CIP_DRV_HASH_ALGO_SHA3_384:                 Hash Algorithm SHA3-384
 *  - CIP_DRV_HASH_ALGO_SHA3_512:                 Hash Algorithm SHA3-512
 *  - SB_PRV_RET_UNSUPPORTED_ALGO:                Unsupported algorithm specified
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Returns the hash algorithm according to the argument
 *      - Convert SB-Lib Signature HASH type to Crypto IP-Driver HASH algorithm value
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_PRV_RET_UNSUPPORTED_ALGO
 * -# switch (type & #SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_MASK)
 *   -# type == #SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_224, Set CIP_DRV_HASH_ALGO_SHA2_224 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_256, Set CIP_DRV_HASH_ALGO_SHA2_256 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_384, Set CIP_DRV_HASH_ALGO_SHA2_384 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_512, Set CIP_DRV_HASH_ALGO_SHA2_512 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_224, Set CIP_DRV_HASH_ALGO_SHA3_224 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_256, Set CIP_DRV_HASH_ALGO_SHA3_256 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_384, Set CIP_DRV_HASH_ALGO_SHA3_384 to hash_algo
 *   -# type == #SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_512, Set CIP_DRV_HASH_ALGO_SHA3_512 to hash_algo
 *   -# In the default case,                                  do nothing
 * -# Return hash_algo
 *
 * \callgraph
 *********************************************************************************************************************/
static uint32_t cmn_drv_get_sign_hash_algo(const uint32_t type)
{
    uint32_t hash_algo = SB_PRV_RET_UNSUPPORTED_ALGO;

    switch (type & SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_MASK)
    {
        case SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_224:
            hash_algo = CIP_DRV_HASH_ALGO_SHA2_224;
            break;
        case SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_256:
            hash_algo = CIP_DRV_HASH_ALGO_SHA2_256;
            break;
        case SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_384:
            hash_algo = CIP_DRV_HASH_ALGO_SHA2_384;
            break;
        case SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA2_512:
            hash_algo = CIP_DRV_HASH_ALGO_SHA2_512;
            break;
        case SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_224:
            hash_algo = CIP_DRV_HASH_ALGO_SHA3_224;
            break;
        case SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_256:
            hash_algo = CIP_DRV_HASH_ALGO_SHA3_256;
            break;
        case SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_384:
            hash_algo = CIP_DRV_HASH_ALGO_SHA3_384;
            break;
        case SB_PRV_TLV_TYPE_CLS_SIGN_HASH_ALGO_SHA3_512:
            hash_algo = CIP_DRV_HASH_ALGO_SHA3_512;
            break;
        default: /* In the default case, return SB_PRV_RET_UNSUPPORTED_ALGO */
            break;
    }

    return hash_algo;
}
/**********************************************************************************************************************
* End of function cmn_drv_get_sign_hash_algo()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : cmn_drv_get_sign_algo
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Get Signature Algorithm
 * \param       [in]   type                   Signature Algorithm type
 * \return
 *  - CIP_DRV_SIGN_ALGO_ECDSA_P192:               Signature Algorithm ECC NIST P-192
 *  - CIP_DRV_SIGN_ALGO_ECDSA_P224:               Signature Algorithm ECC NIST P-224
 *  - CIP_DRV_SIGN_ALGO_ECDSA_P256:               Signature Algorithm ECC NIST P-256
 *  - CIP_DRV_SIGN_ALGO_ECDSA_P384:               Signature Algorithm ECC NIST P-384
 *  - CIP_DRV_SIGN_ALGO_ECDSA_P521:               Signature Algorithm ECC NIST P-521
 *  - CIP_DRV_SIGN_ALGO_ECDSA_BP192R1:            Signature Algorithm ECC BrainpoolP192
 *  - CIP_DRV_SIGN_ALGO_ECDSA_BP224R1:            Signature Algorithm ECC BrainpoolP224
 *  - CIP_DRV_SIGN_ALGO_ECDSA_BP256R1:            Signature Algorithm ECC BrainpoolP256
 *  - CIP_DRV_SIGN_ALGO_ECDSA_BP384R1:            Signature Algorithm ECC BrainpoolP384
 *  - CIP_DRV_SIGN_ALGO_ECDSA_BP512R1:            Signature Algorithm ECC BrainpoolP512
 *  - CIP_DRV_SIGN_ALGO_EDDSA_ED25519:            Signature Algorithm EdDSA Ed25519
 *  - CIP_DRV_SIGN_ALGO_EDDSA_ED448:              Signature Algorithm EdDSA Ed448
 *  - CIP_DRV_SIGN_ALGO_RSA1024:                  Signature Algorithm RSA 1024bit
 *  - CIP_DRV_SIGN_ALGO_RSA2048:                  Signature Algorithm RSA 2048bit
 *  - CIP_DRV_SIGN_ALGO_RSA3072:                  Signature Algorithm RSA 3072bit
 *  - CIP_DRV_SIGN_ALGO_RSA4096:                  Signature Algorithm RSA 4096bit
 *  - SB_PRV_RET_UNSUPPORTED_ALGO:                Unsupported algorithm specified
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Returns the Signature algorithm according to the argument
 *      - Convert SB-Lib Signature algorithm type to Crypto IP-Driver Signature algorithm value
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_PRV_RET_UNSUPPORTED_ALGO
 * -# switch (type & #SB_PRV_TLV_TYPE_CRYPTO_ALGO_MASK)
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P192,    Set CIP_DRV_SIGN_ALGO_ECDSA_P192 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P224,    Set CIP_DRV_SIGN_ALGO_ECDSA_P224 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P256,    Set CIP_DRV_SIGN_ALGO_ECDSA_P256 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P384,    Set CIP_DRV_SIGN_ALGO_ECDSA_P384 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P521,    Set CIP_DRV_SIGN_ALGO_ECDSA_P521 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP192R1, Set CIP_DRV_SIGN_ALGO_ECDSA_BP192R1 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP224R1, Set CIP_DRV_SIGN_ALGO_ECDSA_BP224R1 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP256R1, Set CIP_DRV_SIGN_ALGO_ECDSA_BP256R1 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP384R1, Set CIP_DRV_SIGN_ALGO_ECDSA_BP384R1 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP512R1, Set CIP_DRV_SIGN_ALGO_ECDSA_BP512R1 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_CURVE25519, Set CIP_DRV_SIGN_ALGO_EDDSA_ED25519 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_CURVE448, Set CIP_DRV_SIGN_ALGO_EDDSA_ED448 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA1024, Set CIP_DRV_SIGN_ALGO_RSA1024 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA2048, Set CIP_DRV_SIGN_ALGO_RSA2048 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA3072, Set CIP_DRV_SIGN_ALGO_RSA3072 to sign_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA4096, Set CIP_DRV_SIGN_ALGO_RSA4096 to sign_algo
 *   -# In the default case,                          do nothing
 * -# Return sign_algo
 *
 * \callgraph
 *********************************************************************************************************************/
static uint32_t cmn_drv_get_sign_algo(const uint32_t type)
{
    uint32_t sign_algo = SB_PRV_RET_UNSUPPORTED_ALGO;

    switch (type & SB_PRV_TLV_TYPE_CRYPTO_ALGO_MASK)
    {
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P192:
            sign_algo = CIP_DRV_SIGN_ALGO_ECDSA_P192;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P224:
            sign_algo = CIP_DRV_SIGN_ALGO_ECDSA_P224;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P256:
            sign_algo = CIP_DRV_SIGN_ALGO_ECDSA_P256;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P384:
            sign_algo = CIP_DRV_SIGN_ALGO_ECDSA_P384;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_P521:
            sign_algo = CIP_DRV_SIGN_ALGO_ECDSA_P521;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP192R1:
            sign_algo = CIP_DRV_SIGN_ALGO_ECDSA_BP192R1;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP224R1:
            sign_algo = CIP_DRV_SIGN_ALGO_ECDSA_BP224R1;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP256R1:
            sign_algo = CIP_DRV_SIGN_ALGO_ECDSA_BP256R1;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP384R1:
            sign_algo = CIP_DRV_SIGN_ALGO_ECDSA_BP384R1;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_ECC_BP512R1:
            sign_algo = CIP_DRV_SIGN_ALGO_ECDSA_BP512R1;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_CURVE25519:
            sign_algo = CIP_DRV_SIGN_ALGO_EDDSA_ED25519;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_CURVE448:
            sign_algo = CIP_DRV_SIGN_ALGO_EDDSA_ED448;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA1024:
            sign_algo = CIP_DRV_SIGN_ALGO_RSA1024;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA2048:
            sign_algo = CIP_DRV_SIGN_ALGO_RSA2048;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA3072:
            sign_algo = CIP_DRV_SIGN_ALGO_RSA3072;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_RSA4096:
            sign_algo = CIP_DRV_SIGN_ALGO_RSA4096;
            break;
        default: /* In the default case, return SB_PRV_RET_UNSUPPORTED_ALGO */
            break;
    }

    return sign_algo;
}
/**********************************************************************************************************************
* End of function cmn_drv_get_sign_algo()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : cmn_drv_get_sign_scheme
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Get Signature Scheme
 * \param       [in]   type                   Signature Scheme type
 * \param       [in]   sign_algo              Signature Algorithm
 * \return
 *  - CIP_DRV_SCHEME_NONE:                        Signature Scheme none
 *  - CIP_DRV_SCHEME_RSASSA_PKCS1_V1_5:           Signature Scheme RSASSA-PKCS1_v1_5
 *  - CIP_DRV_SCHEME_RSASSA_PSS:                  Signature Scheme RSASSA-PSS
 *  - SB_PRV_RET_UNSUPPORTED_ALGO:                Unsupported algorithm specified
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Returns the Signature scheme according to the argument
 *      - Convert SB-Lib Signature scheme type to Crypto IP-Driver Signature scheme value
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_PRV_RET_UNSUPPORTED_ALGO
 * -# If (CIP_DRV_SIGN_ALGO_RSA1024 == sign_algo) || (CIP_DRV_SIGN_ALGO_RSA2048 == sign_algo) ||
 *       (CIP_DRV_SIGN_ALGO_RSA3072 == sign_algo) || (CIP_DRV_SIGN_ALGO_RSA4096 == sign_algo)
 *   -# switch (type & #SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_MASK)
 *     -# type == #SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_RSASSA_PKCS1_V1_5, Set CIP_DRV_SCHEME_RSASSA_PKCS1_V1_5 to sign_scheme
 *     -# type == #SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_RSASSA_PSS,        Set CIP_DRV_SCHEME_RSASSA_PSS to sign_scheme
 *     -# In the default case,                                        do nothing
 * -# Else
 *   -# Set CIP_DRV_SCHEME_NONE to sign_scheme
 * -# Return sign_scheme
 *
 * \callgraph
 *********************************************************************************************************************/
static uint32_t cmn_drv_get_sign_scheme(const uint32_t type, const uint32_t sign_algo)
{
    uint32_t sign_scheme = SB_PRV_RET_UNSUPPORTED_ALGO;

    if ((CIP_DRV_SIGN_ALGO_RSA1024 == sign_algo) || (CIP_DRV_SIGN_ALGO_RSA2048 == sign_algo) ||
        (CIP_DRV_SIGN_ALGO_RSA3072 == sign_algo) || (CIP_DRV_SIGN_ALGO_RSA4096 == sign_algo))
    {
        switch (type & SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_MASK)
        {
            case SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_RSASSA_PKCS1_V1_5:
                sign_scheme = CIP_DRV_SCHEME_RSASSA_PKCS1_V1_5;
                break;
            case SB_PRV_TLV_TYPE_CLS_SIGN_SCHEME_RSASSA_PSS:
                sign_scheme = CIP_DRV_SCHEME_RSASSA_PSS;
                break;
            default: /* In the default case, return SB_PRV_RET_UNSUPPORTED_ALGO */
                break;
        }
    }
    else
    {
        sign_scheme = CIP_DRV_SCHEME_NONE;
    }

    return sign_scheme;
}
/**********************************************************************************************************************
* End of function cmn_drv_get_sign_scheme()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : cmn_drv_get_img_cip_info_algo
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Get Cipher algorithm
 * \param       [in]   type                    Cipher algorithm type
 * \return
 *  - CIP_DRV_CIPHER_ALGO_AES128:                 Cipher Algorithm AES-128
 *  - CIP_DRV_CIPHER_ALGO_AES192:                 Cipher Algorithm AES-192
 *  - CIP_DRV_CIPHER_ALGO_AES256:                 Cipher Algorithm AES-256
 *  - SB_PRV_RET_UNSUPPORTED_ALGO:                Unsupported algorithm specified
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Returns the Cipher algorithm according to the argument
 *      - Convert SB-Lib Cipher algorithm type to Crypto IP-Driver Cipher algorithm value
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_PRV_RET_UNSUPPORTED_ALGO
 * -# switch (type & #SB_PRV_TLV_TYPE_CRYPTO_ALGO_MASK)
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_AES128, Set CIP_DRV_CIPHER_ALGO_AES128 to cip_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_AES192, Set CIP_DRV_CIPHER_ALGO_AES192 to cip_algo
 *   -# type == #SB_PRV_TLV_TYPE_CRYPTO_ALGO_AES256, Set CIP_DRV_CIPHER_ALGO_AES256 to cip_algo
 *   -# In the default case,                         do nothing
 * -# Return cip_algo
 *
 * \callgraph
 *********************************************************************************************************************/
static uint32_t cmn_drv_get_img_cip_info_algo(const uint32_t type)
{
    uint32_t cip_algo = SB_PRV_RET_UNSUPPORTED_ALGO;

    switch (type & SB_PRV_TLV_TYPE_CRYPTO_ALGO_MASK)
    {
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_AES128:
            cip_algo = CIP_DRV_CIPHER_ALGO_AES128;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_AES192:
            cip_algo = CIP_DRV_CIPHER_ALGO_AES192;
            break;
        case SB_PRV_TLV_TYPE_CRYPTO_ALGO_AES256:
            cip_algo = CIP_DRV_CIPHER_ALGO_AES256;
            break;
        default: /* In the default case, return SB_PRV_RET_UNSUPPORTED_ALGO */
            break;
    }

    return cip_algo;
}
/**********************************************************************************************************************
* End of function cmn_drv_get_img_cip_info_algo()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : cmn_drv_get_img_cip_info_mode
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Get Cipher mode
 * \param       [in]   type                    Cipher mode type
 * \return
 *  - CIP_DRV_CIPHER_MODE_ECB:                    Cipher mode ECB
 *  - CIP_DRV_CIPHER_MODE_CBC:                    Cipher mode CBC
 *  - CIP_DRV_CIPHER_MODE_CFB:                    Cipher mode CFB
 *  - CIP_DRV_CIPHER_MODE_OFB:                    Cipher mode OFB
 *  - CIP_DRV_CIPHER_MODE_CTR:                    Cipher mode CTR
 *  - SB_PRV_RET_UNSUPPORTED_ALGO:                Unsupported algorithm specified
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Returns the Cipher mode according to the argument
 *      - Convert SB-Lib Cipher mode type to Crypto IP-Driver Cipher mod value
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_PRV_RET_UNSUPPORTED_ALGO
 * -# switch (type & #SB_PRV_TLV_TYPE_CLS_ICI_MODE_MASK)
 *   -# type == #SB_PRV_TLV_TYPE_CLS_ICI_MODE_ECB, Set CIP_DRV_CIPHER_MODE_ECB to cip_mode
 *   -# type == #SB_PRV_TLV_TYPE_CLS_ICI_MODE_CBC, Set CIP_DRV_CIPHER_MODE_CBC to cip_mode
 *   -# type == #SB_PRV_TLV_TYPE_CLS_ICI_MODE_CFB, Set CIP_DRV_CIPHER_MODE_CFB to cip_mode
 *   -# type == #SB_PRV_TLV_TYPE_CLS_ICI_MODE_OFB, Set CIP_DRV_CIPHER_MODE_OFB to cip_mode
 *   -# type == #SB_PRV_TLV_TYPE_CLS_ICI_MODE_CTR, Set CIP_DRV_CIPHER_MODE_CTR to cip_mode
 *   -# In the default case,                       do nothing
 * -# Return cip_mode
 *
 * \callgraph
 *********************************************************************************************************************/
static uint32_t cmn_drv_get_img_cip_info_mode(const uint32_t type)
{
    uint32_t cip_mode = SB_PRV_RET_UNSUPPORTED_ALGO;

    switch (type & SB_PRV_TLV_TYPE_CLS_ICI_MODE_MASK)
    {
        case SB_PRV_TLV_TYPE_CLS_ICI_MODE_ECB:
            cip_mode = CIP_DRV_CIPHER_MODE_ECB;
            break;
        case SB_PRV_TLV_TYPE_CLS_ICI_MODE_CBC:
            cip_mode = CIP_DRV_CIPHER_MODE_CBC;
            break;
        case SB_PRV_TLV_TYPE_CLS_ICI_MODE_CFB:
            cip_mode = CIP_DRV_CIPHER_MODE_CFB;
            break;
        case SB_PRV_TLV_TYPE_CLS_ICI_MODE_OFB:
            cip_mode = CIP_DRV_CIPHER_MODE_OFB;
            break;
        case SB_PRV_TLV_TYPE_CLS_ICI_MODE_CTR:
            cip_mode = CIP_DRV_CIPHER_MODE_CTR;
            break;
        default: /* In the default case, return SB_PRV_RET_UNSUPPORTED_ALGO */
            break;
    }

    return cip_mode;
}
/**********************************************************************************************************************
* End of function cmn_drv_get_img_cip_info_mode()
**********************************************************************************************************************/

/*=====================================================================================================================
 End of file
=====================================================================================================================*/
