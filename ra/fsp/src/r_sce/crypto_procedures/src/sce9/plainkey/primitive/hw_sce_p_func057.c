/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func057_r1 (uint32_t ARG1[], uint32_t ARG2[], uint32_t ARG3[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    static const uint32_t Param_func057_func100_001[] =
    {
        0xf31fc280U, 0xb1f04b9eU, 0x9454ff9bU, 0x9c90f37eU,
    };
    HW_SCE_p_func100(Param_func057_func100_001);
    WR1_PROG(REG_104H, 0x00000361U);
    WR1_PROG(REG_A4H, 0x00040805U);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &ARG1[0]);

    HW_SCE_p_func_sub021(0x00050804U);

    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

    HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
    WR1_PROG(REG_00H, 0x0000020fU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x000000ffU);

    static const uint32_t Param_func057_func101_001[] =
    {
        0xab47b184U, 0xfa6aa1bfU, 0x2f5a393fU, 0x383be959U,
    };
    HW_SCE_p_func101(Param_func057_func101_001);
    HW_SCE_p_func043();

    HW_SCE_p_func_sub005(0x000034e4U, 0x00000058U, 0x800103a0U, 0x000000feU);

    static const uint32_t Param_func057_func101_002[] =
    {
        0x8579d3eaU, 0x0270bbfcU, 0x83222df1U, 0x72d3673dU,
    };
    HW_SCE_p_func101(Param_func057_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_func057_func100_002[] =
    {
        0x09b4fe19U, 0xcd9e71faU, 0x41f1394cU, 0xd138ac96U,
    };
    HW_SCE_p_func100(Param_func057_func100_002);

    HW_SCE_p_func_sub012(0x00000052U, 0x00040804U, 0x00000000U);

    HW_SCE_p_func_sub012(0x00000052U, 0x00050804U, 0x00000000U);

    HW_SCE_p_func081();

    WR1_PROG(REG_ECH, 0x00007c01U);
    WR1_PROG(REG_1CH, 0x00600000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
    {
        static const uint32_t Param_func057_func100_003[] =
        {
            0xd863f335U, 0x104e1c40U, 0x70842eb1U, 0xa48e0ba2U,
        };
        HW_SCE_p_func100(Param_func057_func100_003);
        WR1_PROG(REG_00H, 0x80002100U);
        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_A4H, 0x00d049a6U);
        WR1_PROG(REG_D0H, 0x40000000U);
        WR1_PROG(REG_C4H, 0x02e087b6U);
        WR1_PROG(REG_04H, 0x0000c200U);

        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &ARG2[0]);
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 8); )
        {
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &ARG2[4 + iLoop]);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &ARG3[1 + iLoop]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &ARG3[1 + iLoop]);
        iLoop = iLoop + 4;
        oLoop = iLoop;

        HW_SCE_p_func202();

        static const uint32_t Param_func057_func101_003[] =
        {
            0x4ca67631U, 0xbfe8efa6U, 0x42650b01U, 0x9a59c797U,
        };
        HW_SCE_p_func101(Param_func057_func101_003);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x0a000000U)
    {
        static const uint32_t Param_func057_func100_004[] =
        {
            0xc39300fcU, 0x932823baU, 0xdc7a21f7U, 0x41e8b020U,
        };
        HW_SCE_p_func100(Param_func057_func100_004);
        WR1_PROG(REG_28H, 0x009f0001U);

        WR1_PROG(REG_00H, 0x00003183U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func061(0, ARG2);
        iLoop = 0 + 32;

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000024U);

        WR1_PROG(REG_D0H, 0x40000700U);
        WR1_PROG(REG_C4H, 0x02e08887U);
        WR1_PROG(REG_04H, 0x00000282U);

        for (oLoop = 0U; oLoop < 32U; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &ARG3[1 + oLoop]);
            oLoop = oLoop + 4;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_func057_func100_005[] =
        {
            0x4efe8e8aU, 0xfeed2dfcU, 0xdadb5c4aU, 0x65e1b33dU,
        };
        HW_SCE_p_func100(Param_func057_func100_005);
        WR1_PROG(REG_104H, 0x00000361U);
        WR1_PROG(REG_A4H, 0x00d049a5U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &ARG2[iLoop]);
        iLoop = iLoop + 4;

        WR1_PROG(REG_D0H, 0x40000000U);
        HW_SCE_p_func_sub013(0x00e08885U, 0x00002113U);
        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &ARG3[1 + oLoop]);

        WAIT_STS(REG_C8H, 6, 0);

        static const uint32_t Param_func057_func100_006[] =
        {
            0xa393ce95U, 0x386cc78fU, 0x4a0dde05U, 0x23b90198U,
        };
        HW_SCE_p_func100(Param_func057_func100_006);
        HW_SCE_p_func060();

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func062(36, ARG3);
        oLoop = 36 + 32;

        static const uint32_t Param_func057_func101_004[] =
        {
            0xb78e40beU, 0x9a507c58U, 0xa058119cU, 0x4604a55aU,
        };
        HW_SCE_p_func101(Param_func057_func101_004);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x0b000000U)
    {
        static const uint32_t Param_func057_func100_007[] =
        {
            0x0ec0ae03U, 0xbdb21de0U, 0x33e56e86U, 0x9376b996U,
        };
        HW_SCE_p_func100(Param_func057_func100_007);
        WR1_PROG(REG_28H, 0x009f0001U);

        WR1_PROG(REG_00H, 0x00003183U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func061(0, ARG2);
        iLoop = 0 + 32;

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000024U);
        HW_SCE_p_func062(0, ARG3);
        oLoop = 0 + 32;

        static const uint32_t Param_func057_func100_008[] =
        {
            0x04750e53U, 0x7952bb79U, 0xc5800b7eU, 0x403b9779U,
        };
        HW_SCE_p_func100(Param_func057_func100_008);
        WR1_PROG(REG_00H, 0x00003183U);
        WR1_PROG(REG_2CH, 0x00000011U);
        HW_SCE_p_func061(32, ARG2);
        iLoop = 32 + 32;

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000021U);
        HW_SCE_p_func062(32, ARG3);
        oLoop = 32 + 32;

        static const uint32_t Param_func057_func100_009[] =
        {
            0xf1f9707fU, 0x25d81b4fU, 0x22350d39U, 0x14f1ca2aU,
        };
        HW_SCE_p_func100(Param_func057_func100_009);
        HW_SCE_p_func060();

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func062(64, ARG3);
        oLoop = 64 + 32;

        static const uint32_t Param_func057_func101_005[] =
        {
            0x03dad023U, 0xcec3eca2U, 0xaa31e30fU, 0x45a27577U,
        };
        HW_SCE_p_func101(Param_func057_func101_005);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x0c000000U)
    {
        static const uint32_t Param_func057_func100_010[] =
        {
            0x40b8f383U, 0xcc74ecfdU, 0xa253bdf2U, 0x5d08ae64U,
        };
        HW_SCE_p_func100(Param_func057_func100_010);
        WR1_PROG(REG_28H, 0x00bf0001U);

        WR1_PROG(REG_00H, 0x00013103U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func063(0, ARG2);
        iLoop = 0 + 64;

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000024U);

        WR1_PROG(REG_D0H, 0x40000f00U);
        WR1_PROG(REG_C4H, 0x02e08887U);
        WR1_PROG(REG_04H, 0x00000202U);

        for (oLoop = 0U; oLoop < 64U; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &ARG3[1 + oLoop]);
            oLoop = oLoop + 4;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_func057_func100_011[] =
        {
            0xd5560200U, 0x28a09e8eU, 0xdf18a10aU, 0xa09ce3bdU,
        };
        HW_SCE_p_func100(Param_func057_func100_011);
        WR1_PROG(REG_104H, 0x00000361U);
        WR1_PROG(REG_A4H, 0x00d049a5U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &ARG2[iLoop]);
        iLoop = iLoop + 4;

        WR1_PROG(REG_D0H, 0x40000000U);
        HW_SCE_p_func_sub013(0x00e08885U, 0x00002113U);
        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &ARG3[1 + oLoop]);

        WAIT_STS(REG_C8H, 6, 0);

        static const uint32_t Param_func057_func100_012[] =
        {
            0xb55664d8U, 0xdda299b2U, 0xa618943dU, 0x763fa4a4U,
        };
        HW_SCE_p_func100(Param_func057_func100_012);
        HW_SCE_p_func060();

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func064(68, ARG3);
        oLoop = 68 + 64;

        static const uint32_t Param_func057_func101_006[] =
        {
            0x197c0cd4U, 0x2641e686U, 0xca561b5aU, 0x3a15237aU,
        };
        HW_SCE_p_func101(Param_func057_func101_006);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x0d000000U)
    {
        static const uint32_t Param_func057_func100_013[] =
        {
            0xbe980790U, 0x643b9dc7U, 0x163962b6U, 0xc3cc6613U,
        };
        HW_SCE_p_func100(Param_func057_func100_013);
        WR1_PROG(REG_28H, 0x00bf0001U);

        WR1_PROG(REG_00H, 0x00013103U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func063(0, ARG2);
        iLoop = 0 + 64;

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000024U);
        HW_SCE_p_func064(0, ARG3);
        oLoop = 0 + 64;

        static const uint32_t Param_func057_func100_014[] =
        {
            0x7e2b313aU, 0xa6926a4dU, 0x837b0236U, 0xe47c35d1U,
        };
        HW_SCE_p_func100(Param_func057_func100_014);

        WR1_PROG(REG_00H, 0x00013103U);
        WR1_PROG(REG_2CH, 0x00000010U);
        HW_SCE_p_func063(64, ARG2);
        iLoop = 64 + 64;

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000020U);
        HW_SCE_p_func064(64, ARG3);
        oLoop = 64 + 64;

        static const uint32_t Param_func057_func100_015[] =
        {
            0xee7b76e5U, 0xc6116ce8U, 0x9952521eU, 0xf6ef1e2fU,
        };
        HW_SCE_p_func100(Param_func057_func100_015);
        HW_SCE_p_func060();

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func064(128, ARG3);
        oLoop = 128 + 64;

        static const uint32_t Param_func057_func101_007[] =
        {
            0x0bbc011eU, 0x8bf07c60U, 0x4ce1e9aaU, 0x24601a0cU,
        };
        HW_SCE_p_func101(Param_func057_func101_007);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x12000000U)
    {
        static const uint32_t Param_func057_func100_016[] =
        {
            0xdb02e3c5U, 0x8f35d0d4U, 0xb1fca80fU, 0xd78d93b5U,
        };
        HW_SCE_p_func100(Param_func057_func100_016);
        WR1_PROG(REG_00H, 0x80002100U);
        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_A4H, 0x00d049a6U);
        WR1_PROG(REG_D0H, 0x40000000U);
        WR1_PROG(REG_C4H, 0x02e08886U);
        WR1_PROG(REG_04H, 0x0000c200U);

        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &ARG2[0]);
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 8); )
        {
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &ARG2[4 + iLoop]);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &ARG3[1 + iLoop]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &ARG3[1 + iLoop]);
        iLoop = iLoop + 4;
        oLoop = iLoop;

        HW_SCE_p_func202();

        static const uint32_t Param_func057_func101_008[] =
        {
            0x0052d385U, 0xd76d9a95U, 0x7739e2c2U, 0x966b5ef3U,
        };
        HW_SCE_p_func101(Param_func057_func101_008);
    }

    static const uint32_t Param_func057_func100_017[] =
    {
        0xd3371c6dU, 0xd24af252U, 0x239fe0dcU, 0x815b0e6cU,
    };
    HW_SCE_p_func100(Param_func057_func100_017);
    HW_SCE_p_func_sub012(0x00000052U, 0x00000c84U, 0x00000000U);

    WR1_PROG(REG_D0H, 0x40000000U);
    HW_SCE_p_func_sub013(0x000089c5U, 0x00002213U);
    WR1_PROG(REG_04H, 0x00000212U);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &ARG3[1 + oLoop]);

    WR1_PROG(REG_104H, 0x00000361U);
    WR1_PROG(REG_A4H, 0x000049a5U);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &ARG2[iLoop]);

    HW_SCE_p_func_sub019(0x00900c45U, 0x00001113U);

    WR1_PROG(REG_ECH, 0x00007c1cU);
    WR1_PROG(REG_1CH, 0x00602000U);
}
