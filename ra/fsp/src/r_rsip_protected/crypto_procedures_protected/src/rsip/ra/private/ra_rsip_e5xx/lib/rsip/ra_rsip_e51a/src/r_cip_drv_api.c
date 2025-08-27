/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name    : r_tsip_api.c
 * @brief Interface definition for the r_tsip module.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup grp_device_hal_tsip Device HAL TSIP Implementation
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#include <stddef.h>
#include "r_cip_private.h"
#include "r_sb_api.h"
#include "r_sb_manifest.h"
#include "r_vdev_fsbl_option.h"
#include "r_rsip_primitive.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#define QX_END_POSTION_OFFSET   (31)
#define QY_START_POSTION_OFFSET (32)
#define QY_END_POSTION_OFFSET   (63)

#define KEY_CART_TLV_START_POSTION     (9)
#define KEY_CART_TLV_LENGTH_POSTION    (8)

#define CRC_DMA_BLOCK_WORD_SIZE    (64u)
#define CRC_DMA_BLOCK_BYTE_SIZE    (256u)

#define OEMBL_VER_INIT_VALUE    (0xFF)
#define OEMBL_VER_MASK_INIT     (0x80000000)
#define OEMBL_VER_LOOP_MASK     (0x1F)
#define OEMBL_VER_MAX_VALUE     (64)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief The API for outputting random User Key Generation Information of AES256 bit.
 * @param[in,out] *key_index Output the user Key Generation Information
 * @retval TSIP_SUCCESS Success
 * @retval TSIP_ERR_RESOURCE_CONFLICT Resource conflict
 * @details This API outputs 256-bit AES user key index.@n
 *          This API generates a user key from a random number in the TSIP. Accordingly, user key input is unnecessary.
 *          By encrypting data using the user key index that is output by this API, dead copying of data
 *          can be prevented.
 * @pre TSIP Enabled State
 * @post TSIP Enabled State@n
 **********************************************************************************************************************/
cip_drv_ret_t R_CIP_DRV_CheckImageVersion(const uint32_t image_version, const uint32_t build_num)
{
    FSP_PARAMETER_NOT_USED(build_num);

    rsip_ret_t    rsip_ret;
    cip_drv_ret_t ret;

    uint32_t next_ver[1];
    uint32_t current_ver[1];
    uint32_t Fcntdata[2];
    uint8_t  loop = 0;
    uint8_t  oembl_version = OEMBL_VER_INIT_VALUE;

    next_ver[0] = image_version;

    Fcntdata[0] = VFSBL_FCNTDATAR1;
    Fcntdata[1] = VFSBL_FCNTDATAR0;

    /* Convert version value read from Flash to integer format */
    while( ( ( Fcntdata[(loop >> 5)] & ( OEMBL_VER_MASK_INIT >> ( loop & OEMBL_VER_LOOP_MASK ) ) ) ==  0 ) )
    {
        loop++;

        if( loop >= OEMBL_VER_MAX_VALUE ){ break; }
    }

    oembl_version = OEMBL_VER_MAX_VALUE - loop;

    current_ver[0] = (uint32_t)oembl_version;

    rsip_ret = r_rsip_p0c(current_ver, next_ver);

    /* Convert error code */
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            ret = CIP_DRV_RET_PASS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            ret = CIP_DRV_RET_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_RET_VERIFICATION_FAIL:
        {
            ret = CIP_DRV_RET_LOWER_IMAGE_VERSION;
            break;
        }

        case RSIP_RET_VERSION_MATCH:
        {
            ret = CIP_DRV_RET_SAME_IMAGE_VERSION;
            break;
        }

        default:
        {
            ret = CIP_DRV_RET_FAIL;
        }
    }

    return ret;
}

/***************************************
 End of function R_CIP_DRV_CheckImageVersion
 ***************************************/

