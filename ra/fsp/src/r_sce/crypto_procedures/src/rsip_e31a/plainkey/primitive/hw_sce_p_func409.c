/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func409 (void)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_94H, 0x00000800U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_94H, 0x00000842U);
    WR1_PROG(REG_94H, 0x0000b460U);
    WR1_PROG(REG_94H, 0x0000001fU);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        WR1_PROG(REG_94H, 0x02003801U);
        WR1_PROG(REG_94H, 0x02003843U);
        WR1_PROG(REG_94H, 0x02003c41U);
        WR1_PROG(REG_94H, 0x02003c03U);

        WR1_PROG(REG_94H, 0x00002c20U);
        WR1_PROG(REG_94H, 0x00003060U);
    }
}
