/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "hw_sce_aes_private.h"
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define HW_BYTE_TO_BIT_LENGTH(x)    ((x) << 3)

#define SCE_AES_PRV_CCM_TLEN_VALUE_OFFSET     (16 / 8)
#define SCE_AES_PRV_CCM_TLEN_MIN_VALUE        (32 / 8)

#define SCE_AES_PRV_CCM_NLEN_VALUE_OFFSET     (8 / 8)
#define SCE_AES_PRV_CCM_NLEN_MIN_VALUE        (56 / 8)

#define HW_SCE_AES_CCM_B0_TLEN_32BITS_CFG     (0x00000000)
#define HW_SCE_AES_CCM_B0_TLEN_48BITS_CFG     (0x00000001)
#define HW_SCE_AES_CCM_B0_TLEN_64BITS_CFG     (0x00000002)
#define HW_SCE_AES_CCM_B0_TLEN_80BITS_CFG     (0x00000003)
#define HW_SCE_AES_CCM_B0_TLEN_96BITS_CFG     (0x00000004)
#define HW_SCE_AES_CCM_B0_TLEN_112BITS_CFG    (0x00000005)
#define HW_SCE_AES_CCM_B0_TLEN_128BITS_CFG    (0x00000006)

#define HW_SCE_AES_CCM_B0_NLEN_56BITS_CFG     (0x00000000)
#define HW_SCE_AES_CCM_B0_NLEN_64BITS_CFG     (0x00000001)
#define HW_SCE_AES_CCM_B0_NLEN_72BITS_CFG     (0x00000002)
#define HW_SCE_AES_CCM_B0_NLEN_80BITS_CFG     (0x00000003)
#define HW_SCE_AES_CCM_B0_NLEN_88BITS_CFG     (0x00000004)
#define HW_SCE_AES_CCM_B0_NLEN_96BITS_CFG     (0x00000005)
#define HW_SCE_AES_CCM_B0_NLEN_104BITS_CFG    (0x00000006)

#define PARAM_B0_PLEN_3BITS_MSB_OFFSET        (29)
#define PARAM_B0_ALEN_3BITS_MSB_OFFSET        (13)
#define PARAM_B0_B127_B96_MASK                (0x0007FFF8)
#define PARAM_B0_B95_B64_MASK                 (0x00770000)
#define PARAM_B0_B63_B32_MASK                 (0x00000007)
#define PARAM_B0_B31_B0_MASK                  (0xFFFFFFF8)
#define PARAM_B0_B95_B64_TLEN_OFFSET          (16)
#define PARAM_B0_B95_B64_NLEN_OFFSET          (20)

#define HW_AES_BLOCK_LAST_WORD                (3)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/
typedef struct B0_param
{
    uint32_t B31_B0;                   /*!< B0[31:30]: bitfield of Plen                                                 */
    uint32_t B63_B32;                  /*!< B0[63:32]: bitfield of Plen                                                 */
    uint32_t B95_B64;                  /*!< B0[66:64]: bitfield of Plen, B0[79:67]: reserved, B0[82:80]: bitfield of Tlen,
                                        *   B0[83:83]: reserved, B0[86:84]: bitfield of Nlen, B0[95:87]: reserved       */
    uint32_t B127_B96;                 /*!< B0[114:96]: bitfield of Alen, B0[127:115]: reserved                         */
} st_AES_Ccm_B0_param_t;

/***********************************************************************************************************************
 * Imported global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private variables and functions
 ***********************************************************************************************************************/
static uint32_t const g_aes_ccm_tlen_cfg_lut[] =
{
    HW_SCE_AES_CCM_B0_TLEN_32BITS_CFG, HW_SCE_AES_CCM_B0_TLEN_48BITS_CFG, HW_SCE_AES_CCM_B0_TLEN_64BITS_CFG,
    HW_SCE_AES_CCM_B0_TLEN_80BITS_CFG, HW_SCE_AES_CCM_B0_TLEN_96BITS_CFG, HW_SCE_AES_CCM_B0_TLEN_112BITS_CFG,
    HW_SCE_AES_CCM_B0_TLEN_128BITS_CFG
};

