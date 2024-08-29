/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if RSIP_CFG_AES_128_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_AES_128                  RSIP_PRV_FUNC_NAME_KEY_GENERATE_AES_128
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_AES_128                  RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_AES_128
 #define RSIP_PRV_FUNC_RFC3394_AES_128_KEY_WRAP              RSIP_PRV_FUNC_NAME_RFC3394_AES_128_KEY_WRAP
 #define RSIP_PRV_FUNC_RFC3394_AES_128_KEY_UNWRAP            RSIP_PRV_FUNC_NAME_RFC3394_AES_128_KEY_UNWRAP
 #define RSIP_PRV_FUNC_OTF_CHANNEL_0_AES_128                 RSIP_PRV_FUNC_NAME_OTF_CHANNEL_0_AES_128
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_AES_128                  NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_AES_128                  NULL
 #define RSIP_PRV_FUNC_RFC3394_AES_128_KEY_WRAP              NULL
 #define RSIP_PRV_FUNC_RFC3394_AES_128_KEY_UNWRAP            NULL
 #define RSIP_PRV_FUNC_OTF_CHANNEL_0_AES_128                 NULL
#endif

#if RSIP_CFG_AES_128_ENABLE && RSIP_CFG_AES_ECB_CBC_CTR_ENABLE
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_128           RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_ENC_128
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_128           RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_DEC_128
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_128           RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_128
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_128           RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_128
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_128               RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CTR_128
 #define RSIP_PRV_FUNC_AES_CIPHER_UPDATE_128                 RSIP_PRV_FUNC_NAME_AES_CIPHER_UPDATE_128
 #define RSIP_PRV_FUNC_AES_CIPHER_FINAL_128                  RSIP_PRV_FUNC_NAME_AES_CIPHER_FINAL_128
#else
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_128           NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_128           NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_128           NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_128           NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_128               NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_UPDATE_128                 NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_FINAL_128                  NULL
#endif

#if RSIP_CFG_AES_128_ENABLE && RSIP_CFG_AES_GCM_ENABLE
 #define RSIP_PRV_FUNC_AES_GCM_ENC_INIT_128                  RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_128
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_AAD_128            RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_AAD_128
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_TRANSITION_128     RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_TRANSITION_128
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_128                RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_128
 #define RSIP_PRV_FUNC_AES_GCM_ENC_FINAL_128                 RSIP_PRV_FUNC_NAME_AES_GCM_ENC_FINAL_128
 #define RSIP_PRV_FUNC_AES_GCM_DEC_INIT_128                  RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_128
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_AAD_128            RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_AAD_128
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_TRANSITION_128     RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_TRANSITION_128
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_128                RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_128
 #define RSIP_PRV_FUNC_AES_GCM_DEC_FINAL_128                 RSIP_PRV_FUNC_NAME_AES_GCM_DEC_FINAL_128
#else
 #define RSIP_PRV_FUNC_AES_GCM_ENC_INIT_128                  NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_AAD_128            NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_TRANSITION_128     NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_128                NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_FINAL_128                 NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_INIT_128                  NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_AAD_128            NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_TRANSITION_128     NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_128                NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_FINAL_128                 NULL
#endif

#if RSIP_CFG_AES_128_ENABLE && RSIP_CFG_AES_CCM_ENABLE
 #define RSIP_PRV_FUNC_AES_CCM_ENC_INIT_128                  RSIP_PRV_FUNC_NAME_AES_CCM_ENC_INIT_128
 #define RSIP_PRV_FUNC_AES_CCM_ENC_UPDATE_128                RSIP_PRV_FUNC_NAME_AES_CCM_ENC_UPDATE_128
 #define RSIP_PRV_FUNC_AES_CCM_ENC_FINAL_128                 RSIP_PRV_FUNC_NAME_AES_CCM_ENC_FINAL_128
 #define RSIP_PRV_FUNC_AES_CCM_DEC_INIT_128                  RSIP_PRV_FUNC_NAME_AES_CCM_DEC_INIT_128
 #define RSIP_PRV_FUNC_AES_CCM_DEC_UPDATE_128                RSIP_PRV_FUNC_NAME_AES_CCM_DEC_UPDATE_128
 #define RSIP_PRV_FUNC_AES_CCM_DEC_FINAL_128                 RSIP_PRV_FUNC_NAME_AES_CCM_DEC_FINAL_128
