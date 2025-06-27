/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_private.h"
#include "r_rsip_primitive.h"
#include "r_rsip_wrapper.h"
#include "r_rsip_reg.h"
#include "r_rsip_addr.h"
#include "r_rsip_util.h"
#include "r_rsip_public.h"
#include "r_rsip_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* For AES-ECB/CBC/CTR */
#define RSIP_PRV_CMD_AES_CIPHER_ECB_ENCRYPT                 (0U)
#define RSIP_PRV_CMD_AES_CIPHER_ECB_DECRYPT                 (1U)
#define RSIP_PRV_CMD_AES_CIPHER_CBC_ENCRYPT                 (2U)
#define RSIP_PRV_CMD_AES_CIPHER_CBC_DECRYPT                 (3U)
#define RSIP_PRV_CMD_AES_CIPHER_CTR_CRYPT                   (4U)

/* For AES-CCM/GCMC */
#define RSIP_PRV_KEY_TYPE_AES_CCM_GCM_GENERAL_KEY           (0U)
#define RSIP_PRV_KEY_TYPE_AES_CCM_GCM_TLS_KEY               (1U)
#define RSIP_PRV_KEY_TYPE_AES_CCM_GCM_DLMS_COSEM_KEY        (2U)
#define RSIP_PRV_KEY_TYPE_AES_CCM_GCM_IAR_KEY               (3U)
#define RSIP_PRV_KEY_TYPE_AES_CCM_GCM_TLS_1_3_KEY           (4U)

/* For AES-CMAC. These commands do not require byte swapping */
#define RSIP_PRV_CMD_AES_CMAC_GENERATE_WITHOUT_REMAINDER    (0U)
#define RSIP_PRV_CMD_AES_CMAC_GENERATE_WITH_REMAINDER       (1U)
#define RSIP_PRV_CMD_AES_CMAC_VERIFY_WITHOUT_REMAINDER      (2U)
#define RSIP_PRV_CMD_AES_CMAC_VERIFY_WITH_REMAINDER         (3U)

/* For RSA */

/*
 * Maximum retry count of RSA key generation derived from FIPS186-4 B.3.3. 4.7 and 5.8 (1024, 2048, 3072)
 * Maximum retry count of RSA key generation derived from FIPS186-5 A.1.3. 4.7 and 5.8 (4096)
 */
#define RSIP_PRV_MAX_RETRY_COUNT_KEY_GEN_RSA_2048           (2 * (5 * 2048 / 2))
#define RSIP_PRV_MAX_RETRY_COUNT_KEY_GEN_RSA_3072           (2 * (5 * 3072 / 2))
#define RSIP_PRV_MAX_RETRY_COUNT_KEY_GEN_RSA_4096           (5 * 4096 + 10 * 4096)

/* For RFC3394 Key Wrap */
#define RSIP_PRV_WORD_SIZE_RFC3394_WRAPPED_KEY_AES_128      (6U)
#define RSIP_PRV_WORD_SIZE_RFC3394_WRAPPED_KEY_AES_256      (10U)

