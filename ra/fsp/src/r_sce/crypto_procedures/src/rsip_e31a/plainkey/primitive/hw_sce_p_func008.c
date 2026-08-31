/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func008 (void)
{
    HW_SCE_p_func_sub002(0x0037000fU, 0x00190005U, 0x04040002U);

    HW_SCE_p_func_sub002(0x00370014U, 0x001e0005U, 0x04040002U);

    HW_SCE_p_func_sub002(0x00190019U, 0x000f0005U, 0x04040002U);

    HW_SCE_p_func_sub002(0x005f000fU, 0x00140005U, 0x04040005U);

    HW_SCE_p_func_sub002(0x00190014U, 0x000f0005U, 0x04040002U);

    HW_SCE_p_func_sub002(0x0064000fU, 0x00140005U, 0x04040005U);

    HW_SCE_p_func_sub002(0x001e001eU, 0x000f0005U, 0x04040002U);

    HW_SCE_p_func_sub002(0x0014000fU, 0x00230000U, 0x0404000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    HW_SCE_p_func_sub002(0x000f0014U, 0x00230000U, 0x0404000aU);

    WR1_PROG(REG_40H, 0x00210000U);
}
