/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

void r_rsip_func424 (void)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1600H, 0x00000bffU);

    for (iLoop = 0U; iLoop < 4; iLoop++)
    {
        WR1_PROG(REG_1600H, 0x00003840U);
        WR1_PROG(REG_1600H, 0x00003861U);

        WR1_PROG(REG_1600H, 0x38000843U);
        WR1_PROG(REG_1600H, 0x2000b7e0U);
        WR1_PROG(REG_1600H, 0x1ae211e9U);

        WR1_PROG(REG_1600H, 0x0000a400U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000a420U);
        WR1_PROG(REG_1600H, 0x00000004U);
    }

    WR1_PROG(REG_1458H, 0x00000000U);
}
