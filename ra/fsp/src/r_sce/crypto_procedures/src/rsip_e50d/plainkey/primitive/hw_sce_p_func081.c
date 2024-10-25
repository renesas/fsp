/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func081_r1 (void)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1600H, 0x00003424U);

    WR1_PROG(REG_1600H, 0x3420a880U);
    WR1_PROG(REG_1600H, 0x0000000aU);
    WR1_PROG(REG_1600H, 0x10000821U);

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x0000000dU);
    WR1_PROG(REG_1600H, 0x342028e4U);
    WR1_PROG(REG_1600H, 0x10000821U);

    WR1_PROG(REG_1600H, 0x38008880U);
    WR1_PROG(REG_1600H, 0x000000feU);
    WR1_PROG(REG_1600H, 0x1000b420U);
    WR1_PROG(REG_1600H, 0x0000000cU);

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000012U);

    WR1_PROG(REG_1600H, 0x0000b7a0U);
    WR1_PROG(REG_1600H, 0x00000004U);

    WR1_PROG(REG_1600H, 0x00000bffU);
    WR1_PROG(REG_1444H, 0x00000ba7U);
    WR1_PROG(REG_1608H, 0x808c001fU);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000012U));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000014U));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000016U));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000018U));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000001cU));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000001eU));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000020U));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000000eU));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000010U));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000022U));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000024U));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000026U));
    WR1_PROG(REG_1458H, 0x00000000U);

    for (iLoop = 0U; iLoop < 12U; iLoop++)
    {
        WR1_PROG(REG_1600H, 0x00003bdfU);

        WR1_PROG(REG_1600H, 0x3800089eU);
        WR1_PROG(REG_1600H, 0x10003427U);

        WR1_PROG(REG_1600H, 0x000027fdU);
    }

    WR1_PROG(REG_1458H, 0x00000000U);
}