static uint32_t const g_aes_ccm_nlen_cfg_lut[] =
{
    HW_SCE_AES_CCM_B0_NLEN_56BITS_CFG, HW_SCE_AES_CCM_B0_NLEN_64BITS_CFG, HW_SCE_AES_CCM_B0_NLEN_72BITS_CFG,
    HW_SCE_AES_CCM_B0_NLEN_80BITS_CFG, HW_SCE_AES_CCM_B0_NLEN_88BITS_CFG, HW_SCE_AES_CCM_B0_NLEN_96BITS_CFG,
    HW_SCE_AES_CCM_B0_NLEN_104BITS_CFG
};

static void hw_aes_ccm_calculate_b0(st_AES_Ccm_B0_param_t * Out_ParamB0,
                                    uint32_t                plen,
                                    uint32_t                alen,
                                    uint32_t                tlen,
                                    uint32_t                nlen);
static void hw_aes_ccm_encrypt_init(uint32_t indata_cmd);

static void aes_block_swap_endian(uint32_t * InOut_Block, uint32_t MaxBlock);

/***********************************************************************************************************************
 * Global variables and functions
 ***********************************************************************************************************************/
void hw_aes_ccm_decrypt_init(uint32_t indata_cmd);
void HW_SCE_AesCcmEncryptKeyOperation(uint32_t * InData_KeyIndex,
                                      uint32_t   InData_KeyType,
                                      uint32_t * InData_IV,
                                      uint32_t   InData_IVLength);
void HW_SCE_AesCcmDecryptKeyOperation(uint32_t * InData_KeyIndex,
                                      uint32_t   InData_KeyType,
                                      uint32_t * InData_IV,
                                      uint32_t   InData_IVLength);
void HW_SCE_AesCcmEncryptCounterGenerate(uint32_t InData_TextLength,
                                         uint32_t InData_Hdrlen,
                                         uint32_t InData_MacLength,
                                         uint32_t InData_IVLength);
void HW_SCE_AesCcmDecryptCounterGenerate(uint32_t InData_TextLength,
                                         uint32_t InData_Hdrlen,
                                         uint32_t InData_MacLength,
                                         uint32_t InData_IVLength);
void HW_SCE_AesCcmEncryptInputAssociatedData(uint32_t * InData_Header, uint32_t InData_Hdrlen);
void HW_SCE_AesCcmDecryptInputAssociatedData(uint32_t * InData_Header, uint32_t InData_Hdrlen);
void HW_SCE_AesCcmEncryptPlaintextInputInit();
void HW_SCE_AesCcmEncryptGenerateTag(uint32_t * OutData_MAC);

/***********************************************************************************************************************
 * @brief Swap byte-order of an AES block
 *
 * @param[in,out]   InOut_Block  pointer to blocks need to convert endianess
 * @param[in]       MaxBlock     number of block need to convert
 ***********************************************************************************************************************/
static void aes_block_swap_endian (uint32_t * InOut_Block, uint32_t MaxBlock)
{
    uint32_t   aes_block_tmp[SIZE_AES_BLOCK_BYTES / 4];
    uint32_t * InBlock = InOut_Block;
    uint32_t   block_cnt;

    for (block_cnt = 0; block_cnt < MaxBlock; block_cnt++)
    {
        uint32_t index;
        for (index = 0; index <= HW_AES_BLOCK_LAST_WORD; index++)
        {
            aes_block_tmp[HW_AES_BLOCK_LAST_WORD - index] = __REV(*(InBlock + index));
        }

        memcpy(InBlock, aes_block_tmp, SIZE_AES_BLOCK_BYTES);
        InBlock += 4;
    }
}

/***********************************************************************************************************************
 * @brief Implement common operation, input key and IV for encryption
 *
 * @param[in] InData_KeyIndex       pointer to key to be input
 * @param[in] InData_KeyType        to determine which key type is input
 * @param[in] InData_IV             pointer to IV to be input
 * @param[in] InData_IVLength       to determine IV length in byte to be input
 ***********************************************************************************************************************/