#else
 #define RSIP_PRV_FUNC_AES_CCM_ENC_INIT_128                  NULL
 #define RSIP_PRV_FUNC_AES_CCM_ENC_UPDATE_128                NULL
 #define RSIP_PRV_FUNC_AES_CCM_ENC_FINAL_128                 NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_INIT_128                  NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_UPDATE_128                NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_FINAL_128                 NULL
#endif

#if RSIP_CFG_AES_128_ENABLE && RSIP_CFG_AES_CMAC_ENABLE
 #define RSIP_PRV_FUNC_AES_CMAC_INIT_128                     RSIP_PRV_FUNC_NAME_AES_CMAC_INIT_128
 #define RSIP_PRV_FUNC_AES_CMAC_UPDATE_128                   RSIP_PRV_FUNC_NAME_AES_CMAC_UPDATE_128
 #define RSIP_PRV_FUNC_AES_CMAC_GENERATE_FINAL_128           RSIP_PRV_FUNC_NAME_AES_CMAC_GENERATE_FINAL_128
 #define RSIP_PRV_FUNC_AES_CMAC_VERIFY_FINAL_128             RSIP_PRV_FUNC_NAME_AES_CMAC_VERIFY_FINAL_128
#else
 #define RSIP_PRV_FUNC_AES_CMAC_INIT_128                     NULL
 #define RSIP_PRV_FUNC_AES_CMAC_UPDATE_128                   NULL
 #define RSIP_PRV_FUNC_AES_CMAC_GENERATE_FINAL_128           NULL
 #define RSIP_PRV_FUNC_AES_CMAC_VERIFY_FINAL_128             NULL
#endif

#if RSIP_CFG_AES_256_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_AES_256                  RSIP_PRV_FUNC_NAME_KEY_GENERATE_AES_256
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_AES_256                  RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_AES_256
 #define RSIP_PRV_FUNC_RFC3394_AES_256_KEY_WRAP              RSIP_PRV_FUNC_NAME_RFC3394_AES_256_KEY_WRAP
 #define RSIP_PRV_FUNC_RFC3394_AES_256_KEY_UNWRAP            RSIP_PRV_FUNC_NAME_RFC3394_AES_256_KEY_UNWRAP
 #define RSIP_PRV_FUNC_OTF_CHANNEL_0_AES_256                 RSIP_PRV_FUNC_NAME_OTF_CHANNEL_0_AES_256
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_AES_256                  NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_AES_256                  NULL
 #define RSIP_PRV_FUNC_RFC3394_AES_256_KEY_WRAP              NULL
 #define RSIP_PRV_FUNC_RFC3394_AES_256_KEY_UNWRAP            NULL
 #define RSIP_PRV_FUNC_OTF_CHANNEL_0_AES_256                 NULL
#endif

#if RSIP_CFG_AES_256_ENABLE && RSIP_CFG_AES_ECB_CBC_CTR_ENABLE
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_256           RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_ENC_256
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_256           RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_DEC_256
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_256           RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_256
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_256           RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_256
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_256               RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CTR_256
 #define RSIP_PRV_FUNC_AES_CIPHER_UPDATE_256                 RSIP_PRV_FUNC_NAME_AES_CIPHER_UPDATE_256
 #define RSIP_PRV_FUNC_AES_CIPHER_FINAL_256                  RSIP_PRV_FUNC_NAME_AES_CIPHER_FINAL_256
#else
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_ENC_256           NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_ECB_DEC_256           NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_ENC_256           NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CBC_DEC_256           NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_INIT_CTR_256               NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_UPDATE_256                 NULL
 #define RSIP_PRV_FUNC_AES_CIPHER_FINAL_256                  NULL
#endif

