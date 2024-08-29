/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_EcdsaSignatureGenerateSub (const uint32_t InData_CurveType[],
                                            const uint32_t InData_KeyMode[],
                                            const uint32_t InData_KeyIndex[],
                                            const uint32_t InData_Key[],
                                            const uint32_t InData_MsgDgst[],
                                            const uint32_t InData_DomainParam[],
                                            uint32_t       OutData_Signature[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00f00001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00A60000U);

    HW_SCE_p_func100(0xfd930acbU, 0x5f7dae3eU, 0xdb481737U, 0x02b3719cU);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x0dbefb02U, 0xf58d669dU, 0x9fe89dedU, 0x87108f6aU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func070(InData_DomainParam);

        HW_SCE_p_func100(0x88a198d6U, 0x40267339U, 0xc4747ec4U, 0xcf0adae9U);

        WR1_PROG(REG_B0H, 0x0000140fU);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x7eacebe1U, 0x0a53c92eU, 0x6b4bb952U, 0x7e6b3ca7U);
        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D0H, 0x0c200104U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
        WR1_PROG(REG_00H, 0x00c10011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func103();
        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D0H, 0x0c200104U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
        WR1_PROG(REG_00H, 0x00c10011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B0H, 0x00001428U);
        WR1_PROG(REG_00H, 0x00c0001dU);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_14H, 0x000000a5U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

        WR1_PROG(REG_B0H, 0x00001419U);
        WR1_PROG(REG_00H, 0x00c0001dU);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_14H, 0x000000a5U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000002U));

        WR1_PROG(REG_B4H, 0x0019000aU);
        WR1_PROG(REG_B8H, 0x00140000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_A0H, 0x20010000U);
        WR1_PROG(REG_B8H, 0x00000014U);

        WR1_PROG(REG_A4H, 0x04040010U);

        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x0028000fU);
        WR1_PROG(REG_B8H, 0x002d0014U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x0028002dU);
        WR1_PROG(REG_B8H, 0x00320000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        HW_SCE_p_func071(InData_DomainParam);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x000000f0U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0xb57d02d9U, 0xd7e8754eU, 0xfa62fd94U, 0x15262966U);
        HW_SCE_p_func088();

        HW_SCE_p_func100(0xaaf87e98U, 0xe8e3ec7eU, 0xce77ae89U, 0x9572cbaeU);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0xc815d4cfU, 0xf1790d98U, 0xa66a0668U, 0x3b5401e7U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_B8H, 0x0000000aU);

            WR1_PROG(REG_A4H, 0x04040010U);

            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x005a0028U);
            WR1_PROG(REG_B8H, 0x002d000aU);

            WR1_PROG(REG_A4H, 0x04040002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_14H, 0x000000a5U);
            WR1_PROG(REG_B0H, 0x0000140fU);
            WR1_PROG(REG_00H, 0x00c0001dU);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

            WR1_PROG(REG_B4H, 0x000f002dU);
            WR1_PROG(REG_B8H, 0x0028000aU);

            WR1_PROG(REG_A4H, 0x04040002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x000f0028U);
            WR1_PROG(REG_B8H, 0x00140000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_40H, 0x00210000U);

            HW_SCE_p_func100(0xfdbaed1cU, 0xd56ce5beU, 0x639635d2U, 0xcacc94b9U);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0xd2c4ec5dU, 0x25fc2807U, 0xc3e3dac8U, 0xb2c34828U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0xaf54dd06U, 0x6f470315U, 0x0e2b326dU, 0xa4ee0942U);
                WR1_PROG(REG_B0H, 0x00001414U);
                WR1_PROG(REG_00H, 0x00c0001dU);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);
                WR1_PROG(REG_14H, 0x000000a5U);
                WAIT_STS(REG_14H, 31, 1);
                WR1_PROG(REG_2CH, change_endian_long(0x00000002U));

                WR1_PROG(REG_B4H, 0x0014000aU);
                WR1_PROG(REG_B8H, 0x000f0000U);

                WR1_PROG(REG_A4H, 0x0404000aU);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B4H, 0x000f0032U);
                WR1_PROG(REG_B8H, 0x0014000aU);

                WR1_PROG(REG_A4H, 0x04040000U);
                WR1_PROG(REG_08H, 0x00020000U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);
                WR1_PROG(REG_40H, 0x00000d00U);

                WR1_PROG(REG_B4H, 0x005a0014U);
                WR1_PROG(REG_B8H, 0x000f000aU);

                WR1_PROG(REG_A4H, 0x04040002U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_14H, 0x000007c5U);
                WR1_PROG(REG_B0H, 0x00001414U);
                WAIT_STS(REG_14H, 31, 1);
                WR8_ADDR(REG_2CH, &InData_MsgDgst[0]);

                WR1_PROG(REG_14H, 0x000000c7U);
                WR1_PROG(REG_9CH, 0x80010000U);
                WAIT_STS(REG_14H, 31, 1);
                WR1_PROG(REG_2CH, InData_KeyMode[0]);
                WR1_PROG(REG_24H, 0x00000000U);

                WR1_PROG(REG_94H, 0x38000c00U);
                WR1_PROG(REG_9CH, 0x00000080U);
                WR1_PROG(REG_40H, 0x00260000U);

                HW_SCE_p_func100(0x533eeeeeU, 0x8b40ae27U, 0x3299f79cU, 0x86fe532dU);
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
                    WR1_PROG(REG_2CH, change_endian_long(0x000000f0U));
                    WR1_PROG(REG_24H, 0x00000000U);

                    HW_SCE_p_func101(0x6c37c3f9U, 0x5ab97345U, 0xb744f508U, 0x2b081a6eU);
                    HW_SCE_p_func043();

                    WR1_PROG(REG_94H, 0x0000b4c0U);
                    WR1_PROG(REG_94H, 0x00000017U);

                    WR1_PROG(REG_14H, 0x000000a7U);
                    WR1_PROG(REG_9CH, 0x800100e0U);
                    WAIT_STS(REG_14H, 31, 1);
                    WR1_PROG(REG_2CH, change_endian_long(0x000000f0U));
                    WR1_PROG(REG_24H, 0x00000000U);

                    HW_SCE_p_func101(0x395dfcbfU, 0x9de1b66dU, 0x1d5c144eU, 0xabbe75e3U);
                    HW_SCE_p_func044();

                    WR1_PROG(REG_14H, 0x000007c1U);
                    WR1_PROG(REG_D4H, 0x40000100U);
                    WR1_PROG(REG_D0H, 0xf7009d07U);
                    WAIT_STS(REG_14H, 31, 1);
                    WR4_ADDR(REG_2CH, &InData_KeyIndex[1]);
                    WAIT_STS(REG_14H, 31, 1);
                    WR4_ADDR(REG_2CH, &InData_KeyIndex[5]);

                    WR1_PROG(REG_B0H, 0x0000141eU);
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

                    HW_SCE_p_func101(0x53e20bf4U, 0xedfd1779U, 0x099a4fd8U, 0x51a8b7d1U);
                }
                else
                {
                    WR1_PROG(REG_14H, 0x000007c5U);
                    WR1_PROG(REG_B0H, 0x0000141eU);
                    WAIT_STS(REG_14H, 31, 1);
                    WR8_ADDR(REG_2CH, &InData_Key[0]);

                    HW_SCE_p_func101(0x1d013a9eU, 0x16120328U, 0xc822b330U, 0xb50d0c07U);
                }

                HW_SCE_p_func100(0xe9fcbeceU, 0x076b959bU, 0xb316972fU, 0xbb7bc321U);
                WR1_PROG(REG_40H, 0x00400000U);
                WR1_PROG(REG_24H, 0x00000000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    HW_SCE_p_func102(0x5ab4eafdU, 0xe84d02b0U, 0xd6ba5b5eU, 0xf69185c1U);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
                }
                else
                {
                    WR1_PROG(REG_B4H, 0x005a001eU);
                    WR1_PROG(REG_B8H, 0x0019000aU);

                    WR1_PROG(REG_A4H, 0x04040002U);
                    WR1_PROG(REG_A0H, 0x20010001U);
                    WAIT_STS(REG_A8H, 0, 1);
                    WR1_PROG(REG_ACH, 0x00000001U);

                    WR1_PROG(REG_B4H, 0x00280019U);
                    WR1_PROG(REG_B8H, 0x001e000aU);

                    WR1_PROG(REG_A4H, 0x04040002U);
                    WR1_PROG(REG_A0H, 0x20010001U);
                    WAIT_STS(REG_A8H, 0, 1);
                    WR1_PROG(REG_ACH, 0x00000001U);

                    WR1_PROG(REG_B4H, 0x001e0014U);
                    WR1_PROG(REG_B8H, 0x0019000aU);

                    WR1_PROG(REG_A4H, 0x04040005U);
                    WR1_PROG(REG_A0H, 0x20010001U);
                    WAIT_STS(REG_A8H, 0, 1);
                    WR1_PROG(REG_ACH, 0x00000001U);

                    WR1_PROG(REG_B4H, 0x0019000fU);
                    WR1_PROG(REG_B8H, 0x001e000aU);

                    WR1_PROG(REG_A4H, 0x04040002U);
                    WR1_PROG(REG_A0H, 0x20010001U);
                    WAIT_STS(REG_A8H, 0, 1);
                    WR1_PROG(REG_ACH, 0x00000001U);

                    WR1_PROG(REG_B0H, 0x0000140fU);
                    WR1_PROG(REG_00H, 0x00c0001dU);
                    WAIT_STS(REG_04H, 30, 0);
                    WR1_PROG(REG_40H, 0x00001800U);
                    WR1_PROG(REG_14H, 0x000000a5U);
                    WAIT_STS(REG_14H, 31, 1);
                    WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

                    WR1_PROG(REG_B4H, 0x000f001eU);
                    WR1_PROG(REG_B8H, 0x00140000U);

                    WR1_PROG(REG_A4H, 0x0404000aU);
                    WR1_PROG(REG_A0H, 0x20010001U);
                    WAIT_STS(REG_A8H, 0, 1);
                    WR1_PROG(REG_ACH, 0x00000001U);

                    WR1_PROG(REG_40H, 0x00210000U);

                    HW_SCE_p_func100(0xfdf98537U, 0x88686999U, 0x5dbdc03fU, 0x7a51cf04U);
                    WR1_PROG(REG_40H, 0x00400000U);
                    WR1_PROG(REG_24H, 0x00000000U);

                    if (CHCK_STS(REG_40H, 22, 1))
                    {
                        HW_SCE_p_func102(0x958994e2U, 0x31cd8014U, 0x83b5923dU, 0xf77c8004U);
                        WR1_PROG(REG_6CH, 0x00000040U);
                        WAIT_STS(REG_20H, 12, 0);

                        return FSP_ERR_CRYPTO_SCE_FAIL;
                    }
                    else
                    {
                        HW_SCE_p_func100(0x014a78bcU, 0x323cfaaeU, 0x1c1adda2U, 0xae02aec1U);
                        WR1_PROG(REG_B0H, 0x00001828U);
                        WR1_PROG(REG_08H, 0x00006022U);
                        WAIT_STS(REG_08H, 30, 1);
                        RD8_ADDR(REG_2CH, &OutData_Signature[0]);

                        HW_SCE_p_func100(0x4494f1a1U, 0xdce6128fU, 0x80f2a930U, 0xb4ebaf68U);
                        WR1_PROG(REG_B0H, 0x0000181eU);
                        WR1_PROG(REG_08H, 0x00006022U);
                        WAIT_STS(REG_08H, 30, 1);
                        RD8_ADDR(REG_2CH, &OutData_Signature[8]);

                        HW_SCE_p_func102(0x33b7c3a5U, 0xcbf88c64U, 0x98226388U, 0x44c14fbdU);
                        WR1_PROG(REG_6CH, 0x00000040U);
                        WAIT_STS(REG_20H, 12, 0);

                        return FSP_SUCCESS;
                    }
                }
            }
        }
    }
}
