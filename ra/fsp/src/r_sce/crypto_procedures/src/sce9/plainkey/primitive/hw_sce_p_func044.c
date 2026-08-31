/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func044 (void)
{
    static const uint32_t Param_func044_func100_001[] =
    {
        0xcc2b6612U, 0x09aeabefU, 0xf30f09aaU, 0xcd0102c9U,
    };
    HW_SCE_p_func100(Param_func044_func100_001);
    HW_SCE_p_func_sub022(0x00008ce0U, 0x00ffffffU, 0x000090e0U, 0x01000000U);

    HW_SCE_p_func_sub018(0x00000052U, 0x40000000U, 0x00448a04U);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_D0H, 0x40000000U);
    WR1_PROG(REG_C4H, 0x00008e94U);
    HW_SCE_p_func_sub010(0x810100e0U, 0x00002807U);

    HW_SCE_p_func_sub022(0x00008ce0U, 0x00ffffffU, 0x000090e0U, 0x02000000U);

    HW_SCE_p_func_sub018(0x00000052U, 0x40000000U, 0x00448a04U);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_D0H, 0x40000000U);
    WR1_PROG(REG_C4H, 0x00098e14U);
    HW_SCE_p_func_sub010(0x810100e0U, 0x00002807U);

    static const uint32_t Param_func044_func100_002[] =
    {
        0x99fe09e3U, 0x8a2aaee4U, 0xdcec14e9U, 0x4d2dcd38U,
    };
    HW_SCE_p_func100(Param_func044_func100_002);
    HW_SCE_p_func_sub013(0x00080805U, 0x00002213U);

    WR1_PROG(REG_ECH, 0x00007c1dU);
    WR1_PROG(REG_1CH, 0x00602000U);
}
