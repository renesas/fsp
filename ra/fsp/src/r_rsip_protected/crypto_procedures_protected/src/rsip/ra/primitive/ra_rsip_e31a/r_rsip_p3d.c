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

rsip_ret_t r_rsip_p3d (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x003d0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0xf12f7d67U),
                   bswap_32big(0x667db8bdU),
                   bswap_32big(0xdc0dc64dU),
                   bswap_32big(0x33314c61U));
    r_rsip_func103();
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

    r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

    WR1_PROG(REG_0094H, 0x000034c0U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000003dU, 0x00000000U);

    r_rsip_func101(bswap_32big(0x907e92cbU),
                   bswap_32big(0x71fd6ad8U),
                   bswap_32big(0x3340c26fU),
                   bswap_32big(0x071636fdU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000029U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000003dU, 0x00000000U);

    r_rsip_func101(bswap_32big(0x43b3a583U),
                   bswap_32big(0xa214b777U),
                   bswap_32big(0xcece4f66U),
                   bswap_32big(0x9596b56dU));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x245cced6U),
                   bswap_32big(0x837c3fceU),
                   bswap_32big(0x84c176e0U),
                   bswap_32big(0x543e85a7U));
    r_rsip_func103();

    r_rsip_func100(bswap_32big(0x75032959U),
                   bswap_32big(0x0e349884U),
                   bswap_32big(0xc4d9a2b3U),
                   bswap_32big(0x5b300a51U));
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub007(0x00000821U, 0x80840001U, 0x03410011U);

    r_rsip_func103();

    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    r_rsip_func_sub007(0x00000010U, 0x80840001U, 0x03410011U);

    r_rsip_func100(bswap_32big(0x86269470U),
                   bswap_32big(0x22f0c182U),
                   bswap_32big(0x45b107baU),
                   bswap_32big(0x1ce24012U));
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe7009d07U);
    r_rsip_func_sub007(0x00000821U, 0x81880001U, 0x00490021U);

    WR1_PROG(REG_0008H, 0x00001022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

    r_rsip_func100(bswap_32big(0x458ff219U),
                   bswap_32big(0xa2d6a314U),
                   bswap_32big(0x4f191acdU),
                   bswap_32big(0xc96aafceU));
    r_rsip_func103();

    r_rsip_func100(bswap_32big(0x1e252ec6U),
                   bswap_32big(0xda6b226fU),
                   bswap_32big(0x06866e12U),
                   bswap_32big(0xda63a593U));
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub007(0x00000821U, 0x80840001U, 0x03410011U);

    r_rsip_func103();

    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    r_rsip_func_sub007(0x00000010U, 0x80840001U, 0x03410011U);

    r_rsip_func100(bswap_32big(0x63c2577fU),
                   bswap_32big(0x52f66878U),
                   bswap_32big(0xab937587U),
                   bswap_32big(0xa32c0c05U));
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe7008d07U);
    r_rsip_func_sub007(0x00000821U, 0x81880001U, 0x00490021U);

    WR1_PROG(REG_0008H, 0x00001022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[13]);

    r_rsip_func100(bswap_32big(0xf95f4767U),
                   bswap_32big(0x25c0e757U),
                   bswap_32big(0xbf39e6faU),
                   bswap_32big(0x37642446U));
    r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

    r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[17]);

    r_rsip_func100(bswap_32big(0x134c9efdU),
                   bswap_32big(0x78f933a8U),
                   bswap_32big(0x7a98dc38U),
                   bswap_32big(0x78a09080U));
    r_rsip_func_sub017(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

    r_rsip_func102(bswap_32big(0x06b85d66U),
                   bswap_32big(0xe13b94d7U),
                   bswap_32big(0x061a653cU),
                   bswap_32big(0x7e40d884U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
