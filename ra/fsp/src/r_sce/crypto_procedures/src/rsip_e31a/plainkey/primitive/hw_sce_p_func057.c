/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func057 (const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    WR1_PROG(REG_94H, 0x00003467U);

    HW_SCE_p_func_sub011(0x000003c1U, 0x08000065U);
    WR4_ADDR(REG_2CH, &ARG1[0]);

    HW_SCE_p_func_sub004(0x000000a1U, 0x08000074U, 0x00000000U);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f057U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_func057_func101_001[] =
    {
        0xb7279142U, 0xeb3a0fc4U, 0xa84aeb8cU, 0x60f2cb11U,
    };
    HW_SCE_p_func101(Param_func057_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x000034c4U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f057U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_func057_func101_002[] =
    {
        0xa8e27b98U, 0x07e332edU, 0xcdc51840U, 0x0e25c1c7U,
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
            0x9d4467e3U, 0x6af5b59aU, 0xca9cf05eU, 0x98652b59U,
        };
        HW_SCE_p_func100(Param_func057_func100_001);
        HW_SCE_p_func_sub011(0x000003c1U, 0xd922090dU);
        WR4_ADDR(REG_2CH, &ARG2[iLoop]);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xe7008d05U);
        HW_SCE_p_func_sub003(0x00410011U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &ARG3[1 + iLoop]);

        static const uint32_t Param_func057_func101_003[] =
        {
            0x03764098U, 0x8ed5324eU, 0x93d7ca31U, 0xaab000fbU,
        };
        HW_SCE_p_func101(Param_func057_func101_003);
        iLoop = iLoop + 4U;
    }

    oLoop = iLoop;

    static const uint32_t Param_func057_func100_002[] =
    {
        0x6ddd675fU, 0xdd86e307U, 0x0b96b5d5U, 0x91b3f744U,
    };
    HW_SCE_p_func100(Param_func057_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);
    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &ARG3[1 + oLoop]);

    HW_SCE_p_func_sub011(0x000003c1U, 0x0922090dU);
    WR4_ADDR(REG_2CH, &ARG2[iLoop]);

    WR1_PROG(REG_D0H, 0x9c300005U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_94H, 0x000034e3U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
