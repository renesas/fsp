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

void r_rsip_func082 (void)
{
    r_rsip_func100(bswap_32big(0x85e2aebeU),
                   bswap_32big(0x98480a19U),
                   bswap_32big(0xffcf0a19U),
                   bswap_32big(0x4eb8c805U));
    WR1_PROG(REG_1600H, 0x0000b540U);
    WR1_PROG(REG_1600H, 0x000001d0U);
    WR1_PROG(REG_1608H, 0x8188000aU);

    WR1_PROG(REG_1A24H, 0x08000085U);
    WR1_PROG(REG_1400H, 0x00890011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x24fa535aU),
                   bswap_32big(0x33c4841dU),
                   bswap_32big(0x567dacccU),
                   bswap_32big(0x475ab5a9U));
    WR1_PROG(REG_1A24H, 0x08000095U);
    WR1_PROG(REG_1400H, 0x00890011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x9cef12b2U),
                   bswap_32big(0x31d8c68fU),
                   bswap_32big(0x94279a36U),
                   bswap_32big(0xbda605daU));

    WR1_PROG(REG_1600H, 0x0000b540U);
    WR1_PROG(REG_1600H, 0x000001c0U);
    WR1_PROG(REG_1608H, 0x8184000aU);

    WR1_PROG(REG_1A24H, 0x080000c5U);
    WR1_PROG(REG_1400H, 0x00890011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1A24H, 0x0b040104U);
    WR1_PROG(REG_1608H, 0x810100e0U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1608H, 0x80040140U);
    WR1_PROG(REG_1400H, 0x03420011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x00008d40U);
    WR1_PROG(REG_1600H, 0x00ffffffU);
    WR1_PROG(REG_1600H, 0x00009140U);
    WR1_PROG(REG_1600H, 0x01000000U);

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x30009105U);

    WR1_PROG(REG_1608H, 0x81040140U);
    WR1_PROG(REG_1400H, 0x00890011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000004U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1600H, 0x00008d40U);
    WR1_PROG(REG_1600H, 0x00ffffffU);
    WR1_PROG(REG_1600H, 0x00009140U);
    WR1_PROG(REG_1600H, 0x02000000U);

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x30009105U);

    WR1_PROG(REG_1608H, 0x81040140U);
    WR1_PROG(REG_1400H, 0x00890011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000004U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1400H, 0x01420021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