/*******************************************************************************************************************//**
 * @brief The API unwraps Wraped Hardware Unique Key(W-HUK) and loads it inside IP.
 * @retval CIP_DRV_RET_SUCCESS Success
 * @retval CIP_DRV_RET_ERR_RESOURCE_CONFLICT Resource conflict
 * @retval CIP_DRV_RET_ERR_FAIL Abnormal termination
 * @details The API unwraps Wraped Hardware Unique Key(W-HUK) and loads it inside IP.
 **********************************************************************************************************************/
cip_drv_ret_t R_CIP_DRV_PrcDeriveMacKeyFromHuk(void)
{
    return CIP_DRV_RET_SUCCESS;
}
/***************************************
 End of function R_CIP_DRV_PrcDeriveMacKeyFromHuk
 ***************************************/


/*******************************************************************************************************************//**
 * @brief Data (key certificate and code certificate) signature verification is performed.
 * @param[in] *p_cc_key_cert_param key certification information,
 * @param[in] p_cc_code_cert_param code certification information.
 * @param[in] p_dec_tmp_img_param dummy
 * @param[in] p_enc_img_param
 * @param[in] mac_algo dummy
 * @param[in,out] *p_tag MAC of Code Certificate.
 * @retval CIP_DRV_RET_PASS Success
 * @retval CIP_DRV_RET_RESOURCE_CONFLICT Resource conflict
 * @retval CIP_DRV_RET_PARAM_ERROR Input parameter error
 * @retval CIP_DRV_RET_FAIL Abnormal termination
 * @details This API verifies the signatures of Data.
 *          If the signature verification is successful, the HMAC-SHA256 caluclation of the Image and Code certificate.
 *          Support elliptic curves are NIST P-256.
 **********************************************************************************************************************/
