/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func044 (void)
{
    HW_SCE_p_func_sub001(0x00008cc0U, 0x00ffffffU, 0x000090c0U, 0x01000000U);

    HW_SCE_p_func_sub021(0x40000000U, 0x30009104U, 0x810100c0U);
    HW_SCE_p_func_sub003(0x00490005U);

    HW_SCE_p_func_sub001(0x00008cc0U, 0x00ffffffU, 0x000090c0U, 0x02000000U);

    HW_SCE_p_func_sub021(0x40000000U, 0x30009044U, 0x810100c0U);
    HW_SCE_p_func_sub003(0x00490005U);

    static const uint32_t Param_func044_func100_001[] =
    {
        0xde92c9d7U, 0x4135eb5dU, 0x51204f50U, 0xba008022U,
    };
    HW_SCE_p_func100(Param_func044_func100_001);
    WR1_PROG(REG_D0H, 0x08000085U);
    HW_SCE_p_func_sub003(0x00410011U);

    static const uint32_t Param_func044_func100_002[] =
    {
        0x4d13874cU, 0x18c0031bU, 0x72e9c9e1U, 0x6c1ecdaaU,
    };
    HW_SCE_p_func100(Param_func044_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000094U, 0x00000000U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
