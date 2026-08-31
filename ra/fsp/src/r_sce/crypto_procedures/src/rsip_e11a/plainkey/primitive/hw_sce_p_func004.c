/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func004 (void)
{
    WR1_PROG(REG_F4H, 0x00000010U);

    WR1_PROG(REG_14H, 0x000007a4U);
    WAIT_STS(REG_14H, 31, 1);
    WR8_PROG(REG_2CH,
             change_endian_long(0x6a09e667U),
             change_endian_long(0xbb67ae85U),
             change_endian_long(0x3c6ef372U),
             change_endian_long(0xa54ff53aU),
             change_endian_long(0x510e527fU),
             change_endian_long(0x9b05688cU),
             change_endian_long(0x1f83d9abU),
             change_endian_long(0x5be0cd19U));
}
