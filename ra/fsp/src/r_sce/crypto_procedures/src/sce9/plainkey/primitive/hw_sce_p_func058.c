/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func058 (uint32_t ARG1[], uint32_t ARG2)
{
    static const uint32_t Param_func058_func100_001[] =
    {
        0xf09a7897U, 0xa3a7a023U, 0x3b7a61fdU, 0x362e6610U,
    };
    HW_SCE_p_func100(Param_func058_func100_001);
    WR1_PROG(REG_C4H, 0x00443a0cU);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_C4H, 0x000c3e1cU);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x0174d08aU));

    static const uint32_t Param_func058_func100_002[] =
    {
        0x884433ccU, 0x9a27dd57U, 0x8cdc7aa3U, 0xbb2d9912U,
    };
    HW_SCE_p_func100(Param_func058_func100_002);
    WR1_PROG(REG_ECH, 0x00009020U);
    WR1_PROG(REG_ECH, 0x01000000U);

    WR1_PROG(REG_C4H, 0x00440a0cU);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_C4H, 0x000c0e1cU);
    HW_SCE_p_func_sub010(0x81010020U, 0x00002807U);

    static const uint32_t Param_func058_func100_003[] =
    {
        0xa363e8a4U, 0x95c20c4fU, 0x7c0172d7U, 0xdab18365U,
    };
    HW_SCE_p_func100(Param_func058_func100_003);
    WR1_PROG(REG_A4H, 0x02fb073dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_FLASH2[ARG2]);

    static const uint32_t Param_func058_func100_004[] =
    {
        0xc113d43fU, 0x19520dc7U, 0x0b311f0aU, 0x07b8b3c5U,
    };
    HW_SCE_p_func100(Param_func058_func100_004);
    WR1_PROG(REG_A4H, 0x000007bdU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_FLASH2[ARG2 + 4]);

    HW_SCE_p_func_sub019(0x00800c45U, 0x00001113U);

    WR1_PROG(REG_104H, 0x00000361U);
    WR1_PROG(REG_A4H, 0x00087a05U);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &ARG1[0]);

    static const uint32_t Param_func058_func100_005[] =
    {
        0x81625709U, 0x8fa95ce2U, 0xa44190b7U, 0xe2458f05U,
    };
    HW_SCE_p_func100(Param_func058_func100_005);
    WR1_PROG(REG_104H, 0x00000361U);
    WR1_PROG(REG_A4H, 0x00097a05U);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &ARG1[4]);

    WR1_PROG(REG_ECH, 0x00007c1dU);
    WR1_PROG(REG_1CH, 0x00602000U);
}
