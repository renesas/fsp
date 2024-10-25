/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes192GcmDecryptUpdateTransitionSub (void)
{
    WR1_PROG(REG_1824H, 0x08000045U);
    WR1_PROG(REG_1608H, 0x81040080U);
    WR1_PROG(REG_1400H, 0x00490011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_182CH, 0x40000030U);
    WR1_PROG(REG_1824H, 0x07008c04U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));
}
