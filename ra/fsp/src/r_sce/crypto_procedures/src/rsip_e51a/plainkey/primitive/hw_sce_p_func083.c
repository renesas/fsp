/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func083 (void)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1600H, 0x000034a4U);

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x584c6f1dU);

    WR1_PROG(REG_1600H, 0x0000b7a0U);
    WR1_PROG(REG_1600H, 0x00000004U);

    WR1_PROG(REG_1600H, 0x00000b9cU);
    WR1_PROG(REG_1444H, 0x00000da7U);
    WR1_PROG(REG_1608H, 0x808e001cU);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000000aU));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000000cU));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000000eU));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000010U));
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
    WR1_PROG(REG_1420H, change_endian_long(0x00000022U));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000024U));
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000026U));
    WR1_PROG(REG_1458H, 0x00000000U);

    for (iLoop = 0U; iLoop < 14U; iLoop++)
    {
        WR1_PROG(REG_1600H, 0x00003bdcU);

        WR1_PROG(REG_1600H, 0x3800089eU);
        WR1_PROG(REG_1600H, 0x100034a7U);

        WR1_PROG(REG_1600H, 0x0000279dU);
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00003485U);
}