void HW_SCE_AesCcmEncryptKeyOperation (uint32_t * InData_KeyIndex,
                                       uint32_t   InData_KeyType,
                                       uint32_t * InData_IV,
                                       uint32_t   InData_IVLength)
{
    uint8_t InData_IV_tmp[SIZE_AES_BLOCK_BYTES] = {0};

    /* SCE AES hardware configuration for key operation */
    if (SIZE_AES_128BIT_KEYLEN_BYTES == InData_KeyType)
    {
        hw_aes_ccm_encrypt_init(SCE_AES_IN_DATA_CMD_CCM_128_ENC_COMMON_INIT);
    }
    else if (SIZE_AES_192BIT_KEYLEN_BYTES == InData_KeyType)
    {
        hw_aes_ccm_encrypt_init(SCE_AES_IN_DATA_CMD_CCM_192_ENC_COMMON_INIT);
    }
    else
    {
        /* Input key is 256bits length  */
        hw_aes_ccm_encrypt_init(SCE_AES_IN_DATA_CMD_CCM_256_ENC_COMMON_INIT);
    }

    /* Key input */
    hw_aes_set_key((uint8_t *) InData_KeyIndex, InData_KeyType);

    /* IV input */
    memcpy(&InData_IV_tmp[SIZE_AES_BLOCK_BYTES - InData_IVLength], InData_IV, InData_IVLength);
    hw_aes_set_iv(InData_IV_tmp);
}

/***********************************************************************************************************************
 * @brief Implement common operation, input key and IV for decryption
 *
 * @param[in] InData_KeyIndex       pointer to key to be input
 * @param[in] InData_KeyType        to determine which key type is input
 * @param[in] InData_IV             pointer to IV to be input
 * @param[in] InData_IVLength       to determine IV length in byte to be input
 ***********************************************************************************************************************/
void HW_SCE_AesCcmDecryptKeyOperation (uint32_t * InData_KeyIndex,
                                       uint32_t   InData_KeyType,
                                       uint32_t * InData_IV,
                                       uint32_t   InData_IVLength)
{
    uint8_t InData_IV_tmp[SIZE_AES_BLOCK_BYTES] = {0};

    /* SCE AES hardware configuration for key operation */
    if (SIZE_AES_128BIT_KEYLEN_BYTES == InData_KeyType)
    {
        hw_aes_ccm_decrypt_init(SCE_AES_IN_DATA_CMD_CCM_128_DEC_COMMON_INIT);
    }
    else if (SIZE_AES_192BIT_KEYLEN_BYTES == InData_KeyType)
    {
        hw_aes_ccm_decrypt_init(SCE_AES_IN_DATA_CMD_CCM_192_DEC_COMMON_INIT);
    }
    else
    {
        /* Input key is 256bits length  */
        hw_aes_ccm_decrypt_init(SCE_AES_IN_DATA_CMD_CCM_256_DEC_COMMON_INIT);
    }

    /* Key input */
    hw_aes_set_key((uint8_t *) InData_KeyIndex, InData_KeyType);

    /* IV input */
    memcpy(&InData_IV_tmp[SIZE_AES_BLOCK_BYTES - InData_IVLength], InData_IV, InData_IVLength);
    hw_aes_set_iv(InData_IV_tmp);
}

/***********************************************************************************************************************
 * @brief Implement common operation to generate counter and input parameter B0
 *
 * @param[in] InData_TextLength         length in byte of payload data to be input
 * @param[in] InData_Hdrlen             length in byte of associated data to be input
 * @param[in] InData_MacLength          length in byte of tag need to be generated
 * @param[in] InData_IVLength           length in byte of IV to be input
 ***********************************************************************************************************************/
void HW_SCE_AesCcmEncryptCounterGenerate (uint32_t InData_TextLength,
                                          uint32_t InData_Hdrlen,
                                          uint32_t InData_MacLength,
                                          uint32_t InData_IVLength)
{
    st_AES_Ccm_B0_param_t param_B0;

    /* SCE AES hardware configuration for parameter B0 input */
    hw_aes_ccm_encrypt_init(SCE_AES_IN_DATA_CMD_CCM_ENC_COUNTER_GENERATE);

    /* Apply formatting function for parameter B0 */
    hw_aes_ccm_calculate_b0(&param_B0, InData_TextLength, InData_Hdrlen, InData_MacLength, InData_IVLength);

    /* Swap endian to have parameter B0 with big endian */
    aes_block_swap_endian((uint32_t *) &param_B0, sizeof(st_AES_Ccm_B0_param_t) / SIZE_AES_BLOCK_BYTES);

    /* Input parameter B0 and apply counter generation function */
    hw_aes_ccm_mode_start((uint8_t *) &param_B0, NULL, sizeof(st_AES_Ccm_B0_param_t) / SIZE_AES_BLOCK_BYTES);
}

