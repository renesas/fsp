/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func074 (void)
{
    WR1_PROG(REG_94H, 0x30003020U);
    WR1_PROG(REG_94H, 0x00050020U);
    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000023U);
    WR1_PROG(REG_94H, 0x00030040U);
    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x0000001dU);
    WR1_PROG(REG_94H, 0x00070040U);
    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000017U);
    WR1_PROG(REG_94H, 0x00000080U);
}
