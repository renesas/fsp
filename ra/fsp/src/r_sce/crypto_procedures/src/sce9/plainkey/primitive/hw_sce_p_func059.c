/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func059 (void)
{
    static const uint32_t Param_func059_func100_001[] =
    {
        0xaf5c1169U, 0xccd8bd52U, 0x88a2f82fU, 0xd9406fc9U,
    };
    HW_SCE_p_func100(Param_func059_func100_001);
    HW_SCE_p_func_sub022(0x00008d40U, 0x00ffffffU, 0x00009140U, 0x01000000U);

    HW_SCE_p_func_sub012(0x00000052U, 0x00442a0cU, 0x00000000U);

    WR1_PROG(REG_C4H, 0x00082e0dU);
    HW_SCE_p_func_sub010(0x81040140U, 0x00002813U);

    static const uint32_t Param_func059_func100_002[] =
    {
        0xef23bf66U, 0x10c19a29U, 0x3551f208U, 0xce071e80U,
    };
    HW_SCE_p_func100(Param_func059_func100_002);
    HW_SCE_p_func_sub022(0x00008d40U, 0x00ffffffU, 0x00009140U, 0x02000000U);

    WR1_PROG(REG_C4H, 0x00092e0dU);
    HW_SCE_p_func_sub010(0x81040140U, 0x00002813U);

    WR1_PROG(REG_ECH, 0x00007c1dU);
    WR1_PROG(REG_1CH, 0x00602000U);
}