/***********************************************************************************************************************
 * @brief Implement common operation to generate counter and input parameter B0
 *
 * @param[in] InData_TextLength         length in byte of payload data to be input
 * @param[in] InData_Hdrlen             length in byte of associated data to be input
 * @param[in] InData_MacLength          length in byte of tag need to be generated
 * @param[in] InData_IVLength           length in byte of IV to be input
 ***********************************************************************************************************************/
void HW_SCE_AesCcmDecryptCounterGenerate (uint32_t InData_TextLength,
                                          uint32_t InData_Hdrlen,
                                          uint32_t InData_MacLength,
                                          uint32_t InData_IVLength)
{
    st_AES_Ccm_B0_param_t param_B0;

    /* SCE AES hardware configuration for parameter B0 input */
    hw_aes_ccm_decrypt_init(SCE_AES_IN_DATA_CMD_CCM_DEC_COUNTER_GENERATE);

    /* Apply formatting function for parameter B0 */
    hw_aes_ccm_calculate_b0(&param_B0, InData_TextLength, InData_Hdrlen, InData_MacLength, InData_IVLength);

    /* Swap endian to have parameter B0 with big endian */
    aes_block_swap_endian((uint32_t *) &param_B0, sizeof(st_AES_Ccm_B0_param_t) / SIZE_AES_BLOCK_BYTES);

    /* Input parameter B0 and apply counter generation function */
    hw_aes_ccm_mode_start((uint8_t *) &param_B0, NULL, sizeof(st_AES_Ccm_B0_param_t) / SIZE_AES_BLOCK_BYTES);
}

/***********************************************************************************************************************
 * @brief Implement common operation and input associated data
 *
 * @param[in] InData_Header         pointer to associated data string need to be input
 * @param[in] InData_Hdrlen         length in byte of associated data string
 ***********************************************************************************************************************/
void HW_SCE_AesCcmEncryptInputAssociatedData (uint32_t * InData_Header, uint32_t InData_Hdrlen)
{
    /* SCE AES hardware configuration for associated data input */
    hw_aes_ccm_encrypt_init(SCE_AES_IN_DATA_CMD_CCM_ENC_FORMAT_A_DATA);

    /* Input associated data */
    uint8_t * p_a_data  = (uint8_t *) InData_Header;
    uint32_t  block_cnt = HW_AES_DATA_FIT_TO_BLOCK_SIZE(InData_Hdrlen);
    if (0 < block_cnt)
    {
        hw_aes_ccm_mode_start((uint8_t *) InData_Header, NULL, block_cnt / SIZE_AES_BLOCK_BYTES);
        p_a_data += block_cnt;
    }

    uint32_t remain_data = HW_AES_DATA_GET_LAST_REMAINS(InData_Hdrlen);
    if (0 < remain_data)
    {
        uint32_t a_data_tmp[SIZE_AES_BLOCK_BYTES / sizeof(uint32_t)] = {0};
        memcpy(a_data_tmp, p_a_data, remain_data);
        hw_aes_ccm_mode_start((uint8_t *) a_data_tmp, NULL, SIZE_AES_BLOCK_BYTES / SIZE_AES_BLOCK_BYTES);
    }
}

/***********************************************************************************************************************
 * @brief Implement common operation and input associated data
 *
 * @param[in] InData_Header         pointer to associated data string need to be input
 * @param[in] InData_Hdrlen         length in byte of associated data string
 ***********************************************************************************************************************/
void HW_SCE_AesCcmDecryptInputAssociatedData (uint32_t * InData_Header, uint32_t InData_Hdrlen)
{
    /* SCE AES hardware configuration for associated data input */
    hw_aes_ccm_decrypt_init(SCE_AES_IN_DATA_CMD_CCM_DEC_FORMAT_A_DATA);

    /* Input associated data */
    uint8_t * p_a_data  = (uint8_t *) InData_Header;
    uint32_t  block_cnt = HW_AES_DATA_FIT_TO_BLOCK_SIZE(InData_Hdrlen);
    if (0 < block_cnt)
    {
        hw_aes_ccm_mode_start((uint8_t *) InData_Header, NULL, block_cnt / SIZE_AES_BLOCK_BYTES);
        p_a_data += block_cnt;
    }

    uint32_t remain_data = HW_AES_DATA_GET_LAST_REMAINS(InData_Hdrlen);
    if (0 < remain_data)
    {
        uint32_t a_data_tmp[SIZE_AES_BLOCK_BYTES / sizeof(uint32_t)] = {0};
        memcpy(a_data_tmp, p_a_data, remain_data);
        hw_aes_ccm_mode_start((uint8_t *) a_data_tmp, NULL, SIZE_AES_BLOCK_BYTES / SIZE_AES_BLOCK_BYTES);
    }
}

