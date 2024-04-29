/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

rsip_ret_t r_rsip_p16 (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00160001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0xd52ed01dU), bswap_32big(0x30b07d1bU), bswap_32big(0x84c0306dU), bswap_32big(0xd98cc76dU));
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
    WR1_PROG(REG_1420H, bswap_32big(0x00000016U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xf9c864f8U), bswap_32big(0x6a513fe2U), bswap_32big(0xee41edd4U), bswap_32big(0x5f7deef3U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000008U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000016U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xa4b38418U), bswap_32big(0xc019998cU), bswap_32big(0xe88e49d4U), bswap_32big(0x17b28f5eU));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x073ecd13U), bswap_32big(0xc52122d9U), bswap_32big(0x1c22a30aU), bswap_32big(0xc612613cU));
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

    r_rsip_func100(bswap_32big(0x5e1b4189U), bswap_32big(0x995f6815U), bswap_32big(0xe454dc90U), bswap_32big(0x8cc59da2U));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1608H, 0x80080000U);
    WR1_PROG(REG_1400H, 0x03420011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x4634b201U), bswap_32big(0x4a1784e1U), bswap_32big(0x9961c578U), bswap_32big(0xcbe7b7f6U));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1400H, 0x03420011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x47664939U), bswap_32big(0xb56c81b4U), bswap_32big(0x1be0f2cdU), bswap_32big(0x72e87248U));
    WR1_PROG(REG_1A2CH, 0x40000100U);
    WR1_PROG(REG_1A24H, 0xe7009d47U);
    WR1_PROG(REG_1608H, 0x81080000U);
    WR1_PROG(REG_1400H, 0x00890021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000003a2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108105U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_PROG(REG_1420H, bswap_32big(0x00000000U), bswap_32big(0x00000000U), bswap_32big(0x00000000U), bswap_32big(0x00000002U));

    WR1_PROG(REG_1408H, 0x00002032U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_KeyIndex[1]);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_KeyIndex[5]);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_KeyIndex[9]);

    r_rsip_func102(bswap_32big(0x87f143a8U), bswap_32big(0x9321a914U), bswap_32big(0xed53bf11U), bswap_32big(0x1d841416U));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
