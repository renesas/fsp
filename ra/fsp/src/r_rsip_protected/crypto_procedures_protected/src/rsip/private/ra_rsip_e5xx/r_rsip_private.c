/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_private.h"
#include "r_rsip_wrapper.h"
#include "r_rsip_primitive.h"
#include "r_rsip_api.h"
#include "r_rsip_reg.h"
#include "r_rsip_addr.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MSTP_SECURITY                                       R_MSTP->MSTPCRC_b.MSTPC31

/* For SHA, HMAC-SHA */
#define RSIP_PRV_SHA_INIT_VAL1                              (0x80000000U)
#define RSIP_PRV_SHA_INIT_VAL2                              (0x00000000U)
#define RSIP_PRV_CMD_INIT_TO_FINAL                          (0U)
#define RSIP_PRV_CMD_INIT_TO_SUSPEND                        (1U)
#define RSIP_PRV_CMD_RESUME_TO_SUSPEND                      (2U)
#define RSIP_PRV_CMD_RESUME_TO_FINAL                        (3U)
#define RSIP_PRV_CMD_INIT_TO_COMP_FINAL                     (4U)
#define RSIP_PRV_CMD_RESUME_TO_COMP_FINAL                   (5U)
#define RSIP_PRV_CMD_SHA_256                                (2U)
#define RSIP_PRV_CMD_SHA_384                                (5U)
#define RSIP_PRV_WORD_SIZE_HMAC_MAC_BUFFER                  (8U)

/* Primitive function names */
#if RSIP_CFG_AES_128_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_AES_128                 r_rsip_p07
 #define RSIP_PRV_FUNC_KEY_WRAP_AES_128                     r_rsip_wrapper_p6f_aes128
 #if RSIP_CFG_AES_ECB_CBC_CTR_ENABLE
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_128         r_rsip_wrapper_p47i_aes128ecb_encrypt
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_128         r_rsip_wrapper_p47i_aes128ecb_decrypt
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_128         r_rsip_wrapper_p47i_aes128cbc_encrypt
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_128         r_rsip_wrapper_p47i_aes128cbc_decrypt
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_128             r_rsip_wrapper_p47i_aes128ctr_crypt
  #define RSIP_PRV_FUNC_AES_CIPHER_UPDATE_128               r_rsip_p47u
  #define RSIP_PRV_FUNC_AES_CIPHER_FINAL_128                r_rsip_p47f
 #else
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_128         NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_128         NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_128         NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_128         NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_128             NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_UPDATE_128               NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_FINAL_128                NULL
 #endif
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_AES_128                 NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_AES_128                     NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_128          NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_128          NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_128          NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_128          NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_128              NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_UPDATE_128                NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_FINAL_128                 NULL
#endif
#if RSIP_CFG_AES_GCM_ENABLE
 #define RSIP_PRV_FUNC_AES_GCM_ENC_INIT_128                 r_rsip_wrapper_p29i_aes128gcm_encrypt
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_AAD_128           r_rsip_p29a
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_TRANSITION_128    r_rsip_p29t
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_128               r_rsip_p29u
 #define RSIP_PRV_FUNC_AES_GCM_ENC_FINAL_128                r_rsip_p29f
 #define RSIP_PRV_FUNC_AES_GCM_DEC_INIT_128                 r_rsip_wrapper_p32i_aes128gcm_decrypt
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_AAD_128           r_rsip_p32a
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_TRANSITION_128    r_rsip_p32t
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_128               r_rsip_p32u
 #define RSIP_PRV_FUNC_AES_GCM_DEC_FINAL_128                r_rsip_p32f
#else
 #define RSIP_PRV_FUNC_AES_GCM_ENC_INIT_128                 NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_AAD_128           NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_TRANSITION_128    NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_128               NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_FINAL_128                NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_INIT_128                 NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_AAD_128           NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_TRANSITION_128    NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_128               NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_FINAL_128                NULL
#endif
#if RSIP_CFG_AES_CCM_ENABLE
 #define RSIP_PRV_FUNC_AES_CCM_ENC_INIT_128                 r_rsip_wrapper_p95i_aes128ccm_encrypt
 #define RSIP_PRV_FUNC_AES_CCM_ENC_UPDATE_128               r_rsip_p95u
 #define RSIP_PRV_FUNC_AES_CCM_ENC_FINAL_128                r_rsip_wrapper_p95f_aes128ccm_encrypt
 #define RSIP_PRV_FUNC_AES_CCM_DEC_INIT_128                 r_rsip_wrapper_p98i_aes128ccm_decrypt
 #define RSIP_PRV_FUNC_AES_CCM_DEC_UPDATE_128               r_rsip_p98u
 #define RSIP_PRV_FUNC_AES_CCM_DEC_FINAL_128                r_rsip_wrapper_p98f_aes128ccm_decrypt
#else
 #define RSIP_PRV_FUNC_AES_CCM_ENC_INIT_128                 NULL
 #define RSIP_PRV_FUNC_AES_CCM_ENC_UPDATE_128               NULL
 #define RSIP_PRV_FUNC_AES_CCM_ENC_FINAL_128                NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_INIT_128                 NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_UPDATE_128               NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_FINAL_128                NULL
#endif
#if RSIP_CFG_AES_CMAC_ENABLE
 #define RSIP_PRV_FUNC_AES_MAC_INIT_128                     r_rsip_wrapper_p41i_aes128mac
 #define RSIP_PRV_FUNC_AES_MAC_UPDATE_128                   r_rsip_p41u
 #define RSIP_PRV_FUNC_AES_MAC_GENERATE_FINAL_128           r_rsip_wrapper_p41f_aes128mac_generate
 #define RSIP_PRV_FUNC_AES_MAC_VERIFY_FINAL_128             r_rsip_wrapper_p41f_aes128mac_verify
