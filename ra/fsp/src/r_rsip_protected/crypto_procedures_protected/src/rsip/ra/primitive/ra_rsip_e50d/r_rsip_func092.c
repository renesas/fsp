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

void r_rsip_func092 (void)
{
    r_rsip_func100(bswap_32big(0xd4026ab7U),
                   bswap_32big(0x4cb770aaU),
                   bswap_32big(0x13d66d1dU),
                   bswap_32big(0x475c04ffU));
    WR1_PROG(REG_1600H, 0x00008d40U);
    WR1_PROG(REG_1600H, 0x00ffffffU);
    WR1_PROG(REG_1600H, 0x00009140U);
    WR1_PROG(REG_1600H, 0x01000000U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x4a060044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1A24H, 0x0e060084U);
    WR1_PROG(REG_1608H, 0x81010140U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0xda78a32dU),
                   bswap_32big(0x8e38a4c3U),
                   bswap_32big(0x0a6c4ff5U),
                   bswap_32big(0x1be859eaU));
    WR1_PROG(REG_1600H, 0x00008d40U);
    WR1_PROG(REG_1600H, 0x00ffffffU);
    WR1_PROG(REG_1600H, 0x00009140U);
    WR1_PROG(REG_1600H, 0x02000000U);

    WR1_PROG(REG_1A24H, 0x0e060094U);
    WR1_PROG(REG_1608H, 0x81010140U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x300032a0U);
    WR1_PROG(REG_1600H, 0x00070020U);
    WR1_PROG(REG_1600H, 0x0000b6e0U);
    WR1_PROG(REG_1600H, 0x1204c99cU);
    WR1_PROG(REG_1600H, 0x00030040U);
    WR1_PROG(REG_1600H, 0x0000b6e0U);
    WR1_PROG(REG_1600H, 0xa9ed4879U);
    WR1_PROG(REG_1600H, 0x00050040U);
    WR1_PROG(REG_1600H, 0x0000b6e0U);
    WR1_PROG(REG_1600H, 0x7c182e99U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1600H, 0x00008ee0U);
    WR1_PROG(REG_1600H, 0x00ffffffU);
    WR1_PROG(REG_1600H, 0x000092e0U);
    WR1_PROG(REG_1600H, 0x01000000U);

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x30009104U);
    WR1_PROG(REG_1608H, 0x810102e0U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000004U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1600H, 0x00008ee0U);
    WR1_PROG(REG_1600H, 0x00ffffffU);
    WR1_PROG(REG_1600H, 0x000092e0U);
    WR1_PROG(REG_1600H, 0x02000000U);

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x30009044U);
    WR1_PROG(REG_1608H, 0x810102e0U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000004U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    r_rsip_func100(bswap_32big(0x6aca5809U),
                   bswap_32big(0x331407fbU),
                   bswap_32big(0x0de35e2cU),
                   bswap_32big(0x40b6223eU));
    WR1_PROG(REG_1A24H, 0x08000085U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x34a533c2U),
                   bswap_32big(0x58750b30U),
                   bswap_32big(0x1133044cU),
                   bswap_32big(0x6f64466fU));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000094U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1600H, 0x00008ec0U);
    WR1_PROG(REG_1600H, 0x00ffffffU);
    WR1_PROG(REG_1600H, 0x000092c0U);
    WR1_PROG(REG_1600H, 0x01000000U);

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x30009104U);
    WR1_PROG(REG_1608H, 0x810102c0U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000004U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1600H, 0x00008ec0U);
    WR1_PROG(REG_1600H, 0x00ffffffU);
    WR1_PROG(REG_1600H, 0x000092c0U);
    WR1_PROG(REG_1600H, 0x02000000U);

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x30009044U);
    WR1_PROG(REG_1608H, 0x810102c0U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000004U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    r_rsip_func100(bswap_32big(0xd151f813U),
                   bswap_32big(0x3dd3ca1cU),
                   bswap_32big(0xf9386f7bU),
                   bswap_32big(0xfd4765d4U));
    WR1_PROG(REG_1A24H, 0x08000085U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x87ae7eedU),
                   bswap_32big(0x9dc63c83U),
                   bswap_32big(0x34600170U),
                   bswap_32big(0x7a232d88U));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000094U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
