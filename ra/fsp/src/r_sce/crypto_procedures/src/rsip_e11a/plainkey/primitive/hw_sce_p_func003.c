/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func003 (void)
{
    WR1_PROG(REG_F4H, 0x00000010U);

    WR1_PROG(REG_14H, 0x000007a4U);
    WAIT_STS(REG_14H, 31, 1);
    WR8_PROG(REG_2CH,
             change_endian_long(0xc1059ed8U),
             change_endian_long(0x367cd507U),
             change_endian_long(0x3070dd17U),
             change_endian_long(0xf70e5939U),
             change_endian_long(0xffc00b31U),
             change_endian_long(0x68581511U),
             change_endian_long(0x64f98fa7U),
             change_endian_long(0xbefa4fa4U));
}
