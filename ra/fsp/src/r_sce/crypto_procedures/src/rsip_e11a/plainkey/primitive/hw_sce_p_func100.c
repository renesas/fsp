/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func100 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4)
{
    WR1_PROG(REG_D0H, 0x0a0701f5U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_PROG(REG_2CH, change_endian_long(ARG1), change_endian_long(ARG2), change_endian_long(ARG3),
             change_endian_long(ARG4));
    WAIT_STS(REG_C8H, 16, 0);
}
