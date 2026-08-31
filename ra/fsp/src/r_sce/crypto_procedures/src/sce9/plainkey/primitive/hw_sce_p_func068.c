/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func068 (void)
{
    static const uint32_t Param_func068_func100_001[] =
    {
        0xd4a52766U, 0x8a66b39cU, 0x3e9135a1U, 0x2cc5d444U,
    };
    HW_SCE_p_func100(Param_func068_func100_001);
    HW_SCE_p_func_sub022(0x00008d40U, 0x00ffffffU, 0x00009140U, 0x01000000U);

    HW_SCE_p_func_sub012(0x00000052U, 0x00442a0cU, 0x00000000U);

    WR1_PROG(REG_C4H, 0x00082e0cU);
    HW_SCE_p_func_sub010(0x81010140U, 0x00002807U);

    static const uint32_t Param_func068_func100_002[] =
    {
        0xb473d362U, 0xa92dfd51U, 0x9eb15e5aU, 0x0ba44048U,
    };
    HW_SCE_p_func100(Param_func068_func100_002);
    HW_SCE_p_func_sub022(0x00008d40U, 0x00ffffffU, 0x00009140U, 0x02000000U);

    WR1_PROG(REG_C4H, 0x00092e0cU);
    HW_SCE_p_func_sub010(0x81010140U, 0x00002807U);

    WR1_PROG(REG_ECH, 0x00007c1dU);
    WR1_PROG(REG_1CH, 0x00602000U);
}