#if RSIP_CFG_AES_256_ENABLE && RSIP_CFG_AES_GCM_ENABLE
 #define RSIP_PRV_FUNC_AES_GCM_ENC_INIT_256                  RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_256
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_AAD_256            RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_AAD_256
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_TRANSITION_256     RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_TRANSITION_256
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_256                RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_256
 #define RSIP_PRV_FUNC_AES_GCM_ENC_FINAL_256                 RSIP_PRV_FUNC_NAME_AES_GCM_ENC_FINAL_256
 #define RSIP_PRV_FUNC_AES_GCM_DEC_INIT_256                  RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_256
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_AAD_256            RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_AAD_256
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_TRANSITION_256     RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_TRANSITION_256
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_256                RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_256
 #define RSIP_PRV_FUNC_AES_GCM_DEC_FINAL_256                 RSIP_PRV_FUNC_NAME_AES_GCM_DEC_FINAL_256
#else
 #define RSIP_PRV_FUNC_AES_GCM_ENC_INIT_256                  NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_AAD_256            NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_TRANSITION_256     NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_UPDATE_256                NULL
 #define RSIP_PRV_FUNC_AES_GCM_ENC_FINAL_256                 NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_INIT_256                  NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_AAD_256            NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_TRANSITION_256     NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_UPDATE_256                NULL
 #define RSIP_PRV_FUNC_AES_GCM_DEC_FINAL_256                 NULL
#endif

#if RSIP_CFG_AES_256_ENABLE && RSIP_CFG_AES_CCM_ENABLE
 #define RSIP_PRV_FUNC_AES_CCM_ENC_INIT_256                  RSIP_PRV_FUNC_NAME_AES_CCM_ENC_INIT_256
 #define RSIP_PRV_FUNC_AES_CCM_ENC_UPDATE_256                RSIP_PRV_FUNC_NAME_AES_CCM_ENC_UPDATE_256
 #define RSIP_PRV_FUNC_AES_CCM_ENC_FINAL_256                 RSIP_PRV_FUNC_NAME_AES_CCM_ENC_FINAL_256
 #define RSIP_PRV_FUNC_AES_CCM_DEC_INIT_256                  RSIP_PRV_FUNC_NAME_AES_CCM_DEC_INIT_256
 #define RSIP_PRV_FUNC_AES_CCM_DEC_UPDATE_256                RSIP_PRV_FUNC_NAME_AES_CCM_DEC_UPDATE_256
 #define RSIP_PRV_FUNC_AES_CCM_DEC_FINAL_256                 RSIP_PRV_FUNC_NAME_AES_CCM_DEC_FINAL_256
#else
 #define RSIP_PRV_FUNC_AES_CCM_ENC_INIT_256                  NULL
 #define RSIP_PRV_FUNC_AES_CCM_ENC_UPDATE_256                NULL
 #define RSIP_PRV_FUNC_AES_CCM_ENC_FINAL_256                 NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_INIT_256                  NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_UPDATE_256                NULL
 #define RSIP_PRV_FUNC_AES_CCM_DEC_FINAL_256                 NULL
#endif

#if RSIP_CFG_AES_256_ENABLE && RSIP_CFG_AES_CMAC_ENABLE
 #define RSIP_PRV_FUNC_AES_CMAC_INIT_256                     RSIP_PRV_FUNC_NAME_AES_CMAC_INIT_256
 #define RSIP_PRV_FUNC_AES_CMAC_UPDATE_256                   RSIP_PRV_FUNC_NAME_AES_CMAC_UPDATE_256
 #define RSIP_PRV_FUNC_AES_CMAC_GENERATE_FINAL_256           RSIP_PRV_FUNC_NAME_AES_CMAC_GENERATE_FINAL_256
 #define RSIP_PRV_FUNC_AES_CMAC_VERIFY_FINAL_256             RSIP_PRV_FUNC_NAME_AES_CMAC_VERIFY_FINAL_256
#else
 #define RSIP_PRV_FUNC_AES_CMAC_INIT_256                     NULL
 #define RSIP_PRV_FUNC_AES_CMAC_UPDATE_256                   NULL
 #define RSIP_PRV_FUNC_AES_CMAC_GENERATE_FINAL_256           NULL
 #define RSIP_PRV_FUNC_AES_CMAC_VERIFY_FINAL_256             NULL
