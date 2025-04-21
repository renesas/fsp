/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
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

    WR1_PROG(REG_94H, 0x3420a800U);
    WR1_PROG(REG_94H, 0x00000003U);
    WR1_PROG(REG_94H, 0x2000b400U);
    WR1_PROG(REG_94H, 0x00000002U);

    HW_SCE_p_func070(InData_DomainParam);

    HW_SCE_p_func100(0x163cc17dU, 0x7320319eU, 0x61df029cU, 0x73889bd7U);

    WR1_PROG(REG_B0H, 0x0000140fU);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xa2653666U, 0x7bca9ad9U, 0xd3f82bbdU, 0xaac3d6bfU);
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

    WR1_PROG(REG_94H, 0x00003420U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f0U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x65fa125eU, 0xc9eb1085U, 0x0e1ad059U, 0x9cd8d4b5U);
    HW_SCE_p_func088();

    HW_SCE_p_func100(0x72f3a9d9U, 0xa35ea6e7U, 0x472b6dd7U, 0x80388eedU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xfdea0504U, 0x497a96adU, 0x4ea04cf0U, 0xf70d38f5U);
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

        HW_SCE_p_func100(0x78fe5066U, 0x20853a9fU, 0x08bb7ec5U, 0x59f15f60U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x94ef55cbU, 0xc6016474U, 0x1002235fU, 0x33432705U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0x7d8779b5U, 0x93adecd9U, 0x33061924U, 0x7909f056U);
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
            WR1_PROG(REG_40H, 0x00270000U);

            HW_SCE_p_func100(0x120f7687U, 0x7251ac49U, 0xec7aa935U, 0x9643c035U);
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
                WR1_PROG(REG_2CH, change_endian_long(0x000000f0U));
                WR1_PROG(REG_24H, 0x00000000U);

                HW_SCE_p_func101(0xaeeabdd2U, 0x7b2e3d4cU, 0x951575fdU, 0x70a96f70U);
                HW_SCE_p_func043();

                HW_SCE_p_func074();

                WR1_PROG(REG_14H, 0x000000a7U);
                WR1_PROG(REG_9CH, 0x800100e0U);
                WAIT_STS(REG_14H, 31, 1);
                WR1_PROG(REG_2CH, change_endian_long(0x000000f0U));
                WR1_PROG(REG_24H, 0x00000000U);

                HW_SCE_p_func101(0x3f50d72eU, 0x95dfef3fU, 0x436e2184U, 0x2be56ef4U);
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

                HW_SCE_p_func101(0xedf56c5aU, 0xacaef197U, 0x2d8b674dU, 0x13971992U);
            }
            else
            {
                WR1_PROG(REG_14H, 0x000007c5U);
                WR1_PROG(REG_B0H, 0x0000141eU);
                WAIT_STS(REG_14H, 31, 1);
                WR8_ADDR(REG_2CH, &InData_Key[0]);

                HW_SCE_p_func101(0xe8ca23f6U, 0x18d5619fU, 0x7d74bfc1U, 0x9565b9abU);
            }

            HW_SCE_p_func100(0x05f020ceU, 0x391c5d7eU, 0xa4f4f478U, 0x11162e6dU);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0x1b3a2f77U, 0x7f313ed8U, 0xfa97a595U, 0x09457bf7U);
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

                HW_SCE_p_func100(0x10ba9dceU, 0x9d987c2fU, 0x20bd2c5bU, 0xd9141c14U);
                WR1_PROG(REG_40H, 0x00400000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    HW_SCE_p_func102(0x8f759b69U, 0xc74283deU, 0x8666d871U, 0x62493441U);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    HW_SCE_p_func100(0xcf769527U, 0xe558fa1dU, 0x6731cb78U, 0x7354cbf8U);
                    WR1_PROG(REG_B0H, 0x00001828U);
                    WR1_PROG(REG_08H, 0x00006022U);
                    WAIT_STS(REG_08H, 30, 1);
                    RD8_ADDR(REG_2CH, &OutData_Signature[0]);

                    HW_SCE_p_func100(0x7c41474eU, 0xd5abc5d2U, 0xcc77457cU, 0x98c91fe0U);
                    WR1_PROG(REG_B0H, 0x0000181eU);
                    WR1_PROG(REG_08H, 0x00006022U);
                    WAIT_STS(REG_08H, 30, 1);
                    RD8_ADDR(REG_2CH, &OutData_Signature[8]);

                    HW_SCE_p_func102(0xf2a607a0U, 0xe0fa2a17U, 0x2dd7ee3cU, 0x834c99f2U);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
