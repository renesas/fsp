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

rsip_ret_t r_rsip_p40 (const uint32_t InData_LC[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00400001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    r_rsip_func048(InData_LC);

    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1600H, 0x0000000aU);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1600H, 0x10003401U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x10003401U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1600H, 0x10003401U);

    WR1_PROG(REG_1600H, 0x34202801U);
    WR1_PROG(REG_1600H, 0x20003401U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (InData_LC[0] == 0x00000000U)
    {
        WR1_PROG(REG_143CH, 0x00b80000U);

        r_rsip_func101(bswap_32big(0x87d73112U), bswap_32big(0x99489c5eU), bswap_32big(0xf20e6c89U),
                       bswap_32big(0x032ed21cU));
    }
    else if (InData_LC[0] == 0x00000001U)
    {
        WR1_PROG(REG_143CH, 0x00b00000U);

        r_rsip_func101(bswap_32big(0xec9bfc30U), bswap_32big(0xfb4affb3U), bswap_32big(0x6bb08ff3U),
                       bswap_32big(0x62202101U));
    }
    else if (InData_LC[0] == 0x00000004U)
    {
        WR1_PROG(REG_143CH, 0x00b30000U);

        r_rsip_func101(bswap_32big(0x86402685U), bswap_32big(0x1b8cfb91U), bswap_32big(0x6abda81cU),
                       bswap_32big(0x62d9c55fU));
    }
    else if (InData_LC[0] == 0x00000006U)
    {
        WR1_PROG(REG_143CH, 0x00b50000U);

        r_rsip_func101(bswap_32big(0x3e0f61a3U), bswap_32big(0xb24c4426U), bswap_32big(0x9999b1daU),
                       bswap_32big(0x6facaf71U));
    }
    else if (InData_LC[0] == 0x00000007U)
    {
        WR1_PROG(REG_143CH, 0x00b60000U);

        r_rsip_func101(bswap_32big(0x7895e3f6U), bswap_32big(0x5ff712f1U), bswap_32big(0x7ff1876fU),
                       bswap_32big(0x5cdceddcU));
    }
    else if (InData_LC[0] == 0x00000008U)
    {
        WR1_PROG(REG_143CH, 0x00b70000U);

        r_rsip_func101(bswap_32big(0x3a062cc7U), bswap_32big(0x70fe1d0cU), bswap_32big(0x75bc5cdcU),
                       bswap_32big(0xbc4ea24fU));
    }
    else if (InData_LC[0] == 0x00000009U)
    {
        WR1_PROG(REG_143CH, 0x00b90000U);

        r_rsip_func101(bswap_32big(0x2d92e5ebU), bswap_32big(0xa26ef03dU), bswap_32big(0x08914987U),
                       bswap_32big(0x5f530e60U));
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38000c00U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func101(bswap_32big(0x5de847ccU), bswap_32big(0x6e822bb4U), bswap_32big(0x1d247d2fU),
                       bswap_32big(0xf1d42455U));
    }

    r_rsip_func100(bswap_32big(0xccdbfba4U),
                   bswap_32big(0x31d111c4U),
                   bswap_32big(0x885a0cd4U),
                   bswap_32big(0xe3b36ac9U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x415a6dceU), bswap_32big(0x7a2bb17bU), bswap_32big(0x784354ccU),
                       bswap_32big(0xfda5486eU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000040U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x193e2eddU), bswap_32big(0x8264c7ccU), bswap_32big(0x702c0503U),
                       bswap_32big(0x7a200f8bU));
        r_rsip_func040();

        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d05U);
        WR1_PROG(REG_1438H, 0x20000000U);
        WR1_PROG(REG_1400H, 0x00880011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xf7008d05U);
        WR1_PROG(REG_1438H, 0x20000010U);
        WR1_PROG(REG_1400H, 0x00880011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x000001d0U);
        WR1_PROG(REG_1608H, 0x80880001U);
        WR1_PROG(REG_1400H, 0x03420021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x000001b0U);
        WR1_PROG(REG_1600H, 0x00003c01U);

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WR1_PROG(REG_1438H, 0x20000020U);
        WR1_PROG(REG_1400H, 0x00880011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1A24H, 0x8c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0x8f0ea4ceU), bswap_32big(0xdebcbecfU), bswap_32big(0x253b5caaU),
                       bswap_32big(0x8407d742U));
        WR1_PROG(REG_1A24H, 0x4a470044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1A24H, 0x0e4704c4U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0152db38U));

        WR1_PROG(REG_1A24H, 0x4a040044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1A24H, 0x0e040504U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x01f7370eU));

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x000001c0U);
        WR1_PROG(REG_1608H, 0x80840001U);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1B08H, 0x00000202U);

        r_rsip_func102(bswap_32big(0x14440fd8U), bswap_32big(0x7bc5db83U), bswap_32big(0x360b67c8U),
                       bswap_32big(0xeb01427aU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_PASS;
    }
}
