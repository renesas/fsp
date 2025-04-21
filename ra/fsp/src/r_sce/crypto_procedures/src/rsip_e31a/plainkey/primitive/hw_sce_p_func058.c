/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func058 (const uint32_t ARG1[], uint32_t ARG2)
{
    HW_SCE_p_func100(0x0f95746fU, 0x781a477aU, 0x9cafd5cdU, 0x42d13ba4U);
    WR1_PROG(REG_D0H, 0x4a070044U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_D0H, 0x0e0704c4U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x01b16437U));

    HW_SCE_p_func100(0xcc1df52fU, 0xe605691cU, 0x094df5bdU, 0xcd7a1a77U);
    WR1_PROG(REG_94H, 0x00009020U);
    WR1_PROG(REG_94H, 0x01000000U);

    WR1_PROG(REG_D0H, 0x4a040044U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_D0H, 0x0e0404c4U);
    WR1_PROG(REG_9CH, 0x81010020U);
    WR1_PROG(REG_00H, 0x00490005U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    HW_SCE_p_func100(0x48951875U, 0x1eb64374U, 0x3baa9eb7U, 0x6a3f644bU);
    WR1_PROG(REG_D0H, 0xf7041c85U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &S_FLASH[ARG2]);

    HW_SCE_p_func100(0x185add42U, 0xc99eac3aU, 0xd47d014fU, 0xf5acaab0U);
    WR1_PROG(REG_D0H, 0x07040d05U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &S_FLASH[ARG2 + 4]);

    WR1_PROG(REG_D0H, 0x8c100005U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_14H, 0x000003c1U);
    WR1_PROG(REG_D0H, 0x0a0000adU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[0]);

    HW_SCE_p_func100(0x0d63cf81U, 0x54e7746bU, 0xa8926355U, 0xc495d02eU);
    WR1_PROG(REG_14H, 0x000003c1U);
    WR1_PROG(REG_D0H, 0x0a0000bdU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[4]);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
