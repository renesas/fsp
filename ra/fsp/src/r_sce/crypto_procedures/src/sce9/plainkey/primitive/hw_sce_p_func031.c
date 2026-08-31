/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func031 (uint32_t ARG1[])
{
    HW_SCE_p_func_sub022(0x0000356aU, 0x0420a960U, 0x00000002U, 0x0001696bU);
    HW_SCE_p_func_sub022(0x00036d6bU, 0x00009160U, 0x00000042U, 0x00186d6bU);

    HW_SCE_p_func_sub022(0x00008c60U, 0x00ffffffU, 0x0000106bU, 0x000010c9U);

    WR1_PROG(REG_A4H, 0x00000885U);
    HW_SCE_p_func_sub010(0x81040060U, 0x00001813U);

    WR1_PROG(REG_ECH, 0x00000821U);
    HW_SCE_p_func_sub010(0x80840001U, 0x00008113U);

    WR1_PROG(REG_104H, 0x00000361U);
    WR1_PROG(REG_A4H, 0x00000885U);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &ARG1[0]);
    HW_SCE_p_func_sub010(0x80040180U, 0x00008113U);

    HW_SCE_p_func_sub022(0x0000b560U, 0x00000005U, 0x01906d6cU, 0x01906d8dU);
    WR1_PROG(REG_ECH, 0x000009adU);
    WR1_PROG(REG_ECH, 0x000009ceU);

    WR1_PROG(REG_A4H, 0x00000885U);
    HW_SCE_p_func_sub010(0x81040160U, 0x00001813U);

    WR1_PROG(REG_ECH, 0x0000a420U);
    WR1_PROG(REG_ECH, 0x00000010U);
    HW_SCE_p_func_sub010(0x80840001U, 0x00008113U);

    WR1_PROG(REG_B0H, 0x00000100U);
    WR1_PROG(REG_A4H, 0x00f08807U);
    WR1_PROG(REG_ECH, 0x00000821U);
    HW_SCE_p_func_sub010(0x81880001U, 0x00001823U);
}