cip_drv_ret_t R_CIP_DRV_PrcCheckIntegrity(const st_cip_drv_cc_key_cert_param_t*  const p_cc_key_cert_param,
        const st_cip_drv_cc_code_cert_param_t* const p_cc_code_cert_param,
        const st_cip_drv_cipher_img_param_t* const p_dec_tmp_img_param,
        const st_cip_drv_cipher_img_param_t* const p_enc_img_param,
        const uint32_t mac_algo, uint32_t* const p_tag)
{
    FSP_PARAMETER_NOT_USED(p_dec_tmp_img_param);
    FSP_PARAMETER_NOT_USED(p_enc_img_param);
    FSP_PARAMETER_NOT_USED(mac_algo);

    rsip_ret_t    rsip_ret;
    cip_drv_ret_t ret;
    uint32_t KeyCertificateLength[1];
    uint32_t KeyCertificatePubKey[4];
    uint32_t ImgPkHash[2];
    uint32_t CodeCertificateLength[1];
    uint32_t CodeCertificatePubKey[4];
    uint32_t QxPubKeyPt;
    uint32_t ImgPkHashPt;
    uint32_t ImageLen;
    const st_sb_search_tlv_type_t search_tlv_signer_id[1] =
            {
                    { 0x10000000U, 0xFF000000U }
            };
    st_sb_tlv_t signer_id_tlvs[1];
    cip_drv_ret_t ret_complement;

    if(p_cc_code_cert_param->img_len < R_SHIP_OEM_BL_MIN_SIZE)
    {
        return CIP_DRV_RET_PARAM_ERROR;
    }

    KeyCertificateLength[0] = bswap_32big(p_cc_key_cert_param->key_cert_sign_len ) ;
    QxPubKeyPt = (uint32_t) ((p_cc_key_cert_param->p_sign_pk - p_cc_key_cert_param->p_key_cert)<<2);
    KeyCertificatePubKey[0] = bswap_32big(QxPubKeyPt);
    KeyCertificatePubKey[1] = bswap_32big(QxPubKeyPt + QX_END_POSTION_OFFSET);
    KeyCertificatePubKey[2] = bswap_32big(QxPubKeyPt + QY_START_POSTION_OFFSET);
    KeyCertificatePubKey[3] = bswap_32big(QxPubKeyPt + QY_END_POSTION_OFFSET);

    ret = r_sb_mani_parse_tlvs((const uint8_t*)&p_cc_key_cert_param->p_key_cert[KEY_CART_TLV_START_POSTION] ,
                               (p_cc_key_cert_param->p_key_cert[KEY_CART_TLV_LENGTH_POSTION]),
                               1, search_tlv_signer_id, signer_id_tlvs);
    if (SB_RET_SUCCESS != ret)
    {
        return CIP_DRV_RET_PARAM_ERROR;
    }
    ImgPkHashPt = (uint32_t) ((signer_id_tlvs->p_val - p_cc_key_cert_param->p_key_cert)<<2);
    ImgPkHash[0] = bswap_32big(ImgPkHashPt );
    ImgPkHash[1] = bswap_32big((ImgPkHashPt + signer_id_tlvs->byte_len) -1 );

    CodeCertificateLength[0] = bswap_32big(p_cc_code_cert_param->code_cert_sign_len);
    QxPubKeyPt = (uint32_t) ((p_cc_code_cert_param->p_sign_pk - p_cc_code_cert_param->p_code_cert)<<2);
    CodeCertificatePubKey[0] = bswap_32big(QxPubKeyPt);
    CodeCertificatePubKey[1] = bswap_32big(QxPubKeyPt + QX_END_POSTION_OFFSET);
    CodeCertificatePubKey[2] = bswap_32big(QxPubKeyPt + QY_START_POSTION_OFFSET);
    CodeCertificatePubKey[3] = bswap_32big(QxPubKeyPt + QY_END_POSTION_OFFSET);
    ImageLen = bswap_32big(p_cc_code_cert_param->img_len>>2);

    rsip_ret = r_rsip_p0d((uint32_t *) p_cc_key_cert_param->p_key_cert,
                          KeyCertificateLength,
                          (uint32_t *) p_cc_key_cert_param->p_sign,
                          KeyCertificatePubKey,
                          ImgPkHash,
                          (uint32_t *) VFSBL_OEMROOTPKHASH_ADDR,
                          (uint32_t *) p_cc_code_cert_param->p_code_cert,
                          CodeCertificateLength,
                          (uint32_t *) p_cc_code_cert_param->p_sign,
                          CodeCertificatePubKey,
                          (uint32_t *) p_cc_code_cert_param->p_img,
                          DomainParam_NIST_P256,
                          ImageLen,
                          &p_tag[1]);

    /* Convert error code */
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            ret = CIP_DRV_RET_PASS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            ret = CIP_DRV_RET_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_RET_PARAM_FAIL:
        {
            ret = CIP_DRV_RET_PARAM_ERROR;
            break;
        }

        case RSIP_RET_VERIFICATION_FAIL:
        {
            ret = CIP_DRV_RET_AUTH_FAIL;
            break;
        }

        default:
        {
            ret = CIP_DRV_RET_FAIL;
        }
    }

    if (CIP_DRV_RET_PASS == ret)
    {
        ret_complement = ~CIP_DRV_RET_PASS;
        if((~ret) == ret_complement)
        {
            p_tag[0] = R_CIP_DRV_HMAC_SHA256_TLV;
            rsip_ret = r_rsip_p0e();

            /* Convert error code */
            switch (rsip_ret)
            {
                case RSIP_RET_PASS:
                {
                    ret = CIP_DRV_RET_PASS;
                    break;
                }

                case RSIP_RET_RESOURCE_CONFLICT:
                {
                    ret = CIP_DRV_RET_RESOURCE_CONFLICT;
                    break;
                }

                default:
                {
                    ret = CIP_DRV_RET_FAIL;
                }
            }
        }
        else
        {
            ret = CIP_DRV_RET_TAMPER_DETECT;
        }
    }
    else
    {
        __NOP();
    }

    return ret;
}
/***************************************
 End of function R_CIP_DRV_PrcCheckIntegrity
 ***************************************/

/*******************************************************************************************************************//**
 * @} (end addtogroup Device HAL TSIP (Trusted Secure IP modules))
 **********************************************************************************************************************/

/* End of File */
