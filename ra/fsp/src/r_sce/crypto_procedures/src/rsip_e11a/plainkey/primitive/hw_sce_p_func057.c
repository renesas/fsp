/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func057 (const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    WR1_PROG(REG_94H, 0x00003467U);

    WR1_PROG(REG_14H, 0x000003c1U);
    WR1_PROG(REG_D0H, 0x08000065U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[0]);

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x08000074U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_94H, 0x000034c0U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f057U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x4c437ef4U, 0xf183082bU, 0x036cbc0bU, 0xb2679d51U);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x000034c4U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x0000f057U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0xf06e7e8fU, 0xcd47bb6eU, 0xcb0f84e9U, 0x2caf947aU);
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
    for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); )
    {
        HW_SCE_p_func100(0x3cb9c1e8U, 0xe3a43a93U, 0xdc4c8215U, 0x835fe270U);
        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D0H, 0xd922090dU);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &ARG2[iLoop]);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xe7008d05U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &ARG3[1 + iLoop]);

        HW_SCE_p_func101(0x38335429U, 0x6f036347U, 0x64ebe0a6U, 0x729068d1U);
	    iLoop = iLoop + 4U;
    }

    oLoop = iLoop;

    HW_SCE_p_func100(0x1f39ac92U, 0xcb5c9da3U, 0x4559a597U, 0x6f7a7f61U);
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
    RD4_ADDR(REG_2CH, &ARG3[1 + oLoop]);

    WR1_PROG(REG_14H, 0x000003c1U);
    WR1_PROG(REG_D0H, 0x0922090dU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG2[iLoop]);

    WR1_PROG(REG_D0H, 0x9c300005U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_94H, 0x000034e3U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
    WR1_PROG(REG_24H, 0x00000000U);
}
