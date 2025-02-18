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

    HW_SCE_p_func100(0xf26d692cU, 0xcf9189b9U, 0x4a2543f1U, 0xef34ef74U);
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

    HW_SCE_p_func101(0x882ddb8fU, 0xa82250e6U, 0x8421c22dU, 0xae30cc4cU);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x000034c4U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f093U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0xa95fe062U, 0xe0f1a48eU, 0xabeba203U, 0x95c81036U);
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
        HW_SCE_p_func100(0x72bfa833U, 0xff8cb213U, 0x8112c7cfU, 0x7fc571aaU);
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

        HW_SCE_p_func101(0xfa2b8363U, 0xfef991bdU, 0xf1631ffaU, 0xaa454934U);
		iLoop = iLoop + 4U;
    }

    oLoop = iLoop;

    HW_SCE_p_func100(0xdd637773U, 0x4456a2f1U, 0xf4152398U, 0x895bad4dU);
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
    WR1_PROG(REG_24H, 0x00000000U);
}
