/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_Aes256GcmDecryptUpdateTransitionSub (void)
{
    WR1_PROG(REG_D0H, 0x08000045U);
    HW_SCE_p_func_sub013(0x81840001U);
    HW_SCE_p_func_sub002(0x00490011U);

    HW_SCE_p_func_sub007(0x000000a1U, 0x40000020U, 0x07008c04U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
}
