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

void r_rsip_func043 (void)
{
    r_rsip_func100(bswap_32big(0x6ab71710U),
                   bswap_32big(0xb914c763U),
                   bswap_32big(0x60a8d359U),
                   bswap_32big(0xb76d5418U));
    WR1_PROG(REG_1600H, 0x0000b540U);
    WR1_PROG(REG_1600H, 0x000001d0U);
    WR1_PROG(REG_1608H, 0x8188000aU);

    WR1_PROG(REG_1A24H, 0x08000085U);
    WR1_PROG(REG_1400H, 0x00890011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x6a1baa91U),
                   bswap_32big(0x0f3acd3dU),
                   bswap_32big(0x401977b6U),
                   bswap_32big(0xb1b408a5U));
    WR1_PROG(REG_1A24H, 0x08000095U);
    WR1_PROG(REG_1400H, 0x00890011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0xcbbf314bU),
                   bswap_32big(0x8579611fU),
                   bswap_32big(0x5e2a7cf5U),
                   bswap_32big(0x3cff2581U));

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
    WR1_PROG(REG_1A24H, 0x30009045U);
    WR1_PROG(REG_1608H, 0x81040140U);
    WR1_PROG(REG_1400H, 0x00890011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000004U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    r_rsip_func100(bswap_32big(0xb63c4bacU),
                   bswap_32big(0x458abb86U),
                   bswap_32big(0xb9a13e61U),
                   bswap_32big(0xb132cd47U));
    WR1_PROG(REG_1A24H, 0x08000085U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x915d9137U),
                   bswap_32big(0x7df2d248U),
                   bswap_32big(0xcc59b369U),
                   bswap_32big(0x184be643U));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000094U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
