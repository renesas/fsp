/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func043 (void)
{
    WR1_PROG(REG_A0H, 0x00010000U);

    static const uint32_t Param_func043_func100_001[] =
    {
        0x59a3c2c5U, 0x13732de0U, 0x35332b22U, 0xea0dddd9U,
    };
    HW_SCE_p_func100(Param_func043_func100_001);
    WR1_PROG(REG_B0H, 0x000018b8U);
    WR1_PROG(REG_D0H, 0x08000085U);
    HW_SCE_p_func_sub003(0x00430011U);

    static const uint32_t Param_func043_func100_002[] =
    {
        0x69c8b1b2U, 0xe50345e1U, 0x9be36b6cU, 0xd923a03eU,
    };
    HW_SCE_p_func100(Param_func043_func100_002);
    WR1_PROG(REG_D0H, 0x08000095U);
    HW_SCE_p_func_sub003(0x00430011U);

    static const uint32_t Param_func043_func100_003[] =
    {
        0x1ac9d401U, 0x53e0f859U, 0x27570086U, 0xab75570bU,
    };
    HW_SCE_p_func100(Param_func043_func100_003);

    WR1_PROG(REG_D0H, 0x080000c5U);
    WR1_PROG(REG_B0H, 0x000008b3U);
    HW_SCE_p_func_sub003(0x00430009U);
    WR1_PROG(REG_B0H, 0x000008b4U);
    HW_SCE_p_func_sub003(0x00430009U);

    WR1_PROG(REG_D0H, 0x0b040104U);
    WR1_PROG(REG_9CH, 0x810100c0U);
    HW_SCE_p_func_sub003(0x00490005U);

    WR1_PROG(REG_94H, 0x000008c6U);

    WR1_PROG(REG_9CH, 0x80840006U);
    HW_SCE_p_func_sub003(0x03410011U);

    HW_SCE_p_func_sub001(0x00003846U, 0x00008c40U, 0x00ffffffU, 0x00009040U);
    WR1_PROG(REG_94H, 0x01000000U);
    WR1_PROG(REG_94H, 0x00003c46U);

    HW_SCE_p_func_sub021(0x40000000U, 0x30009105U, 0x81840006U);
    HW_SCE_p_func_sub003(0x00490011U);

    HW_SCE_p_func_sub001(0x00008c40U, 0x00ffffffU, 0x00009040U, 0x02000000U);
    WR1_PROG(REG_94H, 0x00003c46U);

    HW_SCE_p_func_sub021(0x40000000U, 0x30009045U, 0x81840006U);
    HW_SCE_p_func_sub003(0x00490011U);

    static const uint32_t Param_func043_func100_004[] =
    {
        0x2b606db4U, 0xd3e66ad5U, 0xee3b4d15U, 0x2274f27dU,
    };
    HW_SCE_p_func100(Param_func043_func100_004);
    WR1_PROG(REG_D0H, 0x08000085U);
    HW_SCE_p_func_sub003(0x00410011U);

    static const uint32_t Param_func043_func100_005[] =
    {
        0x16e4d947U, 0xe5f4c0c4U, 0x3e438ba4U, 0xf5b079abU,
    };
    HW_SCE_p_func100(Param_func043_func100_005);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000094U, 0x00000000U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
