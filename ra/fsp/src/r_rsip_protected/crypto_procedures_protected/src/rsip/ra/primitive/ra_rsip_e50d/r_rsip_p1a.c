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

rsip_ret_t r_rsip_p1a (const uint32_t InData_DomainParam[],
                       uint32_t       OutData_PubKeyIndex[],
                       uint32_t       OutData_PrivKeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x0001a001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000008c8U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001a01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xd554bd5dU),
                   bswap_32big(0xc8ce8c28U),
                   bswap_32big(0x3f23c0f6U),
                   bswap_32big(0x21d5d25aU));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000050U);
    WR1_PROG(REG_1608H, 0x80840000U);
    WR1_PROG(REG_1400H, 0x03420011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001a02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xc591e0cdU),
                   bswap_32big(0xb821a25fU),
                   bswap_32big(0x7da1151cU),
                   bswap_32big(0xfd90c1bbU));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000040U);
    WR1_PROG(REG_1608H, 0x80840000U);
    WR1_PROG(REG_1400H, 0x03420011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_2000H, 0x00000001U);
    WR1_PROG(REG_2004H, 0x000000b0U);

    WR1_PROG(REG_1444H, 0x00000020U);
    WR1_PROG(REG_2014H, 0x00000000U);
    WR1_PROG(REG_1444H, 0x00000020U);
    WR1_PROG(REG_2010H, 0x00000100U);

    WR1_PROG(REG_1608H, 0x81880000U);
    WR1_PROG(REG_1400H, 0x01490021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WAIT_STS(REG_2030H, 4, 1);

    WR1_PROG(REG_1600H, 0x00000800U);
    WR1_PROG(REG_1608H, 0x80880000U);
    WR1_PROG(REG_1400H, 0x03450021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00050021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x00003820U);
    WR1_PROG(REG_1600H, 0x00008c20U);
    WR1_PROG(REG_1600H, 0xf8ffffffU);
    WR1_PROG(REG_1600H, 0x00003c20U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x0000001cU);

    WR1_PROG(REG_1600H, 0x00003820U);
    WR1_PROG(REG_1600H, 0x00008c20U);
    WR1_PROG(REG_1600H, 0xffffff3fU);
    WR1_PROG(REG_1600H, 0x00009020U);
    WR1_PROG(REG_1600H, 0x00000040U);
    WR1_PROG(REG_1600H, 0x00003c20U);

    WR1_PROG(REG_1600H, 0x00000800U);
    WR1_PROG(REG_1600H, 0x00000821U);
    WR1_PROG(REG_1600H, 0x00000842U);
    WR1_PROG(REG_1600H, 0x0000b460U);
    WR1_PROG(REG_1600H, 0x0000001fU);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        WR1_PROG(REG_1600H, 0x02003801U);
        WR1_PROG(REG_1600H, 0x02003843U);
        WR1_PROG(REG_1600H, 0x02003c41U);
        WR1_PROG(REG_1600H, 0x02003c03U);

        WR1_PROG(REG_1600H, 0x00002c20U);
        WR1_PROG(REG_1600H, 0x00003060U);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1004H, 0x00000000U);
    WR1_PROG(REG_1004H, 0x04040000U);

    r_rsip_func100(bswap_32big(0x7f914ae6U),
                   bswap_32big(0x5cb3110dU),
                   bswap_32big(0x6e09a0a2U),
                   bswap_32big(0xa0c9863eU));
    r_rsip_func401(InData_DomainParam);

    r_rsip_func100(bswap_32big(0x102c581fU),
                   bswap_32big(0x63de2631U),
                   bswap_32big(0x332030d7U),
                   bswap_32big(0x6e1d3e98U));
    r_rsip_func406(InData_DomainParam);

    WR1_PROG(REG_1404H, 0x15000000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000026U));
    WR1_PROG(REG_1400H, 0x00c00015U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c2000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00020005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1404H, 0x16400000U);
    WR1_PROG(REG_1400H, 0x00c00021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1404H, 0x16900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000026U));
    WR1_PROG(REG_1400H, 0x00c00015U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c2000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00020005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1404H, 0x16e00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000026U));
    WR1_PROG(REG_1400H, 0x00c00015U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c2000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00020005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1404H, 0x1b400000U);
    WR1_PROG(REG_1400H, 0x00c00021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1404H, 0x1b900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000026U));
    WR1_PROG(REG_1400H, 0x00c00015U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c2000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00020005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1404H, 0x1be00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000026U));
    WR1_PROG(REG_1400H, 0x00c00015U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c2000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00020005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x00000908U);
    WR1_PROG(REG_1600H, 0x00000800U);
    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1600H, 0x0000001fU);

    WR1_PROG(REG_1600H, 0x0000b660U);
    WR1_PROG(REG_1600H, 0x00000001U);

    WR1_PROG(REG_1600H, 0x0000b520U);
    WR1_PROG(REG_1600H, 0x00000100U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000001aU));
    WR1_PROG(REG_1458H, 0x00000000U);

    for (iLoop = 0U; iLoop < 256U; iLoop++)
    {
        r_rsip_func405();

        r_rsip_func403();

        r_rsip_func101(bswap_32big(0xec1b2ce2U), bswap_32big(0x09d227bfU), bswap_32big(0xd1ed09e3U),
                       bswap_32big(0x090c4fecU));
        r_rsip_func402();

        r_rsip_func404();

        WR1_PROG(REG_1600H, 0x00002d00U);

        r_rsip_func101(bswap_32big(0xe554e47eU), bswap_32big(0x3296aebcU), bswap_32big(0x412a548aU),
                       bswap_32big(0x9eeec0cfU));
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x08000909U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1014H, 0x00000660U);
    WR1_PROG(REG_1018H, 0x00000b10U);
    WR1_PROG(REG_1020H, 0x00000570U);

    WR1_PROG(REG_1004H, 0x0404000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x000006b0U);
    WR1_PROG(REG_1018H, 0x00000b10U);
    WR1_PROG(REG_1020H, 0x000005c0U);

    WR1_PROG(REG_1004H, 0x0404000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000700U);
    WR1_PROG(REG_1018H, 0x00000b10U);
    WR1_PROG(REG_1020H, 0x00000610U);

    WR1_PROG(REG_1004H, 0x0404000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000610U);
    WR1_PROG(REG_101CH, 0x00000070U);
    WR1_PROG(REG_1020H, 0x00000250U);
    WR1_PROG(REG_1010H, 0x00000008U);

    WR1_PROG(REG_1004H, 0x04040004U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x12d00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
    WR1_PROG(REG_1400H, 0x00c0001dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000070U);
    WR1_PROG(REG_1018H, 0x000002f0U);
    WR1_PROG(REG_1020H, 0x000002a0U);

    WR1_PROG(REG_1004H, 0x0404000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    r_rsip_func100(bswap_32big(0x0c9982c0U),
                   bswap_32big(0xcbb05197U),
                   bswap_32big(0x583cce74U),
                   bswap_32big(0x22f03686U));
    WR1_PROG(REG_1014H, 0x00000250U);
    WR1_PROG(REG_1018H, 0x000002a0U);
    WR1_PROG(REG_101CH, 0x00000070U);
    WR1_PROG(REG_1020H, 0x000002f0U);

    WR1_PROG(REG_1004H, 0x0404000fU);
    WR1_PROG(REG_1408H, 0x00020000U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000570U);
    WR1_PROG(REG_1018H, 0x000002f0U);
    WR1_PROG(REG_101CH, 0x00000070U);
    WR1_PROG(REG_1020H, 0x00000250U);

    WR1_PROG(REG_1004H, 0x04040002U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x000005c0U);
    WR1_PROG(REG_1018H, 0x000002f0U);
    WR1_PROG(REG_101CH, 0x00000070U);
    WR1_PROG(REG_1020H, 0x000002a0U);

    WR1_PROG(REG_1004H, 0x04040002U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x12800000U);
    WR1_PROG(REG_1600H, 0x00000821U);
    WR1_PROG(REG_1608H, 0x80880001U);
    WR1_PROG(REG_1400H, 0x03430021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x00003801U);
    WR1_PROG(REG_1600H, 0x00008c00U);
    WR1_PROG(REG_1600H, 0x7fffffffU);

    WR1_PROG(REG_1404H, 0x12300000U);
    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1600H, 0x00000020U);
    WR1_PROG(REG_1608H, 0x80880001U);
    WR1_PROG(REG_1400H, 0x03430021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1600H, 0x0000003cU);
    WR1_PROG(REG_1600H, 0x00003841U);

    WR1_PROG(REG_1600H, 0x001f6c42U);
    WR1_PROG(REG_1600H, 0x00001002U);

    WR1_PROG(REG_1600H, 0x00000821U);
    WR1_PROG(REG_1600H, 0x00003c01U);

    WR1_PROG(REG_1600H, 0x00000800U);
    WR1_PROG(REG_1600H, 0x00000821U);
    WR1_PROG(REG_1600H, 0x00000842U);
    WR1_PROG(REG_1600H, 0x0000b460U);
    WR1_PROG(REG_1600H, 0x0000001fU);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        WR1_PROG(REG_1600H, 0x02003801U);
        WR1_PROG(REG_1600H, 0x02003843U);
        WR1_PROG(REG_1600H, 0x02003c41U);
        WR1_PROG(REG_1600H, 0x02003c03U);

        WR1_PROG(REG_1600H, 0x00002c20U);
        WR1_PROG(REG_1600H, 0x00003060U);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001a03U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x7b72a8abU),
                   bswap_32big(0x8a09952eU),
                   bswap_32big(0x3e852eacU),
                   bswap_32big(0x3808d940U));
    r_rsip_func103();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1400H, 0x03420005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x000034e0U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001a01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x09b991b9U),
                   bswap_32big(0xc0a78c03U),
                   bswap_32big(0x9295e8c3U),
                   bswap_32big(0x37b6e1a5U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000027U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001a01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x8e8f190bU),
                   bswap_32big(0x18f82bb9U),
                   bswap_32big(0x551416bfU),
                   bswap_32big(0xbfe9a918U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x32ed748dU),
                   bswap_32big(0x7931b41fU),
                   bswap_32big(0xb590287aU),
                   bswap_32big(0x6f4df683U));
    WR1_PROG(REG_1A2CH, 0x40000100U);
    WR1_PROG(REG_1A24H, 0xe7009d07U);
    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1600H, 0x00000040U);
    WR1_PROG(REG_1608H, 0x81880001U);
    WR1_PROG(REG_1400H, 0x00890021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00002022U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[1]);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[5]);

    r_rsip_func100(bswap_32big(0x93ecbffbU),
                   bswap_32big(0xb67331d4U),
                   bswap_32big(0x8b2eb2a4U),
                   bswap_32big(0x91dab59bU));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108105U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[9]);

    r_rsip_func100(bswap_32big(0xce3b75bbU),
                   bswap_32big(0xd25eccfeU),
                   bswap_32big(0x220f01a3U),
                   bswap_32big(0xfbce9766U));
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_PrivKeyIndex[0]);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001a04U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xc6606eceU),
                   bswap_32big(0x66f719e9U),
                   bswap_32big(0xa978cb01U),
                   bswap_32big(0x4b4415ceU));
    r_rsip_func103();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1400H, 0x03420005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x000034e0U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001a02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x9f07471dU),
                   bswap_32big(0xb8fc4dcbU),
                   bswap_32big(0xf9562fe2U),
                   bswap_32big(0x954692e7U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000026U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001a02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xda7399faU),
                   bswap_32big(0xef82f87cU),
                   bswap_32big(0xa46328b2U),
                   bswap_32big(0xbb4bbc13U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x4a15e963U),
                   bswap_32big(0x5fc230e4U),
                   bswap_32big(0x48ffe099U),
                   bswap_32big(0xdecc5d81U));
    WR1_PROG(REG_1A2CH, 0x40000100U);
    WR1_PROG(REG_1A24H, 0xe8009107U);
    WR1_PROG(REG_1600H, 0x00000821U);
    WR1_PROG(REG_1608H, 0x81880001U);
    WR1_PROG(REG_1400H, 0x00890021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00002022U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[1]);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[5]);

    r_rsip_func100(bswap_32big(0xa5557d94U),
                   bswap_32big(0x07c7160eU),
                   bswap_32big(0xbde5e463U),
                   bswap_32big(0xc038adcfU));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[9]);

    r_rsip_func100(bswap_32big(0x53dc76eaU),
                   bswap_32big(0xa52ec353U),
                   bswap_32big(0x06f66599U),
                   bswap_32big(0xf6502fdaU));
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_PubKeyIndex[0]);

    r_rsip_func102(bswap_32big(0xf08d02c7U),
                   bswap_32big(0x51e1a254U),
                   bswap_32big(0x5de71d48U),
                   bswap_32big(0x681da887U));
    WR1_PROG(REG_14B8H, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
