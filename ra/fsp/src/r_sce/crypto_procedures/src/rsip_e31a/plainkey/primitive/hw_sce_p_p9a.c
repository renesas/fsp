/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_KeyMode[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_Key[],
                                                const uint32_t InData_PubKey[],
                                                const uint32_t InData_DomainParam[],
                                                uint32_t       OutData_R[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x009a0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_A0H, 0x20010000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x3420a800U);
    WR1_PROG(REG_94H, 0x00000003U);
    WR1_PROG(REG_94H, 0x2000b400U);
    WR1_PROG(REG_94H, 0x00000002U);

    WR1_PROG(REG_94H, 0x00003420U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(0xfc7ac214U, 0x103c6538U, 0x5127dc85U, 0x125eb450U);
    WR1_PROG(REG_40H, 0x00400000U);
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
        WR1_PROG(REG_2CH, change_endian_long(0x0000009aU));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0xe15af534U, 0x6e74180fU, 0x34d4b18cU, 0x8a1f9e62U);
        HW_SCE_p_func043();

        HW_SCE_p_func074();

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x0000009aU));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x7af7c759U, 0x4696810cU, 0x2437a24fU, 0x61c26ea8U);
        HW_SCE_p_func044();

        WR1_PROG(REG_14H, 0x000007c1U);
        WR1_PROG(REG_D4H, 0x40000100U);
        WR1_PROG(REG_D0H, 0xf7009d07U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_B0H, 0x00001432U);
        WR1_PROG(REG_00H, 0x00c10021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[9]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func101(0x3a287061U, 0x2a230bb7U, 0x0c356758U, 0xfb61093aU);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000007c5U);
        WR1_PROG(REG_B0H, 0x00001432U);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_Key[0]);

        HW_SCE_p_func101(0x7938dd91U, 0x8d90fbf4U, 0x162f4b4eU, 0xfe873c94U);
    }

    HW_SCE_p_func100(0xd1e511b6U, 0x864427d8U, 0xaac39985U, 0xc5c264afU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xf8b3a65eU, 0x0feead67U, 0x3f0cecadU, 0xe971497cU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_94H, 0x00003401U);

        HW_SCE_p_func070(InData_DomainParam);

        WR1_PROG(REG_B8H, 0x00000005U);

        WR1_PROG(REG_A4H, 0x04040010U);

        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_14H, 0x00000fc5U);
        WR1_PROG(REG_B0H, 0x0000140fU);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_PubKey[0]);

        WR1_PROG(REG_B0H, 0x00001414U);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_PubKey[8]);

        HW_SCE_p_func008();

        HW_SCE_p_func100(0x46d2046dU, 0x749ecfacU, 0x7666dff8U, 0x4d6fff2bU);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x89f5874cU, 0xe86afc4aU, 0x05ebe120U, 0x3085b0afU);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x0000009aU));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0xf860a957U, 0x7b127890U, 0x36b15afcU, 0xd294428bU);
            HW_SCE_p_func088();

            HW_SCE_p_func100(0x6ed553f7U, 0x197e36f2U, 0x9084d0f2U, 0x144b9ab5U);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0x395234eeU, 0x7f3e77f3U, 0x0eff5cccU, 0xf8eb73bcU);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0xb11338c2U, 0x208c6a40U, 0xb321da10U, 0x58e89618U);
                WR1_PROG(REG_B0H, 0x00001828U);
                WR1_PROG(REG_08H, 0x00006022U);
                WAIT_STS(REG_08H, 30, 1);
                RD8_ADDR(REG_2CH, &OutData_R[0]);

                HW_SCE_p_func100(0x0c80998fU, 0xb96d0eb3U, 0xd930ad6fU, 0xed342749U);
                WR1_PROG(REG_B0H, 0x0000182dU);
                WR1_PROG(REG_08H, 0x00006022U);
                WAIT_STS(REG_08H, 30, 1);
                RD8_ADDR(REG_2CH, &OutData_R[8]);

                HW_SCE_p_func102(0x9ea457f8U, 0x7041c0b8U, 0x3f5ce921U, 0x563fd987U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
