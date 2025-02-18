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

void r_rsip_func002 (void)
{
    WR1_PROG(REG_0000H, 0x01410041U);
    WR1_PROG(REG_0014H, 0x00000fa1U);

    WR1_PROG(REG_00D0H, 0x0c000105U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_PROG(REG_002CH, bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU));

    WR1_PROG(REG_00D0H, 0x0c100105U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_PROG(REG_002CH, bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU));

    WR1_PROG(REG_00D4H, 0x00000100U);
    WR1_PROG(REG_00D0H, 0x08008107U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_PROG(REG_002CH, bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU));
    WAIT_STS(REG_0014H, 31, 1);
    WR4_PROG(REG_002CH, bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU), bswap_32big(0x5c5c5c5cU));

    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
}
