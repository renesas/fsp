/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func081 (void)
{
    uint32_t iLoop = 0U;

    HW_SCE_p_func_sub022(0x00003424U, 0x3420a880U, 0x0000000aU, 0x10000821U);

    HW_SCE_p_func_sub022(0x0000b4e0U, 0x0000000dU, 0x342028e4U, 0x10000821U);

    HW_SCE_p_func_sub022(0x0000b4e0U, 0x00000012U, 0x0000b7a0U, 0x00000004U);

    HW_SCE_p_func_sub005(0x00000bffU, 0x00000958U, 0x808a001fU, 0x00000012U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000014U));
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000016U));
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000018U));
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x0000001cU));
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x0000001eU));
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000020U));
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x0000000eU));
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000010U));
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000022U));

    for (iLoop = 0U; iLoop < 10U; iLoop++)
    {
        HW_SCE_p_func_sub022(0x00003bdfU, 0x3800089eU, 0x10003427U, 0x000027fdU);
    }
}