/* For ECC */
#define RSIP_PRV_WORD_SIZE_SIGNATURE_ECC_521                (40U)
#define RSIP_PRV_BYTE_SIZE_SIGNATURE_PAD_ECC_521            (14U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_cmd
{
    CMD_AES_KEY_WRAP_AES128 = 0,
    CMD_AES_KEY_WRAP_AES256 = 1,

    CMD_AES_MODE_ECB_ENCRYPT = 0,
    CMD_AES_MODE_ECB_DECRYPT = 1,
    CMD_AES_MODE_CBC_ENCRYPT = 2,
    CMD_AES_MODE_CBC_DECRYPT = 3,
    CMD_AES_MODE_CTR_CRYPT   = 4,

    CMD_AES_IV_TYPE_PLAIN   = 0,
    CMD_AES_IV_TYPE_WRAPPED = 1,

    CMD_AES_CMAC_GENERATE_WITHOUT_REMAINDER = 0,
    CMD_AES_CMAC_GENERATE_WITH_REMAINDER    = 1,
    CMD_AES_CMAC_VERIFY_WITHOUT_REMAINDER   = 2,
    CMD_AES_CMAC_VERIFY_WITH_REMAINDER      = 3,

    CMD_ECC_TYPE_NIST      = 0,
    CMD_ECC_TYPE_BRAINPOOL = 1,
    CMD_ECC_TYPE_KOBLITZ   = 2,

    CMD_ECC_KEY_LENGTH_256 = 0,

    CMD_ECDH_PUBKEY_TYPE_PLAIN   = 0,
    CMD_ECDH_PUBKEY_TYPE_WRAPPED = 1,

    CMD_PKI_KEY_TYPE_RSA_2048      = 0,
    CMD_PKI_KEY_TYPE_ECC_SECP256R1 = 3,
    CMD_PKI_KEY_TYPE_ECC_SECP384R1 = 4,
    CMD_PKI_KEY_TYPE_ECC_SECP521R1 = 5,

    CMD_KDF_HASH_TYPE_SHA256 = 0,
    CMD_KDF_HASH_TYPE_SHA384 = 1,
    CMD_KDF_HASH_TYPE_SHA512 = 2,

    CMD_KDF_OUTDATA_TYPE_AES128      = 0,
    CMD_KDF_OUTDATA_TYPE_AES256      = 1,
    CMD_KDF_OUTDATA_TYPE_IV_AES      = 2,
    CMD_KDF_OUTDATA_TYPE_IV_TLS12    = 3,
    CMD_KDF_OUTDATA_TYPE_HMAC_SHA1   = 5,
    CMD_KDF_OUTDATA_TYPE_HMAC_SHA256 = 6,
    CMD_KDF_OUTDATA_TYPE_HMAC_SHA384 = 7,
    CMD_KDF_OUTDATA_TYPE_HMAC_SHA512 = 8,
} cmd_t;

