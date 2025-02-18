/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128GcmDecryptUpdateTransitionSub (void)
{
    WR1_PROG(REG_D0H, 0x08000045U);
    WR1_PROG(REG_94H, 0x0000b420U);
    WR1_PROG(REG_94H, 0x00000010U);
    WR1_PROG(REG_9CH, 0x81840001U);
    WR1_PROG(REG_00H, 0x00490011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D4H, 0x00000020U);
    WR1_PROG(REG_D0H, 0x07008c04U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
}
