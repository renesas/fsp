/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func316 (void)
{
    uint32_t oLoop2 = 0U;

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    WR1_PROG(REG_ECH, 0x0000000cU);
    WR1_PROG(REG_ECH, 0x00003fbeU);

    WR1_PROG(REG_28H, 0x009f0001U);
    WR1_PROG(REG_ECH, 0x0000d779U);

    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_E0H, 0x80010300U);
    HW_SCE_p_func_sub011(0x00008307U, 0x000000acU);
    WR1_PROG(REG_00H, 0x0000031fU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
    WR1_PROG(REG_24H, 0x0000e0d0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_28H, 0x009f0001U);

    WR1_PROG(REG_ECH, 0x3800db1fU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00260000U);

    static const uint32_t Param_func316_func100_001[] =
    {
        0x8dd5b077U, 0xd50c776fU, 0x9d162b11U, 0xab952327U,
    };
    HW_SCE_p_func100(Param_func316_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_28H, 0x00a70001U);
        WR1_PROG(REG_24H, 0x000001c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_28H, 0x00870001U);
        WR1_PROG(REG_24H, 0x00000682U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_28H, 0x00a70001U);
        WR1_PROG(REG_24H, 0x00001991U);
        HW_SCE_p_func_sub016(0x0000c0c1U, 0x0000d379U);

        static const uint32_t Param_func316_func101_001[] =
        {
            0x1eb5c006U, 0x14f8b611U, 0x3c79c58bU, 0x2b91f0c0U,
        };
        HW_SCE_p_func101(Param_func316_func101_001);
    }

    HW_SCE_p_func_sub022(0x0000b7e0U, 0x0000001cU, 0x0000b7a0U, 0x000000f0U);
    static const uint32_t Param_func316_func101_002[] =
    {
        0x2d145c92U, 0x70901d38U, 0x611110efU, 0x988983bfU,
    };
    HW_SCE_p_func101(Param_func316_func101_002);
    HW_SCE_p_func317();

    WR1_PROG(REG_ECH, 0x00003759U);

    WR1_PROG(REG_24H, 0x000050d0U);
    HW_SCE_p_func_sub016(0x000080c1U, 0x0000b7e0U);
    WR1_PROG(REG_ECH, 0x0000001dU);

    WR1_PROG(REG_ECH, 0x0000b7a0U);
    WR1_PROG(REG_ECH, 0x000000f1U);
    static const uint32_t Param_func316_func101_003[] =
    {
        0x82531a33U, 0xa8d87c8fU, 0x6ac862c0U, 0x734e49c8U,
    };
    HW_SCE_p_func101(Param_func316_func101_003);
    HW_SCE_p_func317();

    WR1_PROG(REG_24H, 0x000050d0U);
    HW_SCE_p_func_sub015(0x000080c1U, 0x009f0001U);

    HW_SCE_p_func_sub023(0x0000b0d0U, 0x0000082cU);
    WR1_PROG(REG_24H, 0x100019b1U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1U);
    HW_SCE_p_func_sub015(0x000060c1U, 0x00870001U);
    WR1_PROG(REG_34H, 0x00000c00U);
    HW_SCE_p_func_sub001(0x8000ecd0U, 0x00000800U, 0x8000f0d0U, 0x00007cd0U);
    WR1_PROG(REG_24H, 0x0000bcd0U);
    HW_SCE_p_func_sub015(0x0000e4d0U, 0x00a00001U);
    HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
    WR1_PROG(REG_24H, 0x000019a1U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1U);
    HW_SCE_p_func_sub015(0x000011c0U, 0x00a70001U);
    for (oLoop2 = 0; oLoop2 < 32; oLoop2 = oLoop2 + 1)
    {
        HW_SCE_p_func_sub023(0x00000189U, 0x100019b1U);
        WR1_PROG(REG_24H, 0x000019a1U);
        WAIT_STS(REG_24H, 21, 0);
    }

    WR1_PROG(REG_24H, 0x000080c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_34H, 0x00000030U);
    WR1_PROG(REG_24H, 0x80007cd0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000002c0U);
    HW_SCE_p_func_sub015(0x0000e0d0U, 0x009f0001U);
    WR1_PROG(REG_24H, 0x00000dc0U);
    WAIT_STS(REG_24H, 21, 0);

    HW_SCE_p_func_sub020(0x00a00001U, 0x00001151U, 0x000080c1U);
    HW_SCE_p_func_sub017(0x00001991U, 0x00210000U);

    static const uint32_t Param_func316_func100_002[] =
    {
        0x511e8e8eU, 0xd9e12ddbU, 0xf22bed32U, 0x73de2ff2U,
    };
    HW_SCE_p_func100(Param_func316_func100_002);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_24H, 0x00001981U);
        WAIT_STS(REG_24H, 21, 0);

        static const uint32_t Param_func316_func101_004[] =
        {
            0x1e68f2e3U, 0xb5e7bbfcU, 0x18236343U, 0xecce8c56U,
        };
        HW_SCE_p_func101(Param_func316_func101_004);
    }
    else
    {
        WR1_PROG(REG_24H, 0x000080c1U);
        HW_SCE_p_func_sub015(0x000001c0U, 0x00870001U);
        WR1_PROG(REG_24H, 0x000006c0U);
        WAIT_STS(REG_24H, 21, 0);
        HW_SCE_p_func_sub020(0x00a00001U, 0x040091c1U, 0x00001191U);
        WAIT_STS(REG_24H, 21, 0);

        static const uint32_t Param_func316_func101_005[] =
        {
            0x91b9177bU, 0xc40e686dU, 0xce3d3442U, 0x8db507f8U,
        };
        HW_SCE_p_func101(Param_func316_func101_005);
    }

    WR1_PROG(REG_24H, 0x000080c1U);
    HW_SCE_p_func_sub015(0x000001c0U, 0x00870001U);
    WR1_PROG(REG_24H, 0x000006c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_28H, 0x00a00001U);

    WR1_PROG(REG_24H, 0x00001181U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00210000U);

    static const uint32_t Param_func316_func100_003[] =
    {
        0xffb51ee1U, 0x2551d008U, 0x419923a9U, 0xa6a91ad0U,
    };
    HW_SCE_p_func100(Param_func316_func100_003);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_24H, 0x00001981U);
        WAIT_STS(REG_24H, 21, 0);

        static const uint32_t Param_func316_func101_006[] =
        {
            0x8bafbae7U, 0xcc319b8eU, 0x09db8e30U, 0x6719a39aU,
        };
        HW_SCE_p_func101(Param_func316_func101_006);
    }
    else
    {
        WR1_PROG(REG_24H, 0x000080c1U);
        HW_SCE_p_func_sub015(0x000001c0U, 0x00870001U);
        WR1_PROG(REG_24H, 0x000006c0U);
        WAIT_STS(REG_24H, 21, 0);
        HW_SCE_p_func_sub020(0x00a00001U, 0x040091c1U, 0x00001191U);
        WAIT_STS(REG_24H, 21, 0);

        static const uint32_t Param_func316_func101_007[] =
        {
            0x4ee65c47U, 0x1e802413U, 0xe499d1a8U, 0xdb8fab6aU,
        };
        HW_SCE_p_func101(Param_func316_func101_007);
    }

    WR1_PROG(REG_24H, 0x000080c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x3800db20U);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00A60000U);

    static const uint32_t Param_func316_func100_004[] =
    {
        0x1d570422U, 0xba2e8875U, 0x4417d7b7U, 0x75e2ba4aU,
    };
    HW_SCE_p_func100(Param_func316_func100_004);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_24H, 0x000009c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_28H, 0x00870001U);
        WR1_PROG(REG_24H, 0x000002c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_28H, 0x00a00001U);
        WR1_PROG(REG_24H, 0x00001181U);
        HW_SCE_p_func_sub015(0x000080c1U, 0x009f0001U);
        WR1_PROG(REG_24H, 0x000015c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_28H, 0x00870001U);
        HW_SCE_p_func_sub006(0x000002c0U, 0x00000020U, 0x80001dc0U);
        HW_SCE_p_func_sub020(0x00a00001U, 0x00001981U, 0x0000c0c1U);
        WAIT_STS(REG_24H, 21, 0);

        static const uint32_t Param_func316_func101_008[] =
        {
            0x5930a123U, 0xe735b3d5U, 0xc4d172b9U, 0x05e9d5b3U,
        };
        HW_SCE_p_func101(Param_func316_func101_008);
    }
    else
    {
        WR1_PROG(REG_28H, 0x009f0001U);
        WR1_PROG(REG_24H, 0x0000d4d0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_28H, 0x00870001U);
        WR1_PROG(REG_34H, 0x00000020U);
        HW_SCE_p_func_sub023(0x8000dcd0U, 0x0000e0d0U);

        static const uint32_t Param_func316_func101_009[] =
        {
            0xaa453373U, 0xe70c1f7bU, 0x2794ae86U, 0x1e04ffb8U,
        };
        HW_SCE_p_func101(Param_func316_func101_009);
    }

    WR1_PROG(REG_28H, 0x009f0001U);
    WR1_PROG(REG_24H, 0x00004cd0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_24H, 0x000060d0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00a00001U);
    WR1_PROG(REG_24H, 0x000011c0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x00000bffU);

    static const uint32_t Param_func316_func100_005[] =
    {
        0x1424e022U, 0x37343771U, 0xa0416005U, 0x010b4e36U,
    };
    HW_SCE_p_func100(Param_func316_func100_005);
    WR1_PROG(REG_E0H, 0x81010340U);
    WR1_PROG(REG_04H, 0x00000607U);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);
    S_RAM[0] = change_endian_long(S_RAM[0]);

    WR1_PROG(REG_ECH, 0x3800db7cU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00A60000U);

    static const uint32_t Param_func316_func100_006[] =
    {
        0xd4918aa4U, 0x20669ad3U, 0x6d1f6b3fU, 0x6459ad47U,
    };
    HW_SCE_p_func100(Param_func316_func100_006);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            WR1_PROG(REG_24H, 0x00001991U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_ECH, 0x00002fe0U);

            static const uint32_t Param_func316_func101_010[] =
            {
                0xb7698563U, 0x1d329d6bU, 0x968a2dceU, 0xd32a5eadU,
            };
            HW_SCE_p_func101(Param_func316_func101_010);
        }

        static const uint32_t Param_func316_func101_011[] =
        {
            0x8cfc7f48U, 0x1596a76dU, 0xe304f64aU, 0xe359ab67U,
        };
        HW_SCE_p_func101(Param_func316_func101_011);
    }
    else
    {
        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            WR1_PROG(REG_24H, 0x00001981U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_ECH, 0x00002fe0U);

            static const uint32_t Param_func316_func101_012[] =
            {
                0x4e152c24U, 0xe90797beU, 0x172490f0U, 0x260bc8bcU,
            };
            HW_SCE_p_func101(Param_func316_func101_012);
        }

        static const uint32_t Param_func316_func101_013[] =
        {
            0xb6fea3f5U, 0x85e41681U, 0xb3f14e96U, 0x5022aeefU,
        };
        HW_SCE_p_func101(Param_func316_func101_013);
    }

    WR1_PROG(REG_ECH, 0x38000b5fU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00260000U);
    WR1_PROG(REG_1CH, 0x00402000U);

    WR1_PROG(REG_24H, 0x000080c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x3800db79U);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00A60000U);

    static const uint32_t Param_func316_func100_007[] =
    {
        0x40f924e5U, 0xc4f5438dU, 0xb74cc091U, 0xf662ab19U,
    };
    HW_SCE_p_func100(Param_func316_func100_007);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_24H, 0x000001c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00001191U);
        HW_SCE_p_func_sub015(0x000080c1U, 0x00a00001U);
        HW_SCE_p_func_sub023(0x000009c0U, 0x00001191U);
        WR1_PROG(REG_24H, 0x000040c1U);
        WAIT_STS(REG_24H, 21, 0);

        static const uint32_t Param_func316_func101_014[] =
        {
            0x0270d572U, 0x600e206bU, 0x72b67275U, 0xfd7bff07U,
        };
        HW_SCE_p_func101(Param_func316_func101_014);
    }
    else
    {
        static const uint32_t Param_func316_func101_015[] =
        {
            0x145e3f7dU, 0x4bd25dc4U, 0x94ed56edU, 0x32ddd531U,
        };
        HW_SCE_p_func101(Param_func316_func101_015);
    }

    HW_SCE_p_func_sub022(0x0000b7c0U, 0x0000000cU, 0x00003bbeU, 0x00007c1dU);
    WR1_PROG(REG_1CH, 0x00602000U);
}