/***********************************************************************************************************************
 * @brief Implement common operation before in put plaintext to be encrypted
 *
 ***********************************************************************************************************************/
void HW_SCE_AesCcmEncryptPlaintextInputInit ()
{
    /* Hardware config to input plaintext */
    hw_aes_ccm_encrypt_init(SCE_AES_IN_DATA_CMD_CCM_ENC_CTR_ENCRYPT);
}

/***********************************************************************************************************************
 * @brief Implement common operations and generate Tag
 *
 * @param[out] OutData_MAC          pointer to memory to output Tag
 ***********************************************************************************************************************/
void HW_SCE_AesCcmEncryptGenerateTag (uint32_t * OutData_MAC)
{
    uint32_t dummy_data[SIZE_AES_BLOCK_BYTES / sizeof(uint32_t)] = {0};

    /* Generate Tag */
    hw_aes_ccm_encrypt_init(SCE_AES_IN_DATA_CMD_CCM_ENC_GENERATE_TAG);
    hw_aes_ccm_mode_start((uint8_t *) dummy_data, (uint8_t *) OutData_MAC, sizeof(dummy_data) / SIZE_AES_BLOCK_BYTES);
}

/***********************************************************************************************************************
 * @brief Assign value for parameter B0 to setting HW SCE AES CCM mode, output parameter B0 as little endian order
 *
 * @param[in,out]   Out_ParamB0     pointer to parameter B0 block
 * @param[in]       plen            payload length in byte
 * @param[in]       alen            associated length in byte
 * @param[in]       tlen            tag length in byte
 * @param[in]       nlen            nonce length in byte
 ***********************************************************************************************************************/
static void hw_aes_ccm_calculate_b0 (st_AES_Ccm_B0_param_t * Out_ParamB0,
                                     uint32_t                plen,
                                     uint32_t                alen,
                                     uint32_t                tlen,
                                     uint32_t                nlen)
{
    uint32_t index;
    memset(Out_ParamB0, 0, sizeof(st_AES_Ccm_B0_param_t));

    /* Assign Plaintext length Bit */
    Out_ParamB0->B31_B0  = HW_BYTE_TO_BIT_LENGTH(plen) & PARAM_B0_B31_B0_MASK;
    Out_ParamB0->B63_B32 = (plen >> PARAM_B0_PLEN_3BITS_MSB_OFFSET) & PARAM_B0_B63_B32_MASK;

    /* Assign Tag length Bit */
    uint32_t b95_b64 = 0;
    index   = (tlen - SCE_AES_PRV_CCM_TLEN_MIN_VALUE) / SCE_AES_PRV_CCM_TLEN_VALUE_OFFSET;
    b95_b64 = g_aes_ccm_tlen_cfg_lut[index] << PARAM_B0_B95_B64_TLEN_OFFSET;

    /* Assign Nonce length Bit */
    index                = (nlen - SCE_AES_PRV_CCM_NLEN_MIN_VALUE) / SCE_AES_PRV_CCM_NLEN_VALUE_OFFSET;
    b95_b64             |= g_aes_ccm_nlen_cfg_lut[index] << PARAM_B0_B95_B64_NLEN_OFFSET;
    Out_ParamB0->B95_B64 = b95_b64 & PARAM_B0_B95_B64_MASK;

    /* Assign Non-Encryption word length Bit */
    Out_ParamB0->B127_B96 = HW_BYTE_TO_BIT_LENGTH(alen) & PARAM_B0_B127_B96_MASK;
}

/***********************************************************************************************************************
 * @brief Configure AES module to run CCM mode encryption operation
 *
 * @param[in] indata_cmd            to be determined which operation need to be initial
 **********************************************************************************************************************/
