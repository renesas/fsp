/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func441 (const uint32_t ARG1[], const uint32_t ARG2[])
{
    WR1_PROG(REG_94H, 0x00003467U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(0x5362e9aaU, 0xdf94cad7U, 0x89811c51U, 0x531fa2eaU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x800100c0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, ARG1[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000441U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x4c1f7a94U, 0xe14c9e3bU, 0x57b44f18U, 0x8f4d7965U);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x000034c5U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000441U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x944e4636U, 0x32c65948U, 0x2e924804U, 0x5e859e5fU);
        HW_SCE_p_func044();

        WR1_PROG(REG_14H, 0x000007c1U);
        WR1_PROG(REG_D4H, 0x40000100U);
        WR1_PROG(REG_D0H, 0xf7009d07U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &ARG1[1]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &ARG1[5]);

        WR1_PROG(REG_B0H, 0x0000141eU);
        WR1_PROG(REG_00H, 0x00c10021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &ARG1[9]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func101(0x437e5b64U, 0xc27d48b5U, 0x1fc92ab1U, 0x954d09a9U);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000007c5U);
        WR1_PROG(REG_B0H, 0x0000141eU);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &ARG2[0]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &ARG2[4]);

        HW_SCE_p_func101(0xcde689ecU, 0xb9778a59U, 0xe28e91bbU, 0x260b83d3U);
    }

    WR1_PROG(REG_94H, 0x000034e3U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