#endif

#if RSIP_CFG_AES_GCM_ENABLE
 #define RSIP_PRV_FUNC_GHASH_COMPUTE                         RSIP_PRV_FUNC_NAME_GHASH_COMPUTE
#else
 #define RSIP_PRV_FUNC_GHASH_COMPUTE                         NULL
#endif

#if RSIP_CFG_XTS_AES_128_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_128              RSIP_PRV_FUNC_NAME_KEY_GENERATE_XTS_AES_128
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_XTS_AES_128              RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_XTS_AES_128
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_128              NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_XTS_AES_128              NULL
#endif

#if RSIP_CFG_XTS_AES_128_ENABLE && RSIP_CFG_AES_XTS_ENABLE
 #define RSIP_PRV_FUNC_XTS_AES_ENC_INIT_128                  RSIP_PRV_FUNC_NAME_XTS_AES_ENC_INIT_128
 #define RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_128                RSIP_PRV_FUNC_NAME_XTS_AES_ENC_UPDATE_128
 #define RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_128                 RSIP_PRV_FUNC_NAME_XTS_AES_ENC_FINAL_128
 #define RSIP_PRV_FUNC_XTS_AES_DEC_INIT_128                  RSIP_PRV_FUNC_NAME_XTS_AES_DEC_INIT_128
 #define RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_128                RSIP_PRV_FUNC_NAME_XTS_AES_DEC_UPDATE_128
 #define RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_128                 RSIP_PRV_FUNC_NAME_XTS_AES_DEC_FINAL_128
#else
 #define RSIP_PRV_FUNC_XTS_AES_ENC_INIT_128                  NULL
 #define RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_128                NULL
 #define RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_128                 NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_INIT_128                  NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_128                NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_128                 NULL
#endif

#if RSIP_CFG_XTS_AES_256_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_256              RSIP_PRV_FUNC_NAME_KEY_GENERATE_XTS_AES_256
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_XTS_AES_256              RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_XTS_AES_256
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_256              NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_XTS_AES_256              NULL
#endif

#if RSIP_CFG_XTS_AES_256_ENABLE && RSIP_CFG_AES_XTS_ENABLE
 #define RSIP_PRV_FUNC_XTS_AES_ENC_INIT_256                  RSIP_PRV_FUNC_NAME_XTS_AES_ENC_INIT_256
 #define RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_256                RSIP_PRV_FUNC_NAME_XTS_AES_ENC_UPDATE_256
 #define RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_256                 RSIP_PRV_FUNC_NAME_XTS_AES_ENC_FINAL_256
 #define RSIP_PRV_FUNC_XTS_AES_DEC_INIT_256                  RSIP_PRV_FUNC_NAME_XTS_AES_DEC_INIT_256
 #define RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_256                RSIP_PRV_FUNC_NAME_XTS_AES_DEC_UPDATE_256
 #define RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_256                 RSIP_PRV_FUNC_NAME_XTS_AES_DEC_FINAL_256
#else
 #define RSIP_PRV_FUNC_XTS_AES_ENC_INIT_256                  NULL
 #define RSIP_PRV_FUNC_XTS_AES_ENC_UPDATE_256                NULL
 #define RSIP_PRV_FUNC_XTS_AES_ENC_FINAL_256                 NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_INIT_256                  NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_UPDATE_256                NULL
 #define RSIP_PRV_FUNC_XTS_AES_DEC_FINAL_256                 NULL
#endif


#if RSIP_CFG_ECC_SECP256R1_ENABLE
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP256R1       RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP256R1
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP256R1_PUBLIC     RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256R1_PUBLIC
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP256R1_PRIVATE    RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256R1_PRIVATE

 #define RSIP_PRV_FUNC_ECDSA_SIGN_SECP256R1                  RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP256R1
 #define RSIP_PRV_FUNC_ECDSA_VERIFY_SECP256R1                RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP256R1
#else
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP256R1       NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP256R1_PUBLIC     NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP256R1_PRIVATE    NULL

 #define RSIP_PRV_FUNC_ECDSA_SIGN_SECP256R1                  NULL
 #define RSIP_PRV_FUNC_ECDSA_VERIFY_SECP256R1                NULL
