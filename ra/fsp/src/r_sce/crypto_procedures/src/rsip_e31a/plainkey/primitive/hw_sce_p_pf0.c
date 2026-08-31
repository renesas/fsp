/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

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

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub001(0x3420a800U, 0x00000003U, 0x2000b400U, 0x00000002U);

    HW_SCE_p_func070(InData_DomainParam);

    static const uint32_t Param_pf0_func100_001[] =
    {
        0x163cc17dU, 0x7320319eU, 0x61df029cU, 0x73889bd7U,
    };
    HW_SCE_p_func100(Param_pf0_func100_001);

    WR1_PROG(REG_B0H, 0x0000140fU);
    HW_SCE_p_func103();
    static const uint32_t Param_pf0_func100_002[] =
    {
        0xa2653666U, 0x7bca9ad9U, 0xd3f82bbdU, 0xaac3d6bfU,
    };
    HW_SCE_p_func100(Param_pf0_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    WR1_PROG(REG_B0H, 0x00001428U);
    HW_SCE_p_func_sub003(0x00c0001dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

    WR1_PROG(REG_B0H, 0x00001419U);
    HW_SCE_p_func_sub003(0x00c0001dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

    HW_SCE_p_func_sub002(0x0019000aU, 0x00140000U, 0x0404000aU);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B8H, 0x00000014U);

    WR1_PROG(REG_A4H, 0x04040010U);

    HW_SCE_p_func_sub012();

    HW_SCE_p_func_sub002(0x0028000fU, 0x002d0014U, 0x04040002U);

    HW_SCE_p_func_sub002(0x0028002dU, 0x00320000U, 0x04040009U);

    HW_SCE_p_func071(InData_DomainParam);

    WR1_PROG(REG_94H, 0x00003420U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f0U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pf0_func101_001[] =
    {
        0x65fa125eU, 0xc9eb1085U, 0x0e1ad059U, 0x9cd8d4b5U,
    };
    HW_SCE_p_func101(Param_pf0_func101_001);
    HW_SCE_p_func088();

    static const uint32_t Param_pf0_func100_003[] =
    {
        0x72f3a9d9U, 0xa35ea6e7U, 0x472b6dd7U, 0x80388eedU,
    };
    HW_SCE_p_func100(Param_pf0_func100_003);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pf0_func102_001[] =
        {
            0xfdea0504U, 0x497a96adU, 0x4ea04cf0U, 0xf70d38f5U,
        };
        HW_SCE_p_func102(Param_pf0_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_B8H, 0x0000000aU);

        WR1_PROG(REG_A4H, 0x04040010U);

        HW_SCE_p_func_sub012();

        HW_SCE_p_func_sub002(0x005a0028U, 0x002d000aU, 0x04040002U);

        WR1_PROG(REG_14H, 0x000000a5U);
        WR1_PROG(REG_B0H, 0x0000140fU);
        HW_SCE_p_func_sub003(0x00c0001dU);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

        HW_SCE_p_func_sub002(0x000f002dU, 0x0028000aU, 0x04040002U);

        HW_SCE_p_func_sub002(0x000f0028U, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        static const uint32_t Param_pf0_func100_004[] =
        {
            0x78fe5066U, 0x20853a9fU, 0x08bb7ec5U, 0x59f15f60U,
        };
        HW_SCE_p_func100(Param_pf0_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_pf0_func102_002[] =
            {
                0x94ef55cbU, 0xc6016474U, 0x1002235fU, 0x33432705U,
            };
            HW_SCE_p_func102(Param_pf0_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            static const uint32_t Param_pf0_func100_005[] =
            {
                0x7d8779b5U, 0x93adecd9U, 0x33061924U, 0x7909f056U,
            };
            HW_SCE_p_func100(Param_pf0_func100_005);
            WR1_PROG(REG_B0H, 0x00001414U);
            HW_SCE_p_func_sub003(0x00c0001dU);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

            HW_SCE_p_func_sub002(0x0014000aU, 0x000f0000U, 0x0404000aU);

            HW_SCE_p_func_sub019(0x000f0032U, 0x0014000aU, 0x04040000U);
            HW_SCE_p_func_sub012();
            WR1_PROG(REG_40H, 0x00000d00U);

            HW_SCE_p_func_sub002(0x005a0014U, 0x000f000aU, 0x04040002U);

            HW_SCE_p_func_sub017(0x000007c5U, 0x00001414U);
            WR8_ADDR(REG_2CH, &InData_MsgDgst[0]);

            HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
            WR1_PROG(REG_2CH, InData_KeyMode[0]);
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func074();

            WR1_PROG(REG_94H, 0x000034a6U);

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x000000f0U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_pf0_func101_002[] =
            {
                0x9cc44df1U, 0x8b2ce20aU, 0x6cead866U, 0xd42327b3U,
            };
            HW_SCE_p_func101(Param_pf0_func101_002);
            HW_SCE_p_func441(InData_KeyIndex, InData_Key);

            static const uint32_t Param_pf0_func100_006[] =
            {
                0xa62e3c5fU, 0xe6de3d10U, 0xd91be5b3U, 0x50f84b39U,
            };
            HW_SCE_p_func100(Param_pf0_func100_006);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                static const uint32_t Param_pf0_func102_003[] =
                {
                    0xf7905899U, 0xa9756c56U, 0x73d377c6U, 0xe533792eU,
                };
                HW_SCE_p_func102(Param_pf0_func102_003);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
            }
            else
            {
                HW_SCE_p_func_sub002(0x005a001eU, 0x0019000aU, 0x04040002U);

                HW_SCE_p_func_sub002(0x00280019U, 0x001e000aU, 0x04040002U);

                HW_SCE_p_func_sub002(0x001e0014U, 0x0019000aU, 0x04040005U);

                HW_SCE_p_func_sub002(0x0019000fU, 0x001e000aU, 0x04040002U);

                WR1_PROG(REG_B0H, 0x0000140fU);
                HW_SCE_p_func_sub003(0x00c0001dU);
                HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

                HW_SCE_p_func_sub002(0x000f001eU, 0x00140000U, 0x0404000aU);

                WR1_PROG(REG_40H, 0x00210000U);

                static const uint32_t Param_pf0_func100_007[] =
                {
                    0x24976abfU, 0x02ca9173U, 0xee25215cU, 0x424831c4U,
                };
                HW_SCE_p_func100(Param_pf0_func100_007);
                WR1_PROG(REG_40H, 0x00400000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    static const uint32_t Param_pf0_func102_004[] =
                    {
                        0x9c940f98U, 0x4b40e51bU, 0xebb5ded4U, 0xd208cb83U,
                    };
                    HW_SCE_p_func102(Param_pf0_func102_004);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    static const uint32_t Param_pf0_func100_008[] =
                    {
                        0xc3bebe86U, 0x01e6d9f2U, 0x258c198cU, 0x3abc4d4bU,
                    };
                    HW_SCE_p_func100(Param_pf0_func100_008);
                    HW_SCE_p_func_sub015(0x00001828U, 0x00006022U);
                    RD8_ADDR(REG_2CH, &OutData_Signature[0]);

                    static const uint32_t Param_pf0_func100_009[] =
                    {
                        0x5cb1d8ceU, 0xe8823910U, 0xb268c2c0U, 0xeeb40fc5U,
                    };
                    HW_SCE_p_func100(Param_pf0_func100_009);
                    HW_SCE_p_func_sub015(0x0000181eU, 0x00006022U);
                    RD8_ADDR(REG_2CH, &OutData_Signature[8]);

                    static const uint32_t Param_pf0_func102_005[] =
                    {
                        0xaa7f86a9U, 0xf461362fU, 0x8f7338a3U, 0x68a99f53U,
                    };
                    HW_SCE_p_func102(Param_pf0_func102_005);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
