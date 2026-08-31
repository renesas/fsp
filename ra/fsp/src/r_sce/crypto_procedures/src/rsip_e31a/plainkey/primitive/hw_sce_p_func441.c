/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func441 (const uint32_t ARG1[], const uint32_t ARG2[])
{
    WR1_PROG(REG_94H, 0x00003467U);

    static const uint32_t Param_func441_sub100_001[] =
    {
        0x5362e9aaU, 0xdf94cad7U, 0x89811c51U, 0x531fa2eaU, 0x00000441U, 0x4c1f7a94U, 0xe14c9e3bU, 0x57b44f18U,
        0x8f4d7965U, 0x00000441U, 0x944e4636U, 0x32c65948U, 0x2e924804U, 0x5e859e5fU, 0x0000141eU, 0x437e5b64U,
        0xc27d48b5U, 0x1fc92ab1U, 0x954d09a9U, 0x0000141eU, 0xcde689ecU, 0xb9778a59U, 0xe28e91bbU, 0x260b83d3U,
    };
    HW_SCE_p_func_sub100(ARG1, ARG2, Param_func441_sub100_001, RSIP_SEL_BIT_LENGTH_256);

    WR1_PROG(REG_94H, 0x000034e3U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