#endif

#if RSIP_CFG_ECC_SECP384R1_ENABLE
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP384R1       RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP384R1
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP384R1_PUBLIC     RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP384R1_PUBLIC
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP384R1_PRIVATE    RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP384R1_PRIVATE

 #define RSIP_PRV_FUNC_ECDSA_SIGN_SECP384R1                  RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP384R1
 #define RSIP_PRV_FUNC_ECDSA_VERIFY_SECP384R1                RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP384R1
#else
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP384R1       NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP384R1_PUBLIC     NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP384R1_PRIVATE    NULL

 #define RSIP_PRV_FUNC_ECDSA_SIGN_SECP384R1                  NULL
 #define RSIP_PRV_FUNC_ECDSA_VERIFY_SECP384R1                NULL
#endif

#if RSIP_CFG_ECC_SECP521R1_ENABLE
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP521R1       RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP521R1
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP521R1_PUBLIC     RSIP_PRV_FUNC_NAME_KEY_WRAP_ECC_SECP521R1_PUBLIC
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP521R1_PRIVATE    RSIP_PRV_FUNC_NAME_KEY_WRAP_ECC_SECP521R1_PRIVATE

 #define RSIP_PRV_FUNC_ECDSA_SIGN_SECP521R1                  RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP521R1
 #define RSIP_PRV_FUNC_ECDSA_VERIFY_SECP521R1                RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP521R1
#else
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP521R1       NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP521R1_PUBLIC     NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP521R1_PRIVATE    NULL

 #define RSIP_PRV_FUNC_ECDSA_SIGN_SECP521R1                  NULL
 #define RSIP_PRV_FUNC_ECDSA_VERIFY_SECP521R1                NULL
#endif

#if RSIP_CFG_RSA_2048_ENABLE
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_2048                  RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_RSA_2048
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_2048_PUBLIC                RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_2048_PUBLIC
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_2048_PRIVATE               RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_2048_PRIVATE

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_2048                            RSIP_PRV_FUNC_NAME_RSA_ENCRYPT_2048
 #define RSIP_PRV_FUNC_RSA_DECRYPT_2048                            RSIP_PRV_FUNC_NAME_RSA_DECRYPT_2048
#else
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_2048                  NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_2048_PUBLIC                NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_2048_PRIVATE               NULL

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_2048                            NULL
 #define RSIP_PRV_FUNC_RSA_DECRYPT_2048                            NULL
#endif

#if RSIP_CFG_RSA_3072_ENABLE
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_3072                  RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_RSA_3072
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_3072_PUBLIC                RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_3072_PUBLIC
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_3072_PRIVATE               RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_3072_PRIVATE

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_3072                            RSIP_PRV_FUNC_NAME_RSA_ENCRYPT_3072
 #define RSIP_PRV_FUNC_RSA_DECRYPT_3072                            RSIP_PRV_FUNC_NAME_RSA_DECRYPT_3072
#else
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_3072                  NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_3072_PUBLIC                NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_3072_PRIVATE               NULL

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_3072                            NULL
 #define RSIP_PRV_FUNC_RSA_DECRYPT_3072                            NULL
#endif

#if RSIP_CFG_RSA_4096_ENABLE
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_4096                  RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_RSA_4096
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_4096_PUBLIC                RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_4096_PUBLIC
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_4096_PRIVATE               RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_4096_PRIVATE

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_4096                            RSIP_PRV_FUNC_NAME_RSA_ENCRYPT_4096
 #define RSIP_PRV_FUNC_RSA_DECRYPT_4096                            RSIP_PRV_FUNC_NAME_RSA_DECRYPT_4096
#else
 #define RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_4096                  NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_4096_PUBLIC                NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_4096_PRIVATE               NULL

 #define RSIP_PRV_FUNC_RSA_ENCRYPT_4096                            NULL
 #define RSIP_PRV_FUNC_RSA_DECRYPT_4096                            NULL
#endif

