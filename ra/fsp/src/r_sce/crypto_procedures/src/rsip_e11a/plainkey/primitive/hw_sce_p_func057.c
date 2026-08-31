/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func057_r1 (const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    WR1_PROG(REG_94H, 0x00003467U);

    HW_SCE_p_func_sub008(0x000003c1U, 0x08000065U);
    WR4_ADDR(REG_2CH, &ARG1[0]);

    HW_SCE_p_func_sub004(0x000000a1U, 0x08000074U, 0x00000000U);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f057U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_func057_func101_001[] =
    {
        0x4c437ef4U, 0xf183082bU, 0x036cbc0bU, 0xb2679d51U,
    };
    HW_SCE_p_func101(Param_func057_func101_001);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_94H, 0x000034c4U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f057U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_func057_func101_002[] =
    {
        0xeea8a3b0U, 0x330566eaU, 0xadb2cd17U, 0x9c29c374U,
    };
    HW_SCE_p_func101(Param_func057_func101_002);
    HW_SCE_p_func044();

    HW_SCE_p_func_sub004(0x000000a1U, 0x08000044U, 0x00000000U);

    HW_SCE_p_func_sub004(0x000000a1U, 0x08000054U, 0x00000000U);

    oLoop = 0U;
    for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); )
    {
        static const uint32_t Param_func057_func100_001[] =
        {
            0x3cb9c1e8U, 0xe3a43a93U, 0xdc4c8215U, 0x835fe270U,
        };
        HW_SCE_p_func100(Param_func057_func100_001);
        HW_SCE_p_func_sub008(0x000003c1U, 0xd922090dU);
        WR4_ADDR(REG_2CH, &ARG2[iLoop]);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xe7008d05U);
        HW_SCE_p_func_sub002(0x00410011U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &ARG3[1 + iLoop]);

        static const uint32_t Param_func057_func101_003[] =
        {
            0x38335429U, 0x6f036347U, 0x64ebe0a6U, 0x729068d1U,
        };
        HW_SCE_p_func101(Param_func057_func101_003);
        iLoop = iLoop + 4U;
    }

    oLoop = iLoop;

    static const uint32_t Param_func057_func100_002[] =
    {
        0x1f39ac92U, 0xcb5c9da3U, 0x4559a597U, 0x6f7a7f61U,
    };
    HW_SCE_p_func100(Param_func057_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub002(0x00410011U);
    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &ARG3[1 + oLoop]);

    HW_SCE_p_func_sub008(0x000003c1U, 0x0922090dU);
    WR4_ADDR(REG_2CH, &ARG2[iLoop]);

    WR1_PROG(REG_D0H, 0x9c300005U);
    HW_SCE_p_func_sub002(0x00410011U);

    WR1_PROG(REG_94H, 0x000034e3U);

    HW_SCE_p_func_sub015(0x00007c07U, 0x00602000U);
}
