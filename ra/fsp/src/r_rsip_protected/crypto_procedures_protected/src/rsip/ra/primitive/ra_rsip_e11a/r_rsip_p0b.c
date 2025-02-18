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

rsip_ret_t r_rsip_p0b (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x000b0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0x7667dd67U), bswap_32big(0xdf479f14U), bswap_32big(0x267d4696U), bswap_32big(0x769659a9U));
    r_rsip_func103();
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_009CH, 0x80010000U);
    WR1_PROG(REG_0000H, 0x03410005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0000H, 0x0001000dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x000034c0U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000000bU));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xd88a8727U), bswap_32big(0x9bc05470U), bswap_32big(0x78898577U), bswap_32big(0x1a66470fU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x0000001bU);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000000bU));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xce6d834aU), bswap_32big(0x9cea5ff2U), bswap_32big(0x0ed0a3f4U), bswap_32big(0x6dbf7291U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xc134c96aU), bswap_32big(0xd09a2756U), bswap_32big(0xe9e81f19U), bswap_32big(0x74815247U));
    r_rsip_func103();

    r_rsip_func100(bswap_32big(0x62e0df7eU), bswap_32big(0xd09160a4U), bswap_32big(0xb3ef725cU), bswap_32big(0xfb750681U));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0094H, 0x00000821U);
    WR1_PROG(REG_009CH, 0x80840001U);
    WR1_PROG(REG_0000H, 0x03410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func103();

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x00000010U);
    WR1_PROG(REG_009CH, 0x80840001U);
    WR1_PROG(REG_0000H, 0x03410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x0cbd7281U), bswap_32big(0x3cd224abU), bswap_32big(0x4437ea67U), bswap_32big(0xdb8ad7c8U));
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe7009d07U);
    WR1_PROG(REG_0094H, 0x00000821U);
    WR1_PROG(REG_009CH, 0x81880001U);
    WR1_PROG(REG_0000H, 0x00490021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

    r_rsip_func100(bswap_32big(0xf77e5cc8U), bswap_32big(0xa7fcecd0U), bswap_32big(0xf705ef52U), bswap_32big(0xbeca54bdU));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c000104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x09108105U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);

    r_rsip_func100(bswap_32big(0x10586f4dU), bswap_32big(0x463390ecU), bswap_32big(0xd2c4fd81U), bswap_32big(0xb531ef9cU));
    WR1_PROG(REG_009CH, 0x81010000U);
    WR1_PROG(REG_0008H, 0x00005006U);
    WAIT_STS(REG_0008H, 30, 1);
    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

    r_rsip_func102(bswap_32big(0xc28b6eebU), bswap_32big(0x48dff61cU), bswap_32big(0xf2aa636bU), bswap_32big(0x0140aa14U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