#if RSIP_CFG_HMAC_SHA1_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA1                      RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA1
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA1                      RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA1
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA1                      NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA1                      NULL
#endif

#if RSIP_CFG_HMAC_SHA224_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA224                    RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA224
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA224                    RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA224
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA224                    NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA224                    NULL
#endif

#if RSIP_CFG_HMAC_SHA256_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA256                    RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA256
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA256                    RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA256
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA256                    NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA256                    NULL
#endif

#if RSIP_CFG_HMAC_SHA384_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA384                    RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA384
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA384                    RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA384
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA384                    NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA384                    NULL
#endif

#if RSIP_CFG_HMAC_SHA512_ENABLE
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA512                    RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA512
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA512                    RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA512
#else
 #define RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA512                    NULL
 #define RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA512                    NULL
#endif

#define RSIP_PRV_FUNC_RANDOM_NUMBER_GENERATE                       RSIP_PRV_FUNC_NAME_RANDOM_NUMBER_GENERATE

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const bool g_sha_enabled[RSIP_HASH_TYPE_NUM] =
{
    [RSIP_HASH_TYPE_SHA256]     = RSIP_CFG_SHA256_ENABLE,
    [RSIP_HASH_TYPE_SHA384]     = RSIP_CFG_SHA384_ENABLE,
    [RSIP_HASH_TYPE_SHA512]     = RSIP_CFG_SHA512_ENABLE,
};

const bool g_hmac_enabled[RSIP_KEY_HMAC_NUM] =
{
    [RSIP_KEY_HMAC_SHA256] = RSIP_CFG_HMAC_SHA256_ENABLE,
    [RSIP_KEY_HMAC_SHA384] = RSIP_CFG_HMAC_SHA384_ENABLE,
    [RSIP_KEY_HMAC_SHA512] = RSIP_CFG_HMAC_SHA512_ENABLE,
};

const rsip_func_key_generate_t gp_func_key_generate_aes[RSIP_KEY_AES_NUM] =
{
    [RSIP_KEY_AES_128] = RSIP_PRV_FUNC_KEY_GENERATE_AES_128,
    [RSIP_KEY_AES_256] = RSIP_PRV_FUNC_KEY_GENERATE_AES_256
};

const rsip_func_key_generate_t gp_func_key_generate_xts_aes[RSIP_KEY_AES_NUM] =
{
    [RSIP_KEY_AES_128] = RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_128,
    [RSIP_KEY_AES_256] = RSIP_PRV_FUNC_KEY_GENERATE_XTS_AES_256
};

const rsip_func_key_generate_t gp_func_key_generate_chacha[RSIP_KEY_CHACHA_NUM] =
{
    NULL
};

const rsip_func_key_generate_t gp_func_key_generate_hmac[RSIP_KEY_HMAC_NUM] =
{
    [RSIP_KEY_HMAC_SHA1]   = RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA1,
    [RSIP_KEY_HMAC_SHA224] = RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA224,
    [RSIP_KEY_HMAC_SHA256] = RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA256,
    [RSIP_KEY_HMAC_SHA384] = RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA384,
    [RSIP_KEY_HMAC_SHA512] = RSIP_PRV_FUNC_KEY_GENERATE_HMAC_SHA512
};

const rsip_func_key_pair_generate_t gp_func_key_pair_generate_ecc[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP256R1,
    [RSIP_KEY_ECC_SECP384R1]       = RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP384R1,
    [RSIP_KEY_ECC_SECP521R1]       = RSIP_PRV_FUNC_KEY_PAIR_GENERATE_ECC_SECP521R1,
};

const rsip_func_key_pair_generate_t gp_func_key_pair_generate_rsa[RSIP_KEY_RSA_NUM] =
{
    [RSIP_KEY_RSA_1024] = NULL,
    [RSIP_KEY_RSA_2048] = RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_2048,
    [RSIP_KEY_RSA_3072] = RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_3072,
    [RSIP_KEY_RSA_4096] = RSIP_PRV_FUNC_KEY_PAIR_GENERATE_RSA_4096
};

