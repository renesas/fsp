/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func043_r1 (void)
{
    WR1_PROG(REG_A0H, 0x00010000U);

    static const uint32_t Param_func043_func100_001[] =
    {
        0x8e389e5eU, 0xbf24033dU, 0x7a882180U, 0x3de84865U,
    };
    HW_SCE_p_func100(Param_func043_func100_001);
    WR1_PROG(REG_B0H, 0x00001898U);
    WR1_PROG(REG_D0H, 0x08000085U);
    HW_SCE_p_func_sub002(0x00430011U);

    static const uint32_t Param_func043_func100_002[] =
    {
        0xc8abd055U, 0xaf022a14U, 0x43fe3a31U, 0x214b2c28U,
    };
    HW_SCE_p_func100(Param_func043_func100_002);
    WR1_PROG(REG_D0H, 0x08000095U);
    HW_SCE_p_func_sub002(0x00430011U);

    static const uint32_t Param_func043_func100_003[] =
    {
        0x693c97deU, 0x7c7819acU, 0x8f295defU, 0x361d0452U,
    };
    HW_SCE_p_func100(Param_func043_func100_003);

    WR1_PROG(REG_D0H, 0x080000c5U);
    WR1_PROG(REG_B0H, 0x00000893U);
    HW_SCE_p_func_sub002(0x00430009U);
    WR1_PROG(REG_B0H, 0x00000894U);
    HW_SCE_p_func_sub002(0x00430009U);

    WR1_PROG(REG_D0H, 0x0b040104U);
    WR1_PROG(REG_9CH, 0x810100c0U);
    HW_SCE_p_func_sub002(0x00490005U);

    WR1_PROG(REG_94H, 0x000008c6U);

    WR1_PROG(REG_9CH, 0x80840006U);
    HW_SCE_p_func_sub002(0x03410011U);

    HW_SCE_p_func_sub001(0x00003846U, 0x00008c40U, 0x00ffffffU);
    HW_SCE_p_func_sub001(0x00009040U, 0x01000000U, 0x00003c46U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x30009105U);
    WR1_PROG(REG_9CH, 0x81840006U);
    HW_SCE_p_func_sub002(0x00490011U);

    HW_SCE_p_func_sub001(0x00008c40U, 0x00ffffffU, 0x00009040U);
    WR1_PROG(REG_94H, 0x02000000U);
    WR1_PROG(REG_94H, 0x00003c46U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x30009045U);
    WR1_PROG(REG_9CH, 0x81840006U);
    HW_SCE_p_func_sub002(0x00490011U);

    static const uint32_t Param_func043_func100_004[] =
    {
        0xcf10af82U, 0xb2f9e4a8U, 0x71946456U, 0x5fb1057cU,
    };
    HW_SCE_p_func100(Param_func043_func100_004);
    WR1_PROG(REG_D0H, 0x08000085U);
    HW_SCE_p_func_sub002(0x00410011U);

    static const uint32_t Param_func043_func100_005[] =
    {
        0xe75b0a7cU, 0xb570b383U, 0xaf71a60bU, 0xee3a5f2eU,
    };
    HW_SCE_p_func100(Param_func043_func100_005);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000094U, 0x00000000U);

    HW_SCE_p_func_sub015(0x00007c07U, 0x00602000U);
}
