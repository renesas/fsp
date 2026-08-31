/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func093 (const uint32_t ARG1[], uint32_t ARG2[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    WR1_PROG(REG_94H, 0x00003467U);

    static const uint32_t Param_func093_func100_001[] =
    {
        0x6e9a6593U, 0xf57d0f2fU, 0x17988c6aU, 0x86159419U,
    };
    HW_SCE_p_func100(Param_func093_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub003(0x03410005U);
    HW_SCE_p_func_sub003(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f093U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_func093_func101_001[] =
    {
        0xeb4aef99U, 0x5472bcdcU, 0x4608e035U, 0x16f28500U,
    };
    HW_SCE_p_func101(Param_func093_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x000034c4U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f093U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_func093_func101_002[] =
    {
        0xca5d2be3U, 0x176939b6U, 0x501d9905U, 0xf5824c40U,
    };
    HW_SCE_p_func101(Param_func093_func101_002);
    HW_SCE_p_func044();

    HW_SCE_p_func_sub004(0x000000a1U, 0x08000044U, 0x00000000U);

    HW_SCE_p_func_sub004(0x000000a1U, 0x08000054U, 0x00000000U);

    oLoop = 0U;
    for (iLoop = 0U; iLoop < (INST_DATA_SIZE); )
    {
        static const uint32_t Param_func093_func100_002[] =
        {
            0x5cb0d313U, 0xa071bed5U, 0x39a37695U, 0xc161d80dU,
        };
        HW_SCE_p_func100(Param_func093_func100_002);
        HW_SCE_p_func_sub011(0x000003c1U, 0x08000105U);
        WR4_ADDR(REG_2CH, &ARG1[iLoop]);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xe7008d05U);
        HW_SCE_p_func_sub003(0x00410011U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &ARG2[1 + iLoop]);

        static const uint32_t Param_func093_func101_003[] =
        {
            0x7af59531U, 0xa8e0ed94U, 0x99464b3eU, 0x7d07b0dcU,
        };
        HW_SCE_p_func101(Param_func093_func101_003);
        iLoop = iLoop + 4U;
    }

    oLoop = iLoop;

    static const uint32_t Param_func093_func100_003[] =
    {
        0x2ac41436U, 0x6b49cb36U, 0x25218215U, 0x3a675d82U,
    };
    HW_SCE_p_func100(Param_func093_func100_003);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);
    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &ARG2[1 + oLoop]);

    WR1_PROG(REG_94H, 0x000034e3U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