const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_aes[RSIP_KEY_AES_NUM] =
{
    [RSIP_KEY_AES_128] = RSIP_PRV_FUNC_ENC_KEY_WRAP_AES_128,
    [RSIP_KEY_AES_256] = RSIP_PRV_FUNC_ENC_KEY_WRAP_AES_256
};

const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_xts_aes[RSIP_KEY_AES_NUM] =
{
    [RSIP_KEY_AES_128] = RSIP_PRV_FUNC_ENC_KEY_WRAP_XTS_AES_128,
    [RSIP_KEY_AES_256] = RSIP_PRV_FUNC_ENC_KEY_WRAP_XTS_AES_256
};

const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_chacha[RSIP_KEY_CHACHA_NUM] =
{
    NULL
};

const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_ecc_pub[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP256R1_PUBLIC,
    [RSIP_KEY_ECC_SECP384R1]       = RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP384R1_PUBLIC,
    [RSIP_KEY_ECC_SECP521R1]       = RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP521R1_PUBLIC
};

const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_ecc_priv[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP256R1_PRIVATE,
    [RSIP_KEY_ECC_SECP384R1]       = RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP384R1_PRIVATE,
    [RSIP_KEY_ECC_SECP521R1]       = RSIP_PRV_FUNC_ENC_KEY_WRAP_ECC_SECP521R1_PRIVATE
};

const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_rsa_pub[RSIP_KEY_RSA_NUM] =
{
    [RSIP_KEY_RSA_2048] = RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_2048_PUBLIC,
    [RSIP_KEY_RSA_3072] = RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_3072_PUBLIC,
    [RSIP_KEY_RSA_4096] = RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_4096_PUBLIC
};

const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_rsa_priv[RSIP_KEY_RSA_NUM] =
{
    [RSIP_KEY_RSA_2048] = RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_2048_PRIVATE,
    [RSIP_KEY_RSA_3072] = RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_3072_PRIVATE,
    [RSIP_KEY_RSA_4096] = RSIP_PRV_FUNC_ENC_KEY_WRAP_RSA_4096_PRIVATE
};

const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_hmac[RSIP_KEY_HMAC_NUM] =
{
    [RSIP_KEY_HMAC_SHA256] = RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA256,
    [RSIP_KEY_HMAC_SHA384] = RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA384,
    [RSIP_KEY_HMAC_SHA512] = RSIP_PRV_FUNC_ENC_KEY_WRAP_HMAC_SHA512
};

const rsip_func_subset_aes_cipher_t gp_func_aes_cipher[RSIP_KEY_AES_NUM] =
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
};

const rsip_func_subset_aes_xts_t gp_func_aes_xts_enc[RSIP_KEY_AES_NUM] =
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
};

const rsip_func_subset_aes_xts_t gp_func_aes_xts_dec[RSIP_KEY_AES_NUM] =
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
};

const rsip_func_subset_aes_gcm_t gp_func_aes_gcm_enc[RSIP_KEY_AES_NUM] =
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
};

const rsip_func_subset_aes_gcm_t gp_func_aes_gcm_dec[RSIP_KEY_AES_NUM] =
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
};

const rsip_func_subset_aes_ccm_t gp_func_aes_ccm_enc[RSIP_KEY_AES_NUM] =
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
};

const rsip_func_subset_aes_ccm_t gp_func_aes_ccm_dec[RSIP_KEY_AES_NUM] =
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
};

const rsip_func_subset_aes_cmac_t gp_func_aes_cmac[RSIP_KEY_AES_NUM] =
{
    [RSIP_KEY_AES_128] =
    {
    .p_init          = RSIP_PRV_FUNC_AES_CMAC_INIT_128,
    .p_update        = RSIP_PRV_FUNC_AES_CMAC_UPDATE_128,
    .p_generateFinal = RSIP_PRV_FUNC_AES_CMAC_GENERATE_FINAL_128,
    .p_verifyFinal   = RSIP_PRV_FUNC_AES_CMAC_VERIFY_FINAL_128
     },
     [RSIP_KEY_AES_256] =
     {
     .p_init          = RSIP_PRV_FUNC_AES_CMAC_INIT_256,
     .p_update        = RSIP_PRV_FUNC_AES_CMAC_UPDATE_256,
     .p_generateFinal = RSIP_PRV_FUNC_AES_CMAC_GENERATE_FINAL_256,
     .p_verifyFinal   = RSIP_PRV_FUNC_AES_CMAC_VERIFY_FINAL_256
    }
};

