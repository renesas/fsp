/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func323 (void)
{
    WR1_PROG(REG_24H, 0x00001dc0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_24H, 0x000060d0U);
    HW_SCE_p_func_sub015(0x000002c0U, 0x00a30001U);
    WR1_PROG(REG_24H, 0x00000981U);
    HW_SCE_p_func_sub015(0x000040c1U, 0x009f0001U);
    WR1_PROG(REG_24H, 0x000019c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_24H, 0x0000a0d0U);
    HW_SCE_p_func_sub015(0x000002c0U, 0x00a30001U);
    WR1_PROG(REG_24H, 0x00001181U);
    HW_SCE_p_func_sub015(0x000080c1U, 0x00a70001U);
    WR1_PROG(REG_2CH, 0x00000000U);
    WR1_PROG(REG_24H, 0x0000480aU);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_34H, 0x00000003U);
    HW_SCE_p_func_sub006(0x800068d0U, 0x00000c02U, 0x800048d0U);
    WR1_PROG(REG_34H, 0x00000801U);
    HW_SCE_p_func_sub001(0x800048d0U, 0x00000400U, 0x800048d0U, 0x000054d0U);
    WR1_PROG(REG_24H, 0x0000a0d0U);
    WAIT_STS(REG_24H, 21, 0);
}
