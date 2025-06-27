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

void r_rsip_func081 (void)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0094H, 0x00000821U);

    WR1_PROG(REG_0094H, 0x0000b4e0U);
    WR1_PROG(REG_0094H, 0x00000016U);

    WR1_PROG(REG_0094H, 0x00000842U);
    WR1_PROG(REG_0014H, 0x000005a7U);
    WR1_PROG(REG_009CH, 0x80860002U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000016U));
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000018U));
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000001cU));
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000001eU));
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000022U));
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000026U));
    WR1_PROG(REG_0024H, 0x00000000U);

    for (iLoop = 0U; iLoop < 6; iLoop++)
    {
        WR1_PROG(REG_0094H, 0x000038a2U);

        WR1_PROG(REG_0094H, 0x38000885U);
        WR1_PROG(REG_0094H, 0x10003427U);

        WR1_PROG(REG_0094H, 0x0000a440U);
        WR1_PROG(REG_0094H, 0x00000004U);
    }
}
