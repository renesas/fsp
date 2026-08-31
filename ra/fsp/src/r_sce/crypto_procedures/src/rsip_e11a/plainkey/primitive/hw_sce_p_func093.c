/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func093_r1 (const uint32_t ARG1[], uint32_t ARG2[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    WR1_PROG(REG_94H, 0x00003467U);

    static const uint32_t Param_func093_func100_001[] =
    {
        0xf26d692cU, 0xcf9189b9U, 0x4a2543f1U, 0xef34ef74U,
    };
    HW_SCE_p_func100(Param_func093_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub002(0x03410005U);
    HW_SCE_p_func_sub002(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f093U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_func093_func101_001[] =
    {
        0x882ddb8fU, 0xa82250e6U, 0x8421c22dU, 0xae30cc4cU,
    };
    HW_SCE_p_func101(Param_func093_func101_001);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_94H, 0x000034c4U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f093U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_func093_func101_002[] =
    {
        0x93d95d2fU, 0x2cce36a1U, 0xbdddd971U, 0xedfdfabdU,
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
            0x72bfa833U, 0xff8cb213U, 0x8112c7cfU, 0x7fc571aaU,
        };
        HW_SCE_p_func100(Param_func093_func100_002);
        HW_SCE_p_func_sub008(0x000003c1U, 0x08000105U);
        WR4_ADDR(REG_2CH, &ARG1[iLoop]);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xe7008d05U);
        HW_SCE_p_func_sub002(0x00410011U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &ARG2[1 + iLoop]);

        static const uint32_t Param_func093_func101_003[] =
        {
            0xfa2b8363U, 0xfef991bdU, 0xf1631ffaU, 0xaa454934U,
        };
        HW_SCE_p_func101(Param_func093_func101_003);
        iLoop = iLoop + 4U;
    }

    oLoop = iLoop;

    static const uint32_t Param_func093_func100_003[] =
    {
        0xdd637773U, 0x4456a2f1U, 0xf4152398U, 0x895bad4dU,
    };
    HW_SCE_p_func100(Param_func093_func100_003);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub002(0x00410011U);
    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &ARG2[1 + oLoop]);

    WR1_PROG(REG_94H, 0x000034e3U);

    HW_SCE_p_func_sub015(0x00007c07U, 0x00602000U);
}
