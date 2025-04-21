/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*!********************************************************************************************************************
* \file             : r_sb_api.c
* \par version      : 1.00
* \par Product Name : Renesas-SB-Lib FSBL Custom
* \par Device(s)    : Does not depend on specific hardware
* \par Description  : This file implements the SB-Lib public APIs.
**********************************************************************************************************************/

/*=====================================================================================================================
 Includes <System Includes> , "Project Includes"
=====================================================================================================================*/
#include <stddef.h>
#include "r_sb_api.h"
#include "r_sb_build_config.h"
#include "r_sb_cmn.h"
#include "r_sb_manifest.h"
#include "r_sb_sb.h"

/*=====================================================================================================================
 Private macro definitions
=====================================================================================================================*/
/* Error checking needs to be done where the settings are used, not in a configuration file. */
#if (SB_CFG_PARAM_CHECKING_ENABLE == 1U)
    #if (0U != SB_CFG_SB_MAC_VERIFICATION) && (1U != SB_CFG_SB_MAC_VERIFICATION)
    #error This is an error check from the build configuration. Cause: SB_CFG_SB_MAC_VERIFICATION
    #endif
    #if (0U != SB_CFG_SB_CERT_CHAIN_VERIFICATION) && (1U != SB_CFG_SB_CERT_CHAIN_VERIFICATION)
    #error This is an error check from the build configuration. Cause: SB_CFG_SB_CERT_CHAIN_VERIFICATION
    #endif
    #if (0U != SB_CFG_SB_CERT_CHAIN_USE_IMG_PK) && (1U != SB_CFG_SB_CERT_CHAIN_USE_IMG_PK)
    #error This is an error check from the build configuration. Cause: SB_CFG_SB_CERT_CHAIN_USE_IMG_PK
    #endif
    #if (0U != SB_CFG_IMAGE_ENC_DEC) && (1U != SB_CFG_IMAGE_ENC_DEC)
    #error This is an error check from the build configuration. Cause: SB_CFG_IMAGE_ENC_DEC
    #endif
    #if (0U != SB_CFG_CHECK_CRC) && (1U != SB_CFG_CHECK_CRC)
    #error This is an error check from the build configuration. Cause: SB_CFG_CHECK_CRC
    #endif
    #if (0U != SB_CFG_CHECK_INTEGRITY) && (1U != SB_CFG_CHECK_INTEGRITY)
    #error This is an error check from the build configuration. Cause: SB_CFG_CHECK_INTEGRITY
    #endif
#endif

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

/*=====================================================================================================================
 Public function definitions
=====================================================================================================================*/

/**********************************************************************************************************************
* Function Name : R_SB_CheckIntegrity
**********************************************************************************************************************/
sb_ret_t R_SB_CheckIntegrity(const uint8_t* const p_key_cert, const uint32_t key_cert_len_max,
                                const uint8_t* const p_code_cert, const uint32_t code_cert_len_max,
                                const e_sb_mac_type_t mac_type, uint32_t* const p_tag)
{
#if (SB_CFG_CHECK_INTEGRITY == 1U)
    /*-----------------------------------------------------------------------------------------------------------------
     Local variables
    -----------------------------------------------------------------------------------------------------------------*/
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    sb_bool_t         flow_correct_ret = SB_PRV_FALSE;
    st_sb_key_cert_t  key_cert_st;
    st_sb_code_cert_t code_cert_st;

    /*-----------------------------------------------------------------------------------------------------------------
     Function body
    -----------------------------------------------------------------------------------------------------------------*/
    /* Initialize flow counter */
    r_sb_cmn_fc_ci_init();

    /* Check NULL argument excepted mac_tlv */
    if ((NULL != p_key_cert) && (NULL != p_code_cert) && (NULL != p_tag))
    {
        /* Check alignment */
        /* No problem with casting to pointer size */
        if ((((uintptr_t)p_key_cert & (uintptr_t)SB_PRV_REMAINDER_DIV4) == (uintptr_t)0UL) &&
            (((uintptr_t)p_code_cert & (uintptr_t)SB_PRV_REMAINDER_DIV4) == (uintptr_t)0UL) && /* Same cast as above */
            (((uintptr_t)p_tag & (uintptr_t)SB_PRV_REMAINDER_DIV4) == (uintptr_t)0UL)) /* Same cast as above */
        {
            /* Set Key cert structure */
            ret = r_sb_mani_set_key_cert_st(p_key_cert, &key_cert_st);
            if (SB_RET_SUCCESS == ret)
            {
                /* Clear ret */
                ret = SB_RET_ERR_INTERNAL_FAIL;
                (void) ret;

                /* Check key cert */
                ret = r_sb_mani_chk_key_cert(&key_cert_st, key_cert_len_max);
                if (SB_RET_SUCCESS == ret)
                {
                    /* Clear ret */
                    ret = SB_RET_ERR_INTERNAL_FAIL;
                    (void) ret;

                    /* Set Code cert structure */
                    ret = r_sb_mani_set_code_cert_st(p_code_cert, &code_cert_st);
                    if (SB_RET_SUCCESS == ret)
                    {
                        /* Clear ret */
                        ret = SB_RET_ERR_INTERNAL_FAIL;
                        (void) ret;

                        /* Check code cert */
                        ret = r_sb_mani_chk_code_cert(&code_cert_st, code_cert_len_max);
                        if (SB_RET_SUCCESS == ret)
                        {
                            /* Clear ret */
                            ret = SB_RET_ERR_INTERNAL_FAIL;
                            (void) ret;

                            /* Verifies the image integrity with a certificate chain and generate MAC */
                            ret = r_sb_sb_check_integrity(&key_cert_st, &code_cert_st, mac_type, p_tag);
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
                /* Do nothing. */
            }
        }
        else
        {
            /* Invalid alignment */
            ret = SB_RET_ERR_INVALID_ALIGNMENT;
        }
    }
    else
    {
        /* Invalid argument */
        ret = SB_RET_ERR_INVALID_ARG;
    }

    /* Verify flow counter */
    flow_correct_ret = r_sb_cmn_fc_is_ci_flow_correct();
    if ((SB_RET_SUCCESS == ret) || (SB_RET_SAME_IMAGE_VERSION == ret))
    {
        if (SB_PRV_TRUE == flow_correct_ret)
        {
            /* Do nothing */
        }
        else
        {
            /* Flow counter mismatch  */
            ret = SB_RET_ERR_INTERNAL_FAIL;
        }
    }
    else
    {
        /* Do nothing */
    }

    return ret;
#else /* (SB_CFG_CHECK_INTEGRITY == 1U) */
    return SB_RET_ERR_UNSUPPORTED_FUNCTION;
#endif /* (SB_CFG_CHECK_INTEGRITY == 1U) */
}
/**********************************************************************************************************************
* End of function R_SB_CheckIntegrity()
**********************************************************************************************************************/

/*=====================================================================================================================
 Private function definitions
=====================================================================================================================*/

/*=====================================================================================================================
 End of file
=====================================================================================================================*/