typedef enum e_rsip_oem_cmd
{
    RSIP_OEM_CMD_INVALID = 0,
    RSIP_OEM_CMD_AES128  = 5,
    RSIP_OEM_CMD_AES192,
    RSIP_OEM_CMD_AES256,
    RSIP_OEM_CMD_AES128_XTS,
    RSIP_OEM_CMD_AES256_XTS,
    RSIP_OEM_CMD_RSA1024_PUBLIC,
    RSIP_OEM_CMD_RSA1024_PRIVATE,
    RSIP_OEM_CMD_RSA2048_PUBLIC,
    RSIP_OEM_CMD_RSA2048_PRIVATE,
    RSIP_OEM_CMD_RSA3072_PUBLIC,
    RSIP_OEM_CMD_RSA3072_PRIVATE,
    RSIP_OEM_CMD_RSA4096_PUBLIC,
    RSIP_OEM_CMD_RSA4096_PRIVATE,
    RSIP_OEM_CMD_ECC_P192_PUBLIC,
    RSIP_OEM_CMD_ECC_P192_PRIVATE,
    RSIP_OEM_CMD_ECC_P224_PUBLIC,
    RSIP_OEM_CMD_ECC_P224_PRIVATE,
    RSIP_OEM_CMD_ECC_SECP256R1_PUBLIC,
    RSIP_OEM_CMD_ECC_SECP256R1_PRIVATE,
    RSIP_OEM_CMD_ECC_SECP384R1_PUBLIC,
    RSIP_OEM_CMD_ECC_SECP384R1_PRIVATE,
    RSIP_OEM_CMD_HMAC_SHA224,
    RSIP_OEM_CMD_HMAC_SHA256,
    RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PUBLIC,
    RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PRIVATE,
    RSIP_OEM_CMD_ECC_BRAINPOOLP384R1_PUBLIC,
    RSIP_OEM_CMD_ECC_BRAINPOOLP384R1_PRIVATE,
    RSIP_OEM_CMD_ECC_BRAINPOOLP512R1_PUBLIC,
    RSIP_OEM_CMD_ECC_BRAINPOOLP512R1_PRIVATE,
    RSIP_OEM_CMD_ECC_SECP256K1_PUBLIC,
    RSIP_OEM_CMD_ECC_SECP256K1_PRIVATE,
    RSIP_OEM_CMD_ECC_SECP521R1_PUBLIC,
    RSIP_OEM_CMD_ECC_SECP521R1_PRIVATE,
    RSIP_OEM_CMD_ECC_EDWARDS25519_PUBLIC,
    RSIP_OEM_CMD_ECC_EDWARDS25519_PRIVATE,
    RSIP_OEM_CMD_HMAC_SHA384,
    RSIP_OEM_CMD_HMAC_SHA512,
    RSIP_OEM_CMD_HMAC_SHA512_224,
    RSIP_OEM_CMD_HMAC_SHA512_256,
    RSIP_OEM_CMD_RAS_2048_PUBLIC_FOR_TLS = 0xfe,
    RSIP_OEM_CMD_NUM
} rsip_oem_cmd_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static const uint32_t gs_cmd[7] =
{
    BSWAP_32BIG_C(0U), BSWAP_32BIG_C(1U), BSWAP_32BIG_C(2U), BSWAP_32BIG_C(3U), BSWAP_32BIG_C(4U), BSWAP_32BIG_C(5U),
    BSWAP_32BIG_C(6U)
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/
rsip_ret_t r_rsip_wrapper_pf0_secp256r1 (const uint32_t InData_KeyIndex[],
                                         const uint32_t InData_MsgDgst[],
                                         uint32_t       OutData_Signature[])
{
    const uint32_t * in_data_domain_param = DomainParam_NIST_P256;
    uint32_t         cv_type              = bswap_32big(RSIP_ECC_CURVE_TYPE_NIST);

    return r_rsip_pf0(&cv_type, InData_KeyIndex, InData_MsgDgst, in_data_domain_param, OutData_Signature);
}

rsip_ret_t r_rsip_wrapper_pf1_secp256r1 (const uint32_t InData_KeyIndex[],
                                         const uint32_t InData_MsgDgst[],
                                         const uint32_t InData_Signature[])
{
    const uint32_t * in_data_domain_param = DomainParam_NIST_P256;
    uint32_t         cv_type              = bswap_32big(RSIP_ECC_CURVE_TYPE_NIST);

    return r_rsip_pf1(&cv_type, InData_KeyIndex, InData_MsgDgst, InData_Signature, in_data_domain_param);
}

rsip_ret_t r_rsip_wrapper_pf4_secp256r1 (uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    uint32_t         in_data_curve_type = bswap_32big(RSIP_ECC_CURVE_TYPE_NIST);
    uint32_t const * p_domain_param     = DomainParam_NIST_P256;

    return r_rsip_pf4(&in_data_curve_type, p_domain_param, OutData_PubKeyIndex, OutData_PrivKeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_aes128 (const uint32_t InData_IV[],
                                      const uint32_t InData_InstData[],
                                      uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD[1] = {bswap_32big(RSIP_OEM_CMD_AES128)};
    uint32_t LC[1]  = {0};
    LC[0]          = R_PSCU->DLMMON;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_AES128_INST_DATA_WORD;

    return r_rsip_p6f(LC, CMD, InData_IV, InData_InstData, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_aes256 (const uint32_t InData_IV[],
                                      const uint32_t InData_InstData[],
                                      uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD[1] = {bswap_32big(RSIP_OEM_CMD_AES256)};
    uint32_t LC[1]  = {0};
    LC[0]          = R_PSCU->DLMMON;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_AES256_INST_DATA_WORD;

    return r_rsip_p6f(LC, CMD, InData_IV, InData_InstData, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_secp256r1_pub (const uint32_t InData_IV[],
                                             const uint32_t InData_InstData[],
                                             uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD[1] = {bswap_32big(RSIP_OEM_CMD_ECC_SECP256R1_PUBLIC)};
    uint32_t LC[1]  = {0};
    LC[0]          = R_PSCU->DLMMON;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PUBLIC_KEY_INST_DATA_WORD;

    return r_rsip_p6f(LC, CMD, InData_IV, InData_InstData, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_secp256r1_priv (const uint32_t InData_IV[],
                                              const uint32_t InData_InstData[],
                                              uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD[1] = {bswap_32big(RSIP_OEM_CMD_ECC_SECP256R1_PRIVATE)};
    uint32_t LC[1]  = {0};
    LC[0]          = R_PSCU->DLMMON;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PRIVATE_KEY_INST_DATA_WORD;

    return r_rsip_p6f(LC, CMD, InData_IV, InData_InstData, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_hmacsha224 (const uint32_t InData_IV[],
                                          const uint32_t InData_InstData[],
                                          uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD[1] = {bswap_32big(RSIP_OEM_CMD_HMAC_SHA224)};
    uint32_t LC[1]  = {0};
    LC[0]          = R_PSCU->DLMMON;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_HMAC_SHA224_KEY_INST_DATA_WORD;

    return r_rsip_p6f(LC, CMD, InData_IV, InData_InstData, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_hmacsha256 (const uint32_t InData_IV[],
                                          const uint32_t InData_InstData[],
                                          uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD[1] = {bswap_32big(RSIP_OEM_CMD_HMAC_SHA256)};
    uint32_t LC[1]  = {0};
    LC[0]          = R_PSCU->DLMMON;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_HMAC_SHA256_KEY_INST_DATA_WORD;

    return r_rsip_p6f(LC, CMD, InData_IV, InData_InstData, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p8f_aes128 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_WrappedKeyIndex[],
                                      uint32_t       OutData_Text[],
                                      uint32_t       KEY_INDEX_SIZE,
                                      uint32_t       WRAPPED_KEY_SIZE)
{
    return r_rsip_p8f(&gs_cmd[CMD_AES_KEY_WRAP_AES128],
                      InData_KeyIndex,
                      InData_WrappedKeyType,
                      InData_WrappedKeyIndex,
                      OutData_Text,
                      KEY_INDEX_SIZE,
                      WRAPPED_KEY_SIZE);
}

rsip_ret_t r_rsip_wrapper_p8f_aes256 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_WrappedKeyIndex[],
                                      uint32_t       OutData_Text[],
                                      uint32_t       KEY_INDEX_SIZE,
                                      uint32_t       WRAPPED_KEY_SIZE)
{
    return r_rsip_p8f(&gs_cmd[CMD_AES_KEY_WRAP_AES256],
                      InData_KeyIndex,
                      InData_WrappedKeyType,
                      InData_WrappedKeyIndex,
                      OutData_Text,
                      KEY_INDEX_SIZE,
                      WRAPPED_KEY_SIZE);
}

rsip_ret_t r_rsip_wrapper_p90_aes128 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_Text[],
                                      uint32_t       OutData_KeyIndex[],
                                      uint32_t       WRAPPED_KEY_SIZE,
                                      uint32_t       KEY_INDEX_SIZE)
{
    return r_rsip_p90(&gs_cmd[CMD_AES_KEY_WRAP_AES128],
                      InData_KeyIndex,
                      InData_WrappedKeyType,
                      InData_Text,
                      OutData_KeyIndex,
                      WRAPPED_KEY_SIZE,
                      KEY_INDEX_SIZE);
}

rsip_ret_t r_rsip_wrapper_p90_aes256 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_Text[],
                                      uint32_t       OutData_KeyIndex[],
                                      uint32_t       WRAPPED_KEY_SIZE,
                                      uint32_t       KEY_INDEX_SIZE)
{
    return r_rsip_p90(&gs_cmd[CMD_AES_KEY_WRAP_AES256],
                      InData_KeyIndex,
                      InData_WrappedKeyType,
                      InData_Text,
                      OutData_KeyIndex,
                      WRAPPED_KEY_SIZE,
                      KEY_INDEX_SIZE);
}

rsip_ret_t r_rsip_wrapper_p47i_ecb_enc (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p47i(&gs_cmd[CMD_AES_MODE_ECB_ENCRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_ecb_dec (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p47i(&gs_cmd[CMD_AES_MODE_ECB_DECRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_cbc_enc (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p47i(&gs_cmd[CMD_AES_MODE_CBC_ENCRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_cbc_dec (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p47i(&gs_cmd[CMD_AES_MODE_CBC_DECRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_cbc_enc_wrapped_iv (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p47i(&gs_cmd[CMD_AES_MODE_CBC_ENCRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_cbc_dec_wrapped_iv (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p47i(&gs_cmd[CMD_AES_MODE_CBC_DECRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_ctr (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p47i(&gs_cmd[CMD_AES_MODE_CTR_CRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_ecb_enc (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_ECB_ENCRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_ecb_dec (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_ECB_DECRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_cbc_enc (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_CBC_ENCRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_cbc_dec (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_CBC_DECRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_cbc_enc_wrapped_iv (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_CBC_ENCRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_cbc_dec_wrapped_iv (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_CBC_DECRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_ctr (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_CTR_CRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p29i_plain_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p29i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p29i_wrapped_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p29i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p32i_plain_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p32i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p32i_wrapped_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p32i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p34i_plain_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p34i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p34i_wrapped_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p34i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p36i_plain_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p36i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p36i_wrapped_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p36i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p95i_aes128ccm_encrypt (const uint32_t * InData_KeyIndex,
                                                  const uint32_t * InData_TextLen,
                                                  const uint32_t * InData_IV,
                                                  const uint32_t * InData_Header,
                                                  uint32_t         Header_Len)
{
    (void) InData_TextLen;

    return r_rsip_p95i(InData_KeyIndex, InData_IV, InData_Header, Header_Len);
}

rsip_ret_t r_rsip_wrapper_p95f_aes128ccm_encrypt (const uint32_t * InData_Text,
                                                  const uint32_t * InData_TextLen,
                                                  uint32_t       * OutData_Text,
                                                  uint32_t       * OutData_MAC)
{
    return r_rsip_p95f(InData_Text, InData_TextLen, OutData_Text, OutData_MAC);
}

rsip_ret_t r_rsip_wrapper_p98i_aes128ccm_decrypt (const uint32_t * InData_KeyIndex,
                                                  const uint32_t * InData_TextLen,
                                                  const uint32_t * InData_MACLength,
                                                  const uint32_t * InData_IV,
                                                  const uint32_t * InData_Header,
                                                  uint32_t         Header_Len)
{
    (void) InData_TextLen;
    (void) InData_MACLength;

    return r_rsip_p98i(InData_KeyIndex, InData_IV, InData_Header, Header_Len);
}

rsip_ret_t r_rsip_wrapper_p98f_aes128ccm_decrypt (const uint32_t * InData_Text,
                                                  const uint32_t * InData_TextLen,
                                                  const uint32_t * InData_MAC,
                                                  const uint32_t * InData_MACLength,
                                                  uint32_t       * OutData_Text)
{
    return r_rsip_p98f(InData_Text, InData_TextLen, InData_MAC, InData_MACLength, OutData_Text);
}

rsip_ret_t r_rsip_wrapper_pa1i_aes256ccm_encrypt (const uint32_t * InData_KeyIndex,
                                                  const uint32_t * InData_TextLen,
                                                  const uint32_t * InData_IV,
                                                  const uint32_t * InData_Header,
                                                  uint32_t         Header_Len)
{
    (void) InData_TextLen;

    return r_rsip_pa1i(InData_KeyIndex, InData_IV, InData_Header, Header_Len);
}

rsip_ret_t r_rsip_wrapper_pa4i_aes256ccm_decrypt (const uint32_t * InData_KeyIndex,
                                                  const uint32_t * InData_TextLen,
                                                  const uint32_t * InData_MACLength,
                                                  const uint32_t * InData_IV,
                                                  const uint32_t * InData_Header,
                                                  uint32_t         Header_Len)
{
    (void) InData_TextLen;
    (void) InData_MACLength;

    return r_rsip_pa4i(InData_KeyIndex, InData_IV, InData_Header, Header_Len);
}

rsip_ret_t r_rsip_wrapper_p41i_aes128mac (const uint32_t * InData_KeyIndex)
{
    return r_rsip_p41i(InData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p41f_aes128mac_generate (const uint32_t * InData_Text,
                                                   uint32_t       * OutData_DataT,
                                                   const uint32_t   all_msg_len)
{
    uint32_t InData_Cmd[1] =
    {
        ((0 == (all_msg_len % 16)) &&
         (0 !=
          all_msg_len)) ? RSIP_PRV_CMD_AES_CMAC_GENERATE_WITHOUT_REMAINDER :
        RSIP_PRV_CMD_AES_CMAC_GENERATE_WITH_REMAINDER
    };
    uint32_t InData_DataT = 0;

    return r_rsip_p41f(InData_Cmd, InData_Text, &InData_DataT, (uint32_t *) &all_msg_len, OutData_DataT);
}

rsip_ret_t r_rsip_wrapper_p41f_aes128mac_verify (const uint32_t * InData_Text,
                                                 const uint32_t * InData_DataT,
                                                 const uint32_t * InData_DataTLen,
                                                 const uint32_t   all_msg_len)
{
    uint32_t InData_Cmd[1] =
    {
        ((0 == (all_msg_len % 16)) &&
         (0 !=
          all_msg_len)) ? RSIP_PRV_CMD_AES_CMAC_VERIFY_WITHOUT_REMAINDER :
        RSIP_PRV_CMD_AES_CMAC_VERIFY_WITH_REMAINDER
    };
    uint32_t OutData_DataT[4] = {0};
    (void) all_msg_len;

    return r_rsip_p41f(InData_Cmd, InData_Text, InData_DataT, InData_DataTLen, OutData_DataT);
}

rsip_ret_t r_rsip_wrapper_p44i_aes256mac (const uint32_t * InData_KeyIndex)
{
    return r_rsip_p44i(InData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p44f_aes256mac_generate (const uint32_t * InData_Text,
                                                   uint32_t       * OutData_DataT,
                                                   const uint32_t   all_msg_len)
{
    uint32_t InData_Cmd[1] =
    {
        ((0 == (all_msg_len % 16)) &&
         (0 !=
          all_msg_len)) ? RSIP_PRV_CMD_AES_CMAC_GENERATE_WITHOUT_REMAINDER :
        RSIP_PRV_CMD_AES_CMAC_GENERATE_WITH_REMAINDER
    };
    uint32_t InData_DataT = 0;

    return r_rsip_p44f(InData_Cmd, InData_Text, &InData_DataT, (uint32_t *) &all_msg_len, OutData_DataT);
}

rsip_ret_t r_rsip_wrapper_p44f_aes256mac_verify (const uint32_t * InData_Text,
                                                 const uint32_t * InData_DataT,
                                                 const uint32_t * InData_DataTLen,
                                                 const uint32_t   all_msg_len)
{
    uint32_t InData_Cmd[1] =
    {
        ((0 == (all_msg_len % 16)) &&
         (0 !=
          all_msg_len)) ? RSIP_PRV_CMD_AES_CMAC_VERIFY_WITHOUT_REMAINDER :
        RSIP_PRV_CMD_AES_CMAC_VERIFY_WITH_REMAINDER
    };
    uint32_t OutData_DataT[4] = {0};
    (void) all_msg_len;

    return r_rsip_p44f(InData_Cmd, InData_Text, InData_DataT, InData_DataTLen, OutData_DataT);
}

rsip_ret_t r_rsip_wrapper_pe2_wrapped (const uint32_t InData_PubKey[],
                                       const uint32_t InData_KeyIndex[],
                                       uint32_t       OutData_EncSecret[])
{
    return r_rsip_pe2(&gs_cmd[CMD_ECC_TYPE_NIST],
                      &gs_cmd[CMD_ECDH_PUBKEY_TYPE_WRAPPED],
                      InData_PubKey,
                      InData_KeyIndex,
                      DomainParam_NIST_P256,
                      OutData_EncSecret);
}

rsip_ret_t r_rsip_wrapper_pe2_plain (const uint32_t InData_PubKey[],
                                     const uint32_t InData_KeyIndex[],
                                     uint32_t       OutData_EncSecret[])
{
    return r_rsip_pe2(&gs_cmd[CMD_ECC_TYPE_NIST],
                      &gs_cmd[CMD_ECDH_PUBKEY_TYPE_PLAIN],
                      InData_PubKey,
                      InData_KeyIndex,
                      DomainParam_NIST_P256,
                      OutData_EncSecret);
}

rsip_ret_t r_rsip_wrapper_peei (const uint32_t InData_KeyIndex[],
                                const uint32_t InData_MsgDgst[],
                                const uint32_t InData_Signature[])
{
    return r_rsip_peei(&gs_cmd[CMD_ECC_TYPE_NIST],
                       InData_KeyIndex,
                       InData_MsgDgst,
                       InData_Signature,
                       DomainParam_NIST_P256);
}

rsip_ret_t r_rsip_wrapper_pe1_secp256r1 (const uint32_t InData_HashType[],
                                         const uint32_t InData_Certificate[],
                                         const uint32_t InData_CertificateLength[],
                                         const uint32_t InData_CertificatePubKey[],
                                         const uint32_t InData_EncCertificateInfo[],
                                         uint32_t       OutData_KeyIndex[])
{
    FSP_PARAMETER_NOT_USED(InData_HashType);

    return r_rsip_pe1(&gs_cmd[CMD_PKI_KEY_TYPE_ECC_SECP256R1],
                      InData_Certificate,
                      InData_CertificateLength,
                      InData_CertificatePubKey,
                      InData_EncCertificateInfo,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pe3_sha256 (const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[])
{
    return r_rsip_pe3(InData_EncSecret, OutData_EncMsg);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_aes128 (const uint32_t InData_KDFInfo[],
                                             const uint32_t InData_KDFInfo_Count[],
                                             const uint32_t InData_OutDataLocation[],
                                             uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pe7(InData_KDFInfo,
                      InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_AES128],
                      InData_OutDataLocation,
                      OutData_KeyIndex,
                      NULL);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_aes256 (const uint32_t InData_KDFInfo[],
                                             const uint32_t InData_KDFInfo_Count[],
                                             const uint32_t InData_OutDataLocation[],
                                             uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pe7(InData_KDFInfo,
                      InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_AES256],
                      InData_OutDataLocation,
                      OutData_KeyIndex,
                      NULL);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_iv_aes (const uint32_t InData_KDFInfo[],
                                             const uint32_t InData_KDFInfo_Count[],
                                             const uint32_t InData_OutDataLocation[],
                                             const uint32_t InData_SeqNum[],
                                             uint32_t       OutData_EncIV[])
{
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return r_rsip_pe7(InData_KDFInfo,
                      InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_IV_AES],
                      InData_OutDataLocation,
                      NULL,
                      OutData_EncIV);
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
