/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_PubKey[],
                                                uint32_t       OutData_R[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;

    if (RD1_MASK(REG_1B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00009b02U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_28H, 0x008b0001U);
    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010340U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_CurveType[0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x0000009bU);

    static const uint32_t Param_p9b_func101_001[] =
    {
        0x729ab639U, 0xfe0a0d1dU, 0x1e7fbae5U, 0x6d0e18e6U,
    };
    HW_SCE_p_func101(Param_p9b_func101_001);
    HW_SCE_p_func043();

    HW_SCE_p_func076();

    HW_SCE_p_func_sub005(0x000034feU, 0x00000058U, 0x800103a0U, 0x0000009bU);

    static const uint32_t Param_p9b_func101_002[] =
    {
        0xba343e79U, 0xfe31a1f3U, 0x7dbd0515U, 0xb71fd7baU,
    };
    HW_SCE_p_func101(Param_p9b_func101_002);
    HW_SCE_p_func044();

    WR1_PROG(REG_104H, 0x00000b62U);
    WR1_PROG(REG_D0H, 0x40000200U);
    WR1_PROG(REG_C4H, 0x02f087b7U);

    WR1_PROG(REG_00H, 0x00003233U);
    WR1_PROG(REG_2CH, 0x00000011U);

    for (iLoop = 0U; iLoop < 12U; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_p9b_func100_001[] =
    {
        0xa67b83a2U, 0xc869f5b9U, 0x79ac9b3aU, 0x05db1be5U,
    };
    HW_SCE_p_func100(Param_p9b_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p9b_func102_001[] =
        {
            0xf1c61cd6U, 0x638a9ff7U, 0x30d2fddfU, 0x66063230U,
        };
        HW_SCE_p_func102(Param_p9b_func102_001);
        WR1_PROG(REG_1B8H, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p9b_func100_002[] =
        {
            0x4d994ba1U, 0x0e83dd5fU, 0x1ad395aeU, 0xf05795a2U,
        };
        HW_SCE_p_func100(Param_p9b_func100_002);

        HW_SCE_p_func_sub022(0x38000f5aU, 0x00030020U, 0x0000b400U, 0x000002B4U);
        HW_SCE_p_func_sub022(0x00000060U, 0x0000b400U, 0x000003D8U, 0x00000080U);

        WR1_PROG(REG_E0H, 0x81010000U);
        WR1_PROG(REG_04H, 0x00000606U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);
        OFS_ADR  = S_RAM[0];

        static const uint32_t Param_p9b_func100_003[] =
        {
            0x7c3c2b42U, 0x77da4ba5U, 0xdd828a5fU, 0xf0ae4b81U,
        };
        HW_SCE_p_func100(Param_p9b_func100_003);
        HW_SCE_p_func027_r2(OFS_ADR);

        static const uint32_t Param_p9b_func100_004[] =
        {
            0xada38979U, 0x5574dcfbU, 0xcbcebb86U, 0x44cc9663U,
        };
        HW_SCE_p_func100(Param_p9b_func100_004);
        HW_SCE_p_func_sub001(0x0000dcd0U, 0x00000820U, 0x80009cd0U, 0x000084d0U);
        HW_SCE_p_func_sub023(0x00021028U, 0x100019b1U);

        HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x8000c0c1U, 0x00004404U);
        HW_SCE_p_func_sub006(0x0000e8d0U, 0x00000808U, 0x8000f0d0U);

        WR1_PROG(REG_2CH, 0x00000010U);
        WR1_PROG(REG_104H, 0x00000b67U);
        WAIT_STS(REG_104H, 31, 1);
        WR12_ADDR(REG_100H, &InData_PubKey[0]);
        HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
        HW_SCE_p_func_sub006(0x000019a1U, 0x00000800U, 0x800040c1U);
        WR1_PROG(REG_34H, 0x00000800U);
        WR1_PROG(REG_24H, 0x800080c1U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_2CH, 0x00000010U);
        WR1_PROG(REG_104H, 0x00000b67U);
        WAIT_STS(REG_104H, 31, 1);
        WR12_ADDR(REG_100H, &InData_PubKey[12]);
        HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
        HW_SCE_p_func_sub006(0x000019a1U, 0x00000800U, 0x800060c1U);
        WR1_PROG(REG_34H, 0x00000800U);
        WR1_PROG(REG_24H, 0x8000a0c1U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub002(0x00000bffU, 0x808c001fU, 0x00008333U, 0x00000021U);

        HW_SCE_p_func_sub022(0x00000bdeU, 0x00000842U, 0x0000b420U, 0x00000004U);

        HW_SCE_p_func_sub022(0x0000b480U, 0x00000180U, 0x0000b7a0U, 0x0000009bU);

        WR1_PROG(REG_ECH, 0x00000b9cU);

        WR1_PROG(REG_E0H, 0x81010380U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        for (iLoop = 0U; iLoop < 384; iLoop++)
        {
            static const uint32_t Param_p9b_func101_003[] =
            {
                0xd1a20304U, 0x7ec5a832U, 0xfe786d80U, 0x8db0ff21U,
            };
            HW_SCE_p_func101(Param_p9b_func101_003);
            HW_SCE_p_func300();

            if (S_RAM[0] == 0x00000001U)
            {
                break;
            }

            static const uint32_t Param_p9b_func101_004[] =
            {
                0xd89c8381U, 0xd1f4a61cU, 0x434fe417U, 0x7150d01dU,
            };
            HW_SCE_p_func101(Param_p9b_func101_004);
        }

        WR1_PROG(REG_24H, 0x00001dc0U);
        HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
        WR1_PROG(REG_1CH, 0x00210000U);

        static const uint32_t Param_p9b_func100_005[] =
        {
            0x62b875dcU, 0x77b1bd44U, 0x9da356ddU, 0x268018dbU,
        };
        HW_SCE_p_func100(Param_p9b_func100_005);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p9b_func102_002[] =
            {
                0x142493c0U, 0x7f78d4e0U, 0xc34d38b2U, 0x5166c60eU,
            };
            HW_SCE_p_func102(Param_p9b_func102_002);
            WR1_PROG(REG_1B8H, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub023(0x00001dc0U, 0x000080c1U);

            HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
            HW_SCE_p_func_sub023(0x00000591U, 0x0000a0c1U);

            WR1_PROG(REG_24H, 0x00005004U);
            HW_SCE_p_func_sub016(0x00008404U, 0x0000b420U);
            WR1_PROG(REG_ECH, 0x00000004U);

            HW_SCE_p_func_sub002(0x00000bffU, 0x808c001fU, 0x00008333U, 0x00000021U);

            for (iLoop = 0U; iLoop < 12U; iLoop++)
            {
                WR1_PROG(REG_ECH, 0x0000381fU);

                for (jLoop = 0U; jLoop < 32U; jLoop++)
                {
                    HW_SCE_p_func_sub023(0x0000102cU, 0x100019b1U);

                    WR1_PROG(REG_24H, 0x000019a1U);
                    HW_SCE_p_func_sub016(0x000080c1U, 0x3800d81fU);
                    WR1_PROG(REG_E0H, 0x00000080U);
                    WR1_PROG(REG_1CH, 0x00A60000U);

                    WR1_PROG(REG_ECH, 0x00016c00U);

                    static const uint32_t Param_p9b_func100_006[] =
                    {
                        0x6dfda009U, 0xdb9d8c6fU, 0x5f3558dfU, 0x4eeb90f1U,
                    };
                    HW_SCE_p_func100(Param_p9b_func100_006);
                    WR1_PROG(REG_1CH, 0x00400000U);
                    WR1_PROG(REG_1D0H, 0x00000000U);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                        HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                        static const uint32_t Param_p9b_func101_005[] =
                        {
                            0x97eb165fU, 0x003b8d10U, 0xd9f32031U, 0xa635451cU,
                        };
                        HW_SCE_p_func101(Param_p9b_func101_005);
                    }
                    else
                    {
                        static const uint32_t Param_p9b_func101_006[] =
                        {
                            0x3775974eU, 0xfd8b4302U, 0x33a3cd37U, 0x5bcc8a49U,
                        };
                        HW_SCE_p_func101(Param_p9b_func101_006);
                    }
                }

                WR1_PROG(REG_ECH, 0x000027e1U);

                static const uint32_t Param_p9b_func101_007[] =
                {
                    0xa93bfadeU, 0x9ae6845aU, 0x6ec11109U, 0x707f0125U,
                };
                HW_SCE_p_func101(Param_p9b_func101_007);
            }

            WR1_PROG(REG_ECH, 0x00008be0U);
            WR1_PROG(REG_ECH, 0x00000030U);

            WR1_PROG(REG_ECH, 0x00007c1fU);
            WR1_PROG(REG_1CH, 0x00602000U);

            HW_SCE_p_func301();

            static const uint32_t Param_p9b_func100_007[] =
            {
                0x036d9c54U, 0xe4a2ebc2U, 0x357cde20U, 0xd1165e27U,
            };
            HW_SCE_p_func100(Param_p9b_func100_007);
            WR1_PROG(REG_2CH, 0x00000022U);
            WR1_PROG(REG_04H, 0x00000332U);
            WAIT_STS(REG_04H, 30, 1);
            RD12_ADDR(REG_100H, &OutData_R[0]);

            static const uint32_t Param_p9b_func100_008[] =
            {
                0x05a57fffU, 0x0c4047f5U, 0xb8df91a5U, 0x33f572e9U,
            };
            HW_SCE_p_func100(Param_p9b_func100_008);
            WR1_PROG(REG_2CH, 0x00000023U);
            WR1_PROG(REG_04H, 0x00000332U);
            WAIT_STS(REG_04H, 30, 1);
            RD12_ADDR(REG_100H, &OutData_R[12]);

            static const uint32_t Param_p9b_func102_003[] =
            {
                0xd6535d3fU, 0x32ed02a4U, 0xf2ad998eU, 0x83ac46d5U,
            };
            HW_SCE_p_func102(Param_p9b_func102_003);
            WR1_PROG(REG_1B8H, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
