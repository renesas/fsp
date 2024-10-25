/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func102(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4)
{
    WR1_PROG(REG_1A24H, 0x0a0701d5U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_PROG(REG_1420H, change_endian_long(ARG1), change_endian_long(ARG2), change_endian_long(ARG3), change_endian_long(ARG4));
}

