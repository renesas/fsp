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

void r_rsip_func040 (void)
{
    r_rsip_func100(bswap_32big(0xde1b6cb4U),
                   bswap_32big(0xdd98add5U),
                   bswap_32big(0x7f36fb9dU),
                   bswap_32big(0x7cc785dbU));
    WR1_PROG(REG_00D0H, 0x4a470044U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_00D0H, 0x0e470484U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x01a5da45U));

    r_rsip_func100(bswap_32big(0x94c2b463U),
                   bswap_32big(0xb981928aU),
                   bswap_32big(0x1f24086bU),
                   bswap_32big(0xe0328ef8U));
    WR1_PROG(REG_00D0H, 0x4a470044U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_00D0H, 0x0e470494U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x02a5da45U));

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
