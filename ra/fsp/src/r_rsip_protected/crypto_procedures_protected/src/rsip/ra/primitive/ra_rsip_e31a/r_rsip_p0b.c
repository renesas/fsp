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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

rsip_ret_t r_rsip_p0b (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x000b0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0x31cb70e6U),
                   bswap_32big(0x6e37642fU),
                   bswap_32big(0xbf6a794eU),
                   bswap_32big(0xa3171b8eU));
    r_rsip_func103();
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

    r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

    WR1_PROG(REG_0094H, 0x000034c0U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000000bU, 0x00000000U);

    r_rsip_func101(bswap_32big(0xa0ee1bf9U),
                   bswap_32big(0xd764c4ffU),
                   bswap_32big(0xef31fc35U),
                   bswap_32big(0x85c39dd5U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x0000001bU);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000000bU, 0x00000000U);

    r_rsip_func101(bswap_32big(0x1e3b1f33U),
                   bswap_32big(0x592c1962U),
                   bswap_32big(0xbf68bd87U),
                   bswap_32big(0x782ec3fdU));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xc0dedf8eU),
                   bswap_32big(0x64c59c01U),
                   bswap_32big(0x0e290b37U),
                   bswap_32big(0x73a8f6aaU));
    r_rsip_func103();

    r_rsip_func100(bswap_32big(0xf7a485d3U),
                   bswap_32big(0xcdf80844U),
                   bswap_32big(0xf15ea782U),
                   bswap_32big(0x48221169U));
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub007(0x00000821U, 0x80840001U, 0x03410011U);

    r_rsip_func103();

    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    r_rsip_func_sub007(0x00000010U, 0x80840001U, 0x03410011U);

    r_rsip_func100(bswap_32big(0xf5950164U),
                   bswap_32big(0xe81ff0fbU),
                   bswap_32big(0x204fa4bcU),
                   bswap_32big(0x62257242U));
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe7009d07U);
    r_rsip_func_sub007(0x00000821U, 0x81880001U, 0x00490021U);

    WR1_PROG(REG_0008H, 0x00001022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

    r_rsip_func100(bswap_32big(0xba8c9524U),
                   bswap_32big(0x2697967eU),
                   bswap_32big(0x7bcc4d5fU),
                   bswap_32big(0xc5c68326U));
    r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

    r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);

    r_rsip_func100(bswap_32big(0x741bfbcaU),
                   bswap_32big(0xed3d684cU),
                   bswap_32big(0x7dfca7f3U),
                   bswap_32big(0x5aa97244U));
    r_rsip_func_sub017(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

    r_rsip_func102(bswap_32big(0x672b0866U),
                   bswap_32big(0x7f740ac0U),
                   bswap_32big(0x6c213e16U),
                   bswap_32big(0x4e3645d6U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
