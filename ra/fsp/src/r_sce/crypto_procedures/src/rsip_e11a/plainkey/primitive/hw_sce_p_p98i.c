/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128CcmDecryptInitSub (const uint32_t InData_KeyMode[],
                                          const uint32_t InData_TextLen[],
                                          const uint32_t InData_MACLength[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Key[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_Header[],
                                          const uint32_t Header_Len)
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00980001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010080U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_TextLen[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010060U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_MACLength[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    HW_SCE_p_func100(0xbd38fa23U, 0xd996c72bU, 0xe03e648aU, 0xb9fa9b04U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x800100c0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_KeyIndex[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000098U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0xfcb237d3U, 0x6aa84faaU, 0x7dbf795bU, 0x4f97cf2cU);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x0000b4c0U);
        WR1_PROG(REG_94H, 0x00000005U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000098U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x8d3a1b06U, 0x6a726965U, 0xd24b7839U, 0x23bac381U);
        HW_SCE_p_func044();

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xf7009d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1]);

        WR1_PROG(REG_B0H, 0x00000401U);
        WR1_PROG(REG_00H, 0x00c10009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_B0H, 0x00000402U);
        WR1_PROG(REG_00H, 0x00c10009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func101(0xcf03c749U, 0xf2e6c4e0U, 0xa5e50dddU, 0x65bb1a38U);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000003c5U);
        WR1_PROG(REG_B0H, 0x00000401U);
        WAIT_STS(REG_14H, 31, 1);
        WR2_ADDR(REG_2CH, &InData_Key[0]);
        WR1_PROG(REG_B0H, 0x00000402U);
        WAIT_STS(REG_14H, 31, 1);
        WR2_ADDR(REG_2CH, &InData_Key[2]);

        HW_SCE_p_func101(0x06c142dcU, 0x1ad9ea4fU, 0x979a2b0aU, 0xdb11578cU);
    }

    HW_SCE_p_func100(0xaab1023cU, 0x039b8ae3U, 0x68ade1c6U, 0x64376164U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x717dd753U, 0x550301deU, 0xa60b3b3fU, 0x4639fd90U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0xed819a28U, 0xa1217040U, 0x51fa3316U, 0xc47a9ef7U);

        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        WR1_PROG(REG_00H, 0x00430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B0H, 0x00000802U);
        WR1_PROG(REG_00H, 0x00430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_D4H, 0x00000000U);
        HW_SCE_p_func501(InData_IV, InData_Header, Header_Len);

        HW_SCE_p_func101(0x1faade14U, 0x62ef72aaU, 0x17b8b788U, 0x988f772dU);

        return FSP_SUCCESS;
    }
}
