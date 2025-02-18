/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

void r_rsip_func100 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4)
{
    WR1_PROG(REG_00D0H, 0x0a0701f5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_PROG(REG_002CH, ARG1, ARG2, ARG3, ARG4);
    WAIT_STS(REG_00C8H, 16, 0);
}
