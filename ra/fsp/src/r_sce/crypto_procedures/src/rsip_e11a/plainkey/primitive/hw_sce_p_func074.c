/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func074 (void)
{
    HW_SCE_p_func_sub001(0x30003020U, 0x00050020U, 0x0000b4c0U);
    HW_SCE_p_func_sub001(0x00000023U, 0x00030040U, 0x0000b4c0U);
    HW_SCE_p_func_sub001(0x0000001dU, 0x00070040U, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000017U);
    WR1_PROG(REG_94H, 0x00000080U);
}
