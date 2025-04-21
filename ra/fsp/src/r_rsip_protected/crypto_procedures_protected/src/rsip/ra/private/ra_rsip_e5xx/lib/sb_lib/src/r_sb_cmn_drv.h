/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*!********************************************************************************************************************
* \file             : r_sb_cmn_drv.h
* \par version      : 1.00
* \par Product Name : Renesas-SB-Lib FSBL Custom
* \par Device(s)    : Does not depend on specific hardware
* \par Description  : This file defines the macros, types and declarations used in the common API for
*                     CIP (CryptoIP) drivers.
***********************************************************************************************************************/

#ifndef R_SB_CMN_DRV_H
/* Multiple inclusion protection macro */
#define R_SB_CMN_DRV_H

/*=====================================================================================================================
 Public macro definitions
=====================================================================================================================*/

/*=====================================================================================================================
 Public type definitions
=====================================================================================================================*/

/*=====================================================================================================================
 Public global variables
=====================================================================================================================*/

/*=====================================================================================================================
 Public global functions
=====================================================================================================================*/
extern sb_ret_t r_sb_cmn_drv_set_cc_key_cert_param (const st_sb_key_cert_t * const p_key_cert_st,
                                                    const st_sb_tlv_t * const p_img_pk_hash_tlv,
                                                    const st_sb_tlv_t * const p_sign_pk_tlv,
                                                    const st_sb_tlv_t * const p_sign_tlv,
                                                    st_cip_drv_cc_key_cert_param_t* const p_cc_key_cert_param);
extern sb_ret_t r_sb_cmn_drv_set_cc_code_cert_param (const st_sb_code_cert_t * const p_code_cert_st,
                                                    const uint32_t img_addr,
                                                    const st_sb_tlv_t * const p_sign_pk_tlv,
                                                    const st_sb_tlv_t * const p_sign_tlv,
                                                    const st_sb_tlv_t * const p_img_hash_tlv,
                                                    st_cip_drv_cc_code_cert_param_t* const p_cc_code_cert_param);
extern sb_ret_t r_sb_cmn_drv_set_cipher_img_param (const st_sb_code_cert_t * const p_code_cert_st,
                                            const st_sb_tlv_t * const p_img_cip_info,
                                            const st_sb_tlv_t * const p_img_cip_iv,
                                            const sb_bool_t          is_overwrite_image,
                                            const uint32_t           timing,
                                            st_cip_drv_cipher_img_param_t * const p_cipher_img_param);
extern sb_ret_t r_sb_cmn_drv_get_sb_ret_from_cip_ret (const cip_drv_ret_t cip_ret);
extern uint32_t r_sb_cmn_drv_get_mac_algo_from_sb_mac_type (const e_sb_mac_type_t mac_type);

#endif /* R_SB_CMN_DRV_H */
/*=====================================================================================================================
 End of File
=====================================================================================================================*/