#else
 #define RSIP_PRV_FUNC_AES_MAC_INIT_128                     NULL
 #define RSIP_PRV_FUNC_AES_MAC_UPDATE_128                   NULL
 #define RSIP_PRV_FUNC_AES_MAC_GENERATE_FINAL_128           NULL
 #define RSIP_PRV_FUNC_AES_MAC_VERIFY_FINAL_128             NULL
#endif

#if RSIP_CFG_AES_256_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_AES_256                 r_rsip_p08
 #define RSIP_PRV_FUNC_KEY_WRAP_AES_256                     r_rsip_wrapper_p6f_aes256
 #if RSIP_CFG_AES_ECB_CBC_CTR_ENABLE
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_256         r_rsip_wrapper_p50i_aes256ecb_encrypt
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_256         r_rsip_wrapper_p50i_aes256ecb_decrypt
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_256         r_rsip_wrapper_p50i_aes256cbc_encrypt
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_256         r_rsip_wrapper_p50i_aes256cbc_decrypt
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_256             r_rsip_wrapper_p50i_aes256ctr_crypt
  #define RSIP_PRV_FUNC_AES_CIPHER_UPDATE_256               r_rsip_p50u
  #define RSIP_PRV_FUNC_AES_CIPHER_FINAL_256                r_rsip_p50f
 #else
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_256         NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_256         NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_256         NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_256         NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_256             NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_UPDATE_256               NULL
  #define RSIP_PRV_FUNC_AES_CIPHER_FINAL_256                NULL
 #endif
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_AES_256                 NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_AES_256                     NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_256          NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_256          NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_256          NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_256          NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_256              NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_UPDATE_256                NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_FINAL_256                 NULL
#endif
#if RSIP_CFG_AES_GCM_ENABLE
 #define RSIP_PRV_FUNC_AES_GCM_ENC_INIT_256                 r_rsip_wrapper_p34i_aes256gcm_encrypt
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_AAD_256           r_rsip_p34a
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_TRANSITION_256    r_rsip_p34t
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_256               r_rsip_p34u
 #define RSIP_PRV_FUNC_AES_GCM_ENC_FINAL_256                r_rsip_p34f
 #define RSIP_PRV_FUNC_AES_GCM_DEC_INIT_256                 r_rsip_wrapper_p36i_aes256gcm_decrypt
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_AAD_256           r_rsip_p36a
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_TRANSITION_256    r_rsip_p36t
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_256               r_rsip_p36u
 #define RSIP_PRV_FUNC_AES_GCM_DEC_FINAL_256                r_rsip_p36f
#else
 #define RSIP_PRV_FUNC_AES_GCM_ENC_INIT_256                 NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_AAD_256           NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_TRANSITION_256    NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_256               NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_FINAL_256                NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_INIT_256                 NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_AAD_256           NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_TRANSITION_256    NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_256               NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_FINAL_256                NULL
#endif
#if RSIP_CFG_AES_CCM_ENABLE
 #define RSIP_PRV_FUNC_AES_CCM_ENC_INIT_256                 r_rsip_wrapper_pa1i_aes256ccm_encrypt
 #define RSIP_PRV_FUNC_AES_CCM_ENC_UPDATE_256               r_rsip_pa1u
 #define RSIP_PRV_FUNC_AES_CCM_ENC_FINAL_256                r_rsip_pa1f
 #define RSIP_PRV_FUNC_AES_CCM_DEC_INIT_256                 r_rsip_wrapper_pa4i_aes256ccm_decrypt
 #define RSIP_PRV_FUNC_AES_CCM_DEC_UPDATE_256               r_rsip_pa4u
 #define RSIP_PRV_FUNC_AES_CCM_DEC_FINAL_256                r_rsip_pa4f
#else
 #define RSIP_PRV_FUNC_AES_CCM_ENC_INIT_256                 NULL
 #define RSIP_PRV_FUNC_AES_CCM_ENC_UPDATE_256               NULL
 #define RSIP_PRV_FUNC_AES_CCM_ENC_FINAL_256                NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_INIT_256                 NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_UPDATE_256               NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_FINAL_256                NULL
#endif
#if RSIP_CFG_AES_CMAC_ENABLE
 #define RSIP_PRV_FUNC_AES_MAC_INIT_256                     r_rsip_wrapper_p44i_aes256mac
 #define RSIP_PRV_FUNC_AES_MAC_UPDATE_256                   r_rsip_p44u
 #define RSIP_PRV_FUNC_AES_MAC_GENERATE_FINAL_256           r_rsip_wrapper_p44f_aes256mac_generate
 #define RSIP_PRV_FUNC_AES_MAC_VERIFY_FINAL_256             r_rsip_wrapper_p44f_aes256mac_verify
#else
 #define RSIP_PRV_FUNC_AES_MAC_INIT_256                     NULL
 #define RSIP_PRV_FUNC_AES_MAC_UPDATE_256                   NULL
 #define RSIP_PRV_FUNC_AES_MAC_GENERATE_FINAL_256           NULL
 #define RSIP_PRV_FUNC_AES_MAC_VERIFY_FINAL_256             NULL
#endif

#if RSIP_CFG_XTS_AES_128_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_128             r_rsip_p16
 #define RSIP_PRV_FUNC_KEY_WRAP_XTS_AES_128                 r_rsip_wrapper_p6f_aes128xts
 #if RSIP_CFG_AES_XTS_ENABLE
  #define RSIP_PRV_FUNC_XTS_AES_ENC_INIT_128                r_rsip_pb3i
  #define RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_128              r_rsip_pb3u
  #define RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_128               r_rsip_pb3f
  #define RSIP_PRV_FUNC_XTS_AES_DEC_INIT_128                r_rsip_pb6i
  #define RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_128              r_rsip_pb6u
  #define RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_128               r_rsip_pb6f
 #else
  #define RSIP_PRV_FUNC_XTS_AES_ENC_INIT_128                NULL
  #define RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_128              NULL
  #define RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_128               NULL
  #define RSIP_PRV_FUNC_XTS_AES_DEC_INIT_128                NULL
  #define RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_128              NULL
  #define RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_128               NULL
 #endif
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_128             NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_XTS_AES_128                 NULL

 #define RSIP_PRV_FUNC_XTS_AES_ENC_INIT_128                 NULL
 #define RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_128               NULL
 #define RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_128                NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_INIT_128                 NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_128               NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_128                NULL
