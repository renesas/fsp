/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func440 (const uint32_t ARG1[], const uint32_t ARG2[])
{
    HW_SCE_p_func_sub006(0x00003467U, 0x38000c00U, 0x00260000U);

    static const uint32_t Param_func440_func100_001[] =
    {
        0xfad567bfU, 0xd8317754U, 0x7d886cf5U, 0x1f1c43b9U,
    };
    HW_SCE_p_func100(Param_func440_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func_sub005(0x000000c7U, 0x800100c0U);
        WR1_PROG(REG_2CH, ARG1[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000440U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_func440_func101_001[] =
        {
            0x3511ae49U, 0x20e9c61bU, 0xd73f8d08U, 0x7080a5ceU,
        };
        HW_SCE_p_func101(Param_func440_func101_001);
        HW_SCE_p_func043_r1();

        WR1_PROG(REG_94H, 0x000034c5U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000440U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_func440_func101_002[] =
        {
            0x0281e361U, 0x59b62b3fU, 0xcbca9bceU, 0xc0f75c0cU,
        };
        HW_SCE_p_func101(Param_func440_func101_002);
        HW_SCE_p_func044();

        HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0xf7009d05U);
        WR4_ADDR(REG_2CH, &ARG1[1]);

        WR1_PROG(REG_B0H, 0x00000401U);
        HW_SCE_p_func_sub002(0x00c10009U);
        WR1_PROG(REG_B0H, 0x00000402U);
        HW_SCE_p_func_sub002(0x00c10009U);

        HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0x07008d05U);
        WR4_ADDR(REG_2CH, &ARG1[5]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        HW_SCE_p_func_sub002(0x00410011U);

        static const uint32_t Param_func440_func101_003[] =
        {
            0x5ef7dae9U, 0x5df6057aU, 0x4eefb4d0U, 0x8aeda87bU,
        };
        HW_SCE_p_func101(Param_func440_func101_003);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000003c5U);
        WR1_PROG(REG_B0H, 0x00000401U);
        WAIT_STS(REG_14H, 31, 1);
        WR2_ADDR(REG_2CH, &ARG2[0]);
        WR1_PROG(REG_B0H, 0x00000402U);
        WAIT_STS(REG_14H, 31, 1);
        WR2_ADDR(REG_2CH, &ARG2[2]);

        static const uint32_t Param_func440_func101_004[] =
        {
            0xddbaf16eU, 0x3b791390U, 0xdd18f831U, 0xeead2c0eU,
        };
        HW_SCE_p_func101(Param_func440_func101_004);
    }

    WR1_PROG(REG_94H, 0x000034e3U);

    HW_SCE_p_func_sub015(0x00007c07U, 0x00602000U);
}