const rsip_func_ecdsa_sign_t gp_func_ecdsa_sign[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_PRV_FUNC_ECDSA_SIGN_SECP256R1,
    [RSIP_KEY_ECC_SECP384R1]       = RSIP_PRV_FUNC_ECDSA_SIGN_SECP384R1,
    [RSIP_KEY_ECC_SECP521R1]       = RSIP_PRV_FUNC_ECDSA_SIGN_SECP521R1,
};

const rsip_func_ecdsa_verify_t gp_func_ecdsa_verify[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_PRV_FUNC_ECDSA_VERIFY_SECP256R1,
    [RSIP_KEY_ECC_SECP384R1]       = RSIP_PRV_FUNC_ECDSA_VERIFY_SECP384R1,
    [RSIP_KEY_ECC_SECP521R1]       = RSIP_PRV_FUNC_ECDSA_VERIFY_SECP521R1,
};

const rsip_func_rsa_t gp_func_rsa_public[RSIP_KEY_RSA_NUM] =
{
    [RSIP_KEY_RSA_2048] = RSIP_PRV_FUNC_RSA_ENCRYPT_2048,
    [RSIP_KEY_RSA_3072] = RSIP_PRV_FUNC_RSA_ENCRYPT_3072,
    [RSIP_KEY_RSA_4096] = RSIP_PRV_FUNC_RSA_ENCRYPT_4096
};

const rsip_func_rsa_t gp_func_rsa_private[RSIP_KEY_RSA_NUM] =
{
    [RSIP_KEY_RSA_2048] = RSIP_PRV_FUNC_RSA_DECRYPT_2048,
    [RSIP_KEY_RSA_3072] = RSIP_PRV_FUNC_RSA_DECRYPT_3072,
    [RSIP_KEY_RSA_4096] = RSIP_PRV_FUNC_RSA_DECRYPT_4096
};

const rsip_func_rfc3394_key_wrap_t gp_func_rfc3394_key_wrap[RSIP_KEY_AES_NUM] =
{
    [RSIP_KEY_AES_128] = RSIP_PRV_FUNC_RFC3394_AES_128_KEY_WRAP,
    [RSIP_KEY_AES_192] = NULL,
    [RSIP_KEY_AES_256] = RSIP_PRV_FUNC_RFC3394_AES_256_KEY_WRAP
};

const rsip_func_rfc3394_key_unwrap_t gp_func_rfc3394_key_unwrap[RSIP_KEY_AES_NUM] =
{
    [RSIP_KEY_AES_128] = RSIP_PRV_FUNC_RFC3394_AES_128_KEY_UNWRAP,
    [RSIP_KEY_AES_192] = NULL,
    [RSIP_KEY_AES_256] = RSIP_PRV_FUNC_RFC3394_AES_256_KEY_UNWRAP
};


const rsip_func_otf_t gp_func_otf[RSIP_OTF_CHANNEL_NUM][RSIP_KEY_AES_NUM] =
{
    [RSIP_OTF_CHANNEL_0] =
    {
        [RSIP_KEY_AES_128] = RSIP_PRV_FUNC_OTF_CHANNEL_0_AES_128,
        [RSIP_KEY_AES_192] = NULL,
        [RSIP_KEY_AES_256] = RSIP_PRV_FUNC_OTF_CHANNEL_0_AES_256
    },
    [RSIP_OTF_CHANNEL_1] =
    {
        [RSIP_KEY_AES_128] = NULL,
        [RSIP_KEY_AES_192] = NULL,
        [RSIP_KEY_AES_256] = NULL
    }
};

const rsip_func_rng_t   gp_func_rng           = RSIP_PRV_FUNC_RANDOM_NUMBER_GENERATE;
const rsip_func_ghash_t gp_func_ghash_compute = RSIP_PRV_FUNC_GHASH_COMPUTE;

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
