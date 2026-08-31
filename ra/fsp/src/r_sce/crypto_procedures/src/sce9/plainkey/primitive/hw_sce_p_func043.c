/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func043 (void)
{
    static const uint32_t Param_func043_func100_001[] =
    {
        0x763017c1U, 0xa6e06e5cU, 0x413ee7c5U, 0x8be19d82U,
    };
    HW_SCE_p_func100(Param_func043_func100_001);
    WR1_PROG(REG_ECH, 0x0000b540U);
    WR1_PROG(REG_ECH, 0x000001d0U);
    WR1_PROG(REG_E0H, 0x8188000aU);

    HW_SCE_p_func_sub013(0x00080805U, 0x00002813U);

    static const uint32_t Param_func043_func100_002[] =
    {
        0x661813d3U, 0x1f0216ddU, 0xdb1c9067U, 0xe4e2daeeU,
    };
    HW_SCE_p_func100(Param_func043_func100_002);
    HW_SCE_p_func_sub013(0x00090805U, 0x00002813U);

    static const uint32_t Param_func043_func100_003[] =
    {
        0x41d550f1U, 0x3237f543U, 0x559f9bcaU, 0x9aceaba9U,
    };
    HW_SCE_p_func100(Param_func043_func100_003);

    WR1_PROG(REG_ECH, 0x0000b540U);
    WR1_PROG(REG_ECH, 0x000001c0U);
    WR1_PROG(REG_E0H, 0x8184000aU);

    HW_SCE_p_func_sub013(0x000c0805U, 0x00002813U);

    static const uint32_t Param_func043_func100_004[] =
    {
        0x3778e67fU, 0x59eb9657U, 0x649d9837U, 0x6e6ab952U,
    };
    HW_SCE_p_func100(Param_func043_func100_004);
    WR1_PROG(REG_C4H, 0x00000b8cU);
    HW_SCE_p_func_sub010(0x810100e0U, 0x00002807U);

    HW_SCE_p_func_sub010(0x80040140U, 0x00008213U);

    HW_SCE_p_func_sub022(0x00008d40U, 0x00ffffffU, 0x00009140U, 0x01000000U);

    HW_SCE_p_func_sub018(0x00000052U, 0x40000000U, 0x00448a04U);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_D0H, 0x40000000U);
    WR1_PROG(REG_C4H, 0x00008e95U);

    HW_SCE_p_func_sub010(0x81040140U, 0x00002813U);

    HW_SCE_p_func_sub022(0x00008d40U, 0x00ffffffU, 0x00009140U, 0x02000000U);

    HW_SCE_p_func_sub018(0x00000052U, 0x40000000U, 0x00448a04U);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_D0H, 0x40000000U);
    WR1_PROG(REG_C4H, 0x00098e15U);

    HW_SCE_p_func_sub010(0x81040140U, 0x00002813U);

    static const uint32_t Param_func043_func100_005[] =
    {
        0x1bbad22dU, 0xbc25efb7U, 0x0737ee54U, 0x5dcc4009U,
    };
    HW_SCE_p_func100(Param_func043_func100_005);
    HW_SCE_p_func_sub013(0x00080805U, 0x00002213U);

    WR1_PROG(REG_ECH, 0x00007c1dU);
    WR1_PROG(REG_1CH, 0x00602000U);
}
