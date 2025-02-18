/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func058 (const uint32_t ARG1[], uint32_t ARG2)
{
    HW_SCE_p_func100(0xbbbfda21U, 0x17944ed0U, 0x0a552a41U, 0x49492666U);
    WR1_PROG(REG_D0H, 0x4a070044U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_D0H, 0x0e0704c4U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x017a1b82U));

    HW_SCE_p_func100(0x789979acU, 0x30731f75U, 0x9f18dd36U, 0xa2776335U);
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

    HW_SCE_p_func100(0x607b3f38U, 0xd59a5b21U, 0x23c741c9U, 0xabb8971dU);
    WR1_PROG(REG_D0H, 0xf7041c85U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &S_FLASH[ARG2]);

    HW_SCE_p_func100(0x40cc7015U, 0x5f864117U, 0x59d85843U, 0x9823a95dU);
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

    HW_SCE_p_func100(0xc37244c7U, 0x3ef27430U, 0xe87665dfU, 0x12ce27fbU);
    WR1_PROG(REG_14H, 0x000003c1U);
    WR1_PROG(REG_D0H, 0x0a0000bdU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[4]);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
    WR1_PROG(REG_24H, 0x00000000U);
}
