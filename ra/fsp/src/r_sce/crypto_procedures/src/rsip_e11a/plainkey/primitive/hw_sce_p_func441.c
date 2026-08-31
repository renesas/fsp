/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func441 (const uint32_t ARG1[], const uint32_t ARG2[])
{
    WR1_PROG(REG_94H, 0x00003467U);

    static const uint32_t Param_func441_sub100_001[] =
    {
        0x05ba1b01U, 0x13de7084U, 0x3238967dU, 0xab7c2361U, 0x00000441U, 0xe96bb24bU, 0xa544e9abU, 0x36b0abb7U,
        0x9d3694d8U, 0x00000441U, 0x86a643bdU, 0x27c5759dU, 0x8669ed95U, 0x3fd98745U, 0x0000141eU, 0xf49149bdU,
        0xc1fca362U, 0x9bef778bU, 0xb7966351U, 0x0000141eU, 0x2f19ff8fU, 0x1e52ce0aU, 0x3c661cc8U, 0xaea73b56U,
    };
    HW_SCE_p_func_sub100(ARG1, ARG2, Param_func441_sub100_001);

    WR1_PROG(REG_94H, 0x000034e3U);

    HW_SCE_p_func_sub015(0x00007c07U, 0x00602000U);
}
