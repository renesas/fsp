/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func044 (void)
{
    HW_SCE_p_func_sub001(0x00008cc0U, 0x00ffffffU, 0x000090c0U);
    WR1_PROG(REG_94H, 0x01000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x30009104U);
    WR1_PROG(REG_9CH, 0x810100c0U);
    HW_SCE_p_func_sub002(0x00490005U);

    HW_SCE_p_func_sub001(0x00008cc0U, 0x00ffffffU, 0x000090c0U);
    WR1_PROG(REG_94H, 0x02000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x30009044U);
    WR1_PROG(REG_9CH, 0x810100c0U);
    HW_SCE_p_func_sub002(0x00490005U);

    static const uint32_t Param_func044_func100_001[] =
    {
        0x557291dfU, 0xab11119fU, 0x8e2ea344U, 0x6ec6e690U,
    };
    HW_SCE_p_func100(Param_func044_func100_001);
    WR1_PROG(REG_D0H, 0x08000085U);
    HW_SCE_p_func_sub002(0x00410011U);

    static const uint32_t Param_func044_func100_002[] =
    {
        0xd49ae696U, 0x6384130bU, 0xb60237f3U, 0x6cb3510aU,
    };
    HW_SCE_p_func100(Param_func044_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000094U, 0x00000000U);

    HW_SCE_p_func_sub015(0x00007c07U, 0x00602000U);
}