#endif

#if RSIP_CFG_XTS_AES_256_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_256             r_rsip_p17
 #define RSIP_PRV_FUNC_KEY_WRAP_XTS_AES_256                 r_rsip_wrapper_p6f_aes256xts
 #if RSIP_CFG_AES_XTS_ENABLE
  #define RSIP_PRV_FUNC_XTS_AES_ENC_INIT_256                r_rsip_pb9i
  #define RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_256              r_rsip_pb9u
  #define RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_256               r_rsip_pb9f
  #define RSIP_PRV_FUNC_XTS_AES_DEC_INIT_256                r_rsip_pc2i
  #define RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_256              r_rsip_pc2u
  #define RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_256               r_rsip_pc2f
 #else
  #define RSIP_PRV_FUNC_XTS_AES_ENC_INIT_256                NULL
  #define RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_256              NULL
  #define RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_256               NULL
  #define RSIP_PRV_FUNC_XTS_AES_DEC_INIT_256                NULL
  #define RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_256              NULL
  #define RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_256               NULL
 #endif
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_256             NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_XTS_AES_256                 NULL

 #define RSIP_PRV_FUNC_XTS_AES_ENC_INIT_256                 NULL
 #define RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_256               NULL
 #define RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_256                NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_INIT_256                 NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_256               NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_256                NULL
#endif

#if RSIP_CFG_ECC_SECP256R1_ENABLE
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP256R1      r_rsip_wrapper_pf4_secp256r1
 #define RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP256R1_PUBLIC        r_rsip_wrapper_p6f_secp256r1_pub
 #define RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP256R1_PRIVATE       r_rsip_wrapper_p6f_secp256r1_priv

 #define RSIP_PRV_FUNC_ECDSA_SIGN_SECP256R1                 r_rsip_wrapper_pf0_secp256r1
 #define RSIP_PRV_FUNC_ECDSA_VERIFY_SECP256R1               r_rsip_wrapper_pf1_secp256r1
#else
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP256R1      NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP256R1_PUBLIC        NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP256R1_PRIVATE       NULL

 #define RSIP_PRV_FUNC_ECDSA_SIGN_SECP256R1                 NULL
 #define RSIP_PRV_FUNC_ECDSA_VERIFY_SECP256R1               NULL
#endif

#if RSIP_CFG_ECC_SECP384R1_ENABLE
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP384R1      r_rsip_wrapper_pf9_secp384r1
 #define RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP384R1_PUBLIC        r_rsip_wrapper_p6f_secp384r1_pub
 #define RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP384R1_PRIVATE       r_rsip_wrapper_p6f_secp384r1_priv

 #define RSIP_PRV_FUNC_ECDSA_SIGN_SECP384R1                 r_rsip_wrapper_pf5_secp384r1
 #define RSIP_PRV_FUNC_ECDSA_VERIFY_SECP384R1               r_rsip_wrapper_pf6_secp384r1
#else
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP384R1      NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP384R1_PUBLIC        NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP384R1_PRIVATE       NULL

 #define RSIP_PRV_FUNC_ECDSA_SIGN_SECP384R1                 NULL
 #define RSIP_PRV_FUNC_ECDSA_VERIFY_SECP384R1               NULL
#endif

#if RSIP_CFG_RSA_2048_ENABLE
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_2048           r_rsip_wrapper_p2b_rsa2048
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_2048_PUBLIC             r_rsip_wrapper_p6f_rsa2048_pub
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_2048_PRIVATE            r_rsip_wrapper_p6f_rsa2048_priv

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_2048                     r_rsip_p56
 #define RSIP_PRV_FUNC_RSA_DECRYPT_2048                     r_rsip_p57
#else
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_2048           NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_2048_PUBLIC             NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_2048_PRIVATE            NULL

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_2048                     NULL
 #define RSIP_PRV_FUNC_RSA_DECRYPT_2048                     NULL
#endif

#if RSIP_CFG_RSA_3072_ENABLE
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_3072           NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_3072_PUBLIC             r_rsip_wrapper_p6f_rsa3072_pub
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_3072_PRIVATE            r_rsip_wrapper_p6f_rsa3072_priv

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_3072                     r_rsip_p79
 #define RSIP_PRV_FUNC_RSA_DECRYPT_3072                     r_rsip_p7a
#else
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_3072           NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_3072_PUBLIC             NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_3072_PRIVATE            NULL

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_3072                     NULL
 #define RSIP_PRV_FUNC_RSA_DECRYPT_3072                     NULL
#endif

#if RSIP_CFG_RSA_4096_ENABLE
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_4096           NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_4096_PUBLIC             r_rsip_wrapper_p6f_rsa4096_pub
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_4096_PRIVATE            r_rsip_wrapper_p6f_rsa4096_priv

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_4096                     r_rsip_p7b
 #define RSIP_PRV_FUNC_RSA_DECRYPT_4096                     r_rsip_p7c
#else
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_4096           NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_4096_PUBLIC             NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_RSA_4096_PRIVATE            NULL

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_4096                     NULL
 #define RSIP_PRV_FUNC_RSA_DECRYPT_4096                     NULL
#endif

