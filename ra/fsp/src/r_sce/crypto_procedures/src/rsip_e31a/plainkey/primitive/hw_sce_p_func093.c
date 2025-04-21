/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func093 (const uint32_t ARG1[], uint32_t ARG2[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    WR1_PROG(REG_94H, 0x00003467U);

    HW_SCE_p_func100(0x6e9a6593U, 0xf57d0f2fU, 0x17988c6aU, 0x86159419U);
    HW_SCE_p_func103();
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_9CH, 0x80010000U);
    WR1_PROG(REG_00H, 0x03410005U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_00H, 0x0001000dU);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_94H, 0x000034c0U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f093U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0xeb4aef99U, 0x5472bcdcU, 0x4608e035U, 0x16f28500U);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x000034c4U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f093U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0xca5d2be3U, 0x176939b6U, 0x501d9905U, 0xf5824c40U);
    HW_SCE_p_func044();

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x08000044U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x08000054U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    oLoop = 0U;
    for (iLoop = 0U; iLoop < (INST_DATA_SIZE); )
    {
        HW_SCE_p_func100(0x5cb0d313U, 0xa071bed5U, 0x39a37695U, 0xc161d80dU);
        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D0H, 0x08000105U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &ARG1[iLoop]);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xe7008d05U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &ARG2[1 + iLoop]);

        HW_SCE_p_func101(0x7af59531U, 0xa8e0ed94U, 0x99464b3eU, 0x7d07b0dcU);
        iLoop = iLoop + 4U;
    }

    oLoop = iLoop;

    HW_SCE_p_func100(0x2ac41436U, 0x6b49cb36U, 0x25218215U, 0x3a675d82U);
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c000104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &ARG2[1 + oLoop]);

    WR1_PROG(REG_94H, 0x000034e3U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