static void hw_aes_ccm_encrypt_init (uint32_t indata_cmd)
{
    switch (indata_cmd)
    {
        case SCE_AES_IN_DATA_CMD_CCM_128_ENC_COMMON_INIT:
        {
            R_AES_B->AESCNTH = R_AES_AESCNTH_INIT;
            R_AES_B->AESCNTL = R_AES_AESCNTL_CCM_128_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_192_ENC_COMMON_INIT:
        {
            R_AES_B->AESCNTH = R_AES_AESCNTH_INIT;
            R_AES_B->AESCNTL = R_AES_AESCNTL_CCM_192_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_256_ENC_COMMON_INIT:
        {
            R_AES_B->AESCNTH = R_AES_AESCNTH_INIT;
            R_AES_B->AESCNTL = R_AES_AESCNTL_CCM_256_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_ENC_COUNTER_GENERATE:
        {
            R_AES_B->AESDCNTH = R_AES_AESDCNTH_NOT_EXECUTE_TAG_CALCULATION;
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_ATTR_CCM_MODE_1 |
                                R_AES_AESDCNTL_FIST_SET |
                                R_AES_AESDCNTL_NEW_KEY_SET;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_ENC_FORMAT_A_DATA:
        {
            R_AES_B->AESDCNTH = R_AES_AESDCNTH_NOT_EXECUTE_TAG_CALCULATION;
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_ATTR_CCM_MODE_3;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_ENC_CTR_ENCRYPT:
        {
            R_AES_B->AESDCNTH = R_AES_AESDCNTH_NOT_EXECUTE_TAG_CALCULATION;
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_ATTR_CCM_MODE_4;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_ENC_GENERATE_TAG:
        {
            R_AES_B->AESDCNTH = R_AES_AESDCNTH_EXECUTE_TAG_CALCULATION;
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_ATTR_CCM_MODE_5;
            break;
        }

        default:
        {
            break;
        }
    }
}

/***********************************************************************************************************************
 * @brief Configure AES module to run CCM mode decryption operation
 *
 * @param[in] indata_cmd            to be determined which operation need to be initial
 **********************************************************************************************************************/
void hw_aes_ccm_decrypt_init (uint32_t indata_cmd)
{
    switch (indata_cmd)
    {
        case SCE_AES_IN_DATA_CMD_CCM_128_DEC_COMMON_INIT:
        {
            R_AES_B->AESCNTH = R_AES_AESCNTH_INIT;
            R_AES_B->AESCNTL = R_AES_AESCNTL_CCM_128_DEC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_192_DEC_COMMON_INIT:
        {
            R_AES_B->AESCNTH = R_AES_AESCNTH_INIT;
            R_AES_B->AESCNTL = R_AES_AESCNTL_CCM_192_DEC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_256_DEC_COMMON_INIT:
        {
            R_AES_B->AESCNTH = R_AES_AESCNTH_INIT;
            R_AES_B->AESCNTL = R_AES_AESCNTL_CCM_256_DEC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_DEC_COUNTER_GENERATE:
        {
            R_AES_B->AESDCNTH = R_AES_AESDCNTH_NOT_EXECUTE_TAG_CALCULATION;
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_ATTR_CCM_MODE_1 |
                                R_AES_AESDCNTL_FIST_SET |
                                R_AES_AESDCNTL_NEW_KEY_SET;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_DEC_CTR_DECRYPT:
        {
            R_AES_B->AESDCNTH = R_AES_AESDCNTH_NOT_EXECUTE_TAG_CALCULATION;
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_ATTR_CCM_MODE_2;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_DEC_FORMAT_A_DATA:
        {
            R_AES_B->AESDCNTH = R_AES_AESDCNTH_NOT_EXECUTE_TAG_CALCULATION;
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_ATTR_CCM_MODE_3;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_DEC_FORMAT_PAYLOAD:
        {
            R_AES_B->AESDCNTH = R_AES_AESDCNTH_NOT_EXECUTE_TAG_CALCULATION;
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_ATTR_CCM_MODE_4;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CCM_DEC_GENERATE_TAG:
        {
            R_AES_B->AESDCNTH = R_AES_AESDCNTH_EXECUTE_TAG_CALCULATION;
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_ATTR_CCM_MODE_6;
            break;
        }

        default:
        {
            break;
        }
    }
}