#if RSIP_CFG_HMAC_SHA256_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA256             r_rsip_p0b
 #define RSIP_PRV_FUNC_KEY_WRAP_HMAC_SHA256                 r_rsip_wrapper_p6f_hmacsha256
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA256             NULL
 #define RSIP_PRV_FUNC_KEY_WRAP_HMAC_SHA256                 NULL
#endif

#define RSIP_PRV_FUNC_RANDOM_NUMBER_GENERATE                r_rsip_p20
#define RSIP_PRV_FUNC_GHASH_COMPUTE                         r_rsip_p21

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_rsip_sha_cmd
{
    RSIP_SHA_CMD_INIT_TO_FINAL,
    RSIP_SHA_CMD_INIT_TO_SUSPEND,
    RSIP_SHA_CMD_RESUME_TO_SUSPEND,
    RSIP_SHA_CMD_RESUME_TO_FINAL,
    RSIP_SHA_CMD_INIT_TO_COMP_FINAL,
    RSIP_SHA_CMD_RESUME_TO_COMP_FINAL,
} rsip_sha_cmd_t;

typedef enum e_rsip_hmac_cmd
{
    RSIP_HMAC_CMD_SIGN   = 0U,
    RSIP_HMAC_CMD_VERIFY = 1U,
} rsip_hmac_cmd_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
const bool g_sha_enabled[RSIP_HASH_TYPE_NUM] =
{
    [RSIP_HASH_TYPE_SHA256] = RSIP_CFG_SHA256_ENABLE,
    [RSIP_HASH_TYPE_SHA384] = RSIP_CFG_SHA384_ENABLE
};

static const uint32_t gs_cmd_hash_type[] =
{
    [RSIP_HASH_TYPE_SHA256] = RSIP_PRV_CMD_SHA_256,
    [RSIP_HASH_TYPE_SHA384] = RSIP_PRV_CMD_SHA_384,
};

static const uint32_t gs_hmac_hash_type[] =
{
    [RSIP_KEY_HMAC_SHA256] = BSWAP_32BIG_C(2U)
};

static const uint32_t gs_hmac_cmd[] =
{
    [RSIP_HMAC_CMD_SIGN]   = BSWAP_32BIG_C(0U),
    [RSIP_HMAC_CMD_VERIFY] = BSWAP_32BIG_C(1U),
};

static const uint32_t gs_cmd_sha_cmd[] =
{
    [RSIP_SHA_CMD_INIT_TO_FINAL]        = RSIP_PRV_CMD_INIT_TO_FINAL,
    [RSIP_SHA_CMD_INIT_TO_SUSPEND]      = RSIP_PRV_CMD_INIT_TO_SUSPEND,
    [RSIP_SHA_CMD_RESUME_TO_SUSPEND]    = RSIP_PRV_CMD_RESUME_TO_SUSPEND,
    [RSIP_SHA_CMD_RESUME_TO_FINAL]      = RSIP_PRV_CMD_RESUME_TO_FINAL,
    [RSIP_SHA_CMD_INIT_TO_COMP_FINAL]   = RSIP_PRV_CMD_INIT_TO_COMP_FINAL,
    [RSIP_SHA_CMD_RESUME_TO_COMP_FINAL] = RSIP_PRV_CMD_RESUME_TO_COMP_FINAL,
};

