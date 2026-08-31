/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func440 (const uint32_t ARG1[], const uint32_t ARG2[])
{
    HW_SCE_p_func_sub006(0x00003467U, 0x38000c00U, 0x00270000U);

    static const uint32_t Param_func440_func100_001[] =
    {
        0xde6f2827U, 0xa2470251U, 0xc7e44d6dU, 0x9e25ac14U,
    };
    HW_SCE_p_func100(Param_func440_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

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
            0x61df1cddU, 0xa81ec4dcU, 0x90036fdcU, 0x908db83cU,
        };
        HW_SCE_p_func101(Param_func440_func101_001);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x000034c5U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000440U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_func440_func101_002[] =
        {
            0x4a01c75fU, 0x348e57b3U, 0x77b09092U, 0x671af53fU,
        };
        HW_SCE_p_func101(Param_func440_func101_002);
        HW_SCE_p_func044();

        HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0xf7009d05U);
        WR4_ADDR(REG_2CH, &ARG1[1]);

        WR1_PROG(REG_B0H, 0x00000401U);
        HW_SCE_p_func_sub003(0x00c10009U);
        WR1_PROG(REG_B0H, 0x00000402U);
        HW_SCE_p_func_sub003(0x00c10009U);

        HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0x07008d05U);
        WR4_ADDR(REG_2CH, &ARG1[5]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        HW_SCE_p_func_sub003(0x00410011U);

        static const uint32_t Param_func440_func101_003[] =
        {
            0x403522c1U, 0x9b420366U, 0x78d96680U, 0xc9fcbfc4U,
        };
        HW_SCE_p_func101(Param_func440_func101_003);
    }
    else
    {
        HW_SCE_p_func_sub017(0x000003c5U, 0x00000401U);
        WR2_ADDR(REG_2CH, &ARG2[0]);
        WR1_PROG(REG_B0H, 0x00000402U);
        WAIT_STS(REG_14H, 31, 1);
        WR2_ADDR(REG_2CH, &ARG2[2]);

        static const uint32_t Param_func440_func101_004[] =
        {
            0xb74c4f6bU, 0x07e3beb2U, 0x27b49511U, 0x10662881U,
        };
        HW_SCE_p_func101(Param_func440_func101_004);
    }

    WR1_PROG(REG_94H, 0x000034e3U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