static const uint32_t gs_sha_msg_len_multi[2] =
{
    RSIP_PRV_SHA_INIT_VAL1, RSIP_PRV_SHA_INIT_VAL2
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const bool g_hmac_enabled[RSIP_KEY_HMAC_NUM] =
{
    [RSIP_KEY_HMAC_SHA256] = RSIP_CFG_HMAC_SHA256_ENABLE
};

const rsip_func_t g_func =
{
    .p_key_generate_aes            =
    {
        [RSIP_KEY_AES_128] = RSIP_PRV_FUNC_KEY_GENERATE_AES_128,
        [RSIP_KEY_AES_256] = RSIP_PRV_FUNC_KEY_GENERATE_AES_256
    },
    .p_key_generate_xts_aes        =
    {
        [RSIP_KEY_AES_128] = RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_128,
        [RSIP_KEY_AES_256] = RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_256
    },
    .p_key_generate_hmac           =
    {
        [RSIP_KEY_HMAC_SHA256] = RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA256
    },
    .p_key_pair_generate_ecc       =
    {
        [RSIP_KEY_ECC_SECP256R1] = RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP256R1,
        [RSIP_KEY_ECC_SECP384R1] = RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP384R1
    },
    .p_key_pair_generate_rsa       =
    {
        [RSIP_KEY_RSA_2048] = RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_2048
    },

    .p_encrypted_key_wrap_aes      =
    {
        [RSIP_KEY_AES_128] = RSIP_PRV_FUNC_KEY_WRAP_AES_128,
        [RSIP_KEY_AES_256] = RSIP_PRV_FUNC_KEY_WRAP_AES_256
    },
    .p_encrypted_key_wrap_xts_aes  =
    {
        [RSIP_KEY_AES_128] = RSIP_PRV_FUNC_KEY_WRAP_XTS_AES_128,
        [RSIP_KEY_AES_256] = RSIP_PRV_FUNC_KEY_WRAP_XTS_AES_256
    },
    .p_encrypted_key_wrap_ecc_pub  =
    {
        [RSIP_KEY_ECC_SECP256R1] = RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP256R1_PUBLIC,
        [RSIP_KEY_ECC_SECP384R1] = RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP384R1_PUBLIC
    },
    .p_encrypted_key_wrap_ecc_priv =
    {
        [RSIP_KEY_ECC_SECP256R1] = RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP256R1_PRIVATE,
        [RSIP_KEY_ECC_SECP384R1] = RSIP_PRV_FUNC_KEY_WRAP_ECC_SECP384R1_PRIVATE
    },
    .p_encrypted_key_wrap_rsa_pub  =
    {
        [RSIP_KEY_RSA_2048] = RSIP_PRV_FUNC_KEY_WRAP_RSA_2048_PUBLIC,
        [RSIP_KEY_RSA_3072] = RSIP_PRV_FUNC_KEY_WRAP_RSA_3072_PUBLIC,
        [RSIP_KEY_RSA_4096] = RSIP_PRV_FUNC_KEY_WRAP_RSA_4096_PUBLIC
    },
    .p_encrypted_key_wrap_rsa_priv =
    {
        [RSIP_KEY_RSA_2048] = RSIP_PRV_FUNC_KEY_WRAP_RSA_2048_PRIVATE,
        [RSIP_KEY_RSA_3072] = RSIP_PRV_FUNC_KEY_WRAP_RSA_3072_PRIVATE,
        [RSIP_KEY_RSA_4096] = RSIP_PRV_FUNC_KEY_WRAP_RSA_4096_PRIVATE
    },
    .p_rsa_public                  =
    {
        [RSIP_KEY_RSA_2048] = RSIP_PRV_FUNC_RSA_ENCRYPT_2048,
        [RSIP_KEY_RSA_3072] = RSIP_PRV_FUNC_RSA_ENCRYPT_3072,
        [RSIP_KEY_RSA_4096] = RSIP_PRV_FUNC_RSA_ENCRYPT_4096
    },
    .p_rsa_private                 =
    {
        [RSIP_KEY_RSA_2048] = RSIP_PRV_FUNC_RSA_DECRYPT_2048,
        [RSIP_KEY_RSA_3072] = RSIP_PRV_FUNC_RSA_DECRYPT_3072,
        [RSIP_KEY_RSA_4096] = RSIP_PRV_FUNC_RSA_DECRYPT_4096
    },
    .p_aes_cipher                  =
    {
        [RSIP_KEY_AES_128] =
        {
        .p_init_ecb_enc = RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_128,
        .p_init_ecb_dec = RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_128,
        .p_init_cbc_enc = RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_128,
        .p_init_cbc_dec = RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_128,
        .p_init_ctr     = RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_128,
        .p_update       = RSIP_PRV_FUNC_AES_CIPHER_UPDATE_128,
        .p_final        = RSIP_PRV_FUNC_AES_CIPHER_FINAL_128,
        },
        [RSIP_KEY_AES_256] =
        {
        .p_init_ecb_enc = RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_256,
        .p_init_ecb_dec = RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_256,
        .p_init_cbc_enc = RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_256,
        .p_init_cbc_dec = RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_256,
        .p_init_ctr     = RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_256,
        .p_update       = RSIP_PRV_FUNC_AES_CIPHER_UPDATE_256,
        .p_final        = RSIP_PRV_FUNC_AES_CIPHER_FINAL_256,
        }
    },

    .p_aes_xts_enc                 =
    {
        [RSIP_KEY_AES_128] =
        {
        .p_init   = RSIP_PRV_FUNC_XTS_AES_ENC_INIT_128,
        .p_update = RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_128,
        .p_final  = RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_128
        },
        [RSIP_KEY_AES_256] =
        {
        .p_init   = RSIP_PRV_FUNC_XTS_AES_ENC_INIT_256,
        .p_update = RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_256,
        .p_final  = RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_256
        }
    },
    .p_aes_xts_dec                 =
    {
        [RSIP_KEY_AES_128] =
        {
        .p_init   = RSIP_PRV_FUNC_XTS_AES_DEC_INIT_128,
        .p_update = RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_128,
        .p_final  = RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_128
        },
        [RSIP_KEY_AES_256] =
        {
        .p_init   = RSIP_PRV_FUNC_XTS_AES_DEC_INIT_256,
        .p_update = RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_256,
        .p_final  = RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_256
        }
    },

    .p_aes_gcm_enc                 =
    {
        [RSIP_KEY_AES_128] =
        {
        .p_init             = RSIP_PRV_FUNC_AES_GCM_ENC_INIT_128,
        .p_updateAad        = RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_AAD_128,
        .p_updateTransition = RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_TRANSITION_128,
        .p_update           = RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_128,
        .p_encryptFinal     = RSIP_PRV_FUNC_AES_GCM_ENC_FINAL_128
        },
        [RSIP_KEY_AES_256] =
        {
        .p_init             = RSIP_PRV_FUNC_AES_GCM_ENC_INIT_256,
        .p_updateAad        = RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_AAD_256,
        .p_updateTransition = RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_TRANSITION_256,
        .p_update           = RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_256,
        .p_encryptFinal     = RSIP_PRV_FUNC_AES_GCM_ENC_FINAL_256
        }
    },
    .p_aes_gcm_dec                 =
    {
        [RSIP_KEY_AES_128] =
        {
        .p_init             = RSIP_PRV_FUNC_AES_GCM_DEC_INIT_128,
        .p_updateAad        = RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_AAD_128,
        .p_updateTransition = RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_TRANSITION_128,
        .p_update           = RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_128,
        .p_decryptFinal     = RSIP_PRV_FUNC_AES_GCM_DEC_FINAL_128
        },
        [RSIP_KEY_AES_256] =
        {
        .p_init             = RSIP_PRV_FUNC_AES_GCM_DEC_INIT_256,
        .p_updateAad        = RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_AAD_256,
        .p_updateTransition = RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_TRANSITION_256,
        .p_update           = RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_256,
        .p_decryptFinal     = RSIP_PRV_FUNC_AES_GCM_DEC_FINAL_256
        }
    },
    .p_aes_ccm_enc                 =
    {
        [RSIP_KEY_AES_128] =
        {
        .p_encryptInit  = RSIP_PRV_FUNC_AES_CCM_ENC_INIT_128,
        .p_update       = RSIP_PRV_FUNC_AES_CCM_ENC_UPDATE_128,
        .p_encryptFinal = RSIP_PRV_FUNC_AES_CCM_ENC_FINAL_128
        },
        [RSIP_KEY_AES_256] =
        {
        .p_encryptInit  = RSIP_PRV_FUNC_AES_CCM_ENC_INIT_256,
        .p_update       = RSIP_PRV_FUNC_AES_CCM_ENC_UPDATE_256,
        .p_encryptFinal = RSIP_PRV_FUNC_AES_CCM_ENC_FINAL_256
        }
    },
    .p_aes_ccm_dec                 =
    {
        [RSIP_KEY_AES_128] =
        {
        .p_decryptInit  = RSIP_PRV_FUNC_AES_CCM_DEC_INIT_128,
        .p_update       = RSIP_PRV_FUNC_AES_CCM_DEC_UPDATE_128,
        .p_decryptFinal = RSIP_PRV_FUNC_AES_CCM_DEC_FINAL_128
        },
        [RSIP_KEY_AES_256] =
        {
        .p_decryptInit  = RSIP_PRV_FUNC_AES_CCM_DEC_INIT_256,
        .p_update       = RSIP_PRV_FUNC_AES_CCM_DEC_UPDATE_256,
        .p_decryptFinal = RSIP_PRV_FUNC_AES_CCM_DEC_FINAL_256
        }
    },

    .p_aes_mac                     =
    {
        [RSIP_KEY_AES_128] =
        {
        .p_init          = RSIP_PRV_FUNC_AES_MAC_INIT_128,
        .p_update        = RSIP_PRV_FUNC_AES_MAC_UPDATE_128,
        .p_generateFinal = RSIP_PRV_FUNC_AES_MAC_GENERATE_FINAL_128,
        .p_verifyFinal   = RSIP_PRV_FUNC_AES_MAC_VERIFY_FINAL_128
        },
        [RSIP_KEY_AES_256] =
        {
        .p_init          = RSIP_PRV_FUNC_AES_MAC_INIT_256,
        .p_update        = RSIP_PRV_FUNC_AES_MAC_UPDATE_256,
        .p_generateFinal = RSIP_PRV_FUNC_AES_MAC_GENERATE_FINAL_256,
        .p_verifyFinal   = RSIP_PRV_FUNC_AES_MAC_VERIFY_FINAL_256
        }
    },
    .p_ecdsa_sign                  =
    {
        [RSIP_KEY_ECC_SECP256R1] = RSIP_PRV_FUNC_ECDSA_SIGN_SECP256R1,
        [RSIP_KEY_ECC_SECP384R1] = RSIP_PRV_FUNC_ECDSA_SIGN_SECP384R1,
    },
    .p_ecdsa_verify                =
    {
        [RSIP_KEY_ECC_SECP256R1] = RSIP_PRV_FUNC_ECDSA_VERIFY_SECP256R1,
        [RSIP_KEY_ECC_SECP384R1] = RSIP_PRV_FUNC_ECDSA_VERIFY_SECP384R1,
    },
    .p_encrypted_key_wrap_hmac     =
    {
        [RSIP_KEY_HMAC_SHA256] = RSIP_PRV_FUNC_KEY_WRAP_HMAC_SHA256
    },
    .p_rng           = RSIP_PRV_FUNC_RANDOM_NUMBER_GENERATE,
    .p_ghash_compute = RSIP_PRV_FUNC_GHASH_COMPUTE
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_open (void)
{
    uint32_t   LC[1]    = {0};
    rsip_ret_t rsip_ret = RSIP_RET_FAIL;

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

    /* Casting structure pointer is used for address. */
    MSTP_SECURITY = 0U;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);

    r_rsip_p00();

    rsip_ret = r_rsip_p81();

    if (RSIP_RET_PASS == rsip_ret)
    {
        WR1_PROG(REG_1424H, RSIP_PRV_CMD_REG_1424H);
        WR1_PROG(REG_1428H, RSIP_PRV_CMD_REG_1428H);
        rsip_ret = r_rsip_p82();
        if (RSIP_RET_RETRY == rsip_ret)
        {
            rsip_ret = r_rsip_p82();
            if (RSIP_RET_RETRY == rsip_ret)
            {
                rsip_ret = r_rsip_p82();
            }
        }
    }

    if (RSIP_RET_PASS == rsip_ret)
    {
        LC[0]    = (R_PSCU->DLMMON);
        rsip_ret = r_rsip_p40(LC);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_close (void)
{
    r_rsip_p00();

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

    /* Casting structure pointer is used for address. */
    MSTP_SECURITY = 1U;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);

    return RSIP_RET_PASS;
}

void r_rsip_kuk_store (const uint8_t * p_key_update_key_value)
{
    memcpy(S_INST2, p_key_update_key_value, sizeof(S_INST2));
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_sha1sha2_compute_single (const uint32_t   in_data_msg[],
                                           uint32_t         out_data_msg_digest[],
                                           rsip_hash_type_t hash_type,
                                           uint32_t         message_length)
{
    uint32_t in_data_hash_type[1] =
    {
        bswap_32big(gs_cmd_hash_type[hash_type])
    };
    uint32_t in_data_msg_len[2] =
    {
        in_data_msg_len[0] = r_rsip_byte_to_bit_convert_upper(message_length),
        in_data_msg_len[1] = r_rsip_byte_to_bit_convert_lower(message_length)
    };

    /* MAX_CNT: message length in word order */
    uint32_t max_cnt = r_rsip_byte_to_word_convert(message_length);

    /** Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_p31(in_data_hash_type, in_data_msg, in_data_msg_len, out_data_msg_digest, max_cnt);
}

rsip_ret_t r_rsip_sha1sha2_init_update (rsip_hash_type_t hash_type,
                                        const uint8_t  * p_message,
                                        uint64_t         message_length,
                                        uint32_t       * internal_state)
{
    /* Call primitive (cast to match the argument type with the primitive function) */
    uint32_t in_data_hasg_type[1] =
    {
        bswap_32big(gs_cmd_hash_type[hash_type])
    };

    uint32_t in_data_cmd[1] =
    {
        bswap_32big(gs_cmd_sha_cmd[RSIP_SHA_CMD_INIT_TO_SUSPEND])
    };

    return r_rsip_p72(in_data_hasg_type,
                      in_data_cmd,
                      (const uint32_t *) p_message,
                      gs_sha_msg_len_multi,
                      NULL,
                      NULL,
                      internal_state,
                      r_rsip_byte_to_word_convert((uint32_t) message_length));
}

rsip_ret_t r_rsip_sha1sha2_resume_update (rsip_hash_type_t hash_type,
                                          const uint8_t  * p_message,
                                          uint64_t         message_length,
                                          uint32_t       * internal_state)
{
    uint32_t in_data_hash_type[1] =
    {
        bswap_32big(gs_cmd_hash_type[hash_type])
    };

    uint32_t in_data_cmd[1] =
    {
        bswap_32big(gs_cmd_sha_cmd[RSIP_SHA_CMD_RESUME_TO_SUSPEND])
    };

    return r_rsip_p72(in_data_hash_type,
                      in_data_cmd,
                      (const uint32_t *) p_message,
                      NULL,
                      internal_state,
                      NULL,
                      internal_state,
                      r_rsip_byte_to_word_convert((uint32_t) message_length));
}

rsip_ret_t r_rsip_sha1sha2_update (rsip_hash_type_t hash_type,
                                   const uint8_t  * p_message,
                                   uint64_t         message_length,
                                   uint32_t       * internal_state)
{
    return r_rsip_sha1sha2_resume_update(hash_type, p_message, message_length, internal_state);
}

rsip_ret_t r_rsip_sha1sha2_suspend (uint32_t * internal_state)
{

    /* Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_p73s(internal_state);
}

rsip_ret_t r_rsip_sha1sha2_init_final (rsip_hash_type_t hash_type,
                                       const uint8_t  * p_message,
                                       uint64_t         message_length,
                                       uint8_t        * p_digest)
{
    uint32_t in_data_hash_type[1] =
    {
        bswap_32big(gs_cmd_hash_type[hash_type])
    };
    uint32_t msg_len[2] =
    {
        r_rsip_byte_to_bit_convert_upper(message_length),
        r_rsip_byte_to_bit_convert_lower(message_length)
    };

    uint32_t in_data_cmd[1] =
    {
        bswap_32big(gs_cmd_sha_cmd[RSIP_SHA_CMD_INIT_TO_FINAL])
    };

    return r_rsip_p72(in_data_hash_type,
                      in_data_cmd,
                      (const uint32_t *) p_message,
                      msg_len,
                      NULL,
                      (uint32_t *) p_digest,
                      NULL,
                      r_rsip_byte_to_word_convert((uint32_t) message_length));
}

rsip_ret_t r_rsip_sha1sha2_resume_final (rsip_hash_type_t hash_type,
                                         const uint8_t  * p_message,
                                         uint64_t         message_length,
                                         uint64_t         total_message_length,
                                         uint8_t        * p_digest,
                                         uint32_t       * internal_state)
{
    /* Overwrite internal state */
    internal_state[16] = r_rsip_byte_to_bit_convert_lower(total_message_length);
    internal_state[17] = r_rsip_byte_to_bit_convert_upper(total_message_length);
    internal_state[18] = r_rsip_byte_to_bit_convert_upper(message_length);
    internal_state[19] = r_rsip_byte_to_bit_convert_lower(message_length);

    uint32_t in_data_hash_type[1] =
    {
        bswap_32big(gs_cmd_hash_type[hash_type])
    };

    uint32_t in_data_cmd[1] =
    {
        bswap_32big(gs_cmd_sha_cmd[RSIP_SHA_CMD_RESUME_TO_FINAL])
    };

    return r_rsip_p72(in_data_hash_type,
                      in_data_cmd,
                      (const uint32_t *) p_message,
                      NULL,
                      internal_state,
                      (uint32_t *) p_digest,
                      NULL,
                      r_rsip_byte_to_word_convert((uint32_t) message_length));
}

rsip_ret_t r_rsip_sha1sha2_final (rsip_hash_type_t hash_type,
                                  const uint8_t  * p_message,
                                  uint64_t         message_length,
                                  uint64_t         total_message_length,
                                  uint8_t        * p_digest,
                                  uint32_t       * internal_state)
{
    return r_rsip_sha1sha2_resume_final(hash_type,
                                        p_message,
                                        message_length,
                                        total_message_length,
                                        p_digest,
                                        internal_state);
}

rsip_ret_t r_rsip_hmac_init_update (const rsip_wrapped_key_t * p_wrapped_key,
                                    const uint8_t            * p_message,
                                    uint64_t                   message_length,
                                    uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(internal_state);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p75i((uint32_t *) p_wrapped_key->value,
                                      &gs_hmac_hash_type[p_wrapped_key->subtype],
                                      gs_sha_msg_len_multi);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret = r_rsip_p75u((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_resume_update (const rsip_wrapped_key_t * p_wrapped_key,
                                      const uint8_t            * p_message,
                                      uint64_t                   message_length,
                                      uint32_t                 * internal_state)
{
    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p75r((uint32_t *) p_wrapped_key->value,
                                      &gs_hmac_hash_type[p_wrapped_key->subtype],
                                      internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret = r_rsip_p75u((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_update (const rsip_wrapped_key_t * p_wrapped_key,
                               const uint8_t            * p_message,
                               uint64_t                   message_length,
                               uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(internal_state);

    /* Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_p75u((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
}

rsip_ret_t r_rsip_hmac_suspend (uint32_t * internal_state)
{

    /* Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_p75s(internal_state);
}

rsip_ret_t r_rsip_hmac_init_final (const rsip_wrapped_key_t * p_wrapped_key,
                                   const uint8_t            * p_message,
                                   uint64_t                   message_length,
                                   uint8_t                  * p_mac)
{
    uint32_t msg_len[2] =
    {
        r_rsip_byte_to_bit_convert_upper(message_length),
        r_rsip_byte_to_bit_convert_lower(message_length)
    };

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p75i((uint32_t *) p_wrapped_key->value,
                                      &gs_hmac_hash_type[p_wrapped_key->subtype],
                                      msg_len);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret =
            r_rsip_p75f(&gs_hmac_cmd[RSIP_HMAC_CMD_SIGN],
                        (const uint32_t *) p_message,
                        NULL,
                        NULL,
                        r_rsip_byte_to_word_convert((uint32_t) message_length),
                        (uint32_t *) p_mac);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_resume_final (const rsip_wrapped_key_t * p_wrapped_key,
                                     const uint8_t            * p_message,
                                     uint64_t                   message_length,
                                     uint64_t                   total_message_length,
                                     uint8_t                  * p_mac,
                                     uint32_t                 * internal_state)
{
    /* Overwrite internal state */
    internal_state[16] = r_rsip_byte_to_bit_convert_lower(total_message_length);
    internal_state[17] = r_rsip_byte_to_bit_convert_upper(total_message_length);
    internal_state[18] = r_rsip_byte_to_bit_convert_upper(message_length);
    internal_state[19] = r_rsip_byte_to_bit_convert_lower(message_length);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p75r((uint32_t *) p_wrapped_key->value,
                                      &gs_hmac_hash_type[p_wrapped_key->subtype],
                                      internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret =
            r_rsip_p75f(&gs_hmac_cmd[RSIP_HMAC_CMD_SIGN],
                        (const uint32_t *) p_message,
                        NULL,
                        NULL,
                        r_rsip_byte_to_word_convert((uint32_t) message_length),
                        (uint32_t *) p_mac);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_final (const rsip_wrapped_key_t * p_wrapped_key,
                              const uint8_t            * p_message,
                              uint64_t                   message_length,
                              uint64_t                   total_message_length,
                              uint8_t                  * p_mac,
                              uint32_t                 * internal_state)
{
    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p75s(internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret = r_rsip_hmac_resume_final(p_wrapped_key,
                                            p_message,
                                            message_length,
                                            total_message_length,
                                            p_mac,
                                            internal_state);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_init_verify (const rsip_wrapped_key_t * p_wrapped_key,
                                    const uint8_t            * p_message,
                                    uint64_t                   message_length,
                                    const uint8_t            * p_mac,
                                    uint32_t                   mac_length)
{
    uint32_t msg_len[2] =
    {
        r_rsip_byte_to_bit_convert_upper(message_length),
        r_rsip_byte_to_bit_convert_lower(message_length)
    };
    uint32_t InData_MAC[RSIP_PRV_WORD_SIZE_HMAC_MAC_BUFFER] =
    {
        0
    };
    memcpy(InData_MAC, p_mac, mac_length);
    uint32_t mac_len[1] =
    {
        bswap_32big(mac_length)
    };

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p75i((uint32_t *) p_wrapped_key->value,
                                      &gs_hmac_hash_type[p_wrapped_key->subtype],
                                      msg_len);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret =
            r_rsip_p75f(&gs_hmac_cmd[RSIP_HMAC_CMD_VERIFY],
                        (const uint32_t *) p_message,
                        InData_MAC,
                        mac_len,
                        r_rsip_byte_to_word_convert((uint32_t) message_length),
                        (uint32_t *) NULL);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_resume_verify (const rsip_wrapped_key_t * p_wrapped_key,
                                      const uint8_t            * p_message,
                                      uint64_t                   message_length,
                                      uint64_t                   total_message_length,
                                      const uint8_t            * p_mac,
                                      uint32_t                   mac_length,
                                      uint32_t                 * internal_state)
{
    /* Overwrite internal state */
    internal_state[16] = r_rsip_byte_to_bit_convert_lower(total_message_length);
    internal_state[17] = r_rsip_byte_to_bit_convert_upper(total_message_length);
    internal_state[18] = r_rsip_byte_to_bit_convert_upper(message_length);
    internal_state[19] = r_rsip_byte_to_bit_convert_lower(message_length);

    uint32_t InData_MAC[RSIP_PRV_WORD_SIZE_HMAC_MAC_BUFFER] =
    {
        0
    };
    memcpy(InData_MAC, p_mac, mac_length);
    uint32_t mac_len[1] =
    {
        bswap_32big(mac_length)
    };

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p75r((uint32_t *) p_wrapped_key->value,
                                      &gs_hmac_hash_type[p_wrapped_key->subtype],
                                      internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret =
            r_rsip_p75f(&gs_hmac_cmd[RSIP_HMAC_CMD_VERIFY],
                        (const uint32_t *) p_message,
                        InData_MAC,
                        mac_len,
                        r_rsip_byte_to_word_convert((uint32_t) message_length),
                        (uint32_t *) NULL);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_verify (const rsip_wrapped_key_t * p_wrapped_key,
                               const uint8_t            * p_message,
                               uint64_t                   message_length,
                               uint64_t                   total_message_length,
                               const uint8_t            * p_mac,
                               uint32_t                   mac_length,
                               uint32_t                 * internal_state)
{
    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p75s(internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret = r_rsip_hmac_resume_verify(p_wrapped_key,
                                             p_message,
                                             message_length,
                                             total_message_length,
                                             p_mac,
                                             mac_length,
                                             internal_state);
    }

    return rsip_ret;
}
